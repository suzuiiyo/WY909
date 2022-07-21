#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include "dbconnection.h"
#include "otherdatainfo.h"
#include "dbotherdatainfodao.h"
//#include "realdata.h"
//#include "dbrealdatadao.h"
#include "dastruct.h"
#include "dbdastructdao.h"
#include "dbcolumntypetransform.h"
DBOtherDataInfoDAO::DBOtherDataInfoDAO()
    : m_connectionName("connectOtherInfo")
{
    doCreateTable();
}

DBOtherDataInfoDAO::~DBOtherDataInfoDAO()
{

}

OtherDataInfo::List DBOtherDataInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    OtherDataInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM otherdatainfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                OtherDataInfo::Ptr ptr(new OtherDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
                ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
                ptr->m_minSetting = query.value("MINSETTING").toFloat();
                ptr->m_stepSize = query.value("STEPSIZE").toFloat();
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

OtherDataInfo::Ptr DBOtherDataInfoDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM otherdatainfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                OtherDataInfo::Ptr ptr(new OtherDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
                ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
                ptr->m_minSetting = query.value("MINSETTING").toFloat();
                ptr->m_stepSize = query.value("STEPSIZE").toFloat();
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

OtherDataInfo::List DBOtherDataInfoDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    OtherDataInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM otherdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                OtherDataInfo::Ptr ptr(new OtherDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
                ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
                ptr->m_minSetting = query.value("MINSETTING").toFloat();
                ptr->m_stepSize = query.value("STEPSIZE").toFloat();
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

OtherDataInfo::List DBOtherDataInfoDAO::doQuery(const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    OtherDataInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM otherdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
                .arg(iedName)
                .arg(setType);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                OtherDataInfo::Ptr ptr(new OtherDataInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dimension = query.value("DIMENSION").toString();
                ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
                ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
                ptr->m_minSetting = query.value("MINSETTING").toFloat();
                ptr->m_stepSize = query.value("STEPSIZE").toFloat();
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

OtherDataInfo::List DBOtherDataInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    OtherDataInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM otherdatainfo a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            OtherDataInfo::Ptr ptr(new OtherDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
            ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
            ptr->m_minSetting = query.value("MINSETTING").toFloat();
            ptr->m_stepSize = query.value("STEPSIZE").toFloat();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

OtherDataInfo::Ptr DBOtherDataInfoDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM otherdatainfo a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            OtherDataInfo::Ptr ptr(new OtherDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
            ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
            ptr->m_minSetting = query.value("MINSETTING").toFloat();
            ptr->m_stepSize = query.value("STEPSIZE").toFloat();
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

OtherDataInfo::List DBOtherDataInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    OtherDataInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM otherdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(query.exec(sql))
    {
        while(query.next())
        {
            OtherDataInfo::Ptr ptr(new OtherDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
            ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
            ptr->m_minSetting = query.value("MINSETTING").toFloat();
            ptr->m_stepSize = query.value("STEPSIZE").toFloat();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

OtherDataInfo::List DBOtherDataInfoDAO::doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok)
{
    bool bSucc = false;
    OtherDataInfo::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DIMENSION, a.REFERENCEVALUE, a.MAXSETTING, a.MINSETTING, a.STEPSIZE, b.IEDNAME, b.DATADESC, b.DATAVALUETYPE, b.DATASET, b.DATASETDESC FROM otherdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF AND b.DATASET=\"%2\"")
            .arg(iedName)
            .arg(setType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            OtherDataInfo::Ptr ptr(new OtherDataInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dimension = query.value("DIMENSION").toString();
            ptr->m_referenceValue = query.value("REFERENCEVALUE").toString();
            ptr->m_maxSetting = query.value("MAXSETTING").toFloat();
            ptr->m_minSetting = query.value("MINSETTING").toFloat();
            ptr->m_stepSize = query.value("STEPSIZE").toFloat();
            ptr->m_dataSet = query.value("DATASET").toString();
            ptr->m_dataSetDesc = query.value("DATASETDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBOtherDataInfoDAO::doInsert(OtherDataInfo::List &lst)
{
    bool bSucc = false;
    OtherDataInfo::List::iterator iter = lst.begin();
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
                OtherDataInfo::Ptr ptr(new OtherDataInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dimension = ptr->dimension();
                QString referenceValue = ptr->referenceValue();
                float maxValue = ptr->maxSetting();
                float minValue = ptr->minSetting();
                float stepSize = ptr->stepSize();

                sql = QObject::tr("REPLACE INTO otherdatainfo VALUES(NULL, \"%1\", \"%2\", %3, %4, \"%5\", %6)")
                        .arg(dataRef)//1
                        .arg(dimension)//2
                        .arg(maxValue)//3
                        .arg(minValue)//4
                        .arg(referenceValue)//5
                        .arg(stepSize);//6
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
                OtherDataInfo::Ptr ptr(new OtherDataInfo());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dimension = ptr->dimension();
                QString referenceValue = ptr->referenceValue();
                float maxValue = ptr->maxSetting();
                float minValue = ptr->minSetting();
                float stepSize = ptr->stepSize();

                sql = QObject::tr("REPLACE INTO otherdatainfo VALUES(NULL, \"%1\", \"%2\", %3, %4, \"%5\", %6)")
                        .arg(dataRef)//1
                        .arg(dimension)//2
                        .arg(maxValue)//3
                        .arg(minValue)//4
                        .arg(referenceValue)//5
                        .arg(stepSize);//6
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

bool DBOtherDataInfoDAO::doUpdate(const OtherDataInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE otherdatainfo SET DATAREF=\"%1\", DIMENSION=\"%2\", MAXSETTING=%3, MINSETTING=%4, REFERENCEVALUE=\"%5\", STEPSIZE=%6 WHERE GUID=%7")
                .arg(ptr->dataRef())
                .arg(ptr->dimension())
                .arg(ptr->maxSetting())
                .arg(ptr->minSetting())
                .arg(ptr->referenceValue())
                .arg(ptr->stepSize())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOtherDataInfoDAO::doUpdate(OtherDataInfo::List &lst)
{
    bool bSucc = false;
    OtherDataInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            OtherDataInfo::Ptr ptr(new OtherDataInfo());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE otherdatainfo SET DATAREF=\"%1\", DIMENSION=\"%2\", MAXSETTING=%3, MINSETTING=%4, REFERENCEVALUE=\"%5\", STEPSIZE=%6 WHERE GUID=%7")
                    .arg(ptr->dataRef())
                    .arg(ptr->dimension())
                    .arg(ptr->maxSetting())
                    .arg(ptr->minSetting())
                    .arg(ptr->referenceValue())
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

bool DBOtherDataInfoDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM otherdatainfo WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOtherDataInfoDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE a FROM otherdatainfo a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOtherDataInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM otherdatainfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='otherdatainfo'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOtherDataInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS otherdatainfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) UNIQUE NOT NULL,"
                                  "DIMENSION CHAR(255) NOT NULL,"
                                  "MAXSETTING FLOAT(8,3) NOT NULL,"
                                  "MINSETTING FLOAT(8,3) NOT NULL,"
                                  "REFERENCEVALUE CHAR(255) NOT NULL,"
                                  "STEPSIZE FLOAT(8,3) NOT NULL");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
