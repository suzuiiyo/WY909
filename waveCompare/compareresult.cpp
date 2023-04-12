#include "compareresult.h"
#include <QDebug>
#include <QFile>

CompareResult::CompareResult(const QString &strPath, const QString &strPath2):
    keyPara(new CalParameter(strPath, strPath2))
   ,wavePoints1(0)
   ,wavePoints2(0)
   ,startPos1(0)
   ,startPos2(0)
{
}

CompareResult::~CompareResult()
{
    if(keyPara==nullptr){
        delete keyPara;
    }

    if(effVal==nullptr){
        delete effVal;
    }
}

QMap<QStringList, QStringList> CompareResult::calBayNameCompareRef1Ref2(const QString &str1, const QString &str2)
{
    bool chaneliniStatus = keyPara->getChanelDataListStatus();
    QMap<QStringList, QStringList> bayNameComMap;
    if(chaneliniStatus){
        //dataRef1
        chSeqList1 = keyPara->getChanelRef1List();
        //dataRef2
        chSeqList2 = keyPara->getChanelRef2List();
        iedNameList = keyPara->getIedNameList();
        bayNameList = keyPara->getBayNameList();
        itemNameList = keyPara->getItemNameList();
        phaseList = keyPara->getPhaseList();
        itemTypeList = keyPara->getItemTypeList();
        setTypeList = keyPara->getSetTypeList();
        chDescribeList = keyPara->getchDescribeList();

        chSeqTypeList = keyPara->getChseqTypeList();

        //指定的录波器的dataRef1
        QList<int> ref2On;
        //判断读取哪个dataRef1
        QStringList dcStatusList = respDataRef2(chSeqList2);

        for(int i=0; i<dcStatusList.size(); i++){
            if(dcStatusList.at(i) == "\u0001"){
                ref2On.append(chSeqList2.at(i).toInt());
            }
        }

        QMultiMap<QString, QStringList> bayNameCorrMap;
        for(int i=0; i<bayNameList.size(); i++){
            QStringList corrList;
            corrList << itemNameList.at(i)
                     << itemTypeList.at(i)
                    << phaseList.at(i)
                     << iedNameList.at(i)
                     << chSeqList1.at(i)
                     << chSeqList2.at(i)
                     << setTypeList.at(i)
                     << chDescribeList.at(i);

            //相同bayNameList
            bayNameCorrMap.insertMulti(bayNameList.at(i), corrList);
        }
        bayNameComMap = calBayNameCorrMap(str1, str2, bayNameCorrMap, bayNameList, itemNameList, ref2On);
    }else {
        qDebug() << "无模拟量配置信息";
    }
    return bayNameComMap;
}

QMap<QStringList, QStringList> CompareResult::calBayNameCompareRef1(const QString &str1, const QString &str2)
{
    bool chDataStatus = keyPara->getChanelDataListStatus();

    QMap<QStringList, QStringList> bayNameComMap;
    if(chDataStatus){
        //dataRef1
        chSeqList1 = keyPara->getChanelRef1List();
        //dataRef2
        chSeqList2 = keyPara->getChanelRef2List();

        iedNameList = keyPara->getIedNameList();
        bayNameList = keyPara->getBayNameList();
        itemNameList = keyPara->getItemNameList();
        phaseList = keyPara->getPhaseList();
        itemTypeList = keyPara->getItemTypeList();
        setTypeList = keyPara->getSetTypeList();
        chDescribeList = keyPara->getchDescribeList();

        chSeqTypeList = keyPara->getChseqTypeList();

        QMultiMap<QString, QStringList> bayNameCorrMap;
        for(int i=0; i < bayNameList.size(); i++){
            QStringList corrList;
            corrList << itemNameList.at(i)
                    << itemTypeList.at(i)
                    << phaseList.at(i)
                    << iedNameList.at(i)
                    << chSeqList1.at(i)
                    << chSeqList2.at(i)
                    << setTypeList.at(i)
                    << chDescribeList.at(i);

            //相同bayNameList
            bayNameCorrMap.insertMulti(bayNameList.at(i), corrList);
            bayNameComMap = calBayNameCorrMap(str1, str2, bayNameCorrMap, bayNameList, itemNameList);
        }
    }
    else{
        qDebug() << "无模拟量配置信息";
    }
    return bayNameComMap;
}

QMap<QStringList, QStringList> CompareResult::calBayNameCompareSwitch(const QString &str1, const QString &str2)
{
    bool swIniStatus = keyPara->getSwChanelDataListStatus();
    QMap<QStringList, QStringList> swBayNameComSMap;
    if(swIniStatus){
        //dataRef1
        swChseqList1 = keyPara->getSwChanelRef1List();

        swIedNameList = keyPara->getSwIedNameList();
        swBayNameList = keyPara->getSwBayNameList();
        swItemNameList = keyPara->getSwItemNameList();
        swPhaseList = keyPara->getSwPhaseList();
        swItemTypeList = keyPara->getSwItemTypeList();
        swSetTypeList = keyPara->getSwSetTypeList();
        swChdescribeList = keyPara->getSwchDescribeList();

        QMultiMap<QString, QStringList> swBayNameCorrMap;
        for(int i=0; i < swBayNameList.size(); i++){
        QStringList corrList;
        corrList << swItemNameList.at(i)
                 << swItemTypeList.at(i)
                 << swPhaseList.at(i)
                 << swIedNameList.at(i)
                 << swChseqList1.at(i)
                 << swSetTypeList.at(i)
                 << swChdescribeList.at(i);

            //相同bayNameList
            swBayNameCorrMap.insertMulti(swBayNameList.at(i), corrList);
        }
        swBayNameComSMap = calSwitchBayNameCorrMap(str1, str2, swBayNameCorrMap, swBayNameList, swItemNameList);
    }else{
        qDebug() << "无开关量配置信息";
    }
    return swBayNameComSMap;
}

QList<QList<QList<int>>> CompareResult::getPointSeqlistList() const
{
    return pointSeqlistList;
}

QList<QList<QVector<float>>> CompareResult::getInsertCompareDataList() const
{
    return insertCompareDataList;
}

