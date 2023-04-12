#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include "dbconnection.h"
#include "svinfo.h"
#include "dbsvinfodao.h"
//#include "realdata.h"
//#include "dbrealdatadao.h"
DBSVInfoDAO::DBSVInfoDAO()
    : m_connectionName("connectSVInfo")
{
    doCreateTable();
}

DBSVInfoDAO::~DBSVInfoDAO()
{

}

SVInfo::List DBSVInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    SVInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.DATASET, b.IEDNAME, b.DATADESC FROM svinfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SVInfo::Ptr ptr(new SVInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SVInfo::Ptr DBSVInfoDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.DATASET, b.IEDNAME, b.DATADESC FROM svinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            SVInfo::Ptr ptr(new SVInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            if(ok)
                *ok = bSucc;
            db.close();
            return ptr;
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

SVInfo::List DBSVInfoDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    SVInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.DATASET, b.IEDNAME, b.DATADESC FROM svinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SVInfo::Ptr ptr(new SVInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SVInfo::List DBSVInfoDAO::doQuery(const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    SVInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.DATASET, b.IEDNAME, b.DATADESC FROM svinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
                .arg(iedName)
                .arg(setType);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SVInfo::Ptr ptr(new SVInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SVInfo::List DBSVInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    SVInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.DATASET, b.IEDNAME, b.DATADESC FROM svinfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SVInfo::Ptr ptr(new SVInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SVInfo::Ptr DBSVInfoDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.DATASET, b.IEDNAME, b.DATADESC FROM svinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        SVInfo::Ptr ptr(new SVInfo());
        ptr->m_GUID = query.value("GUID").toInt();
        ptr->m_iedName = query.value("IEDNAME").toString();
        ptr->m_dataRef = query.value("DATAREF").toString();
        ptr->m_dataSet = query.value("DATASET").toString();
        ptr->m_dataDesc = query.value("DATADESC").toString();
        ptr->m_dimension = query.value("DIMENSION").toString();
        if(ok)
            *ok = bSucc;
        return ptr;
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

SVInfo::List DBSVInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    SVInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.DATASET, b.IEDNAME, b.DATADESC FROM svinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SVInfo::Ptr ptr(new SVInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SVInfo::List DBSVInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    SVInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.DATASET, b.IEDNAME, b.DATADESC FROM svinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
            .arg(iedName)
            .arg(setType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SVInfo::Ptr ptr(new SVInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBSVInfoDAO::doInsert(SVInfo::List &lst)
{
    bool bSucc = false;
    SVInfo::List::iterator iter = lst.begin();
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
                SVInfo::Ptr ptr(new SVInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dimension = ptr->dimension();
                QString dataSet = ptr->dataSet();

                sql = QObject::tr("REPLACE INTO svinfo VALUES(NULL, \"%1\", \"%2\", \"%3\")")
                        .arg(dataRef)
                        .arg(dimension)
                        .arg(dataSet);
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
                SVInfo::Ptr ptr(new SVInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dimension = ptr->dimension();
                QString dataSet = ptr->dataSet();

                sql = QObject::tr("REPLACE INTO svinfo VALUES(NULL, \"%1\", \"%2\", \"%3\")")
                        .arg(dataRef)
                        .arg(dimension)
                        .arg(dataSet);
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

bool DBSVInfoDAO::doUpdate(const SVInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE svinfo SET DATAREF=\"%1\", DATASET=\"%2\", DIMENSION=\"%3\" WHERE GUID=%4")
                .arg(ptr->dataRef())
                .arg(ptr->dataSet())
                .arg(ptr->dimension())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSVInfoDAO::doUpdate(SVInfo::List &lst)
{
    bool bSucc = false;

    SVInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            SVInfo::Ptr ptr(new SVInfo());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE svinfo SET DATAREF=\"%1\", DATASET=\"%2\", DIMENSION=\"%3\" WHERE GUID=%4")
                    .arg(ptr->dataRef())
                    .arg(ptr->dataSet())
                    .arg(ptr->dimension())
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

bool DBSVInfoDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM svinfo WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSVInfoDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE a FROM svinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSVInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM svinfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='svinfo'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSVInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS svinfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) UNIQUE NOT NULL,"
                                  "DIMENSION CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
