#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include "dbconnection.h"
#include "gooseinfo.h"
#include "dbgooseinfodao.h"
#include "dastruct.h"
#include "dbdastructdao.h"
#include "dbcolumntypetransform.h"
DBGooseInfoDAO::DBGooseInfoDAO()
    : m_connectionName("connectGooseInfo")
{
    doCreateTable();
}

DBGooseInfoDAO::~DBGooseInfoDAO()
{

}

GooseInfo::List DBGooseInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    GooseInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                GooseInfo::Ptr ptr(new GooseInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_dataSetRef = query.value("DATASETREF").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
                ptr->m_appId = query.value("APPID").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

GooseInfo::List DBGooseInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    GooseInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            GooseInfo::Ptr ptr(new GooseInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_dataSetRef = query.value("DATASETREF").toString();
            ptr->m_appId = query.value("APPID").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

GooseInfo::Ptr DBGooseInfoDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            GooseInfo::Ptr ptr(new GooseInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_dataSetRef = query.value("DATASETREF").toString();
            ptr->m_appId = query.value("APPID").toString();
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

GooseInfo::List DBGooseInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    GooseInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            GooseInfo::Ptr ptr(new GooseInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_dataSetRef = query.value("DATASETREF").toString();
            ptr->m_appId = query.value("APPID").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

GooseInfo::List DBGooseInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    GooseInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
            .arg(iedName)
            .arg(setType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            GooseInfo::Ptr ptr(new GooseInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_dataSetRef = query.value("DATASETREF").toString();
            ptr->m_appId = query.value("APPID").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

GooseInfo::Ptr DBGooseInfoDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                GooseInfo::Ptr ptr(new GooseInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_dataSetRef = query.value("DATASETREF").toString();
                ptr->m_appId = query.value("APPID").toString();
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

GooseInfo::List DBGooseInfoDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    GooseInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                GooseInfo::Ptr ptr(new GooseInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_dataSetRef = query.value("DATASETREF").toString();
                ptr->m_appId = query.value("APPID").toString();
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

GooseInfo::List DBGooseInfoDAO::doQuery(const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    GooseInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
                .arg(iedName)
                .arg(setType);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                GooseInfo::Ptr ptr(new GooseInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_dataSetRef = query.value("DATASETREF").toString();
                ptr->m_appId = query.value("APPID").toString();
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

GooseInfo::List DBGooseInfoDAO::doQueryUsingIed(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    GooseInfo::List lst;
    QString sql = QObject::tr("SELECT a.IEDNAME, c.BAYID FROM gooseinfo a, primarydeviceinfo b, iedinfo c WHERE a.DEVNAME=b.DEVNAME AND a.IEDNAME=c.IEDNAME");
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            GooseInfo::Ptr ptr(new GooseInfo());
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_bayName = query.value("BAYID").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

GooseInfo * DBGooseInfoDAO::gooseInfo(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                GooseInfo *ptr = new GooseInfo();
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_dataSetRef = query.value("DATASETREF").toString();
                ptr->m_appId = query.value("APPID").toString();
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

GooseInfo *DBGooseInfoDAO::gooseInfo(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.DATASET, a.DATASETREF, a.APPID, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASETDESC FROM gooseinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            GooseInfo *ptr = new GooseInfo();
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_dataSetRef = query.value("DATASETREF").toString();
            ptr->m_appId = query.value("APPID").toString();
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

bool DBGooseInfoDAO::doInsert(GooseInfo::List &lst)
{
    bool bSucc = false;
    GooseInfo::List::iterator iter = lst.begin();
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
                GooseInfo::Ptr ptr(new GooseInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dataSet = ptr->dataSet();
                QString dimension = ptr->dimension();
                QString referenceValue = ptr->referenceValue();
                QString dataSetRef = ptr->dataSetRef();
                QString appId = ptr->appId();
                QString iedName = ptr->iedName();
                QString devName = ptr->devName();

                sql = QObject::tr("REPLACE INTO gooseinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\")")
                        .arg(dataRef)//1
                        .arg(dataSet)//2
                        .arg(dimension)//3
                        .arg(referenceValue)//4
                        .arg(dataSetRef)//5
                        .arg(appId)//6
                        .arg(iedName)//7
                        .arg(devName);//8
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
                GooseInfo::Ptr ptr(new GooseInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dataSet = ptr->dataSet();
                QString dimension = ptr->dimension();
                QString referenceValue = ptr->referenceValue();
                QString dataSetRef = ptr->dataSetRef();
                QString appId = ptr->appId();
                QString iedName = ptr->iedName();
                QString devName = ptr->devName();

                sql = QObject::tr("REPLACE INTO gooseinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\")")
                        .arg(dataRef)//1
                        .arg(dataSet)//2
                        .arg(dimension)//3
                        .arg(referenceValue)//4
                        .arg(dataSetRef)//5
                        .arg(appId)//6
                        .arg(iedName)//7
                        .arg(devName);//8
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

bool DBGooseInfoDAO::doUpdate(const GooseInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE gooseinfo SET DATAREF=\"%1\", DATASET=\"%2\", DIMENSION=\"%3\", REFERENCEVALUE=\"4\", DATASETREF=\"%5\", APPID=\"%6\", IEDNAME=\"%7\", DEVNAME=\"%8\" WHERE GUID=%9")
                .arg(ptr->dataRef())//1
                .arg(ptr->dataSet())//2
                .arg(ptr->dimension())//3
                .arg(ptr->referenceValue())//4
                .arg(ptr->dataSetRef())//5
                .arg(ptr->appId())//6
                .arg(ptr->iedName())//7
                .arg(ptr->devName())//8
                .arg(ptr->GUID());//9
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBGooseInfoDAO::doUpdate(GooseInfo::List &lst)
{
    bool bSucc = false;
    GooseInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            GooseInfo::Ptr ptr(new GooseInfo());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE gooseinfo SET DATAREF=\"%1\", DATASET=\"%2\", DIMENSION=\"%3\", REFERENCEVALUE=\"4\", DATASETREF=\"%5\", APPID=\"%6\", IEDNAME=\"%7\", DEVNAME=\"%8\" WHERE GUID=%9")
                    .arg(ptr->dataRef())//1
                    .arg(ptr->dataSet())//2
                    .arg(ptr->dimension())//3
                    .arg(ptr->referenceValue())//4
                    .arg(ptr->dataSetRef())//5
                    .arg(ptr->appId())//6
                    .arg(ptr->iedName())//7
                    .arg(ptr->devName())//8
                    .arg(ptr->GUID());//9
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

bool DBGooseInfoDAO::doUpdate(GooseInfo::List &lst, int type)
{
    bool bSucc = false;
    GooseInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        if(type == 0)
        {
            query.exec("begin transaction");

            while(iter < lst.end())
            {
                GooseInfo::Ptr ptr(new GooseInfo());
                ptr = *iter;
                QString sql = QObject::tr("UPDATE gooseinfo SET IEDNAME=\"%1\", DEVNAME=\"%2\" WHERE DATAREF=\"%3\"")
                        .arg(ptr->iedName())//1
                        .arg(ptr->devName())//2
                        .arg(ptr->dataRef());//3
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
        }
        db.close();
    }
    return bSucc;
}

bool DBGooseInfoDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM gooseinfo WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBGooseInfoDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE a FROM gooseinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBGooseInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM gooseinfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='gooseinfo'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBGooseInfoDAO::configGooseInfo()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT b.DATAREF, b.IEDNAME, b.DEVNAME FROM gooseinfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
        if(query.exec(sql))
        {
            GooseInfo::List lst;
            while(query.next())
            {
                QString dataRef = query.value("DATAREF").toString();
                QString iedName = query.value("IEDNAME").toString();
                QString devName = query.value("DEVNAME").toString();
                GooseInfo::Ptr ptr(new GooseInfo());
                ptr->setDataRef(dataRef);
                ptr->setIedName(iedName);
                ptr->setDevName(devName);
                lst.append(ptr);
            }
            bSucc = doUpdate(lst, 0);
        }
    }
    db.close();

    return bSucc;
}

bool DBGooseInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS gooseinfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) UNIQUE NOT NULL,"
                                  "DATASET CHAR(255) NOT NULL,"
                                  "DIMENSION CHAR(255) NOT NULL,"
                                  "REFERENCEVALUE CHAR(255) NOT NULL,"
                                  "DATASETREF CHAR(255) NOT NULL,"
                                  "APPID CHAR(255) NOT NULL,"
                                  "IEDNAME CHAR(255) NOT NULL,"
                                  "DEVNAME CHAR(255) NOT NULL,"
                                  "UNIQUE(DATAREF, DATASET)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
