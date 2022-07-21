#include <QObject>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QProcessEnvironment>
#include "dbconnectionreal.h"
#include "dbrcdfiledao.h"
DBRcdFileDAO::DBRcdFileDAO()
    : m_connectionName("connectRcdFile")
{

}

DBRcdFileDAO::~DBRcdFileDAO()
{

}

bool DBRcdFileDAO::initWaveFileTable(QSqlDatabase db, const QStringList &lst)
{
    bool bSucc = true;
    if(lst.size() == 0)
        return bSucc;
    else
    {
        QString sql = "";
        for(int i=0; i<lst.size(); i++)
        {
            QSqlQuery query(db);
            sql = QString("CREATE TABLE IF NOT EXISTS %1 ("
                            "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                            "FILEPATH VARCHAR(255) NOT NULL,"
                            "FILENAME VARCHAR(255) NOT NULL,"
                            "IEDNAME VARCHAR(255) NOT NULL,"
                            "IP VARCHAR(255) NOT NULL,"
                            "ENDSTR VARCHAR(255) NOT NULL,"
                            "SIZE VARCHAR(255) NOT NULL,"
                            "FILETIME VARCHAR(255) NOT NULL,"
                            "DBRECORDTIME VARCHAR(255) NOT NULL,"
                            "RECVSTATE INT(11) NOT NULL,"
                            "PRIMARY KEY (GUID))")
                          .arg(lst.at(i));
            //printf("sql: %s\n", sql.toStdString().data());
            if(!query.exec(sql))
            {
                bSucc = false;
                return bSucc;
            }
        }

        return bSucc;
    }
}

RcdFile::List DBRcdFileDAO::doQuery(const SearchCondition::Ptr &ptr)
{
    RcdFile::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "wavefiledb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        QString iedName = ptr->iedName();
        if(iedName != "")
        {
            sql = QObject::tr("SELECT * FROM %1 ORDER BY GUID DESC LIMIT %2,%3")
                    .arg(ptr->iedName())
                    .arg(ptr->startCount())
                    .arg(ptr->recordCount());
        }

        if (query.exec(sql))
        {
            while (query.next())
            {
                RcdFile::Ptr ptrFile(new RcdFile());
                ptrFile->m_GUID = query.value("GUID").toInt();
                ptrFile->m_iedName = query.value("IEDNAME").toString();
                ptrFile->m_ip = query.value("IP").toString();
                ptrFile->m_filePath = query.value("FILEPATH").toString();
                ptrFile->m_fileName = query.value("FILENAME").toString();
                ptrFile->m_endStr = query.value("ENDSTR").toString();
                ptrFile->m_size = query.value("SIZE").toString();
                ptrFile->m_fileTime = query.value("FILETIME").toString();
                ptrFile->m_dbRecordTime = query.value("DBRECORDTIME").toString();
                ptrFile->m_recvState = query.value("RECVSTATE").toInt();
                lst.append(ptrFile);
            }
        }
        db.close();
    }

    return lst;
}

RcdFile::List DBRcdFileDAO::doQuery(QSqlDatabase dbR, const SearchCondition::Ptr &ptr)
{
    RcdFile::List lst;
    QSqlQuery query(dbR);
    QString sql = "";
    QString iedName = ptr->iedName();
    if(iedName != "")
    {
        sql = QObject::tr("SELECT * FROM %1 ORDER BY GUID DESC LIMIT %2,%3")
                .arg(ptr->iedName())
                .arg(ptr->startCount())
                .arg(ptr->recordCount());
    }

    if (query.exec(sql))
    {
        while (query.next())
        {
            RcdFile::Ptr ptrFile(new RcdFile());
            ptrFile->m_GUID = query.value("GUID").toInt();
            ptrFile->m_iedName = query.value("IEDNAME").toString();
            ptrFile->m_ip = query.value("IP").toString();
            ptrFile->m_filePath = query.value("FILEPATH").toString();
            ptrFile->m_fileName = query.value("FILENAME").toString();
            ptrFile->m_endStr = query.value("ENDSTR").toString();
            ptrFile->m_size = query.value("SIZE").toString();
            ptrFile->m_fileTime = query.value("FILETIME").toString();
            ptrFile->m_dbRecordTime = query.value("DBRECORDTIME").toString();
            ptrFile->m_recvState = query.value("RECVSTATE").toInt();
            lst.append(ptrFile);
        }
    }

    return lst;
}

