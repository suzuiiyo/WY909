#include "calparameter.h"
#include <QMapIterator>
#include <QDebug>
#include "unistd.h"

CalParameter::CalParameter(QString path1, QString path2):
     openComtrade(nullptr)
    ,openComtrade2(nullptr)
    ,chanelPara(nullptr)
    ,strPath1(path1)
    ,strPath2(path2)
    ,wavePoints1(0)
    ,wavePoints2(0)
{
}

bool CalParameter::getCalInit()
{
    chanelPara = new ChanelParaDAO();
    bool dbStatus = chanelPara->init("db1");
    if(dbStatus){
        chanelDataList = chanelPara->getComtradeFactor();
        swChanelDataList = chanelPara->getSwitchComtradeFactor();
        bool dbInfoFlag = chanelPara->getDbInfo();

        if(dbInfoFlag){
           qDebug() << "配置库读取成功";
           return true;
        }else
        {
           qDebug() << "配置库读取失败";
           return false;
        }
    }else{
        return false;
    }
}

bool CalParameter::getComtradeInit()
{
    openComtrade = new LoadComtrade();
    openComtrade2 = new LoadComtrade();
    bool comtradeFlag1 = openComtrade->init(strPath1);
    bool comtradeFlag2 = openComtrade2->init(strPath2);

    if(comtradeFlag1 && comtradeFlag2){
        return true;
    }else{
        qDebug() << "comtrade文件数据不完整,比对失败";
        exit(0);
    }
}

CalParameter::~CalParameter()
{
    if(openComtrade != nullptr){
    	delete openComtrade;
    }

    if(openComtrade2 != nullptr){
        delete openComtrade2;
    }

    if(chanelPara != nullptr){
        delete chanelPara;
    }
}

QStringList CalParameter::getChanelRef1List()
{
   QStringList chanelRef1List;
   for(int i=0; i<chanelDataList.size(); i++){
        chanelRef1List.append(chanelDataList.at(i).at(1));
   }
   return chanelRef1List;
}

QStringList CalParameter::getChanelRef2List()
{
    QStringList chanelRef2List;
    for(int i=0; i<chanelDataList.size(); i++){
        chanelRef2List.append(chanelDataList.at(i).at(2));
    }
    return chanelRef2List;
}

QStringList CalParameter::getIedNameList()
{
   //iedName
   QStringList iedNameList;
   for(int i=0; i<chanelDataList.size(); i++)
   {
       iedNameList.append(chanelDataList.at(i).at(0));
   }
   return iedNameList;
}

QStringList CalParameter::getBayNameList()
{
    //bayName
    QStringList bayNameList;
    for(int i=0; i<chanelDataList.size(); i++)
    {
        bayNameList.append(chanelDataList.at(i).at(3));
    }
    return bayNameList;
}

QStringList CalParameter::getItemNameList()
{
    //itemName
    QStringList itemNameList;
    for(int i=0; i<chanelDataList.size(); i++)
    {
        itemNameList.append(chanelDataList.at(i).at(4));
    }
    return itemNameList;
}

QStringList CalParameter::getItemTypeList()
{
   //itemType
   QStringList itemTypeList;
   for(int i=0; i<chanelDataList.size(); i++)
   {
       itemTypeList.append(chanelDataList.at(i).at(5));
   }
   return itemTypeList;
}

QStringList CalParameter::getchDescribeList()
{
   //通道描述
   QStringList chDescribeList;
   for(int i=0; i<chanelDataList.size(); i++){
        chDescribeList.append(chanelDataList.at(i).at(6));
   }
   return chDescribeList;
}

QList<int> CalParameter::getCountList1()
{
    //通道总数
    QList<int> countList1 = openComtrade->getChTotal();
    return countList1;
}

QList<int> CalParameter::getCountList2()
{
    QList<int> countList2 = openComtrade2->getChTotal();
    return countList2;
}

QStringList CalParameter::getPhaseList()
{
   //相别
   QStringList phaseList;
   for(int i=0; i<chanelDataList.size(); i++)
   {
        phaseList.append(chanelDataList.at(i).at(7));
   }
   return phaseList;
}

QStringList CalParameter::getSetTypeList()
{
    //setType
    QStringList setTypeList;
    for(int i=0; i<chanelDataList.size(); i++)
    {
        setTypeList.append(chanelDataList.at(i).at(8));
    }
    return setTypeList;
}

double CalParameter::getTotalTime()
{
    double time = openComtrade->getTotalTime();
    return time;
}

