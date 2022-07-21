#include "compareresult.h"
#include <QDebug>

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
    return calBayNameCorrMap(str1, str2, bayNameCorrMap, bayNameList, itemNameList, ref2On);
}

QMap<QStringList, QStringList> CompareResult::calBayNameCompareRef1(const QString &str1, const QString &str2)
{
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
    }
    return calBayNameCorrMap(str1, str2, bayNameCorrMap, bayNameList, itemNameList);
}

QMap<QStringList, QStringList> CompareResult::calBayNameCompareSwitch(const QString &str1, const QString &str2)
{
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
    return calSwitchBayNameCorrMap(str1, str2, swBayNameCorrMap, swBayNameList, swItemNameList);
}

QList<QMap<QList<int>, QList<int> > > CompareResult::getPointSeqlistMapList() const
{
    return pointSeqlistMapList;
}

QList<QMap<QVector<float>, QVector<float>> > CompareResult::getInsertCompareDataMapList() const
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

        //起始位置
        startPos1 = keyPara->getStartPos1();
        startPos2 = keyPara->getStartPos2();

        //通道总数
        countMap1 = keyPara->getCountMap1();
        countMap2 = keyPara->getCountMap2();

        //遍历KeyMap,获取原始采样数据
        QMap<QStringList, QList<int>>::const_iterator j;
        //采样值序列数据
        QList<QList<QVector<float>>> sampleValueTotalList;
        //有效值序列数据
        QList<QList<QVector<float>>> effectValueTotalList;

        for(j=keyMap.constBegin(); j!=keyMap.constEnd(); j++){
            QList<QVector<float>> oriSampleValueList;
            if(j.value().at(0) - 1 < countMap1.begin().key() && j.value().at(1) - 1 < countMap2.begin().key()){
                //基准比对序列突变前采样序列
                QVector<float> chopBefore1zhou = keyPara->getSampleValueMap1(j.value().at(0) - 1).begin().key();
                oriSampleValueList.append(chopBefore1zhou);
                //基准比对序列突变后采样序列
                QVector<float> chopAfter1zhou = keyPara->getSampleValueMap1(j.value().at(0) - 1).begin().value();
                oriSampleValueList.append(chopAfter1zhou);

                //参与比对序列突变前采样序列
                QVector<float> chopBefore1zhou2 = keyPara->getSampleValueMap2(j.value().at(1) - 1).begin().key();
                oriSampleValueList.append(chopBefore1zhou2);

                //参与比对序列突变后采样序列
                QVector<float> chopAfter1zhou2 = keyPara->getSampleValueMap2(j.value().at(1) - 1).begin().value();
                oriSampleValueList.append(chopAfter1zhou2);

                //原始序列和有效值序列
                effVal = new CalEffectiveValue(oriSampleValueList, wavePoints1, wavePoints2);
                effectValueTotalList.append(effVal->getEffectiveValueList());
                sampleValueTotalList.append(oriSampleValueList);
            }else{
                qDebug() << "模拟量dataRef1配置有误,超出最大通道数量";
                return false;
            }
        }

        QVector<int> alignVec;
        for(int i = 0; i<effectValueTotalList.size(); i++){
            CompareAlgorithm comAlg(sampleValueTotalList.at(i), effectValueTotalList.at(i));
            comAlg.setSurgeTime(surgeTime1, surgeTime2);
            comAlg.setWavePoint(wavePoints1, wavePoints2);
            comAlg.setStartPoint(startPos1, startPos2);

            int alignposition = comAlg.calAlignPosition();
            alignVec.append(alignposition);

            comAlg.calBeforeCompareData(alignVec.at(0));
            comAlg.calAfterCompareData(alignVec.at(0));
//            comAlg.calBeforeCompareData(alignposition);
//            comAlg.calAfterCompareData(alignposition);
            compareDatalistMapList.append(comAlg.getCompareDataMap());
            pointSeqlistMapList.append(comAlg.getPointSeqMap());
            insertCompareDataList.append(comAlg.getInsertCompareVector());

            relativeErrorVectorList.append(comAlg.getRelativeError());
            absoluteErrorVectorList.append(comAlg.getAbsoluteError());
            pointConclusionlistList.append(comAlg.getPointConclusion());

            compareConclusionList.append(comAlg.getCompareConclusion());
        }
        return true;
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

