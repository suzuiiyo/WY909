#include <QObject>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbsteadytasktsrecorddao.h"
DBSteadyTaskTSRecordDAO::DBSteadyTaskTSRecordDAO()
    : m_connectionName("connectSteadyTS")
{

}

DBSteadyTaskTSRecordDAO::~DBSteadyTaskTSRecordDAO()
{

}

int DBSteadyTaskTSRecordDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    int count = 0;
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
                    sql = QObject::tr("SELECT count(*) as ct FROM steadytasktsrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM steadytasktsrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM steadytasktsrecord WHERE IEDNAME='%1' AND ACKTIP=%2")
                            .arg(ptr->iedName())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM steadytasktsrecord WHERE ACKTIP=%1")
                            .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM steadytasktsrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3'")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM steadytasktsrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2'")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM steadytasktsrecord WHERE IEDNAME='%1'")
                            .arg(ptr->iedName());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM steadytasktsrecord");
            }
        }
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                count = query.value("ct").toInt();
                db.close();
                if(ok)
                    *ok = bSucc;
                return count;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return count;
}

SteadyTaskTSRecord::List DBSteadyTaskTSRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    SteadyTaskTSRecord::List lstRecord;
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
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC LIMIT %5, %6")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC")
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
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->iedName())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC")
                                .arg(ptr->iedName())
                                .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE ACKTIP=%1 ORDER BY GUID DESC")
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
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
            }
            else
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE IEDNAME='%1' ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord WHERE IEDNAME='%1' ORDER BY GUID DESC")
                                .arg(ptr->iedName());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord ORDER BY GUID DESC LIMIT %1, %2")
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM steadytasktsrecord ORDER BY GUID DESC");
                }
            }
        }

        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                SteadyTaskTSRecord::Ptr ptrRecod(new SteadyTaskTSRecord());
                ptrRecod->m_GUID = query.value("GUID").toInt();
                ptrRecod->m_iedName = query.value("IEDNAME").toString();
                ptrRecod->m_dataRef = query.value("DATAREF").toString();
                ptrRecod->m_dataDesc = query.value("DATADESC").toString();
                ptrRecod->m_dataType1 = query.value("DATATYPE1").toInt();
                ptrRecod->m_dataValue1 = query.value("DATAVALUE1").toString();
                ptrRecod->m_dataType2 = query.value("DATATYPE2").toInt();
                ptrRecod->m_dataValue2 = query.value("DATAVALUE2").toString();
                ptrRecod->m_quality = query.value("QUALITY").toString();
                ptrRecod->m_recordTime = query.value("RECORDTIME").toString();
                ptrRecod->m_scope = query.value("SCOPE").toString();
                ptrRecod->m_ackTip = query.value("ACKTIP").toInt();
                lstRecord.append(ptrRecod);
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return lstRecord;
}

bool DBSteadyTaskTSRecordDAO::ackRecord(SteadyTaskTSRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    SteadyTaskTSRecord::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            SteadyTaskTSRecord::Ptr ptr(new SteadyTaskTSRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE steadytasktsrecord SET ACKTIP=%1 WHERE GUID=%2")
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

