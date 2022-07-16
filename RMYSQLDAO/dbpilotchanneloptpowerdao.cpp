#include "dbpilotchanneloptpowerdao.h"
#include "dbconnectionreal.h"
#include "pilotchanneloptpower.h"
#include "searchcondition.h"
#include <QByteArray>
#include <QList>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <QDateTime>
DBPilotChannelOptPowerDAO::DBPilotChannelOptPowerDAO()
    : m_connectionName("connectPCOP") {}

DBPilotChannelOptPowerDAO::~DBPilotChannelOptPowerDAO() {}

int DBPilotChannelOptPowerDAO::countRecord(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM pilotchanneloptpower WHERE IEDNAME='%1'")
                        .arg(iedName);
        bSucc = query.exec(sql);
        if (bSucc)
            count = query.size();
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return count;
}

PilotChannelOptPower::List
DBPilotChannelOptPowerDAO::doQuery(SearchCondition::List &lst, bool *ok)
{
    bool bSucc = false;
    PilotChannelOptPower::List lst_act;
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
            sql = QObject::tr("SELECT * FROM pilotchanneloptpower WHERE IEDNAME='%1' ORDER BY GUID DESC LIMT %2,%3")
                .arg(iedName)
                .arg(startCount)
                .arg(recordCount);
            bSucc = query.exec(sql);
            if (bSucc)
            {
                while (query.next())
                {
                    PilotChannelOptPower::Ptr ptr_pv(new PilotChannelOptPower());
                    ptr_pv->m_iedName = iedName;
                    ptr_pv->m_dataRef = query.value("DATAREF").toString();
                    ptr_pv->m_dataType = query.value("DATATYPE").toInt();
                    ptr_pv->m_dataValue = query.value("DATAVALUE").toString();
                    ptr_pv->m_quality = query.value("QUALITY").toString();
                    ptr_pv->m_recordTime = query.value("RECORDTIME").toString();
                    lst_act.append(ptr_pv);
                }
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return lst_act;
}

PilotChannelOptPower::List DBPilotChannelOptPowerDAO::doQuery(const QString &dataRef, qint64 startTime, qint64 endTime, bool *ok)
{
    bool bSucc = false;
    PilotChannelOptPower::List lst;
    if (endTime - startTime < 0)
        return lst;

    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM pilotchanneloptpower WHERE DATAREF='%1' AND unix_timestamp(RECORDTIME)*1000>=%2 AND unix_timestamp(RECORDTIME)*1000<=%3 ORDER BY GUID ASC")
                    .arg(dataRef)
                    .arg(startTime)
                    .arg(endTime);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                PilotChannelOptPower::Ptr ptr(new PilotChannelOptPower());
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = dataRef;
                ptr->m_dataType = query.value("DATATYPE").toInt();
                ptr->m_dataValue = query.value("DATAVALUE").toString();
                ptr->m_quality = query.value("QUALITY").toString();
                ptr->m_recordTime = query.value("RECORDTIME").toString();
                lst.append(ptr);
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBPilotChannelOptPowerDAO::doInsert(PilotChannelOptPower::List &lst)
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
        PilotChannelOptPower::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            PilotChannelOptPower::Ptr ptr(new PilotChannelOptPower());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO pilotchanneloptpower VALUES(NULL, '%1', '%2', '%3', %4, '%5', '%6', '%7', '')")
                    .arg(ptr->iedName())     // 1
                    .arg(ptr->dataRef())     // 2
                    .arg(ptr->dataDesc())    // 3
                    .arg(ptr->dataType())    // 4
                    .arg(ptr->dataValue())   // 5
                    .arg(ptr->quality())     // 6
                    .arg(ptr->recordTime()); // 7
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

bool DBPilotChannelOptPowerDAO::doInsert(QSqlDatabase db, PilotChannelOptPower::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
      return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    PilotChannelOptPower::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        PilotChannelOptPower::Ptr ptr(new PilotChannelOptPower());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO pilotchanneloptpower(GUID, IEDNAME, DATAREF, DATADESC, DATATYPE, DATAVALUE, QUALITY, RECORDTIME, SCOPE) VALUES(NULL, '%1', '%2', '%3', %4, '%5', '%6', '%7', '')")
                    .arg(ptr->iedName())     // 1
                    .arg(ptr->dataRef())     // 2
                    .arg(ptr->dataDesc())    // 3
                    .arg(ptr->dataType())    // 4
                    .arg(ptr->dataValue())   // 5
                    .arg(ptr->quality())     // 6
                    .arg(ptr->recordTime()); // 7
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

bool DBPilotChannelOptPowerDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QDateTime time = QDateTime::currentDateTime();
        QString time_str1 = time.addDays(+1).toString("yyyyMMdd");
        QString time_str2 = time.addDays(+1).toString("yyyy-MM-dd");
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS pilotchannelothertmdata("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "DBTIME DATETIME NOT NULL DEFAULT NOW(),"
                                  "SCOPE VARCHAR(255) NOT NULL,"
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
