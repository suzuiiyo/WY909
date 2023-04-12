#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QVariant>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbormfactory.h"
#include "dbtransienttaskconclusionrecorddao.h"

DBTransientTaskConclusionRecordDAO::DBTransientTaskConclusionRecordDAO()
    : m_connectionName("connectTTConclusion")
{
    m_ptrOrm = DBOrmFactory::create(TransientTaskConclusionRecordORM::Type);
}

DBTransientTaskConclusionRecordDAO::~DBTransientTaskConclusionRecordDAO()
{

}

int DBTransientTaskConclusionRecordDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->ackTip() != 0)
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM transienttaskconclusionrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND ACKTIP=%2")
                            .arg(ptr->iedName())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM transienttaskconclusionrecord WHERE ACKTIP=%1")
                            .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND RECORDTIME >= '%2' AND RECORDTIME <= '%3'")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM transienttaskconclusionrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2'")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM transienttaskconclusionrecord WHERE IEDNAME='%1' OR IEDNAMECOMP='%1'")
                            .arg(ptr->iedName());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM transienttaskconclusionrecord");
            }
        }
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                count = query.value("ct").toInt();
                if(ok)
                    *ok = bSucc;
                db.close();
                return count;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return count;
}

//int DBTransientTaskConclusionRecordDAO::countRecord(const SearchCondition::Ptr &ptr, QSqlDatabase db, bool *ok)
//{
//    bool bSucc = false;
//    int count = 0;
//    QSqlQuery query(db);
//    QString sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord ORDER BY GUID DESC LIMIT 1");
//    bSucc = query.exec(sql);
//    if (bSucc)
//    {
//        while (query.next())
//        {
//            count = query.value("GUID").toInt();
//            if(ok)
//                *ok = bSucc;
//            return count;
//        }
//    }
//    if(ok)
//        *ok = bSucc;

//    return count;
//}

