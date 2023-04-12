#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbcrcfiletaskrecorddao.h"
DBCRCFileTaskRecordDAO::DBCRCFileTaskRecordDAO()
    : m_connectionName("connectCRCFileTaskRecord")
{

}

DBCRCFileTaskRecordDAO::~DBCRCFileTaskRecordDAO()
{

}

int DBCRCFileTaskRecordDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
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
                    sql = QObject::tr("SELECT count(*) as ct FROM crcfiletaskrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM crcfiletaskrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM crcfiletaskrecord WHERE IEDNAME='%1' AND ACKTIP=%2")
                            .arg(ptr->iedName())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM crcfiletaskrecord WHERE ACKTIP=%1")
                            .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM crcfiletaskrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3'")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM crcfiletaskrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2'")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM crcfiletaskrecord WHERE IEDNAME='%1'")
                            .arg(ptr->iedName());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM crcfiletaskrecord");
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

CRCFileTaskRecord::List DBCRCFileTaskRecordDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    CRCFileTaskRecord::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM crcfiletaskrecord");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                CRCFileTaskRecord::Ptr ptrRecord(new CRCFileTaskRecord());
                ptrRecord->m_GUID = query.value("GUID").toInt();
                ptrRecord->m_iedName = query.value("IEDNAME").toString();
                ptrRecord->m_recordTime = query.value("RECORDTIME").toString();
                ptrRecord->m_taskType = query.value("TASKTYPE").toInt();
                ptrRecord->m_csCRC = query.value("CSCRC").toString();
                ptrRecord->m_fileCRC = query.value("FILECRC").toString();
                ptrRecord->m_virCRC = query.value("VIRCRC").toString();
                ptrRecord->m_recordType = query.value("RECORDTYPE").toInt();
                ptrRecord->m_ackTip = query.value("ACKTIP").toInt();
                lst.append(ptrRecord);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

CRCFileTaskRecord::List DBCRCFileTaskRecordDAO::doQuery(SearchCondition::List &lst, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    CRCFileTaskRecord::List lst_alarm;
    SearchCondition::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            SearchCondition::Ptr ptr(new SearchCondition());
            ptr = *iter;
            int startCount = ptr->startCount();
            int recordCount = ptr->recordCount();
            QString iedName = ptr->iedName();
            if(iedName != "" && startCount > 0 && recordCount > 0)
                sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC LIMIT %4,%5")
                        .arg(iedName)
                        .arg(ptr->startTime())
                        .arg(ptr->endTime())
                        .arg(startCount)
                        .arg(recordCount);
            else
            {
                if(startCount > 0 && recordCount > 0)
                    sql = QObject::tr("SELECT * FROM crcfiletaskrecord ORDER BY GUID DESC LIMIT %1,%2")
                            .arg(startCount)
                            .arg(recordCount);
                else
                    sql = QObject::tr("SELECT * FROM crcfiletaskrecord");
            }
            bSucc1 = query.exec(sql);
            if (bSucc1)
            {
                while (query.next())
                {
                    CRCFileTaskRecord::Ptr ptrRecord(new CRCFileTaskRecord());
                    ptrRecord->m_GUID = query.value("GUID").toInt();
                    ptrRecord->m_iedName = query.value("IEDNAME").toString();
                    ptrRecord->m_recordTime = query.value("RECORDTIME").toString();
                    ptrRecord->m_taskType = query.value("TASKTYPE").toInt();
                    ptrRecord->m_csCRC = query.value("CSCRC").toString();
                    ptrRecord->m_fileCRC = query.value("FILECRC").toString();
                    ptrRecord->m_virCRC = query.value("VIRCRC").toString();
                    ptrRecord->m_recordType = query.value("RECORDTYPE").toInt();
                    ptrRecord->m_ackTip = query.value("ACKTIP").toInt();
                    lst_alarm.append(ptrRecord);
                }
            }
            else
                bSucc2 = bSucc1;
        }
        db.close();
    }
    if(ok)
        *ok = bSucc2;

    return lst_alarm;
}