bool CompareResult::parse2WaveParameter(const QString &varName1, const QString &varName2)
{
    reportTime = QDateTime::currentDateTime();

    //先判断配置库打开情况
    bool openStatus = keyPara->getCalInit();
    //comtrade文件读取情况
    bool comtradeStatus = keyPara->getComtradeInit();

    if(openStatus && comtradeStatus){
        //获取对应的相同的iedName
        //执行calItemTypeCompareRef1可得对应的iedNameList, phaseList, itemTypeList, chDescribeList
        QMap<QStringList, QStringList> phaseRef1Map = calBayNameCompareRef1(varName1, varName2);
        QMap<QStringList, QStringList>::const_iterator i;

        if(!iedNameList.contains(varName1) || !iedNameList.contains(varName2)){
            qDebug() << "配置库读取的iedName与录波文件名不一致,获取通道信息失败";
            exit(0);
        }

        if(!phaseRef1Map.isEmpty()){
            for(i=phaseRef1Map.constBegin(); i!=phaseRef1Map.constEnd(); i++){
                //参与比对的通道参数
                //依次为间隔名, 组别, 采样量类型, 相别, 套别1, 套别2, 通道描述1, 通道描述2
                //参与对比的通道索引
                QStringList wordList;
                //依次为八组比对的dataRef1
                QList<int> refList;
                //间隔名
                wordList << i.key().at(0)
                //组别
                        << i.key().at(1)
                //采样量类型
                        << i.key().at(2)
                //相别
                        << i.key().at(3)
                //套别1
                        << i.value().at(4)
                //套别2
                        << i.value().at(5)
                //通道描述1
                        << i.value().at(6)
                //通道描述2
                        << i.value().at(7);

                //基准比对通道索引
                refList  << i.value().at(0).toInt()
                //参与比对通道索引
                         << i.value().at(1).toInt();
                keyMap.insert(wordList, refList);
            }

            //通道描述
            chDescribeList = keyPara->getchDescribeList();

            //录波总时长
            totalTime = keyPara->getTotalTime();

            //通道名称
            chNameList1 = keyPara->getChanelNameList1();
            chNameList2 = keyPara->getChanelNameList2();

            //基准比对序列突变点时刻
            surgeTime1 = keyPara->getSurgeTime1();
            wavePoints1 = keyPara->getWavePoint1();

            //参与比对序列突变点时刻
            surgeTime2 = keyPara->getSurgeTime2();
            wavePoints2 = keyPara->getWavePoint2();

            QString day = surgeTime1.section("/", 0, 0);
            QString month = surgeTime1.section("/", 1, 1).section("/", 0, 0);
            QString year = surgeTime1.section("/", 1, 2).section("/", 1, 1).section(",", 0, 0);
            QString time = surgeTime1.section("/", 1, 2).section("/", 1, 1).section(",", 1, 2).section(".", 0, 0);
            QString mecSec = surgeTime1.section(".", 1, 1);
            surgeDateTime1 = QDateTime::fromString(year + "-" + month + "-" + day + " " + time + "." + mecSec.mid(0, 3), "yyyy-MM-dd hh:mm:ss.zzz");

            QString day2 = surgeTime2.section("/", 0, 0);
            QString month2 = surgeTime2.section("/", 1, 1).section("/", 0, 0);
            QString year2 = surgeTime2.section("/", 1, 2).section("/", 1, 1).section(",", 0, 0);
            QString time2 = surgeTime2.section("/", 1, 2).section("/", 1, 1).section(",", 1, 2).section(".", 0, 0);
            QString mecSec2 = surgeTime2.section(".", 1, 1);
            surgeDateTime2 = QDateTime::fromString(year2 + "-" + month2 + "-" + day2 + " " + time2 + "." + mecSec2.mid(0, 3), "yyyy-MM-dd hh:mm:ss.zzz");

            //最左点时刻
            leftTime1 = keyPara->getLeftTimeList().at(0);
            leftTime2 = keyPara->getLeftTimeList().at(1);

            //通道总数
            countList1 = keyPara->getCountList1();
            countList2 = keyPara->getCountList2();

            //遍历KeyMap,获取原始采样数据
            QMap<QStringList, QList<int>>::const_iterator j;
            //采样值序列数据
            QList<QList<QVector<float>>> sampleValueTotalList;
            //有效值序列数据
            QList<QList<QVector<float>>> effectValueTotalList;

    //通道号索引
            //文件1通道号索引
            QList<int> chseq1List;
            //文件2通道号索引
            QList<int> chseq2List;
            //待续
    //        int numModify = keyPara->modifyNtbpos(chseq1, chseq2);
            for(j=keyMap.constBegin(); j!=keyMap.constEnd(); j++){
                chseq1List.append(j.value().at(0));
                chseq2List.append(j.value().at(1));

                //突变量
                int surgeNum1 = keyPara->getSurgeNum(j.value().at(0));
                int surgeNum2 = keyPara->getSurgeNum2(j.value().at(1));

                QList<QVector<float>> oriSampleValueList;
                if(j.value().at(0) - 1 < countList1.first() && j.value().at(1) - 1 < countList2.first()){
                    //基准比对序列突变前采样序列
                    QVector<float> chopBefore1zhou = keyPara->getSampleValueList1(j.value().at(0)).at(0);
                    oriSampleValueList.append(chopBefore1zhou);
                    //基准比对序列突变后采样序列
                    QVector<float> chopAfter1zhou = keyPara->getSampleValueList1(j.value().at(0)).at(1);
                    oriSampleValueList.append(chopAfter1zhou);

                    //本采集通道第一个点的位置
                    //先取采集在取保护通道索引
                    int recordFirstPos = keyPara->getRecordFirPos(j.value().at(1), j.value().at(0));
                    //参与比对序列突变前采样序列
                    QVector<float> chopBefore1zhou2 = keyPara->getSampleValueList2(j.value().at(1), recordFirstPos).at(0);
                    oriSampleValueList.append(chopBefore1zhou2);

                    //参与比对序列突变后采样序列
                    QVector<float> chopAfter1zhou2 = keyPara->getSampleValueList2(j.value().at(1), recordFirstPos).at(1);
                    oriSampleValueList.append(chopAfter1zhou2);

                    //采集本通道取的第一个有效值的点的序号
                    int recordFirPos = keyPara->getRecordFirPos(j.value().at(1), j.value().at(0));
                    //原始序列和有效值序列
                    effVal = new CalEffectiveValue(oriSampleValueList, wavePoints1, wavePoints2, surgeNum1, surgeNum2, recordFirPos);
                    effectValueTotalList.append(effVal->getEffectiveValueList());
                    sampleValueTotalList.append(oriSampleValueList);
                }else{
                    qDebug() << "模拟量dataRef1配置有误,超出最大通道数量";
                    return false;
                }
            }

            //起始位置
            startPos1 = keyPara->getStartPos1(chseq1List.at(0));
            startPos2 = keyPara->getRecordFirPos(chseq2List.at(0), chseq1List.at(0));

            //只计算一次
            //计算相关系数平均值和偏移量
            //偏移量以电压通道为准
            int alignPositionFix = 0;

            //记录电压通道是否有采样值
            QList<bool> VChanelStatusList;
            for(int i = 0; i<effectValueTotalList.size(); i++){
               CompareAlgorithm comAlg(sampleValueTotalList.at(i), effectValueTotalList.at(i));
               comAlg.setSurgeTime(surgeTime1, surgeTime2);
               comAlg.setWavePoint(wavePoints1, wavePoints2);
               comAlg.setStartPoint(startPos1, startPos2);
               //计算最小公倍数
               int multiRate = comAlg.calMultipleRate(wavePoints1, wavePoints2);

               //判断通道类型
               //以电压通道采样值计算为准，获取通道类型
               QString curChanelType = nullptr;
               for(int j=0; j< chSeqTypeList.size() - 1; j++)
               {
                   //通道序号相同
                   if(!QString::compare(QString::number(chseq1List.at(i)), chSeqTypeList.at(j))){
                       curChanelType = chSeqTypeList.at(j + 1);
                   }
               }

               if("V" == curChanelType){
                    //先计算偏移量的出通道是否有采样值
                    int alignpositionTemp = comAlg.calAlignPosition(multiRate);
                    //计算通道是否有采样值
                    bool valueStatus = comAlg.getChValueStatus();
                    //通道要有采样值
                    if(valueStatus)
                    {
                        alignPositionFix = alignpositionTemp;
                        VChanelStatusList.append(true);
                    }else{
                        VChanelStatusList.append(false);
                    }
               }

               if(!VChanelStatusList.contains(true)){
                    //先计算偏移量的出通道是否有采样值
                    int alignpositionTemp = comAlg.calAlignPosition(multiRate);
                    //计算通道是否有采样值
                    bool valueStatus = comAlg.getChValueStatus();
                    //通道要有采样值
                    if(valueStatus)
                    {
                        alignPositionFix = alignpositionTemp;
                    }
               }
            }

//            double relSum=0.0;
//            double relAve=0.0;
            //计算相关系数
    //        for(int i=0; i<effectValueTotalList.size(); i++){
    //           CompareAlgorithm comAlg(sampleValueTotalList.at(i), effectValueTotalList.at(i));
    //           comAlg.setSurgeTime(surgeTime1, surgeTime2);
    //           comAlg.setWavePoint(wavePoints1, wavePoints2);
    //           comAlg.setStartPoint(startPos1, startPos2);
    //           int multiRate = comAlg.calMultipleRate(wavePoints1, wavePoints2);a
    //a
    //           comAlg.calEffectInsertZero(multiRate);
    //           comAlg.calEffectInsert2Zero(alignPositionFix, multiRate);

               //判断通道类型
               //以电压通道采样值计算为准，获取通道类型
    //           QString curChanelType = nullptr;
    //           for(int j=0; j< chSeqTypeList.size() - 1; j++)
    //           {
    //               //通道序号相同
    //               if(!QString::compare(QString::number(chseq1List.at(i)), chSeqTypeList.at(j))){
    //                   curChanelType = chSeqTypeList.at(j + 1);
    //               }
    //           }
    //           comAlg.calBeforeCompareData(alignPositionFix, multiRate, curChanelType);
    //           comAlg.calAfterCompareData(multiRate, curChanelType);

    //           relSum += comAlg.getRelevence();
    //        }
    //        relAve = relSum/effectValueTotalList.size();

            //不再重复计算偏移量
    //        if(relAve > 0.5){
                for(int i = 0; i<effectValueTotalList.size(); i++){
                    CompareAlgorithm comAlg(sampleValueTotalList.at(i), effectValueTotalList.at(i));
                    comAlg.setSurgeTime(surgeTime1, surgeTime2);
                    comAlg.setWavePoint(wavePoints1, wavePoints2);
                    comAlg.setStartPoint(startPos1, startPos2);
                    int multiRate = comAlg.calMultipleRate(wavePoints1, wavePoints2);

                    comAlg.calEffectInsertZero(multiRate);
                    comAlg.calEffectInsert2Zero(alignPositionFix, multiRate);

                    QString curItemType = itemTypeList.at(i);
                    comAlg.calBeforeCompareData(alignPositionFix, multiRate, curItemType);
                    comAlg.calAfterCompareData(multiRate, curItemType);

                    compareDatalistList.append(comAlg.getCompareDataList());
                    pointSeqlistList.append(comAlg.getPointSeqList());
                    startPosList = comAlg.getFirstPos();
                    insertCompareDataList.append(comAlg.getInsertCompareVector());

                    relativeErrorVectorList.append(comAlg.getRelativeError());
                    absoluteErrorVectorList.append(comAlg.getAbsoluteError());
                    pointConclusionlistList.append(comAlg.getPointConclusion());

                    compareConclusionList.append(comAlg.getCompareConclusion());
                    compareResultList.append(comAlg.getCompareResult());
                }
                return true;
    //        }
    //        else{
    //            qDebug() << "比对文件无相关性,停止比对";
    //            exit(0);
    //        }
        }else{
            qDebug() << "当前比对文件无配置数据";
            return false;
        }
    }else{
        return false;
    }
}

