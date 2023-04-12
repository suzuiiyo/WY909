#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include "dbconnection.h"
#include "setting.h"
#include "dbsettingdao.h"
//#include "realdata.h"
//#include "dbrealdatadao.h"
#include "dastruct.h"
#include "dbdastructdao.h"
#include "dbcolumntypetransform.h"
DBSettingDAO::DBSettingDAO()
    : m_connectionName("connectSetting")
{
    doCreateTable();
}

DBSettingDAO::~DBSettingDAO()
{

}

Setting::List DBSettingDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    Setting::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.SETTINGTYPE, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM setting a, ieddataset b WHERE a.DATAREF=b.DATAREF");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                Setting::Ptr ptr(new Setting());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_settingType = query.value("SETTINGTYPE").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toFloat();
                ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
                ptr->m_minSetting = query.value("MINSETTING").toFloat();
                ptr->m_stepSize = query.value("STEPSIZE").toFloat();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Setting::Ptr DBSettingDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.SETTINGTYPE, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM setting a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Setting::Ptr ptr(new Setting());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_settingType = query.value("SETTINGTYPE").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toFloat();
                ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
                ptr->m_minSetting = query.value("MINSETTING").toFloat();
                ptr->m_stepSize = query.value("STEPSIZE").toFloat();
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

Setting::List DBSettingDAO::doQueryByIedName(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    Setting::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.SETTINGTYPE, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM setting a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Setting::Ptr ptr(new Setting());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_settingType = query.value("SETTINGTYPE").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toFloat();
                ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
                ptr->m_minSetting = query.value("MINSETTING").toFloat();
                ptr->m_stepSize = query.value("STEPSIZE").toFloat();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Setting::List DBSettingDAO::doQueryBySetType(const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    Setting::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.SETTINGTYPE, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM setting a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
                .arg(iedName)
                .arg(setType);

        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {

            while(query.next())
            {
                Setting::Ptr ptr(new Setting());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataSet = query.value("DATASET").toString();
                ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_settingType = query.value("SETTINGTYPE").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toFloat();
                ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
                ptr->m_minSetting = query.value("MINSETTING").toFloat();
                ptr->m_stepSize = query.value("STEPSIZE").toFloat();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Setting::List DBSettingDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    Setting::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.SETTINGTYPE, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM setting a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Setting::Ptr ptr(new Setting());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_settingType = query.value("SETTINGTYPE").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toFloat();
            ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
            ptr->m_minSetting = query.value("MINSETTING").toFloat();
            ptr->m_stepSize = query.value("STEPSIZE").toFloat();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Setting::Ptr DBSettingDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.SETTINGTYPE, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM setting a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Setting::Ptr ptr(new Setting());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_settingType = query.value("SETTINGTYPE").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toFloat();
            ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
            ptr->m_minSetting = query.value("MINSETTING").toFloat();
            ptr->m_stepSize = query.value("STEPSIZE").toFloat();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

Setting::List DBSettingDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    Setting::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.SETTINGTYPE, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM setting a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Setting::Ptr ptr(new Setting());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_settingType = query.value("SETTINGTYPE").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toFloat();
            ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
            ptr->m_minSetting = query.value("MINSETTING").toFloat();
            ptr->m_stepSize = query.value("STEPSIZE").toFloat();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Setting::List DBSettingDAO::doQueryBySetType(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    Setting::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.SETTINGTYPE, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM setting a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
            .arg(iedName)
            .arg(setType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Setting::Ptr ptr(new Setting());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_settingType = query.value("SETTINGTYPE").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toFloat();
            ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
            ptr->m_minSetting = query.value("MINSETTING").toFloat();
            ptr->m_stepSize = query.value("STEPSIZE").toFloat();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBSettingDAO::doInsert(Setting::List &lst)
{
    bool bSucc = false;
    Setting::List::iterator iter = lst.begin();
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
                Setting::Ptr ptr(new Setting());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dimension = ptr->dimension();
                QString settingType = ptr->settingType();
                float referenceValue = ptr->referenceValue();
                float maxValue = ptr->maxSetting();
                float minValue = ptr->minSetting();
                float stepSize = ptr->stepSize();
                sql = QObject::tr("REPLACE INTO setting VALUES(NULL, \"%1\", \"%2\", \"%3\", %4, %5, %6, %7)")
                        .arg(dataRef)//1
                        .arg(settingType)//2
                        .arg(dimension)//3
                        .arg(referenceValue)//4
                        .arg(maxValue)//5
                        .arg(minValue)//6
                        .arg(stepSize);//7
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
                Setting::Ptr ptr(new Setting());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dimension = ptr->dimension();
                QString settingType = ptr->settingType();
                float referenceValue = ptr->referenceValue();
                float maxValue = ptr->maxSetting();
                float minValue = ptr->minSetting();
                float stepSize = ptr->stepSize();
                sql = QObject::tr("REPLACE INTO setting VALUES(NULL, \"%1\", \"%2\", \"%3\", %4, %5, %6, %7)")
                        .arg(dataRef)//1
                        .arg(settingType)//2
                        .arg(dimension)//3
                        .arg(referenceValue)//4
                        .arg(maxValue)//5
                        .arg(minValue)//6
                        .arg(stepSize);//7
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

bool DBSettingDAO::doUpdate(const Setting::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE setting SET DATAREF=\"%1\", SETTINGTYPE=\"%2\", DIMENSION=\"%3\", REFERENCEVALUE=%4, MAXSETTING=%5, MINSETTING=%6, STEPSIZE=%7 WHERE GUID=%8")
                .arg(ptr->dataRef())
                .arg(ptr->settingType())
                .arg(ptr->dimension())
                .arg(ptr->referenceValue())
                .arg(ptr->maxSetting())
                .arg(ptr->minSetting())
                .arg(ptr->stepSize())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSettingDAO::doUpdate(Setting::List &lst)
{
    bool bSucc = false;
    Setting::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");
        while(iter < lst.end())
        {
            Setting::Ptr ptr(new Setting());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE setting SET DATAREF=\"%1\", SETTINGTYPE=\"%2\", DIMENSION=\"%3\", REFERENCEVALUE=%4, MAXSETTING=%5, MINSETTING=%6, STEPSIZE=%7 WHERE GUID=%8")
                    .arg(ptr->dataRef())
                    .arg(ptr->settingType())
                    .arg(ptr->dimension())
                    .arg(ptr->referenceValue())
                    .arg(ptr->maxSetting())
                    .arg(ptr->minSetting())
                    .arg(ptr->stepSize())
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

bool DBSettingDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM setting WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSettingDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE a FROM setting a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSettingDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM setting");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='setting'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSettingDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS setting("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) UNIQUE NOT NULL,"
                                  "SETTINGTYPE CHAR(255) NOT NULL,"
                                  "DIMENSION CHAR(255) NOT NULL,"
                                  "REFERENCEVALUE FLOAT(8,3) NOT NULL,"
                                  "MAXSETTING FLOAT(8,3) NOT NULL,"
                                  "MINSETTING FLOAT(8,3) NOT NULL,"
                                  "STEPSIZE FLOAT(8,3) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