TransientTaskConclusionRecord::List DBTransientTaskConclusionRecordDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    TransientTaskConclusionRecord::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                TransientTaskConclusionRecord::Ptr ptrCon(new TransientTaskConclusionRecord());
                ptrCon->m_GUID = query.value("GUID").toInt();
                ptrCon->m_iedName = query.value("IEDNAME").toString();
                ptrCon->m_setType = query.value("SETTYPE").toString();
                ptrCon->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                ptrCon->m_setTypeComp = query.value("SETTYPECOMP").toString();
                ptrCon->m_protStartTime = query.value("PROTSTARTTIME").toString();
                ptrCon->m_protStartResetTime = query.value("PROTSTARTRESETTIME").toString();
                ptrCon->m_protFaultNum = query.value("PROTFAULTNUM").toInt();
                ptrCon->m_protFaultValue = query.value("PROTFAULTVALUE").toFloat();
                ptrCon->m_srIedAFileName = query.value("SRIEDAFILENAME").toString();
                ptrCon->m_srIedBFileName = query.value("SRIEDBFILENAME").toString();
                ptrCon->m_srTMDataType = query.value("SRTMDATATYPE").toInt();
                ptrCon->m_srTMDataValue = query.value("SRTMDATAVALUE").toFloat();
                ptrCon->m_srTMThreshold = query.value("SRTMTHRESHOLD").toFloat();
                ptrCon->m_taskFileName = query.value("TASKFILENAME").toString();
                ptrCon->m_standardFileName = query.value("STANDARDFILENAME").toString();
                ptrCon->m_channelType = query.value("CHANNELTYPE").toString();
                ptrCon->m_conclusion = query.value("CONCLUSION").toString();
                ptrCon->m_abnormalThreshold = query.value("ABNORMALTHRESHOLD").toString();
                ptrCon->m_seriousThreshold = query.value("SERIOUSTHRESHOLD").toString();
                ptrCon->m_result = query.value("RESULT").toString();
                ptrCon->m_taskChannelRef = query.value("TASKCHANNELREF").toInt();
                ptrCon->m_taskChannelDesc = query.value("TASKCHANNELDESC").toString();
                ptrCon->m_taskSamplesValue = query.value("TASKSAMPLESVALUE").toString();
                ptrCon->m_taskSamplesPointSeq = query.value("TASKSAMPLESPOINTSEQ").toString();
                ptrCon->m_standardChannelRef = query.value("STANDARDCHANNELREF").toInt();
                ptrCon->m_standardChannelDesc = query.value("STANDARDCHANNELDESC").toString();
                ptrCon->m_standardSamplesValue = query.value("STANDARDSAMPLESVALUE").toString();
                ptrCon->m_standardSamplesPointSeq = query.value("STANDARDSAMPLESPOINTSEQ").toString();
                ptrCon->m_iedFaultType = query.value("IEDFAULTTYPE").toString();
                ptrCon->m_iedRanging = query.value("IEDRANGING").toString();
                ptrCon->m_iedCompFaultType = query.value("IEDCOMPFAULTTYPE").toString();
                ptrCon->m_iedCompRanging = query.value("IEDCOMPRANGING").toString();
                ptrCon->m_recordTime = query.value("RECORDTIME").toString();
                ptrCon->m_ackTip = query.value("ACKTIP").toInt();
                ptrCon->m_iedTaskType = query.value("IEDTASKTYPE").toString();
                ptrCon->m_iedPhase = query.value("IEDPHASE").toString();
                ptrCon->m_bayName = query.value("BAYNAME").toString();
                ptrCon->m_itemName = query.value("ITEMNAME").toString();
                ptrCon->m_faultInfo = query.value("FAULTINFO").toString();
                ptrCon->m_faultInfoComp = query.value("FAULTINFOCOMP").toString();
                ptrCon->m_pointRelativeError = query.value("POINTRELATIVEERROR").toString();
                ptrCon->m_pointAbsoluteError = query.value("POINTABSOLUTEERROR").toString();
                ptrCon->m_pointConclusion = query.value("POINTCONCLUSION").toString();
                lst.append(ptrCon);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TransientTaskConclusionRecord::List DBTransientTaskConclusionRecordDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    TransientTaskConclusionRecord::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while (query.next())
        {
            TransientTaskConclusionRecord::Ptr ptrCon(new TransientTaskConclusionRecord());
            ptrCon->m_GUID = query.value("GUID").toInt();
            ptrCon->m_iedName = query.value("IEDNAME").toString();
            ptrCon->m_setType = query.value("SETTYPE").toString();
            ptrCon->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            ptrCon->m_setTypeComp = query.value("SETTYPECOMP").toString();
            ptrCon->m_protStartTime = query.value("PROTSTARTTIME").toString();
            ptrCon->m_protStartResetTime = query.value("PROTSTARTRESETTIME").toString();
            ptrCon->m_protFaultNum = query.value("PROTFAULTNUM").toInt();
            ptrCon->m_protFaultValue = query.value("PROTFAULTVALUE").toFloat();
            ptrCon->m_srIedAFileName = query.value("SRIEDAFILENAME").toString();
            ptrCon->m_srIedBFileName = query.value("SRIEDBFILENAME").toString();
            ptrCon->m_srTMDataType = query.value("SRTMDATATYPE").toInt();
            ptrCon->m_srTMDataValue = query.value("SRTMDATAVALUE").toFloat();
            ptrCon->m_srTMThreshold = query.value("SRTMTHRESHOLD").toFloat();
            ptrCon->m_taskFileName = query.value("TASKFILENAME").toString();
            ptrCon->m_standardFileName = query.value("STANDARDFILENAME").toString();
            ptrCon->m_channelType = query.value("CHANNELTYPE").toString();
            ptrCon->m_conclusion = query.value("CONCLUSION").toString();
            ptrCon->m_abnormalThreshold = query.value("ABNORMALTHRESHOLD").toString();
            ptrCon->m_seriousThreshold = query.value("SERIOUSTHRESHOLD").toString();
            ptrCon->m_result = query.value("RESULT").toString();
            ptrCon->m_taskChannelRef = query.value("TASKCHANNELREF").toInt();
            ptrCon->m_taskChannelDesc = query.value("TASKCHANNELDESC").toString();
            ptrCon->m_taskSamplesValue = query.value("TASKSAMPLESVALUE").toString();
            ptrCon->m_taskSamplesPointSeq = query.value("TASKSAMPLESPOINTSEQ").toString();
            ptrCon->m_standardChannelRef = query.value("STANDARDCHANNELREF").toInt();
            ptrCon->m_standardChannelDesc = query.value("STANDARDCHANNELDESC").toString();
            ptrCon->m_standardSamplesValue = query.value("STANDARDSAMPLESVALUE").toString();
            ptrCon->m_standardSamplesPointSeq = query.value("STANDARDSAMPLESPOINTSEQ").toString();
            ptrCon->m_iedFaultType = query.value("IEDFAULTTYPE").toString();
            ptrCon->m_iedRanging = query.value("IEDRANGING").toString();
            ptrCon->m_iedCompFaultType = query.value("IEDCOMPFAULTTYPE").toString();
            ptrCon->m_iedCompRanging = query.value("IEDCOMPRANGING").toString();
            ptrCon->m_recordTime = query.value("RECORDTIME").toString();
            ptrCon->m_ackTip = query.value("ACKTIP").toInt();
            ptrCon->m_iedTaskType = query.value("IEDTASKTYPE").toString();
            ptrCon->m_iedPhase = query.value("IEDPHASE").toString();
            ptrCon->m_bayName = query.value("BAYNAME").toString();
            ptrCon->m_itemName = query.value("ITEMNAME").toString();
            ptrCon->m_faultInfo = query.value("FAULTINFO").toString();
            ptrCon->m_faultInfoComp = query.value("FAULTINFOCOMP").toString();
            ptrCon->m_pointRelativeError = query.value("POINTRELATIVEERROR").toString();
            ptrCon->m_pointAbsoluteError = query.value("POINTABSOLUTEERROR").toString();
            ptrCon->m_pointConclusion = query.value("POINTCONCLUSION").toString();
            lst.append(ptrCon);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TransientTaskConclusionRecord::List DBTransientTaskConclusionRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    TransientTaskConclusionRecord::List lst_act;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->ackTip() != -1)
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND PROTSTARTTIME >= '%2' AND PROTSTARTTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC LIMIT %5, %6")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND PROTSTARTTIME >= '%2' AND PROTSTARTTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE PROTSTARTTIME >= '%1' AND PROTSTARTTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE PROTSTARTTIME >= '%1' AND PROTSTARTTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
            }
            else
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND ACKTIP=%2 ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->iedName())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND ACKTIP=%2 ORDER BY GUID DESC")
                                .arg(ptr->iedName())
                                .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE ACKTIP=%1 ORDER BY GUID DESC")
                                    .arg(ptr->ackTip());
                }
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND PROTSTARTTIME >= '%2' AND PROTSTARTTIME <= '%3' ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND PROTSTARTTIME >= '%2' AND PROTSTARTTIME <= '%3' ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE PROTSTARTTIME >= '%1' AND PROTSTARTTIME <= '%2' ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE PROTSTARTTIME >= '%1' AND PROTSTARTTIME <= '%2' ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
            }
            else
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord WHERE IEDNAME='%1' OR IEDNAMECOMP='%1' ORDER BY GUID DESC")
                                .arg(ptr->iedName());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord ORDER BY GUID DESC LIMIT %1, %2")
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord ORDER BY GUID DESC");
                }
            }
        }
        if(sql != "")
        {
            bSucc1 = query.exec(sql);
            if (bSucc1)
            {
                while (query.next())
                {
                    TransientTaskConclusionRecord::Ptr ptrCon(new TransientTaskConclusionRecord());
                    ptrCon->m_GUID = query.value("GUID").toInt();
                    ptrCon->m_iedName = query.value("IEDNAME").toString();
                    ptrCon->m_setType = query.value("SETTYPE").toString();
                    ptrCon->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                    ptrCon->m_setTypeComp = query.value("SETTYPECOMP").toString();
                    ptrCon->m_protStartTime = query.value("PROTSTARTTIME").toString();
                    ptrCon->m_protStartResetTime = query.value("PROTSTARTRESETTIME").toString();
                    ptrCon->m_protFaultNum = query.value("PROTFAULTNUM").toInt();
                    ptrCon->m_protFaultValue = query.value("PROTFAULTVALUE").toFloat();
                    ptrCon->m_srIedAFileName = query.value("SRIEDAFILENAME").toString();
                    ptrCon->m_srIedBFileName = query.value("SRIEDBFILENAME").toString();
                    ptrCon->m_srTMDataType = query.value("SRTMDATATYPE").toInt();
                    ptrCon->m_srTMDataValue = query.value("SRTMDATAVALUE").toFloat();
                    ptrCon->m_srTMThreshold = query.value("SRTMTHRESHOLD").toFloat();
                    ptrCon->m_taskFileName = query.value("TASKFILENAME").toString();
                    ptrCon->m_standardFileName = query.value("STANDARDFILENAME").toString();
                    ptrCon->m_channelType = query.value("CHANNELTYPE").toString();
                    ptrCon->m_conclusion = query.value("CONCLUSION").toString();
                    ptrCon->m_abnormalThreshold = query.value("ABNORMALTHRESHOLD").toString();
                    ptrCon->m_seriousThreshold = query.value("SERIOUSTHRESHOLD").toString();
                    ptrCon->m_result = query.value("RESULT").toString();
                    ptrCon->m_taskChannelRef = query.value("TASKCHANNELREF").toInt();
                    ptrCon->m_taskChannelDesc = query.value("TASKCHANNELDESC").toString();
                    ptrCon->m_taskSamplesValue = query.value("TASKSAMPLESVALUE").toString();
                    ptrCon->m_taskSamplesPointSeq = query.value("TASKSAMPLESPOINTSEQ").toString();
                    ptrCon->m_standardChannelRef = query.value("STANDARDCHANNELREF").toInt();
                    ptrCon->m_standardChannelDesc = query.value("STANDARDCHANNELDESC").toString();
                    ptrCon->m_standardSamplesValue = query.value("STANDARDSAMPLESVALUE").toString();
                    ptrCon->m_standardSamplesPointSeq = query.value("STANDARDSAMPLESPOINTSEQ").toString();
                    ptrCon->m_iedFaultType = query.value("IEDFAULTTYPE").toString();
                    ptrCon->m_iedRanging = query.value("IEDRANGING").toString();
                    ptrCon->m_iedCompFaultType = query.value("IEDCOMPFAULTTYPE").toString();
                    ptrCon->m_iedCompRanging = query.value("IEDCOMPRANGING").toString();
                    ptrCon->m_recordTime = query.value("RECORDTIME").toString();
                    ptrCon->m_ackTip = query.value("ACKTIP").toInt();
                    ptrCon->m_iedTaskType = query.value("IEDTASKTYPE").toString();
                    ptrCon->m_iedPhase = query.value("IEDPHASE").toString();
                    ptrCon->m_bayName = query.value("BAYNAME").toString();
                    ptrCon->m_itemName = query.value("ITEMNAME").toString();
                    ptrCon->m_faultInfo = query.value("FAULTINFO").toString();
                    ptrCon->m_faultInfoComp = query.value("FAULTINFOCOMP").toString();
                    ptrCon->m_pointRelativeError = query.value("POINTRELATIVEERROR").toString();
                    ptrCon->m_pointAbsoluteError = query.value("POINTABSOLUTEERROR").toString();
                    ptrCon->m_pointConclusion = query.value("POINTCONCLUSION").toString();
                    lst_act.append(ptrCon);
                }
            }
            else
                bSucc2 = bSucc1;
        }
        db.close();
    }

    if(ok)
        *ok = bSucc2;

    return lst_act;
}

