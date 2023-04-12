#include "resultintodb.h"
#include <hdrReader.h>
#include <writeresultdao.h>
#include <writeswitchresultdao.h>
#include <compareresult.h>
#include <parsefilename.h>
#include <QDebug>
#include <dbtransienttaskfiledao.h>
#include <QFileInfo>
#include <QSystemSemaphore>

ResultIntoDb::ResultIntoDb()
{

}

ResultIntoDb::ResultIntoDb(QStringList& var1, QStringList& var2, QStringList& var3):
       cfgFile1(var1.at(0))
      ,cfgFile2(var1.at(1))
      ,hdrFile1(var2.at(0))
      ,hdrFile2(var2.at(1))
      ,iedName1(var3.at(0))
      ,iedName2(var3.at(1))
{
}

ResultIntoDb::~ResultIntoDb()
{
}

bool ResultIntoDb::productResult()
{
    ParseFileName pfn;
    //计算nameList
    QStringList dataList = pfn.getDataList(cfgFile1, cfgFile2);
    //获得解析数据
    pfn.getWordList(dataList);
//  iedName1 = pfn.getIedNameList().at(0);
//  iedName2 = pfn.getIedNameList().at(1);

    QString AFileName = cfgFile1;
    QString BFileName = cfgFile2;
    QFileInfo finfoA(AFileName);
    QFileInfo finfoB(BFileName);
    QString fileNamePathA = finfoA.completeBaseName();
    QString fileNamePathB = finfoB.completeBaseName();

//    QString deviceType1 = pfn.getDeviceTypeList().at(0);
//    QString deviceType2 = pfn.getDeviceTypeList().at(1);

    QString faultSeq1 = pfn.getFaultSeqList().at(0);
//    QString faultSeq2 = pfn.getFaultSeqList().at(1);

    HdrReader reader(hdrFile1);
    QMap<QString, QMap<QString, QString>> qTrig = reader.getTrigInfo();
    QSet<QString> qFault = reader.getFaultInfo();
    QString qFaultInfo;

    QMap<QString, QMap<QString, QString>>::const_iterator i;
    QMap<QString, QString>::const_iterator j;
    QString startReason;
    QString startValue;
    QString settingValue;

    for(i= qTrig.begin(); i!=qTrig.end(); i++){
        startReason = i.key();
//      "启动原因";
        for(j = i.value().begin(); j != i.value().end(); j++){
//          "启动值";
            startValue = j.key();
            settingValue = j.value();
//          "整定值";
        }
    }

    QSet<QString>::const_iterator iq;
    for(iq=qFault.constBegin(); iq!=qFault.constEnd(); iq++){
        qFaultInfo.append(*iq);
    }
    QString ringing = reader.getMessValue();
    QString faultType = reader.getFaultReason();

    HdrReader reader2(hdrFile2);
    QMap<QString, QMap<QString, QString>> qTrigCom = reader2.getTrigInfo();
    QSet<QString> qFaultCom = reader2.getFaultInfo();
    QString qFaultInfoCom;

    QMap<QString, QMap<QString, QString>>::const_iterator icom;
    QMap<QString, QString>::const_iterator jcom;
    QString startReasonCom;
    QString startValueCom;
    QString settingValueCom;

    for(icom= qTrigCom.begin(); icom!=qTrigCom.end(); icom++){
        startReasonCom = icom.key();
        for(jcom = icom.value().begin(); jcom != icom.value().end(); jcom++){
            startValueCom = jcom.key();
            settingValueCom = jcom.value();
        }
    }

    QSet<QString>::const_iterator iqcom;
    for(iqcom=qFaultCom.constBegin(); iqcom!=qFaultCom.constEnd(); iqcom++){
        qFaultInfoCom.append(*iqcom);
    }

    QString ringingCom = reader2.getMessValue();
    QString faultTypeCom = reader2.getFaultReason();

    if(!cfgFile1.isNull() && !cfgFile2.isNull()){
        CompareResult result(cfgFile1, cfgFile2);
        //获取比对计算参数
        bool readSysconf = result.parse2WaveParameter(iedName1, iedName2);
        if(readSysconf){
            chKeyMap = result.getKeyMap();
            chChanelNameMap = result.getChanelNameMap();
            chCompareDatalistMapList = result.getCompareDatalistList();
            chPointSeqlistMapList = result.getPointSeqlistList();
            chCompareConclusionList = result.getCompareConclusionList();

            relativeErrorVectorList = result.getRelativeErrorVectorList();
            absoluteErrorVectorList = result.getAbsoluteErrorVectorList();
            pointConclusionlistList = result.getPointConclusionVectorList();
//           "组别";
//           "采样量类型";
//           "相别";

            QString surgeTime1 = result.getSurgeTimeList().at(0).toString("yyyy-MM-dd hh:mm:ss.zzz");
//            QString surgeTime2 = result.getSurgeTimeList().at(1).toString("yyyy-MM-dd hh:mm:ss.zzz");

            double resetTime = result.getResetTime1();
            QString proRestTime = QString::number(resetTime/(1000 * 60), 10, 4);
            keyWordList = result.getWordList();

//            "设备1启动时间";
//            "设备2启动时间";
//            "保护启动复归时间";

//            "故障序号";
//            "保护故障数据的值";

//            "A套录波文件名";
//            "B套录波文件名";

//            "基准对比的录波文件名";
//            "参与对比的录波文件名";

//            "模拟量" << "通道类型";
//            "异常阈值";
//            "严重阈值";

            //间隔名, 组别, 采样类型, 相别, 套别1, 套别2, 通道描述1, 通道描述2
            QList<QStringList> factorlistList;
            //dataref1, 基准比对通道, 参与比对通道
            QList<QList<int>>  chSeqlistList;
            QMap<QStringList, QList<int> >::const_iterator i;
            //第i个比对组的基准通道名
            //总比较组数
            int num = 0;
            QStringList bayNameList;
            QStringList itemNameList;
            QStringList itemTypeList;
            QStringList phaseTypeList;
            for(i=chKeyMap.constBegin(); i!=chKeyMap.constEnd(); i++){
                bayNameList.append(i.key().at(0));
                itemNameList.append(i.key().at(1));
                itemTypeList.append(i.key().at(2));
                phaseTypeList.append(i.key().at(3));
                factorlistList.append(i.key());
                chSeqlistList.append(i.value());
                num++;
            }

            for(int i=0; i<num; i++){
//              QVector<float> beforeCompareData = chCompareDatalistMapList.at(i).begin().key();
//              QVector<float> afterCompareData = chCompareDatalistMapList.at(i).begin().value();

//              "突变前比对结果序列"
//              "突变后比对结果序列"

//              QList<int> pointSeqList1 = chPointSeqlistMapList.at(i).begin().key();
//              QList<int> pointSeqList2 = chPointSeqlistMapList.at(i).begin().value();

//              "基准比对点序号序列集"
//              "参与比对点序号序列集"
                //相对误差
                QVector<double> relativeError = relativeErrorVectorList.at(i);
                //绝对误差
                QVector<double> absoluteError = absoluteErrorVectorList.at(i);
                //点结论
                QList<int> pointConclusion = pointConclusionlistList.at(i);

                int standardCompareChSeq = chSeqlistList.at(i).at(0);
//                "基准对比的录波通道索引"

                QString standardChDescribe = factorlistList.at(i).at(6);
//                "基准对比的录波通道描述"

                QString standardSetType = factorlistList.at(i).at(4);
//                "基准对比的套别1"

                QVector<float> standardSampleVector = result.getInsertCompareDataList().at(i).at(0);
//                "基准对比的录波采样点值"

                QList<int> standardComparePointSeq = result.getPointSeqlistList().at(i).at(0);
//               "基准比对的录波点序号序列"

                int taskCompareChSeq = chSeqlistList.at(i).at(1);
//                "参与对比的录波通道索引"

                QString taskChDescribe = factorlistList.at(i).at(7);
//                "参与对比的录波通道描述"

                QString taskSetType = factorlistList.at(i).at(5);
//                "基准对比的套别2" << endl

                QVector<float> taskSampleVector = result.getInsertCompareDataList().at(i).at(1);
//                "参与对比的录波采样点值"

                QList<int> taskComparePointSeq = result.getPointSeqlistList().at(i).at(1);
//               "参与对比的录波点序号序列"

                reportTime = result.getReportTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
//               "产生结论记录时间"


                QString compareConclusion = QString("%1").arg(result.getCompareConclusionList().at(i));
//                "比对结论"
                QString finalResult = result.getFinalResultList().at(i);
//                "最终结果"

                WriteResultDAO wr;
                bool wrFlag = wr.init();

                if(wrFlag){
                    //写入数据库
                    QSystemSemaphore sem("sem", 1, QSystemSemaphore::Open);
                    sem.acquire();

//                  "间隔名";
                    wr.setBayName(bayNameList.at(i));
                    wr.setItemName(itemNameList.at(i));
                    wr.setItemType(itemTypeList.at(i));
                    QString phaseType = phaseTypeList.at(i);
                    wr.setPhaseType(phaseType.mid(0, 1));

                    wr.setprotStartTime(surgeTime1);
                    wr.setprotStartResetTime(proRestTime);
                    wr.setprotFaultNum(faultSeq1.toInt());

                    //保护故障数据的值
                    wr.setprotFaultValue(0.0);

                    wr.setSrIedAFileName(AFileName);
                    wr.setSrIedBFileName(BFileName);
                    wr.setSrTMDataType(startReason.toInt());
                    wr.setSrTMDataValue(startValue.toFloat());
                    wr.setSrTMThreshold(settingValue.toFloat());

                    wr.setIedName(iedName1);
                    wr.setIedNameComp(iedName2);
                    wr.setSetType(standardSetType);
                    wr.setSetTypeComp(taskSetType);

                    wr.setConclusion(compareConclusion);
                    wr.setTaskFileName(fileNamePathB);
                    wr.setStandardFileName(fileNamePathA);

                    wr.setChannelType("0");
                    wr.setResult(finalResult);
                    wr.setAbnormalThreshold("5");
                    wr.setSeriousThreshold("10");
                    wr.setStandardChannelRef(standardCompareChSeq);
                    wr.setStandardChannelDesc(standardChDescribe);

                    wr.setIedFaultInfo(qFaultInfo);
                    wr.setIedFaultInfoCom(qFaultInfoCom);

                    wr.setIedFaultType(faultType);
                    wr.setIedCompFaultType(faultTypeCom);
                    wr.setIedRanging(ringing);
                    wr.setIedCompRing(ringingCom);

                    //
                    QString standardSampleVectorString = "{";
                    foreach (float var, standardSampleVector) {
                        QString varStr = QString("%1").arg(static_cast<double>(var));
                        QString unit = varStr + ", ";
                        standardSampleVectorString += unit;
                    }
                    standardSampleVectorString += "}";
                    wr.setStandardSamplesValue(standardSampleVectorString);

                    //
                    QString standPointSeqString = "{";
                    foreach(float var, standardComparePointSeq){
                       QString varStr = QString("%1").arg(static_cast<double>(var));
                       QString unit = varStr + ", ";
                       standPointSeqString += unit;
                    }
                    standPointSeqString += "}";
                    wr.setStandardSamplesPointSeq(standPointSeqString);

                    wr.setTaskChannelRef(taskCompareChSeq);
                    wr.setTaskChanelDesc(taskChDescribe);

                    //
                    QString taskSampleVectorString = "{";
                    foreach(float var, taskSampleVector){
                        QString varStr = QString("%1").arg(static_cast<double>(var));
                        QString unit = varStr + ", ";
                        taskSampleVectorString += unit;
                    }
                    taskSampleVectorString += "}";
                    wr.setTaskSamplesValue(taskSampleVectorString);

                    //
                    QString taskPointSeqString = "{";
                    foreach(int var, taskComparePointSeq){
                       QString varStr = QString("%1").arg(var);
                       QString unit = varStr + ", ";
                       taskPointSeqString.append(unit);
                    }
                    taskPointSeqString += "}";
                    wr.setTaskSamplesPointSeq(taskPointSeqString);

                    //
                    QString relativeErrorString = "{";
                    foreach(double var, relativeError){
                        QString varStr = QString("%1").arg(var);
                        QString unit = varStr + ", ";
                        relativeErrorString += unit;
                    }
                    relativeErrorString += "}";
                    wr.setPointRelativeError(relativeErrorString);

                    //
                    QString absoluteErrorString = "{";
                    foreach(double var, absoluteError){
                        QString varStr = QString("%1").arg(var);
                        QString unit = varStr + ", ";
                        absoluteErrorString += unit;
                    }
                    absoluteErrorString += "}";
                    wr.setPointAbsoluteError(absoluteErrorString);

                    //
                    QString pointConclusionString ="{";
                    foreach(int var, pointConclusion){
                        QString varStr = QString("%1").arg(var);
                        QString unit = varStr + ", ";
                        pointConclusionString += unit;
                    }
                    pointConclusionString += "}";
                    wr.setPointColusion(pointConclusionString);

                    //
                    wr.setRecordTime(reportTime);

                    DBTransientTaskConclusionRecordDAO dao;
                    if(dao.doCreateTable())
                        dao.doInsert(wr.getTTCR());
                    sem.release();

                    QStringList forthWordList;
                    forthWordList << bayNameList.at(i)
                                  << itemNameList.at(i)
                                  << itemTypeList.at(i)
                                  << phaseTypeList.at(i);


                    QStringList keyWordList;
                    keyWordList << iedName1
                                << AFileName
                                << iedName2
                                << BFileName
                                << standardChDescribe
                                << taskChDescribe
                                << finalResult;

                    protkeyWordMap.insertMulti(forthWordList, keyWordList);
                }
             }
          }

            //先调用parse2WaveParameter
            //先计算模拟量得到开关量序号
            QList<int> startPosList = result.getFirstPosList();
            bool switchRead = result.parseSwitchParameter(iedName1, iedName2, startPosList);
            if(switchRead){
                //开关量
                dcChKeyMap = result.getKeySwicthMap();
                //开关变位时间差
                dcConclusionlistList = result.getDcConclusionlistList();

                //开关变位比对结果
                dcAckResultlistList = result.getDcCompareResultlistList();

                //开关是否一致动作
                jumpAckResultlistList = result.getJumpAckResultlistList();

                //各开关变位时延
                dcAckDelaylistList = result.getDcDelaylistList();

                QList<int> lackNumList = result.getLackNumList();
                //间隔名, 组别, 采样类型, 相别, 套别1, 套别2, 通道描述1, 通道描述2
                QList<QStringList> dcFactorlistList;
                //dataref1, 基准比对通道, 参与比对通道
                QList<QList<int>>  dcChSeqlistList;
                //第i个比对组的基准通道名
                QMap<QStringList, QList<int>>::const_iterator j;
                //总比较组数
                //第i个比对组的基准通道名
                QStringList bayNameList;
                QStringList itemNameList;
                QStringList itemTypeList;
                QStringList phaseTypeList;

                int switchNum = 0;
                for(j=dcChKeyMap.constBegin(); j!=dcChKeyMap.constEnd(); j++){
                   bayNameList.append(j.key().at(0));
                   itemNameList.append(j.key().at(1));
                   itemTypeList.append(j.key().at(2));
                   phaseTypeList.append(j.key().at(3));
                   dcFactorlistList.append(j.key());
                   dcChSeqlistList.append(j.value());
                   switchNum++;
               }

               for(int i=0; i < switchNum; i++){
                    int standardCompareChSeq = dcChSeqlistList.at(i).at(0) + lackNumList.at(0);
//                "基准对比的录波通道索引"

                    QString standardChDescribe = dcFactorlistList.at(i).at(6);
//                "基准对比的录波通道描述"

                    QString standardSetType = dcFactorlistList.at(i).at(4);
//                "基准对比的套别1"

                    int taskCompareChSeq = dcChSeqlistList.at(i).at(1) + lackNumList.at(1);
//                "参与对比的录波通道索引"

                    QString taskChDescribe = dcFactorlistList.at(i).at(7);
//                "参与对比的录波通道描述"

                    QString taskSetType = dcFactorlistList.at(i).at(5);
//                "基准对比的套别2"

                    QString reportTime = result.getReportTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
//                "产生结论记录时间"

                    QString surgeTime1 = result.getSurgeTimeList().at(0).toString("yyyy-MM-dd hh:mm:ss.zzz");

                    QString iedTaskType = itemTypeList.at(i);

                    QString phaseType = phaseTypeList.at(i);

                    //时延对
                    QString dcDelayCop;
                    //开关A 第一次动作时延
                    int dcAckDelayA;
                    //开关B 第一次动作时延
                    int dcAckDelayB;
                    if(dcAckDelaylistList.at(i).size() >= 2){
                        //保护A跳闸时延
                        dcAckDelayA = dcAckDelaylistList.at(i).at(0);
                        //保护B跳闸时延
                        dcAckDelayB = dcAckDelaylistList.at(i).at(1);

                        dcDelayCop = QString::number(dcAckDelayA) + "," + QString::number(dcAckDelayB);
                    }else{
                        dcAckDelayA = -1;
                        dcAckDelayB = -1;
                        dcDelayCop = QString::number(dcAckDelayA) + "," + QString::number(dcAckDelayB);
                    }

                    int dcCompareResult = dcAckResultlistList.at(i).at(0);

                    int dcFirstConclusion = dcConclusionlistList.at(i).at(0);

                    QString jumpAckFirstResult = jumpAckResultlistList.at(i).at(0);

                    WriteSwitchResultDao wsr;
                    bool wsrFlag = wsr.init();

                    if(wsrFlag){
                        //写入开关量数据库
                        QSystemSemaphore sem("sem", 1, QSystemSemaphore::Open);
                        sem.acquire();

//                  	"间隔名";
                        wsr.setBayName(bayNameList.at(i));
                        wsr.setItemName(itemNameList.at(i));

                        wsr.setSrIedAFileName(AFileName);
                        wsr.setSrIedBFileName(BFileName);

                        wsr.setIedName(iedName1);
                        wsr.setIedNameComp(iedName2);
                        wsr.setSetType(standardSetType);
                        wsr.setSetTypeComp(taskSetType);

                        wsr.setIedTaskType(iedTaskType);
                        wsr.setIedPhase(phaseType);

                        wsr.setConclusion(jumpAckFirstResult);
                        wsr.setRecloseConclusion(dcFirstConclusion);
                        wsr.setBreakerConclusion(-1);

                        wsr.setTaskFileName(fileNamePathB);
                        wsr.setStandardFileName(fileNamePathA);

                        wsr.setChannelType("1");

                        wsr.setRecloseAckDelay(dcDelayCop);
                        wsr.setBreakerAckDelay("NULL");

                        wsr.setReclosingInnormalTime("15");
                        wsr.setReclosingSeriousTime("20");

                        wsr.setbreakerInnormalTime("15");
                        wsr.setbreakerSeriousTime("20");
                        wsr.setReclosingResult(dcCompareResult);
                        wsr.setBreakerResult(-1);

                        wsr.setTaskChannelRef(taskCompareChSeq);
                        wsr.setTaskChannelDesc(taskChDescribe);

                        wsr.setStandardChannelRef(standardCompareChSeq);
                        wsr.setStandardChannelDesc(standardChDescribe);

                        //记录时间
                        wsr.setRecordTime(reportTime);
                        //故障时间
                        wsr.setFaultZeroTime(surgeTime1);

                        //插入类
                        DBTransientSwitchConclusionRecordDAO dao;
                        if(dao.doCreateTable())
                            dao.doInsert(wsr.getTSCR());
                        sem.release();
                    }
                 }
            }
            return true;
    }else{
        return false;
    }
}

