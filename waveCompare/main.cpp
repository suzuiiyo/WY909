#include <QCoreApplication>
#include <QDebug>
#include <resultintodb.h>
#include <recognizecomtradefile.h>
#include <QFile>
#include <QList>
#include <QMap>
#include <QMutex>
#include "hdrReader.h"
#include "reportWriter.h"
#include "chanelparadao.h"
#include "dbtransienttaskconclusionrecorddao.h"
#include "searchcondition.h"
#include <QFileInfo>
#include <QDir>
#include <QSystemSemaphore>
#include "dborm.h"
#include "dbcondition.h"

QString curWorkPath;
//const int log_size = 6*1024*1024;          //日志文件大小
//const int reserve_size = 2*1024*1024;      //超出之后保留部分

//void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    Q_UNUSED(context);
//    static QMutex mutex;
//    mutex.lock();

//    QString message = QString("[%1] %2").arg(QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss.zzz")).arg(msg);
//    if(type == QtCriticalMsg){
//        printf(message.toUtf8().constData());
//    }
//    else
//    {
//        QString logPath = curWorkPath + QString("/暂态比对日志/");

//        QDir dir(logPath);
//        if(!dir.exists()){
//            dir.mkpath(logPath);
//        }
//        QFile logFile(logPath + QString("暂态比对日志_") + QString("%1").arg(QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss.zzz") + QString(".log")));
//        if(logFile.open(QIODevice::ReadWrite | QIODevice::Append))
//        {
//            if(logFile.size() >= log_size)
//            {
//                int fsize = logFile.size();
//                char* chbuf = new char[reserve_size + 5*1024];
//                logFile.seek(fsize-reserve_size);
//                logFile.read(chbuf, reserve_size);
//                logFile.seek(0);
//                logFile.write(chbuf, reserve_size);
//                logFile.resize(reserve_size);
//                logFile.close();
//                delete []chbuf;

//                if(logFile.open(QIODevice::WriteOnly | QIODevice::Append)){
//                    QTextStream text_stream(&logFile);
//                    text_stream << message << endl;
//                    logFile.flush();
//                    logFile.close();
//                }
//            }
//            else
//            {
//                QTextStream text_stream(&logFile);
//                text_stream << message << endl;
//                logFile.flush();
//                logFile.close();
//            }
//        }
//    }
//    mutex.unlock();
//}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    curWorkPath = QCoreApplication::applicationDirPath();
    curWorkPath += QString("/");

    //注册MessageHandler
//    qInstallMessageHandler(outputMessage);

    qDebug("waveCompare 程序启动\n");
    qDebug("传入参数列表:");
    for(int i=1; i< argc; i++){
        qDebug() << argv[i];
    }

    QByteArray strTemp = QString(argv[1]).trimmed().toLatin1();
    char* strFile;
    strFile = strTemp.data();
    char* charFile = strrchr(strFile,  '/');
    QString taskFileName = QString(charFile).section("/", 1, 1);
    QByteArray strTemp2 = QString(argv[2]).trimmed().toLatin1();
    char* strFile2;
    strFile2 = strTemp2.data();
    char* charFile2 = strrchr(strFile2,  '/');
    QString standFileName = QString(charFile2).section("/", 1, 1);

    QStringList paraIedNameList;
    paraIedNameList << argv[4]
                    << argv[3];

    //统计写入记录条数
    int iCount=0;
    //无对套结果
    xmlINFO localResult;
    //本次保护文件突变时间
    QString surgeTime1;
    //传入文件列表,录波在前,保护在后
    RecognizeComtradeFile recComFile(argv[2], argv[1], paraIedNameList);
    //判断文件是否存在
    bool fileStatus = recComFile.getFileExistStatus();
    //传递四元组
    QStringList headWordListRef2;
    QStringList headWordList;
    if(fileStatus){
       //是否传入成功
       bool transFileStatus = recComFile.transCompareFile();
       if(transFileStatus){
           //获取写入数据库对象,解析并写入数据库
           ResultIntoDb* resultDb = recComFile.getResultIntoDb();
           bool resultStatus = resultDb->productResult(iCount, localResult);
           resultDb->deleteLater();
           if(resultStatus){
                surgeTime1 = resultDb->getSurgeTime(0);
                headWordListRef2 = resultDb->getKeyWordList();
                qDebug() << "计算比对结果成功";
           }else{
                qDebug() << "比对失败";
           }
       }else{
           qDebug("没有文件传入，程序即将退出，请传入录波文件目录");
           exit(0);
       }
    }else{
       qDebug("该目录下录波文件不存在,程序退出");
       exit(0);
    }

    DBOrmOperation::List dbList;
    DBTransientTaskConclusionRecordDAO* ttcr = new DBTransientTaskConclusionRecordDAO();
    DBOrmOperation::Ptr dbo(new DBOrmOperation());
    dbo->setDataId(TransientTaskConclusionRecordORM::taskFileName);
    dbo->setDataType(DBOrmOperation::Char);
    dbo->setOpType(DBOrmOperation::OpType::seq);
    dbo->setValue(taskFileName);
    dbList.append(dbo);