TransientTaskConclusionRecord::List DBTransientTaskConclusionRecordDAO::doQuery(DBOrmOperation::List &lst, bool *ok)
{
    QSharedPointer<TransientTaskConclusionRecordORM> ormInst = qSharedPointerDynamicCast<TransientTaskConclusionRecordORM>(m_ptrOrm);
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    TransientTaskConclusionRecord::List lst_act;
    if (db.isOpen() || db.open())
    {
        QString sql = "";
        QSqlQuery query(db);

        if(!lst.isEmpty())
        {
            sql = "SELECT * FROM transienttaskconclusionrecord WHERE";
            QHash<int, DBCondition> varColumnInfo = ormInst->columnInfo();
            for(int i=0; i<lst.size(); i++)
            {
                DBOrmOperation::Ptr ptrOp = lst[i];
                if(ptrOp)
                {
                    if(varColumnInfo.contains(ptrOp->dataId()))
                    {
                        sql += ptrOp->linkStr();
                        sql += varColumnInfo[ptrOp->dataId()].name() + ptrOp->opStr();
                        if(varColumnInfo[ptrOp->dataId()].type() != DBCondition::DataType::Unknown)
                        {
                            if(varColumnInfo[ptrOp->dataId()].type() != DBCondition::DataType::Char)
                                sql += ptrOp->value();
                            else
                                sql = sql + "'" + ptrOp->value() + "'";
                        }
                        sql += ptrOp->endStr();
                    }
                }
            }
        }
        else
            sql = "SELECT * FROM transienttaskconclusionrecord";

        //printf("sql: %s\n", sql.toStdString().data());

        QByteArray ba = sql.toUtf8();
        QString sqlMix = QObject::tr(ba.data());
        bSucc = query.exec(sqlMix);
        if(bSucc)
        {
            while(query.next())
            {
                TransientTaskConclusionRecord::Ptr ptrCon(new TransientTaskConclusionRecord());
                ptrCon->m_GUID = query.value("GUID").toInt();
                ptrCon->m_iedName = query.value("IEDNAME").toString();
                ptrCon->m_setType = query.value("SETTYPE").toString();
                ptrCon->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                ptrCon->m_setTypeComp = query.value("SETTYPECOMP").toString();
                ptrCon->m_protStartTime = query.value("PROTSTARTTIME").toString();
                ptrCon->m_protStartResetTime = query.value("PROTSTARTRESETTIME").toString();
                ptrCon->m_protFaultNum = query.value("PROTFAULTNUM").toInt();
                ptrCon->m_protFaultValue = query.value("PROTFAULTVALUE").toFloat();
                ptrCon->m_srIedAFileName = query.value("SRIEDAFILENAME").toString();
                ptrCon->m_srIedBFileName = query.value("SRIEDBFILENAME").toString();
                ptrCon->m_srTMDataType = query.value("SRTMDATATYPE").toInt();
                ptrCon->m_srTMDataValue = query.value("SRTMDATAVALUE").toFloat();
                ptrCon->m_srTMThreshold = query.value("SRTMTHRESHOLD").toFloat();
                ptrCon->m_taskFileName = query.value("TASKFILENAME").toString();
                ptrCon->m_standardFileName = query.value("STANDARDFILENAME").toString();
                ptrCon->m_channelType = query.value("CHANNELTYPE").toString();
                ptrCon->m_conclusion = query.value("CONCLUSION").toString();
                ptrCon->m_abnormalThreshold = query.value("ABNORMALTHRESHOLD").toString();
                ptrCon->m_seriousThreshold = query.value("SERIOUSTHRESHOLD").toString();
                ptrCon->m_result = query.value("RESULT").toString();
                ptrCon->m_taskChannelRef = query.value("TASKCHANNELREF").toInt();
                ptrCon->m_taskChannelDesc = query.value("TASKCHANNELDESC").toString();
                ptrCon->m_taskSamplesValue = query.value("TASKSAMPLESVALUE").toString();
                ptrCon->m_taskSamplesPointSeq = query.value("TASKSAMPLESPOINTSEQ").toString();
                ptrCon->m_standardChannelRef = query.value("STANDARDCHANNELREF").toInt();
                ptrCon->m_standardChannelDesc = query.value("STANDARDCHANNELDESC").toString();
                ptrCon->m_standardSamplesValue = query.value("STANDARDSAMPLESVALUE").toString();
                ptrCon->m_standardSamplesPointSeq = query.value("STANDARDSAMPLESPOINTSEQ").toString();
                ptrCon->m_iedFaultType = query.value("IEDFAULTTYPE").toString();
                ptrCon->m_iedRanging = query.value("IEDRANGING").toString();
                ptrCon->m_iedCompFaultType = query.value("IEDCOMPFAULTTYPE").toString();
                ptrCon->m_iedCompRanging = query.value("IEDCOMPRANGING").toString();
                ptrCon->m_recordTime = query.value("RECORDTIME").toString();
                ptrCon->m_ackTip = query.value("ACKTIP").toInt();
                ptrCon->m_iedTaskType = query.value("IEDTASKTYPE").toString();
                ptrCon->m_iedPhase = query.value("IEDPHASE").toString();
                ptrCon->m_bayName = query.value("BAYNAME").toString();
                ptrCon->m_itemName = query.value("ITEMNAME").toString();
                ptrCon->m_faultInfo = query.value("FAULTINFO").toString();
                ptrCon->m_faultInfoComp = query.value("FAULTINFOCOMP").toString();
                ptrCon->m_pointRelativeError = query.value("POINTRELATIVEERROR").toString();
                ptrCon->m_pointAbsoluteError = query.value("POINTABSOLUTEERROR").toString();
                ptrCon->m_pointConclusion = query.value("POINTCONCLUSION").toString();
                lst_act.append(ptrCon);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst_act;
}

//TransientTaskConclusionRecord::List DBTransientTaskConclusionRecordDAO::doQuery(QSqlDatabase db, const SearchCondition::Ptr &ptr, bool *ok)
//{
//    bool bSucc = false;
//    TransientTaskConclusionRecord::List lst;
//    QSqlQuery query(db);
//    QString sql = "";
//    int startCount = ptr->startCount();
//    int recordCount = ptr->recordCount();
//    if(recordCount != 0)
//        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord ORDER BY GUID DESC LIMIT %1,%2")
//                .arg(startCount)
//                .arg(recordCount);
//    else
//        sql = QObject::tr("SELECT * FROM transienttaskconclusionrecord");
//    bSucc = query.exec(sql);
//    if (bSucc)
//    {
//        while (query.next())
//        {
//            TransientTaskConclusionRecord::Ptr ptrCon(new TransientTaskConclusionRecord());
//            ptrCon->m_GUID = query.value("GUID").toInt();
//            ptrCon->m_iedName = query.value("IEDNAME").toString();
//            ptrCon->m_setType = query.value("SETTYPE").toString();
//            ptrCon->m_iedNameComp = query.value("IEDNAMECOMP").toString();
//            ptrCon->m_setTypeComp = query.value("SETTYPECOMP").toString();
//            ptrCon->m_protStartTime = query.value("PROTSTARTTIME").toString();
//            ptrCon->m_protStartResetTime = query.value("PROTSTARTRESETTIME").toString();
//            ptrCon->m_protFaultNum = query.value("PROTFAULTNUM").toInt();
//            ptrCon->m_protFaultValue = query.value("PROTFAULTVALUE").toFloat();
//            ptrCon->m_srIedAFileName = query.value("SRIEDAFILENAME").toString();
//            ptrCon->m_srIedBFileName = query.value("SRIEDBFILENAME").toString();
//            ptrCon->m_srTMDataType = query.value("SRTMDATATYPE").toInt();
//            ptrCon->m_srTMDataValue = query.value("SRTMDATAVALUE").toFloat();
//            ptrCon->m_srTMThreshold = query.value("SRTMTHRESHOLD").toFloat();
//            ptrCon->m_taskFileName = query.value("TASKFILENAME").toString();
//            ptrCon->m_standardFileName = query.value("STANDARDFILENAME").toString();
//            ptrCon->m_channelType = query.value("CHANNELTYPE").toString();
//            ptrCon->m_conclusion = query.value("CONCLUSION").toString();
//            ptrCon->m_abnormalThreshold = query.value("ABNORMALTHRESHOLD").toString();
//            ptrCon->m_seriousThreshold = query.value("SERIOUSTHRESHOLD").toString();
//            ptrCon->m_result = query.value("RESULT").toString();
//            ptrCon->m_taskChannelRef = query.value("TASKCHANNELREF").toInt();
//            ptrCon->m_taskChannelDesc = query.value("TASKCHANNELDESC").toString();
//            ptrCon->m_taskSamplesValue = query.value("TASKSAMPLESVALUE").toString();
//            ptrCon->m_taskSamplesPointSeq = query.value("TASKSAMPLESPOINTSEQ").toString();
//            ptrCon->m_standardChannelRef = query.value("STANDARDCHANNELREF").toInt();
//            ptrCon->m_standardChannelDesc = query.value("STANDARDCHANNELDESC").toString();
//            ptrCon->m_standardSamplesValue = query.value("STANDARDSAMPLESVALUE").toString();
//            ptrCon->m_standardSamplesPointSeq = query.value("STANDARDSAMPLESPOINTSEQ").toString();
//            ptrCon->m_iedFaultType = query.value("IEDFAULTTYPE").toString();
//            ptrCon->m_iedRanging = query.value("IEDRANGING").toString();
//            ptrCon->m_iedCompFaultType = query.value("IEDCOMPFAULTTYPE").toString();
//            ptrCon->m_iedCompRanging = query.value("IEDCOMPRANGING").toString();
//            ptrCon->m_recordTime = query.value("RECORDTIME").toString();
//            ptrCon->m_ackTip = query.value("ACKTIP").toInt();
//            lst.append(ptrCon);
//        }
//    }
//    if(ok)
//        *ok = bSucc;

//    return lst;
//}

bool DBTransientTaskConclusionRecordDAO::doInsert(const TransientTaskConclusionRecord::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = QObject::tr("INSERT INTO transienttaskconclusionrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', %7, %8, '%9', '%10', %11, %12, %13, '%14', '%15', '%16', '%17', '%18', '%19', '%20', %21, '%22', '%23', '%24', %25, '%26', '%27', '%28', '%29', '%30', '%31', '%32', '%33', %34, '%35', '%36', '%37', '%38', '%39', '%40', '%41', '%42', '%43')")
                .arg(ptr->iedName())                //1
                .arg(ptr->setType())                //2
                .arg(ptr->iedNameComp())            //3
                .arg(ptr->setTypeComp())            //4
                .arg(ptr->protStartTime())          //5
                .arg(ptr->protStartResetTime())     //6
                .arg(ptr->protFaultNum())           //7
                .arg(ptr->protFaultValue())         //8
                .arg(ptr->srIedAFileName())         //9
                .arg(ptr->srIedBFileName())         //10
                .arg(ptr->srTMDataType())           //11
                .arg(ptr->srTMDataValue())          //12
                .arg(ptr->srTMThreshold())          //13
                .arg(ptr->taskFileName())           //14
                .arg(ptr->standardFileName())       //15
                .arg(ptr->channelType())            //16
                .arg(ptr->conclusion())             //17
                .arg(ptr->abnormalThreshold())      //18
                .arg(ptr->seriousThreshold())       //19
                .arg(ptr->result())                 //20
                .arg(ptr->taskChannelRef())         //21
                .arg(ptr->taskChannelDesc())        //22
                .arg(ptr->taskSamplesValue())       //23
                .arg(ptr->taskSamplesValuePointSeq())//24
                .arg(ptr->standardChannelRef())     //25
                .arg(ptr->standardChannelDesc())    //26
                .arg(ptr->standardSamplesValue())   //27
                .arg(ptr->standardSamplesPointSeq())//28
                .arg(ptr->iedFaultType())           //29
                .arg(ptr->iedRanging())             //30
                .arg(ptr->iedCompFaultType())       //31
                .arg(ptr->iedCompRanging())         //32
                .arg(ptr->recordTime())             //33
                .arg(ptr->ackTip())                 //34
                .arg(ptr->iedTaskType())            //35
                .arg(ptr->iedPhase())               //36
                .arg(ptr->bayName())                //37
                .arg(ptr->itemName())               //38
                .arg(ptr->faultInfo())              //39
                .arg(ptr->faultInfoComp())          //40
                .arg(ptr->pointRelativeError())     //41
                .arg(ptr->pointAbsoluteError())     //42
                .arg(ptr->pointColusion());         //43
        query.exec(sql);
        bSucc = query.exec("COMMIT");
        if (!bSucc)
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }

    return bSucc;
}

bool DBTransientTaskConclusionRecordDAO::doInsert(QSqlDatabase db, const TransientTaskConclusionRecord::Ptr &ptr)
{
    bool bSucc = false;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = QObject::tr("INSERT INTO transienttaskconclusionrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', %7, %8, '%9', '%10', %11, %12, %13, '%14', '%15', '%16', '%17', '%18', '%19', '%20', %21, '%22', '%23', '%24', %25, '%26', '%27', '%28', '%29', '%30', '%31', '%32', '%33', %34, '%35', '%36', '%37', '%38', '%39', '%40', '%41', '%42', '%43')")
            .arg(ptr->iedName())                //1
            .arg(ptr->setType())                //2
            .arg(ptr->iedNameComp())            //3
            .arg(ptr->setTypeComp())            //4
            .arg(ptr->protStartTime())          //5
            .arg(ptr->protStartResetTime())     //6
            .arg(ptr->protFaultNum())           //7
            .arg(ptr->protFaultValue())         //8
            .arg(ptr->srIedAFileName())         //9
            .arg(ptr->srIedBFileName())         //10
            .arg(ptr->srTMDataType())           //11
            .arg(ptr->srTMDataValue())          //12
            .arg(ptr->srTMThreshold())          //13
            .arg(ptr->taskFileName())           //14
            .arg(ptr->standardFileName())       //15
            .arg(ptr->channelType())            //16
            .arg(ptr->conclusion())             //17
            .arg(ptr->abnormalThreshold())      //18
            .arg(ptr->seriousThreshold())       //19
            .arg(ptr->result())                 //20
            .arg(ptr->taskChannelRef())         //21
            .arg(ptr->taskChannelDesc())        //22
            .arg(ptr->taskSamplesValue())       //23
            .arg(ptr->taskSamplesValuePointSeq())//24
            .arg(ptr->standardChannelRef())     //25
            .arg(ptr->standardChannelDesc())    //26
            .arg(ptr->standardSamplesValue())   //27
            .arg(ptr->standardSamplesPointSeq())//28
            .arg(ptr->iedFaultType())           //29
            .arg(ptr->iedRanging())             //30
            .arg(ptr->iedCompFaultType())       //31
            .arg(ptr->iedCompRanging())         //32
            .arg(ptr->recordTime())             //33
            .arg(ptr->ackTip())                 //34
            .arg(ptr->iedTaskType())            //35
            .arg(ptr->iedPhase())               //36
            .arg(ptr->bayName())                //37
            .arg(ptr->itemName())               //38
            .arg(ptr->faultInfo())              //39
            .arg(ptr->faultInfoComp())          //40
            .arg(ptr->pointRelativeError())     //41
            .arg(ptr->pointAbsoluteError())     //42
            .arg(ptr->pointColusion());         //43
    query.exec(sql);
    bSucc = query.exec("COMMIT");
    if (!bSucc)
    {
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }

    return bSucc;
}

bool DBTransientTaskConclusionRecordDAO::doInsert(TransientTaskConclusionRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        TransientTaskConclusionRecord::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            TransientTaskConclusionRecord::Ptr ptr(new TransientTaskConclusionRecord());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO transienttaskconclusionrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', %7, %8, '%9', '%10', %11, %12, %13, '%14', '%15', '%16', '%17', '%18', '%19', '%20', %21, '%22', '%23', '%24', %25, '%26', '%27', '%28', '%29', '%30', '%31', '%32', '%33', %34, '%35', '%36', '%37', '%38', '%39', '%40', '%41', '%42', '%43')")
                    .arg(ptr->iedName())                //1
                    .arg(ptr->setType())                //2
                    .arg(ptr->iedNameComp())            //3
                    .arg(ptr->setTypeComp())            //4
                    .arg(ptr->protStartTime())          //5
                    .arg(ptr->protStartResetTime())     //6
                    .arg(ptr->protFaultNum())           //7
                    .arg(ptr->protFaultValue())         //8
                    .arg(ptr->srIedAFileName())         //9
                    .arg(ptr->srIedBFileName())         //10
                    .arg(ptr->srTMDataType())           //11
                    .arg(ptr->srTMDataValue())          //12
                    .arg(ptr->srTMThreshold())          //13
                    .arg(ptr->taskFileName())           //14
                    .arg(ptr->standardFileName())       //15
                    .arg(ptr->channelType())            //16
                    .arg(ptr->conclusion())             //17
                    .arg(ptr->abnormalThreshold())      //18
                    .arg(ptr->seriousThreshold())       //19
                    .arg(ptr->result())                 //20
                    .arg(ptr->taskChannelRef())         //21
                    .arg(ptr->taskChannelDesc())        //22
                    .arg(ptr->taskSamplesValue())       //23
                    .arg(ptr->taskSamplesValuePointSeq())//24
                    .arg(ptr->standardChannelRef())     //25
                    .arg(ptr->standardChannelDesc())    //26
                    .arg(ptr->standardSamplesValue())   //27
                    .arg(ptr->standardSamplesPointSeq())//28
                    .arg(ptr->iedFaultType())           //29
                    .arg(ptr->iedRanging())             //30
                    .arg(ptr->iedCompFaultType())       //31
                    .arg(ptr->iedCompRanging())         //32
                    .arg(ptr->recordTime())             //33
                    .arg(ptr->ackTip())                 //34
                    .arg(ptr->iedTaskType())            //35
                    .arg(ptr->iedPhase())               //36
                    .arg(ptr->bayName())                //37
                    .arg(ptr->itemName())               //38
                    .arg(ptr->faultInfo())              //39
                    .arg(ptr->faultInfoComp())          //40
                    .arg(ptr->pointRelativeError())     //41
                    .arg(ptr->pointAbsoluteError())     //42
                    .arg(ptr->pointColusion());         //43
            if (!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return false;
            }

            count++;
            if (count == 100)
            {
                bSucc = query.exec("COMMIT");
                query.exec("START TRANSACTION");
                count = 0;
            }
        }
        bSucc = query.exec("COMMIT");
        if (!bSucc)
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }

    return bSucc;
}

