#include <QSqlQuery>
#include <QString>
#include <QObject>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbearlywarningrecorddao.h"
DBEarlyWarningRecordDAO::DBEarlyWarningRecordDAO()
    : m_connectionName("connectEWRecord")
{

}

DBEarlyWarningRecordDAO::~DBEarlyWarningRecordDAO()
{

}

int DBEarlyWarningRecordDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
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
                sql = QObject::tr("SELECT count(*) as ct FROM earlywarningrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3")
                                            .arg(ptr->startTime())
                                            .arg(ptr->endTime())
                                            .arg(ptr->ackTip());
            else
                sql = QObject::tr("SELECT count(*) as ct FROM earlywarningrecord WHERR ACKTIP=%1")
                                            .arg(ptr->ackTip());
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
                sql = QObject::tr("SELECT count(*) as ct FROM earlywarningrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2'")
                                            .arg(ptr->startTime())
                                            .arg(ptr->endTime());
            else
                sql = QObject::tr("SELECT count(*) as ct FROM earlywarningrecord");
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

EarlyWarningRecord::List DBEarlyWarningRecordDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    EarlyWarningRecord::List lst_alarm;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM earlywarningrecord");

        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                EarlyWarningRecord::Ptr ptr_alarm(new EarlyWarningRecord());
                ptr_alarm->m_GUID = query.value("GUID").toInt();
                ptr_alarm->m_dataRef = query.value("DATAREF").toString();
                ptr_alarm->m_warningType = query.value("WARNINGTYPE").toInt();
                ptr_alarm->m_ewType = query.value("EWTYPE").toInt();
                ptr_alarm->m_dataValue = query.value("DATAVALUE").toFloat();
                ptr_alarm->m_recordTime = query.value("RECORDTIME").toString();
                ptr_alarm->m_maxData = query.value("MAXDATA").toFloat();
                ptr_alarm->m_minData = query.value("MINDATA").toFloat();
                ptr_alarm->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
                ptr_alarm->m_ackTip = query.value("ACKTIP").toInt();
                lst_alarm.append(ptr_alarm);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst_alarm;
}

