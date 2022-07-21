#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QVariant>
#include "dbconnectionreal.h"
#include "dbdevnoncorrespondingrecorddao.h"
DBDevNonCorrespondingRecordDAO::DBDevNonCorrespondingRecordDAO()
    : m_connectionName("connectCorrespondingRecord")
{

}

DBDevNonCorrespondingRecordDAO::~DBDevNonCorrespondingRecordDAO()
{

}

int DBDevNonCorrespondingRecordDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
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
                if(ptr->bayName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM devnoncorrespondingrecord WHERE BAYNAME='%1' AND UPDATETIME >= '%2' AND UPDATETIME <= '%3' AND ACKTIP=%4")
                            .arg(ptr->bayName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM devnoncorrespondingrecord WHERE UPDATETIME >= '%1' AND UPDATETIME <= '%2'  AND ACKTIP=%3")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->bayName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM devnoncorrespondingrecord WHERE BAYNAME='%1' AND ACKTIP=%2")
                            .arg(ptr->bayName())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM devnoncorrespondingrecord WHERE ACKTIP=%1")
                            .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->bayName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM devnoncorrespondingrecord WHERE BAYNAME='%1' AND UPDATETIME >= '%2' AND UPDATETIME <= '%3'")
                            .arg(ptr->bayName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM devnoncorrespondingrecord WHERE UPDATETIME >= '%1' AND UPDATETIME <= '%2'")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
            }
            else
            {
                if(ptr->bayName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM devnoncorrespondingrecord WHERE BAYNAME='%1'")
                            .arg(ptr->bayName());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM devnoncorrespondingrecord");
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

DevNonCorrespondingRecord::List DBDevNonCorrespondingRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    DevNonCorrespondingRecord::List lst_act;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->ackTip() != -1)
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->bayName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE BAYNAME='%1' AND UPDATETIME >= '%2' AND UPDATETIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC LIMIT %5, %6")
                                    .arg(ptr->bayName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE BAYNAME='%1' AND UPDATETIME >= '%2' AND UPDATETIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC")
                                    .arg(ptr->bayName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE UPDATETIME >= '%1' AND UPDATETIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE UPDATETIME >= '%1' AND UPDATETIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
            }
            else
            {
                if(ptr->bayName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE BAYNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->bayName())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE BAYNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC")
                                .arg(ptr->bayName())
                                .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE ACKTIP=%1 ORDER BY GUID DESC")
                                    .arg(ptr->ackTip());
                }
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->bayName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE BAYNAME='%1' AND UPDATETIME >= '%2' AND UPDATETIME <= '%3' ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->bayName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE BAYNAME='%1' AND UPDATETIME >= '%2' AND UPDATETIME <= '%3' ORDER BY GUID DESC")
                                    .arg(ptr->bayName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE UPDATETIME >= '%1' AND UPDATETIME <= '%2' ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE UPDATETIME >= '%1' AND UPDATETIME <= '%2' ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
            }
            else
            {
                if(ptr->bayName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE BAYNAME='%1' ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->bayName())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord WHERE BAYNAME='%1' ORDER BY GUID DESC")
                                .arg(ptr->bayName());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord ORDER BY GUID DESC LIMIT %1, %2")
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM devnoncorrespondingrecord ORDER BY GUID DESC");
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
                    DevNonCorrespondingRecord::Ptr ptrRecod(new DevNonCorrespondingRecord());
                    ptrRecod->m_GUID = query.value("GUID").toInt();
                    ptrRecod->m_bayName = query.value("BAYNAME").toString();
                    ptrRecod->m_bayType = query.value("BAYTYPE").toString();
                    ptrRecod->m_iedName = query.value("IEDNAME").toString();
                    ptrRecod->m_iedDesc = query.value("IEDDESC").toString();
                    ptrRecod->m_setType = query.value("SETTYPE").toString();
                    ptrRecod->m_state = query.value("STATE").toInt();
                    ptrRecod->m_updateTime = query.value("UPDATETIME").toString();
                    ptrRecod->m_remarks = query.value("REMARKS").toString();
                    ptrRecod->m_ackTip = query.value("ACKTIP").toInt();
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

bool DBDevNonCorrespondingRecordDAO::ackRecord(DevNonCorrespondingRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    DevNonCorrespondingRecord::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            DevNonCorrespondingRecord::Ptr ptr(new DevNonCorrespondingRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE devnoncorrespondingrecord SET ACKTIP=%1 WHERE GUID=%2")
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

bool DBDevNonCorrespondingRecordDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS devnoncorrespondingrecord("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "BAYNAME VARCHAR(255) NOT NULL,"
                                  "BAYTYPE VARCHAR(255) DEFAULT NULL,"
                                  "SETTYPE VARCHAR(255) NOT NULL,"
                                  "STATE INT(11) NOT NULL,"
                                  "IEDNAME VARCHAR(255) DEFAULT NULL,"
                                  "IEDDESC VARCHAR(255) DEFAULT NULL,"
                                  "BAYCOMPCOD JSON,"
                                  "IEDCOMPRLT JSON,"
                                  "UPDATETIME VARCHAR(255) DEFAULT NULL,"
                                  "REMARKS VARCHAR(255) DEFAULT NULL,"
                                  "ACKTIP INT(11) NOT NULL DEFAULT 0,"
                                  "PRIMARY KEY(GUID))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
