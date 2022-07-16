#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include "dbconnection.h"
#include "fibreoptical.h"
#include "dbfibreopticaldao.h"
DBFibreOpticalDAO::DBFibreOpticalDAO()
    : m_connectionName("connectOptPort")
{

}

DBFibreOpticalDAO::~DBFibreOpticalDAO()
{

}

FibreOptical::List DBFibreOpticalDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    FibreOptical::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM fibreoptical");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                FibreOptical::Ptr ptr(new FibreOptical());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_lineDesc = query.value("LINEDESC").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_port1 = query.value("PORT1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_port2 = query.value("PORT2").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

FibreOptical::List DBFibreOpticalDAO::doQueryByIedName(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    FibreOptical::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE IEDNAME=\"%1\")")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                FibreOptical::Ptr ptr(new FibreOptical());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_lineDesc = query.value("LINEDESC").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_port1 = query.value("PORT1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_port2 = query.value("PORT2").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

FibreOptical::Ptr DBFibreOpticalDAO::doQueryByLineRef(const QString &lineRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE LINEREF=\"%1\"")
                .arg(lineRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                FibreOptical::Ptr ptr(new FibreOptical());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_lineDesc = query.value("LINEDESC").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_port1 = query.value("PORT1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_port2 = query.value("PORT2").toString();
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

FibreOptical::Ptr DBFibreOpticalDAO::doQueryByPortID(const QString &portID, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE PORT1=\"%1\" OR PORT2=\"%1\")")
                .arg(portID);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                FibreOptical::Ptr ptr(new FibreOptical());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_lineDesc = query.value("LINEDESC").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_port1 = query.value("PORT1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_port2 = query.value("PORT2").toString();
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

FibreOptical::List DBFibreOpticalDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    FibreOptical::List lst;
    QString sql = QObject::tr("SELECT * FROM fibreoptical");
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            FibreOptical::Ptr ptr(new FibreOptical());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_lineDesc = query.value("LINEDESC").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_port1 = query.value("PORT1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_port2 = query.value("PORT2").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

FibreOptical::List DBFibreOpticalDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    FibreOptical::List lst;
    QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE IEDNAME=\"%1\")")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(query.exec(sql))
    {
        while(query.next())
        {
            FibreOptical::Ptr ptr(new FibreOptical());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_lineDesc = query.value("LINEDESC").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_port1 = query.value("PORT1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_port2 = query.value("PORT2").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

FibreOptical::Ptr DBFibreOpticalDAO::doQueryByLineRef(QSqlDatabase db, const QString &lineRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE LINEREF=\"%1\"")
            .arg(lineRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            FibreOptical::Ptr ptr(new FibreOptical());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_lineDesc = query.value("LINEDESC").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_port1 = query.value("PORT1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_port2 = query.value("PORT2").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

FibreOptical::Ptr DBFibreOpticalDAO::doQueryByPortID(QSqlDatabase db, const QString &portID, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE PORT1=\"%1\" OR PORT2=\"%1\")")
            .arg(portID);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            FibreOptical::Ptr ptr(new FibreOptical());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_lineDesc = query.value("LINEDESC").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_port1 = query.value("PORT1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_port2 = query.value("PORT2").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

FibreOptical * DBFibreOpticalDAO::line(const QString &portID1, const QString &portID2, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE PORT1=\"%1\" OR PORT2=\"%2\"")
                .arg(portID1)
                .arg(portID2);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                FibreOptical *ptr = new FibreOptical();
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_lineDesc = query.value("LINEDESC").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_port1 = query.value("PORT1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_port2 = query.value("PORT2").toString();
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

FibreOptical * DBFibreOpticalDAO::line(const QString &lineRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE LINEREF=\"%1\"")
                .arg(lineRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                FibreOptical *ptr = new FibreOptical();
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_lineDesc = query.value("LINEDESC").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_port1 = query.value("PORT1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_port2 = query.value("PORT2").toString();
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

FibreOptical *DBFibreOpticalDAO::line(QSqlDatabase db, const QString &portID1, const QString &portID2, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE PORT1=\"%1\" OR PORT2=\"%2\"")
            .arg(portID1)
            .arg(portID2);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            FibreOptical *ptr = new FibreOptical();
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_lineDesc = query.value("LINEDESC").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_port1 = query.value("PORT1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_port2 = query.value("PORT2").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

FibreOptical *DBFibreOpticalDAO::line(QSqlDatabase db, const QString &lineRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM fibreoptical WHERE LINEREF=\"%1\"")
            .arg(lineRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            FibreOptical *ptr = new FibreOptical();
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_lineDesc = query.value("LINEDESC").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_port1 = query.value("PORT1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_port2 = query.value("PORT2").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

bool DBFibreOpticalDAO::doInsert(FibreOptical::List &lst)
{
    bool bSucc = false;
    FibreOptical::List::iterator iter = lst.begin();
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
                FibreOptical::Ptr ptr(new FibreOptical());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO fibreoptical VALUES (NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\")")
                        .arg(ptr->m_lineRef)//1
                        .arg(ptr->m_lineDesc)//2
                        .arg(ptr->m_iedName1)//3
                        .arg(ptr->m_port1)//4
                        .arg(ptr->m_iedName2)//5
                        .arg(ptr->m_port2);//6
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
                FibreOptical::Ptr ptr(new FibreOptical());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO fibreoptical VALUES (NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\")")
                        .arg(ptr->m_lineRef)//1
                        .arg(ptr->m_lineDesc)//2
                        .arg(ptr->m_iedName1)//3
                        .arg(ptr->m_port1)//4
                        .arg(ptr->m_iedName2)//5
                        .arg(ptr->m_port2);//6
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

bool DBFibreOpticalDAO::doUpdate(const FibreOptical::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE fibreoptical SET LINEREF=\"%1\", LINEDESC=\"%2\", IEDNAME1=\"%3\", PORT1=\"%4\", IEDNAME2=\"%5\", PORT2=\"%6\" WHERE GUID=%7")
                .arg(ptr->lineRef())//1
                .arg(ptr->lineDesc())//2
                .arg(ptr->iedName1())//3
                .arg(ptr->port1())//4
                .arg(ptr->iedName2())//5
                .arg(ptr->port2())//6
                .arg(ptr->GUID());//7
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBFibreOpticalDAO::doUpdate(FibreOptical::List &lst)
{
    bool bSucc = false;
    FibreOptical::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            FibreOptical::Ptr ptr(new FibreOptical());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE fibreoptical SET LINEREF=\"%1\", LINEDESC=\"%2\", IEDNAME1=\"%3\", PORT1=\"%4\", IEDNAME2=\"%5\", PORT2=\"%6\" WHERE GUID=%7")
                    .arg(ptr->lineRef())//1
                    .arg(ptr->lineDesc())//2
                    .arg(ptr->iedName1())//3
                    .arg(ptr->port1())//4
                    .arg(ptr->iedName2())//5
                    .arg(ptr->port2())//6
                    .arg(ptr->GUID());//7
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

bool DBFibreOpticalDAO::doDeleteByLineRef(const QString &lineRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM fibreoptical WHERE LINEREF=\"%1\"")
                .arg(lineRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBFibreOpticalDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM fibreoptical WHERE IEDNAME1=\"%1\" OR IEDNAME2=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBFibreOpticalDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM fibreoptical");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='fibreoptical'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBFibreOpticalDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS fibreoptical("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "LINEREF CHAR(255) UNIQUE NOT NULL,"
                                  "LINEDESC INTEGER NOT NULL,"
                                  "IEDNAME1 CHAR(255) NOT NULL,"
                                  "PORT1 CHAR(255) NOT NULL,"
                                  "IEDNAME2 CHAR(255) NOT NULL,"
                                  "PORT2 CHAR(255) NOT NULL");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
