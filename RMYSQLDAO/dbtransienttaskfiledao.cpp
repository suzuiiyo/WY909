#include <QObject>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbtransienttaskfiledao.h"
DBTransientTaskFileDAO::DBTransientTaskFileDAO()
    : m_connectionName("connectTransientFile")
{

}

DBTransientTaskFileDAO::~DBTransientTaskFileDAO()
{

}

int DBTransientTaskFileDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "file");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->startTime() != "" && ptr->endTime() != "")
            sql = QObject::tr("SELECT count(*) as ct FROM transienttaskfile WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2'")
                    .arg(ptr->startTime())
                    .arg(ptr->endTime());
        else
            sql = QObject::tr("SELECT count(*) as ct FROM transienttaskfile");
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

TransientTaskFile::List DBTransientTaskFileDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    TransientTaskFile::List lst_act;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "file");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->startTime() != "" && ptr->endTime() != "")
        {
            if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                sql = QObject::tr("SELECT * FROM transienttaskfile WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY UNIX_TIMESTAMP(RECORDTIME) DESC LIMIT %3, %4")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->startCount())
                            .arg(ptr->recordCount());
            else
                sql = QObject::tr("SELECT * FROM transienttaskfile WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY UNIX_TIMESTAMP(RECORDTIME) DESC")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
        }
        else
        {
            if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                sql = QObject::tr("SELECT * FROM transienttaskfile ORDER BY UNIX_TIMESTAMP(RECORDTIME) DESC LIMIT %1, %2")
                            .arg(ptr->startCount())
                            .arg(ptr->recordCount());
            else
                sql = QObject::tr("SELECT * FROM transienttaskfile ORDER BY UNIX_TIMESTAMP(RECORDTIME) DESC");
        }
        if(sql != "")
        {
            bSucc1 = query.exec(sql);
            if (bSucc1)
            {
                while (query.next())
                {
                    TransientTaskFile::Ptr ptr_alarm(new TransientTaskFile());
                    ptr_alarm->m_fileName = query.value("FILENAME").toString();
                    ptr_alarm->m_recordTime = query.value("RECORDTIME").toString();
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

bool DBTransientTaskFileDAO::doInsert(const QString &fileName)
{
    bool bSucc = false;
    if(fileName != "")
    {
        QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "file");
        if(db.isOpen() || db.open())
        {
            QSqlQuery query(db);
            query.exec("START TRANSACTION");
            QString sql = QObject::tr("INSERT INTO transienttaskfile(FILENAME) VALUES('%1')")
                    .arg(fileName);
            if (!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                return false;
            }
            bSucc = query.exec("COMMIT");
            if (!bSucc)
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
            }
        }
    }

    return bSucc;
}
