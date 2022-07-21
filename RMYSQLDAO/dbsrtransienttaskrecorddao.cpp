#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbsrtransienttaskrecorddao.h"
DBSRTransientTaskRecordDAO::DBSRTransientTaskRecordDAO()
    : m_connectionName("connectSRTTRecord")
{

}

DBSRTransientTaskRecordDAO::~DBSRTransientTaskRecordDAO()
{

}

int DBSRTransientTaskRecordDAO::countRecord(bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM srtransienttaskrecord ORDER BY GUID DESC LIMIT 1");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                count = query.value("GUID").toInt();
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

int DBSRTransientTaskRecordDAO::countRecord(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM srtransienttaskrecord ORDER BY GUID DESC LIMIT 1");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while (query.next())
        {
            count = query.value("GUID").toInt();
            if(ok)
                *ok = bSucc;
            return count;
        }
    }
    if(ok)
        *ok = bSucc;

    return count;
}

SRTransientTaskRecord::List DBSRTransientTaskRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    SRTransientTaskRecord::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        int startCount = ptr->startCount();
        int recordCount = ptr->recordCount();
        if(recordCount != 0)
            sql = QObject::tr("SELECT * FROM srtransienttaskrecord ORDER BY GUID DESC LIMIT %1,%2")
                    .arg(startCount)
                    .arg(recordCount);
        else
            sql = QObject::tr("SELECT * FROM srtransienttaskrecord");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                SRTransientTaskRecord::Ptr ptrSR(new SRTransientTaskRecord());
                ptrSR->m_GUID = query.value("GUID").toInt();
                ptrSR->m_iedAFileName = query.value("IEDAFILENAME").toString();
                ptrSR->m_iedBFileName = query.value("IEDBFILENAME").toString();
                ptrSR->m_tmDataType = query.value("TMDATATYPE").toInt();
                ptrSR->m_tmDataValue = query.value("TMDATAVALUE").toFloat();
                ptrSR->m_tmThreshold = query.value("TMTHRESHOLD").toFloat();
                lst.append(ptrSR);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SRTransientTaskRecord::List DBSRTransientTaskRecordDAO::doQuery(QSqlDatabase db, const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    SRTransientTaskRecord::List lst;
    QSqlQuery query(db);
    QString sql = "";
    int startCount = ptr->startCount();
    int recordCount = ptr->recordCount();
    if(recordCount != 0)
        sql = QObject::tr("SELECT * FROM srtransienttaskrecord ORDER BY GUID DESC LIMIT %1,%2")
                .arg(startCount)
                .arg(recordCount);
    else
        sql = QObject::tr("SELECT * FROM srtransienttaskrecord");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while (query.next())
        {
            SRTransientTaskRecord::Ptr ptrSR(new SRTransientTaskRecord());
            ptrSR->m_GUID = query.value("GUID").toInt();
            ptrSR->m_iedAFileName = query.value("IEDAFILENAME").toString();
            ptrSR->m_iedBFileName = query.value("IEDBFILENAME").toString();
            ptrSR->m_tmDataType = query.value("TMDATATYPE").toInt();
            ptrSR->m_tmDataValue = query.value("TMDATAVALUE").toFloat();
            ptrSR->m_tmThreshold = query.value("TMTHRESHOLD").toFloat();
            lst.append(ptrSR);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBSRTransientTaskRecordDAO::doInsert(SRTransientTaskRecord::List &lst)
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
        SRTransientTaskRecord::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            SRTransientTaskRecord::Ptr ptr(new SRTransientTaskRecord());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO srtransienttaskrecord VALUES(NULL, '%1', '%2', %3, %4, %5)")
                    .arg(ptr->iedAFileName())
                    .arg(ptr->iedBFileName())
                    .arg(ptr->tmDataType())
                    .arg(ptr->tmDataValue())
                    .arg(ptr->tmThreshold());
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

bool DBSRTransientTaskRecordDAO::doInsert(QSqlDatabase db, SRTransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    SRTransientTaskRecord::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        SRTransientTaskRecord::Ptr ptr(new SRTransientTaskRecord());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO srtransienttaskrecord VALUES(NULL, '%1', '%2', %3, %4, %5)")
                .arg(ptr->iedAFileName())
                .arg(ptr->iedBFileName())
                .arg(ptr->tmDataType())
                .arg(ptr->tmDataValue())
                .arg(ptr->tmThreshold());
        if (!query.exec(sql))
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
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

    return bSucc;
}

bool DBSRTransientTaskRecordDAO::doUpdate(SRTransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    SRTransientTaskRecord::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        while(iter < lst.end())
        {
            SRTransientTaskRecord::Ptr ptr(new SRTransientTaskRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE srtransienttaskrecord SET IEDAFILENAME='%1', IEDBFILENAME='%2', TMDATATYPE=%3, TMDATAVALUE=%4, TMTHRESHOLD=%5 WHERE GUID=%6")
                    .arg(ptr->iedAFileName())//1
                    .arg(ptr->iedBFileName())//2
                    .arg(ptr->tmDataType())//3
                    .arg(ptr->tmDataValue())//4
                    .arg(ptr->tmThreshold())//5
                    .arg(ptr->GUID());//6
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

bool DBSRTransientTaskRecordDAO::doUpdate(QSqlDatabase db, SRTransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    SRTransientTaskRecord::List::iterator iter = lst.begin();
    QSqlQuery query(db);
    query.exec("START TRANSACTION");

    while(iter < lst.end())
    {
        SRTransientTaskRecord::Ptr ptr(new SRTransientTaskRecord());
        ptr = *iter;

        QString sql = QObject::tr("UPDATE srtransienttaskrecord SET IEDAFILENAME='%1', IEDBFILENAME='%2', TMDATATYPE=%3, TMDATAVALUE=%4, TMTHRESHOLD=%5 WHERE GUID=%6")
                .arg(ptr->iedAFileName())//1
                .arg(ptr->iedBFileName())//2
                .arg(ptr->tmDataType())//3
                .arg(ptr->tmDataValue())//4
                .arg(ptr->tmThreshold())//5
                .arg(ptr->GUID());//6
        if(!query.exec(sql))
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
            return bSucc;
        }
        iter++;
    }
    bSucc = query.exec("COMMIT");
    if(!bSucc){
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }

    return bSucc;
}
