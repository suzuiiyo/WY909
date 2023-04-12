#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QVariant>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbormfactory.h"
#include "dbtransientswitchconclusionrecorddao.h"

DBTransientSwitchConclusionRecordDAO::DBTransientSwitchConclusionRecordDAO()
    : m_connectionName("connectTTConclusion")
{
    m_ptrOrm = DBOrmFactory::create(TransientSwitchTaskConclusionRecordORM::Type);
}

DBTransientSwitchConclusionRecordDAO::~DBTransientSwitchConclusionRecordDAO()
{

}

int DBTransientSwitchConclusionRecordDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->ackTip() != 0)
        {
            if(!ptr->iedName().isEmpty()){
                sql = QObject::tr("SELECT count(*) as ct FROM transientswitchtaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND ACKTIP=%2")
                    .arg(ptr->iedName())
                    .arg(ptr->ackTip());
            }
            else{
                sql = QObject::tr("SELECT count(*) as ct FROM transientswitchtaskconclusionrecord WHERE ACKTIP=%1")
                    .arg(ptr->ackTip());
            }
        }else{
            if(!ptr->iedName().isEmpty())
                sql = QObject::tr("SELECT count(*) as ct FROM transientswitchtaskconclusionrecord WHERE IEDNAME='%1' OR IEDNAMECOMP='%1'")
                    .arg(ptr->iedName());
            else
                sql = QObject::tr("SELECT count(*) as ct FROM transientswitchtaskconclusionrecord");
        }
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
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

