#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbprottransienttaskrecorddao.h"
DBProtTransientTaskRecordDAO::DBProtTransientTaskRecordDAO()
    : m_connectionName("connectProtTTRecord")
{

}

DBProtTransientTaskRecordDAO::~DBProtTransientTaskRecordDAO()
{

}

int DBProtTransientTaskRecordDAO::countRecord(bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM prottransienttaskrecord ORDER BY GUID DESC LIMIT 1");
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

int DBProtTransientTaskRecordDAO::countRecord(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM prottransienttaskrecord ORDER BY GUID DESC LIMIT 1");
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

ProtTransientTaskRecord::List DBProtTransientTaskRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    ProtTransientTaskRecord::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        int startCount = ptr->startCount();
        int recordCount = ptr->recordCount();
        if(recordCount != 0)
            sql = QObject::tr("SELECT * FROM prottransienttaskrecord ORDER BY GUID DESC LIMIT %1,%2")
                    .arg(startCount)
                    .arg(recordCount);
        else
            sql = QObject::tr("SELECT * FROM prottransienttaskrecord");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                ProtTransientTaskRecord::Ptr ptrProt(new ProtTransientTaskRecord());
                ptrProt->m_GUID = query.value("GUID").toInt();
                ptrProt->m_startTime = query.value("STARTTIME").toString();
                ptrProt->m_startResetTime = query.value("STARTRESETTIME").toString();
                ptrProt->m_faultNum = query.value("FAULTNUM").toInt();
                ptrProt->m_faultValue = query.value("FAULTVALUE").toFloat();
                lst.append(ptrProt);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

ProtTransientTaskRecord::List DBProtTransientTaskRecordDAO::doQuery(QSqlDatabase db, const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    ProtTransientTaskRecord::List lst;
    QSqlQuery query(db);
    QString sql = "";
    int startCount = ptr->startCount();
    int recordCount = ptr->recordCount();
    if(recordCount != 0)
        sql = QObject::tr("SELECT * FROM prottransienttaskrecord ORDER BY GUID DESC LIMIT %1,%2")
                .arg(startCount)
                .arg(recordCount);
    else
        sql = QObject::tr("SELECT * FROM prottransienttaskrecord");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while (query.next())
        {
            ProtTransientTaskRecord::Ptr ptrProt(new ProtTransientTaskRecord());
            ptrProt->m_GUID = query.value("GUID").toInt();
            ptrProt->m_startTime = query.value("STARTTIME").toString();
            ptrProt->m_startResetTime = query.value("STARTRESETTIME").toString();
            ptrProt->m_faultNum = query.value("FAULTNUM").toInt();
            ptrProt->m_faultValue = query.value("FAULTVALUE").toFloat();
            lst.append(ptrProt);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBProtTransientTaskRecordDAO::doInsert(ProtTransientTaskRecord::List &lst)
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
        ProtTransientTaskRecord::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            ProtTransientTaskRecord::Ptr ptr(new ProtTransientTaskRecord());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO prottransienttaskrecord VALUES(NULL, '%1', '%2', %3, %4)")
                    .arg(ptr->startTime())
                    .arg(ptr->startResetTime())
                    .arg(ptr->faultNum())
                    .arg(ptr->faultValue());
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

bool DBProtTransientTaskRecordDAO::doInsert(QSqlDatabase db, ProtTransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    ProtTransientTaskRecord::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        ProtTransientTaskRecord::Ptr ptr(new ProtTransientTaskRecord());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO prottransienttaskrecord VALUES(NULL, '%1', '%2', %3, %4)")
                .arg(ptr->startTime())
                .arg(ptr->startResetTime())
                .arg(ptr->faultNum())
                .arg(ptr->faultValue());
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

bool DBProtTransientTaskRecordDAO::doUpdate(ProtTransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    ProtTransientTaskRecord::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        while(iter < lst.end())
        {
            ProtTransientTaskRecord::Ptr ptr(new ProtTransientTaskRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE prottransienttaskrecord SET STARTTIME='%1', STARTRESETTIME='%2', FAULTNUM=%3, FAULTVALUE=%4 WHERE GUID=%5")
                    .arg(ptr->startTime())      //1
                    .arg(ptr->startResetTime()) //2
                    .arg(ptr->faultNum())       //3
                    .arg(ptr->faultValue())     //4
                    .arg(ptr->GUID());          //5
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

bool DBProtTransientTaskRecordDAO::doUpdate(QSqlDatabase db, ProtTransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    ProtTransientTaskRecord::List::iterator iter = lst.begin();
    QSqlQuery query(db);
    query.exec("START TRANSACTION");

    while(iter < lst.end())
    {
        ProtTransientTaskRecord::Ptr ptr(new ProtTransientTaskRecord());
        ptr = *iter;

        QString sql = QObject::tr("UPDATE prottransienttaskrecord SET STARTTIME='%1', STARTRESETTIME='%2', FAULTNUM=%3, FAULTVALUE=%4 WHERE GUID=%5")
                .arg(ptr->startTime())      //1
                .arg(ptr->startResetTime()) //2
                .arg(ptr->faultNum())       //3
                .arg(ptr->faultValue())     //4
                .arg(ptr->GUID());          //5
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