bool DBTransientTaskConclusionRecordDAO::doInsert(QSqlDatabase db, TransientTaskConclusionRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    TransientTaskConclusionRecord::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        TransientTaskConclusionRecord::Ptr ptr(new TransientTaskConclusionRecord());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO transienttaskconclusionrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', %7, %8, '%9', '%10', %11, %12, %13, '%14', '%15', '%16', '%17', '%18', '%19', '%20', %21, '%22', '%23', '%24', %25, '%26', '%27', '%28', '%29', '%30', '%31', '%32', '%33', %34, '%35', '%36', '%37', '%38', '%39', '%40', '%41', '%42', '%43')")
                .arg(ptr->iedName())                //1
                .arg(ptr->setType())                //2
                .arg(ptr->iedNameComp())            //3
                .arg(ptr->setTypeComp())            //4
                .arg(ptr->protStartTime())          //5
                .arg(ptr->protStartResetTime())     //6
                .arg(ptr->protFaultNum())           //7
                .arg(ptr->protFaultValue())         //8
                .arg(ptr->srIedAFileName())         //9
                .arg(ptr->srIedBFileName())         //10
                .arg(ptr->srTMDataType())           //11
                .arg(ptr->srTMDataValue())          //12
                .arg(ptr->srTMThreshold())          //13
                .arg(ptr->taskFileName())           //14
                .arg(ptr->standardFileName())       //15
                .arg(ptr->channelType())            //16
                .arg(ptr->conclusion())             //17
                .arg(ptr->abnormalThreshold())      //18
                .arg(ptr->seriousThreshold())       //19
                .arg(ptr->result())                 //20
                .arg(ptr->taskChannelRef())         //21
                .arg(ptr->taskChannelDesc())        //22
                .arg(ptr->taskSamplesValue())       //23
                .arg(ptr->taskSamplesValuePointSeq())//24
                .arg(ptr->standardChannelRef())     //25
                .arg(ptr->standardChannelDesc())    //26
                .arg(ptr->standardSamplesValue())   //27
                .arg(ptr->standardSamplesPointSeq())//28
                .arg(ptr->iedFaultType())           //29
                .arg(ptr->iedRanging())             //30
                .arg(ptr->iedCompFaultType())       //31
                .arg(ptr->iedCompRanging())         //32
                .arg(ptr->recordTime())             //33
                .arg(ptr->ackTip())                 //34
                .arg(ptr->iedTaskType())            //35
                .arg(ptr->iedPhase())               //36
                .arg(ptr->bayName())                //37
                .arg(ptr->itemName())               //38
                .arg(ptr->faultInfo())              //39
                .arg(ptr->faultInfoComp())          //40
                .arg(ptr->pointRelativeError())     //41
                .arg(ptr->pointAbsoluteError())     //42
                .arg(ptr->pointColusion());         //43
        if (!query.exec(sql))
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
            return false;
        }

        count++;
        if (count == 100)
        {
            bSucc = query.exec("COMMIT");
            query.exec("START TRANSACTION");
            count = 0;
        }
    }
    bSucc = query.exec("COMMIT");
    if (!bSucc)
    {
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }

    return bSucc;
}