TransientSwitchTaskConclusionRecord::List DBTransientSwitchConclusionRecordDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    TransientSwitchTaskConclusionRecord::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord");
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while (query.next()) {
                TransientSwitchTaskConclusionRecord::Ptr ptrCon(new TransientSwitchTaskConclusionRecord());
                ptrCon->setGUID(query.value("GUID").toInt());
                ptrCon->setIedName(query.value("IEDNAME").toString());
                ptrCon->setSetType(query.value("SETTYPE").toString());
                ptrCon->setIedNameComp(query.value("IEDNAMECOMP").toString());
                ptrCon->setSetTypeComp(query.value("SETTYPECOMP").toString());
                ptrCon->setRecloseAckDelay(query.value("RECLOSEACKDELAY").toString());
                ptrCon->setBreakerAckDelay(query.value("BREAKERACKDELAY").toString());
                ptrCon->setFaultZeroTime(query.value("FAULTZEROTIME").toString());
                ptrCon->setSrIedAFileName(query.value("SRIEDAFILENAME").toString());
                ptrCon->setSrIedBFileName(query.value("SRIEDBFILENAME").toString());
                ptrCon->setTaskFileName(query.value("TASKFILENAME").toString());
                ptrCon->setStandardFileName(query.value("STANDARDFILENAME").toString());
                ptrCon->setChannelType(query.value("CHANNELTYPE").toString());
                ptrCon->setConclusion(query.value("CONCLUSION").toString());
                ptrCon->setRecloseConclusion(query.value("RECLOSECONCLUSION").toFloat());
                ptrCon->setBreakerConclusion(query.value("BREAKERCONCLUSION").toFloat());
                ptrCon->setReclosingInnormalTime(query.value("RECLOSINGINNORMALTIME").toString());
                ptrCon->setReclosingSeriousTime(query.value("RECLOSINGSERIOUSTIME").toString());
                ptrCon->setBreakerInnormalTime(query.value("BREAKERINNORMALTIME").toString());
                ptrCon->setBreakerSeriousTime(query.value("BREAKERSERIOUSTIME").toString());
                ptrCon->setBreakerResult(query.value("BREAKERRESULT").toInt());
                ptrCon->setReclosingResult(query.value("RECLOSINGRESULT").toInt());
                ptrCon->setTaskChannelRef(query.value("TASKCHANNELREF").toInt());
                ptrCon->setTaskChannelDesc(query.value("TASKCHANNELDESC").toString());
                ptrCon->setStandChannelRef(query.value("STANDARDCHANNELREF").toInt());
                ptrCon->setStandChannelDesc(query.value("STANDARDCHANNELDESC").toString());
                ptrCon->setRecordTime(query.value("RECORDTIME").toString());
                ptrCon->setAckTip(query.value("ACKTIP").toInt());
                ptrCon->setIedTaskType(query.value("IEDTASKTYPE").toString());
                ptrCon->setIedPhase(query.value("IEDPHASE").toString());
                ptrCon->setBayName(query.value("BAYNAME").toString());
                ptrCon->setItemName(query.value("ITEMNAME").toString());
                lst.append(ptrCon);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TransientSwitchTaskConclusionRecord::List DBTransientSwitchConclusionRecordDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    TransientSwitchTaskConclusionRecord::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord");
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while (query.next()) {
            TransientSwitchTaskConclusionRecord::Ptr ptrCon(new TransientSwitchTaskConclusionRecord());
            ptrCon->setGUID(query.value("GUID").toInt());
            ptrCon->setIedName(query.value("IEDNAME").toString());
            ptrCon->setSetType(query.value("SETTYPE").toString());
            ptrCon->setIedNameComp(query.value("IEDNAMECOMP").toString());
            ptrCon->setSetTypeComp(query.value("SETTYPECOMP").toString());
            ptrCon->setRecloseAckDelay(query.value("RECLOSEACKDELAY").toString());
            ptrCon->setBreakerAckDelay(query.value("BREAKERACKDELAY").toString());
            ptrCon->setFaultZeroTime(query.value("FAULTZEROTIME").toString());
            ptrCon->setSrIedAFileName(query.value("SRIEDAFILENAME").toString());
            ptrCon->setSrIedBFileName(query.value("SRIEDBFILENAME").toString());
            ptrCon->setTaskFileName(query.value("TASKFILENAME").toString());
            ptrCon->setStandardFileName(query.value("STANDARDFILENAME").toString());
            ptrCon->setChannelType(query.value("CHANNELTYPE").toString());
            ptrCon->setConclusion(query.value("CONCLUSION").toString());
            ptrCon->setRecloseConclusion(query.value("RECLOSECONCLUSION").toFloat());
            ptrCon->setBreakerConclusion(query.value("BREAKERCONCLUSION").toFloat());
            ptrCon->setReclosingInnormalTime(query.value("RECLOSINGINNORMALTIME").toString());
            ptrCon->setReclosingSeriousTime(query.value("RECLOSINGSERIOUSTIME").toString());
            ptrCon->setBreakerInnormalTime(query.value("BREAKERINNORMALTIME").toString());
            ptrCon->setBreakerSeriousTime(query.value("BREAKERSERIOUSTIME").toString());
            ptrCon->setReclosingResult(query.value("RECLOSINGRESULT").toInt());
            ptrCon->setBreakerResult(query.value("BREAKERRESULT").toInt());
            ptrCon->setTaskChannelRef(query.value("TASKCHANNELREF").toInt());
            ptrCon->setTaskChannelDesc(query.value("TASKCHANNELDESC").toString());
            ptrCon->setStandChannelRef(query.value("STANDARDCHANNELREF").toInt());
            ptrCon->setStandChannelDesc(query.value("STANDARDCHANNELDESC").toString());
            ptrCon->setRecordTime(query.value("RECORDTIME").toString());
            ptrCon->setAckTip(query.value("ACKTIP").toInt());
            ptrCon->setIedTaskType(query.value("IEDTASKTYPE").toString());
            ptrCon->setIedPhase(query.value("IEDPHASE").toString());
            ptrCon->setBayName(query.value("BAYNAME").toString());
            ptrCon->setItemName(query.value("ITEMNAME").toString());
            lst.append(ptrCon);
        }
    }
    if(ok)
        *ok = bSucc;
    return lst;
}

