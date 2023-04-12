#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVector>
#include <QVariant>
#include <QString>
#include <QList>
#include <QHash>
#include "dbconnection.h"
#include "strap.h"
#include "dbstraplightplatedao.h"
//#include "realdata.h"
//#include "dbrealdatadao.h"
#include "dbcolumntypetransform.h"
#include "dastruct.h"
#include "dbdastructdao.h"
DBStrapLightPlateDAO::DBStrapLightPlateDAO()
{
    doCreateTable();
}

DBStrapLightPlateDAO::~DBStrapLightPlateDAO()
{

}

Strap::List DBStrapLightPlateDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    Strap::List lstStrap;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Strap::Ptr strap(new Strap());
                strap->m_GUID = query.value("GUID").toInt();
                strap->m_iedName = query.value("IEDNAME").toString();
                strap->m_dataRef = query.value("DATAREF").toString();
                strap->m_dataDesc = query.value("DATADESC").toString();
                strap->m_strapType = query.value("STRAPTYPE").toString();
                strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
                strap->m_signalType = query.value("SIGNALTYPE").toString();
                strap->m_bayName = query.value("BAYNAME").toString();
                strap->m_dataSet = query.value("DATASET").toString();
                strap->m_dataSetDesc = query.value("DATASETDESC").toString();
                lstStrap.append(strap);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstStrap;
}

Strap::Ptr DBStrapLightPlateDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Strap::Ptr strap(new Strap());
                strap->m_GUID = query.value("GUID").toInt();
                strap->m_iedName = query.value("IEDNAME").toString();
                strap->m_dataRef = query.value("DATAREF").toString();
                strap->m_dataDesc = query.value("DATADESC").toString();
                strap->m_strapType = query.value("STRAPTYPE").toString();
                strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
                strap->m_signalType = query.value("SIGNALTYPE").toString();
                strap->m_bayName = query.value("BAYNAME").toString();
                strap->m_dataSet = query.value("DATASET").toString();
                strap->m_dataSetDesc = query.value("DATASETDESC").toString();
                if(ok)
                    *ok = bSucc;
                db.close();
                return strap;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

Strap::List DBStrapLightPlateDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    Strap::List lstStrap;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Strap::Ptr strap(new Strap());
                strap->m_GUID = query.value("GUID").toInt();
                strap->m_iedName = query.value("IEDNAME").toString();
                strap->m_dataRef = query.value("DATAREF").toString();
                strap->m_dataDesc = query.value("DATADESC").toString();
                strap->m_strapType = query.value("STRAPTYPE").toString();
                strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
                strap->m_signalType = query.value("SIGNALTYPE").toString();
                strap->m_bayName = query.value("BAYNAME").toString();
                strap->m_dataSet = query.value("DATASET").toString();
                strap->m_dataSetDesc = query.value("DATASETDESC").toString();
                lstStrap.append(strap);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstStrap;
}

Strap::List DBStrapLightPlateDAO::doQuery(const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    Strap::List lstStrap;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
                .arg(iedName)
                .arg(setType);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Strap::Ptr strap(new Strap());
                strap->m_GUID = query.value("GUID").toInt();
                strap->m_iedName = query.value("IEDNAME").toString();
                strap->m_dataRef = query.value("DATAREF").toString();
                strap->m_dataDesc = query.value("DATADESC").toString();
                strap->m_strapType = query.value("STRAPTYPE").toString();
                strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
                strap->m_signalType = query.value("SIGNALTYPE").toString();
                strap->m_bayName = query.value("BAYNAME").toString();
                strap->m_dataSet = query.value("DATASET").toString();
                strap->m_dataSetDesc = query.value("DATASETDESC").toString();
                lstStrap.append(strap);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstStrap;
}

QList<Strap*> DBStrapLightPlateDAO::doQueryLst(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QList<Strap*> lstStrap;

    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Strap *strap = new Strap();
                strap->m_GUID = query.value("GUID").toInt();
                strap->m_iedName = query.value("IEDNAME").toString();
                strap->m_dataRef = query.value("DATAREF").toString();
                strap->m_dataDesc = query.value("DATADESC").toString();
                strap->m_strapType = query.value("STRAPTYPE").toString();
                strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
                strap->m_signalType = query.value("SIGNALTYPE").toString();
                strap->m_bayName = query.value("BAYNAME").toString();
                strap->m_dataSet = query.value("DATASET").toString();
                strap->m_dataSetDesc = query.value("DATASETDESC").toString();
                lstStrap.append(strap);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstStrap;
}

