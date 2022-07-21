#include <QObject>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dblogrecorddao.h"
DBLogRecordDAO::DBLogRecordDAO()
    : m_connectionName("connectLogs")
{

}

DBLogRecordDAO::~DBLogRecordDAO()
{

}

int DBLogRecordDAO::countRecord(const SearchCondition::Ptr &ptr, int logType, bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "file");
    if (db.isOpen() || db.open())
    {
        if(logType != LogRecord::Unknown)
        {
            QSqlQuery query(db);
            QString sql = "";
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(logType == LogRecord::Running)
                    sql = QObject::tr("SELECT count(*) as ct FROM runninglog WHERE RECORDTIME>='%1' AND RECORDTIME<='%2'")
                                        .arg(ptr->startTime())
                                        .arg(ptr->endTime());
                if(logType == LogRecord::Operation)
                    sql = QObject::tr("SELECT count(*) as ct FROM operationlog WHERE RECORDTIME>='%1' AND RECORDTIME<='%2'")
                                        .arg(ptr->startTime())
                                        .arg(ptr->endTime());
                if(logType == LogRecord::Maintain)
                    sql = QObject::tr("SELECT count(*) as ct FROM maintainlog WHERE RECORDTIME>='%1' AND RECORDTIME<='%2'")
                                        .arg(ptr->startTime())
                                        .arg(ptr->endTime());
            }
            else
            {
                if(logType == LogRecord::Running)
                    sql = QObject::tr("SELECT count(*) as ct FROM runninglog");
                if(logType == LogRecord::Operation)
                    sql = QObject::tr("SELECT count(*) as ct FROM operationlog");
                if(logType == LogRecord::Maintain)
                    sql = QObject::tr("SELECT count(*) as ct FROM maintainlog");
            }
            if(sql != "")
            {
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
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return count;
}

LogRecord::List DBLogRecordDAO::doQuery(const SearchCondition::Ptr &ptr, int logType, bool *ok)
{
    bool bSucc = false;
    LogRecord::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "file");
    if (db.isOpen() || db.open())
    {
        if(logType != LogRecord::Unknown)
        {
            QSqlQuery query(db);
            QString sql = "";
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                {
                    if(logType == LogRecord::Running)
                        sql = QObject::tr("SELECT * FROM runninglog WHERE RECORDTIME>='%1' AND RECORDTIME<='%2' ORDER BY GUID LIMIT %3,%4")
                                            .arg(ptr->startTime())
                                            .arg(ptr->endTime())
                                            .arg(ptr->startCount())
                                            .arg(ptr->recordCount());
                    if(logType == LogRecord::Operation)
                        sql = QObject::tr("SELECT * FROM operationlog WHERE RECORDTIME>='%1' AND RECORDTIME<='%2' ORDER BY GUID LIMIT %3,%4")
                                            .arg(ptr->startTime())
                                            .arg(ptr->endTime())
                                            .arg(ptr->startCount())
                                            .arg(ptr->recordCount());
                    if(logType == LogRecord::Maintain)
                        sql = QObject::tr("SELECT * FROM maintainlog WHERE RECORDTIME>='%1' AND RECORDTIME<='%2' ORDER BY GUID LIMIT %3,%4")
                                            .arg(ptr->startTime())
                                            .arg(ptr->endTime())
                                            .arg(ptr->startCount())
                                            .arg(ptr->recordCount());
                }
                else
                {
                    if(logType == LogRecord::Running)
                        sql = QObject::tr("SELECT * FROM runninglog WHERE RECORDTIME>='%1' AND RECORDTIME<='%2'")
                                            .arg(ptr->startTime())
                                            .arg(ptr->endTime());
                    if(logType == LogRecord::Operation)
                        sql = QObject::tr("SELECT * FROM operationlog WHERE RECORDTIME>='%1' AND RECORDTIME<='%2'")
                                            .arg(ptr->startTime())
                                            .arg(ptr->endTime());
                    if(logType == LogRecord::Maintain)
                        sql = QObject::tr("SELECT * FROM maintainlog WHERE RECORDTIME>='%1' AND RECORDTIME<='%2'")
                                            .arg(ptr->startTime())
                                            .arg(ptr->endTime());
                }
            }
            else
            {
                if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                {
                    if(logType == LogRecord::Running)
                        sql = QObject::tr("SELECT * FROM runninglog ORDER BY GUID LIMIT %1,%2")
                                            .arg(ptr->startCount())
                                            .arg(ptr->recordCount());
                    if(logType == LogRecord::Operation)
                        sql = QObject::tr("SELECT * FROM operationlog ORDER BY GUID LIMIT %1,%2")
                                            .arg(ptr->startCount())
                                            .arg(ptr->recordCount());
                    if(logType == LogRecord::Maintain)
                        sql = QObject::tr("SELECT * FROM maintainlog ORDER BY GUID LIMIT %1,%2")
                                            .arg(ptr->startCount())
                                            .arg(ptr->recordCount());
                }
                else
                {
                    if(logType == LogRecord::Running)
                        sql = QObject::tr("SELECT * FROM runninglog");
                    if(logType == LogRecord::Operation)
                        sql = QObject::tr("SELECT * FROM operationlog");
                    if(logType == LogRecord::Maintain)
                        sql = QObject::tr("SELECT * FROM maintainlog");
                }
            }
            if(sql != "")
            {
                bSucc = query.exec(sql);
                if (bSucc)
                {
                    while (query.next())
                    {
                        LogRecord::Ptr ptrRecord(new LogRecord());
                        ptrRecord->m_logType = logType;
                        ptrRecord->m_GUID = query.value("GUID").toInt();
                        ptrRecord->m_fileName = query.value("FILENAME").toString();
                        ptrRecord->m_recordTime = query.value("RECORDTIME").toString();
                        lst.append(ptrRecord);
                    }
                }
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBLogRecordDAO::doInsert(const QString &fileName, int logType)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "file");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        if(logType == LogRecord::Running)
            sql = QObject::tr("INSERT INTO runninglog(GUID, FILENAME) VALUES(NULL, '%1')")
                    .arg(fileName);
        if(logType == LogRecord::Operation)
            sql = QObject::tr("INSERT INTO operationlog(GUID, FILENAME) VALUES(NULL, '%1')")
                    .arg(fileName);
        if(logType == LogRecord::Maintain)
            sql = QObject::tr("INSERT INTO maintainlog(GUID, FILENAME) VALUES(NULL, '%1')")
                    .arg(fileName);
        if(!query.exec(sql))
        {
            db.close();
            return bSucc;
        }
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

