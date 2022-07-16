#include "loadcomtrade.h"
#include "dbtransienttaskrecorddao.h"
#include "dbtransienttasktmconfigdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <dbconnection.h>
#include <QSet>
#include <QFile>
#include <QDebug>
#include "unistd.h"
#include <QElapsedTimer>
#include <QCoreApplication>
#include <GenerateReport.h>

void Func_Sleep(uint msecond){
    QElapsedTimer t;
    t.start();
    while (t.elapsed() < msecond) {
        QCoreApplication::processEvents();
    }
}

LoadComtrade::LoadComtrade(QObject *parent): QObject(parent)
   ,p_cmtdFile(new CCmtdFile())
   ,wavePoints(0)
   ,nTbPos(0)
   ,totalPoints(0)
   ,jibaoFile(false)
//   ,readOver(false)
{
//    connect(p_cmtdFile->m_pThread, &ReadThread::SIG_ReadData_Finished, this, &LoadComtrade::readThFinished);
    utf8 = QTextCodec::codecForName("utf-8");
}

LoadComtrade::~LoadComtrade()
{
    if(p_cmtdFile!=nullptr){
        delete	p_cmtdFile;
    }

//    delete utf8;
}

bool LoadComtrade::init(const QString &strPath)
{
    if(Func_LoadCmtdFile(p_cmtdFile, strPath)){
//        QVector<double> sampleTimeVector = p_cmtdFile->m_pSampleTime;
        wavePoints = p_cmtdFile->m_pSegment->m_nWavePoints;
        totalPoints = p_cmtdFile->m_nTotalPoints;

//        float timeDiff = p_cmtdFile->m_dTimeSpan;

        QFile cfgFile(strPath);
        if(!cfgFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "Can't read cfg file!" << endl;
        }

        QList<QByteArray> cfgLine;
        while(!cfgFile.atEnd()){
           QByteArray line = cfgFile.readLine();
           cfgLine.append(line);
        }


        QString str = utf8->toUnicode(cfgLine.at(0));
        if(!strncmp(str.section(',', 0, 0).toLocal8Bit().constData(), "南瑞继保", strlen("南瑞继保"))
                ||
           !strncmp(str.section(',', 0, 0).toLocal8Bit().constData(), "NRR", strlen("NRR"))){
            jibaoFile = true;
        }

        //开关量总数
        QString dchTotalInfo = cfgLine.at(1);
        int dchanelNum = dchTotalInfo.section("," , 2, 2).section("D", 0, 0).toInt();
        QString dchTotalReal;
        int dchanelNumReal;

        for(int i=0; i<cfgLine.size(); i++){
            if(cfgLine.at(i) == "50\n" || cfgLine.at(i)=="50.000\n" || cfgLine.at(i)=="50.000000\n"){
                dchTotalReal = cfgLine.at(i - 1);
                dchanelNumReal = dchTotalReal.section(",", 0, 0).toInt();

                if(dchanelNumReal > dchanelNum){
                    dchIdVector.append(uncontinuous);
                    for(int j=dchanelNum; j>0; j--){
                        QString dchId = cfgLine.at(i - j);
                        int dchIdNum = dchId.section(",", 0, 0).toInt();
                        dchIdVector.append(dchIdNum);
                    }
                }else{
                    dchIdVector.append(continuous);
                }
            }

            if(cfgLine.at(i) == "BINARY\n" || cfgLine.at(i) == "ASCII\n"){
                strStartTime = cfgLine.at(i - 1);
                strLeftTime = cfgLine.at(i - 2);
                break;
            }
        }
        cfgFile.close();

        int ssStart = strStartTime.section(',', 1, 1).section(':', 2, 2).section('.', 0, 0).toInt();
        int ssLeft = strLeftTime.section(',', 1, 1).section(':', 2, 2).section('.', 0 , 0).toInt();

        int mesStart = strStartTime.section(',', 1, 1).section(':', 2, 2).section('.', 1, 1).toInt();
        int mesLeft = strLeftTime.section(',', 1, 1).section(':', 2, 2).section('.', 1 , 1).toInt();

        //突变点
        nTbPos = ((ssStart - ssLeft)*1000 + (mesStart - mesLeft)/1000)/((double)20/wavePoints);

        
//        }else{
//            for(int i=0; i<sampleTimeVector.size(); i++){
//                //如果最左采样时刻小于0
//                if(sampleTimeVector.at(0) < 0){
//                    if(0 == sampleTimeVector.at(i)){
//                        nTbPos = i;
//                        break;
//                    }
//                    //找到采样时刻大于等于timeDiff的点
//                }else if(sampleTimeVector.at(0) >= 0 && sampleTimeVector.at(i) >= timeDiff){
//                        nTbPos = i;
//                        break;
//                }
//            }
//        }
        if(nTbPos < wavePoints || totalPoints < 7*wavePoints){
            return false;
        }else{
            return true;
        }
    }else{
        return false;
    }
}