QList<QDateTime> CalParameter::getLeftTimeList()
{
    QList<QDateTime> leftTimeList;
    QDateTime time = openComtrade->getLeftTime();
    leftTimeList.append(time);
    QDateTime time2 = openComtrade2->getLeftTime();
    leftTimeList.append(time2);

    return leftTimeList;
}

QList<QVector<float>> CalParameter::getSampleValueList1(const int& chseq)
{
   QList<QVector<float>> sampleValueList1;
   //修正ntbPos
   int surgePos = openComtrade->getSurgeNum(chseq);
   sampleValueList1 = openComtrade->getSampleValue(chseq, surgePos);

   return sampleValueList1;
}

QStringList CalParameter::getChanelNameList1()
{
   QStringList chanelNameList1 = openComtrade->getChName();
   return chanelNameList1;
}

int CalParameter::getWavePoint1()
{
    wavePoints1 = openComtrade->getWavePoints();
    return wavePoints1;
}

QString CalParameter::getSurgeTime1()
{
    tmSurge1 = openComtrade->getSurgeTime();
    return tmSurge1;
}

int CalParameter::getStartPos1(const int& chseq)
{
   int surgePos = openComtrade->getSurgeNum(chseq);
   int startPos1 = openComtrade->getStartPos(wavePoints1, surgePos);
   return startPos1;
}

QList<QVector<float>> CalParameter::getSampleValueList2(const int& chseq, const int&firPos)
{
   QList<QVector<float>> sampleValueList2;
   int surgePos = openComtrade2->getSurgeNum(chseq);

   sampleValueList2 = openComtrade2->getRecordSampleValue(chseq, surgePos, firPos);

   return sampleValueList2;
}

QStringList CalParameter::getChanelNameList2()
{
   QStringList chanelNameList2 = openComtrade2->getChName();
   return chanelNameList2;
}

int CalParameter::getWavePoint2()
{
   wavePoints2 = openComtrade2->getWavePoints();
   return wavePoints2;
}

QString CalParameter::getSurgeTime2()
{
   tmSurge2 = openComtrade2->getSurgeTime();
   return tmSurge2;
}

int CalParameter::getStartPos2(const int& chseq)
{
   int surgePos = openComtrade2->getSurgeNum(chseq);
   int startPos2 = openComtrade2->getStartPos(wavePoints2, surgePos);
   return startPos2;
}

//修正通道号
int CalParameter::modifyNtbpos(const int& chseq1, const int& chseq2)
{
   QVector<float> modifyChanel1 = openComtrade->modifyWholeChop(chseq1);
   QVector<float> modifyChanel2 = openComtrade2->modifyWholeChop(chseq2);

   for(int i=0; i<modifyChanel1.size() - 1; i++)
   {
       if(fabs(static_cast<double>(modifyChanel1.at(i+1) - modifyChanel1.at(i))) > 1.0)
       {
           break;
       }
   }

   for(int i=0; i<modifyChanel2.size() - 1; i++)
   {
       if(fabs(static_cast<double>(modifyChanel2.at(i+1) - modifyChanel2.at(i))) > 1.0)
       {
           break;
       }
   }

   return 0;
}

int CalParameter::getDchanelValue(const int chseq)
{
    //开关量通道值
    int dChValue = openComtrade2->getSwitchStatus(chseq);
    return dChValue;
}

QStringList CalParameter::getSwChanelRef1List()
{
    QStringList chanelRef1List;
    for(int i=0; i<swChanelDataList.size(); i++){
        chanelRef1List.append(swChanelDataList.at(i).at(1));
    }
    return chanelRef1List;
}

QStringList CalParameter::getSwIedNameList()
{
    //iedName
    QStringList iedNameList;
    for(int i=0; i<swChanelDataList.size(); i++){
        iedNameList.append(swChanelDataList.at(i).at(0));
    }
    return iedNameList;
}

QStringList CalParameter::getSwBayNameList()
{
    //bayName
    QStringList bayNameList;
    for(int i=0; i<swChanelDataList.size(); i++)
    {
        bayNameList.append(swChanelDataList.at(i).at(2));
    }
    return bayNameList;
}

QStringList CalParameter::getSwItemNameList()
{
    //itemName
    QStringList itemNameList;
    for(int i=0; i<swChanelDataList.size(); i++)
    {
        itemNameList.append(swChanelDataList.at(i).at(3));
    }
    return itemNameList;
}

QStringList CalParameter::getSwItemTypeList()
{
   //itemType
   QStringList itemTypeList;
   for(int i=0; i<swChanelDataList.size(); i++)
   {
       itemTypeList.append(swChanelDataList.at(i).at(4));
   }
   return itemTypeList;
}

