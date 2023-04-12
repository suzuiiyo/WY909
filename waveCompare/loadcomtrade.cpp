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

void Func_Sleep(uint msecond){
    QElapsedTimer t;
    t.start();
    while (t.elapsed() < msecond) {
        QCoreApplication::processEvents();
    }
}

LoadComtrade::LoadComtrade(QObject *parent): QObject(parent)
   , p_cmtdFile(new CCmtdFile())
   , wavePoints(0)
   , nTbPos(0)
   , lackChNum(0)
   , jibaoFile(false)
   , totalPoints(0)
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
        //按cfg时间算突变点
//        QVector<double> sampleTimeVector = p_cmtdFile->m_pSampleTime;
        wavePoints = p_cmtdFile->m_pSegment->m_nWavePoints;
        totalPoints = p_cmtdFile->m_nTotalPoints;

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

        QString dchTotalInfo = cfgLine.at(1);
        //模拟量总数
        int achanelNum = dchTotalInfo.section(",", 1, 1).section("A", 0, 0).toInt();
        for(int i=0; i<achanelNum; i++)
        {
            QString achanelInfo = cfgLine.at(i + 2);
            QString chseqNum = achanelInfo.section(",", 0, 0);
            QString itemType = achanelInfo.section(",", 4, 4);
            chseqItemTypeList.append(chseqNum);
            chseqItemTypeList.append(itemType);
        }

        //开关量总数
        int dchanelNum = dchTotalInfo.section("," , 2, 2).section("D", 0, 0).toInt();
        QString dchTotalReal;
        int dchanelNumReal;
        for(int i=0; i<cfgLine.size(); i++){
            if(cfgLine.at(i) == "50\n" || cfgLine.at(i) == "50.0\n" || cfgLine.at(i) == "50.00\n" || cfgLine.at(i)=="50.000\n" || cfgLine.at(i)=="50.0000\n"
               || cfgLine.at(i) == "50.00000\n" || cfgLine.at(i) == "50.000000\n"){
                dchTotalReal = cfgLine.at(i - 1);
                dchanelNumReal = dchTotalReal.section(",", 0, 0).toInt();

                //判断开关量通道号是否连续
                //如果连续第一位存0
                //如果不连续第一位存1，第二位存缺失的通道数
                if(dchanelNumReal > dchanelNum){
                    dchIdVector.append(uncontinuous);
                    lackChNum = dchanelNumReal - dchanelNum;
                    for(int j=dchanelNum; j>0; j--){
                        QString dchId = cfgLine.at(i - j);
                        int dchIdNum = dchId.section(",", 0, 0).toInt();
                        dchIdVector.append(dchIdNum);
                    }
                }else if(dchanelNumReal == dchanelNum){
                    dchIdVector.append(continuous);
                }
            }

            if(cfgLine.at(i) == "BINARY\n" || cfgLine.at(i) == "ASCII\n"){
                strStartTime = cfgLine.at(i - 1).trimmed();
                strLeftTime = cfgLine.at(i - 2).trimmed();
                break;
            }
        }
        cfgFile.close();

        QString mesStartStr = strStartTime.section('.', 1, 1);
        QString mesLeftStr = strLeftTime.section('.', 1 , 1);


        QString excMesStartTime = strStartTime.section('.', 0, 0);
        QString excMesLeftTime = strLeftTime.section('.', 0, 0);
        ulong allmesStartTime = QDateTime::fromString(excMesStartTime, "dd/MM/yyyy,hh:mm:ss").toSecsSinceEpoch();
        ulong allmesLeftTime = QDateTime::fromString(excMesLeftTime, "dd/MM/yyyy,hh:mm:ss").toSecsSinceEpoch();

//      //转换为6位
//      QString mesStart = QString("%1").arg(mesStartStr.toInt(), 6, 10, QLatin1Char('0'));
//      QString mesLeft = QString("%1").arg(mesLeftStr.toInt(), 6, 10, QLatin1Char('0'));

        for(int i=0; i< 6 - mesStartStr.size(); i++){
            mesStartStr = mesStartStr.trimmed() + "0";
        }

        for(int i=0; i< 6 - mesLeftStr.size(); i++){
            mesLeftStr = mesLeftStr.trimmed() + "0";
        }
        //零时刻
        //最左时刻和零时刻的标准格式，毫秒数应该是6位
        nTbPos = ((((allmesStartTime - allmesLeftTime)*1000 + (ceil(mesStartStr.toInt() - mesLeftStr.toInt())/1000)))*wavePoints)/20;

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