QStringList CompareResult::respDataRef2(QStringList& dataRef2List)
{
    QStringList dcStatusList;
    for(int i=0; i<dataRef2List.size(); i++){
        if(dataRef2List.at(i).isEmpty()){
          dcStatusList.append("NULL");
        }else if(!dataRef2List.at(i).isEmpty()){
          dcStatusList.append(QString(keyPara->getDchanelValue(dataRef2List.at(i).toInt())));
        }
    }
    return dcStatusList;
}

bool CompareResult::parseSwitchParameter(const QString &varName1, const QString &varName2, QList<int>startList)
{
    //获取对应的相同的iedName
    //执行calItemTypeCompareRef1可得对应的iedNameList, phaseList, itemTypeList, chDescribeList
    QMap<QStringList, QStringList> swPhaseRef1Map = calBayNameCompareSwitch(varName1, varName2);
    QMap<QStringList, QStringList>::const_iterator i;

    //检查开关量通道号是否连续
    QVector<int> dchId1 = keyPara->getDchIdVector1();
    //检查开关量通道号是否连续
    QVector<int> dchId2 = keyPara->getDchIdVector2();
    //不连续的开关量通道号
    lackNum1 = keyPara->getSwLackNumList().at(0);
    lackNum2 = keyPara->getSwLackNumList().at(1);

    if(!swPhaseRef1Map.isEmpty()){
        for(i=swPhaseRef1Map.constBegin(); i!=swPhaseRef1Map.constEnd(); i++){
            //参与比对的通道参数
            //依次为间隔名, 组别, 采样量类型, 相别, 套别1, 套别2, 通道描述1, 通道描述2
            //参与对比的通道索引
            QStringList wordList;
            //依次为八组比对的dataRef1
            QList<int> refList;
            //间隔名
            wordList << i.key().at(0)
            //组别
                     << i.key().at(1)
            //采样量类型
                     << i.key().at(2)
            //相别
                     << i.key().at(3)
            //套别1
                     << i.value().at(4)
            //套别2
                     << i.value().at(5)
            //通道描述1
                     << i.value().at(6)
            //通道描述2
                     << i.value().at(7);

            if(0 == dchId1.at(0) && 0 == dchId2.at(0)){
                //基准比对通道索引
                refList  << i.value().at(2).toInt()
                //参与比对通道索引
                          << i.value().at(3).toInt();
            }else if(1 == dchId1.at(0) && 0 == dchId2.at(0)){
                int dcRefReal1;
                for(int j=1; j<dchId1.size(); j++) {
                    if(dchId1.at(j) == i.value().at(2).toInt()){
                        dcRefReal1 = j;
                    }
                }
                //基准比对通道索引
                refList  << dcRefReal1
                //参与比对通道索引
                         << i.value().at(3).toInt();
            }else if(0 == dchId1.at(0) && 1 == dchId2.at(0)){
                int dcRefReal2;
                for(int j=1; j<dchId2.size(); j++) {
                    if(dchId2.at(j) == i.value().at(3).toInt()){
                        dcRefReal2 = j;
                    }
                }

                //基准比对通道索引
                refList  << i.value().at(2).toInt()
                //参与比对通道索引
                         << dcRefReal2;
            }else if(1 == dchId1.at(0) && 1 == dchId2.at(0)){
                int dcRefReal1;
                int dcRefReal2;
                for(int j=1; j<dchId1.size(); j++) {
                    if(dchId1.at(j) == i.value().at(2).toInt()){
                        dcRefReal1 = j;
                    }
                }

                for(int j=1; j<dchId2.size(); j++) {
                    if(dchId2.at(j) == i.value().at(3).toInt()){
                        dcRefReal2 = j;
                    }
                }
                //基准比对通道索引&& timespan < 20){
                refList  << dcRefReal1
                //参与比对通道索引
                         << dcRefReal2;
            }
            keySwitchMap.insert(wordList, refList);
        }

        //通道描述
        swChdescribeList = keyPara->getSwchDescribeList();

        //通道名称
        swChNameList1 = keyPara->getSwChanelNameList1();
        swChNameList2 = keyPara->getSwChanelNameList2();

        //遍历KeyMap,获取原始采样数据
        QMap<QStringList, QList<int>>::const_iterator swj;

        for(swj=keySwitchMap.constBegin(); swj!=keySwitchMap.constEnd(); swj++){
            if(swj.value().at(0) - 1 < countList1.last() && swj.value().at(1) - 1 < countList2.last()){
                //有几个值就有几次跳变
                //获得通道名称和对应的开关量状态
                QMap<QString, QList<int>> switchMap1 = keyPara->getSwitchStatusMap1(swj.value().at(0), startList.at(0));
                QMap<QString, QList<int>> switchMap2 = keyPara->getSwitchStatusMap2(swj.value().at(1), startList.at(1));

                //开关量通道名称
                QString swChName1 = switchMap1.begin().key();
                QString swChName2 = switchMap2.begin().key();

                //按采样段第一个点计算开关动作时间差
                QList<int> swStatusList1 = switchMap1.begin().value();
                QList<int> swStatusList2 = switchMap2.begin().value();

                //开关量时延
                QList<int> swDcDelayList;
                //开关动作是否一致动作
                QStringList swJumpResultList;
                //开关动作时延比对结果
                QList<int> swCompareList;
                //开关动作时间差
                QList<int> swJumpSpanList;
                for(int i=0; i<swStatusList1.size(); i++){
                    //swStatusList.size个动作点
                    if(swStatusList1.at(i)!=0 && swStatusList2.at(i)!=0)
                    {
                        int timespan = abs(swStatusList1.at(i) - swStatusList2.at(i));
                        //...........依次为各次动作时间.......
                        //开关动作时延
                        swDcDelayList.append(swStatusList1.at(i));
                        swDcDelayList.append(swStatusList2.at(i));

                        //保护跳闸
                        if(timespan < 10)
                        {
                            swCompareList.append(dc_normal);
                        }else if(timespan >=10 && timespan < 20){
                            swCompareList.append(dc_innormal);
                        }else if(timespan >=20){
                            swCompareList.append(dc_critical);
                        }

                        //动作时间差
                        swJumpSpanList.append(timespan);
                        swJumpResultList.append("AB套保护均已动作");
                    }else if(swStatusList1.at(i) ==0 && swStatusList2.at(i) == 0)
                    {
                        swCompareList.append(dc_critical);
                        swJumpSpanList.append(0);
                        swJumpResultList.append("AB套保护均未动作");
                    }else if(swStatusList1.at(i) == 0 && swStatusList2.at(i) !=0)
                    {
                        swCompareList.append(dc_critical);
                        swJumpSpanList.append(-1);
                        swJumpResultList.append("A套保护未动作");
                    }else if(swStatusList1.at(i) != 0 && swStatusList2.at(i) == 0)
                    {
                        swCompareList.append(dc_critical);
                        swJumpSpanList.append(-1);
                        swJumpResultList.append("B套保护未动作");
                    }
                }
                //保护跳闸动作时间
                dcAckDelaylistList.append(swDcDelayList);
                //开关是否一致变位
                swJumpAckResultlistList.append(swJumpResultList);
                //开关变位时延比对结果
                swComparelistList.append(swCompareList);
                //开关动作时间差
                swJumpSpanlistList.append(swJumpSpanList);
            }else{
                qDebug() << "开关量dataRef1配置有误,超出最大通道数量";
                return false;
            }
        }
    }else{
        //开关量为空
        return false;
    }
    return true;
}

