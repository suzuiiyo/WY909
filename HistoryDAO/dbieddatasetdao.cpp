#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QList>
#include <QByteArray>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "ieddataset.h"
#include "dbconnection.h"
#include "dbiedinfodao.h"
#include "dbieddatasetdao.h"
#include "dbtsdatainfodao.h"
#include "dbeventinfodao.h"
#include "dbalarminfodao.h"
#include "dbdevrunstatedao.h"
#include "dbotherdatainfodao.h"
#include "dbtmdatainfodao.h"
#include "dbsettingdao.h"
#include "dbstraplightplatedao.h"
#include "dbrcdinfodao.h"
#include "dbgooseinfodao.h"
#include "dbsvinfodao.h"
#include "dbindicatorlampdao.h"
#include "dbdastructdao.h"
#include "dbanaconfigdao.h"
#include "dbsteadytasktmconfigdao.h"
#include "dbsteadytasktsconfigdao.h"
#include "dbtransienttasktmconfigdao.h"
#include "dbtransienttasktsconfigdao.h"
#include "dbdiagnosisofprotoperateconfigdao.h"
#include "dbearlywarningconfigdao.h"
DBIedDataSetDAO::DBIedDataSetDAO()
    : m_connectionName("ConnectIedDataSet")
{
    doCreateTable();
}

DBIedDataSetDAO::~DBIedDataSetDAO()
{
    //clearIedDataSet();
}

int DBIedDataSetDAO::select_guid(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    int guid = -1;
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT GUID FROM ieddataset WHERE DATAREF = \"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
                guid = query.value("GUID").toInt();
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return guid;
}

IedDataSet::List DBIedDataSetDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM ieddataset");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet->m_GUID = query.value("GUID").toInt();
                iedDataSet->m_iedName = query.value("IEDNAME").toString();
                iedDataSet->m_dataRef = query.value("DATAREF").toString();
                iedDataSet->m_dataDesc = query.value("DATADESC").toString();
                iedDataSet->m_LDevice = query.value("LDEVICE").toString();
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                iedDataSet->m_dataType = query.value("DATATYPE").toString();
                iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
                iedDataSet->m_devName = query.value("DEVNAME").toString();
                iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
                iedDataSet->m_business = query.value("BUSINESS").toString();
                iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
                lstIedDataSet.append(iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QString sql = QObject::tr("SELECT * FROM ieddataset");
    QSqlQuery query(db);
    if(query.exec(sql))
    {
        while(query.next())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet());
            iedDataSet->m_GUID = query.value("GUID").toInt();
            iedDataSet->m_iedName = query.value("IEDNAME").toString();
            iedDataSet->m_dataRef = query.value("DATAREF").toString();
            iedDataSet->m_dataDesc = query.value("DATADESC").toString();
            iedDataSet->m_LDevice = query.value("LDEVICE").toString();
            iedDataSet->m_dataSet = query.value("DATASET").toString();
            iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
            iedDataSet->m_dataType = query.value("DATATYPE").toString();
            iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
            iedDataSet->m_devName = query.value("DEVNAME").toString();
            iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
            iedDataSet->m_business = query.value("BUSINESS").toString();
            iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
            lstIedDataSet.append(iedDataSet);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM ieddataset WHERE DATAREF = \"%1\"")
                .arg(dataRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet->m_GUID = query.value("GUID").toInt();
                iedDataSet->m_iedName = query.value("IEDNAME").toString();
                iedDataSet->m_dataRef = query.value("DATAREF").toString();
                iedDataSet->m_dataDesc = query.value("DATADESC").toString();
                iedDataSet->m_LDevice = query.value("LDEVICE").toString();
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                iedDataSet->m_dataType = query.value("DATATYPE").toString();
                iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
                iedDataSet->m_devName = query.value("DEVNAME").toString();
                iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
                iedDataSet->m_business = query.value("BUSINESS").toString();
                iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
                lstIedDataSet.append(iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QString sql = QObject::tr("SELECT * FROM ieddataset WHERE DATAREF = \"%1\"")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet());
            iedDataSet->m_GUID = query.value("GUID").toInt();
            iedDataSet->m_iedName = query.value("IEDNAME").toString();
            iedDataSet->m_dataRef = query.value("DATAREF").toString();
            iedDataSet->m_dataDesc = query.value("DATADESC").toString();
            iedDataSet->m_LDevice = query.value("LDEVICE").toString();
            iedDataSet->m_dataSet = query.value("DATASET").toString();
            iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
            iedDataSet->m_dataType = query.value("DATATYPE").toString();
            iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
            iedDataSet->m_devName = query.value("DEVNAME").toString();
            iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
            iedDataSet->m_business = query.value("BUSINESS").toString();
            iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
            lstIedDataSet.append(iedDataSet);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}


