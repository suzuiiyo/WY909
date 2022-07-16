#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include "dbconnection.h"
#include "tmdatainfo.h"
#include "dbtmdatainfodao.h"
//#include "realdata.h"
//#include "dbrealdatadao.h"
#include "dbcolumntypetransform.h"
#include "dastruct.h"
#include "dbdastructdao.h"
DBTMDataInfoDAO::DBTMDataInfoDAO()
    : m_connectionName("connectTMDataInfo")
{
    doCreateTable();
}

DBTMDataInfoDAO::~DBTMDataInfoDAO()
{

}

TMDataInfo::List DBTMDataInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    TMDataInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tmdatainfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");

        QSqlQuery query(db);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                TMDataInfo::Ptr ptr(new TMDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
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

TMDataInfo::Ptr DBTMDataInfoDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tmdatainfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);

        QSqlQuery query(db);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                TMDataInfo::Ptr ptr(new TMDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
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

TMDataInfo::List DBTMDataInfoDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    TMDataInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tmdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);

        QSqlQuery query(db);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                TMDataInfo::Ptr ptr(new TMDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
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

TMDataInfo::List DBTMDataInfoDAO::doQuery(const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    TMDataInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tmdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
                .arg(iedName)
                .arg(setType);

        QSqlQuery query(db);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                TMDataInfo::Ptr ptr(new TMDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
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

TMDataInfo::List DBTMDataInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    TMDataInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tmdatainfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            TMDataInfo::Ptr ptr(new TMDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TMDataInfo::Ptr DBTMDataInfoDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tmdatainfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            TMDataInfo::Ptr ptr(new TMDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

TMDataInfo::List DBTMDataInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    TMDataInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tmdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            TMDataInfo::Ptr ptr(new TMDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TMDataInfo::List DBTMDataInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    TMDataInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tmdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
            .arg(iedName)
            .arg(setType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            TMDataInfo::Ptr ptr(new TMDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBTMDataInfoDAO::doInsert(TMDataInfo::List &lst)
{
    bool bSucc = false;
    TMDataInfo::List::iterator iter = lst.begin();
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
                TMDataInfo::Ptr ptr(new TMDataInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dimension = ptr->dimension();

                sql = QObject::tr("REPLACE INTO tmdatainfo VALUES(NULL, \"%1\", \"%2\")")
                        .arg(dataRef)
                        .arg(dimension);
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
                TMDataInfo::Ptr ptr(new TMDataInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dimension = ptr->dimension();

                sql = QObject::tr("REPLACE INTO tmdatainfo VALUES(NULL, \"%1\", \"%2\")")
                        .arg(dataRef)
                        .arg(dimension);
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

bool DBTMDataInfoDAO::doUpdate(const TMDataInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE tmdatainfo SET DATAREF=\"%1\", DIMENSION=\"%2\" WHERE GUID=%3")
                .arg(ptr->dataRef())
                .arg(ptr->dimension())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBTMDataInfoDAO::doUpdate(TMDataInfo::List &lst)
{
    bool bSucc = false;
    TMDataInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            TMDataInfo::Ptr ptr(new TMDataInfo());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE tmdatainfo SET DATAREF=\"%1\", DIMENSION=\"%2\" WHERE GUID=%3")
                    .arg(ptr->dataRef())
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

bool DBTMDataInfoDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM tmdatainfo WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBTMDataInfoDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE tmdatainfo FROM tmdatainfo, ieddataset WHERE ieddataset.IEDNAME=\"%1\" AND tmdatainfo.DATAREF=ieddataset.DATAREF")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBTMDataInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM tmdatainfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='tmdatainfo'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBTMDataInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS tmdatainfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) UNIQUE NOT NULL,"
                                  "DIMENSION CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
