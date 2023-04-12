#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include "connectionhistory.h"
#include "dbconnectionreal.h"
#include "dbconnectionhistorydao.h"
DBConnectionHistoryDAO::DBConnectionHistoryDAO()
    : m_connectionName("connectCHistory")
{

}

DBConnectionHistoryDAO::~DBConnectionHistoryDAO()
{

}

int DBConnectionHistoryDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
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
                    sql = QObject::tr("SELECT count(*) as ct FROM connectionhistory WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM connectionhistory WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM connectionhistory WHERE IEDNAME='%1' AND ACKTIP=%2")
                            .arg(ptr->iedName())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM connectionhistory WHERE ACKTIP=%1")
                            .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM connectionhistory WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3'")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM connectionhistory WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2'")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM connectionhistory WHERE IEDNAME='%1'")
                            .arg(ptr->iedName());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM connectionhistory");
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

ConnectionHistory::List DBConnectionHistoryDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    ConnectionHistory::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("SELECT * FROM connectionhistory");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                ConnectionHistory::Ptr ptr(new ConnectionHistory());
                ptr->m_dataValue = query.value("DATAVALUE").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_recordTime = query.value("RECORDTIME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

ConnectionHistory::List DBConnectionHistoryDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    ConnectionHistory::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("SELECT * FROM connectionhistory WHERE IEDNAME='%1'")
                .arg(iedName);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                ConnectionHistory::Ptr ptr(new ConnectionHistory());
                ptr->m_dataValue = query.value("DATAVALUE").toInt();
                ptr->m_iedName = iedName;
                ptr->m_recordTime = query.value("RECORDTIME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

ConnectionHistory::List DBConnectionHistoryDAO::doQuery(SearchCondition::List &lst, bool *ok)
{
    bool bSucc = false;
    ConnectionHistory::List lstRecord;
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
            if(ptr->ackTip() != -1)
            {
                if(ptr->iedName() != "" && ptr->startCount() > 0 && ptr->recordCount() > 0)
                {
                    sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE IEDNAME = '%1' AND RECORDTIME>='%2' AND RECORDTIME<='%3' AND ACKTIP=%4 ORDER BY GUID DESC LIMIT %5,%6")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip())
                            .arg(ptr->startCount())
                            .arg(ptr->recordCount());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE RECORDTIME>='%1' AND RECORDTIME<='%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT %4,%5")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime())
                                .arg(ptr->ackTip())
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE ACKTIP=%1")
                                .arg(ptr->ackTip());
                }
            }
            else
            {
                if(ptr->iedName() != "" && ptr->startCount() > 0 && ptr->recordCount() > 0)
                {
                    sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE IEDNAME = '%1' AND RECORDTIME>='%2' AND RECORDTIME<='%3' ORDER BY GUID DESC LIMIT %4,%5")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->startCount())
                            .arg(ptr->recordCount());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE RECORDTIME>='%1' AND RECORDTIME<='%2' ORDER BY GUID DESC LIMIT %3,%4")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime())
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory");
                }
            }


            bSucc = query.exec(sql);
            if (bSucc)
            {
                while (query.next())
                {
                    ConnectionHistory::Ptr ptrRecod(new ConnectionHistory());
                    ptrRecod->m_dataValue = query.value("DATAVALUE").toInt();
                    ptrRecod->m_iedName = query.value("IEDNAME").toString();
                    ptrRecod->m_recordTime = query.value("RECORDTIME").toString();
                    lstRecord.append(ptrRecod);
                }
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return lstRecord;
}

ConnectionHistory::List DBConnectionHistoryDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    ConnectionHistory::List lst_act;
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
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC LIMIT %5, %6")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC")
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
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->iedName())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC")
                                .arg(ptr->iedName())
                                .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE ACKTIP=%1 ORDER BY GUID DESC")
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
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
            }
            else
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE IEDNAME='%1' ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory WHERE IEDNAME='%1' ORDER BY GUID DESC")
                                .arg(ptr->iedName());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM connectionhistory ORDER BY GUID DESC LIMIT %1, %2")
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM connectionhistory ORDER BY GUID DESC");
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
                    ConnectionHistory::Ptr ptrRecod(new ConnectionHistory());
                    ptrRecod->m_GUID = query.value("GUID").toInt();
                    ptrRecod->m_dataValue = query.value("DATAVALUE").toInt();
                    ptrRecod->m_iedName = query.value("IEDNAME").toString();
                    ptrRecod->m_recordTime = query.value("RECORDTIME").toString();
                    lst_act.append(ptrRecod);
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

bool DBConnectionHistoryDAO::doInsert(const ConnectionHistory::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("INSERT INTO connectionhistory VALUES(NULL, '%1', %2, '%3', 0)")
                .arg(ptr->iedName())
                .arg(ptr->dataValue())
                .arg(ptr->recordTime());
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBConnectionHistoryDAO::ackRecord(ConnectionHistory::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    ConnectionHistory::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            ConnectionHistory::Ptr ptr(new ConnectionHistory());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE connectionhistory SET ACKTIP=%1 WHERE GUID=%2")
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

bool DBConnectionHistoryDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS connectionhistory("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAVALUE INT(11) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "ACKTIP INT(11) NOT NULL DEFAULT 0,"
                                  "PRIMARY KEY(GUID))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