QString LoadComtrade::getSurgeTime()
{
    return strStartTime;
}

QList<QVector<float>> LoadComtrade::getSampleValue(const int& chseq, const int& surgeNum)
{
    //一周波采样点
    QVector<float> aChanelat1;
    QVector<float> chopBefore1zhou;
    QVector<float> chopAfter1zhou;
    QList<QVector<float>> chopList;

    //往前计算有效值
    //同一个周波的突变前三个周波和突变后六个周波
    aChanelat1 = p_cmtdFile->m_arAChanel.at(chseq - 1)->m_pData;
//    if(!jibaoFile){
//        //3 circle before surge
//        if(nTbPos >= 3*wavePoints){
//            for(int i=nTbPos - 3*wavePoints; i<=nTbPos; i++){
//                chopBefore1zhou.append(aChanelat1.at(i));
//            }
//        }else{
//            qDebug() << "录波文件A段不足3个波长";
//            exit(0);
//        }

//        //6 circle after surge
//        for(int i=nTbPos; i<=nTbPos + 6*wavePoints; i++){
//            chopAfter1zhou.append(aChanelat1.at(i));
//        }
//    }else{
//        //1 circle before surge
//        if(nTbPos >= 3*wavePoints){
//            for(int i=nTbPos - 3*wavePoints; i<=nTbPos; i++){
//                chopBefore1zhou.append(-1*aChanelat1.at(i));
//            }
//        }else{
//            qDebug() << "录波文件A段不足3个波长";
//            exit(0);
//        }

//        //6 circle after surge
//        for(int i=nTbPos; i<=nTbPos + 6*wavePoints; i++){
//            chopAfter1zhou.append(-1*aChanelat1.at(i));
//        }
//    }

    //往后计算有效值
    //同一个周波的突变前两个周波和突变后七个周波
    if(!jibaoFile){
       //往后计算有效值
       //考虑到移位， 前后各多取一个周波
       //突变前两个周波， 本身取一个，考虑偏移量一个周波， 往前推一个周波
        if(surgeNum >= 2*wavePoints){
            for(int i= surgeNum - 2*wavePoints; i<surgeNum; i++){
                chopBefore1zhou.append(aChanelat1.at(i));
            }
            //突变后七个周波， 本身取五个，考虑偏移量一个周波
            for(int i= surgeNum; i<surgeNum + 7*wavePoints; i++){
                chopAfter1zhou.append(aChanelat1.at(i));
            }
        }
        else
        {
            //不足两个周波有多少取多少
            for(int i=0; i<surgeNum; i++)
            {
                chopBefore1zhou.append(-1*aChanelat1.at(i));
            }
            //突变后七个周波
            for(int i=surgeNum; i<surgeNum + 7*wavePoints; i++)
            {
                chopAfter1zhou.append(-1*aChanelat1.at(i));
            }
        }
     }else{
        if(surgeNum >= 2*wavePoints){
            //突变前两个周波
            for(int i= surgeNum - 2*wavePoints; i<surgeNum; i++){
                chopBefore1zhou.append(-1*aChanelat1.at(i));
            }
            //突变后七个周波
            for(int i= surgeNum; i<surgeNum + 7*wavePoints; i++){
                chopAfter1zhou.append(-1*aChanelat1.at(i));
            }
        }
        else
        {
            //不足两个周波有多少取多少
            for(int i=0; i<surgeNum; i++)
            {
                chopBefore1zhou.append(-1*aChanelat1.at(i));
            }
            //突变后七个周波
            for(int i=surgeNum; i<surgeNum + 7*wavePoints; i++)
            {
                chopAfter1zhou.append(-1*aChanelat1.at(i));
            }
        }
    }
    chopList.append(chopBefore1zhou);
    chopList.append(chopAfter1zhou);
    return chopList;
}