IedDataSet::List DBIedDataSetDAO::doQueryByIedName(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME = \"%1\"")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet->m_GUID = query.value("GUID").toInt();
                iedDataSet->m_iedName = query.value("IEDNAME").toString();
                iedDataSet->m_dataRef = query.value("DATAREF").toString();
                iedDataSet->m_dataDesc = query.value("DATADESC").toString();
                iedDataSet->m_LDevice = query.value("LDEVICE").toString();
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                iedDataSet->m_dataType = query.value("DATATYPE").toString();
                iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
                iedDataSet->m_devName = query.value("DEVNAME").toString();
                iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
                iedDataSet->m_business = query.value("BUSINESS").toString();
                iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
                lstIedDataSet.append(iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME = \"%1\"")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet());
            iedDataSet->m_GUID = query.value("GUID").toInt();
            iedDataSet->m_iedName = query.value("IEDNAME").toString();
            iedDataSet->m_dataRef = query.value("DATAREF").toString();
            iedDataSet->m_dataDesc = query.value("DATADESC").toString();
            iedDataSet->m_LDevice = query.value("LDEVICE").toString();
            iedDataSet->m_dataSet = query.value("DATASET").toString();
            iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
            iedDataSet->m_dataType = query.value("DATATYPE").toString();
            iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
            iedDataSet->m_devName = query.value("DEVNAME").toString();
            iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
            iedDataSet->m_business = query.value("BUSINESS").toString();
            iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
            lstIedDataSet.append(iedDataSet);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByLDevice(const QString &iedName, const QString &LDevice, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME = \"%1\" AND LDEVICE = \"%2\"")
                .arg(iedName)
                .arg(LDevice);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet->m_GUID = query.value("GUID").toInt();
                iedDataSet->m_iedName = query.value("IEDNAME").toString();
                iedDataSet->m_dataRef = query.value("DATAREF").toString();
                iedDataSet->m_dataDesc = query.value("DATADESC").toString();
                iedDataSet->m_LDevice = query.value("LDEVICE").toString();
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                iedDataSet->m_dataType = query.value("DATATYPE").toString();
                iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
                iedDataSet->m_devName = query.value("DEVNAME").toString();
                iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
                iedDataSet->m_business = query.value("BUSINESS").toString();
                iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
                lstIedDataSet.append(iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByLDevice(QSqlDatabase db, const QString &iedName, const QString &LDevice, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME = \"%1\" AND LDEVICE = \"%2\"")
            .arg(iedName)
            .arg(LDevice);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet());
            iedDataSet->m_GUID = query.value("GUID").toInt();
            iedDataSet->m_iedName = query.value("IEDNAME").toString();
            iedDataSet->m_dataRef = query.value("DATAREF").toString();
            iedDataSet->m_dataDesc = query.value("DATADESC").toString();
            iedDataSet->m_LDevice = query.value("LDEVICE").toString();
            iedDataSet->m_dataSet = query.value("DATASET").toString();
            iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
            iedDataSet->m_dataType = query.value("DATATYPE").toString();
            iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
            iedDataSet->m_devName = query.value("DEVNAME").toString();
            iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
            iedDataSet->m_business = query.value("BUSINESS").toString();
            iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
            lstIedDataSet.append(iedDataSet);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByDataSet(const QString &iedName, const QString &dataSet, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME = \"%1\" AND DATASET = \"%2\"")
                .arg(iedName)
                .arg(dataSet);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet->m_GUID = query.value("GUID").toInt();
                iedDataSet->m_iedName = query.value("IEDNAME").toString();
                iedDataSet->m_dataRef = query.value("DATAREF").toString();
                iedDataSet->m_dataDesc = query.value("DATADESC").toString();
                iedDataSet->m_LDevice = query.value("LDEVICE").toString();
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                iedDataSet->m_dataType = query.value("DATATYPE").toString();
                iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
                iedDataSet->m_devName = query.value("DEVNAME").toString();
                iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
                iedDataSet->m_business = query.value("BUSINESS").toString();
                iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
                lstIedDataSet.append(iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByDataSet(QSqlDatabase db, const QString &iedName, const QString &dataSet, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME = \"%1\" AND DATASET = \"%2\"")
            .arg(iedName)
            .arg(dataSet);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet());
            iedDataSet->m_GUID = query.value("GUID").toInt();
            iedDataSet->m_iedName = query.value("IEDNAME").toString();
            iedDataSet->m_dataRef = query.value("DATAREF").toString();
            iedDataSet->m_dataDesc = query.value("DATADESC").toString();
            iedDataSet->m_LDevice = query.value("LDEVICE").toString();
            iedDataSet->m_dataSet = query.value("DATASET").toString();
            iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
            iedDataSet->m_dataType = query.value("DATATYPE").toString();
            iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
            iedDataSet->m_devName = query.value("DEVNAME").toString();
            iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
            iedDataSet->m_business = query.value("BUSINESS").toString();
            iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
            lstIedDataSet.append(iedDataSet);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByDataType(const QString &iedName, const QString &dataType, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME = \"%1\" AND DATATYPE = \"%2\"")
                .arg(iedName)
                .arg(dataType);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet->m_GUID = query.value("GUID").toInt();
                iedDataSet->m_iedName = query.value("IEDNAME").toString();
                iedDataSet->m_dataRef = query.value("DATAREF").toString();
                iedDataSet->m_dataDesc = query.value("DATADESC").toString();
                iedDataSet->m_LDevice = query.value("LDEVICE").toString();
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                iedDataSet->m_dataType = query.value("DATATYPE").toString();
                iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
                iedDataSet->m_devName = query.value("DEVNAME").toString();
                iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
                iedDataSet->m_business = query.value("BUSINESS").toString();
                iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
                lstIedDataSet.append(iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByDataType(QSqlDatabase db, const QString &iedName, const QString &dataType, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME = \"%1\" AND DATATYPE = \"%2\"")
            .arg(iedName)
            .arg(dataType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet());
            iedDataSet->m_GUID = query.value("GUID").toInt();
            iedDataSet->m_iedName = query.value("IEDNAME").toString();
            iedDataSet->m_dataRef = query.value("DATAREF").toString();
            iedDataSet->m_dataDesc = query.value("DATADESC").toString();
            iedDataSet->m_LDevice = query.value("LDEVICE").toString();
            iedDataSet->m_dataSet = query.value("DATASET").toString();
            iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
            iedDataSet->m_dataType = query.value("DATATYPE").toString();
            iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
            iedDataSet->m_devName = query.value("DEVNAME").toString();
            iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
            iedDataSet->m_business = query.value("BUSINESS").toString();
            iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
            lstIedDataSet.append(iedDataSet);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByEarlyWarningType(const QString &iedName, int earlyWarningType, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME=\"%1\" AND EARLYWARNINGTYPE=%2")
                .arg(iedName)
                .arg(earlyWarningType);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet->m_GUID = query.value("GUID").toInt();
                iedDataSet->m_iedName = iedName;
                iedDataSet->m_dataRef = query.value("DATAREF").toString();
                iedDataSet->m_dataDesc = query.value("DATADESC").toString();
                iedDataSet->m_LDevice = query.value("LDEVICE").toString();
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                iedDataSet->m_dataType = query.value("DATATYPE").toString();
                iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
                iedDataSet->m_devName = query.value("DEVNAME").toString();
                iedDataSet->m_earlyWarningType = earlyWarningType;
                iedDataSet->m_business = query.value("BUSINESS").toString();
                iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
                lstIedDataSet.append(iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByEarlyWarningType(QSqlDatabase db, const QString &iedName, int earlyWarningType, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME=\"%1\" AND EARLYWARNINGTYPE=%2")
            .arg(iedName)
            .arg(earlyWarningType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet());
            iedDataSet->m_GUID = query.value("GUID").toInt();
            iedDataSet->m_iedName = iedName;
            iedDataSet->m_dataRef = query.value("DATAREF").toString();
            iedDataSet->m_dataDesc = query.value("DATADESC").toString();
            iedDataSet->m_LDevice = query.value("LDEVICE").toString();
            iedDataSet->m_dataSet = query.value("DATASET").toString();
            iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
            iedDataSet->m_dataType = query.value("DATATYPE").toString();
            iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
            iedDataSet->m_devName = query.value("DEVNAME").toString();
            iedDataSet->m_earlyWarningType = earlyWarningType;
            iedDataSet->m_business = query.value("BUSINESS").toString();
            iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
            lstIedDataSet.append(iedDataSet);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::Hash DBIedDataSetDAO::doQueryByEarlyWarningTypeHash(const QString &iedName, int earlyWarningType, bool *ok)
{
    bool bSucc = false;
    IedDataSet::Hash hashIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM ieddataset WHERE IEDNAME=\"%1\" AND EARLYWARNINGTYPE=%2")
                .arg(iedName)
                .arg(earlyWarningType);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet->m_GUID = query.value("GUID").toInt();
                iedDataSet->m_iedName = iedName;
                iedDataSet->m_dataRef = query.value("DATAREF").toString();
                iedDataSet->m_dataDesc = query.value("DATADESC").toString();
                iedDataSet->m_LDevice = query.value("LDEVICE").toString();
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                iedDataSet->m_dataType = query.value("DATATYPE").toString();
                iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
                iedDataSet->m_devName = query.value("DEVNAME").toString();
                iedDataSet->m_earlyWarningType = earlyWarningType;
                iedDataSet->m_business = query.value("BUSINESS").toString();
                iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
                if(!hashIedDataSet.contains(iedDataSet->dataRef()))
                    hashIedDataSet.insert(iedDataSet->dataRef(), iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hashIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByDevName(const QString &devName, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM ieddataset WHERE DEVNAME = \"%1\"")
                .arg(devName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet->m_GUID = query.value("GUID").toInt();
                iedDataSet->m_iedName = query.value("IEDNAME").toString();
                iedDataSet->m_dataRef = query.value("DATAREF").toString();
                iedDataSet->m_dataDesc = query.value("DATADESC").toString();
                iedDataSet->m_LDevice = query.value("LDEVICE").toString();
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                iedDataSet->m_dataType = query.value("DATATYPE").toString();
                iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
                iedDataSet->m_devName = query.value("DEVNAME").toString();
                iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
                iedDataSet->m_business = query.value("BUSINESS").toString();
                iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
                lstIedDataSet.append(iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQueryByDevName(QSqlDatabase db, const QString &devName, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QString sql = QObject::tr("SELECT * FROM ieddataset WHERE DEVNAME = \"%1\"")
            .arg(devName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet());
            iedDataSet->m_GUID = query.value("GUID").toInt();
            iedDataSet->m_iedName = query.value("IEDNAME").toString();
            iedDataSet->m_dataRef = query.value("DATAREF").toString();
            iedDataSet->m_dataDesc = query.value("DATADESC").toString();
            iedDataSet->m_LDevice = query.value("LDEVICE").toString();
            iedDataSet->m_dataSet = query.value("DATASET").toString();
            iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
            iedDataSet->m_dataType = query.value("DATATYPE").toString();
            iedDataSet->m_dataUnit = query.value("DATAUNIT").toString();
            iedDataSet->m_devName = query.value("DEVNAME").toString();
            iedDataSet->m_earlyWarningType = query.value("EARLYWARNINGTYPE").toInt();
            iedDataSet->m_business = query.value("BUSINESS").toString();
            iedDataSet->m_dataValueType = query.value("DATAVALUETYPE").toString();
            lstIedDataSet.append(iedDataSet);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQuerySet(const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT DISTINCT a.DATASET, a.DATASETDESC FROM ieddataset a, %1 b WHERE a.IEDNAME = \"%2\" AND b.DATAREF=a.DATAREF")
                .arg(setType)
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet(iedName,"","","","",""));
                iedDataSet->m_dataSet = query.value("DATASET").toString();
                iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
                lstIedDataSet.append(iedDataSet);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

IedDataSet::List DBIedDataSetDAO::doQuerySet(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    IedDataSet::List lstIedDataSet;
    QString sql = QObject::tr("SELECT DISTINCT a.DATASET, a.DATASETDESC FROM ieddataset a, %1 b WHERE a.IEDNAME = \"%2\" AND b.DATAREF=a.DATAREF")
            .arg(setType)
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet(iedName,"","","","",""));
            iedDataSet->m_dataSet = query.value("DATASET").toString();
            iedDataSet->m_dataSetDesc = query.value("DATASETDESC").toString();
            lstIedDataSet.append(iedDataSet);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIedDataSet;
}

MemoryFCDA::Hash DBIedDataSetDAO::doQueryMemoryFCDA(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    MemoryFCDA::Hash hsh;
    QString sql = QObject::tr("SELECT DATAREF, DATADESC FROM ieddataset WHERE IEDNAME=\"%1\"")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            MemoryFCDA *ptr = new MemoryFCDA();
            ptr->m_refName = query.value("DATAREF").toString();
            ptr->m_fcdaDesc = query.value("DATADESC").toString();
            if(hsh.count(ptr->refName()) == 0)
                hsh.insert(ptr->refName(), ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

bool DBIedDataSetDAO::doInsert(IedDataSet::List &lstIedDataSet)
{
    bool bSucc = false;
    IedDataSet::List::iterator iter = lstIedDataSet.begin();
    int list_size = lstIedDataSet.size();
    if(list_size == 0)
        return true;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        query.exec("begin transaction");

        if(list_size <= 1000){
            while(iter < lstIedDataSet.end())
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet = *iter;

                QString iedName = iedDataSet->iedName();
                QString dataRef = iedDataSet->dataRef();
                QString dataDesc = iedDataSet->dataDesc();
                QString LDevice = iedDataSet->LDevice();
                QString dataSet = iedDataSet->dataSet();
                QString dataSetDesc = iedDataSet->dataSetDesc();
                QString dataType = iedDataSet->dataType();
                QString dataUnit = iedDataSet->dataUnit();
                QString devName = iedDataSet->devName();
                int earlyWarningType = -1;
                QString business = iedDataSet->business();
                QString dataValueType = iedDataSet->dataValueType();

                sql = QObject::tr("INSERT INTO ieddataset VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\", \"%9\", %10, \"%11\", \"%12\")")
                        .arg(iedName)//1
                        .arg(dataRef)//2
                        .arg(dataDesc)//3
                        .arg(LDevice)//4
                        .arg(dataSet)//5
                        .arg(dataSetDesc)//6
                        .arg(dataType)//7
                        .arg(dataUnit)//8
                        .arg(devName)//9
                        .arg(earlyWarningType)//10
                        .arg(business)//11
                        .arg(dataValueType);//12
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
            while(iter < lstIedDataSet.end())
            {
                //QString sql_str_tmp = "";
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet = *iter;

                QString iedName = iedDataSet->iedName();
                QString dataRef = iedDataSet->dataRef();
                QString dataDesc = iedDataSet->dataDesc();
                QString LDevice = iedDataSet->LDevice();
                QString dataSet = iedDataSet->dataSet();
                QString dataSetDesc = iedDataSet->dataSetDesc();
                QString dataType = iedDataSet->dataType();
                QString dataUnit = iedDataSet->dataUnit();
                QString devName = iedDataSet->devName();
                int earlyWarningType = -1;
                QString business = iedDataSet->business();
                QString dataValueType = iedDataSet->dataValueType();

                sql = QObject::tr("INSERT INTO ieddataset VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\", \"%9\", %10, \"%11\", \"%12\")")
                        .arg(iedName)//1
                        .arg(dataRef)//2
                        .arg(dataDesc)//3
                        .arg(LDevice)//4
                        .arg(dataSet)//5
                        .arg(dataSetDesc)//6
                        .arg(dataType)//7
                        .arg(dataUnit)//8
                        .arg(devName)//9
                        .arg(earlyWarningType)//10
                        .arg(business)//11
                        .arg(dataValueType);//12
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


bool DBIedDataSetDAO::doUpdate(const IedDataSet::Ptr &iedDataSet)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE ieddataset SET IEDNAME=\"%1\", DATAREF=\"%2\", DATADESC=\"%3\", LDEVICE=\"%4\", DATASET=\"%5\", DATASETDESC=\"%6\", DATATYPE=\"%7\", DATAUNIT=\"%8\", DEVNAME=\"%9\", EARLYWARNINGTYPE=%10, DATAVALUETYPE=\"%11\" WHERE GUID=%12")
                .arg(iedDataSet->iedName())
                .arg(iedDataSet->dataRef())
                .arg(iedDataSet->dataDesc())
                .arg(iedDataSet->LDevice())
                .arg(iedDataSet->dataSet())
                .arg(iedDataSet->dataSetDesc())
                .arg(iedDataSet->dataType())
                .arg(iedDataSet->dataUnit())
                .arg(iedDataSet->devName())
                .arg(iedDataSet->earlyWarningType())
                .arg(iedDataSet->dataValueType())
                .arg(iedDataSet->GUID());

        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBIedDataSetDAO::doUpdate(IedDataSet::List &lstIedDataSet)
{
    bool bSucc = false;
    if(lstIedDataSet.size() == 0)
        return bSucc;

    IedDataSet::List::iterator iter = lstIedDataSet.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");
        QString sql = "";

        while(iter < lstIedDataSet.end())
        {
            IedDataSet::Ptr iedDataSet(new IedDataSet());
            iedDataSet = *iter;

            sql = QObject::tr("UPDATE ieddataset SET IEDNAME=\"%1\", DATAREF=\"%2\", DATADESC=\"%3\", LDEVICE=\"%4\", DATASET=\"%5\", DATASETDESC=\"%6\", DATATYPE=\"%7\", DATAUNIT=\"%8\", DEVNAME=\"%9\", EARLYWARNINGTYPE=%10, DATAVALUETYPE=\"%11\" WHERE GUID=%12")
                    .arg(iedDataSet->iedName())
                    .arg(iedDataSet->dataRef())
                    .arg(iedDataSet->dataDesc())
                    .arg(iedDataSet->LDevice())
                    .arg(iedDataSet->dataSet())
                    .arg(iedDataSet->dataSetDesc())
                    .arg(iedDataSet->dataType())
                    .arg(iedDataSet->dataUnit())
                    .arg(iedDataSet->devName())
                    .arg(iedDataSet->earlyWarningType())
                    .arg(iedDataSet->dataValueType())
                    .arg(iedDataSet->GUID());
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: update ieddatset(lst), %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }
            iter++;
        }
        bSucc = query.exec("commit transaction");

        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: commit, %s", error_s.toStdString().data());
        }
        db.close();
    }
    return bSucc;
}

bool DBIedDataSetDAO::doUpdate(IedDataSet::List &lstIedDataSet, int type)
{
    bool bSucc = false;
    if(lstIedDataSet.size() == 0)
        return bSucc;

    IedDataSet::List::iterator iter;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = "";

        //update DEVNAME by DATAREF
        if(type == 0)
        {
            query.exec("begin transaction");
            for(iter=lstIedDataSet.begin(); iter!=lstIedDataSet.end(); iter++)
            {
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet = *iter;

                if(iedDataSet->dataRef() == "")
                {
                    sql = QObject::tr("UPDATE ieddataset SET DEVNAME=\"\" WHERE DEVNAME=\"%1\"")
                                    .arg(iedDataSet->devName());
                }
                else
                {
                    sql = QObject::tr("UPDATE ieddataset SET DEVNAME=\"%1\" WHERE DATAREF=\"%2\"")
                                    .arg(iedDataSet->devName())
                                    .arg(iedDataSet->dataRef());
                }

                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: update ieddataset(type=0), %s", error_s.toStdString().data());
                    db.close();
                    return bSucc;
                }
            }

            bSucc = query.exec("commit transaction");
            if(!bSucc)
            {
                QString error_s = query.lastError().text();
                printf("error: commit(type=0), %s", error_s.toStdString().data());
            }
        }

        if(type == 1)
        {
            //IedDataSet::List lst_old = doQueryByEarlyWarningType()
            IedDataSet::Hash hsh_new;

            for(iter=lstIedDataSet.begin(); iter!=lstIedDataSet.end(); iter++)
            {
                if(iter == lstIedDataSet.begin())
                    query.exec("begin transaction");
                IedDataSet::Ptr iedDataSet(new IedDataSet());
                iedDataSet = *iter;

                sql = QObject::tr("UPDATE ieddataset SET EARLYWARNINGTYPE=%1 WHERE DATAREF=\"%2\"")
                        .arg(iedDataSet->earlyWarningType())
                        .arg(iedDataSet->dataRef());

                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: update ieddataset(type=0), %s", error_s.toStdString().data());
                    db.close();
                    return bSucc;
                }

                if(!hsh_new.contains(iedDataSet->dataRef()))
                    hsh_new.insert(iedDataSet->dataRef(), iedDataSet);

                //commit and deal old earl-warning type
                if(iter == lstIedDataSet.end()-1)
                {
                    bSucc = query.exec("commit transaction");
                    if(!bSucc)
                    {
                        QString error_s = query.lastError().text();
                        printf("error: commit(type=1), %s", error_s.toStdString().data());
                    }
                    IedDataSet::Hash hsh_old = doQueryByEarlyWarningTypeHash(iedDataSet->iedName(), iedDataSet->earlyWarningType());

                    if(hsh_old.size() != 0)
                    {
                        IedDataSet::List lst_dealOld;
                        IedDataSet::Hash::const_iterator iter_old;
                        //IedDataSet::Hash::const_iterator iter_new = hsh_new.begin();
                        for(iter_old=hsh_old.begin(); iter_old!=hsh_old.end(); iter_old++)
                        {
                            if(!hsh_new.contains(iter_old.key()))
                            {
                                IedDataSet::Ptr ptr_old = hsh_old.value(iter_old.key());
                                ptr_old->setEarlyWarningType(-1);
                                lst_dealOld.append(ptr_old);
                            }
                        }
                        doUpdate(lst_dealOld);
                    }
                }
            }
        }

        if(type == 2)
        {
            query.exec("begin transaction");
            for(iter=lstIedDataSet.begin(); iter!=lstIedDataSet.end(); iter++)
            {
                IedDataSet::Ptr ptr(new IedDataSet());
                ptr = *iter;
                QString sql = QObject::tr("UPDATE ieddataset SET BUSINESS=\"%1\" WHERE DATAREF=\"%2\"")
                        .arg(ptr->business())
                        .arg(ptr->dataRef());
                bSucc = query.exec(sql);
                if(!bSucc)
                {
                    QString error_s = query.lastError().text();
                    printf("error: commit(type=0), %s", error_s.toStdString().data());
                }
            }
            bSucc = query.exec("commit transaction");
            if(!bSucc)
            {
                QString error_s = query.lastError().text();
                printf("error: commit(type=0), %s", error_s.toStdString().data());
            }
        }
        db.close();
    }
    return bSucc;
}

bool DBIedDataSetDAO::doDelete(int dataSetGUID)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM ieddataset WHERE GUID=%1")
                .arg(dataSetGUID);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBIedDataSetDAO::doDelete(QList<int> lstDataSetGUID)
{
    QList<int>::iterator iter = lstDataSetGUID.begin();
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    int lst_size = lstDataSetGUID.size();
    if(lst_size != 0)
        return bSucc;
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        for(iter = lstDataSetGUID.begin(); iter != lstDataSetGUID.end(); iter++)
        {
            int guid = *iter;
            sql = QObject::tr("DELETE FROM ieddataset WHERE GUID=%1")
                    .arg(guid);
            if(!query.exec(sql))
                return bSucc;
        }
        bSucc = true;
        db.close();
    }
    return bSucc;
}

bool DBIedDataSetDAO::doDelete(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM ieddataset WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBIedDataSetDAO::doDelete(QList<QString> &lstIedName)
{
    QList<QString>::iterator iter = lstIedName.begin();
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    int lst_size = lstIedName.size();
    if(lst_size != 0)
        return bSucc;
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        for(iter = lstIedName.begin(); iter != lstIedName.end(); iter++)
        {
            QString iedName = *iter;
            sql = QObject::tr("DELETE FROM ieddataset WHERE IEDNAME=\"%1\"")
                    .arg(iedName);
            if(!query.exec(sql))
                return bSucc;
        }
        bSucc = true;
        db.close();
    }
    return bSucc;
}

bool DBIedDataSetDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM ieddataset");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='ieddataset'");
        bSucc = query.exec(sql);

        DBTSDataInfoDAO dao_ts;
        dao_ts.doClear();

        DBEventInfoDAO dao_event;
        dao_event.doClear();

        DBAlarmInfoDAO dao_alarm;
        dao_alarm.doClear();

        DBDevRunStateDAO dao_run;
        dao_run.doClear();

        DBOtherDataInfoDAO dao_other;
        dao_other.doClear();

        DBTMDataInfoDAO dao_tm;
        dao_tm.doClear();

        DBSettingDAO dao_setting;
        dao_setting.doClear();

        DBStrapLightPlateDAO dao_strap;
        dao_strap.doClear();

        DBRCDInfoDAO dao_rcd;
        dao_rcd.doClear();

        DBGooseInfoDAO dao_goose;
        dao_goose.doClear();

        DBSVInfoDAO dao_sv;
        dao_sv.doClear();

        DBIndicatorLampDAO dao_lamp;
        dao_lamp.doClear();

        DBDAStructDAO dao_da;
        dao_da.doClear();

        DBAnaConfigDAO dao_ana;
        dao_ana.doClear();

        DBSteadyTaskTMConfigDAO dao_steadyTaskTM;
        dao_steadyTaskTM.doClear();

        DBSteadyTaskTSConfigDAO dao_steadyTaskTS;
        dao_steadyTaskTS.doClear();

        DBTransientTaskTMConfigDAO dao_transientTaskTM;
        dao_transientTaskTM.doClear();

        DBTransientTaskTSConfigDAO dao_transientTaskTS;
        dao_transientTaskTS.doClear();

        DBDiagnosisOfProtOperateConfigDAO dao_dopoc;
        dao_dopoc.doClear();

        DBEarlyWarningConfigDAO dao_ew;
        dao_ew.doClear();

        db.close();
    }
    return bSucc;
}