bool ResultIntoDb::productProtResult()
{
    ParseFileName pfn;
    //计算nameList
    QStringList dataList = pfn.getDataList(cfgFile1, cfgFile2);
    //获得解析数据
    pfn.getWordList(dataList);
//  iedName1 = pfn.getIedNameList().at(0);
//  iedName2 = pfn.getIedNameList().at(1);

    QString AFileName = cfgFile1;
    QString BFileName = cfgFile2;
    QFileInfo finfoA(AFileName);
    QFileInfo finfoB(BFileName);
    QString fileNamePathA = finfoA.completeBaseName();
    QString fileNamePathB = finfoB.completeBaseName();

//    QString deviceType1 = pfn.getDeviceTypeList().at(0);
//    QString deviceType2 = pfn.getDeviceTypeList().at(1);

    QString faultSeq1 = pfn.getFaultSeqList().at(0);
//    QString faultSeq2 = pfn.getFaultSeqList().at(1);

    HdrReader reader(hdrFile1);
    QMap<QString, QMap<QString, QString>> qTrig = reader.getTrigInfo();
    QSet<QString> qFault = reader.getFaultInfo();
    QString qFaultInfo;

    QMap<QString, QMap<QString, QString>>::const_iterator i;
    QMap<QString, QString>::const_iterator j;
    QString startReason;
    QString startValue;
    QString settingValue;

    for(i= qTrig.begin(); i!=qTrig.end(); i++){
        startReason = i.key();
//      "启动原因";
        for(j = i.value().begin(); j != i.value().end(); j++){
//          "启动值";
            startValue = j.key();
            settingValue = j.value();
//          "整定值";
        }
    }

    QSet<QString>::const_iterator iq;
    for(iq=qFault.constBegin(); iq!=qFault.constEnd(); iq++){
        qFaultInfo.append(*iq);
    }
    QString ringing = reader.getMessValue();
    QString faultType = reader.getFaultReason();

    HdrReader reader2(hdrFile2);
    QMap<QString, QMap<QString, QString>> qTrigCom = reader2.getTrigInfo();
    QSet<QString> qFaultCom = reader2.getFaultInfo();
    QString qFaultInfoCom;

    QMap<QString, QMap<QString, QString>>::const_iterator icom;
    QMap<QString, QString>::const_iterator jcom;
    QString startReasonCom;
    QString startValueCom;
    QString settingValueCom;

    for(icom= qTrigCom.begin(); icom!=qTrigCom.end(); icom++){
        startReasonCom = icom.key();
        for(jcom = icom.value().begin(); jcom != icom.value().end(); jcom++){
            startValueCom = jcom.key();
            settingValueCom = jcom.value();
        }
    }

    QSet<QString>::const_iterator iqcom;
    for(iqcom=qFaultCom.constBegin(); iqcom!=qFaultCom.constEnd(); iqcom++){
        qFaultInfoCom.append(*iqcom);
    }

    QString ringingCom = reader2.getMessValue();
    QString faultTypeCom = reader2.getFaultReason();

    if(!cfgFile1.isNull() && !cfgFile2.isNull()){
        CompareResult result(cfgFile1, cfgFile2);
        //获取比对计算参数
        bool readSysconf = result.parse2WaveParameter(iedName1, iedName2);
        if(readSysconf){
            chKeyMap = result.getKeyMap();
            chChanelNameMap = result.getChanelNameMap();
            chCompareDatalistMapList = result.getCompareDatalistList();
            chPointSeqlistMapList = result.getPointSeqlistList();
            chCompareConclusionList = result.getCompareConclusionList();

            relativeErrorVectorList = result.getRelativeErrorVectorList();
            absoluteErrorVectorList = result.getAbsoluteErrorVectorList();
            pointConclusionlistList = result.getPointConclusionVectorList();
//           "组别";
//           "采样量类型";
//           "相别";

            QString surgeTime1 = result.getSurgeTimeList().at(0).toString("yyyy-MM-dd hh:mm:ss.zzz");
//            QString surgeTime2 = result.getSurgeTimeList().at(1).toString("yyyy-MM-dd hh:mm:ss.zzz");

            double resetTime = result.getResetTime1();
            QString proRestTime = QString::number(resetTime/(1000 * 60), 10, 4);
            keyWordList = result.getWordList();

//            "设备1启动时间";
//            "设备2启动时间";
//            "保护启动复归时间";

//            "故障序号";
//            "保护故障数据的值";

//            "A套录波文件名";
//            "B套录波文件名";

//            "基准对比的录波文件名";
//            "参与对比的录波文件名";

//            "模拟量" << "通道类型";
//            "异常阈值";
//            "严重阈值";

            //间隔名, 组别, 采样类型, 相别, 套别1, 套别2, 通道描述1, 通道描述2
            QList<QStringList> factorlistList;
            //dataref1, 基准比对通道, 参与比对通道
            QList<QList<int>>  chSeqlistList;
            QMap<QStringList, QList<int> >::const_iterator i;
            //第i个比对组的基准通道名
            //总比较组数
            int num = 0;
            QStringList bayNameList;
            QStringList itemNameList;
            QStringList itemTypeList;
            QStringList phaseTypeList;
            for(i=chKeyMap.constBegin(); i!=chKeyMap.constEnd(); i++){
                bayNameList.append(i.key().at(0));
                itemNameList.append(i.key().at(1));
                itemTypeList.append(i.key().at(2));
                phaseTypeList.append(i.key().at(3));
                factorlistList.append(i.key());
                chSeqlistList.append(i.value());
                num++;
            }

            for(int i=0; i<num; i++){
//              QVector<float> beforeCompareData = chCompareDatalistMapList.at(i).begin().key();
//              QVector<float> afterCompareData = chCompareDatalistMapList.at(i).begin().value();

//              "突变前比对结果序列"
//              "突变后比对结果序列"

//              QList<int> pointSeqList1 = chPointSeqlistMapList.at(i).begin().key();
//              QList<int> pointSeqList2 = chPointSeqlistMapList.at(i).begin().value();

//              "基准比对点序号序列集"
//              "参与比对点序号序列集"
                //相对误差
                QVector<double> relativeError = relativeErrorVectorList.at(i);
                //绝对误差
                QVector<double> absoluteError = absoluteErrorVectorList.at(i);
                //点结论
                QList<int> pointConclusion = pointConclusionlistList.at(i);

                int standardCompareChSeq = chSeqlistList.at(i).at(0);
//                "基准对比的录波通道索引"

                QString standardChDescribe = factorlistList.at(i).at(6);
//                "基准对比的录波通道描述"

                QString standardSetType = factorlistList.at(i).at(4);
//                "基准对比的套别1"

                QVector<float> standardSampleVector = result.getInsertCompareDataList().at(i).at(0);
//                "基准对比的录波采样点值"

                QList<int> standardComparePointSeq = result.getPointSeqlistList().at(i).at(0);
//               "基准比对的录波点序号序列"

                int taskCompareChSeq = chSeqlistList.at(i).at(1);
//                "参与对比的录波通道索引"

                QString taskChDescribe = factorlistList.at(i).at(7);
//                "参与对比的录波通道描述"

                QString taskSetType = factorlistList.at(i).at(5);
//                "基准对比的套别2" << endl

                QVector<float> taskSampleVector = result.getInsertCompareDataList().at(i).at(1);
//                "参与对比的录波采样点值"

                QList<int> taskComparePointSeq = result.getPointSeqlistList().at(i).at(1);
//               "参与对比的录波点序号序列"

                reportTime = result.getReportTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
//               "产生结论记录时间"


                QString compareConclusion = QString("%1").arg(result.getCompareConclusionList().at(i));
//                "比对结论"
                QString finalResult = result.getFinalResultList().at(i);
//                "最终结果"

//****************************************比对结果不写库
                QStringList forthWordList;
                forthWordList << bayNameList.at(i)
                              << itemNameList.at(i)
                              << itemTypeList.at(i)
                              << phaseTypeList.at(i);


                QStringList keyWordList;
                keyWordList << iedName1
                            << AFileName
                            << iedName2
                            << BFileName
                            << standardChDescribe
                            << taskChDescribe
                            << finalResult;

                protkeyWordMap.insertMulti(forthWordList, keyWordList);
            }
        }
        return true;
    }else{
        return false;
    }
}