QList<QVector<float> > LoadComtrade::getRecordSampleValue(const int&chseq, const int&surgeNum, const int& firPos)
{
    //一周波采样点
    QVector<float> aChanelat1;
    QVector<float> chopBefore1zhou;
    QVector<float> chopAfter1zhou;
    QList<QVector<float>> chopList;

    //往前计算有效值
    //同一个周波的突变前三个周波和突变后六个周波
    aChanelat1 = p_cmtdFile->m_arAChanel.at(chseq - 1)->m_pData;
//    if(!jibaoFile){
//        //3 circle before surge
//        if(nTbPos >= 3*wavePoints){
//            for(int i=nTbPos - 3*wavePoints; i<=nTbPos; i++){
//                chopBefore1zhou.append(aChanelat1.at(i));
//            }
//        }else{
//            qDebug() << "录波文件A段不足3个波长";
//            exit(0);
//        }

//        //6 circle after surge
//        for(int i=nTbPos; i<=nTbPos + 6*wavePoints; i++){
//            chopAfter1zhou.append(aChanelat1.at(i));
//        }
//    }else{
//        //1 circle before surge
//        if(nTbPos >= 3*wavePoints){
//            for(int i=nTbPos - 3*wavePoints; i<=nTbPos; i++){
//                chopBefore1zhou.append(-1*aChanelat1.at(i));
//            }
//        }else{
//            qDebug() << "录波文件A段不足3个波长";
//            exit(0);
//        }

//        //6 circle after surge
//        for(int i=nTbPos; i<=nTbPos + 6*wavePoints; i++){
//            chopAfter1zhou.append(-1*aChanelat1.at(i));
//        }
//    }

    //往后计算有效值
    //同一个周波的突变前两个周波和突变后七个周波
//    if(!jibaoFile){
//       //往后计算有效值
//       //考虑到移位， 前后各多取一个周波
//       //突变前两个周波， 本身取一个，考虑偏移量一个周波， 往前推一个周波
//        if(surgeNum >= 2*wavePoints){
//            for(int i= surgeNum - 2*wavePoints; i<surgeNum; i++){
//                chopBefore1zhou.append(aChanelat1.at(i));
//            }
//            //突变后七个周波， 本身取五个，考虑偏移量一个周波
//            for(int i= surgeNum; i<surgeNum + 7*wavePoints; i++){
//                chopAfter1zhou.append(aChanelat1.at(i));
//            }
//        }
//        else
//        {
//            //不足两个周波有多少取多少
//            for(int i=0; i<surgeNum; i++)
//            {
//                chopBefore1zhou.append(-1*aChanelat1.at(i));
//            }
//            //突变后七个周波
//            for(int i=surgeNum; i<surgeNum + 7*wavePoints; i++)
//            {
//                chopAfter1zhou.append(-1*aChanelat1.at(i));
//            }
//        }
//     }else{
//        if(surgeNum >= 2*wavePoints){
//            //突变前两个周波
//            for(int i= surgeNum - 2*wavePoints; i<surgeNum; i++){
//                chopBefore1zhou.append(-1*aChanelat1.at(i));
//            }
//            //突变后七个周波
//            for(int i= surgeNum; i<surgeNum + 7*wavePoints; i++){
//                chopAfter1zhou.append(-1*aChanelat1.at(i));
//            }
//        }
//        else
//        {
//            //不足两个周波有多少取多少
//            for(int i=0; i<surgeNum; i++)
//            {
//                chopBefore1zhou.append(-1*aChanelat1.at(i));
//            }
//            //突变后七个周波
//            for(int i=surgeNum; i<surgeNum + 7*wavePoints; i++)
//            {
//                chopAfter1zhou.append(-1*aChanelat1.at(i));
//            }
//        }
//    }
    if(!jibaoFile){
       //往后计算有效值
       //考虑到移位， 前后各多取一个周波
      //突变周波， 本身取一个，考虑偏移量一个周波， 往前推一个周波
       if(firPos >= 0){
           for(int i= firPos; i<surgeNum; i++){
                chopBefore1zhou.append(aChanelat1.at(i));
            }
            //突变后七个周波， 本身取五个，考虑偏移量一个周波
           for(int i= surgeNum; i<surgeNum + 7*wavePoints; i++){
                chopAfter1zhou.append(aChanelat1.at(i));
            }
        }
     }else{
        if(firPos >= 0){
            //突变前周波
            for(int i= firPos; i<surgeNum; i++){
                chopBefore1zhou.append(-1*aChanelat1.at(i));
            }
            //突变后七个周波
            for(int i= surgeNum; i<surgeNum + 7*wavePoints; i++){
                chopAfter1zhou.append(-1*aChanelat1.at(i));
            }
        }
    }
    chopList.append(chopBefore1zhou);
    chopList.append(chopAfter1zhou);
    return chopList;
}