//    QString surgeTimeBefore = QDateTime::fromString(surgeTime1, "yyyy-MM-dd hh:mm:ss.zzz").addSecs(-1).toString("yyyy-MM-dd hh:mm:ss.zzz");
//    QString surgeTimeAfter = QDateTime::fromString(surgeTime1, "yyyy-MM-dd hh:mm:ss.zzz").addSecs(+1).toString("yyyy-MM-dd hh:mm:ss.zzz");

//    scd->setStartTime(surgeTimeBefore);
//    scd->setEndTime(surgeTimeAfter);
    QList<QStringList> iedlistList = ChanelParaDAO::getIedInfoList();
    QStringList iedList = ChanelParaDAO::getIedInfo(argv[4]);
    QString stationName = ChanelParaDAO::getStationName();
    QString bayName = ChanelParaDAO::getBayName(argv[4]);

    //保护比对数据
    QMultiMap<QStringList, QStringList> protWordMap;

    bool protInsertStatus = false;

    //如果有对套,才需要回读数据库
    //有对套,录波只有一套有三组结果
    //有对套,录波有两套有五组结果
    if(!iedList.at(2).isEmpty()){
        QSystemSemaphore sem("sem", 1, QSystemSemaphore::Open);
        sem.acquire();
        TransientTaskConclusionRecord::List conclusionListWithoutProtPair = ttcr->doQuery(dbList);
        sem.release();
        //数据库已写入数据
        //一组进行n次比对结果,取n=2
        if(conclusionListWithoutProtPair.size()>=2*iCount){
            //先查一遍,写入保护比对数据
            //取出全部信息
            QMultiMap<QStringList, QStringList> protInfoMap;
            foreach(QSharedPointer<TransientTaskConclusionRecord> var, conclusionListWithoutProtPair){
                //四元组确定唯一性
                QStringList forthWordList;
                forthWordList << var->bayName()
                              << var->itemName()
                              << var->iedTaskType()
                              << var->iedPhase();

                QStringList protInfoList;
                protInfoList << var->iedName()
                             << var->iedNameComp()
//                           << var->standardFileName();
                             << var->srIedAFileName();

                for(int i=0; i<headWordListRef2.size(); i+=8){
                    QStringList sectionList = headWordListRef2.mid(i, 8);
                    for(int j=0; j<4; j++){
                        if(forthWordList.size() >= 4
                            &&
                            !QString::compare(sectionList.at(j), forthWordList.at(j))){
                              protInfoMap.insertMulti(forthWordList, protInfoList);
                        }
                    }
                }
            }

            QMultiMap<QStringList, QStringList>::const_iterator proti;
            QMultiMap<QStringList, QStringList>::const_iterator protj;
            QString protPath1;
            QString protPath2;
            QString protIedName1;
            QString protIedName2;
            QStringList protIedNameList;
            for(proti=protInfoMap.constBegin(); proti!=protInfoMap.constEnd(); proti++){
                for(protj=protInfoMap.constBegin(); protj!=protInfoMap.constEnd(); protj++){
                    if(proti.value().at(1) == protj.value().at(1) && proti.value().at(0) != protj.value().at(0)){
                       QFileInfo finfo1(proti.value().at(2));
                       QFileInfo finfo2(protj.value().at(2));
                       protPath1 = finfo1.absolutePath()+QString("/%1").arg(finfo1.completeBaseName());
                       protPath2 = finfo2.absolutePath()+QString("/%1").arg(finfo2.completeBaseName());

                       protIedName1 = proti.value().at(0);
                       protIedName2 = protj.value().at(0);
                    }
                }
            }
            protIedNameList << protIedName1 << protIedName2;
            RecognizeComtradeFile recComFile(protPath1, protPath2, protIedNameList);
            bool fileExist = recComFile.getFileExistStatus();
            if(fileExist){
               bool transSucc = recComFile.transCompareFile();
               //写入保护比对结论
               if(transSucc){
                    ResultIntoDb* resultDb = recComFile.getResultIntoDb();
                    protInsertStatus = resultDb->productResult();
                    headWordList = resultDb->getKeyWordList();
                    protWordMap = resultDb->getProtKeyWordMap();
                    QString setTime = resultDb->getReportTime();
                    resultDb->deleteLater();

                    foreach(QSharedPointer<TransientTaskConclusionRecord> var, conclusionListWithoutProtPair)
                    {
                        var->setRecordTime(setTime);
                    }
                    ttcr->doUpdate(conclusionListWithoutProtPair);
               }else{
                    qDebug() << "保护比对文件传入失败";
               }
            }else{
                qDebug() << "对套文件不存在";
            }
        }else{
            qDebug() << "数据库未写入对套数据";
        }
    }else if(iedList.at(2).isEmpty()){
        QMultiMap<QStringList, QStringList> keyWordMap;
        QSystemSemaphore sem("sem", 1, QSystemSemaphore::Open);
        sem.acquire();
        TransientTaskConclusionRecord::List conclusionListWithoutProtPair = ttcr->doQuery(dbList);
        sem.release();
        foreach(QSharedPointer<TransientTaskConclusionRecord> var, conclusionListWithoutProtPair){
          //四元组确定唯一性
          QStringList forthWordList;
          forthWordList << var->bayName()
                        << var->itemName()
                        << var->iedTaskType()
                        << var->iedPhase();

          QStringList keyWordList;
          keyWordList << var->iedName()
                      << var->srIedAFileName()
                      << var->iedNameComp()
                      << var->srIedBFileName()
                      << var->standardChannelDesc()
                      << var->taskChannelDesc()
                      << var->result();

          for(int i=0; i<headWordListRef2.size(); i+=8){
              QStringList sectionList = headWordListRef2.mid(i, 8);
              for(int j=0; j<4; j++){
                  if(forthWordList.size() >=4
                     &&
                     !QString::compare(sectionList.at(j), forthWordList.at(j))){
                       keyWordMap.insertMulti(forthWordList, keyWordList);
                  }
              }
          }
       }

       //包含保护和录波
       QString iedDesc;
       QString recordDesc;
       foreach(QStringList varList, iedlistList){
           if(argv[4] == varList.at(0)){
              iedDesc = varList.at(1);
           }

           if(argv[3] == varList.at(0)){
              recordDesc = varList.at(1);
           }
       }

       QMultiMap<QStringList, QStringList>::const_iterator keyi;
       QSet<QStringList> resultInfoSet;
       for(keyi = keyWordMap.constBegin(); keyi!=keyWordMap.constEnd(); keyi++){
            //获取iedName, 通道描述和结论
            QString standChName = keyi.value().at(4);
            QString taskChName = keyi.value().at(5);
            QString finalResult = keyi.value().at(6);

            QStringList resultInfoList;
            resultInfoList << argv[4] << argv[3] << standChName << taskChName << finalResult;

            resultInfoSet.insert(resultInfoList);
       }

       localResult.station = stationName;
       localResult.bayName = bayName;
       localResult.iedDescList << iedDesc << recordDesc;
       localResult.fileNameList << standFileName << taskFileName;
       localResult.resultSet = resultInfoSet;
//       if(2*iCount == localResult.resultSet.size()){
          ReportWriter xw(localResult, surgeTime1);
          xw.writeReportTwo();
//       }
       return 0;
    }

    QSystemSemaphore sem("sem", 1, QSystemSemaphore::Open);
    sem.acquire();
    TransientTaskConclusionRecord::List conclusionList = ttcr->doQuery(dbList);
    sem.release();
    //保护比对数据已写入重查一次
    if(protInsertStatus){
        //取出全部信息
        QMultiMap<QStringList, QStringList> keyWordMap;
        //取对套信息和比对结果
//        QMultiMap<QStringList, QStringList> iedComScreMap;
        //取本套信息
        foreach(QSharedPointer<TransientTaskConclusionRecord> var, conclusionList){
          //四元组确定唯一性
          QStringList forthWordList;
          forthWordList << var->bayName()
                        << var->itemName()
                        << var->iedTaskType()
                        << var->iedPhase();

          //iedName, standFileName, iedNameCom, taskFileName, standChDesc, taskChesc, result
          QStringList keyWordList;
          keyWordList << var->iedName()
                      << var->srIedAFileName()
                      << var->iedNameComp()
                      << var->srIedBFileName()
                      << var->standardChannelDesc()
                      << var->taskChannelDesc()
                      << var->result();

          for(int i=0; i<headWordListRef2.size(); i+=8){
              QStringList sectionList = headWordListRef2.mid(i, 8);
              for(int j=0; j<4; j++){
                  if(forthWordList.size() >=4
                      &&
                     !QString::compare(sectionList.at(j), forthWordList.at(j))){
                      keyWordMap.insertMulti(forthWordList, keyWordList);
                  }
              }
           }
        }
        //合并结果
        QMultiMap<QStringList, QStringList>::const_iterator ik;
        for(ik=protWordMap.constBegin(); ik!=protWordMap.constEnd(); ik++)
        {
            keyWordMap.insertMulti(ik.key(), ik.value());
        }

        QMultiMap<QStringList, QStringList>::const_iterator keyi;
        //排序去重
        QSet<QStringList> iedfileCorrSet;
        QSet<QStringList> resultInfoSet;

        //int a=0;
        //求两套保护设备信息
        for(keyi = keyWordMap.constBegin(); keyi != keyWordMap.constEnd(); keyi++){
            QString iedName = keyi.value().at(0);
            QString comIedName = keyi.value().at(2);

            QString fileName = keyi.value().at(1);
            QString comFileName = keyi.value().at(3);

            QFileInfo finfo(fileName);
            QString fileNamePath = finfo.completeBaseName();

            QFileInfo finfoCom(comFileName);
            QString comfileNamePath = finfoCom.completeBaseName();

            //包含保护和录波
            QString iedDesc;
            QString comDesc;
            foreach(QStringList varList, iedlistList){
               if(iedName == varList.at(0)){
                  iedDesc = varList.at(1);
               }

               if(comIedName == varList.at(0)){
                  comDesc = varList.at(1);
               }
            }

            QStringList iedFileList;
            QStringList comIedFileList;
            iedFileList << iedName << fileNamePath << iedDesc;
            comIedFileList << comIedName << comfileNamePath << comDesc;

            //获取所有的iedName,文件名和 ied描述
            iedfileCorrSet.insert(iedFileList);
            iedfileCorrSet.insert(comIedFileList);

            //获取iedName, 通道描述和结论
            QString standChName = keyi.value().at(4);
            QString taskChName = keyi.value().at(5);
            QString finalResult = keyi.value().at(6);

            QStringList resultInfoList;
            resultInfoList << iedName << comIedName << standChName << taskChName << finalResult;

            resultInfoSet.insert(resultInfoList);
       }

       xmlINFO xmlResult;
       xmlResult.station = stationName;
       xmlResult.bayName = bayName;

       //将record信息放在最后
       QList<QStringList> sortfileCorrList;
       foreach(QStringList varList, iedfileCorrSet){
          sortfileCorrList.append(varList);
       }

       for(int i=0; i<sortfileCorrList.size(); i++){
          if(argv[3] == sortfileCorrList.at(0).at(0)){
              sortfileCorrList.append(sortfileCorrList.at(0));
              sortfileCorrList.removeFirst();
          }else if(argv[3] == sortfileCorrList.at(1).at(0)){
              sortfileCorrList.append(sortfileCorrList.at(1));
              sortfileCorrList.removeOne(sortfileCorrList.at(1));
          }
       }

       foreach(QStringList varList, sortfileCorrList)
       {
          xmlResult.iedNameList.append(varList.at(0));

          QFileInfo finfo(varList.at(1));
          QString fileNamePath = finfo.completeBaseName();
          xmlResult.fileNameList.append(fileNamePath);
          xmlResult.iedDescList.append(varList.at(2));
       }

       xmlResult.resultSet = resultInfoSet;
//       if(3*iCount == resultInfoSet.size()){
           ReportWriter xw(xmlResult, surgeTime1);
           xw.writeReportThree();
//       }
    }else{
        qDebug() << "保护比对数据写入数据库失败";
    }
    return 0;
}


