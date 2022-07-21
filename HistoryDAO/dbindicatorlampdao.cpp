#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include "dbconnection.h"
#include "dbindicatorlampdao.h"
//#include "realdata.h"
//#include "dbrealdatadao.h"
#include "dastruct.h"
#include "dbdastructdao.h"
#include "dbcolumntypetransform.h"
DBIndicatorLampDAO::DBIndicatorLampDAO()
{
    doCreateTable();
}

DBIndicatorLampDAO::~DBIndicatorLampDAO()
{

}

IndicatorLamp::List DBIndicatorLampDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    IndicatorLamp::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.LAMPDESC, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE FROM indicatorlamp a, ieddataset b WHERE a.DATAREF=b.DATAREF");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                IndicatorLamp::Ptr ptr(new IndicatorLamp());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_lampDesc = query.value("LAMPDESC").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

IndicatorLamp::Ptr DBIndicatorLampDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.LAMPDESC, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE FROM indicatorlamp a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                IndicatorLamp::Ptr ptr(new IndicatorLamp());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_lampDesc = query.value("LAMPDESC").toString();
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

IndicatorLamp::List DBIndicatorLampDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    IndicatorLamp::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.LAMPDESC, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE FROM indicatorlamp a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                IndicatorLamp::Ptr ptr(new IndicatorLamp());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_lampDesc = query.value("LAMPDESC").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

IndicatorLamp::List DBIndicatorLampDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    IndicatorLamp::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.LAMPDESC, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE FROM indicatorlamp a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            IndicatorLamp::Ptr ptr(new IndicatorLamp());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_lampDesc = query.value("LAMPDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

IndicatorLamp::Ptr DBIndicatorLampDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.LAMPDESC, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE FROM indicatorlamp a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            IndicatorLamp::Ptr ptr(new IndicatorLamp());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_lampDesc = query.value("LAMPDESC").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

IndicatorLamp::List DBIndicatorLampDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    IndicatorLamp::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.LAMPDESC, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE FROM indicatorlamp a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            IndicatorLamp::Ptr ptr(new IndicatorLamp());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_lampDesc = query.value("LAMPDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBIndicatorLampDAO::doInsert(IndicatorLamp::List &lst)
{
    bool bSucc = false;
    IndicatorLamp::List::iterator iter = lst.begin();
    //QString sql_str = "INSERT INTO indicatorlamp VALUES";
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
                IndicatorLamp::Ptr ptr(new IndicatorLamp());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString lampDesc = ptr->lampDesc();

                sql = QObject::tr("REPLACE INTO indicatorlamp VALUES(NULL, \"%1\", \"%2\")")
                        .arg(dataRef)
                        .arg(lampDesc);
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
                IndicatorLamp::Ptr ptr(new IndicatorLamp());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString lampDesc = ptr->lampDesc();

                sql = QObject::tr("REPLACE INTO indicatorlamp VALUES(NULL, \"%1\", \"%2\")")
                        .arg(dataRef)
                        .arg(lampDesc);
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

bool DBIndicatorLampDAO::doUpdate(const IndicatorLamp::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE indicatorlamp SET DATAREF=\"%1\", LAMPDESC=\"%2\" WHERE GUID=%3")
                .arg(ptr->dataRef())
                .arg(ptr->lampDesc())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBIndicatorLampDAO::doUpdate(IndicatorLamp::List &lst)
{
    bool bSucc = false;
    IndicatorLamp::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        while(iter < lst.end())
        {
            IndicatorLamp::Ptr ptr(new IndicatorLamp());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE indicatorlamp SET DATAREF=\"%1\", LAMPDESC=\"%2\" WHERE GUID=%3")
                    .arg(ptr->dataRef())
                    .arg(ptr->lampDesc())
                    .arg(ptr->GUID());
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

bool DBIndicatorLampDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM indicatorlamp WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBIndicatorLampDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE a FROM indicatorlamp a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBIndicatorLampDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM indicatorlamp");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='indicatorlamp'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBIndicatorLampDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS indicatorlamp("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) UNIQUE NOT NULL,"
                                  "LAMPDESC CHAR(255) NOT NULL");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
