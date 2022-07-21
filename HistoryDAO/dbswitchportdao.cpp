#include <QObject>
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <QSqlError>
#include "dbconnection.h"
#include "dbswitchportdao.h"
#include "dastruct.h"
#include "dbdastructdao.h"
DBSwitchPortDAO::DBSwitchPortDAO()
    : m_connectionName("connectSwitchPort")
{

}

DBSwitchPortDAO::~DBSwitchPortDAO()
{

}

SwitchPort::List DBSwitchPortDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    SwitchPort::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM switchport");

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SwitchPort::Ptr ptr(new SwitchPort());
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_port = query.value("PORT").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SwitchPort::List DBSwitchPortDAO::doQueryByLineRef(const QString &lineRef, bool *ok)
{
    bool bSucc = false;
    SwitchPort::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.PORT, a.DATAREF, a.DATATYPE FROM switchport a, fibreoptical b WHERE b.LINEREF=\"%1\" AND (a.PORT=b.PORT1 OR a.PORT=b.PORT2)")
                .arg(lineRef);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SwitchPort::Ptr ptr(new SwitchPort());
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_port = query.value("PORT").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SwitchPort::List DBSwitchPortDAO::doQueryByIedName(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    SwitchPort::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM switchport WHERE IEDNAME=\"%1\"")
                .arg(iedName);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SwitchPort::Ptr ptr(new SwitchPort());
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_port = query.value("PORT").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SwitchPort::Ptr DBSwitchPortDAO::doQueryByPortID(const QString &iedName, const QString &portID, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM switchport WHERE IEDNAME=\"%1\" AND PORT=\"%2\"")
                .arg(iedName)
                .arg(portID);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SwitchPort::Ptr ptr(new SwitchPort());
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_port = query.value("PORT").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
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

SwitchPort *DBSwitchPortDAO::port(const QString &iedName, const QString &portID, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM switchport WHERE IEDNAME=\"%1\" AND PORT=\"%2\"")
                .arg(iedName)
                .arg(portID);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SwitchPort *ptr = new SwitchPort();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_port = query.value("PORT").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
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

SwitchPort::List DBSwitchPortDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    SwitchPort::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM switchport");

    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SwitchPort::Ptr ptr(new SwitchPort());
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_port = query.value("PORT").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SwitchPort::List DBSwitchPortDAO::doQueryByLineRef(QSqlDatabase db, const QString &lineRef, bool *ok)
{
    bool bSucc = false;
    SwitchPort::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.PORT, a.DATAREF, a.DATATYPE FROM switchport a, fibreoptical b WHERE b.LINEREF=\"%1\" AND (a.PORT=b.PORT1 OR a.PORT=b.PORT2)")
            .arg(lineRef);

    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SwitchPort::Ptr ptr(new SwitchPort());
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_port = query.value("PORT").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SwitchPort::List DBSwitchPortDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    SwitchPort::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM switchport WHERE IEDNAME=\"%1\"")
            .arg(iedName);

    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SwitchPort::Ptr ptr(new SwitchPort());
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_port = query.value("PORT").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SwitchPort::Ptr DBSwitchPortDAO::doQueryByPortID(QSqlDatabase db, const QString &iedName, const QString &portID, bool *ok)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM switchport WHERE IEDNAME=\"%1\" AND PORT=\"%2\"")
            .arg(iedName)
            .arg(portID);

    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SwitchPort::Ptr ptr(new SwitchPort());
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_port = query.value("PORT").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

SwitchPort *DBSwitchPortDAO::port(QSqlDatabase db, const QString &iedName, const QString &portID, bool *ok)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM switchport WHERE IEDNAME=\"%1\" AND PORT=\"%2\"")
            .arg(iedName)
            .arg(portID);

    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SwitchPort *ptr = new SwitchPort();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_port = query.value("PORT").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

bool DBSwitchPortDAO::doInsert(SwitchPort::List &lst)
{
    bool bSucc = false;
    SwitchPort::List::iterator iter = lst.begin();
    int list_size = lst.size();
    //("lst.size: %d\n", list_size);
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
                SwitchPort::Ptr ptr(new SwitchPort());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO switchport VALUES (NULL, \"%1\", \"%2\", \"%3\", \"%4\")")
                        .arg(ptr->iedName())//1
                        .arg(ptr->port())//2
                        .arg(ptr->dataRef())//3
                        .arg(ptr->dataType());//4
                //printf("sql: %s\n", sql.toStdString().data());
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
                SwitchPort::Ptr ptr(new SwitchPort());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO switchport VALUES (NULL, \"%1\", \"%2\", \"%3\", \"%4\")")
                        .arg(ptr->iedName())//1
                        .arg(ptr->port())//2
                        .arg(ptr->dataRef())//3
                        .arg(ptr->dataType());//4
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

bool DBSwitchPortDAO::doUpdate(const SwitchPort::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE switchport SET IEDNAME=\"%1\", PORT=%2, DATAREF=\"%3\", DATATYPE=\"%4\" WHERE GUID=%5")
                .arg(ptr->iedName())//1
                .arg(ptr->port())//2
                .arg(ptr->dataRef())//3
                .arg(ptr->dataType())//4
                .arg(ptr->GUID());//5
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSwitchPortDAO::doUpdate(SwitchPort::List &lst)
{
    bool bSucc = false;
    SwitchPort::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            SwitchPort::Ptr ptr(new SwitchPort());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE switchport SET IEDNAME=\"%1\", PORT=%2, DATAREF=\"%3\", DATATYPE=\"%4\" WHERE GUID=%5")
                    .arg(ptr->iedName())//1
                    .arg(ptr->port())//2
                    .arg(ptr->dataRef())//3
                    .arg(ptr->dataType())//4
                    .arg(ptr->GUID());//5
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

bool DBSwitchPortDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM switchport WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSwitchPortDAO::doDeleteByPortID(const QString &iedName, const QString &portID)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM switchport WHERE IEDNAME=\"%1\" AND PORT=\"%2\"")
                .arg(iedName)
                .arg(portID);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSwitchPortDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM switchport");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='switchport'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSwitchPortDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS switchport("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "IEDNAME CHAR(255) NOT NULL,"
                                  "PORT CHAR(255) NOT NULL,"
                                  "DATAREF CHAR(255) NOT NULL,"
                                  "DATATYPE CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