bool LoadComtrade::Func_LoadCmtdFile(CCmtdFile *pFile, const QString &strPath){
    if(!pFile->ReadComtradeFile(strPath))
    {
        return false;
    }

    const int Max_LoadFileTime = 60000;
    int nTimess = 0;
    while(!pFile->FileLoadFinished())
    {
        Func_Sleep(10);
        nTimess += 10;
        if(nTimess >= Max_LoadFileTime){
             break;
        }
    }

    if(nTimess >= Max_LoadFileTime){
        return false;
    }else{
        return true;
    }
    return true;
}

//同一个周波的突变前两周波和突变后六个周波
QMap<QVector<float>, QVector<float>> LoadComtrade::getSampleValue(int chseq)
{
    //一周波采样点
    QVector<float> aChanelat1;
    QVector<float> chopBefore1zhou;
    QVector<float> chopAfter1zhou;
    QMap<QVector<float>, QVector<float>> chopMap;

    aChanelat1 = p_cmtdFile->m_arAChanel.at(chseq)->m_pData;
    if(!jibaoFile){
        //1 circle before surge
        for(int i=nTbPos - wavePoints; i<=nTbPos; i++){
            chopBefore1zhou.append(aChanelat1.at(i));
        }

        //6 circle after surge
        for(int i=nTbPos; i<nTbPos + 6*wavePoints; i++){
            chopAfter1zhou.append(aChanelat1.at(i));
        }
    }else{
        //1 circle before surge
        for(int i=nTbPos - wavePoints; i<=nTbPos; i++){
            chopBefore1zhou.append(-1*aChanelat1.at(i));
        }

        //6 circle after surge
        for(int i=nTbPos; i<nTbPos + 6*wavePoints; i++){
            chopAfter1zhou.append(-1*aChanelat1.at(i));
        }
    }

    chopMap.insert(chopBefore1zhou, chopAfter1zhou);
    return chopMap;
}

int LoadComtrade::getSwitchStatus(const int& chseq)
{
    int switchStatus = 0;
    unsigned char* m_pDData = NULL;
    m_pDData = p_cmtdFile->m_arDChanel.at(chseq - 1)->m_pData.data();
    int dChPoints = p_cmtdFile->m_nTotalPoints;

    int a_nStartPos = 0;
    for(int i=0; i < dChPoints; i++){
        unsigned char ukg = 0x01;
        if(((m_pDData[(i+a_nStartPos)/8])&(ukg<<((i+a_nStartPos)%8))) == 0){
            switchStatus = 0;
        }else if(((m_pDData[(i+1+a_nStartPos)/8])&(ukg<<((i+1+a_nStartPos)%8))) != 0){
          switchStatus = 1;
          break;
        }
    }
    return switchStatus;
}

QList<int> LoadComtrade::getSwitchDelay(const int & chseq)
{
    unsigned char* m_pDData = NULL;
    m_pDData = p_cmtdFile->m_arDChanel.at(chseq - 1)->m_pData.data();
    int dChPoints = p_cmtdFile->m_nTotalPoints;
    int a_nStartPos = 0;
    unsigned char ukg = 0x01;
    QVector<int> positionVec;
    for(int i=0; i < dChPoints; i++){
        if(((m_pDData[(i + a_nStartPos)/8])&(ukg<<((i + a_nStartPos)%8))) != 0){
            positionVec.append(1);
        }
        else if(0 == ((m_pDData[(i+a_nStartPos)/8])&(ukg<<((i+a_nStartPos)%8))))
        {
            positionVec.append(0);
        }
    }
//        unsigned char ukg = 0x01;
//        if(((m_pDData[(i+a_nStartPos)/8])&(ukg<<((i+a_nStartPos)%8))) == 0
//            &&
//       ((m_pDData[(i+1+a_nStartPos)/8])&(ukg<<((i+1+a_nStartPos)%8))) != 0){
//          switchStatus = 1;
//          surgeNum = i;
//          break;
//        }else if(((m_pDData[(i+a_nStartPos)/8])&(ukg<<((i+a_nStartPos)%8))) != 0
//            &&
//        ((m_pDData[(i+1+a_nStartPos)/8])&(ukg<<((i+1+a_nStartPos)%8))) == 0){
//          switchStatus = 1;
//          surgeNum = i;
//          break;
//        }
//    }
    QList<int> surgeTimeList;
    for(int i=0; i<positionVec.size() - 1; i++){
        if(positionVec.at(i) != positionVec.at(i+1)){
            int timeDelay = (i - nTbPos)*((double)20/wavePoints);
            surgeTimeList.append(timeDelay);
        }
    }

    if(surgeTimeList.isEmpty()){
        surgeTimeList.append(0);
    }

    return surgeTimeList;
}