bool CompareResult::parseSwitchParameter(const QString &varName1, const QString &varName2)
{
    //获取对应的相同的iedName
    //执行calItemTypeCompareRef1可得对应的iedNameList, phaseList, itemTypeList, chDescribeList
    QMap<QStringList, QStringList> swPhaseRef1Map = calBayNameCompareSwitch(varName1, varName2);
    QMap<QStringList, QStringList>::const_iterator i;

    QVector<int> dchId1 = keyPara->getDchIdVector1();
    QVector<int> dchId2 = keyPara->getDchIdVector2();
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
            //基准比对通道索引
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
    QMap<QStringList, QList<int>>::const_iterator j;

    for(j=keySwitchMap.constBegin(); j!=keySwitchMap.constEnd(); j++){
        if(j.value().at(0) - 1 < countMap1.begin().value() && j.value().at(1) - 1 < countMap2.begin().value()){
            QList<int> swStatusList1  = keyPara->getSwitchStatusList1(j.value().at(0));
            QList<int> swStatusList2 = keyPara->getSwitchStatusList2(j.value().at(1));

            if(swStatusList1.at(0) != swStatusList2.at(0)){
                qDebug() << swStatusList1 << swStatusList2 << "AAAAAAAA";
            }else{
                qDebug() << swStatusList1 << swStatusList2 << "BBBBBBBB";
            }
            return true;
        }else{
            qDebug() << "开关量dataRef1配置有误,超出最大通道数量";
            return false;
        }
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

QStringList CompareResult::getWordList()
{
    QStringList wordList;
    QMap<QStringList, QList<int>>::const_iterator i;
    for(i=keyMap.constBegin(); i!=keyMap.constEnd(); i++){
        wordList.append(i.key());
    }
    return wordList;
}

double CompareResult::getTotalTime()
{
    return totalTime;
}


double CompareResult::getResetTime1()
{
    return totalTime - (surgeDateTime1.toMSecsSinceEpoch() - leftTime1.toMSecsSinceEpoch());
}

double CompareResult::getResetTime2()
{
    return totalTime - (surgeDateTime2.toMSecsSinceEpoch() - leftTime2.toMSecsSinceEpoch());
}

QList<QVector<float>> CompareResult::getRelativeErrorVectorList() const
{
    return relativeErrorVectorList;
}

QList<QVector<float>> CompareResult::getAbsoluteErrorVectorList() const
{
    return absoluteErrorVectorList;
}

QList<QList<int>> CompareResult::getPointConclusionVectorList() const
{
    return pointConclusionlistList;
}

QStringList CompareResult::getFinalResultList() const
{
    QStringList finalResultList;
    for(int i=0; i<compareConclusionList.size(); i++){
        if(compareConclusionList.at(i)<0.050){
            finalResultList.append(QString::number(normal));
        }else if(compareConclusionList.at(i) >=0.050 && compareConclusionList.at(i) <0.100){
            finalResultList.append(QString::number(innormal));
        }else if(compareConclusionList.at(i) >=0.100){
            finalResultList.append(QString::number(critical));
        }
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

QList<QMap<QVector<float>, QVector<float> > > CompareResult::getCompareDatalistMapList() const
{
    return compareDatalistMapList;
}

QList<float> CompareResult::getCompareConclusionList() const
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

        //起始位置
        startPos1 = keyPara->getStartPos1();
        startPos2 = keyPara->getStartPos2();

        //通道总数
        countMap1 = keyPara->getCountMap1();
        countMap2 = keyPara->getCountMap2();

        //遍历KeyMap,获取原始采样数据
        QMap<QStringList, QList<int>>::const_iterator j;
        //采样值序列数据
        QList<QList<QVector<float>>> sampleValueTotalList;
        //有效值序列数据
        QList<QList<QVector<float>>> effectValueTotalList;

        for(j=keyMap.constBegin(); j!=keyMap.constEnd(); j++){
            if(j.value().at(0) - 1 < countMap1.begin().key() && j.value().at(1) - 1 < countMap2.begin().key()){
                QList<QVector<float>> oriSampleValueList;
                //基准比对序列突变前采样序列
                QVector<float> chopBefore1zhou = keyPara->getSampleValueMap1(j.value().at(0) - 1).begin().key();
                oriSampleValueList.append(chopBefore1zhou);
                //基准比对序列突变后采样序列
                QVector<float> chopAfter1zhou = keyPara->getSampleValueMap1(j.value().at(0) - 1).begin().value();
                oriSampleValueList.append(chopAfter1zhou);

                //参与比对序列突变前采样序列
                QVector<float> chopBefore1zhou2 = keyPara->getSampleValueMap2(j.value().at(1) - 1).begin().key();
                oriSampleValueList.append(chopBefore1zhou2);

                //参与比对序列突变后采样序列
                QVector<float> chopAfter1zhou2 = keyPara->getSampleValueMap2(j.value().at(1) - 1).begin().value();
                oriSampleValueList.append(chopAfter1zhou2);

                //原始序列和有效值序列
                effVal = new CalEffectiveValue(oriSampleValueList, wavePoints1, wavePoints2);
                sampleValueTotalList.append(oriSampleValueList);
                effectValueTotalList.append(effVal->getEffectiveValueList());
            }else{
                qDebug() << "dataRef1配置有误,超出最大通道数量";
                return false;
            }
        }

        QVector<int> alignVec;
        for(int i = 0; i<effectValueTotalList.size(); i++){
            CompareAlgorithm comAlg(sampleValueTotalList.at(i), effectValueTotalList.at(i));
            comAlg.setSurgeTime(surgeTime1, surgeTime2);
            comAlg.setWavePoint(wavePoints1, wavePoints2);
            comAlg.setStartPoint(startPos1, startPos2);

            int alignposition = comAlg.calAlignPosition();
            alignVec.append(alignposition);

            comAlg.calBeforeCompareData(alignVec.at(0));
            comAlg.calAfterCompareData(alignVec.at(0));
//            comAlg.calBeforeCompareData(alignposition);
//            comAlg.calAfterCompareData(alignposition);
            compareDatalistMapList.append(comAlg.getCompareDataMap());
            pointSeqlistMapList.append(comAlg.getPointSeqMap());
            insertCompareDataList.append(comAlg.getInsertCompareVector());

            relativeErrorVectorList.append(comAlg.getRelativeError());
            absoluteErrorVectorList.append(comAlg.getAbsoluteError());
            pointConclusionlistList.append(comAlg.getPointConclusion());

            compareConclusionList.append(comAlg.getCompareConclusion());
        }
        return true;
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