QStringList CompareResult::getChDescribeList() const
{
    return chDescribeList;
}

QDateTime CompareResult::getReportTime() const
{
    return reportTime;
}

QStringList CompareResult::getWordList() const
{
    QStringList wordList;
    QMap<QStringList, QList<int>>::const_iterator i;
    for(i=keyMap.constBegin(); i!=keyMap.constEnd(); i++){
        wordList.append(i.key());
    }
    return wordList;
}

double CompareResult::getTotalTime() const
{
    return totalTime;
}


double CompareResult::getResetTime1() const
{
    return totalTime - (surgeDateTime1.toMSecsSinceEpoch() - leftTime1.toMSecsSinceEpoch());
}

double CompareResult::getResetTime2() const
{
    return totalTime - (surgeDateTime2.toMSecsSinceEpoch() - leftTime2.toMSecsSinceEpoch());
}

QList<QVector<double>> CompareResult::getRelativeErrorVectorList() const
{
    return relativeErrorVectorList;
}

QList<QVector<double>> CompareResult::getAbsoluteErrorVectorList() const
{
    return absoluteErrorVectorList;
}

QList<QList<int>> CompareResult::getPointConclusionVectorList() const
{
    return pointConclusionlistList;
}

QStringList CompareResult::getDcChDescribeList() const
{
    return swChdescribeList;
}

QStringList CompareResult::getDcWordList() const
{
    QStringList dcWordList;
    QMap<QStringList, QList<int>>::const_iterator i;
    for(i=keySwitchMap.constBegin(); i!=keySwitchMap.constEnd(); i++){
        dcWordList.append(i.key());
    }
    return dcWordList;
}

QList<QList<int>> CompareResult::getDcCompareResultlistList() const
{
    //swComparelistList存的每个开关量通道的动作比对数据， 按配置的分组的通道
    //var.size是该通道的变位次数
    //如果值为2可能是没动作， 也可能是时延差值超出阈值
    return swComparelistList;
}

//QList<int> CompareResult::getBreakerCompareResultList() const
//{
//    QList<int> breakerResult;
//    foreach(QList<int> var, swComparelistList){
//        int result;
//        if(var.at(1) == dc_normal){
//            result = 0;
//        }else if(var.at(1) == dc_innormal){
//            result = 1;
//        }else if(var.at(1) == dc_critical)
//        {
//            result = 2;
//        }
//        breakerResult.append(result);
//    }
//    breakerResult.append(0);
//    breakerResult.append(-1);
//    return breakerResult;
//}

QList<QStringList> CompareResult::getJumpAckResultlistList() const
{
    return swJumpAckResultlistList;
}

QList<QList<int> > CompareResult::getDcDelaylistList() const
{
    return dcAckDelaylistList;
}

QList<int> CompareResult::getLackNumList() const
{
    QList<int> lackNumList;
    lackNumList.append(lackNum1);
    lackNumList.append(lackNum2);
    return lackNumList;
}

QList<int> CompareResult::getFirstPosList() const
{
    return startPosList;
}

int CompareResult::getRecordFirPos(int chseq, int chseqOne) const
{
    int firstPos = keyPara->getRecordFirPos(chseq, chseqOne);
    return  firstPos;
}


QList<QList<int>> CompareResult::getDcConclusionlistList() const
{
   return swJumpSpanlistList;
}

QStringList CompareResult::getFinalResultList() const
{
    QStringList finalResultList;
    foreach(int varNum, compareResultList){
        finalResultList.append(QString::number(varNum));
    }
    return finalResultList;
}

QMap<QStringList, QStringList> CompareResult::getChanelNameMap() const
{
    QMap<QStringList, QStringList> chNameMap;
    chNameMap.insert(chNameList1, chNameList2);
    return chNameMap;
}

QMap<QStringList, QList<int> > CompareResult::getKeyMap() const
{
    return keyMap;
}