//bool DBIedDataSetDAO::doClear(IedDataSet::List &lstIedDataSet, int type)
//{
//    bool bSucc = false;

//    IedDataSet::List::iterator iter = lstIedDataSet.begin();
//    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

//    if(db.isOpen() || db.open())
//    {
//        QSqlQuery query(db);
//        query.exec("begin transaction");
//        QString sql = "";

//        //update DEVNAME by DATAREF
//        if(type == 0)
//        {
//            while(iter < lstIedDataSet.end())
//            {
//                IedDataSet::Ptr iedDataSet(new IedDataSet());
//                iedDataSet = *iter;

//                sql = QObject::tr("UPDATE ieddataset SET DEVNAME="" WHERE DEVNAME=\"%1\"")
//                                .arg(iedDataSet->devName();
//                if(!query.exec(sql))
//                {
//                    QString error_s = query.lastError().text();
//                    printf("error: %s", error_s.toStdString().data());
//                    db.close();
//                    return bSucc;
//                }
//                iter++;
//            }
//        }

//        bSucc = query.exec("commit transaction");
//        if(!bSucc){
//            QString error_s = query.lastError().text();
//            printf("error: %s", error_s.toStdString().data());
//        }
//        db.close();
//    }
//    return bSucc;
//}

void DBIedDataSetDAO::doDeleteRelate(const QString &dataRef)
{
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QList<QString> lst = QList<QString>()<<"ieddataset"<<"tsdatainfo"<<"tmdatainfo"<<"eventinfo"<<"alarminfo"<<"runstateinfo"<<"otherdatainfo"<<"setting"<<"strap"<<"svinfo"<<"gooseinfo";
        QList<QString>::iterator iter;
        QSqlQuery query(db);
        QString sql = "";
        for(iter = lst.begin(); iter!=lst.end(); iter++)
        {
            QString tableName = *iter;
            sql = QObject::tr("DELETE FROM %1 WHERE DATAREF=\"%2\"")
                    .arg(tableName)
                    .arg(dataRef);
            query.exec(sql);
        }

        db.close();
    }
}

