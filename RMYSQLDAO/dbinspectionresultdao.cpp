#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QVariant>
#include "dbconnectionreal.h"
#include "dbinspectionresultdao.h"
DBInspectionResultDAO::DBInspectionResultDAO()
    : m_connectionName("connectInspR")
{

}

DBInspectionResultDAO::~DBInspectionResultDAO()
{

}

InspectionResult::List DBInspectionResultDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    InspectionResult::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM inspectionresult");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                InspectionResult::Ptr ptrRecord(new InspectionResult());
                ptrRecord->m_iedName = query.value("IEDNAME").toString();
                ptrRecord->m_result = query.value("RESULT").toInt();
                ptrRecord->m_dbTime = query.value("DBTIME").toString();
                ptrRecord->m_nextTaskTime = query.value("NEXTTASKTIME").toString();
                ptrRecord->m_content = query.value("CONTENT").toString();
                ptrRecord->m_installTime = query.value("INSTALLTIME").toString();
                ptrRecord->m_deliveryTime = query.value("DELIVERYTIME").toString();
                lst.append(ptrRecord);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

InspectionResult::Ptr DBInspectionResultDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM inspectionresult WHERE IEDNAME='%1'")
                .arg(iedName);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                InspectionResult::Ptr ptrRecord(new InspectionResult());
                ptrRecord->m_iedName = query.value("IEDNAME").toString();
                ptrRecord->m_result = query.value("RESULT").toInt();
                ptrRecord->m_dbTime = query.value("DBTIME").toString();
                ptrRecord->m_nextTaskTime = query.value("NEXTTASKTIME").toString();
                ptrRecord->m_content = query.value("CONTENT").toString();
                ptrRecord->m_installTime = query.value("INSTALLTIME").toString();
                ptrRecord->m_deliveryTime = query.value("DELIVERYTIME").toString();
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

InspectionResult::List DBInspectionResultDAO::doQuery(int result, bool *ok)
{
    bool bSucc = false;
    InspectionResult::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM inspectionresult RESULT=%1")
                .arg(result);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                InspectionResult::Ptr ptrRecord(new InspectionResult());
                ptrRecord->m_iedName = query.value("IEDNAME").toString();
                ptrRecord->m_result = query.value("RESULT").toInt();
                ptrRecord->m_dbTime = query.value("DBTIME").toString();
                ptrRecord->m_nextTaskTime = query.value("NEXTTASKTIME").toString();
                ptrRecord->m_content = query.value("CONTENT").toString();
                ptrRecord->m_installTime = query.value("INSTALLTIME").toString();
                ptrRecord->m_deliveryTime = query.value("DELIVERYTIME").toString();
                lst.append(ptrRecord);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBInspectionResultDAO::doUpdate(InspectionResult::List &lst)
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
        InspectionResult::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            InspectionResult::Ptr ptr(new InspectionResult());
            ptr = *iter;
            sql = QObject::tr("UPDATE inspectionresult SET RESULT=%1, DBTIME='%2', NEXTTASKTIME='%3', CONTENT='%4', INSTALLTIME='%5', DELIVERYTIME='%6' WHERE IEDNAME='%7'")
                    .arg(ptr->result())         // 1
                    .arg(ptr->dbTime())         // 2
                    .arg(ptr->nextTaskTime())   // 3
                    .arg(ptr->content())        // 4
                    .arg(ptr->installTime())    // 5
                    .arg(ptr->deliveryTime());  // 6
            if (!query.exec(sql))
            {
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
        db.close();
    }

    return bSucc;
}

bool DBInspectionResultDAO::doInsert(InspectionResult::List &lst)
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
        InspectionResult::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            InspectionResult::Ptr ptr(new InspectionResult());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO inspectionresult(IEDNAME, RESULT, DBTIME, NEXTTASKTIME, CONTENT, INSTALLTIME, DELIVERYTIME) VALUES(NULL, '%1', %2, '%3', '%4', '%5', '%6', '%7')")
                    .arg(ptr->iedName())                //1
                    .arg(ptr->result())                 //2
                    .arg(ptr->dbTime())                 //3
                    .arg(ptr->nextTaskTime())           //4
                    .arg(ptr->content())                //5
                    .arg(ptr->installTime())            //6
                    .arg(ptr->deliveryTime());          //7
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