QMap<QStringList, QList<int> > CompareResult::getKeySwicthMap() const
{
    return keySwitchMap;
}

QMap<QStringList, QStringList> CompareResult::calBayNameCorrMap(const QString &iedName1, const QString &iedName2, QMap<QString, QStringList> &toMap, QStringList &t_bayNameList, QStringList &t_itemNameList, QList<int> &ref2OnList)
{
    QSet<QString> bayNameSet;
    QSet<QString> itemNameSet;
    foreach (QString str, t_bayNameList) {
        bayNameSet.insert(str);
    }

    foreach (QString str, t_itemNameList){
        itemNameSet.insert(str);
    }

    QStringList onlyBayNameList;
    foreach(QString str, bayNameSet){
        onlyBayNameList.append(str);
    }

    QStringList onlyItemNameList;
    foreach(QString str, itemNameSet){
        onlyItemNameList.append(str);
    }

    QMap<QStringList, QStringList> bayNameCorrMap;
    QMap<QString, QStringList>::const_iterator i;
    QMap<QString, QStringList>::const_iterator j;

    for(i=toMap.constBegin(); i!=toMap.constEnd(); i++){
        QString bayNameCh = i.key();
        QString itemNameCh = i.value().at(0);
        QString itemTypeCh = i.value().at(1);
        QString phaseCh = i.value().at(2);

        foreach (QString bayNameStr, onlyBayNameList) {
              if(!QString::compare(bayNameCh, bayNameStr)){
                  foreach(QString itemNameStr, onlyItemNameList){
                      if(!QString::compare(itemNameCh, itemNameStr)){
                            if(!QString::compare(itemTypeCh,"V")) {
                                if(!QString::compare(phaseCh, "APHASE")) {
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                                }
                                            }
                                        }
                                    }
                                }
                                else if(!QString::compare(phaseCh, "BPHASE")) {
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                                }
                                            }
                                        }
                                    }
                                }else if(!QString::compare(phaseCh, "CPHASE")){
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "CPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                                }
                                            }
                                        }
                                    }
                                }else if(!QString::compare(phaseCh, "NONE")){
                                   if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "NONE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else if(!QString::compare(itemTypeCh,"C")) {
                                if(!QString::compare(phaseCh, "APHASE")){
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                                }
                                            }
                                        }
                                    }
                                }else if(!QString::compare(phaseCh, "BPHASE")){
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                                }
                                            }
                                        }
                                    }
                                }else if(!QString::compare(phaseCh, "CPHASE")){
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "CPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
                                                  bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                                }
                                            }
                                        }
                                    }
                                }else if(!QString::compare(phaseCh, "NONE")){
                                   if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "NONE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                     }
                  }
              }
        }
    return bayNameCorrMap;
}

//QMap<QStringList, QStringList> skg::calBayNameCorrMap(const QString &iedName1, const QString &iedName2, QMap<QString, QStringList> &toMap, QStringList &t_bayNameList, QStringList &t_itemNameList)
//{
//    QSet<QString> bayNameSet;
//    QSet<QString> itemNameSet;
//    foreach (QString str, t_bayNameList) {
//        bayNameSet.insert(str);
//    }

//    foreach (QString str, t_itemNameList){
//        itemNameSet.insert(str);
//    }

//    QStringList onlyBayNameList;
//    foreach(QString str, bayNameSet){
//        onlyBayNameList.append(str);
//    }

//    QStringList onlyItemNameList;
//    foreach(QString str, itemNameSet){
//        onlyItemNameList.append(str);
//    }

//    QMap<QStringList, QStringList> bayNameCorrMap;
//    QMap<QString, QStringList>::const_iterator i;
//    QMap<QString, QStringList>::const_iterator j;

//    for(i=toMap.constBegin(); i!=toMap.constEnd(); i++){
//        QString bayNameCh = i.key();
//        QString itemNameCh = i.value().at(0);
//        const char *itemTypeCh = i.value().at(1).toStdString().c_str();
//        const char *phaseCh = i.value().at(2).toStdString().c_str();

//        foreach (QString bayNameStr, onlyBayNameList) {
//              if(QString::compare(bayNameCh, bayNameStr)==0){
//                  foreach(QString itemNameStr, onlyItemNameList){
//                      if(QString::compare(itemNameCh, itemNameStr)==0){
//                            switch (hash_compile_time(itemTypeCh)) {
//                            case "V"_hash:
//                                switch(hash_compile_time((phaseCh))) {
//                                case "APHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                              QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                              bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
//                                    break;
//                                case "BPHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                              QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                              bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
    
//}

QMap<QStringList, QStringList> CompareResult::calBayNameCorrMap(const QString &iedName1, const QString &iedName2, QMap<QString, QStringList> &toMap, QStringList &t_bayNameList, QStringList &t_itemNameList)
{
    QSet<QString> bayNameSet;
    QSet<QString> itemNameSet;
    foreach (QString str, t_bayNameList) {
        bayNameSet.insert(str);
    }

    foreach (QString str, t_itemNameList){
        itemNameSet.insert(str);
    }

    QStringList onlyBayNameList;
    foreach(QString str, bayNameSet){
        onlyBayNameList.append(str);
    }

    QStringList onlyItemNameList;
    foreach(QString str, itemNameSet){
        onlyItemNameList.append(str);
    }

    QMap<QStringList, QStringList> bayNameCorrMap;
    QMap<QString, QStringList>::const_iterator i;
    QMap<QString, QStringList>::const_iterator j;

    for(i=toMap.constBegin(); i!=toMap.constEnd(); i++){
        QString bayNameCh = i.key();
        QString itemNameCh = i.value().at(0);
        QString itemTypeCh = i.value().at(1);
        QString phaseCh = i.value().at(2);

        foreach (QString bayNameStr, onlyBayNameList) {
              if(!QString::compare(bayNameCh, bayNameStr)){
                  foreach(QString itemNameStr, onlyItemNameList){
                      if(!QString::compare(itemNameCh, itemNameStr)){
                            if(!QString::compare(itemTypeCh, "V")){
                                if(!QString::compare(phaseCh, "APHASE")) {
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }
                                else if(!QString::compare(phaseCh, "BPHASE")) {
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }else if(!QString::compare(phaseCh, "CPHASE")){
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "CPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }else if(!QString::compare(phaseCh, "NONE")){
                                   if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "NONE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }
                            }else if(!QString::compare(itemTypeCh,"C")) {
                                if(!QString::compare(phaseCh, "APHASE")){
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }
                                if(!QString::compare(phaseCh, "BPHASE")){
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }
                                if(!QString::compare(phaseCh, "CPHASE")){
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "CPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }if(!QString::compare(phaseCh, "NONE")){
                                   if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "NONE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
                                                bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }
                            }
                        }
                     }
              }
        }
    }
    return bayNameCorrMap;
}

QMap<QStringList, QStringList> CompareResult::generaBayNameCorrMap(QMap<QString, QStringList>::const_iterator & i, QMap<QString, QStringList>::const_iterator &j)
{
    QMap<QStringList, QStringList> toMap;

    QStringList bayNameCorrList;
    QStringList refCorrList;

    //没有iedName
    bayNameCorrList << i.key()
                    << i.value().at(0)
                    << i.value().at(1)
                    << i.value().at(2);

    refCorrList  << i.value().at(4)
                 << j.value().at(4)
                 << i.value().at(5)
                 << j.value().at(5)
                 << i.value().at(6)
                 << j.value().at(6)
                 << i.value().at(7)
                 << j.value().at(7);

    toMap.insert(bayNameCorrList, refCorrList);
    return toMap;
}

QMap<QStringList, QStringList> CompareResult::calSwitchBayNameCorrMap(const QString &iedName1, const QString &iedName2, QMap<QString, QStringList> &toMap, QStringList &t_bayNameList, QStringList &t_itemNameList)
{
    QSet<QString> bayNameSet;
    QSet<QString> itemNameSet;
    foreach (QString str, t_bayNameList) {
        bayNameSet.insert(str);
    }

    foreach (QString str, t_itemNameList){
        itemNameSet.insert(str);
    }

    QStringList onlyBayNameList;
    foreach(QString str, bayNameSet){
        onlyBayNameList.append(str);
    }

    QStringList onlyItemNameList;
    foreach(QString str, itemNameSet){
        onlyItemNameList.append(str);
    }

    QMap<QStringList, QStringList> swBayNameCorrMap;
    QMap<QString, QStringList>::const_iterator i;
    QMap<QString, QStringList>::const_iterator j;

    for(i=toMap.constBegin(); i!=toMap.constEnd(); i++){
        QString bayNameCh = i.key();
        QString itemNameCh = i.value().at(0);
        QString itemTypeCh = i.value().at(1);
        QString phaseCh = i.value().at(2);

        foreach (QString bayNameStr, onlyBayNameList) {
              if(!QString::compare(bayNameCh, bayNameStr)){
                  foreach(QString itemNameStr, onlyItemNameList){
                      if(!QString::compare(itemNameCh, itemNameStr)){
                            if(!QString::compare(itemTypeCh, "E")){
                                if(!QString::compare(phaseCh, "APHASE")) {
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "E" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaSwitchBayNameCorrMap(i, j);
                                                swBayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }
                                else if(!QString::compare(phaseCh, "BPHASE")) {
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "E" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaSwitchBayNameCorrMap(i, j);
                                                swBayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }else if(!QString::compare(phaseCh, "CPHASE")){
                                    if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "E" == j.value().at(1) && "CPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaSwitchBayNameCorrMap(i, j);
                                                swBayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }else if(!QString::compare(phaseCh, "NONE")){
                                   if(iedName1 == i.value().at(3)){
                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "E" == j.value().at(1) && "NONE" == j.value().at(2) && iedName2 == j.value().at(3)){
                                                QMap<QStringList, QStringList> corrListMap = generaSwitchBayNameCorrMap(i, j);
                                                swBayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
                                            }
                                        }
                                    }
                                }
                            }
                        }
                     }
              }
        }
    }
    return swBayNameCorrMap;
}