RcdFile::List DBRcdFileDAO::doQueryByIedName(QSqlDatabase dbR, const QString &iedName)
{
    RcdFile::List lst;
    QSqlQuery query(dbR);
    QString sql = QObject::tr("SELECT * FROM %1")
            .arg(iedName);

    if (query.exec(sql))
    {
        while (query.next())
        {
            RcdFile::Ptr ptrFile(new RcdFile());
            ptrFile->m_iedName = query.value("IEDNAME").toString();
            ptrFile->m_filePath = query.value("FILEPATH").toString();
            ptrFile->m_fileName = query.value("FILENAME").toString();
            ptrFile->m_fileTime = query.value("FILETIME").toString();
            ptrFile->m_dbRecordTime = query.value("DBRECORDTIME").toString();
            ptrFile->m_recvState = query.value("RECVSTATE").toInt();
            lst.append(ptrFile);
        }
    }

    return lst;
}

bool DBRcdFileDAO::doInsert(RcdFile::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "wavefiledb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        RcdFile::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            RcdFile::Ptr ptr(new RcdFile());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO %1 VALUES(NULL, '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', %10)")
                    .arg(ptr->iedName())//1
                    .arg(ptr->filePath())//2
                    .arg(ptr->fileName())//3
                    .arg(ptr->iedName())//4
                    .arg(ptr->ip())//5
                    .arg(ptr->endStr())//6
                    .arg(ptr->size())//7
                    .arg(ptr->fileTime())//8
                    .arg(ptr->dbRecordTime())//9
                    .arg(ptr->recvState());//10
            if (!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
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
        if (!bSucc)
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }

    return bSucc;
}

bool DBRcdFileDAO::doInsert(QSqlDatabase dbR, RcdFile::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlQuery query(dbR);
    query.exec("START TRANSACTION");
    QString sql = "";
    RcdFile::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        RcdFile::Ptr ptr(new RcdFile());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO %1 VALUES(NULL, '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', %10)")
                .arg(ptr->iedName())//1
                .arg(ptr->filePath())//2
                .arg(ptr->fileName())//3
                .arg(ptr->iedName())//4
                .arg(ptr->ip())//5
                .arg(ptr->endStr())//6
                .arg(ptr->size())//7
                .arg(ptr->fileTime())//8
                .arg(ptr->dbRecordTime())//9
                .arg(ptr->recvState());//10
        if (!query.exec(sql))
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
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
    if (!bSucc)
    {
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }

    return bSucc;
}

bool DBRcdFileDAO::doUpdate(RcdFile::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    RcdFile::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "wavefiledb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        while(iter < lst.end())
        {
            RcdFile::Ptr ptr(new RcdFile());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE %1 SET RECVSTATE=%2 WHERE GUID=%3")
                    .arg(ptr->iedName())//1
                    .arg(ptr->recvState())//2
                    .arg(ptr->GUID());//3
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }
            iter++;
        }
        bSucc = query.exec("COMMIT");
        if(!bSucc)
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }
    return bSucc;
}

bool DBRcdFileDAO::doUpdate(QSqlDatabase dbR, RcdFile::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    RcdFile::List::iterator iter = lst.begin();
    QSqlQuery query(dbR);
    query.exec("START TRANSACTION");
    while(iter < lst.end())
    {
        RcdFile::Ptr ptr(new RcdFile());
        ptr = *iter;
        QString sql = QObject::tr("UPDATE %1 SET RECVSTATE=%2 WHERE GUID=%3")
                .arg(ptr->iedName())//1
                .arg(ptr->recvState())//2
                .arg(ptr->GUID());//3

        if(!query.exec(sql))
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
            return bSucc;
        }
        iter++;
    }
    bSucc = query.exec("COMMIT");
    if(!bSucc)
    {
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }
    return bSucc;
}

//bool DBRcdFileDAO::doDelete(RcdFile::List &lst)
//{

//}

//bool DBRcdFileDAO::doDelete(QSqlDatabase dbR, RcdFile::List &lst)
//{

//}

//bool DBRcdFileDAO::doDelete(const RcdFile::Ptr &ptr)
//{

//}

//bool DBRcdFileDAO::doDelete(QSqlDatabase dbR, const RcdFile::Ptr &ptr)
//{

//}

bool DBRcdFileDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "wavefiledb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        bSucc = query.exec("TRUNCATE TABLE rcdfile");
        db.close();
    }

    return bSucc;
}

bool DBRcdFileDAO::doClear(QSqlDatabase dbR)
{
    bool bSucc = false;
    QSqlQuery query(dbR);
    bSucc = query.exec("TRUNCATE TABLE rcdfile");
    //db.close();

    return bSucc;
}