Strap *DBStrapLightPlateDAO::strap(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);

    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Strap *strap = new Strap();
            strap->m_GUID = query.value("GUID").toInt();
            strap->m_iedName = query.value("IEDNAME").toString();
            strap->m_dataRef = query.value("DATAREF").toString();
            strap->m_dataDesc = query.value("DATADESC").toString();
            strap->m_strapType = query.value("STRAPTYPE").toString();
            strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
            strap->m_signalType = query.value("SIGNALTYPE").toString();
            strap->m_bayName = query.value("BAYNAME").toString();
            strap->m_dataSet = query.value("DATASET").toString();
            strap->m_dataSetDesc = query.value("DATASETDESC").toString();
            if(ok)
                *ok = bSucc;
            return strap;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

Strap * DBStrapLightPlateDAO::strap(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Strap *strap = new Strap();
                strap->m_GUID = query.value("GUID").toInt();
                strap->m_iedName = query.value("IEDNAME").toString();
                strap->m_dataRef = query.value("DATAREF").toString();
                strap->m_dataDesc = query.value("DATADESC").toString();
                strap->m_strapType = query.value("STRAPTYPE").toString();
                strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
                strap->m_signalType = query.value("SIGNALTYPE").toString();
                strap->m_bayName = query.value("BAYNAME").toString();
                strap->m_dataSet = query.value("DATASET").toString();
                strap->m_dataSetDesc = query.value("DATASETDESC").toString();
                if(ok)
                    *ok = bSucc;
                db.close();
                return strap;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

Strap::List DBStrapLightPlateDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    Strap::List lstStrap;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Strap::Ptr strap(new Strap());
            strap->m_GUID = query.value("GUID").toInt();
            strap->m_iedName = query.value("IEDNAME").toString();
            strap->m_dataRef = query.value("DATAREF").toString();
            strap->m_dataDesc = query.value("DATADESC").toString();
            strap->m_strapType = query.value("STRAPTYPE").toString();
            strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
            strap->m_signalType = query.value("SIGNALTYPE").toString();
            strap->m_bayName = query.value("BAYNAME").toString();
            strap->m_dataSet = query.value("DATASET").toString();
            strap->m_dataSetDesc = query.value("DATASETDESC").toString();
            lstStrap.append(strap);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstStrap;
}

Strap::Ptr DBStrapLightPlateDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Strap::Ptr strap(new Strap());
            strap->m_GUID = query.value("GUID").toInt();
            strap->m_iedName = query.value("IEDNAME").toString();
            strap->m_dataRef = query.value("DATAREF").toString();
            strap->m_dataDesc = query.value("DATADESC").toString();
            strap->m_strapType = query.value("STRAPTYPE").toString();
            strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
            strap->m_signalType = query.value("SIGNALTYPE").toString();
            strap->m_bayName = query.value("BAYNAME").toString();
            strap->m_dataSet = query.value("DATASET").toString();
            strap->m_dataSetDesc = query.value("DATASETDESC").toString();
            if(ok)
                *ok = bSucc;

            return strap;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

Strap::List DBStrapLightPlateDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    Strap::List lstStrap;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Strap::Ptr strap(new Strap());
            strap->m_GUID = query.value("GUID").toInt();
            strap->m_iedName = query.value("IEDNAME").toString();
            strap->m_dataRef = query.value("DATAREF").toString();
            strap->m_dataDesc = query.value("DATADESC").toString();
            strap->m_strapType = query.value("STRAPTYPE").toString();
            strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
            strap->m_signalType = query.value("SIGNALTYPE").toString();
            strap->m_bayName = query.value("BAYNAME").toString();
            strap->m_dataSet = query.value("DATASET").toString();
            strap->m_dataSetDesc = query.value("DATASETDESC").toString();
            lstStrap.append(strap);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstStrap;
}

Strap::List DBStrapLightPlateDAO::doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    Strap::List lstStrap;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
            .arg(iedName)
            .arg(setType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Strap::Ptr strap(new Strap());
            strap->m_GUID = query.value("GUID").toInt();
            strap->m_iedName = query.value("IEDNAME").toString();
            strap->m_dataRef = query.value("DATAREF").toString();
            strap->m_dataDesc = query.value("DATADESC").toString();
            strap->m_strapType = query.value("STRAPTYPE").toString();
            strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
            strap->m_signalType = query.value("SIGNALTYPE").toString();
            strap->m_bayName = query.value("BAYNAME").toString();
            strap->m_dataSet = query.value("DATASET").toString();
            strap->m_dataSetDesc = query.value("DATASETDESC").toString();
            lstStrap.append(strap);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstStrap;
}