int LoadComtrade::getSwitchStatus(const int& chseq)
{
    int switchStatus = 0;
    unsigned char* m_pDData = nullptr;
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

QMap<QString, QList<int>> LoadComtrade::getSwitchDelayMap(const int &chseq, const int&startPos)
{
    unsigned char* m_pDData = nullptr;
    m_pDData = p_cmtdFile->m_arDChanel.at(chseq  - 1)->m_pData.data();
    char* name = p_cmtdFile->m_arDChanel.at(chseq - 1)->m_chName;
    QTextCodec* codec = QTextCodec::codecForName("GBK");
    QString nameStr = codec->toUnicode(name);

    int dChPoints = p_cmtdFile->m_nTotalPoints;
    int a_nStartPos = 0;
    unsigned char ukg = 0x01;
    QVector<int> positionVec;
    for(int i=0; i < dChPoints; i++){
        //从开到合
        if(0 == (m_pDData[a_nStartPos/8]&(ukg<<((a_nStartPos)%8)))){
            if(0 == ((m_pDData[(i + a_nStartPos)/8])&(ukg<<((i + a_nStartPos)%8))))
            {
                positionVec.append(0);
            }
            else if(((m_pDData[(i+a_nStartPos)/8])&(ukg<<((i+a_nStartPos)%8))) != 0)
            {
                positionVec.append(1);
            }
            a_nStartPos++;
        //从合到开
        }else
        {
            if(((m_pDData[(i + a_nStartPos)/8])&(ukg<<((i + a_nStartPos)%8))) !=0)
            {
                positionVec.append(1);
            }
            else if(0 == ((m_pDData[(i+a_nStartPos)/8])&(ukg<<((i+a_nStartPos)%8))))
            {
                positionVec.append(0);
            }
            a_nStartPos++;
        }
    }

//    qDebug() << startPos << "开始序列号";
//    qDebug() << nTbPos << "突变点";

    QMap<QString, QList<int>> chNameDelayMap;
    QList<int> surgeTimeList;
    for(int i=0; i<positionVec.size() - 1; i++){
        if(positionVec.at(i) != positionVec.at(i+1)){
            //20毫秒一个周波
            int timeDelay = (i - startPos)*(20/wavePoints);
            surgeTimeList.append(timeDelay);
        }
    }

    //如果没有跳变，首位元素以0表示
    if(surgeTimeList.isEmpty()){
        surgeTimeList.append(0);
    }

    chNameDelayMap.insert(nameStr, surgeTimeList);
    qDebug() << chNameDelayMap << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    return chNameDelayMap;
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

int LoadComtrade::getWavePoints()
{
    int wavePoints = p_cmtdFile->m_pSegment->m_nWavePoints;
    return wavePoints;
}

QList<int> LoadComtrade::getChTotal()
{
    int nACount = 0;
    int nDCount = 0;
    QList<int> countList;

    nACount = p_cmtdFile->m_nACount;
    nDCount = p_cmtdFile->m_nDCount;

    countList.append(nACount);
    countList.append(nDCount);

    return countList;
}

int LoadComtrade::getStartPos(const int wavePoints, const int surgeNum)
{
    int startPosition = 0;
    if(surgeNum - 2*wavePoints > 0){
        startPosition = surgeNum - 2*wavePoints;
    }else{
        startPosition = 0;
    }

    return startPosition;
}

double LoadComtrade::getTotalTime()
{
   //重新计算时间序列
   double valuePoint =0.0;
   bool bIsSame = true;
   QVector<double> sampleTimeVector = p_cmtdFile->m_pSampleTime;
   //逐个元素和第一个比，如果有不同证明读取时间序列正常
   foreach(double time, sampleTimeVector){
       if(time - sampleTimeVector.first() > 0.00001){
           bIsSame = false;
           break;
       }
   }

   QVector<double> reSampleTimeVector;
   if(bIsSame){
        //每两点时间间隔
        float timeper = p_cmtdFile->m_dTimeSpan/nTbPos;
        for(int i=0; i<p_cmtdFile->m_pSampleTime.size(); i++){
            if(i<nTbPos){
                reSampleTimeVector.append(static_cast<double>((i-nTbPos)*timeper));
            }else if(i == nTbPos){
                reSampleTimeVector.append(0);
            }else if(i>nTbPos){
                reSampleTimeVector.append(static_cast<double>((i-nTbPos)*timeper));
            }
        }
   }

   if(!bIsSame){
       for(int i=sampleTimeVector.size() -1; i>0; i--){
          if(sampleTimeVector.at(0) >= 0.0 && sampleTimeVector.at(i) > 0.01){
            valuePoint = sampleTimeVector.at(i);
            break;
          }else if(sampleTimeVector.at(0) < 0.0 && sampleTimeVector.at(i) > 0.01){
            valuePoint = sampleTimeVector.at(i) - sampleTimeVector.at(0);
            break;
          }
       }
   }else if(bIsSame){
       for(int i=reSampleTimeVector.size() -1; i>0; i--){
          if(reSampleTimeVector.at(0) >= 0.0 && reSampleTimeVector.at(i) > 0.01){
            valuePoint = reSampleTimeVector.at(i);
            break;
          }else if(reSampleTimeVector.at(0) < 0.0 && reSampleTimeVector.at(i) > 0.01){
            valuePoint = reSampleTimeVector.at(i) - reSampleTimeVector.at(0);
            break;
          }
       }
   }
   return valuePoint;
}

QDateTime LoadComtrade::getLeftTime()
{
    QString day = strLeftTime.section('/', 0, 0);
    QString month = strLeftTime.section('/', 1, 1);
    QString year = strLeftTime.section(',', 0, 0).section('/', 2, 2);

    QString time = strLeftTime.section("/", 1, 2).section("/", 1, 1).section(",", 1, 2).section(".", 0, 0);
    QString mecSec = strLeftTime.section('.', 1, 1);

    QDateTime leftTime = QDateTime::fromString(year + "-" + month + "-" + day + " " + time + "." + mecSec.mid(0, 3), "yyyy-MM-dd hh:mm:ss.zzz");
    return leftTime;
}

QVector<int> LoadComtrade::getDchIdVector()
{
    return dchIdVector;
}

int LoadComtrade::getlackChNum()
{
    return lackChNum;
}

int LoadComtrade::getSurgeNum(const int& chseq)
{
    QString itemType = nullptr;
    //查找通道类型
    for(int i=0; i<chseqItemTypeList.size(); i++)
    {
        if(!QString::compare(chseqItemTypeList.at(i), QString::number(chseq)))
        {
            itemType.append(chseqItemTypeList.at(i+1));
        }
    }

    int newNtbPos = 0;
    QVector<float> sampleChop = p_cmtdFile->m_arAChanel.at(chseq - 1)->m_pData;
    if(!QString::compare(itemType, "V")){
        for(int n=0; n<sampleChop.size() - 2*wavePoints; n++)
        {
            if(fabs(static_cast<double>(sampleChop.at(n + wavePoints) - sampleChop.at(n)))
               >= 0.9){
                newNtbPos = n + wavePoints;
                break;
            }
        }
    }
    else if(!QString::compare(itemType, "A")){
        for(int n=0; n<sampleChop.size() - 2*wavePoints; n++)
        {
            if(fabs(static_cast<double>(sampleChop.at(n + wavePoints) - sampleChop.at(n)))
               >= 0.25){
                newNtbPos = n + wavePoints;
                break;
            }
        }
    }

    if(newNtbPos!=0 && newNtbPos != nTbPos && abs(newNtbPos -nTbPos) < 2*wavePoints)
    {
//返回突变点位置
//        return nTbPos;
        return newNtbPos;
    }else{
        return nTbPos;
    }
}

QVector<float> LoadComtrade::modifyWholeChop(const int& chseq)
{
    QVector<float> sampleChop = p_cmtdFile->m_arAChanel.at(chseq - 1)->m_pData;
    QVector<float> effectChop;

    for(int i=0; i<5*wavePoints; i++){
        QVector<float> uCalVector;
        float* p_data = new float[2*wavePoints];
        for(int j=i; j<2*wavePoints; j++){
            uCalVector.append(sampleChop.at(j));
        }

        //将值放到p_data里
        if(!uCalVector.empty()){
           memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof (float));
        }

        float drms = 0.0;
        if(wavePoints < 20)
        {
            for(int j=0; j<wavePoints; j++)
            {
                if(drms < fabs(p_data[i + j]))
                    drms = (float)(fabs(p_data[i + j]));
            }
            drms /= m_dsqt2;
            effectChop.append(drms);
            return effectChop;
        }

        /*
        float dreal = 0.0;
        float dimg = 0.0;
        int nsg = a_nWavePoints*50/1000;
        for(int i=0; i<20; i++)
        {
            dreal += a_pData[i*nsg]*m_gRealParam[20-i-1];
            dimg += a_pData[i*nsg]*m_gImgParam[20-i-1];
        }
            a_dAng = atan2(dimg,dreal) + g_dPI/2.0;
        if(a_dAng < 0.0000001)
        {
                a_dAng += 2.0*g_dPI;
        }
        dreal /= 4096.0;
        dimg /= 4096.0;
        drms = sqrt(dreal*dreal+dimg*dimg);
        drms /= m_dsqt2;
        */
        drms = DFT_CalHarm(p_data, wavePoints, 0, 1, 1);
        effectChop.append(drms);
    }

    return effectChop;
}

float LoadComtrade::DFT_CalHarm(float* p_data, int t_wavePoint, int a_Ang, int a_Harm, int nStep){
    float dRms = 0;
    //计算谐波
//    if(t_wavePoint < 20)
//    {
//        dRms = 0;
//        a_Ang = 0;
//        return dRms;
//    }
    float segmaa = 0.0;
    float segmab = 0.0;
    //////////////////////////////////////////////////////////////////////////
    //2009-10-10 修改
    /*
    Filter_Para(a_nHarm,m_dRe,m_dIm,a_nWavePoints);
    for(int i=0; i<a_nWavePoints; i++)
    {
    segmaa += a_pData[i] * m_dRe[a_nWavePoints-i-1];
    segmab += a_pData[i] * m_dIm[a_nWavePoints-i-1];
    }
    dRms = sqrt(segmaa*segmaa + segmab*segmab);
    dRms /= m_dsqt2;
    a_dAng = atan2(segmab,segmaa);
    */

    t_wavePoint /= nStep;
    for(int j=0; j<t_wavePoint*nStep; j+=nStep)
    {
        segmaa += (float)(p_data[j] * cos(a_Harm*((j)/nStep)*2.0*g_dPI/(float)(t_wavePoint)));
        segmab += (float)(p_data[j] * sin(a_Harm*((j)/nStep)*2.0*g_dPI/(float)(t_wavePoint)));
    }
    dRms = (float)(sqrt(segmaa*segmaa + segmab*segmab)/m_dsqt2/((float)t_wavePoint/2.0));
    a_Ang = (float)(atan2(-segmab, segmaa));
    a_Ang += (float)(g_dPI/2.0);
    //	TRACE("%.2f\n",a_dAng*180.0/g_dPI);

    return dRms;
}

QStringList LoadComtrade::getChseqItemTypeList()
{
    return chseqItemTypeList;
}

//void LoadComtrade::readThFinished()
//{
//    readOver = true;
//}