QMap<QStringList, QStringList> CompareResult::generaSwitchBayNameCorrMap(QMap<QString, QStringList>::const_iterator & i, QMap<QString, QStringList>::const_iterator &j)
{
    QMap<QStringList, QStringList> toMap;

    QStringList swBayNameCorrList;
    QStringList swRefCorrList;

    //没有iedName
    swBayNameCorrList << i.key()
                      << i.value().at(0)
                      << i.value().at(1)
                      << i.value().at(2);

    swRefCorrList  << i.value().at(3)
                   << j.value().at(3)
                   << i.value().at(4)
                   << j.value().at(4)
                   << i.value().at(5)
                   << j.value().at(5)
                   << i.value().at(6)
                   << j.value().at(6);

    toMap.insert(swBayNameCorrList, swRefCorrList);
    return toMap;
}

QList<QList<QVector<double>> > CompareResult::getCompareDatalistList() const
{
    return compareDatalistList;
}

QList<double> CompareResult::getCompareConclusionList() const
{
    return compareConclusionList;
}

QList<QDateTime> CompareResult::getSurgeTimeList() const
{
    QList<QDateTime> timeList;

    timeList.append(surgeDateTime1);
    timeList.append(surgeDateTime2);

    return timeList;
}

bool CompareResult::parse2WaveParameterRef2(const QString &varName1, const QString &varName2)
{
    reportTime = QDateTime::currentDateTime();

    //先判断配置库打开情况
    bool openStatus = keyPara->getCalInit();

    //comtrade文件读取情况
    bool comtradeStatus = keyPara->getComtradeInit();

    if(openStatus && comtradeStatus){
        //获取对应的相同的iedName
        //执行calItemTypeCompareRef1可得对应的iedNameList, phaseList, itemTypeList, chDescribeList
        QMap<QStringList, QStringList> phaseRef1Map = calBayNameCompareRef1Ref2(varName1, varName2);
        QMap<QStringList, QStringList>::const_iterator i;

        if(!iedNameList.contains(varName1) || !iedNameList.contains(varName2)){
            qDebug() << "配置库读取的iedName与录波文件名不一致,获取通道信息失败";
            exit(0);
        }

        if(!phaseRef1Map.isEmpty()){
            for(i=phaseRef1Map.constBegin(); i!=phaseRef1Map.constEnd(); i++){
                //参与比对的通道参数
                //依次为间隔名, 组别, 采样量类型, 相别, 套别1, 套别2, 通道描述1, 通道描述2
                QStringList wordList;
                //参与对比的通道索引
                //依次为八组比对的dataRef1
                QList<int> refList;
                //间隔名
                wordList << i.key().at(0)
                //组别
                         << i.key().at(1)
                //采样量类型
                         << i.key().at(2)
                //相别
                         << i.key().at(3)
                //套别1
                         << i.value().at(4)
                //套别2
                         << i.value().at(5)
                //通道描述1
                         << i.value().at(6)
                //通道描述2
                         << i.value().at(7);
                //基准比对通道索引
                refList  << i.value().at(0).toInt()
                //参与比对通道索引
                         << i.value().at(1).toInt();

                keyMap.insert(wordList, refList);
            }

            //通道描述
            chDescribeList = keyPara->getchDescribeList();

            //录波总时长
            totalTime = keyPara->getTotalTime();

            //通道名称
            chNameList1 = keyPara->getChanelNameList1();
            chNameList2 = keyPara->getChanelNameList2();

            //基准比对序列突变点时刻
            surgeTime1 = keyPara->getSurgeTime1();
            wavePoints1 = keyPara->getWavePoint1();

            //参与比对序列突变点时刻
            surgeTime2 = keyPara->getSurgeTime2();
            wavePoints2 = keyPara->getWavePoint2();

            QString day = surgeTime1.section("/", 0, 0);
            QString month = surgeTime1.section("/", 1, 1).section("/", 0, 0);
            QString year = surgeTime1.section("/", 1, 2).section("/", 1, 1).section(",", 0, 0);
            QString time = surgeTime1.section("/", 1, 2).section("/", 1, 1).section(",", 1, 2).section(".", 0, 0);
            QString mecSec = surgeTime1.section(".", 1, 1);
            surgeDateTime1 = QDateTime::fromString(year + "-" + month + "-" + day + " " + time + "." + mecSec.mid(0, 3), "yyyy-MM-dd hh:mm:ss.zzz");

            QString day2 = surgeTime2.section("/", 0, 0);
            QString month2 = surgeTime2.section("/", 1, 1).section("/", 0, 0);
            QString year2 = surgeTime2.section("/", 1, 2).section("/", 1, 1).section(",", 0, 0);
            QString time2 = surgeTime2.section("/", 1, 2).section("/", 1, 1).section(",", 1, 2).section(".", 0, 0);
            QString mecSec2 = surgeTime2.section(".", 1, 1);
            surgeDateTime2 = QDateTime::fromString(year2 + "-" + month2 + "-" + day2 + " " + time2 + "." + mecSec2.mid(0, 3), "yyyy-MM-dd hh:mm:ss.zzz");

            //最左点时刻
            leftTime1 = keyPara->getLeftTimeList().at(0);
            leftTime2 = keyPara->getLeftTimeList().at(1);

            //通道总数
            countList1 = keyPara->getCountList1();
            countList2 = keyPara->getCountList2();

            //遍历KeyMap,获取原始采样数据
            QMap<QStringList, QList<int>>::const_iterator j;
            //采样值序列数据
            QList<QList<QVector<float>>> sampleValueTotalList;
            //有效值序列数据
            QList<QList<QVector<float>>> effectValueTotalList;

            //文件1通道号索引
            QList<int> chseq1List;
            //文件2通道号索引
            QList<int> chseq2List;

            for(j=keyMap.constBegin(); j!=keyMap.constEnd(); j++){
                chseq1List.append(j.value().at(0));
                chseq2List.append(j.value().at(1));

                //突变量
                int surgeNum1 = keyPara->getSurgeNum(j.value().at(0));
                int surgeNum2 = keyPara->getSurgeNum2(j.value().at(0));

                if(j.value().at(0) - 1 < countList1.first() && j.value().at(1) - 1 < countList1.first()){
                    QList<QVector<float>> oriSampleValueList;
                    //基准比对序列突变前采样序列
                    QVector<float> chopBefore1zhou = keyPara->getSampleValueList1(j.value().at(0)).at(0);
                    oriSampleValueList.append(chopBefore1zhou);
                    //基准比对序列突变后采样序列
                    QVector<float> chopAfter1zhou = keyPara->getSampleValueList1(j.value().at(0)).at(1);
                    oriSampleValueList.append(chopAfter1zhou);

                    //参与比对序列突变前采样序列
                    QVector<float> chopBefore1zhou2 = keyPara->getSampleValueList2(j.value().at(1), j.value().at(0)).at(0);
                    oriSampleValueList.append(chopBefore1zhou2);

                    //参与比对序列突变后采样序列
                    QVector<float> chopAfter1zhou2 = keyPara->getSampleValueList2(j.value().at(1), j.value().at(0)).at(1);
                    oriSampleValueList.append(chopAfter1zhou2);

                    //采集通道取第一个有效值的序号
                    int recordFirPos = keyPara->getRecordFirPos(j.value().at(1), j.value().at(0));
                    //原始序列和有效值序列
                    effVal = new CalEffectiveValue(oriSampleValueList, wavePoints1, wavePoints2, surgeNum1, surgeNum2, recordFirPos);
                    sampleValueTotalList.append(oriSampleValueList);
                    effectValueTotalList.append(effVal->getEffectiveValueList());
                }else{
                    qDebug() << "dataRef1配置有误,超出最大通道数量";
                    return false;
                }
            }

            //起始位置
            startPos1 = keyPara->getStartPos1(chseq1List.at(0));
            startPos2 = keyPara->getRecordFirPos(chseq2List.at(0), chseq1List.at(0));

            //只计算一次
            //计算相关系数平均值和偏移量
            //偏移量以电压通道为准
            int alignPositionFix = 0;
            //记录电压通道是否有采样值
            QList<bool> VChanelStatusList;
            for(int i = 0; i<effectValueTotalList.size(); i++){
               CompareAlgorithm comAlg(sampleValueTotalList.at(i), effectValueTotalList.at(i));
               comAlg.setSurgeTime(surgeTime1, surgeTime2);
               comAlg.setWavePoint(wavePoints1, wavePoints2);
               comAlg.setStartPoint(startPos1, startPos2);
               //计算最小公倍数
               int multiRate = comAlg.calMultipleRate(wavePoints1, wavePoints2);

               //判断通道类型
               //以电压通道采样值计算为准，获取通道类型
               QString curChanelType = nullptr;
               for(int j=0; j< chSeqTypeList.size() - 1; j++)
               {
                   //通道序号相同
                   if(!QString::compare(QString::number(chseq1List.at(i)), chSeqTypeList.at(j))){
                       curChanelType = chSeqTypeList.at(j + 1);
                   }
               }

               if("V" == curChanelType){
                    //先计算偏移量得出通道采样值状态
                    int alignpositionTemp = comAlg.calAlignPosition(multiRate);
                    //计算通道是否有采样值
                    bool valueStatus = comAlg.getChValueStatus();
                    //通道要有采样值
                    if(valueStatus)
                    {
                        alignPositionFix = alignpositionTemp;
                        VChanelStatusList.append(true);
                    }else{
                        VChanelStatusList.append(false);
                    }
               }

               //如果电压通道全部没有值
               if(!VChanelStatusList.contains(true)){
                  if("A" == curChanelType){
                     //先计算偏移量得出通道采样值状态
                     int alignpositionTemp = comAlg.calAlignPosition(multiRate);
                     //计算通道是否有采样值
                     bool valueStatus = comAlg.getChValueStatus();
                     //通道要有采样值
                     if(valueStatus)
                     {
                        alignPositionFix = alignpositionTemp;
                     }
                  }
               }
            }

//            double relSum=0.0;
//            double relAve=0.0;
//            //计算相关系数
//            for(int i=0; i<effectValueTotalList.size(); i++){
//               CompareAlgorithm comAlg(sampleValueTotalList.at(i), effectValueTotalList.at(i));
//               comAlg.setSurgeTime(surgeTime1, surgeTime2);
//               comAlg.setWavePoint(wavePoints1, wavePoints2);
//               comAlg.setStartPoint(startPos1, startPos2);
//               int multiRate = comAlg.calMultipleRate(wavePoints1, wavePoints2);

//               comAlg.calEffectInsertZero(multiRate);
//               comAlg.calEffectInsert2Zero(alignPositionFix, multiRate);

//               //判断通道类型
//               //以电压通道采样值计算为准，获取通道类型
//               QString curChanelType = nullptr;
//               for(int j=0; j< chSeqTypeList.size() - 1; j++)
//               {
//                   //通道序号相同
//                   if(!QString::compare(QString::number(chseq1List.at(i)), chSeqTypeList.at(j))){
//                       curChanelType = chSeqTypeList.at(j + 1);
//                   }
//               }
//               comAlg.calBeforeCompareData(alignPositionFix, multiRate, curChanelType);
//               comAlg.calAfterCompareData(multiRate, curChanelType);

//               relSum += comAlg.getRelevence();
//            }
//            relAve = relSum/effectValueTotalList.size();

            for(int i = 0; i<effectValueTotalList.size(); i++){
                CompareAlgorithm comAlg(sampleValueTotalList.at(i), effectValueTotalList.at(i));
                comAlg.setSurgeTime(surgeTime1, surgeTime2);
                comAlg.setWavePoint(wavePoints1, wavePoints2);
                comAlg.setStartPoint(startPos1, startPos2);
                int multiRate = comAlg.calMultipleRate(wavePoints1, wavePoints2);

                comAlg.calEffectInsertZero(multiRate);
                comAlg.calEffectInsert2Zero(alignPositionFix, multiRate);

                QString itemType = itemTypeList.at(i);
                comAlg.calBeforeCompareData(alignPositionFix, multiRate, itemType);
                comAlg.calAfterCompareData(multiRate, itemType);

                compareDatalistList.append(comAlg.getCompareDataList());
                pointSeqlistList.append(comAlg.getPointSeqList());
                startPosList = comAlg.getFirstPos();
                insertCompareDataList.append(comAlg.getInsertCompareVector());

                relativeErrorVectorList.append(comAlg.getRelativeError());
                absoluteErrorVectorList.append(comAlg.getAbsoluteError());
                pointConclusionlistList.append(comAlg.getPointConclusion());

                compareConclusionList.append(comAlg.getCompareConclusion());
                compareResultList.append(comAlg.getCompareResult());
            }
            return true;
        }else{
            qDebug() << "当前比对文件无配置数据";
            return false;
        }
    }else{
        return false;
    }
}