QList<Strap *> DBStrapLightPlateDAO::doQueryLst(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QList<Strap*> lstStrap;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.STRAPTYPE, a.STRAPTYPEDETAIL, a.SIGNALTYPE, a.BAYNAME, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM strapinfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Strap *strap = new Strap();
            strap->m_GUID = query.value("GUID").toInt();
            strap->m_iedName = query.value("IEDNAME").toString();
            strap->m_dataRef = query.value("DATAREF").toString();
            strap->m_dataDesc = query.value("DATADESC").toString();
            strap->m_strapType = query.value("STRAPTYPE").toString();
            strap->m_strapTypeDetail = query.value("STRAPTYPEDETAIL").toString();
            strap->m_signalType = query.value("SIGNALTYPE").toString();
            strap->m_bayName = query.value("BAYNAME").toString();
            strap->m_dataSet = query.value("DATASET").toString();
            strap->m_dataSetDesc = query.value("DATASETDESC").toString();
            lstStrap.append(strap);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstStrap;
}

bool DBStrapLightPlateDAO::doInsert(Strap::List &lstStrap)
{
    bool bSucc = false;
    Strap::List::iterator iter = lstStrap.begin();
    int list_size = lstStrap.size();
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
            while(iter < lstStrap.end())
            {
                Strap::Ptr strap(new Strap());
                strap = *iter;

                QString dataRef = strap->dataRef();
                QString strapType = strap->strapType();
                QString strapTypeDetail = strap->strapTypeDetail();
                QString iedName = strap->iedName();
                QString signalType = strap->signalType();
                QString bayName = strap->bayName();

                sql = QObject::tr("REPLACE INTO strapinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\")")
                        .arg(dataRef)
                        .arg(iedName)
                        .arg(strapType)
                        .arg(strapTypeDetail)
                        .arg(signalType)
                        .arg(bayName);
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
            while(iter < lstStrap.end())
            {
                Strap::Ptr strap(new Strap());
                strap = *iter;

                QString dataRef = strap->dataRef();
                QString strapType = strap->strapType();
                QString strapTypeDetail = strap->strapTypeDetail();
                QString iedName = strap->iedName();
                QString signalType = strap->signalType();
                QString bayName = strap->bayName();

                sql = QObject::tr("REPLACE INTO strapinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\")")
                        .arg(dataRef)
                        .arg(iedName)
                        .arg(strapType)
                        .arg(strapTypeDetail)
                        .arg(signalType)
                        .arg(bayName);
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

bool DBStrapLightPlateDAO::doUpdate(const Strap::Ptr &strap)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE strapinfo SET DATAREF=\"%1\", IEDNAME=\"%2\", STRAPTYPE=\"%3\", STRAPTYPEDETAIL=\"%4\", SIGNALTYPE=\"%5\", BAYNAME=\"%6\" WHERE GUID=%7")
                .arg(strap->dataRef())
                .arg(strap->iedName())
                .arg(strap->strapType())
                .arg(strap->strapTypeDetail())
                .arg(strap->signalType())
                .arg(strap->bayName())
                .arg(strap->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBStrapLightPlateDAO::doUpdate(Strap::List &lstStrap)
{
    bool bSucc = false;
    Strap::List::iterator iter = lstStrap.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lstStrap.end())
        {
            Strap::Ptr strap(new Strap());
            strap = *iter;
            QString sql = QObject::tr("UPDATE strapinfo SET DATAREF=\"%1\", IEDNAME=\"%2\", STRAPTYPE=\"%3\", STRAPTYPEDETAIL=\"%4\", SIGNALTYPE=\"%5\", BAYNAME=\"%6\" WHERE GUID=%7")
                    .arg(strap->dataRef())
                    .arg(strap->iedName())
                    .arg(strap->strapType())
                    .arg(strap->strapTypeDetail())
                    .arg(strap->signalType())
                    .arg(strap->bayName())
                    .arg(strap->GUID());
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


bool DBStrapLightPlateDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM strapinfo WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBStrapLightPlateDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE a FROM strapinfo a, ieddataset b WHERE IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}


bool DBStrapLightPlateDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM strapinfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='strapinfo'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBStrapLightPlateDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS strapinfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) UNIQUE NOT NULL,"
                                  "IEDNAME CHAR(255) NOT NULL,"
                                  "STRAPTYPE CHAR(255) NOT NULL,"
                                  "STRAPTYPEDETAIL CHAR(255) NOT NULL,"
                                  "SIGNALTYPE CHAR(255) NOT NULL,"
                                  "BAYNAME CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}