bool DBTransientTaskConclusionRecordDAO::doUpdate(TransientTaskConclusionRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    TransientTaskConclusionRecord::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        while(iter < lst.end())
        {
            TransientTaskConclusionRecord::Ptr ptr(new TransientTaskConclusionRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE transienttaskconclusionrecord SET RECORDTIME='%1' WHERE GUID=%2")
                    .arg(ptr->recordTime())//1
                    .arg(ptr->GUID());     //2
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }
            iter++;
        }
        bSucc = query.exec("COMMIT");
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }

    return bSucc;
}

bool DBTransientTaskConclusionRecordDAO::ackRecord(TransientTaskConclusionRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    TransientTaskConclusionRecord::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            TransientTaskConclusionRecord::Ptr ptr(new TransientTaskConclusionRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE transienttaskconclusionrecord SET ACKTIP=%1 WHERE GUID=%2")
                    .arg(ptr->ackTip())
                    .arg(ptr->GUID());
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }
        }
        bSucc = query.exec("COMMIT");
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }

    return bSucc;
}

bool DBTransientTaskConclusionRecordDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS transienttaskconclusionrecord("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "SETTYPE VARCHAR(255) NOT NULL,"
                                  "IEDNAMECOMP VARCHAR(255) NOT NULL,"
                                  "SETTYPECOMP VARCHAR(255) NOT NULL,"
                                  "PROTSTARTTIME VARCHAR(255) NOT NULL,"
                                  "PROTSTARTRESETTIME VARCHAR(255) NOT NULL,"
                                  "PROTFAULTNUM INT(11) NOT NULL,"
                                  "PROTFAULTVALUE FLOAT(10,6) NOT NULL,"
                                  "SRIEDAFILENAME VARCHAR(255) NOT NULL,"
                                  "SRIEDBFILENAME VARCHAR(255) NOT NULL,"
                                  "SRTMDATATYPE INT(11) NOT NULL,"
                                  "SRTMDATAVALUE FLOAT(10,6) NOT NULL,"
                                  "SRTMTHRESHOLD FLOAT(10,6) NOT NULL,"
                                  "TASKFILENAME VARCHAR(255) NOT NULL,"
                                  "STANDARDFILENAME VARCHAR(255) NOT NULL,"
                                  "CHANNELTYPE VARCHAR(255) NOT NULL,"
                                  "CONCLUSION VARCHAR(255) NOT NULL,"
                                  "ABNORMALTHRESHOLD VARCHAR(255) NOT NULL,"
                                  "SERIOUSTHRESHOLD VARCHAR(255) NOT NULL,"
                                  "RESULT VARCHAR(255) NOT NULL,"
                                  "TASKCHANNELREF INT(11) NOT NULL,"
                                  "TASKCHANNELDESC VARCHAR(255) NOT NULL,"
                                  "TASKSAMPLESVALUE TEXT,"
                                  "TASKSAMPLESPOINTSEQ TEXT,"
                                  "STANDARDCHANNELREF INT(11) NOT NULL,"
                                  "STANDARDCHANNELDESC VARCHAR(255) NOT NULL,"
                                  "STANDARDSAMPLESVALUE TEXT,"
                                  "STANDARDSAMPLESPOINTSEQ TEXT,"
                                  "IEDFAULTTYPE VARCHAR(255) NOT NULL,"
                                  "IEDRANGING VARCHAR(255) NOT NULL,"
                                  "IEDCOMPFAULTTYPE VARCHAR(255) NOT NULL,"
                                  "IEDCOMPRANGING VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "ACKTIP INT(11) NOT NULL DEFAULT 0,"
                                  "IEDTASKTYPE VARCHAR(255) NOT NULL DEFAULT '',"
                                  "IEDPHASE VARCHAR(255) NOT NULL DEFAULT '',"
                                  "BAYNAME VARCHAR(255) NOT NULL DEFAULT '',"
                                  "ITEMNAME VARCHAR(255) NOT NULL DEFAULT '',"
                                  "FAULTINFO longtext NOT NULL,"
                                  "FAULTINFOCOMP longtext NOT NULL,"
                                  "POINTRELATIVEERROR longtext NOT NULL,"
                                  "POINTABSOLUTEERROR longtext NOT NULL,"
                                  "POINTCONCLUSION longtext NOT NULL,"
                                  "PRIMARY KEY(GUID))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

//bool DBTransientTaskConclusionRecordDAO::doUpdate(QSqlDatabase db, TransientTaskConclusionRecord::List &lst)
//{
//    bool bSucc = false;
//    if(lst.size() == 0)
//        return bSucc;
//    TransientTaskConclusionRecord::List::iterator iter = lst.begin();
//    QSqlQuery query(db);
//    query.exec("START TRANSACTION");

//    while(iter < lst.end())
//    {
//        TransientTaskConclusionRecord::Ptr ptr(new TransientTaskConclusionRecord());
//        ptr = *iter;

//        QString sql = QObject::tr("UPDATE transienttaskconclusionrecord SET PROTSTARTTIME='%1', PROTSTARTRESETTIME='%2', PROTFAULTNUM=%3, PROTFAULTVALUE=%4, SRIEDAFILENAME='%5', SRIEDBFILENAME='%6', SRTMDATATYPE=%7, SRTMDATAVALUE=%8, SRTMTHRESHOLD=%9, TASKFILENAME='%10', STANDARDFILENAME='%11', CHANNELTYPE='%12', CONCLUSION='%13', ABNORMALTHRESHOLD='%14', SERIOUSTHRESHOLD='%15', TASKCHANNELREF=%16, TASKCHANNELDESC='%17', TASKSAMPLES='%18', STANDARDCHANNELREF=%19, STANDARDCHANNELDESC='%20', STANDARDSAMPLES='%21', RECORDTIME='%22' WHERE GUID=%23")
//                .arg(ptr->protStartTime())          //1
//                .arg(ptr->protStartResetTime())     //2
//                .arg(ptr->protFaultNum())           //3
//                .arg(ptr->protFaultValue())         //4
//                .arg(ptr->srIedAFileName())         //5
//                .arg(ptr->srIedBFileName())         //6
//                .arg(ptr->srTMDataType())           //7
//                .arg(ptr->srTMDataValue())          //8
//                .arg(ptr->srTMThreshold())          //9
//                .arg(ptr->taskFileName())           //10
//                .arg(ptr->standardFileName())       //11
//                .arg(ptr->channelType())            //12
//                .arg(ptr->conclusion())             //13
//                .arg(ptr->abnormalThreshold())      //14
//                .arg(ptr->seriousThreshold())       //15
//                .arg(ptr->taskChannelRef())         //16
//                .arg(ptr->taskChannelDesc())        //17
//                .arg(ptr->taskSamples())            //18
//                .arg(ptr->standardChannelRef())     //19
//                .arg(ptr->standardChannelDesc())    //20
//                .arg(ptr->standardSamples())        //21
//                .arg(ptr->recordTime())             //22
//                .arg(ptr->GUID());                  //23
//        if(!query.exec(sql))
//        {
//            QString error_s = query.lastError().text();
//            printf("error: %s", error_s.toStdString().data());
//            return bSucc;
//        }
//        iter++;
//    }
//    bSucc = query.exec("COMMIT");
//    if(!bSucc){
//        QString error_s = query.lastError().text();
//        printf("error: %s", error_s.toStdString().data());
//    }

//    return bSucc;
//}
