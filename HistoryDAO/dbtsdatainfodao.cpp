#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QSqlQuery>
#include <QObject>
#include <QVariant>
#include "dbconnection.h"
#include "tsdatainfo.h"
#include "dbtsdatainfodao.h"
//#include "realdata.h"
//#include "dbrealdatadao.h"
#include "dbcolumntypetransform.h"
#include "dastruct.h"
#include "dbdastructdao.h"
DBTSDataInfoDAO::DBTSDataInfoDAO()
    : m_connectionName("connectTSDataInfo")
{
    doCreateTable();
}

DBTSDataInfoDAO::~DBTSDataInfoDAO()
{

}

TSDataInfo::List DBTSDataInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    TSDataInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tsdatainfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");

        QSqlQuery query(db);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                TSDataInfo::Ptr ptr(new TSDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TSDataInfo::Ptr DBTSDataInfoDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tsdatainfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);

        QSqlQuery query(db);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                TSDataInfo::Ptr ptr(new TSDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
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

TSDataInfo::List DBTSDataInfoDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    TSDataInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tsdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);

        QSqlQuery query(db);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                TSDataInfo::Ptr ptr(new TSDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TSDataInfo::List DBTSDataInfoDAO::doQuery(const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    TSDataInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tsdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
                .arg(iedName)
                .arg(setType);

        QSqlQuery query(db);

        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                TSDataInfo::Ptr ptr(new TSDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TSDataInfo::List DBTSDataInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    TSDataInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tsdatainfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            TSDataInfo::Ptr ptr(new TSDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TSDataInfo::Ptr DBTSDataInfoDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tsdatainfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            TSDataInfo::Ptr ptr(new TSDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

TSDataInfo::List DBTSDataInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    TSDataInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tsdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            TSDataInfo::Ptr ptr(new TSDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TSDataInfo::List DBTSDataInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    TSDataInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM tsdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
            .arg(iedName)
            .arg(setType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            TSDataInfo::Ptr ptr(new TSDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBTSDataInfoDAO::doInsert(TSDataInfo::List &lst)
{
    bool bSucc = false;
    TSDataInfo::List::iterator iter = lst.begin();
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
                TSDataInfo::Ptr ptr(new TSDataInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                sql = QObject::tr("REPLACE INTO tsdatainfo VALUES (NULL, \"%1\")")
                        .arg(dataRef);
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
                TSDataInfo::Ptr ptr(new TSDataInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();

                sql = QObject::tr("REPLACE INTO tsdatainfo VALUES (NULL, \"%1\")")
                        .arg(dataRef);
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

bool DBTSDataInfoDAO::doUpdate(const TSDataInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE tsdatainfo SET DATAREF=\"%1\" WHERE GUID=%2")
                .arg(ptr->dataRef())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBTSDataInfoDAO::doUpdate(TSDataInfo::List &lst)
{
    bool bSucc = false;

    TSDataInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");
        while(iter < lst.end())
        {
            TSDataInfo::Ptr ptr(new TSDataInfo());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE tsdatainfo SET DATAREF=\"%1\" WHERE GUID=%2")
                    .arg(ptr->dataRef())
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

bool DBTSDataInfoDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM tsdatainfo WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBTSDataInfoDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE tsdatainfo FROM tsdatainfo, ieddataset WHERE ieddataset.IEDNAME=\"%1\" AND tsdatainfo.DATAREF=ieddataset.DATAREF")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBTSDataInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM tsdatainfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='tsdatainfo'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBTSDataInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS tsdatainfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) UNIQUE NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