bool DBIedDataSetDAO::configBusiness()
{
    bool bSucc = false;
    QHash<int, QList<QString>> hsh{
        {0, {"earlywarningconfig"}}
        ,{1, {"gooseinfo", "strapinfo"}}
    };

    QList<QString> businessWord = QList<QString>()<<"earlywarningconfig"<<"bayinfo,iedinfo,gooseinfo,strapinfo,primarydeviceinfo";
    QHash<QString, QString> hshConf;
    //QList<QString> lstNeedToFind;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        QHash<int, QList<QString>>::const_iterator iter_hsh;
        for(iter_hsh=hsh.begin(); iter_hsh!=hsh.end(); iter_hsh++)
        {
            QList<QString> lst = iter_hsh.value();
            QList<QString>::iterator iter_lst;
            for(iter_lst=lst.begin(); iter_lst!=lst.end(); iter_lst++)
            {
                QString tableName = *iter_lst;
                sql = QObject::tr("SELECT sql FROM sqlite_master WHERE type = \"table\" AND name=\"%1\"")
                        .arg(tableName);
                if(query.exec(sql))
                {
                    while(query.next())
                    {
                        QString sql_str = query.value("sql").toString();
                        if(sql_str.contains("DATAREF"))
                        {
                            sql = QObject::tr("SELECT DATAREF FROM %1")
                                    .arg(tableName);
                            if(query.exec(sql))
                            {
                                while(query.next())
                                {
                                    QString dataRef = query.value("DATAREF").toString();
                                    if(hshConf.count(dataRef) == 0)
                                    {
                                        hshConf.insert(dataRef, "");
                                    }
                                    if(hshConf[dataRef] == "")
                                    {
                                        hshConf[dataRef] += businessWord[iter_hsh.key()];
                                    }else
                                    {
                                        //qDebug() << "businessWord: " << businessWord[iter_hsh.key()] << endl;

                                        hshConf[dataRef] += "$" + businessWord[iter_hsh.key()];
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }

        if(hshConf.size() != 0)
        {
            IedDataSet::List lstDataSet;
            QHash<QString, QString>::const_iterator iter;
            for(iter=hshConf.begin(); iter!=hshConf.end(); iter++)
            {
                IedDataSet::Ptr ptr(new IedDataSet());
                ptr->setDataRef(iter.key());
                ptr->setBusiness(iter.value());
                lstDataSet.append(ptr);
            }
            bSucc = doUpdate(lstDataSet, 2);
        }
        db.close();

        DBGooseInfoDAO dao;
        bSucc = dao.configGooseInfo();
    }

    return bSucc;
}

bool DBIedDataSetDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS ieddataset("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "IEDNAME CHAR(255) NOT NULL,"
                                  "DATAREF CHAR(255) NOT NULL,"
                                  "DATADESC CHAR(255) NOT NULL,"
                                  "LDEVICE CHAR(255) NOT NULL,"
                                  "DATASET CHAR(255) NOT NULL,"
                                  "DATASETDESC CHAR(255) NOT NULL,"
                                  "DATATYPE CHAR(255) NOT NULL,"
                                  "DATAUNIT CHAR(255) NOT NULL,"
                                  "DEVNAME CHAR(255) NOT NULL,"
                                  "EARLYWARNINGTYPE INTEGER NOT NULL,"
                                  "BUSINESS CHAR(255) NOT NULL,"
                                  "DATAVALUETYPE CHAR(255) NOT NULL,"
                                  "UNIQUE(DATAREF, DATASET)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
