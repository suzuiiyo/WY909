#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QVariant>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbuserinfodao.h"
DBUserInfoDAO::DBUserInfoDAO()
    : m_connectionName("connectionUserInfo")
{

}

DBUserInfoDAO::~DBUserInfoDAO()
{

}

int DBUserInfoDAO::countRecord(bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM userinfo");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                count++;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return count;
}

UserInfo::Ptr DBUserInfoDAO::doQuery(const QString &userName, const QString &passward, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM userinfo WHERE USERNAME='%1' AND PASSWARD='%2'")
                .arg(userName)
                .arg(passward);

        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                UserInfo::Ptr ptr(new UserInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_userName = query.value("USERNAME").toString();
                ptr->m_nickName = query.value("NICKNAME").toString();
                ptr->m_authorityID = query.value("AUTHORITYID").toInt();
                ptr->m_authorityDesc = query.value("AUTHORITYDESC").toString();
                ptr->m_passward = query.value("PASSWARD").toString();
                ptr->m_createTime = query.value("CREATETIME").toString();
                ptr->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
                if(ok)
                    *ok = bSucc;
                db.close();
                return ptr;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

UserInfo::List DBUserInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    UserInfo::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM userinfo");

        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                UserInfo::Ptr ptr(new UserInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_userName = query.value("USERNAME").toString();
                ptr->m_nickName = query.value("NICKNAME").toString();
                ptr->m_authorityID = query.value("AUTHORITYID").toInt();
                ptr->m_authorityDesc = query.value("AUTHORITYDESC").toString();
                ptr->m_passward = query.value("PASSWARD").toString();
                ptr->m_createTime = query.value("CREATETIME").toString();
                ptr->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

UserInfo::List DBUserInfoDAO::doQuery(int authorityID, bool *ok)
{
    bool bSucc = false;
    UserInfo::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM userinfo WHERE AUTHORITYID=%1")
                .arg(authorityID);

        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                UserInfo::Ptr ptr(new UserInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_userName = query.value("USERNAME").toString();
                ptr->m_nickName = query.value("NICKNAME").toString();
                ptr->m_authorityID = query.value("AUTHORITYID").toInt();
                ptr->m_authorityDesc = query.value("AUTHORITYDESC").toString();
                ptr->m_passward = query.value("PASSWARD").toString();
                ptr->m_createTime = query.value("CREATETIME").toString();
                ptr->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBUserInfoDAO::doInsert(const UserInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = QObject::tr("INSERT INTO userinfo VALUES(NULL, '%1', '%2', %3, '%4', '%5', '%6', '%7')")
                    .arg(ptr->userName())               // 1
                    .arg(ptr->nickName())               // 2
                    .arg(ptr->authorityID())            // 3
                    .arg(ptr->authorityDesc())          // 4
                    .arg(ptr->passward())               // 5
                    .arg(ptr->createTime())             // 6
                    .arg(ptr->lastUpdateTime());        // 7
        query.exec(sql);
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

bool DBUserInfoDAO::doInsert(UserInfo::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        UserInfo::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            UserInfo::Ptr ptr(new UserInfo());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO userinfo VALUES(NULL, '%1', '%2', %3, '%4', '%5', '%6', '%7')")
                        .arg(ptr->userName())               // 1
                        .arg(ptr->nickName())               // 2
                        .arg(ptr->authorityID())            // 3
                        .arg(ptr->authorityDesc())          // 4
                        .arg(ptr->passward())               // 5
                        .arg(ptr->createTime())             // 6
                        .arg(ptr->lastUpdateTime());        // 7
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

bool DBUserInfoDAO::doUpdate(const UserInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = QObject::tr("UPDATE userinfo SET USERNAME='%1', NICKNAME='%2', AUTHORITYID=%3, AUTHORITYDESC='%4', PASSWARD='%5', LASTUPDATETIME='%6' WHERE GUID=%7")
                    .arg(ptr->userName())               // 1
                    .arg(ptr->nickName())               // 2
                    .arg(ptr->authorityID())            // 3
                    .arg(ptr->authorityDesc())          // 4
                    .arg(ptr->passward())               // 5
                    .arg(ptr->lastUpdateTime())         // 6
                    .arg(ptr->GUID());                  // 7
        query.exec(sql);
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

bool DBUserInfoDAO::doUpdate(UserInfo::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        UserInfo::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            UserInfo::Ptr ptr(new UserInfo());
            ptr = *iter;
            sql = QObject::tr("UPDATE userinfo SET USERNAME='%1', NICKNAME='%2', AUTHORITYID=%3, AUTHORITYDESC='%4', PASSWARD='%5', LASTUPDATETIME='%6' WHERE GUID=%7")
                                .arg(ptr->userName())               // 1
                                .arg(ptr->nickName())               // 2
                                .arg(ptr->authorityID())            // 3
                                .arg(ptr->authorityDesc())          // 4
                                .arg(ptr->passward())               // 5
                                .arg(ptr->lastUpdateTime())         // 6
                                .arg(ptr->GUID());                  // 7
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

bool DBUserInfoDAO::doDelete(const UserInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM userinfo WHERE GUID=%1")
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBUserInfoDAO::doDelete(UserInfo::List &lst)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        UserInfo::List::iterator iter;
        QString sql = "";
        query.exec("START TRANSACTION");
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            UserInfo::Ptr ptr(new UserInfo());
            ptr = *iter;
            sql = QObject::tr("DELETE FROM userinfo WHERE GUID=%1")
                    .arg(ptr->GUID());
            if(!query.exec(sql))
            {
                db.close();
                return false;
            }
        }
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

bool DBUserInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "userdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS userinfo("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "USENAME VARCHAR(255) NOT NULL,"
                                  "NICKNAME VARCHAR(255) NOT NULL,"
                                  "AUTHORITYID VARCHAR(255) NOT NULL,"
                                  "AUTHORITYDESC INT(11) NOT NULL,"
                                  "PASSWARD VARCHAR(255) NOT NULL,"
                                  "CREATETIME VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID),"
                                  "UNIQUE KEY UK_userinfo_USERNAME(USERNAME))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