QStringList LoadComtrade::getChName()
{
    QList<QString> chNameList;
    foreach(CEleAChanel* varCh, p_cmtdFile->m_arAChanel){
        QString tmp = utf8->toUnicode(varCh->m_chName);
        chNameList.append(tmp);
        chNameList.append(varCh->m_chName);
    }
    return chNameList;
}

QStringList LoadComtrade::getSwitchName()
{
    QList<QString> switchChnameList;
    foreach(CEleDChanel* varCh, p_cmtdFile->m_arDChanel){
        QString tmp = utf8->toUnicode(varCh->m_chName);
        switchChnameList.append(tmp);
        switchChnameList.append(varCh->m_chName);
    }
    return switchChnameList;
}

QMap<QDateTime, int> LoadComtrade::getWavePoints()
{
    QDateTime tmStart;
    int wavePoints = 0;
    QMap<QDateTime, int> chopFactor;

    wavePoints = p_cmtdFile->m_pSegment->m_nWavePoints;

    QString day = strStartTime.section('/', 0, 0);
    QString month = strStartTime.section('/', 1, 1);
    QString year = strStartTime.section(',', 0, 0).section('/', 2, 2);

    QString hour = strStartTime.section(',', 1, 1).section(':', 0, 0);
    QString minute = strStartTime.section(',', 1, 1).section(':', 1, 1);
    QString second = strStartTime.section(',', 1, 1).section(':', 2, 2).section(".", 0, 0);

    QString mecSec = strStartTime.section('.', 1, 1);

    tmStart = QDateTime::fromString(year + "-" + month + "-" + day + " " + hour + ":" + minute + ":" + second + "." + mecSec.mid(0, 3), "yyyy-MM-dd hh:mm:ss.zzz");

    chopFactor.insert(tmStart, wavePoints);

    return chopFactor;
}

QMap<int, int> LoadComtrade::getChTotal()
{
    int nACount = 0;
    int nDCount = 0;
    QMap<int , int> countMap;

    nACount = p_cmtdFile->m_nACount;
    nDCount = p_cmtdFile->m_nDCount;
    
    countMap.insert(nACount, nDCount);

    return countMap;
}

int LoadComtrade::getStartPos(const int& wavePoints)
{
    int nTbPos = 0;
    int startPosition = 0;

    QVector<double> sampleTimeVector = p_cmtdFile->m_pSampleTime;
    float timeDiff = p_cmtdFile->m_dTimeSpan;
    for(int i=0; i<sampleTimeVector.size(); i++){
        //如果最左采样时刻小于0
        if(sampleTimeVector.at(0) < 0){
            if(sampleTimeVector.at(i) >= 0){
                nTbPos = i;
                break;
            }
            //找到采样时刻大于等于timeDiff的点
        }else if(sampleTimeVector.at(0) >= 0 && sampleTimeVector.at(i) >= timeDiff){
                nTbPos = i;
                break;
        }
    }

    startPosition = nTbPos - wavePoints - 1;

    return startPosition;
}

double LoadComtrade::getTotalTime()
{
   double valuePoint =0.0;
   QVector<double> sampleTimeVector = p_cmtdFile->m_pSampleTime;
   for(int i=sampleTimeVector.size() -1; i>0; i--){
       if(sampleTimeVector.at(i)!=0){
          valuePoint = sampleTimeVector.at(i);
          break;
       }
   }
   return valuePoint;
}

QDateTime LoadComtrade::getLeftTime()
{
    QString day = strLeftTime.section('/', 0, 0);
    QString month = strLeftTime.section('/', 1, 1);
    QString year = strLeftTime.section(',', 0, 0).section('/', 2, 2);

    QString hour = strLeftTime.section(',', 1, 1).section(':', 0, 0);
    QString minute = strLeftTime.section(',', 1, 1).section(':', 1, 1);
    QString second = strLeftTime.section(',', 1, 1).section(':', 2, 2).section(".", 0, 0);

    QString mecSec = strLeftTime.section('.', 1, 1);

    QDateTime leftTime = QDateTime::fromString(year + "-" + month + "-" + day + " " + hour + ":" + minute + ":" + second + "." + mecSec.mid(0, 3), "yyyy-MM-dd hh:mm:ss.zzz");
    return leftTime;
}

QVector<int> LoadComtrade::getDchIdVector()
{
    return dchIdVector;
}

//void LoadComtrade::readThFinished()
//{
//    readOver = true;
//}

