#include <QByteArray>
#include <QList>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include "dbactioneventdao.h"
#include "acteventinfo.h"
#include "dbconnectionreal.h"
#include "searchcondition.h"
DBActionEventDAO::DBActionEventDAO()
    : m_connectionName("connectActionEventR")
{

}

DBActionEventDAO::~DBActionEventDAO()
{

}

int DBActionEventDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
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
                    sql = QObject::tr("SELECT count(*) as ct FROM actionevent WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM actionevent WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM actionevent WHERE IEDNAME='%1' AND ACKTIP=%2")
                            .arg(ptr->iedName())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM actionevent WHERE ACKTIP=%1")
                            .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM actionevent WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3'")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM actionevent WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2'")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM actionevent WHERE IEDNAME='%1'");
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM actionevent");
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

ActEventInfo::List DBActionEventDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    ActEventInfo::List lst_act;
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
                        sql = QObject::tr("SELECT * FROM actionevent WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC LIMIT %5, %6")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM actionevent WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM actionevent WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT 4, %5")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM actionevent WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC")
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
                        sql = QObject::tr("SELECT * FROM actionevent WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->iedName())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM actionevent WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC")
                                .arg(ptr->iedName())
                                .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM actionevent WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM actionevent WHERE ACKTIP=%1 ORDER BY GUID DESC")
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
                        sql = QObject::tr("SELECT * FROM actionevent WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM actionevent WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM actionevent WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM actionevent WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
            }
            else
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM actionevent WHERE IEDNAME='%1' ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM actionevent WHERE IEDNAME='%1' ORDER BY GUID DESC")
                                .arg(ptr->iedName());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM actionevent ORDER BY GUID DESC LIMIT %1, %2")
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM actionevent ORDER BY GUID DESC");
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
                    ActEventInfo::Ptr ptr_act(new ActEventInfo());
                    ptr_act->setGUID(query.value("GUID").toInt());
                    ptr_act->setIedName(query.value("IEDNAME").toString());
                    ptr_act->setDataRef(query.value("DATAREF").toString());
                    ptr_act->setDataDesc(query.value("DATADESC").toString());
                    ptr_act->setDataType(query.value("DATATYPE").toInt());
                    ptr_act->setDataValue(query.value("DATAVALUE").toString());
                    ptr_act->setQuality(query.value("QUALITY").toString());
                    ptr_act->setRecordTime(query.value("RECORDTIME").toString());
                    ptr_act->setAckTip(query.value("ACKTIP").toInt());
                    lst_act.append(ptr_act);
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

bool DBActionEventDAO::doInsert(ActEventInfo::List &lst) {
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        ActEventInfo::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            ActEventInfo::Ptr ptr(new ActEventInfo());
            ptr = *iter;
            int dataType = ptr->dataType();
            QString dataValue = ptr->dataValue();
            QString quality = ptr->quality();
            QString recordTime = ptr->recordTime();
            QString iedName = ptr->iedName();
            QString dataRef = ptr->dataRef();
            QString dataDesc = ptr->dataDesc();
            sql = QObject::tr("INSERT INTO actionevent VALUES(NULL, '%1', '%2', '%3', %4, '%5', '%6', '%7', %8)")
                        .arg(iedName)     // 1
                        .arg(dataRef)     // 2
                        .arg(dataDesc)    // 3
                        .arg(dataType)    // 4
                        .arg(dataValue)   // 5
                        .arg(quality)     // 6
                        .arg(recordTime)  // 7
                        .arg(ptr->ackTip());//8
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

bool DBActionEventDAO::doInsert(QSqlDatabase db, ActEventInfo::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    ActEventInfo::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        ActEventInfo::Ptr ptr(new ActEventInfo());
        ptr = *iter;
        int dataType = ptr->dataType();
        QString dataValue = ptr->dataValue();
        QString quality = ptr->quality();
        QString recordTime = ptr->recordTime();
        QString iedName = ptr->iedName();
        QString dataRef = ptr->dataRef();
        QString dataDesc = ptr->dataDesc();
        sql = QObject::tr("INSERT INTO actionevent(GUID, IEDNAME, DATAREF, DATADESC, DATATYPE, DATAVALUE, QUALITY, RECORDTIME) VALUES(NULL, '%1', '%2', '%3', %4, '%5', '%6', '%7')")
                .arg(iedName)     // 1
                .arg(dataRef)     // 2
                .arg(dataDesc)    // 3
                .arg(dataType)    // 4
                .arg(dataValue)   // 5
                .arg(quality)     // 6
                .arg(recordTime);    // 7
        if (!query.exec(sql))
            return false;
        count++;
        if (count == 200)
        {
            bSucc = query.exec("COMMIT");
            query.exec("START TRANSACTION");
            count = 0;
        }
    }
    bSucc = query.exec("COMMIT");

    return bSucc;
}

bool DBActionEventDAO::ackRecord(ActEventInfo::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    ActEventInfo::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            ActEventInfo::Ptr ptr(new ActEventInfo());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE actionevent SET ACKTIP=%1 WHERE GUID=%2")
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

bool DBActionEventDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QDateTime time = QDateTime::currentDateTime();
        QString time_str1 = time.addDays(+1).toString("yyyyMMdd");
        QString time_str2 = time.addDays(+1).toString("yyyy-MM-dd");
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS actionevent("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "DBTIME DATETIME NOT NULL DEFAULT NOW(),"
                                  "ACKTIP INT(11) NOT NULL DEFAULT 0,"
                                  "PRIMARY KEY(GUID, DBTIME))"
                                  "PARTITION BY RANGE(TO_DAYS(DBTIME))("
                                  "PARTITION p%1 VALUES LESS THAN(TO_DAYS('%2')))")
                .arg(time_str1)
                .arg(time_str2);
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