//筛选对应itemType和相位的dataRef1
//QMap<QStringList, QStringList> skg::calBayNameCorrMap(const QString &iedName1, const QString &iedName2, QMap<QString, QStringList> &toMap, QStringList &t_bayNameList, QStringList &t_itemNameList, QList<int>& ref2OnList)
//{
//    QSet<QString> bayNameSet;
//    QSet<QString> itemNameSet;
//    foreach (QString str, t_bayNameList) {
//        bayNameSet.insert(str);
//    }

//    foreach (QString str, t_itemNameList){
//        itemNameSet.insert(str);
//    }

//    QStringList onlyBayNameList;
//    foreach(QString str, bayNameSet){
//        onlyBayNameList.append(str);
//    }

//    QStringList onlyItemNameList;
//    foreach(QString str, itemNameSet){
//        onlyItemNameList.append(str);
//    }

//    QMap<QStringList, QStringList> bayNameCorrMap;
//    QMap<QString, QStringList>::const_iterator i;
//    QMap<QString, QStringList>::const_iterator j;

//    for(i=toMap.constBegin(); i!=toMap.constEnd(); i++){
//        QString bayNameCh = i.key();
//        QString itemNameCh = i.value().at(0);
//        const char *itemTypeCh = i.value().at(1).toStdString().c_str();
//        const char *phaseCh = i.value().at(2).toStdString().c_str();

