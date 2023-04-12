#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dblooplinkalarmrecorddao.h"
DBLoopLinkAlarmRecordDAO::DBLoopLinkAlarmRecordDAO()
    : m_connectionName("connectLARecord")
{

}

DBLoopLinkAlarmRecordDAO::~DBLoopLinkAlarmRecordDAO()
{

}

int DBLoopLinkAlarmRecordDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
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
                    sql = QObject::tr("SELECT count(*) as ct FROM looplinkalarmrecord WHERE IEDNAME='%1' AND GJTIME >= '%2' AND GJTIME <= '%3' AND ACKTIP=%4")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM looplinkalarmrecord WHERE GJTIME >= '%1' AND GJTIME <= '%2' AND ACKTIP=%3")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM looplinkalarmrecord WHERE IEDNAME='%1' AND ACKTIP=%2")
                            .arg(ptr->iedName())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM looplinkalarmrecord WHERE ACKTIP=%1")
                            .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM looplinkalarmrecord WHERE IEDNAME='%1' AND GJTIME >= '%2' AND GJTIME <= '%3'")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM looplinkalarmrecord WHERE GJTIME >= '%1' AND GJTIME <= '%2'")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM looplinkalarmrecord WHERE IEDNAME='%1'")
                            .arg(ptr->iedName());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM looplinkalarmrecord");
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

LoopLinkAlarmRecord::List DBLoopLinkAlarmRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    LoopLinkAlarmRecord::List lst_act;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->ackTip() != -1)
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                    sql = QObject::tr("SELECT * FROM looplinkalarmrecord WHERE PDTIME >= '%1' AND PDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT %4, %5")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime())
                                .arg(ptr->ackTip())
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                else
                    sql = QObject::tr("SELECT * FROM looplinkalarmrecord WHERE PDTIME >= '%1' AND PDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime())
                                .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                    sql = QObject::tr("SELECT * FROM looplinkalarmrecord WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                .arg(ptr->ackTip())
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                else
                    sql = QObject::tr("SELECT * FROM looplinkalarmrecord WHERE ACKTIP=%1 ORDER BY GUID DESC")
                            .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                    sql = QObject::tr("SELECT * FROM looplinkalarmrecord WHERE PDTIME >= '%1' AND PDTIME <= '%2' ORDER BY GUID DESC LIMIT %3, %4")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime())
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                else
                    sql = QObject::tr("SELECT * FROM looplinkalarmrecord WHERE PDTIME >= '%1' AND PDTIME <= '%2' ORDER BY GUID DESC")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime());
            }
            else
            {
                if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                    sql = QObject::tr("SELECT * FROM looplinkalarmrecord ORDER BY GUID DESC LIMIT %1, %2")
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                else
                    sql = QObject::tr("SELECT * FROM looplinkalarmrecord ORDER BY GUID DESC");
            }
        }
        if(sql != "")
        {
            bSucc1 = query.exec(sql);
            if (bSucc1)
            {
                while (query.next())
                {
                    LoopLinkAlarmRecord::Ptr ptr_act(new LoopLinkAlarmRecord());
                    ptr_act->m_GUID = query.value("GUID").toInt();
                    ptr_act->m_lineRef = query.value("LINEREF").toString();
                    ptr_act->m_result = query.value("RESULT").toString();
                    ptr_act->m_p1GUID = query.value("P1GUID").toString();
                    ptr_act->m_p2GUID = query.value("P2GUID").toString();
                    ptr_act->m_cfRef = query.value("CFREF").toString();
                    ptr_act->m_pdTime = query.value("PDTIME").toString();
                    ptr_act->m_xResult = query.value("XRESULT").toString();
                    ptr_act->m_yjAppID = query.value("YJAPPID").toString();
                    ptr_act->m_ackTip = query.value("ACKTIP").toInt();
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

bool DBLoopLinkAlarmRecordDAO::ackRecord(LoopLinkAlarmRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    LoopLinkAlarmRecord::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            LoopLinkAlarmRecord::Ptr ptr(new LoopLinkAlarmRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE looplinkalarmrecord SET ACKTIP=%1 WHERE GUID=%2")
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

bool DBLoopLinkAlarmRecordDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS looplinkalarmrecord("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "LINEREF VARCHAR(255) NOT NULL,"
                                  "RESULT VARCHAR(255) NOT NULL,"
                                  "P1GUID VARCHAR(255) DEFAULT NULL,"
                                  "P2GUID VARCHAR(255) DEFAULT NULL,"
                                  "CFREF VARCHAR(255) NOT NULL,"
                                  "PDTIME VARCHAR(255) NOT NULL,"
                                  "XRESULT VARCHAR(255) NOT NULL,"
                                  "YJAPPID VARCHAR(255) NOT NULL,"
                                  "ACKTIP INT(11) NOT NULL DEFAULT 0"
                                  "PRIMARY KEY(GUID))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
