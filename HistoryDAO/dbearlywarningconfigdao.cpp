#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include "dbconnection.h"
#include "earlywarningconfig.h"
#include "dbearlywarningconfigdao.h"
#include "dastruct.h"
#include "dbdastructdao.h"
//#include "realdata.h"
//#include "dbrealdatadao.h"
//#include "earlywarning.h"
//#include "dbearlywarningdao.h"
DBEarlyWarningConfigDAO::DBEarlyWarningConfigDAO()
    : m_connectionName("connectEWConfig")
{

}

DBEarlyWarningConfigDAO::~DBEarlyWarningConfigDAO()
{

}

EarlyWarningConfig::List DBEarlyWarningConfigDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.DATAREF=b.DATAREF");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataUnit = query.value("DATAUNIT").toString();
                ptr->m_ewType = query.value("EWTYPE").toInt();
                ptr->m_maxValue = query.value("MAXDATA").toFloat();
                ptr->m_minValue = query.value("MINDATA").toFloat();
                ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
                ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

EarlyWarningConfig::List DBEarlyWarningConfigDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataUnit = query.value("DATAUNIT").toString();
            ptr->m_ewType = query.value("EWTYPE").toInt();
            ptr->m_maxValue = query.value("MAXDATA").toFloat();
            ptr->m_minValue = query.value("MINDATA").toFloat();
            ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
            ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

EarlyWarningConfig::List DBEarlyWarningConfigDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.DATAREF=b.DATAREF AND b.IEDNAME=\"%1\"")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = iedName;
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataUnit = query.value("DATAUNIT").toString();
            ptr->m_ewType = query.value("EWTYPE").toInt();
            ptr->m_maxValue = query.value("MAXDATA").toFloat();
            ptr->m_minValue = query.value("MINDATA").toFloat();
            ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
            ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

EarlyWarningConfig::List DBEarlyWarningConfigDAO::doQuery(QSqlDatabase db, const QString &iedName, int ewType, bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE EWTYPE=%1 AND a.DATAREF=b.DATAREF AND b.IEDNAME=\"%2\"")
            .arg(ewType)
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = iedName;
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataUnit = query.value("DATAUNIT").toString();
            ptr->m_ewType = ewType;
            ptr->m_maxValue = query.value("MAXDATA").toFloat();
            ptr->m_minValue = query.value("MINDATA").toFloat();
            ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
            ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

EarlyWarningConfig::Hash DBEarlyWarningConfigDAO::doQueryHash(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::Hash hsh;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.DATAREF=b.DATAREF");
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataUnit = query.value("DATAUNIT").toString();
            ptr->m_ewType = query.value("EWTYPE").toInt();
            ptr->m_maxValue = query.value("MAXDATA").toFloat();
            ptr->m_minValue = query.value("MINDATA").toFloat();
            ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
            ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
            hsh.insert(ptr->m_dataRef, ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

EarlyWarningConfig::Hash DBEarlyWarningConfigDAO::doQueryHash(QSqlDatabase db, const QString &iedName, int ewType, bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::Hash hsh;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.EWTYPE=%1 AND a.DATAREF=b.DATAREF AND b.IEDNAME=\"%2\"")
            .arg(ewType)
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = iedName;
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataUnit = query.value("DATAUNIT").toString();
            ptr->m_ewType = ewType;
            ptr->m_maxValue = query.value("MAXDATA").toFloat();
            ptr->m_minValue = query.value("MINDATA").toFloat();
            ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
            ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
            if(!hsh.contains(ptr->m_dataRef))
                hsh.insert(ptr->m_dataRef, ptr);
        }
    }
    if(ok)
        *ok = bSucc;
    return hsh;
}

EarlyWarningConfig::Ptr DBEarlyWarningConfigDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.DATAREF=\"%1\" a.DATAREF=b.DATAREF")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataRef = dataRef;
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataUnit = query.value("DATAUNIT").toString();
            ptr->m_ewType = query.value("EWTYPE").toInt();
            ptr->m_maxValue = query.value("MAXDATA").toFloat();
            ptr->m_minValue = query.value("MINDATA").toFloat();
            ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
            ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

