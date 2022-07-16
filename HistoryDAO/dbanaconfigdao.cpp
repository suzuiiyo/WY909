#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "dbconnection.h"
#include "dbanaconfigdao.h"
DBAnaConfigDAO::DBAnaConfigDAO()
    : m_connectionName("connectAna")
{

}

DBAnaConfigDAO::~DBAnaConfigDAO()
{

}

AnaConfig::Hash DBAnaConfigDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    AnaConfig::Hash hsh;
    QString sql = QObject::tr("SELECT * FROM anaconfig");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            QString dataRef = query.value("DATAREF").toString();
            if(hsh.count(dataRef) == 0)
            {
                AnaConfig::Ptr ptr(new AnaConfig());
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = dataRef;
                ptr->m_dataDesc = query.value("DATADESC").toString();
                hsh.insert(dataRef, ptr);
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

bool DBAnaConfigDAO::doInsert(AnaConfig::List &lst)
{
    bool bSucc = false;
    AnaConfig::List::iterator iter = lst.begin();
    int list_size = lst.size();
    if(list_size == 0)
        return true;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        query.exec("begin transaction");

        if(list_size <= 1000)
        {
            while(iter < lst.end())
            {
                AnaConfig::Ptr ptr(new AnaConfig());
                ptr = *iter;

                sql = QObject::tr("REPLACE INTO anaconfig VALUES(NULL, \"%1\", \"%2\", \"%3\")")
                        .arg(ptr->iedName())
                        .arg(ptr->dataRef())
                        .arg(ptr->dataDesc());
                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: %s", error_s.toStdString().data());
                    db.close();
                    return bSucc;
                }
                iter++;
            }
        }
        else
        {
            int count = 0;
            while(iter < lst.end())
            {
                AnaConfig::Ptr ptr(new AnaConfig());
                ptr = *iter;

                sql = QObject::tr("REPLACE INTO anaconfig VALUES(NULL, \"%1\", \"%2\", \"%3\")")
                        .arg(ptr->iedName())
                        .arg(ptr->dataRef())
                        .arg(ptr->dataDesc());
                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: %s", error_s.toStdString().data());
                    db.close();
                    return bSucc;
                }
                count++;
                if(count == 1000)
                {
                    bSucc = query.exec("commit transaction");
                    if(!bSucc){
                        QString error_s = query.lastError().text();
                        printf("error: %s", error_s.toStdString().data());
                    }
                    query.exec("begin transaction");
                    count = 0;
                }
                iter++;
            }
        }
        bSucc = query.exec("commit transaction");
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }
    return bSucc;
}

bool DBAnaConfigDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM anaconfig");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='anaconfig'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBAnaConfigDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS anaconfig("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "IEDNAME CHAR(255) NOT NULL,"
                                  "DATAREF CHAR(255) NOT NULL,"
                                  "DATADESC CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