CRCFileTaskRecord::Ptr DBCRCFileTaskRecordDAO::doQueryDevNewest(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' ORDER BY GUID DESC LIMIT 1")
                .arg(iedName);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                CRCFileTaskRecord::Ptr ptrRecord(new CRCFileTaskRecord());
                ptrRecord->m_GUID = query.value("GUID").toInt();
                ptrRecord->m_iedName = query.value("IEDNAME").toString();
                ptrRecord->m_recordTime = query.value("RECORDTIME").toString();
                ptrRecord->m_taskType = query.value("TASKTYPE").toInt();
                ptrRecord->m_csCRC = query.value("CSCRC").toString();
                ptrRecord->m_fileCRC = query.value("FILECRC").toString();
                ptrRecord->m_virCRC = query.value("VIRCRC").toString();
                ptrRecord->m_recordType = query.value("RECORDTYPE").toInt();
                ptrRecord->m_ackTip = query.value("ACKTIP").toInt();
                db.close();
                if(ok)
                    *ok = bSucc;
                return ptrRecord;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

CRCFileTaskRecord::List DBCRCFileTaskRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    CRCFileTaskRecord::List lst_act;
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
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC LIMIT %5, %6")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC")
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
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->iedName())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC")
                                .arg(ptr->iedName())
                                .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE ACKTIP=%1 ORDER BY GUID DESC")
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
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
            }
            else
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord WHERE IEDNAME='%1' ORDER BY GUID DESC")
                                .arg(ptr->iedName());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord ORDER BY GUID DESC LIMIT %1, %2")
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM crcfiletaskrecord ORDER BY GUID DESC");
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
                    CRCFileTaskRecord::Ptr ptrRecord(new CRCFileTaskRecord());
                    ptrRecord->m_GUID = query.value("GUID").toInt();
                    ptrRecord->m_iedName = query.value("IEDNAME").toString();
                    ptrRecord->m_recordTime = query.value("RECORDTIME").toString();
                    ptrRecord->m_taskType = query.value("TASKTYPE").toInt();
                    ptrRecord->m_csCRC = query.value("CSCRC").toString();
                    ptrRecord->m_fileCRC = query.value("FILECRC").toString();
                    ptrRecord->m_virCRC = query.value("VIRCRC").toString();
                    ptrRecord->m_recordType = query.value("RECORDTYPE").toInt();
                    ptrRecord->m_ackTip = query.value("ACKTIP").toInt();
                    lst_act.append(ptrRecord);
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

bool DBCRCFileTaskRecordDAO::doInsert(CRCFileTaskRecord::List &lst)
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
        CRCFileTaskRecord::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            CRCFileTaskRecord::Ptr ptr(new CRCFileTaskRecord());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO crcfiletaskrecord VALUES(NULL, '%1', '%2', %3, %4, '%5', '%6', %7, %8)")
                    .arg(ptr->iedName())        // 1
                    .arg(ptr->recordTime())     // 2
                    .arg(ptr->taskType())       // 3
                    .arg(ptr->csCRC())          // 4
                    .arg(ptr->fileCRC())        // 5
                    .arg(ptr->virCRC())         // 6
                    .arg(ptr->recordType())     // 7
                    .arg(ptr->ackTip());        // 8
            if (!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return false;
            }

            count++;
            if (count == 200)
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

bool DBCRCFileTaskRecordDAO::ackRecord(CRCFileTaskRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    CRCFileTaskRecord::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            CRCFileTaskRecord::Ptr ptr(new CRCFileTaskRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE crcfiletaskrecord SET ACKTIP=%1 WHERE GUID=%2")
                    .arg(ptr->ackTip())
                    .arg(ptr->GUID());                  //23
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

bool DBCRCFileTaskRecordDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS crcfiletaskrecord("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "TASKTYPE INT(11) NOT NULL DEFAULT -1"
                                  "CSCRC VARCHAR(255) NOT NULL,"
                                  "FILECRC VARCHAR(255) NOT NULL,"
                                  "VIRCRC VARCHAR(255) NOT NULL,"
                                  "RECORDTYPE INT(11) NOT NULL DEFAULT 0,"
                                  "ACKTIP INT(11) NOT NULL DEFAULT 0,"
                                  "PRIMARY KEY(GUID))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