EarlyWarningRecord::List DBEarlyWarningRecordDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    EarlyWarningRecord::List lst_alarm;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM earlywarningrecord");

    bSucc = query.exec(sql);
    if (bSucc)
    {
        while (query.next())
        {
            EarlyWarningRecord::Ptr ptr_alarm(new EarlyWarningRecord());
            ptr_alarm->m_GUID = query.value("GUID").toInt();
            ptr_alarm->m_dataRef = query.value("DATAREF").toString();
            ptr_alarm->m_warningType = query.value("WARNINGTYPE").toInt();
            ptr_alarm->m_ewType = query.value("EWTYPE").toInt();
            ptr_alarm->m_dataValue = query.value("DATAVALUE").toFloat();
            ptr_alarm->m_recordTime = query.value("RECORDTIME").toString();
            ptr_alarm->m_maxData = query.value("MAXDATA").toFloat();
            ptr_alarm->m_minData = query.value("MINDATA").toFloat();
            ptr_alarm->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
            ptr_alarm->m_ackTip = query.value("ACKTIP").toInt();
            lst_alarm.append(ptr_alarm);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst_alarm;
}

EarlyWarningRecord::List DBEarlyWarningRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    EarlyWarningRecord::List lst_act;
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
                    sql = QObject::tr("SELECT * FROM earlywarningrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT %4, %5")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime())
                                .arg(ptr->ackTip())
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                else
                    sql = QObject::tr("SELECT * FROM earlywarningrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime())
                                .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                    sql = QObject::tr("SELECT * FROM earlywarningrecord WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                .arg(ptr->ackTip())
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                else
                    sql = QObject::tr("SELECT * FROM earlywarningrecord WHERE ACKTIP=%1 ORDER BY GUID DESC")
                                .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                    sql = QObject::tr("SELECT * FROM earlywarningrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC LIMIT %3, %4")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime())
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                else
                    sql = QObject::tr("SELECT * FROM earlywarningrecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC")
                                .arg(ptr->startTime())
                                .arg(ptr->endTime());
            }
            else
            {
                if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                    sql = QObject::tr("SELECT * FROM earlywarningrecord ORDER BY GUID DESC LIMIT %1, %2")
                                .arg(ptr->startCount())
                                .arg(ptr->recordCount());
                else
                    sql = QObject::tr("SELECT * FROM earlywarningrecord ORDER BY GUID DESC");
            }
        }
        if(sql != "")
        {
            bSucc1 = query.exec(sql);
            if (bSucc1)
            {
                while (query.next())
                {
                    EarlyWarningRecord::Ptr ptr_alarm(new EarlyWarningRecord());
                    ptr_alarm->m_GUID = query.value("GUID").toInt();
                    ptr_alarm->m_dataRef = query.value("DATAREF").toString();
                    ptr_alarm->m_warningType = query.value("WARNINGTYPE").toInt();
                    ptr_alarm->m_ewType = query.value("EWTYPE").toInt();
                    ptr_alarm->m_dataValue = query.value("DATAVALUE").toFloat();
                    ptr_alarm->m_recordTime = query.value("RECORDTIME").toString();
                    ptr_alarm->m_maxData = query.value("MAXDATA").toFloat();
                    ptr_alarm->m_minData = query.value("MINDATA").toFloat();
                    ptr_alarm->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
                    ptr_alarm->m_ackTip = query.value("ACKTIP").toInt();
                    lst_act.append(ptr_alarm);
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

//EarlyWarningRecord::List DBEarlyWarningRecordDAO::doQuery(QSqlDatabase db, SearchCondition::List &lst, bool *ok)
//{
//    bool bSucc1 = false;
//    bool bSucc2 = true;
//    EarlyWarningRecord::List lst_alarm;
//    SearchCondition::List::iterator iter;
//    QSqlQuery query(db);
//    QString sql = "";
//    for (iter = lst.begin(); iter != lst.end(); iter++)
//    {
//        SearchCondition::Ptr ptr(new SearchCondition());
//        ptr = *iter;
//        int startCount = ptr->startCount();
//        int recordCount = ptr->recordCount();
//        if(ptr->startTime() != "" && ptr->endTime() != "" && recordCount > 0 && startCount > 0)
//            sql = QObject::tr("SELECT * FROM earlywarningrecord WHERE RECORDTIME > '%1' AND RECORDTIME < '%2' ORDER BY GUID DESC LIMIT %3,%4")
//                    .arg(ptr->startTime())
//                    .arg(ptr->endTime())
//                    .arg(startCount)
//                    .arg(recordCount);
//        else
//            sql = QObject::tr("SELECT * FROM earlywarningrecord");
//        bSucc1 = query.exec(sql);
//        if (bSucc1)
//        {
//            while (query.next())
//            {
//                EarlyWarningRecord::Ptr ptr_alarm(new EarlyWarningRecord());
//                ptr_alarm->m_GUID = query.value("GUID").toInt();
//                ptr_alarm->m_dataRef = query.value("DATAREF").toString();
//                ptr_alarm->m_warningType = query.value("WARNINGTYPE").toInt();
//                ptr_alarm->m_ewType = query.value("EWTYPE").toInt();
//                ptr_alarm->m_dataValue = query.value("DATAVALUE").toFloat();
//                ptr_alarm->m_recordTime = query.value("RECORDTIME").toString();
//                ptr_alarm->m_maxData = query.value("MAXDATA").toFloat();
//                ptr_alarm->m_minData = query.value("MINDATA").toFloat();
//                ptr_alarm->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
//                ptr_alarm->m_ackTip = query.value("ACKTIP").toInt();
//                lst_alarm.append(ptr_alarm);
//            }
//        }
//        else
//            bSucc2 = bSucc1;
//    }
//    if(ok)
//        *ok = bSucc2;

//    return lst_alarm;
//}

bool DBEarlyWarningRecordDAO::doUpdate(EarlyWarningRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    EarlyWarningRecord::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            EarlyWarningRecord::Ptr ptr(new EarlyWarningRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE earlywarningrecord SET ACKTIP=%1 WHERE GUID=%2")
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

bool DBEarlyWarningRecordDAO::doUpdate(QSqlDatabase db, EarlyWarningRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    EarlyWarningRecord::List::iterator iter;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");

    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        EarlyWarningRecord::Ptr ptr(new EarlyWarningRecord());
        ptr = *iter;

        QString sql = QObject::tr("UPDATE earlywarningrecord SET ACKTIP=%1 WHERE GUID=%2")
                .arg(ptr->ackTip())
                .arg(ptr->GUID());
        if(!query.exec(sql))
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
            return bSucc;
        }
    }
    bSucc = query.exec("COMMIT");
    if(!bSucc){
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }

    return bSucc;
}

bool DBEarlyWarningRecordDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS earlywarningrecord("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "WARNINGTYPE INT(11) NOT NULL,"
                                  "EWTYPE INT(11) NOT NULL,"
                                  "DATAVALUE FLOAT(8,3) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "MAXDATA FLOAT(8,3) NOT NULL,"
                                  "MINDATA FLOAT(8,3) NOT NULL,"
                                  "MUTATIONVALUE FLOAT(8,3) NOT NULL,"
                                  "ACKTIP INT(11) NOT NULL,"
                                  "PRIMARY KEY(GUID))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