EarlyWarningConfig::Hash DBEarlyWarningConfigDAO::doQueryHash(bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::Hash hsh;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.DATAREF=b.DATAREF");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataUnit = query.value("DATAUNIT").toString();
                ptr->m_ewType = query.value("EWTYPE").toInt();
                ptr->m_maxValue = query.value("MAXDATA").toFloat();
                ptr->m_minValue = query.value("MINDATA").toFloat();
                ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
                ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
                hsh.insert(ptr->m_dataRef, ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

EarlyWarningConfig::Hash DBEarlyWarningConfigDAO::doQueryHash(const QString &iedName, int ewType, bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::Hash hsh;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.EWTYPE=%1 AND a.DATAREF=b.DATAREF AND b.IEDNAME=\"%2\"")
                .arg(ewType)
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = iedName;
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataUnit = query.value("DATAUNIT").toString();
                ptr->m_ewType = ewType;
                ptr->m_maxValue = query.value("MAXDATA").toFloat();
                ptr->m_minValue = query.value("MINDATA").toFloat();
                ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
                ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
                if(!hsh.contains(ptr->m_dataRef))
                    hsh.insert(ptr->m_dataRef, ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

EarlyWarningConfig::List DBEarlyWarningConfigDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.DATAREF=b.DATAREF AND b.IEDNAME=\"%1\"")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = iedName;
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataUnit = query.value("DATAUNIT").toString();
                ptr->m_ewType = query.value("EWTYPE").toInt();
                ptr->m_maxValue = query.value("MAXDATA").toFloat();
                ptr->m_minValue = query.value("MINDATA").toFloat();
                ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
                ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

EarlyWarningConfig::List DBEarlyWarningConfigDAO::doQuery(const QString &iedName, int ewType, bool *ok)
{
    bool bSucc = false;
    EarlyWarningConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE EWTYPE=%1 AND a.DATAREF=b.DATAREF AND b.IEDNAME=\"%2\"")
                .arg(ewType)
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = iedName;
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataUnit = query.value("DATAUNIT").toString();
                ptr->m_ewType = ewType;
                ptr->m_maxValue = query.value("MAXDATA").toFloat();
                ptr->m_minValue = query.value("MINDATA").toFloat();
                ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
                ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

EarlyWarningConfig::Ptr DBEarlyWarningConfigDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.EWTYPE, a.MAXDATA, a.MINDATA, a.MUTATIONVALUE, a.STORAGECYCLE, b.IEDNAME, b.DATADESC, b.DATAUNIT FROM earlywarningconfig a, ieddataset b WHERE a.DATAREF=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(dataRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = dataRef;
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataUnit = query.value("DATAUNIT").toString();
                ptr->m_ewType = query.value("EWTYPE").toInt();
                ptr->m_maxValue = query.value("MAXDATA").toFloat();
                ptr->m_minValue = query.value("MINDATA").toFloat();
                ptr->m_mutationValue = query.value("MUTATIONVALUE").toFloat();
                ptr->m_storageCycle = query.value("STORAGECYCLE").toInt();
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

bool DBEarlyWarningConfigDAO::doInsert(EarlyWarningConfig::List &lst)
{
    bool bSucc = false;
    EarlyWarningConfig::List::iterator iter = lst.begin();
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
                EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
                ptr = *iter;

                sql = QObject::tr("REPLACE INTO earlywarningconfig VALUES(NULL, \"%1\", %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14)")
                        .arg(ptr->dataRef())//1
                        .arg(ptr->ewType())//2
                        .arg(ptr->maxValue())//3
                        .arg(ptr->minValue())//4
                        .arg(ptr->mutationValue())//5
                        .arg(ptr->storageCycle())//6
                        .arg(ptr->upLimitStateEnable())//7
                        .arg(ptr->downLimitStateEnable())//8
                        .arg(ptr->mutationStateEnable())//9
                        .arg(ptr->lastCycleULStateEnable())//10
                        .arg(ptr->lastCycleDLStateEnable())//11
                        .arg(ptr->trendULStateEnable())//12
                        .arg(ptr->trendDLStateEnable())//13
                        .arg(ptr->isMonitor());//14
                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: %s\n", error_s.toStdString().data());
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
                EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
                ptr = *iter;

                sql = QObject::tr("REPLACE INTO earlywarningconfig VALUES(NULL, \"%1\", %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14)")
                        .arg(ptr->dataRef())//1
                        .arg(ptr->ewType())//2
                        .arg(ptr->maxValue())//3
                        .arg(ptr->minValue())//4
                        .arg(ptr->mutationValue())//5
                        .arg(ptr->storageCycle())//6
                        .arg(ptr->upLimitStateEnable())//7
                        .arg(ptr->downLimitStateEnable())//8
                        .arg(ptr->mutationStateEnable())//9
                        .arg(ptr->lastCycleULStateEnable())//10
                        .arg(ptr->lastCycleDLStateEnable())//11
                        .arg(ptr->trendULStateEnable())//12
                        .arg(ptr->trendDLStateEnable())//13
                        .arg(ptr->isMonitor());//14
                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: %s\n", error_s.toStdString().data());
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

bool DBEarlyWarningConfigDAO::doUpdate(const EarlyWarningConfig::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE earlywarningconfig SET DATAREF=\"%1\", EWTYPE=%2, MAXDATA=%3, MINDATA=%4, MUTATIONVALUE=%5, STORAGECYCLE=%6 WHERE GUID=%7")
                .arg(ptr->dataRef())//1
                .arg(ptr->ewType())//2
                .arg(ptr->maxValue())//3
                .arg(ptr->minValue())//4
                .arg(ptr->mutationValue())//5
                .arg(ptr->storageCycle())//6
                .arg(ptr->GUID());//7
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBEarlyWarningConfigDAO::doUpdate(EarlyWarningConfig::List &lst)
{
    bool bSucc = false;
    EarlyWarningConfig::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");
        while(iter < lst.end())
        {
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE earlywarningconfig SET DATAREF=\"%1\", EWTYPE=%2, MAXDATA=%3, MINDATA=%4, MUTATIONVALUE=%5, STORAGECYCLE=%6 WHERE GUID=%7")
                    .arg(ptr->dataRef())//1
                    .arg(ptr->ewType())//2
                    .arg(ptr->maxValue())//3
                    .arg(ptr->minValue())//4
                    .arg(ptr->mutationValue())//5
                    .arg(ptr->storageCycle())//6
                    .arg(ptr->GUID());//7
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

bool DBEarlyWarningConfigDAO::doUpdateSP(EarlyWarningConfig::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        EarlyWarningConfig::Hash hsh_new;
        EarlyWarningConfig::List::iterator iter = lst.begin();
        QSqlQuery query(db);
        QString sql = "";
        EarlyWarningConfig::List lst_insert;

        while(iter != lst.end())
        {
            if(iter == lst.begin())
                query.exec("begin transaction");
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr = *iter;
            //printf("iedName: %s\n", ptr->iedName().toStdString().data());

            sql = QObject::tr("UPDATE earlywarningconfig SET EWTYPE=%1, MAXDATA=%2, MINDATA=%3, MUTATIONVALUE=%4, STORAGECYCLE=%5 WHERE DATAREF=\"%6\"")
                    .arg(ptr->ewType())//1
                    .arg(ptr->maxValue())//2
                    .arg(ptr->minValue())//3
                    .arg(ptr->mutationValue())//4
                    .arg(ptr->storageCycle())//5
                    .arg(ptr->dataRef());//6

            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: update earlywarningconfig, %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }

            if(!hsh_new.contains(ptr->dataRef()))
                hsh_new.insert(ptr->dataRef(), ptr);

            //commit and deal old earl-warning type
            if(iter == lst.end()-1)
            {
                bSucc = query.exec("commit transaction");
                if(!bSucc)
                {
                    QString error_s = query.lastError().text();
                    printf("error: commit, %s", error_s.toStdString().data());
                }
                EarlyWarningConfig::Hash hsh_old = doQueryHash(ptr->iedName(), ptr->ewType());
                if(hsh_old.size() != 0)
                {
                    EarlyWarningConfig::List lst_dealOld;
                    EarlyWarningConfig::Hash::const_iterator iter_old = hsh_old.begin();
                    EarlyWarningConfig::Hash::const_iterator iter_new = hsh_new.begin();
                    while(iter_old != hsh_old.end())
                    {
                        if(!hsh_new.contains(iter_old.key()))
                        {
                            EarlyWarningConfig::Ptr ptr_old = hsh_old.value(iter_old.key());
                            lst_dealOld.append(ptr_old);
                        }
                        iter_old++;
                    }
                    while(iter_new != hsh_new.end())
                    {
                        if(!hsh_old.contains(iter_new.key()))
                        {
                            EarlyWarningConfig::Ptr ptr_new = hsh_new.value(iter_new.key());
                            lst_insert.append(ptr_new);
                        }
                        iter_new++;
                    }

                    doDelete(lst_dealOld);
                    doInsert(lst_insert);
                }
            }

            iter++;
        }
        db.close();
    }

    return bSucc;
}

bool DBEarlyWarningConfigDAO::updateEnable(EarlyWarningConfig::List &lst)
{
    bool bSucc = false;
    EarlyWarningConfig::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");
        while(iter < lst.end())
        {
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE earlywarningconfig SET UPLIMITSTATEENABLE=%1, DOWNLIMITSTATEENABLE=%2, MUTATIONSTATEENABLE=%3, LASTCYCLEULSTATEENABLE=%4, LASTCYCLEDLSTATEENABLE=%5, TRENDULSTATEENABLE=%6, TRENDDLSTATEENABLE=%7, ISMONITOR=%8 WHERE DATAREF=\"%9\"")
                    .arg(ptr->upLimitStateEnable())//1
                    .arg(ptr->downLimitStateEnable())//2
                    .arg(ptr->mutationStateEnable())//3
                    .arg(ptr->lastCycleULStateEnable())//4
                    .arg(ptr->lastCycleDLStateEnable())//5
                    .arg(ptr->trendULStateEnable())//6
                    .arg(ptr->trendDLStateEnable())//7
                    .arg(ptr->isMonitor())//8
                    .arg(ptr->dataRef());//9
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

bool DBEarlyWarningConfigDAO::doDelete(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM earlywarningconfig WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBEarlyWarningConfigDAO::doDelete(EarlyWarningConfig::List &lst)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        EarlyWarningConfig::List::iterator iter;
        QSqlQuery query(db);
        query.exec("begin transaction");
        QString sql = "";
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            EarlyWarningConfig::Ptr ptr(new EarlyWarningConfig());
            ptr = *iter;
            sql = QObject::tr("DELETE FROM earlywarningconfig WHERE DATAREF=\"%1\"")
                    .arg(ptr->dataRef());
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: delete earlywarningconfig(lst), %s", error_s.toStdString().data());
            }
        }

        bSucc = query.exec("commit transaction");
        db.close();
    }
    return bSucc;
}

bool DBEarlyWarningConfigDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM earlywarningconfig");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='earlywarningconfig'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBEarlyWarningConfigDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS earlywarningconfig("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) NOT NULL,"
                                  "EWTYPE INTEGER NOT NULL,"
                                  "MAXDATA CHAR(255) NOT NULL,"
                                  "MINDATA CHAR(255) NOT NULL,"
                                  "MUTATIONVALUE FLOAT(8,3) NOT NULL,"
                                  "STORAGECYCLE INTEGER NOT NULL,"
                                  "UPLIMITSTATEENABLE INTEGER NOT NULL,"
                                  "DOWNLIMITSTATEENABLE INTEGER NOT NULL,"
                                  "MUTATIONSTATEENABLE INTEGER NOT NULL,"
                                  "LASTCYCLEULSTATEENABLE INTEGER NOT NULL,"
                                  "LASTCYCLEDLSTATEENABLE INTEGER NOT NULL,"
                                  "TRENDULSTATEENABLE INTEGER NOT NULL,"
                                  "TRENDDLSTATEENABLE INTEGER NOT NULL");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