QStringList CalParameter::getSwPhaseList()
{
   //相别
   QStringList phaseList;
   for(int i=0; i<swChanelDataList.size(); i++)
   {
        phaseList.append(swChanelDataList.at(i).at(6));
   }
   return phaseList;
}

QStringList CalParameter::getSwSetTypeList()
{
    //setType
    QStringList setTypeList;
    for(int i=0; i<swChanelDataList.size(); i++)
    {
        setTypeList.append(swChanelDataList.at(i).at(7));
    }
    return setTypeList;
}

QStringList CalParameter::getSwchDescribeList()
{
   //通道描述
   QStringList chDescribeList;
   for(int i=0; i<swChanelDataList.size(); i++){
        chDescribeList.append(swChanelDataList.at(i).at(5));
   }
   return chDescribeList;
}

QMap<QString, QList<int>> CalParameter::getSwitchStatusMap1(const int& chseq, const int&varPos)
{
   //开关量通道值
   //表示开关量跳变点 距离突变点时长
   QMap<QString, QList<int>> varMap;
   varMap = openComtrade->getSwitchDelayMap(chseq, varPos);

   return varMap;
}

QStringList CalParameter::getSwChanelNameList1()
{
    QStringList chanelNameList1 = openComtrade->getSwitchName();
    return chanelNameList1;
}

QMap<QString, QList<int>> CalParameter::getSwitchStatusMap2(const int &chseq, const int&varPos)
{
   //开关量通道值
   //表示开关量跳变点 距离突变点时长
    QMap<QString, QList<int>> varMap;
    varMap = openComtrade2->getSwitchDelayMap(chseq, varPos);

    return varMap;
}

QStringList CalParameter::getSwChanelNameList2()
{
    QStringList chanelNameList2 = openComtrade2->getSwitchName();
    return chanelNameList2;
}

QVector<int> CalParameter::getDchIdVector1()
{
    QVector<int> dchId = openComtrade->getDchIdVector();
    return dchId;
}

QVector<int> CalParameter::getDchIdVector2()
{
    QVector<int> dchId = openComtrade2->getDchIdVector();
    return dchId;
}

QList<int> CalParameter::getSwLackNumList()
{
    QList<int> lackNumList;
    int lackNum1 = openComtrade->getlackChNum();
    int lackNum2 = openComtrade2->getlackChNum();

    lackNumList.append(lackNum1);
    lackNumList.append(lackNum2);

    return lackNumList;
}

QStringList CalParameter::getChseqTypeList()
{
    QStringList chSeqTypeList = openComtrade->getChseqItemTypeList();
    return chSeqTypeList;
}

int CalParameter::getSurgeNum(int chseq)
{
    int surge = openComtrade->getSurgeNum(chseq);
    return surge;
}

int CalParameter::getSurgeNum2(int chseq)
{
    int surge = openComtrade2->getSurgeNum(chseq);
    return surge;
}

bool CalParameter::getChanelDataListStatus()
{
    if(chanelDataList.isEmpty()){
        return false;
    }else{
        return true;
    }
}

bool CalParameter::getSwChanelDataListStatus()
{
    if(swChanelDataList.isEmpty()){
        return false;
    }else{
        return true;
    }
}

//先传采集通道号， 在传保护通道号
int CalParameter::getRecordFirPos(int chseq, int chseqOne)
{
   int recordFirPos = 0;
   //采集突变点
   int surgePos = openComtrade2->getSurgeNum(chseq);
   //保护突变点
   int surgePosOne = openComtrade->getSurgeNum(chseqOne);

   //如果保护取两个周波
   if(surgePosOne >= 2*wavePoints1){
       recordFirPos = surgePos - 2*wavePoints2;
   //如果保护取不到两个周波
   }else if(surgePosOne < 2*wavePoints1){
        int valueFactor = wavePoints2/wavePoints1;
        int valueFactorVar = 0;
        for(int i=0; i<surgePosOne; i++){
            if(wavePoints2%wavePoints1==0)
            {
                recordFirPos = surgePos - i*valueFactor;
            }else if(wavePoints2%wavePoints1!=0){
            //保护采样频率1.2k
                if(i%3==0 || i%3==1){
                    valueFactorVar += valueFactor;
                }else if(i%3 == 2)
                {
                    valueFactorVar += valueFactor + 1;
                }
                recordFirPos = surgePos - valueFactorVar;
            }
        }
   }
   return recordFirPos;
}
