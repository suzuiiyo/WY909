#include "calparameter.h"
#include <QMapIterator>
#include <QDebug>
#include "unistd.h"

CalParameter::CalParameter(QString path1, QString path2):
     openComtrade(new LoadComtrade())
    ,openComtrade2(new LoadComtrade())
    ,chanelPara(new ChanelParaDAO())
    ,strPath1(path1)
    ,strPath2(path2)
    ,wavePoints1(0)
    ,wavePoints2(0)
{
}

bool CalParameter::getCalInit()
{
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
    bool comtradeFlag1 = openComtrade->init(strPath1);
    bool comtradeFlag2 = openComtrade2->init(strPath2);

    if(comtradeFlag1 && comtradeFlag2){
        return true;
    }else{
        qDebug() << "comtrade文件数据不完整,比对失败";
        return false;
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

QMap<int, int> CalParameter::getCountMap1()
{
    //通道总数
    QMap<int, int> countMap1;
    countMap1 = openComtrade->getChTotal();
    return countMap1;
}

QMap<int, int> CalParameter::getCountMap2()
{
    QMap<int, int> countMap2;
    countMap2 = openComtrade2->getChTotal();
    return countMap2;
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

QMap<QVector<float>, QVector<float> > CalParameter::getSampleValueMap1(const int chseq)
{
   QMap<QVector<float>, QVector<float>> sampleValueMap1;
   sampleValueMap1 = openComtrade->getSampleValue(chseq);
   return sampleValueMap1;
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

int CalParameter::getStartPos1()
{
   int startPos1 = openComtrade->getStartPos(wavePoints1);
   return startPos1;
}

QMap<QVector<float>, QVector<float>> CalParameter::getSampleValueMap2(const int chseq)
{
   QMap<QVector<float>, QVector<float>> sampleValueMap2;
   sampleValueMap2 = openComtrade2->getSampleValue(chseq);

   return sampleValueMap2;
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

int CalParameter::getStartPos2()
{
   int startPos2 = openComtrade2->getStartPos(wavePoints2);
   return startPos2;
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

QList<int> CalParameter::getSwitchStatusList1(const int chseq)
{
   //开关量通道值
   //表示开关量跳变点 距离突变点时长
   QList<int> swStatusList = openComtrade->getSwitchDelay(chseq);
   return swStatusList;
}

QStringList CalParameter::getSwChanelNameList1()
{
    QStringList chanelNameList1 = openComtrade->getSwitchName();
    return chanelNameList1;
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

QList<int> CalParameter::getSwitchStatusList2(const int chseq)
{
   //开关量通道值
   QList<int> swStatusList = openComtrade2->getSwitchDelay(chseq);
   return swStatusList;
}