TransientSwitchTaskConclusionRecord::List DBTransientSwitchConclusionRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    TransientSwitchTaskConclusionRecord::List lst_act;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->ackTip() != -1)
        {
             if(!ptr->iedName().isEmpty())
             {
                  if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                      sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND ACKTIP=%2 ORDER BY GUID DESC LIMIT %3, %4")
                               .arg(ptr->iedName())
                               .arg(ptr->ackTip())
                               .arg(ptr->startCount())
                               .arg(ptr->recordCount());
                    else
                      sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') AND ACKTIP=%2 ORDER BY GUID DESC")
                               .arg(ptr->iedName())
                               .arg(ptr->ackTip());
             }
             else
             {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord WHERE ACKTIP=%1 ORDER BY GUID DESC")
                                    .arg(ptr->ackTip());
             }
        }else{
             if(ptr->iedName() != "")
             {
                 if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                     sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord WHERE (IEDNAME='%1' OR IEDNAMECOMP='%1') ORDER BY GUID DESC LIMIT %2, %3")
                                .arg(ptr->iedName())
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                  else
                     sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord WHERE IEDNAME='%1' OR IEDNAMECOMP='%1' ORDER BY GUID DESC")
                                .arg(ptr->iedName());
             }
             else
             {
                  if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord ORDER BY GUID DESC LIMIT %1, %2")
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                  else
                        sql = QObject::tr("SELECT * FROM transientswitchtaskconclusionrecord ORDER BY GUID DESC");
             }
        }
        if(sql != "")
        {
            bSucc1 = query.exec(sql);
            if (bSucc1)
            {
                while (query.next())
                {
                    TransientSwitchTaskConclusionRecord::Ptr ptrCon(new TransientSwitchTaskConclusionRecord());
                    ptrCon->setGUID(query.value("GUID").toInt());
                    ptrCon->setIedName(query.value("IEDNAME").toString());
                    ptrCon->setSetType(query.value("SETTYPE").toString());
                    ptrCon->setIedNameComp(query.value("IEDNAMECOMP").toString());
                    ptrCon->setSetTypeComp(query.value("SETTYPECOMP").toString());
                    ptrCon->setRecloseAckDelay(query.value("RECLOSEACKDELAY").toString());
                    ptrCon->setBreakerAckDelay(query.value("BREAKERACKDELAY").toString());
                    ptrCon->setFaultZeroTime(query.value("FAULTZEROTIME").toString());
                    ptrCon->setSrIedAFileName(query.value("SRIEDAFILENAME").toString());
                    ptrCon->setSrIedBFileName(query.value("SRIEDBFILENAME").toString());
                    ptrCon->setTaskFileName(query.value("TASKFILENAME").toString());
                    ptrCon->setStandardFileName(query.value("STANDARDFILENAME").toString());
                    ptrCon->setChannelType(query.value("CHANNELTYPE").toString());
                    ptrCon->setConclusion(query.value("CONCLUSION").toString());
                    ptrCon->setRecloseConclusion(query.value("RECLOSECONCLUSION").toFloat());
                    ptrCon->setBreakerConclusion(query.value("BREAKERCONCLUSION").toFloat());
                    ptrCon->setReclosingInnormalTime(query.value("RECLOSINGINNORMALTIME").toString());
                    ptrCon->setReclosingSeriousTime(query.value("RECLOSINGSERIOUSTIME").toString());
                    ptrCon->setBreakerInnormalTime(query.value("BREAKERINNORMALTIME").toString());
                    ptrCon->setBreakerSeriousTime(query.value("BREAKERSERIOUSTIME").toString());
                    ptrCon->setReclosingResult(query.value("RECLOSINGRESULT").toInt());
                    ptrCon->setBreakerResult(query.value("BREAKERRESULT").toInt());
                    ptrCon->setTaskChannelRef(query.value("TASKCHANNELREF").toInt());
                    ptrCon->setTaskChannelDesc(query.value("TASKCHANNELDESC").toString());
                    ptrCon->setStandChannelRef(query.value("STANDARDCHANNELREF").toInt());
                    ptrCon->setStandChannelDesc(query.value("STANDARDCHANNELDESC").toString());
                    ptrCon->setRecordTime(query.value("RECORDTIME").toString());
                    ptrCon->setAckTip(query.value("ACKTIP").toInt());
                    ptrCon->setIedTaskType(query.value("IEDTASKTYPE").toString());
                    ptrCon->setIedPhase(query.value("IEDPHASE").toString());
                    ptrCon->setBayName(query.value("BAYNAME").toString());
                    ptrCon->setItemName(query.value("ITEMNAME").toString());
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

TransientSwitchTaskConclusionRecord::List DBTransientSwitchConclusionRecordDAO::doQuery(DBOrmOperation::List &lst, bool *ok)
{
    QSharedPointer<TransientSwitchTaskConclusionRecordORM> ormInst = qSharedPointerDynamicCast<TransientSwitchTaskConclusionRecordORM>(m_ptrOrm);
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    TransientSwitchTaskConclusionRecord::List lst_act;
    if (db.isOpen() || db.open())
    {
        QString sql = "";
        QSqlQuery query(db);

        if(!lst.isEmpty())
        {
            sql = "SELECT * FROM transienttaskconclusionrecord WHERE";
            for(int i=0; i<lst.size(); i++)
            {
                DBOrmOperation::Ptr ptrOp = lst[i];
                if(ptrOp)
                {
                    QHash<int, DBCondition> varColumnInfo = ormInst->columnInfo();
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
                TransientSwitchTaskConclusionRecord::Ptr ptrCon(new TransientSwitchTaskConclusionRecord());
                ptrCon->setGUID(query.value("GUID").toInt());
                ptrCon->setIedName(query.value("IEDNAME").toString());
                ptrCon->setSetType(query.value("SETTYPE").toString());
                ptrCon->setIedNameComp(query.value("IEDNAMECOMP").toString());
                ptrCon->setSetTypeComp(query.value("SETTYPECOMP").toString());
                ptrCon->setRecloseAckDelay(query.value("RECLOSEACKDELAY").toString());
                ptrCon->setBreakerAckDelay(query.value("BREAKERACKDELAY").toString());
                ptrCon->setFaultZeroTime(query.value("FAULTZEROTIME").toString());
                ptrCon->setSrIedAFileName(query.value("SRIEDAFILENAME").toString());
                ptrCon->setSrIedBFileName(query.value("SRIEDBFILENAME").toString());
                ptrCon->setTaskFileName(query.value("TASKFILENAME").toString());
                ptrCon->setStandardFileName(query.value("STANDARDFILENAME").toString());
                ptrCon->setChannelType(query.value("CHANNELTYPE").toString());
                ptrCon->setConclusion(query.value("CONCLUSION").toString());
                ptrCon->setRecloseConclusion(query.value("RECLOSECONCLUSION").toFloat());
                ptrCon->setBreakerConclusion(query.value("BREAKERCONCLUSION").toFloat());
                ptrCon->setReclosingInnormalTime(query.value("RECLOSINGINNORMALTIME").toString());
                ptrCon->setReclosingSeriousTime(query.value("RECLOSINGSERIOUSTIME").toString());
                ptrCon->setBreakerInnormalTime(query.value("BREAKERINNORMALTIME").toString());
                ptrCon->setBreakerSeriousTime(query.value("BREAKERSERIOUSTIME").toString());
                ptrCon->setReclosingResult(query.value("RECLOSINGRESULT").toInt());
                ptrCon->setBreakerResult(query.value("BREAKERRESULT").toInt());
                ptrCon->setTaskChannelRef(query.value("TASKCHANNELREF").toInt());
                ptrCon->setTaskChannelDesc(query.value("TASKCHANNELDESC").toString());
                ptrCon->setStandChannelRef(query.value("STANDARDCHANNELREF").toInt());
                ptrCon->setStandChannelDesc(query.value("STANDARDCHANNELDESC").toString());
                ptrCon->setRecordTime(query.value("RECORDTIME").toString());
                ptrCon->setAckTip(query.value("ACKTIP").toInt());
                ptrCon->setIedTaskType(query.value("IEDTASKTYPE").toString());
                ptrCon->setIedPhase(query.value("IEDPHASE").toString());
                ptrCon->setBayName(query.value("BAYNAME").toString());
                ptrCon->setItemName(query.value("ITEMNAME").toString());
                lst_act.append(ptrCon);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst_act;
}

bool DBTransientSwitchConclusionRecordDAO::doInsert(const TransientSwitchTaskConclusionRecord::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = QObject::tr("INSERT INTO transientswitchtaskconclusionrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', %14, %15, '%16', '%17', '%18', '%19', %20, %21, %22, '%23', %24, '%25', '%26', %27, '%28', '%29', '%30', '%31')")
                .arg(ptr->iedName())                //1
                .arg(ptr->setType())                //2
                .arg(ptr->iedNameComp())            //3
                .arg(ptr->setTypeComp())            //4
                .arg(ptr->recloseAckDelay())        //5
                .arg(ptr->breakerAckDelay())        //6
                .arg(ptr->faultZeroTime())          //7
                .arg(ptr->srIedAFileName())         //8
                .arg(ptr->srIedBFileName())         //9
                .arg(ptr->taskFileName())           //10
                .arg(ptr->standardFileName())       //11
                .arg(ptr->channelType())            //12
                .arg(ptr->conclusion())             //13
                .arg(ptr->recloseConclusion())		//14
                .arg(ptr->breakerConclusion())		//15
                .arg(ptr->reclosingInnormalTime())  //16
                .arg(ptr->reclosingSeriousTime())   //17
                .arg(ptr->breakerInnormalTime())    //18
                .arg(ptr->breakerSeriousTime())     //19
                .arg(ptr->breakerResult())          //20
                .arg(ptr->reclosingResult())        //21
                .arg(ptr->taskChannelRef())         //22
                .arg(ptr->taskChannelDesc())        //23
                .arg(ptr->standardChannelRef())     //24
                .arg(ptr->standardChannelDesc())    //25
                .arg(ptr->recordTime())             //26
                .arg(ptr->ackTip())                 //27
                .arg(ptr->iedTaskType())            //28
                .arg(ptr->iedPhase())               //29
                .arg(ptr->bayName())                //30
                .arg(ptr->itemName());              //31
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

bool DBTransientSwitchConclusionRecordDAO::doInsert(QSqlDatabase db, const TransientSwitchTaskConclusionRecord::Ptr &ptr)
{
    bool bSucc = false;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = QObject::tr("INSERT INTO transientswitchtaskconclusionrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', %14, %15, '%16', '%17', '%18', '%19', %20, %21, %22, '%23', %24, '%25', '%26', %27, '%28', '%29', '%30', '%31')")
                .arg(ptr->iedName())                //1
                .arg(ptr->setType())                //2
                .arg(ptr->iedNameComp())            //3
                .arg(ptr->setTypeComp())            //4
                .arg(ptr->recloseAckDelay())        //5
                .arg(ptr->breakerAckDelay())        //6
                .arg(ptr->faultZeroTime())          //7
                .arg(ptr->srIedAFileName())         //8
                .arg(ptr->srIedBFileName())         //9
                .arg(ptr->taskFileName())           //10
                .arg(ptr->standardFileName())       //11
                .arg(ptr->channelType())            //12
                .arg(ptr->conclusion())             //13
                .arg(ptr->recloseConclusion())		//14
                .arg(ptr->breakerConclusion())		//15
                .arg(ptr->reclosingInnormalTime())  //16
                .arg(ptr->reclosingSeriousTime())   //17
                .arg(ptr->breakerInnormalTime())    //18
                .arg(ptr->breakerSeriousTime())     //19
                .arg(ptr->breakerResult())          //20
                .arg(ptr->reclosingResult())        //21
                .arg(ptr->taskChannelRef())         //22
                .arg(ptr->taskChannelDesc())        //23
                .arg(ptr->standardChannelRef())     //24
                .arg(ptr->standardChannelDesc())    //25
                .arg(ptr->recordTime())             //26
                .arg(ptr->ackTip())                 //27
                .arg(ptr->iedTaskType())            //28
                .arg(ptr->iedPhase())               //29
                .arg(ptr->bayName())                //30
                .arg(ptr->itemName());              //31
    query.exec(sql);
    bSucc = query.exec("COMMIT");
    if (!bSucc)
    {
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }

    return bSucc;
}

bool DBTransientSwitchConclusionRecordDAO::doInsert(TransientSwitchTaskConclusionRecord::List &lst)
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
        TransientSwitchTaskConclusionRecord::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            TransientSwitchTaskConclusionRecord::Ptr ptr(new TransientSwitchTaskConclusionRecord());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO transientswitchtaskconclusionrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', %14, %15, '%16', '%17', '%18', '%19', %20, %21, %22, '%23', %24, '%25', '%26', %27, '%28', '%29', '%30', '%31')")
                .arg(ptr->iedName())                //1
                .arg(ptr->setType())                //2
                .arg(ptr->iedNameComp())            //3
                .arg(ptr->setTypeComp())            //4
                .arg(ptr->recloseAckDelay())        //5
                .arg(ptr->breakerAckDelay())        //6
                .arg(ptr->faultZeroTime())          //7
                .arg(ptr->srIedAFileName())         //8
                .arg(ptr->srIedBFileName())         //9
                .arg(ptr->taskFileName())           //10
                .arg(ptr->standardFileName())       //11
                .arg(ptr->channelType())            //12
                .arg(ptr->conclusion())             //13
                .arg(ptr->recloseConclusion())		//14
                .arg(ptr->breakerConclusion())		//15
                .arg(ptr->reclosingInnormalTime())  //16
                .arg(ptr->reclosingSeriousTime())   //17
                .arg(ptr->breakerInnormalTime())    //18
                .arg(ptr->breakerSeriousTime())     //19
                .arg(ptr->breakerResult())          //20
                .arg(ptr->reclosingResult())        //21
                .arg(ptr->taskChannelRef())         //22
                .arg(ptr->taskChannelDesc())        //23
                .arg(ptr->standardChannelRef())     //24
                .arg(ptr->standardChannelDesc())    //25
                .arg(ptr->recordTime())             //26
                .arg(ptr->ackTip())                 //27
                .arg(ptr->iedTaskType())            //28
                .arg(ptr->iedPhase())               //29
                .arg(ptr->bayName())                //30
                .arg(ptr->itemName());              //31
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

bool DBTransientSwitchConclusionRecordDAO::doInsert(QSqlDatabase db, const TransientSwitchTaskConclusionRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    TransientSwitchTaskConclusionRecord::List::const_iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        TransientSwitchTaskConclusionRecord::Ptr ptr(new TransientSwitchTaskConclusionRecord());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO transientswitchtaskconclusionrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', %14, %15, '%16', '%17', '%18', '%19', %20, %21, %22, '%23', %24, '%25', '%26', %27, '%28', '%29', '%30', '%31')")
                .arg(ptr->iedName())                //1
                .arg(ptr->setType())                //2
                .arg(ptr->iedNameComp())            //3
                .arg(ptr->setTypeComp())            //4
                .arg(ptr->recloseAckDelay())        //5
                .arg(ptr->breakerAckDelay())        //6
                .arg(ptr->faultZeroTime())          //7
                .arg(ptr->srIedAFileName())         //8
                .arg(ptr->srIedBFileName())         //9
                .arg(ptr->taskFileName())           //10
                .arg(ptr->standardFileName())       //11
                .arg(ptr->channelType())            //12
                .arg(ptr->conclusion())             //13
                .arg(ptr->recloseConclusion())		//14
                .arg(ptr->breakerConclusion())		//15
                .arg(ptr->reclosingInnormalTime())  //16
                .arg(ptr->reclosingSeriousTime())   //17
                .arg(ptr->breakerInnormalTime())    //18
                .arg(ptr->breakerSeriousTime())     //19
                .arg(ptr->breakerResult())          //20
                .arg(ptr->reclosingResult())        //21
                .arg(ptr->taskChannelRef())         //22
                .arg(ptr->taskChannelDesc())        //23
                .arg(ptr->standardChannelRef())     //24
                .arg(ptr->standardChannelDesc())    //25
                .arg(ptr->recordTime())             //26
                .arg(ptr->ackTip())                 //27
                .arg(ptr->iedTaskType())            //28
                .arg(ptr->iedPhase())               //29
                .arg(ptr->bayName())                //30
                .arg(ptr->itemName());              //31
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

bool DBTransientSwitchConclusionRecordDAO::doUpdate(const TransientSwitchTaskConclusionRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    TransientSwitchTaskConclusionRecord::List::const_iterator iter = lst.begin();
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        while(iter < lst.end())
        {
            TransientSwitchTaskConclusionRecord::Ptr ptr(new TransientSwitchTaskConclusionRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE transientswitchtaskconclusionrecord SET RECORDTIME='%1' WHERE GUID=%2")
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

bool DBTransientSwitchConclusionRecordDAO::ackRecord(TransientSwitchTaskConclusionRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    TransientSwitchTaskConclusionRecord::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            TransientSwitchTaskConclusionRecord::Ptr ptr(new TransientSwitchTaskConclusionRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE transientswitchtaskconclusionrecord SET ACKTIP=%1 WHERE GUID=%2")
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

bool DBTransientSwitchConclusionRecordDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS transientswitchtaskconclusionrecord("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "SETTYPE VARCHAR(255) NOT NULL,"
                                  "IEDNAMECOMP VARCHAR(255) NOT NULL,"
                                  "SETTYPECOMP VARCHAR(255) NOT NULL,"
                                  "RECLOSEACKDELAY VARCHAR(255) NOT NULL,"
                                  "BREAKERACKDELAY VARCHAR(255) NOT NULL,"
                                  "FAULTZEROTIME VARCHAR(255) NOT NULL,"
                                  "SRIEDAFILENAME VARCHAR(255) NOT NULL,"
                                  "SRIEDBFILENAME VARCHAR(255) NOT NULL,"
                                  "TASKFILENAME VARCHAR(255) NOT NULL,"
                                  "STANDARDFILENAME VARCHAR(255) NOT NULL,"
                                  "CHANNELTYPE VARCHAR(255) NOT NULL,"
                                  "CONCLUSION VARCHAR(255) NOT NULL,"
                                  "RECLOSECONCLUSION FLOAT(10,6) NOT NULL,"
                                  "BREAKERCONCLUSION FLOAT(10,6) NOT NULL,"
                                  "RECLOSINGINNORMALTIME VARCHAR(255) NOT NULL,"
                                  "RECLOSINGSERIOUSTIME VARCHAR(255) NOT NULL,"
                                  "BREAKERINNORMALTIME VARCHAR(255) NOT NULL,"
                                  "BREAKERSERIOUSTIME VARCHAR(255) NOT NULL,"
                                  "BREAKERRESULT INT(11) NOT NULL,"
                                  "RECLOSINGRESULT INT(11) NOT NULL,"
                                  "TASKCHANNELREF INT(11) NOT NULL,"
                                  "TASKCHANNELDESC VARCHAR(255) NOT NULL,"
                                  "STANDARDCHANNELREF INT(11) NOT NULL,"
                                  "STANDARDCHANNELDESC VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "ACKTIP INT(11) NOT NULL DEFAULT 0,"
                                  "IEDTASKTYPE VARCHAR(255) NOT NULL DEFAULT '',"
                                  "IEDPHASE VARCHAR(255) NOT NULL DEFAULT '',"
                                  "BAYNAME VARCHAR(255) NOT NULL DEFAULT '',"
                                  "ITEMNAME VARCHAR(255) NOT NULL DEFAULT '',"
                                  "PRIMARY KEY(GUID))"
                                  "ENGINE=InnoDB DEFAULT charset=UTF8");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