bool ResultIntoDb::productResult(int &varCount, xmlINFO &varXML)
{
    ParseFileName pfn;
    QStringList dataList = pfn.getDataList(cfgFile1, cfgFile2);

    //get parse value
    pfn.getWordList(dataList);

//  iedName1 = pfn.getIedNameList().at(0);
//  iedName2 = pfn.getIedNameList().at(1);

    QString AFileName = cfgFile1;
    QString BFileName = cfgFile2;
    QFileInfo finfoA(AFileName);
    QFileInfo finfoB(BFileName);
    QString fileNamePathA = finfoA.completeBaseName();
    QString fileNamePathB = finfoB.completeBaseName();

//    QString deviceType1 = pfn.getDeviceTypeList().at(0);
//    QString deviceType2 = pfn.getDeviceTypeList().at(1);

    QString faultSeq1 = pfn.getFaultSeqList().at(0);
//    QString faultSeq2 = pfn.getFaultSeqList().at(1);

    QFile HdrFile(hdrFile1);
    QString startReason;
    QString startValue;
    QString settingValue;
    QString qFaultInfo;
    QString ringring;
    QString faultType;

    if(HdrFile.exists()){
        HdrReader reader(hdrFile1);
        QSet<QString> qFault = reader.getFaultInfo();
        QMap<QString, QMap<QString, QString>> qTrig = reader.getTrigInfo();

        QMap<QString, QMap<QString, QString>>::const_iterator i;
        QMap<QString, QString>::const_iterator j;

        for(i= qTrig.begin(); i!=qTrig.end(); i++){
            startReason = i.key();
            for(j = i.value().begin(); j != i.value().end(); j++){
                startValue = j.key();
                settingValue = j.value();
            }
        }

        QSet<QString>::const_iterator iq;
        for(iq = qFault.constBegin(); iq!=qFault.constEnd(); iq++){
            qFaultInfo.append(*iq);
        }
        ringring = reader.getMessValue();
        faultType = reader.getFaultReason();
    }else{
        startReason = "NULL";
        startValue = "NULL";
        settingValue = "NULL";
        qFaultInfo = "NULL";
        ringring = "NULL";
        faultType = "NULL";
        qDebug() << "基准比对Comtrade文件HDR不存在";
    }

    QFile HdrFile2(hdrFile2);
    QString startReasonCom;
    QString startValueCom;
    QString settingValueCom;
    QString qFaultInfoCom;
    QString ringringCom;
    QString faultTypeCom;

    if(HdrFile2.exists()){
        HdrReader reader2(hdrFile2);
        QMap<QString, QMap<QString, QString>> qTrigCom = reader2.getTrigInfo();
        QSet<QString> qFaultCom = reader2.getFaultInfo();

        QMap<QString, QMap<QString, QString>>::const_iterator icom;
        QMap<QString, QString>::const_iterator jcom;

        for(icom= qTrigCom.begin(); icom!=qTrigCom.end(); icom++){
            startReasonCom = icom.key();
            for(jcom = icom.value().begin(); jcom != icom.value().end(); jcom++){
                startValueCom = jcom.key();
                settingValueCom = jcom.value();
            }
        }

        QSet<QString>::const_iterator iqcom;
        for(iqcom=qFaultCom.constBegin(); iqcom!=qFaultCom.constEnd(); iqcom++){
            qFaultInfoCom.append(*iqcom);
        }
        ringringCom = reader2.getMessValue();
        faultTypeCom = reader2.getFaultReason();
    }else{
        startReasonCom = "NULL";
        startValueCom = "NULL";
        settingValueCom = "NULL";
        qFaultInfoCom = "NULL";
        ringringCom = "NULL";
        faultTypeCom = "NULL";
        qDebug() << "参与比对Comtrade文件HDR不存在";
    }

    if(!cfgFile1.isNull() && !cfgFile2.isNull()){
        CompareResult result(cfgFile1, cfgFile2);
        //获取比对计算参数
        bool readSysconfRef2 = result.parse2WaveParameter(iedName1, iedName2);

        if(readSysconfRef2){
            chKeyMap = result.getKeyMap();
            chChanelNameMap = result.getChanelNameMap();
            chCompareDatalistMapList = result.getCompareDatalistList();
            chPointSeqlistMapList = result.getPointSeqlistList();
            chCompareConclusionList = result.getCompareConclusionList();

            relativeErrorVectorList = result.getRelativeErrorVectorList();
            absoluteErrorVectorList = result.getAbsoluteErrorVectorList();
            pointConclusionlistList = result.getPointConclusionVectorList();

            QString surgeTime1 = result.getSurgeTimeList().at(0).toString("yyyy-MM-dd hh:mm:ss.zzz");
//          QString surgeTime2 = result.getSurgeTimeList().at(1).toString("yyyy-MM-dd hh:mm:ss.zzz");

            double resetTime = result.getResetTime1();
            QString proRestTime = QString::number(resetTime/(1000 * 60), 10, 4);
//          QString proRestTime2 = QString::number(resetTime2/(1000 * 60), 10, 4);
            //传出四元组
            keyWordListRef2 = result.getWordList();
//            surgeTime1;
//            "设备2启动时间";
//            "保护启动复归时间";

//            "故障序号";
//            "保护故障数据的值";

//            "A套录波文件名";
//            "B套录波文件名";

//            "基准对比的录波文件名";
//            "参与对比的录波文件名";

//            "模拟量" << "通道类型";
//            "异常阈值";
//            "严重阈值";

            //间隔名, 组别, 采样类型, 相别, 套别1, 套别2, 通道描述1, 通道描述2
            QList<QStringList> factorlistList;
            //dataref1, 基准比对通道, 参与比对通道
            QList<QList<int>>  chSeqlistList;
            QMap<QStringList, QList<int> >::const_iterator i;
            //总比较组数
            //第i个比对组的基准通道名
            QStringList bayNameList;
            QStringList itemNameList;
            QStringList itemTypeList;
            QStringList phaseTypeList;
            int num = 0;
            for(i=chKeyMap.constBegin(); i!=chKeyMap.constEnd(); i++){
                bayNameList.append(i.key().at(0));
                itemNameList.append(i.key().at(1));
                itemTypeList.append(i.key().at(2));
                phaseTypeList.append(i.key().at(3));
                factorlistList.append(i.key());
                chSeqlistList.append(i.value());
                num++;
            }
            varCount = num;

            //写入xmlINFO
            varXML.bayName = bayNameList.at(0);
            varXML.iedNameList << iedName1 << iedName2;

            for(int i=0; i<dataList.size(); i++){
                QFileInfo finfo(dataList.at(i));
                QString fileNamePath = finfo.completeBaseName();
                varXML.fileNameList << fileNamePath;
            }

            for(int i=0; i<num; i++){
//                QVector<float> beforeCompareData = chCompareDatalistMapList.at(i).begin().key();
//                QVector<float> afterCompareData = chCompareDatalistMapList.at(i).begin().value();

//                "突变前比对结果序列"
//                "突变后比对结果序列"

//                QList<int> pointSeqList1 = chPointSeqlistMapList.at(i).begin().key();
//                QList<int> pointSeqList2 = chPointSeqlistMapList.at(i).begin().value();

//                "基准比对点序号序列集"
//                "参与比对点序号序列集"

                //相对误差
                QVector<double> relativeError = relativeErrorVectorList.at(i);
                //绝对误差
                QVector<double> absoluteError = absoluteErrorVectorList.at(i);
                //点结论
                QList<int> pointConclusion = pointConclusionlistList.at(i);
                //
                int standardCompareChSeq = chSeqlistList.at(i).at(0);
//                "基准对比的录波通道索引"

                QString standardChDescribe = factorlistList.at(i).at(6);
//                "基准对比的录波通道描述"

                QString standardSetType = factorlistList.at(i).at(4);
//                "基准对比的套别1"
                QVector<float> standardSampleVector = result.getInsertCompareDataList().at(i).at(0);
//                "基准对比的录波采样点值"

                QList<int> standardComparePointSeq = result.getPointSeqlistList().at(i).at(0);
//                "基准比对的录波点序号序列"

                int taskCompareChSeq = chSeqlistList.at(i).at(1);
//                "参与对比的录波通道索引"

                QString taskChDescribe = factorlistList.at(i).at(7);
//                "参与对比的录波通道描述"

                QString taskSetType = factorlistList.at(i).at(5);
//                "基准对比的套别2"

                QVector<float> taskSampleVector = result.getInsertCompareDataList().at(i).at(1);
//                "参与对比的录波采样点值"

                QList<int> taskComparePointSeq = result.getPointSeqlistList().at(i).at(1);
//                "参与对比的录波点序号序列"

                QString reportTime = result.getReportTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
//                "产生结论记录时间"

                QString surgeTime1 = result.getSurgeTimeList().at(0).toString("yyyy-MM-dd hh:mm:ss.zzz");

                QString compareConclusion = QString("%1").arg(result.getCompareConclusionList().at(i));
//                "比对结论"
                QString finalResult = result.getFinalResultList().at(i);
//                "最终结果"

                QStringList resultList;
                resultList << standardChDescribe << taskChDescribe << finalResult;
                varXML.resultSet << resultList;

                WriteResultDAO wr;
                bool wrFlag = wr.init();

                if(wrFlag){
                    //写入数据库
                    QSystemSemaphore sem("sem", 1, QSystemSemaphore::Open);
                    sem.acquire();

//                  "间隔名";
                    wr.setBayName(bayNameList.at(i));
                    wr.setItemName(itemNameList.at(i));
                    wr.setItemType(itemTypeList.at(i));

                    QString phaseType = phaseTypeList.at(i);
                    wr.setPhaseType(phaseType.mid(0, 1));

                    wr.setprotStartTime(surgeTime1);
                    wr.setprotStartResetTime(proRestTime);
                    wr.setprotFaultNum(faultSeq1.toInt());

                    //保护故障数据的值
                    wr.setprotFaultValue(0.0);

                    wr.setSrIedAFileName(AFileName);
                    wr.setSrIedBFileName(BFileName);
                    wr.setSrTMDataType(startReason.toInt());
                    wr.setSrTMDataValue(startValue.toFloat());
                    wr.setSrTMThreshold(settingValue.toFloat());

                    wr.setIedName(iedName1);
                    wr.setIedNameComp(iedName2);
                    wr.setSetType(standardSetType);
                    wr.setSetTypeComp(taskSetType);

                    wr.setConclusion(compareConclusion);
                    wr.setTaskFileName(fileNamePathB);
                    wr.setStandardFileName(fileNamePathA);

                    wr.setChannelType("0");
                    wr.setResult(finalResult);
                    wr.setAbnormalThreshold("5");
                    wr.setSeriousThreshold("10");
                    wr.setStandardChannelRef(standardCompareChSeq);
                    wr.setStandardChannelDesc(standardChDescribe);

                    wr.setIedFaultInfo(qFaultInfo);
                    wr.setIedFaultInfoCom(qFaultInfoCom);

                    wr.setIedFaultType(faultType);
                    wr.setIedCompFaultType(faultTypeCom);
                    wr.setIedRanging(ringring);
                    wr.setIedCompRing(ringringCom);

                    //
                    QString standardSampleVectorString = "{";
                    foreach (float var, standardSampleVector) {
                        QString varStr = QString("%1").arg(static_cast<double>(var));
                        QString unit = varStr + ", ";
                        standardSampleVectorString += unit;
                    }
                    standardSampleVectorString += "}";
                    wr.setStandardSamplesValue(standardSampleVectorString);

                    //
                    QString standPointSeqString = "{";
                    foreach(float var, standardComparePointSeq){
                       QString varStr = QString("%1").arg(static_cast<double>(var));
                       QString unit = varStr + ", ";
                       standPointSeqString += unit;
                    }
                    standPointSeqString += "}";
                    wr.setStandardSamplesPointSeq(standPointSeqString);

                    wr.setTaskChannelRef(taskCompareChSeq);
                    wr.setTaskChanelDesc(taskChDescribe);

                    //
                    QString taskSampleVectorString = "{";
                    foreach(float var, taskSampleVector){
                        QString varStr = QString("%1").arg(static_cast<double>(var));
                        QString unit = varStr + ", ";
                        taskSampleVectorString += unit;
                    }
                    taskSampleVectorString += "}";
                    wr.setTaskSamplesValue(taskSampleVectorString);

                    //
                    QString taskPointSeqString = "{";
                    foreach(float var, taskComparePointSeq){
                       QString varStr = QString("%1").arg(static_cast<double>(var));
                       QString unit = varStr + ", ";
                       taskPointSeqString.append(unit);
                    }
                    taskPointSeqString += "}";
                    wr.setTaskSamplesPointSeq(taskPointSeqString);

                    //
                    QString relativeErrorString = "{";
                    foreach(double var, relativeError){
                        QString varStr = QString("%1").arg(var);
                        QString unit = varStr + ", ";
                        relativeErrorString += unit;
                    }
                    relativeErrorString += "}";
                    wr.setPointRelativeError(relativeErrorString);

                    //
                    QString absoluteErrorString = "{";
                    foreach(double var, absoluteError){
                        QString varStr = QString("%1").arg(var);
                        QString unit = varStr + ", ";
                        absoluteErrorString += unit;
                    }
                    absoluteErrorString += "}";
                    wr.setPointAbsoluteError(absoluteErrorString);

                    //
                    QString pointConclusionString ="{";
                    foreach(int var, pointConclusion){
                        QString varStr = QString("%1").arg(var);
                        QString unit = varStr + ", ";
                        pointConclusionString += unit;
                    }
                    pointConclusionString += "}";
                    wr.setPointColusion(pointConclusionString);

                    //
                    wr.setRecordTime(reportTime);

                    DBTransientTaskConclusionRecordDAO dao;
                    if(dao.doCreateTable())
                        dao.doInsert(wr.getTTCR());
                    sem.release();

                    QStringList forthWordList;
                    forthWordList << bayNameList.at(i)
                                  << itemNameList.at(i)
                                  << itemTypeList.at(i)
                                  << phaseTypeList.at(i);

                    QStringList keyWordList;
                    keyWordList << iedName1
                                << AFileName
                                << iedName2
                                << BFileName
                                << standardChDescribe
                                << taskChDescribe
                                << finalResult;

                    protkeyWordMap.insertMulti(forthWordList, keyWordList);
                }
            }
        }
//                    QSqlDatabase db;
//                    if(QSqlDatabase::contains("qt_sql_default_connection")){
//                        db = QSqlDatabase::database("qt_sql_default_connection");
//                    }else{
//                        db = QSqlDatabase::addDatabase("QMYSQL");
//                    }
//                    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
//                    db.setDatabaseName("mmsdb");
//                    db.setHostName("127.0.0.1");
//                    db.setUserName("root");
//                    db.setPassword("root");
//                    db.setPort(3306);


//                    if(file.exist()){
//                      DBTransientTaskFileDAO ttfd;
//                      ttfd.doInsert("fileName");
//                    }

        QList<int> startPosList = result.getFirstPosList();
        bool switchRead = result.parseSwitchParameter(iedName1, iedName2, startPosList);
        if(switchRead){
            //开关量
            dcChKeyMap = result.getKeySwicthMap();
            //开关变位时间差
            dcConclusionlistList = result.getDcConclusionlistList();

            //开关变位比对结果
            dcAckResultlistList = result.getDcCompareResultlistList();

            //开关是否一致动作
            jumpAckResultlistList = result.getJumpAckResultlistList();

            //各开关变位时延
            dcAckDelaylistList = result.getDcDelaylistList();

            QList<int> lackNumList = result.getLackNumList();
            //间隔名, 组别, 采样类型, 相别, 套别1, 套别2, 通道描述1, 通道描述2
            QList<QStringList> dcFactorlistList;
            //dataref1, 基准比对通道, 参与比对通道
            QList<QList<int>>  dcChSeqlistList;
            //第i个比对组的基准通道名
            QMap<QStringList, QList<int>>::const_iterator j;
            //总比较组数
            //第i个比对组的基准通道名
            QStringList bayNameList;
            QStringList itemNameList;
            QStringList itemTypeList;
            QStringList phaseTypeList;

            int switchNum = 0;
            for(j=dcChKeyMap.constBegin(); j!=dcChKeyMap.constEnd(); j++){
                bayNameList.append(j.key().at(0));
                itemNameList.append(j.key().at(1));
                itemTypeList.append(j.key().at(2));
                phaseTypeList.append(j.key().at(3));
                dcFactorlistList.append(j.key());
                dcChSeqlistList.append(j.value());
                switchNum++;
            }

            for(int i=0; i<switchNum; i++){
                int standardCompareChSeq = dcChSeqlistList.at(i).at(0) + lackNumList.at(0);
//                "基准对比的录波通道索引"

                QString standardChDescribe = dcFactorlistList.at(i).at(6);
//                "基准对比的录波通道描述"

                QString standardSetType = dcFactorlistList.at(i).at(4);
//                "基准对比的套别1"

                int taskCompareChSeq = dcChSeqlistList.at(i).at(1) + lackNumList.at(1);
//                "参与对比的录波通道索引"

                QString taskChDescribe = dcFactorlistList.at(i).at(7);
//                "参与对比的录波通道描述"

                QString taskSetType = dcFactorlistList.at(i).at(5);
//                "基准对比的套别2"

                QString itemType = itemTypeList.at(i);
                QString phaseType = phaseTypeList.at(i);

                QString reportTime = result.getReportTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
//                "产生结论记录时间"

                QString surgeTime1 = result.getSurgeTimeList().at(0).toString("yyyy-MM-dd hh:mm:ss.zzz");

                //时延对
                QString dcDelayCop;
                //开关A 第一次动作时延
                int dcAckDelayA;
                //开关B 第一次动作时延
                int dcAckDelayB;
                if(dcAckDelaylistList.at(i).size() >=2){
                    //保护A跳闸时延
                    dcAckDelayA = dcAckDelaylistList.at(i).at(0);
                    //保护B跳闸时延
                    dcAckDelayB = dcAckDelaylistList.at(i).at(1);

                    dcDelayCop = QString::number(dcAckDelayA) + "," + QString::number(dcAckDelayB);
                }else{
                    dcAckDelayA = -1;
                    dcAckDelayB = -1;
                    dcDelayCop = QString::number(dcAckDelayA) + "," + QString::number(dcAckDelayB);
                }

                int dcFirstCompareResult = dcAckResultlistList.at(i).at(0);

                int dcFirstConclusion = dcConclusionlistList.at(i).at(0);

                QString jumpAckFirstResult = jumpAckResultlistList.at(i).at(0);

                WriteSwitchResultDao wsr;
                bool wsrFlag = wsr.init();

                if(wsrFlag){
                    //写入开关量数据库
                    QSystemSemaphore sem("sem", 1, QSystemSemaphore::Open);
                    sem.acquire();

//                  "间隔名";
                    wsr.setBayName(bayNameList.at(i));
                    wsr.setItemName(itemNameList.at(i));

                    wsr.setSrIedAFileName(AFileName);
                    wsr.setSrIedBFileName(BFileName);

                    wsr.setIedTaskType(itemType);
                    wsr.setIedPhase(phaseType);

                    wsr.setIedName(iedName1);
                    wsr.setIedNameComp(iedName2);
                    wsr.setSetType(standardSetType);
                    wsr.setSetTypeComp(taskSetType);

                    wsr.setConclusion(jumpAckFirstResult);
                    wsr.setRecloseConclusion(dcFirstConclusion);
                    wsr.setBreakerConclusion(-1);

                    wsr.setTaskFileName(fileNamePathB);
                    wsr.setStandardFileName(fileNamePathA);
                    wsr.setChannelType("1");

                    wsr.setRecloseAckDelay(dcDelayCop);
                    wsr.setBreakerAckDelay("NULL");

                    wsr.setReclosingInnormalTime("15");
                    wsr.setReclosingSeriousTime("20");

                    wsr.setbreakerInnormalTime("15");
                    wsr.setbreakerSeriousTime("20");
                    wsr.setReclosingResult(dcFirstCompareResult);
                    wsr.setBreakerResult(-1);

                    wsr.setTaskChannelRef(taskCompareChSeq);
                    wsr.setTaskChannelDesc(taskChDescribe);

                    wsr.setStandardChannelRef(standardCompareChSeq);
                    wsr.setStandardChannelDesc(standardChDescribe);

                    //记录时间
                    wsr.setRecordTime(reportTime);
                    //故障时间
                    wsr.setFaultZeroTime(surgeTime1);

                    DBTransientSwitchConclusionRecordDAO dao;
                    if(dao.doCreateTable())
                        dao.doInsert(wsr.getTSCR());
                    sem.release();
               }
            }
        }
        return true;
    }else{
        return false;
    }
}

QString ResultIntoDb::getSurgeTime(const int& num)
{
    CompareResult* result = new CompareResult(cfgFile1, cfgFile2);
//    bool readSysconf = result->parse2WaveParameterRef2(iedName1, iedName2);
    bool readSysconf = result->parse2WaveParameter(iedName1, iedName2);
    QString surgeTime;
    if(readSysconf){
        surgeTime = result->getSurgeTimeList().at(num).toString("yyyy-MM-dd hh:mm:ss.zzz");
    }
    result->deleteLater();
    return surgeTime;
}

QString ResultIntoDb::getReportTime()
{
    return reportTime;
}

QMultiMap<QStringList, QStringList> ResultIntoDb::getProtKeyWordMap()
{
    return protkeyWordMap;
}

QStringList ResultIntoDb::getKeyWordList()
{
    CompareResult* result = new CompareResult(cfgFile1, cfgFile2);
    bool readSysconf = result->parse2WaveParameter(iedName1, iedName2);
    QStringList wordList;
    if(readSysconf){
        wordList = result->getWordList();
    }
    result->deleteLater();
    return wordList;
}
