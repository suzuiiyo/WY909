#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QVariant>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbpatrolfiledao.h"
DBPatrolFileDAO::DBPatrolFileDAO()
    : m_connectionName("connectPatrolFile")
{

}

DBPatrolFileDAO::~DBPatrolFileDAO()
{

}

int DBPatrolFileDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "file");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->startTime() != "" && ptr->endTime() != "")
            sql = QObject::tr("SELECT count(*) as ct FROM patrolfile WHERE TASKFINISHTIME>='%1' AND TASKFINISHTIME<='%2'")
                           .arg(ptr->startTime())
                           .arg(ptr->endTime());
        else
            sql = QObject::tr("SELECT count(*) as ct FROM patrolfile");
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
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return count;
}

PatrolFile::List DBPatrolFileDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    PatrolFile::List lstRecord;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "file");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->startTime() != "" && ptr->endTime() != "")
        {
            if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                sql = QObject::tr("SELECT * FROM patrolfile WHERE TASKFINISHTIME>='%1' AND TASKFINISHTIME<='%2' LIMIT %3,%4")
                        .arg(ptr->startTime())
                        .arg(ptr->endTime())
                        .arg(ptr->startCount())
                        .arg(ptr->recordCount());
            else
                sql = QObject::tr("SELECT * FROM patrolfile WHERE TASKFINISHTIME>='%1' AND TASKFINISHTIME<='%2'")
                        .arg(ptr->startTime())
                        .arg(ptr->endTime());
        }
        else
        {
            if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                sql = QObject::tr("SELECT * FROM patrolfile LIMIT %1,%2")
                        .arg(ptr->startCount())
                        .arg(ptr->recordCount());
            else
                sql = QObject::tr("SELECT * FROM patrolfile");
        }

        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                PatrolFile::Ptr ptrRecod(new PatrolFile());
                ptrRecod->m_fileName = query.value("FILENAME").toString();
                ptrRecod->m_taskFinishTime = query.value("TASKFINISHTIME").toString();
                ptrRecod->m_accessDevNum = query.value("ACCESSDEVNUM").toInt();
                ptrRecod->m_taskDevNum = query.value("TASKDEVNUM").toInt();
                ptrRecod->m_abnormalDevNum = query.value("ABNORMALDEVNUM").toInt();
                ptrRecod->m_seriousDevNum = query.value("SERIOUSDEVNUM").toInt();
                lstRecord.append(ptrRecod);
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return lstRecord;
}
