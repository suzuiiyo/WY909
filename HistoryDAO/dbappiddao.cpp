#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QString>
#include "appid.h"
#include "dbconnection.h"
#include "dbappiddao.h"
DBAppIdDAO::DBAppIdDAO()
    : m_connectionName("connectAppId")
{

}

DBAppIdDAO::~DBAppIdDAO()
{

}

AppId::List DBAppIdDAO::doQuery()
{
    AppId::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM appidrelation");
        QSqlQuery query(db);
        if(query.exec(sql))
        {
            while(query.next())
            {
                AppId::Ptr ptr(new AppId());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_appId = query.value("APPID").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }

    return lst;
}

AppId::List DBAppIdDAO::doQuery(const QString &appId)
{
    AppId::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM appidrelation WHERE APPID=\"%1\"")
                .arg(appId);
        QSqlQuery query(db);
        if(query.exec(sql))
        {
            while(query.next())
            {
                AppId::Ptr ptr(new AppId());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_appId = query.value("APPID").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }

    return lst;
}

AppId::Hash DBAppIdDAO::doQueryHash()
{
    AppId::Hash hsh;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM appidrelation");
        QSqlQuery query(db);
        if(query.exec(sql))
        {
            while(query.next())
            {
                AppId::Ptr ptr(new AppId());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_appId = query.value("APPID").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                hsh.insert(ptr->appId(), ptr);
            }
        }
        db.close();
    }

    return hsh;
}

bool DBAppIdDAO::doInsert(AppId::List &lst)
{
    bool bSucc = false;
    AppId::List::iterator iter = lst.begin();
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
                AppId::Ptr ptr(new AppId());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO appidrelation VALUES(NULL, \"%1\", \"%2\")")
                        .arg(ptr->appId())
                        .arg(ptr->iedName());
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
                AppId::Ptr ptr(new AppId());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO appidrelation VALUES(NULL, \"%1\", \"%2\")")
                        .arg(ptr->appId())
                        .arg(ptr->iedName());
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

bool DBAppIdDAO::doUpdate(const AppId::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE appidrelation SET APPID=\"%1\", IEDNAME=\"%2\" WHERE GUID=%3")
                .arg(ptr->appId())//1
                .arg(ptr->iedName())//2
                .arg(ptr->GUID());//3
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBAppIdDAO::doUpdate(AppId::List &lst)
{
    bool bSucc = false;
    AppId::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            AppId::Ptr ptr(new AppId());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE appidrelation SET APPID=\"%1\", IEDNAME=\"%2\" WHERE GUID=%3")
                    .arg(ptr->appId())//1
                    .arg(ptr->iedName())//2
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

        bSucc = query.exec("commit transaction");
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }
    return bSucc;
}

bool DBAppIdDAO::doDelete(const QString &appId)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM appidrelation WHERE APPID=\"%1\"")
                .arg(appId);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBAppIdDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM appidrelation");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='appidrelation'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}