//        foreach (QString bayNameStr, onlyBayNameList) {
//              if(QString::compare(bayNameCh, bayNameStr)==0){
//                  foreach(QString itemNameStr, onlyItemNameList){
//                      if(QString::compare(itemNameCh, itemNameStr)==0){
//                            switch (hash_compile_time(itemTypeCh)) {
//                            case "V"_hash:
//                                switch(hash_compile_time((phaseCh))) {
//                                case "APHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
//                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                                   break;
//                                                }
//                                            }
//                                        }
//                                    }
//                                    break;
//                                case "BPHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
//                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                                   break;
//                                                }
//                                            }
//                                        }
//                                    }
//                                    break;
//                                case "CPHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "CPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
//                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                                   break;
//                                                }
//                                            }
//                                        }
//                                    }
//                                    break;
//                                 case "NONE"_hash:
//                                   if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "NONE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
//                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                                   break;
//                                                }
//                                            }
//                                        }
//                                    }
//                                    break;
//                                default:
//                                    break;
//                                }
//                                break;
//                            case "C"_hash:
//                                switch(hash_compile_time((phaseCh))){
//                                case "APHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
//                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                                   break;
//                                                }
//                                            }
//                                        }
//                                    }
//                                    break;
//                                case "BPHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
//                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                                   break;
//                                                }
//                                            }
//                                        }
//                                    }
//                                    break;
//                                case "CPHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "CPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
//                                                  bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                                  break;
//                                                }
//                                            }
//                                        }
//                                    }
//                                    break;
//                                 case "NONE"_hash:
//                                   if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "NONE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                                QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                                if(ref2OnList.contains(corrListMap.begin().value().at(3).toInt())){
//                                                   bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                                   break;
//                                                }
//                                            }
//                                        }
//                                    }
//                                    break;
//                                default:
//                                    break;
//                                }
//                                break;
//                            default:
//                                break;
//                            }
//                        }
//                     }
//                  }
//              }
//        }
//    return bayNameCorrMap;
//}

//QMap<QStringList, QStringList> skg::calBayNameCorrMap(const QString &iedName1, const QString &iedName2, QMap<QString, QStringList> &toMap, QStringList &t_bayNameList, QStringList &t_itemNameList)
//{
//    QSet<QString> bayNameSet;
//    QSet<QString> itemNameSet;
//    foreach (QString str, t_bayNameList) {
//        bayNameSet.insert(str);
//    }

//    foreach (QString str, t_itemNameList){
//        itemNameSet.insert(str);
//    }

//    QStringList onlyBayNameList;
//    foreach(QString str, bayNameSet){
//        onlyBayNameList.append(str);
//    }

//    QStringList onlyItemNameList;
//    foreach(QString str, itemNameSet){
//        onlyItemNameList.append(str);
//    }

//    QMap<QStringList, QStringList> bayNameCorrMap;
//    QMap<QString, QStringList>::const_iterator i;
//    QMap<QString, QStringList>::const_iterator j;

//    for(i=toMap.constBegin(); i!=toMap.constEnd(); i++){
//        QString bayNameCh = i.key();
//        QString itemNameCh = i.value().at(0);
//        const char *itemTypeCh = i.value().at(1).toStdString().c_str();
//        const char *phaseCh = i.value().at(2).toStdString().c_str();

//        foreach (QString bayNameStr, onlyBayNameList) {
//              if(QString::compare(bayNameCh, bayNameStr)==0){
//                  foreach(QString itemNameStr, onlyItemNameList){
//                      if(QString::compare(itemNameCh, itemNameStr)==0){
//                            switch (hash_compile_time(itemTypeCh)) {
//                            case "V"_hash:
//                                switch(hash_compile_time((phaseCh))) {
//                                case "APHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                              QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                              bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
//                                    break;
//                                case "BPHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                              QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                              bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
//                                    break;
//                                case "CPHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "CPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                              QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                              bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
//                                    break;
//                                 case "NONE"_hash:
//                                   if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "V" == j.value().at(1) && "NONE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                              QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                              bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
//                                    break;
//                                default:
//                                    break;
//                                }
//                                break;
//                            case "C"_hash:
//                                switch(hash_compile_time((phaseCh))){
//                                case "APHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "APHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                              QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                              bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
//                                    break;
//                                case "BPHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "BPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                              QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                              bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
//                                    break;
//                                case "CPHASE"_hash:
//                                    if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "CPHASE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                               QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                               bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
//                                    break;
//                                 case "NONE"_hash:
//                                   if(iedName1 == i.value().at(3)){
//                                        for(j=toMap.constBegin(); j!=toMap.constEnd(); j++){
//                                            if(bayNameStr == j.key() && itemNameStr == j.value().at(0) && "C" == j.value().at(1) && "NONE" == j.value().at(2) && iedName2 == j.value().at(3)){
//                                              QMap<QStringList, QStringList> corrListMap = generaBayNameCorrMap(i, j);
//                                              bayNameCorrMap.insert(corrListMap.begin().key(), corrListMap.begin().value());
//                                            }
//                                        }
//                                    }
//                                    break;
//                                default:
//                                    break;
//                                }
//                                break;
//                            default:
//                                break;
//                            }
//                        }
//                     }
//                  }
//              }
//        }
//    return bayNameCorrMap;
//}
