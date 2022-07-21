#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QHash>
#include <QDebug>
#include <QVector>
#include <QVariant>
#include <QList>
#include <QByteArray>
#include "ied.h"
#include "dbconnection.h"
#include "dbiedinfodao.h"
#include "dbieddatasetdao.h"
#include "dboptportdao.h"
#include "dbfibreopticaldao.h"
//#include "iedstate.h"
//#include "dbiedrealstatedao.h"
#include "strap.h"
#include "dbstraplightplatedao.h"
#include "dbswitchportdao.h"
DBIedInfoDAO::DBIedInfoDAO()
    : m_connectionName("ConnectIedInfo")
{
    doCreateTable();
}

DBIedInfoDAO::~DBIedInfoDAO()
{

}

int DBIedInfoDAO::select_guid(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    int guid = -1;
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT GUID from iedinfo WHERE IEDNAME = \"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                guid = query.value("GUID").toInt();
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return guid;
}

Ied::List DBIedInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {

        QString sql = QObject::tr("SELECT * FROM iedinfo");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Ied::Ptr ied(new Ied());
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ied->m_iedType = query.value("IEDTYPE").toString();
                ied->m_typeDetail = query.value("TYPEDETAIL").toString();
                ied->m_setType = query.value("SETTYPE").toString();
                ied->m_manufacturer = query.value("MANUFACTURER").toString();
                ied->m_productType = query.value("PRODUCTTYPE").toString();
                ied->m_configVersion = query.value("CONFIGVERSION").toString();
                ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
                ied->m_protocol = query.value("PROTOCOL").toString();
                ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
                ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
                ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
                ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
                ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
                ied->m_criterionRun = query.value("CRITERIONRUN").toString();
                ied->m_stationName = query.value("STATIONID").toString();
                ied->m_voltClass = query.value("VOLTCLASSID").toString();
                ied->m_bayName = query.value("BAYID").toString();
                ied->m_ipA = query.value("IPA").toString();
                ied->m_ipB = query.value("IPB").toString();
                ied->m_ipC = query.value("IPC").toString();
                ied->m_netType = query.value("NETTYPE").toString();
                ied->m_voltage = query.value("VOLTAGE").toString();
                ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
                ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                lstIed.append(ied);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

Ied::List DBIedInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QString sql = QObject::tr("SELECT * FROM iedinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Ied::Ptr ied(new Ied());
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = query.value("STATIONID").toString();
            ied->m_voltClass = query.value("VOLTCLASSID").toString();
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            lstIed.append(ied);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

Ied::List DBIedInfoDAO::doQueryByStationName(const QString &stationName, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM iedinfo WHERE STATIONID=\"%1\"")
                .arg(stationName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Ied::Ptr ied(new Ied());
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ied->m_iedType = query.value("IEDTYPE").toString();
                ied->m_typeDetail = query.value("TYPEDETAIL").toString();
                ied->m_setType = query.value("SETTYPE").toString();
                ied->m_manufacturer = query.value("MANUFACTURER").toString();
                ied->m_productType = query.value("PRODUCTTYPE").toString();
                ied->m_configVersion = query.value("CONFIGVERSION").toString();
                ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
                ied->m_protocol = query.value("PROTOCOL").toString();
                ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
                ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
                ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
                ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
                ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
                ied->m_criterionRun = query.value("CRITERIONRUN").toString();
                ied->m_stationName = stationName;
                ied->m_voltClass = query.value("VOLTCLASSID").toString();
                ied->m_bayName = query.value("BAYID").toString();
                ied->m_ipA = query.value("IPA").toString();
                ied->m_ipB = query.value("IPB").toString();
                ied->m_ipC = query.value("IPC").toString();
                ied->m_netType = query.value("NETTYPE").toString();
                ied->m_voltage = query.value("VOLTAGE").toString();
                ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
                ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                lstIed.append(ied);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

Ied::List DBIedInfoDAO::doQueryByStationName(QSqlDatabase db, const QString &stationName, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QString sql = QObject::tr("SELECT * FROM iedinfo WHERE STATIONID=\"%1\"")
            .arg(stationName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Ied::Ptr ied(new Ied());
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = stationName;
            ied->m_voltClass = query.value("VOLTCLASSID").toString();
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            lstIed.append(ied);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

Ied::List DBIedInfoDAO::doQueryByVoltClass(const QString &voltClass, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM iedinfo WHERE VOLTCLASSID=\"%1\"")
                .arg(voltClass);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Ied::Ptr ied(new Ied());
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ied->m_iedType = query.value("IEDTYPE").toString();
                ied->m_typeDetail = query.value("TYPEDETAIL").toString();
                ied->m_setType = query.value("SETTYPE").toString();
                ied->m_manufacturer = query.value("MANUFACTURER").toString();
                ied->m_productType = query.value("PRODUCTTYPE").toString();
                ied->m_configVersion = query.value("CONFIGVERSION").toString();
                ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
                ied->m_protocol = query.value("PROTOCOL").toString();
                ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
                ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
                ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
                ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
                ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
                ied->m_criterionRun = query.value("CRITERIONRUN").toString();
                ied->m_stationName = query.value("STATIONID").toString();
                ied->m_voltClass = voltClass;
                ied->m_bayName = query.value("BAYID").toString();
                ied->m_ipA = query.value("IPA").toString();
                ied->m_ipB = query.value("IPB").toString();
                ied->m_ipC = query.value("IPC").toString();
                ied->m_netType = query.value("NETTYPE").toString();
                ied->m_voltage = query.value("VOLTAGE").toString();
                ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
                ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                lstIed.append(ied);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

Ied::List DBIedInfoDAO::doQueryByVoltage(const QString &voltage, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM iedinfo WHERE VOLTAGE=\"%1\"")
                .arg(voltage);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Ied::Ptr ied(new Ied());
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ied->m_iedType = query.value("IEDTYPE").toString();
                ied->m_typeDetail = query.value("TYPEDETAIL").toString();
                ied->m_setType = query.value("SETTYPE").toString();
                ied->m_manufacturer = query.value("MANUFACTURER").toString();
                ied->m_productType = query.value("PRODUCTTYPE").toString();
                ied->m_configVersion = query.value("CONFIGVERSION").toString();
                ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
                ied->m_protocol = query.value("PROTOCOL").toString();
                ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
                ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
                ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
                ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
                ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
                ied->m_criterionRun = query.value("CRITERIONRUN").toString();
                ied->m_stationName = query.value("STATIONID").toString();
                ied->m_voltClass = query.value("VOLTCLASSID").toString();
                ied->m_bayName = query.value("BAYID").toString();
                ied->m_ipA = query.value("IPA").toString();
                ied->m_ipB = query.value("IPB").toString();
                ied->m_ipC = query.value("IPC").toString();
                ied->m_netType = query.value("NETTYPE").toString();
                ied->m_voltage = query.value("VOLTAGE").toString();
                ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
                ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                lstIed.append(ied);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

Ied::List DBIedInfoDAO::doQueryByVoltClass(QSqlDatabase db, const QString &voltClass, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QString sql = QObject::tr("SELECT * FROM iedinfo WHERE VOLTCLASSID=\"%1\"")
            .arg(voltClass);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            Ied::Ptr ied(new Ied());
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = query.value("STATIONID").toString();
            ied->m_voltClass = voltClass;
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            lstIed.append(ied);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

Ied::List DBIedInfoDAO::doQueryByVoltage(QSqlDatabase db, const QString &voltage, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QString sql = QObject::tr("SELECT * FROM iedinfo WHERE VOLTAGE=\"%1\"")
            .arg(voltage);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            Ied::Ptr ied(new Ied());
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = query.value("STATIONID").toString();
            ied->m_voltClass = query.value("VOLTCLASSID").toString();
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            lstIed.append(ied);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

Ied::List DBIedInfoDAO::doQueryByBayName(const QString &bayName, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM iedinfo WHERE BAYID=\"%1\"")
                .arg(bayName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Ied::Ptr ied(new Ied());
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ied->m_iedType = query.value("IEDTYPE").toString();
                ied->m_typeDetail = query.value("TYPEDETAIL").toString();
                ied->m_setType = query.value("SETTYPE").toString();
                ied->m_manufacturer = query.value("MANUFACTURER").toString();
                ied->m_productType = query.value("PRODUCTTYPE").toString();
                ied->m_configVersion = query.value("CONFIGVERSION").toString();
                ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
                ied->m_protocol = query.value("PROTOCOL").toString();
                ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
                ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
                ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
                ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
                ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
                ied->m_criterionRun = query.value("CRITERIONRUN").toString();
                ied->m_stationName = query.value("STATIONID").toString();
                ied->m_voltClass = query.value("VOLTCLASSID").toString();
                ied->m_bayName = query.value("BAYID").toString();
                ied->m_ipA = query.value("IPA").toString();
                ied->m_ipB = query.value("IPB").toString();
                ied->m_ipC = query.value("IPC").toString();
                ied->m_netType = query.value("NETTYPE").toString();
                ied->m_voltage = query.value("VOLTAGE").toString();
                ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
                ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                lstIed.append(ied);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

Ied::List DBIedInfoDAO::doQueryByBayName(QSqlDatabase db, const QString &bayName, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QString sql = QObject::tr("SELECT * FROM iedinfo WHERE BAYID=\"%1\"")
            .arg(bayName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            Ied::Ptr ied(new Ied());
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = query.value("STATIONID").toString();
            ied->m_voltClass = query.value("VOLTCLASSID").toString();
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            lstIed.append(ied);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

bool DBIedInfoDAO::doInsert(Ied::List &lstIed)
{
    bool bSucc = false;
    Ied::List::iterator iter = lstIed.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    int list_size = lstIed.size();
    if(list_size == 0)
        return true;
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        query.exec("begin transaction");
        while(iter < lstIed.end())
        {
            Ied::Ptr ied(new Ied());
            ied = *iter;
            QString iedName = ied->iedName();
            QString iedDesc = ied->iedDesc();
            QString iedCateGory = ied->iedCateGory();
            QString iedType = ied->iedType();
            QString typeDetail = ied->typeDetail();
            QString setType = ied->setType();
            QString manufacturer = ied->manufacturer();
            QString productType = ied->productType();
            QString configVersion = ied->configVersion();
            QString VTerminalCRC = ied->VTerminalCRC();
            QString protocol = ied->protocol();
            QString isRemoteSettings = ied->isRemoteSettings();
            QString stationName = ied->stationName();
            QString voltClass = ied->voltClass();
            QString bayName = ied->bayName();
            QString criterionTrip = ied->criterionTrip();
            QString criterionLock = ied->criterionLock();
            QString criterionMaintain = ied->criterionMaintain();
            QString criterionAlarm = ied->criterionAlarm();
            QString criterionRun = ied->criterionRun();
            QString ipA = ied->ipA();
            QString ipB = ied->ipB();
            QString ipC = ied->ipC();
            QString netType = ied->netType();
            QString belongAllBays = ied->belongAllBays();
            QString voltage = ied->voltage();
            QString deliveryDate = ied->deliveryDate();
            QString iedNameComp = ied->iedNameComp();

            QString sql = QObject::tr("insert into iedinfo values(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\", \"%9\", \"%10\", \"%11\", \"%12\", \"%13\", \"%14\", \"%15\", \"%16\", \"%17\", \"%18\", \"%19\", \"%20\", \"%21\", \"%22\", \"%23\", \"%24\", \"%25\", \"%26\", \"%27\", \"%28\")")
                    .arg(iedName)//1
                    .arg(iedDesc)//2
                    .arg(iedCateGory)//3
                    .arg(iedType)//4
                    .arg(typeDetail)//5
                    .arg(setType)//6
                    .arg(manufacturer)//7
                    .arg(productType)//8
                    .arg(configVersion)//9
                    .arg(VTerminalCRC)//10
                    .arg(protocol)//11
                    .arg(isRemoteSettings)//12
                    .arg(stationName)//13
                    .arg(voltClass)//14
                    .arg(bayName)//15
                    .arg(criterionTrip)//16
                    .arg(criterionLock)//17
                    .arg(criterionMaintain)//18
                    .arg(criterionAlarm)//19
                    .arg(criterionRun)//20
                    .arg(ipA)//21
                    .arg(ipB)//22
                    .arg(ipC)//23
                    .arg(netType)//24
                    .arg(belongAllBays)//25
                    .arg(voltage)//26
                    .arg(deliveryDate)//27
                    .arg(iedNameComp);
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

Ied::Ptr DBIedInfoDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM iedinfo WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                Ied::Ptr ied(new Ied());
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ied->m_iedType = query.value("IEDTYPE").toString();
                ied->m_typeDetail = query.value("TYPEDETAIL").toString();
                ied->m_setType = query.value("SETTYPE").toString();
                ied->m_manufacturer = query.value("MANUFACTURER").toString();
                ied->m_productType = query.value("PRODUCTTYPE").toString();
                ied->m_configVersion = query.value("CONFIGVERSION").toString();
                ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
                ied->m_protocol = query.value("PROTOCOL").toString();
                ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
                ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
                ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
                ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
                ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
                ied->m_criterionRun = query.value("CRITERIONRUN").toString();
                ied->m_stationName = query.value("STATIONID").toString();
                ied->m_voltClass = query.value("VOLTCLASSID").toString();
                ied->m_bayName = query.value("BAYID").toString();
                ied->m_ipA = query.value("IPA").toString();
                ied->m_ipB = query.value("IPB").toString();
                ied->m_ipC = query.value("IPC").toString();
                ied->m_netType = query.value("NETTYPE").toString();
                ied->m_voltage = query.value("VOLTAGE").toString();
                ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
                ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                if(ok)
                    *ok = bSucc;
                db.close();
                return ied;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

Ied::Ptr DBIedInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM iedinfo WHERE IEDNAME=\"%1\"")
            .arg(iedName);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            Ied::Ptr ied(new Ied());
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = query.value("STATIONID").toString();
            ied->m_voltClass = query.value("VOLTCLASSID").toString();
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            if(ok)
                *ok = bSucc;
            return ied;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

Ied::List DBIedInfoDAO::doQueryByVoltAndPort(const QString &voltClass, int portNetType, bool *ok)
{
    bool bSucc = false;
    Ied::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    QHash<QString, int> hash_ied;
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT a.IEDNAME FROM iedinfo a, optport b WHERE b.NETTYPE=%1 AND a.IEDNAME=b.IEDNAME AND a.VOLTCLASSID=\"%2\"")
                .arg(portNetType)
                .arg(voltClass);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                QString iedName = query.value("IEDNAME").toString();
                if(!hash_ied.contains(iedName))
                {
                    hash_ied.insert(iedName, 1);
                    Ied::Ptr ptr = this->doQuery(db, iedName);
                    if(ptr)
                    {
                        lst.append(ptr);
                    }
                }
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Ied::List DBIedInfoDAO::doQueryByVoltAndPort(QSqlDatabase db, const QString &voltClass, int portNetType, bool *ok)
{
    bool bSucc = false;
    Ied::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT a.IEDNAME FROM optport b, iedinfo a WHERE b.NETTYPE=%1 AND b.IEDNAME=a.IEDNAME AND a.VOLTCLASSID=\"%2\"")
            .arg(portNetType)
            .arg(voltClass);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        QHash<QString, int> hash_ied;
        while(query.next())
        {
            QString iedName = query.value("IEDNAME").toString();
            if(hash_ied.count(iedName) == 0)
            {
                hash_ied.insert(iedName, 1);
                Ied::Ptr ptr(new Ied());
                ptr = this->doQuery(db, iedName);
                lst.append(ptr);
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Ied * DBIedInfoDAO::ied(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM iedinfo WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Ied *ied = new Ied();
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ied->m_iedType = query.value("IEDTYPE").toString();
                ied->m_typeDetail = query.value("TYPEDETAIL").toString();
                ied->m_setType = query.value("SETTYPE").toString();
                ied->m_manufacturer = query.value("MANUFACTURER").toString();
                ied->m_productType = query.value("PRODUCTTYPE").toString();
                ied->m_configVersion = query.value("CONFIGVERSION").toString();
                ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
                ied->m_protocol = query.value("PROTOCOL").toString();
                ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
                ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
                ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
                ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
                ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
                ied->m_criterionRun = query.value("CRITERIONRUN").toString();
                ied->m_stationName = query.value("STATIONID").toString();
                ied->m_voltClass = query.value("VOLTCLASSID").toString();
                ied->m_bayName = query.value("BAYID").toString();
                ied->m_ipA = query.value("IPA").toString();
                ied->m_ipB = query.value("IPB").toString();
                ied->m_ipC = query.value("IPC").toString();
                ied->m_netType = query.value("NETTYPE").toString();
                ied->m_voltage = query.value("VOLTAGE").toString();
                ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
                ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                if(ok)
                    *ok = bSucc;
                db.close();
                return ied;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

QList<Ied*> DBIedInfoDAO::doQueryLstByBayName(const QString &bayName, bool *ok)
{
    bool bSucc = false;
    QList<Ied*> lst;
    DBStrapLightPlateDAO daoStrap;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM iedinfo WHERE BAYID=\"%1\"")
                .arg(bayName);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                Ied *ied = new Ied();
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ied->m_iedType = query.value("IEDTYPE").toString();
                ied->m_typeDetail = query.value("TYPEDETAIL").toString();
                ied->m_setType = query.value("SETTYPE").toString();
                ied->m_manufacturer = query.value("MANUFACTURER").toString();
                ied->m_productType = query.value("PRODUCTTYPE").toString();
                ied->m_configVersion = query.value("CONFIGVERSION").toString();
                ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
                ied->m_protocol = query.value("PROTOCOL").toString();
                ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
                ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
                ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
                ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
                ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
                ied->m_criterionRun = query.value("CRITERIONRUN").toString();
                ied->m_stationName = query.value("STATIONID").toString();
                ied->m_voltClass = query.value("VOLTCLASSID").toString();
                ied->m_bayName = query.value("BAYID").toString();
                ied->m_ipA = query.value("IPA").toString();
                ied->m_ipB = query.value("IPB").toString();
                ied->m_ipC = query.value("IPC").toString();
                ied->m_netType = query.value("NETTYPE").toString();
                ied->m_voltage = query.value("VOLTAGE").toString();
                ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
                ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                QList<Strap*> lstStrap = daoStrap.doQueryLst(ied->iedName());
                ied->setLstStrap(lstStrap);
                lst.append(ied);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Ied::List DBIedInfoDAO::doQueryByBayNameLike(const QString &bayName, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM iedinfo WHERE BELONGALLBAYS LIKE \"%%1\" OR BELONGALLBAYS LIKE \"%%1|%\"")
                .arg(bayName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Ied::Ptr ied(new Ied());
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ied->m_iedType = query.value("IEDTYPE").toString();
                ied->m_typeDetail = query.value("TYPEDETAIL").toString();
                ied->m_setType = query.value("SETTYPE").toString();
                ied->m_manufacturer = query.value("MANUFACTURER").toString();
                ied->m_productType = query.value("PRODUCTTYPE").toString();
                ied->m_configVersion = query.value("CONFIGVERSION").toString();
                ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
                ied->m_protocol = query.value("PROTOCOL").toString();
                ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
                ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
                ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
                ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
                ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
                ied->m_criterionRun = query.value("CRITERIONRUN").toString();
                ied->m_stationName = query.value("STATIONID").toString();
                ied->m_voltClass = query.value("VOLTCLASSID").toString();
                ied->m_bayName = query.value("BAYID").toString();
                ied->m_ipA = query.value("IPA").toString();
                ied->m_ipB = query.value("IPB").toString();
                ied->m_ipC = query.value("IPC").toString();
                ied->m_netType = query.value("NETTYPE").toString();
                ied->m_voltage = query.value("VOLTAGE").toString();
                ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
                ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                lstIed.append(ied);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

MemoryIed::Hash DBIedInfoDAO::doQueryMemoryIed(bool *ok)
{
    bool bSucc = false;
    MemoryIed::Hash hsh;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM iedinfo");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            DBIedDataSetDAO dao;
            while(query.next())
            {
                MemoryIed::Ptr ied(new MemoryIed());
                ied->m_GUID = query.value("GUID").toInt();
                ied->m_iedName = query.value("IEDNAME").toString();
                ied->m_iedDesc = query.value("IEDDESC").toString();
                ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
                QString netType = query.value("NETTYPE").toString();
                if(netType == "A")
                {
                    ied->m_ip = query.value("IPA").toString();
                }
                else if(netType == "B")
                {
                    ied->m_ip = query.value("IPB").toString();
                }
                else
                {
                    ied->m_ip = query.value("IPC").toString();
                }
                MemoryFCDA::Hash hashFCDA = dao.doQueryMemoryFCDA(db, ied->iedName());
                ied->setLstFCDA(hashFCDA);
                if(hsh.count(ied->iedName()) == 0)
                    hsh.insert(ied->iedName(), ied);
            }
        }

        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

QList<Ied*> DBIedInfoDAO::doQueryLst(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    QList<Ied*> lst;
    QString sql = QObject::tr("SELECT * FROM iedinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            Ied *ied = new Ied();
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = query.value("STATIONID").toString();
            ied->m_voltClass = query.value("VOLTCLASSID").toString();
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            lst.append(ied);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Ied::List DBIedInfoDAO::doQueryByBayNameLike(QSqlDatabase db, const QString &bayName, bool *ok)
{
    bool bSucc = false;
    Ied::List lstIed;
    QString sql = QObject::tr("SELECT * FROM iedinfo WHERE BELONGALLBAYS LIKE \"%%1\" OR BELONGALLBAYS LIKE \"%%1|%\"")
            .arg(bayName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Ied::Ptr ied(new Ied());
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = query.value("STATIONID").toString();
            ied->m_voltClass = query.value("VOLTCLASSID").toString();
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            lstIed.append(ied);
        }
    }
    if(ok)
        *ok = bSucc;

    return lstIed;
}

MemoryIed::Hash DBIedInfoDAO::doQueryMemoryIed(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    MemoryIed::Hash hsh;
    QString sql = QObject::tr("SELECT * FROM iedinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            MemoryIed::Ptr ied(new MemoryIed());
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            QString netType = query.value("NETTYPE").toString();
            if(netType == "A")
            {
                ied->m_ip = query.value("IPA").toString();
            }
            else if(netType == "B")
            {
                ied->m_ip = query.value("IPB").toString();
            }
            else
            {
                ied->m_ip = query.value("IPC").toString();
            }
            if(hsh.count(ied->iedName()) == 0)
                hsh.insert(ied->iedName(), ied);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

QString DBIedInfoDAO::getAllIed()
{
    Ied::List lst = this->doQuery();
    Ied::List::iterator iter;
    QString configIed = "";
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        Ied::Ptr ptr = *iter;
        if(iter!=lst.begin())
            configIed += "$";
        configIed += ptr->iedName();
    }

    return configIed;
}

QList<Ied *> DBIedInfoDAO::doQueryLstByBayName(QSqlDatabase db, const QString &bayName, bool *ok)
{
    bool bSucc = false;
    QList<Ied*> lst;
    DBStrapLightPlateDAO daoStrap;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM iedinfo WHERE BAYID=\"%1\"")
            .arg(bayName);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Ied *ied = new Ied();
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = query.value("STATIONID").toString();
            ied->m_voltClass = query.value("VOLTCLASSID").toString();
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            QList<Strap*> lstStrap = daoStrap.doQueryLst(db, ied->iedName());
            ied->setLstStrap(lstStrap);
            lst.append(ied);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Ied * DBIedInfoDAO::ied(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM iedinfo WHERE IEDNAME=\"%1\"")
            .arg(iedName);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Ied *ied = new Ied();
            ied->m_GUID = query.value("GUID").toInt();
            ied->m_iedName = query.value("IEDNAME").toString();
            ied->m_iedDesc = query.value("IEDDESC").toString();
            ied->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ied->m_iedType = query.value("IEDTYPE").toString();
            ied->m_typeDetail = query.value("TYPEDETAIL").toString();
            ied->m_setType = query.value("SETTYPE").toString();
            ied->m_manufacturer = query.value("MANUFACTURER").toString();
            ied->m_productType = query.value("PRODUCTTYPE").toString();
            ied->m_configVersion = query.value("CONFIGVERSION").toString();
            ied->m_VTerminalCRC = query.value("VTERMINALCRC").toString();
            ied->m_protocol = query.value("PROTOCOL").toString();
            ied->m_isRemoteSettings = query.value("ISREMOTESETTINGS").toString();
            ied->m_criterionTrip = query.value("CRITERIONTRIP").toString();
            ied->m_criterionLock = query.value("CRITERIONLOCK").toString();
            ied->m_criterionMaintain = query.value("CRITERIONMAINTAIN").toString();
            ied->m_criterionAlarm = query.value("CRITERIONALARM").toString();
            ied->m_criterionRun = query.value("CRITERIONRUN").toString();
            ied->m_stationName = query.value("STATIONID").toString();
            ied->m_voltClass = query.value("VOLTCLASSID").toString();
            ied->m_bayName = query.value("BAYID").toString();
            ied->m_ipA = query.value("IPA").toString();
            ied->m_ipB = query.value("IPB").toString();
            ied->m_ipC = query.value("IPC").toString();
            ied->m_netType = query.value("NETTYPE").toString();
            ied->m_voltage = query.value("VOLTAGE").toString();
            ied->m_deliveryDate = query.value("DELIVERYDATE").toString();
            ied->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            if(ok)
                *ok = bSucc;
            return ied;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

bool DBIedInfoDAO::doUpdate(const Ied::Ptr &ied)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE iedinfo SET IEDNAME=\"%1\", IEDDESC=\"%2\", IEDCATEGORY=\"%3\", IEDTYPE=\"%4\", TYPEDETAIL=\"%5\", SETTYPE=\"%6\", MANUFACTURER=\"%7\", PRODUCTTYPE=\"%8\", CONFIGVERSION=\"%9\", VTERMINALCRC=\"%10\", PROTOCOL=\"%11\", ISREMOTESETTINGS=\"%12\", STATIONID=\"%13\", VOLTCLASSID=\"%14\", BAYID=\"%15\", CRITERIONTRIP=\"%16\", CRITERIONLOCK=\"%17\", CRITERIONMAINTAIN=\"%18\", CRITERIONALARM=\"%19\", CRITERIONRUN=\"%20\", IPA=\"%21\", IPB=\"%22\", IPC=\"%23\", NETTYPE=\"%24\", BELONGALLBAYS=\"%25\", VOLTAGE=\"%26\", DELIVERYDATE=\"%27\", IEDNAMECOMP=\"%28\" WHERE GUID=%29")
                .arg(ied->iedName())
                .arg(ied->iedDesc())
                .arg(ied->iedCateGory())
                .arg(ied->iedType())
                .arg(ied->typeDetail())
                .arg(ied->setType())
                .arg(ied->manufacturer())
                .arg(ied->productType())
                .arg(ied->configVersion())
                .arg(ied->VTerminalCRC())
                .arg(ied->protocol())
                .arg(ied->isRemoteSettings())
                .arg(ied->stationName())
                .arg(ied->voltClass())
                .arg(ied->bayName())
                .arg(ied->criterionTrip())
                .arg(ied->criterionLock())
                .arg(ied->criterionMaintain())
                .arg(ied->criterionAlarm())
                .arg(ied->criterionRun())
                .arg(ied->ipA())
                .arg(ied->ipB())
                .arg(ied->ipC())
                .arg(ied->netType())
                .arg(ied->belongAllBays())
                .arg(ied->voltage())
                .arg(ied->deliveryDate())
                .arg(ied->iedNameComp())
                .arg(ied->GUID());
        if(query.exec(sql))
            bSucc = true;
        db.close();
    }
    return bSucc;
}

bool DBIedInfoDAO::doUpdate(Ied::List &lstIed)
{
        bool bSucc = false;

        Ied::List::iterator iter = lstIed.begin();

        QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

        if(db.isOpen() || db.open())
        {
            QSqlQuery query(db);
            QString sql = "";
            query.exec("begin transaction");

            while(iter < lstIed.end())
            {
                Ied::Ptr ied(new Ied());
                ied = *iter;
                sql = QObject::tr("UPDATE iedinfo SET IEDNAME=\"%1\", IEDDESC=\"%2\", IEDCATEGORY=\"%3\", IEDTYPE=\"%4\", TYPEDETAIL=\"%5\", SETTYPE=\"%6\", MANUFACTURER=\"%7\", PRODUCTTYPE=\"%8\", CONFIGVERSION=\"%9\", VTERMINALCRC=\"%10\", PROTOCOL=\"%11\", ISREMOTESETTINGS=\"%12\", STATIONID=\"%13\", VOLTCLASSID=\"%14\", BAYID=\"%15\", CRITERIONTRIP=\"%16\", CRITERIONLOCK=\"%17\", CRITERIONMAINTAIN=\"%18\", CRITERIONALARM=\"%19\", CRITERIONRUN=\"%20\", IPA=\"%21\", IPB=\"%22\", IPC=\"%23\", NETTYPE=\"%24\", BELONGALLBAYS=\"%25\", VOLTAGE=\"%26\", DELIVERYDATE=\"%27\", IEDNAMECOMP=\"%28\" WHERE GUID=%29")
                        .arg(ied->iedName())
                        .arg(ied->iedDesc())
                        .arg(ied->iedCateGory())
                        .arg(ied->iedType())
                        .arg(ied->typeDetail())
                        .arg(ied->setType())
                        .arg(ied->manufacturer())
                        .arg(ied->productType())
                        .arg(ied->configVersion())
                        .arg(ied->VTerminalCRC())
                        .arg(ied->protocol())
                        .arg(ied->isRemoteSettings())
                        .arg(ied->stationName())
                        .arg(ied->voltClass())
                        .arg(ied->bayName())
                        .arg(ied->criterionTrip())
                        .arg(ied->criterionLock())
                        .arg(ied->criterionMaintain())
                        .arg(ied->criterionAlarm())
                        .arg(ied->criterionRun())
                        .arg(ied->ipA())
                        .arg(ied->ipB())
                        .arg(ied->ipC())
                        .arg(ied->netType())
                        .arg(ied->belongAllBays())
                        .arg(ied->voltage())
                        .arg(ied->deliveryDate())
                        .arg(ied->iedNameComp())
                        .arg(ied->GUID());
                //printf("GUID: %d\n", ied->GUID());
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

bool DBIedInfoDAO::doUpdate(Ied::List &lstIed, int type)
{
    bool bSucc = false;

    Ied::List::iterator iter = lstIed.begin();

    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(type == 0)
        {
            query.exec("begin transaction");

            while(iter < lstIed.end())
            {
                Ied::Ptr ied(new Ied());
                ied = *iter;
                sql = QObject::tr("UPDATE iedinfo SET BELONGALLBAYS=\"%1\" WHERE IEDNAME=\"%2\"")
                                .arg(ied->belongAllBays())
                                .arg(ied->iedName());
                //printf("GUID: %d\n", ied->GUID());
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

//mysql版本优化批量更新
//bool DBIedInfoDAO::doUpdate(Ied::List &lstIed)
//{
//    bool bSucc = false;

//    Ied::List::iterator iter = lstIed.begin();
//    QString sql_str_1 = "UPDATE iedinfo a JOIN(";
//    QString sql_str_set = ") b USING(GUID) SET a.IEDNAME=b.IEDNAME, a.IEDDESC=b.IEDDESC, a.IEDCATEGORY=b.IEDCATEGORY, a.IEDTYPE=b.IEDTYPE, a.TYPEDETAIL=b.TYPEDETAIL, a.SETTYPE=b.SETTYPE, a.MANUFACTURER=b.MANUFACTURER, a.PRODUCTTYPE=b.PRODUCTTYPE, a.CONFIGVERSION=b.CONFIGVERSION, a.VTERMINALCRC=b.VTERMINALCRC, a.PROTOCOL=b.PROTOCOL, a.ISREMOTESETTINGS=b.ISREMOTESETTINGS, a.STATIONID=b.STATIONID, a.VOLTCLASSID=b.VOLTCLASSID, a.BAYID=b.BAYID, a.CRITERIONTRIP=b.CRITERIONTRIP, a.CRITERIONLOCK=b.CRITERIONLOCK, a.CRITERIONMAINTAIN=b.CRITERIONMAINTAIN, a.CRITERIONALARM=b.CRITERIONALARM, a.CRITERIONRUN=b.CRITERIONRUN";

//    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

//    if(db.isOpen() || db.open())
//    {
//        QSqlQuery query(db);

//        while(iter < lstIed.end())
//        {
//            Ied::Ptr ied(new Ied());
//            ied = *iter;
//            int GUID = ied->GUID();
//            QString GUID_str = QString::number(GUID);
//            QString iedName = ied->iedName();
//            QString iedDesc = ied->iedDesc();
//            QString iedCateGory = ied->iedCateGory();
//            QString iedType = ied->iedType();
//            QString typeDetail = ied->typeDetail();
//            QString setType = ied->setType();
//            QString manufacturer = ied->manufacturer();
//            QString productType = ied->productType();
//            QString configVersion = ied->configVersion();
//            QString VTerminalCRC = ied->VTerminalCRC();
//            QString protocol = ied->protocol();
//            QString isRemoteSettings = ied->isRemoteSettings();
//            QString stationName = ied->stationName();
//            QString voltClass = ied->voltClass();
//            QString bayName = ied->bayName();
//            QString criterionTrip = ied->criterionTrip();
//            QString criterionLock = ied->criterionLock();
//            QString criterionMaintain = ied->criterionMaintain();
//            QString criterionAlarm = ied->criterionAlarm();
//            QString criterionRun = ied->criterionRun();
//            QString sql_str_2 = " SELECT " + GUID_str + " AS GUID, '" + iedName + "' AS IEDNAME, '" + iedDesc + "' AS IEDDESC, '" + iedCateGory + "' AS IEDCATEGORY,'" + iedType + "' AS IEDTYPE, '" + typeDetail + "' AS TYPEDETAIL, '" + setType + "' AS SETTYPE, '" + manufacturer + "' AS MANUFACTURER, '" + productType + "' AS PRODUCTTYPE, '" + configVersion + "' AS CONFIGVERSION, '" + VTerminalCRC + "' AS VTERMINALCRC, '" + protocol + "' AS PROTOCOL, '" + isRemoteSettings + "' AS ISREMOTESETTINGS, '" + stationName + "' AS STATIONID, '" + voltClass + "' AS VOLTCLASSID, '" + bayName + "' AS BAYID, '" + criterionTrip + "' AS CRITERIONTRIP, '" + criterionLock + "' AS CRITERIONLOCK, '" + criterionMaintain + "' AS CRITERIONMAINTAIN, '" + criterionAlarm + "' AS CRITERIONALARM, '" + criterionRun + "' AS CRITERIONRUN";
//            sql_str_1 += sql_str_2;
//            if(iter < lstIed.end() - 1)
//                sql_str_1 += " UNION";
//            iter++;
//        }

//        sql_str_1 += sql_str_set;
//        //printf("sql: %s\n", sql_str_1.toStdString().data());
//        QByteArray ba = sql_str_1.toUtf8();
//        QString sql = QObject::tr(ba.data());
//        bSucc = query.exec(sql);
//        db.close();
//    }
//    return bSucc;
//}

bool DBIedInfoDAO::doDelete(int iedGUID)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM iedinfo WHERE GUID=%1")
                .arg(iedGUID);
        if(query.exec(sql))
            bSucc = true;
        db.close();
    }
    return bSucc;
}

bool DBIedInfoDAO::doDelete(QList<int> lstIedGUID)
{
    QList<int>::iterator iter = lstIedGUID.begin();
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    int lst_size = lstIedGUID.size();
    if(lst_size != 0)
        return bSucc;
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        for(iter = lstIedGUID.begin(); iter != lstIedGUID.end(); iter++)
        {
            int guid = *iter;
            sql = QObject::tr("DELETE FROM iedinfo WHERE GUID=%1")
                    .arg(guid);
            if(!query.exec(sql))
                return bSucc;
        }
        bSucc = true;
        db.close();
    }
    return bSucc;
}

void DBIedInfoDAO::doDeleteRelate(const QString &iedName)
{
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QList<QString> lst = QList<QString>()<<"iedinfo"<<"ieddataset"<<"tsdatainfo"<<"tmdatainfo"<<"eventinfo"<<"alarminfo"<<"runstateinfo"<<"otherdatainfo"<<"setting"<<"strap"<<"svinfo"<<"gooseinfo";
        QList<QString>::iterator iter;
        QSqlQuery query(db);
        QString sql = "";
        for(iter = lst.begin(); iter!=lst.end(); iter++)
        {
            QString tableName = *iter;
            if(tableName=="iedinfo" || tableName=="ieddataset"){
                sql = QObject::tr("DELETE FROM %1 WHERE IEDNAME=\"%2\"")
                        .arg(tableName)
                        .arg(iedName);
            }else{
                //printf("th\n");
                sql = QObject::tr("DELETE a FROM %1 a, ieddataset b WHERE b.IEDNAME=\"%2\" AND b.DATAREF=a.DATAREF")
                        .arg(tableName)
                        .arg(iedName);
            }
            query.exec(sql);
        }
        db.close();
    }
    //return bSucc;
}

bool DBIedInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS iedinfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "IEDNAME CHAR(255) UNIQUE NOT NULL,"
                                  "IEDDESC CHAR(255) NOT NULL,"
                                  "IEDCATEGORY CHAR(255) NOT NULL,"
                                  "IEDTYPE CHAR(255) NOT NULL,"
                                  "TYPEDETAIL CHAR(255) NOT NULL,"
                                  "SETTYPE CHAR(255) NOT NULL,"
                                  "MANUFACTURER CHAR(255) NOT NULL,"
                                  "PRODUCTTYPE CHAR(255) NOT NULL,"
                                  "CONFIGVERSION CHAR(255) NOT NULL,"
                                  "VTERMINALCRC CHAR(255) NOT NULL,"
                                  "PROTOCOL CHAR(255) NOT NULL,"
                                  "ISREMOTESETTINGS CHAR(255) NOT NULL,"
                                  "STATIONID CHAR(255) NOT NULL,"
                                  "VOLTCLASSID CHAR(255) NOT NULL,"
                                  "BAYID CHAR(255) NOT NULL,"
                                  "CRITERIONTRIP CHAR(255) NOT NULL,"
                                  "CRITERIONLOCK CHAR(255) NOT NULL,"
                                  "CRITERIONMAINTAIN CHAR(255) NOT NULL,"
                                  "CRITERIONALARM CHAR(255) NOT NULL,"
                                  "CRITERIONRUN CHAR(255) NOT NULL,"
                                  "IPA CHAR(255) NOT NULL,"
                                  "IPB CHAR(255) NOT NULL,"
                                  "IPC CHAR(255) NOT NULL,"
                                  "NETTYPE CHAR(255) NOT NULL,"
                                  "BELONGALLBAYS CHAR(255) NOT NULL,"
                                  "VOLTAGE CHAR(255) NOT NULL,"
                                  "DELIVERYDATE CHAR(255) NOT NULL,"
                                  "IEDNAMECOMP CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBIedInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM iedinfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='iedinfo'");
        bSucc = query.exec(sql);
        db.close();
        DBIedDataSetDAO dao;
        dao.doClear();

        DBOptPortDAO dao_port;
        dao_port.doClear();

        DBFibreOpticalDAO dao_fibre;
        dao_fibre.doClear();

        DBSwitchPortDAO dao_switchPort;
        dao_switchPort.doClear();
    }
    return bSucc;
}
