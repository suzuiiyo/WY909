#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QSqlError>
#include "stationinfo.h"
#include "dbconnection.h"
#include "dbstationinfodao.h"
#include "dbvoltclassinfodao.h"
#include "dbvirloopconfigdao.h"
#include "dbfibreopticaldao.h"
#include "dboptportdao.h"
#include "dbsoftversiondao.h"
#include "dbpatroldao.h"
DBStationInfoDAO::DBStationInfoDAO()
    : m_connectionName("connectStationInfo")
{
    doCreateTable();
}

DBStationInfoDAO::~DBStationInfoDAO()
{

}

StationInfo::List DBStationInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    StationInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM stationinfo");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                StationInfo::Ptr ptr(new StationInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_stationName = query.value("STATIONNAME").toString();
                ptr->m_stationDesc = query.value("STATIONDESC").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_longitude = query.value("LONGITUDE").toString();
                ptr->m_latitude = query.value("LATITUDE").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

StationInfo::List DBStationInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    StationInfo::List lst;
    QString sql = QObject::tr("SELECT * FROM stationinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            StationInfo::Ptr ptr(new StationInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_stationName = query.value("STATIONNAME").toString();
            ptr->m_stationDesc = query.value("STATIONDESC").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_longitude = query.value("LONGITUDE").toString();
            ptr->m_latitude = query.value("LATITUDE").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

StationInfo::Ptr DBStationInfoDAO::doQuery(const QString &stationName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM stationinfo WHERE STATIONNAME=\"%1\"")
                .arg(stationName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                StationInfo::Ptr ptr(new StationInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_stationName = query.value("STATIONNAME").toString();
                ptr->m_stationDesc = query.value("STATIONDESC").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_longitude = query.value("LONGITUDE").toString();
                ptr->m_latitude = query.value("LATITUDE").toString();
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

StationInfo::Hash DBStationInfoDAO::doQueryHash(bool *ok)
{
    bool bSucc = false;
    StationInfo::Hash hsh;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM stationinfo");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                StationInfo::Ptr ptr(new StationInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_stationName = query.value("STATIONNAME").toString();
                ptr->m_stationDesc = query.value("STATIONDESC").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_longitude = query.value("LONGITUDE").toString();
                ptr->m_latitude = query.value("LATITUDE").toString();
                hsh.insert(ptr->stationName(), ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

StationInfo::Ptr DBStationInfoDAO::doQuery(QSqlDatabase db, const QString &stationName, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM stationinfo WHERE STATIONNAME=\"%1\"")
            .arg(stationName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            StationInfo::Ptr ptr(new StationInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_stationName = query.value("STATIONNAME").toString();
            ptr->m_stationDesc = query.value("STATIONDESC").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_longitude = query.value("LONGITUDE").toString();
            ptr->m_latitude = query.value("LATITUDE").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

StationInfo::Hash DBStationInfoDAO::doQueryHash(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    StationInfo::Hash hsh;
    QString sql = QObject::tr("SELECT * FROM stationinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            StationInfo::Ptr ptr(new StationInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_stationName = query.value("STATIONNAME").toString();
            ptr->m_stationDesc = query.value("STATIONDESC").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_longitude = query.value("LONGITUDE").toString();
            ptr->m_latitude = query.value("LATITUDE").toString();
            hsh.insert(ptr->stationName(), ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

bool DBStationInfoDAO::doInsert(StationInfo::List &lst)
{
    bool bSucc = false;
    StationInfo::List::iterator iter = lst.begin();
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
                StationInfo::Ptr ptr(new StationInfo());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO stationinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\")")
                        .arg(ptr->stationName())
                        .arg(ptr->stationDesc())
                        .arg(ptr->scheduleName())
                        .arg(ptr->longitude())
                        .arg(ptr->latitude());
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
                StationInfo::Ptr ptr(new StationInfo());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO stationinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\")")
                        .arg(ptr->stationName())
                        .arg(ptr->stationDesc())
                        .arg(ptr->scheduleName())
                        .arg(ptr->longitude())
                        .arg(ptr->latitude());
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

bool DBStationInfoDAO::doUpdate(const StationInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE stationinfo SET STATIONNAME=\"%1\", STATIONDESC=\"%2\", SCHEDULENAME=\"%3\", LONGITUDE=\"%4\", LATITUDE=\"%5\" WHERE GUID=%6")
                .arg(ptr->stationName())
                .arg(ptr->stationDesc())
                .arg(ptr->scheduleName())
                .arg(ptr->longitude())
                .arg(ptr->latitude())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBStationInfoDAO::doUpdate(StationInfo::List &lst)
{
    bool bSucc = false;
    StationInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            StationInfo::Ptr ptr(new StationInfo());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE stationinfo SET STATIONNAME=\"%1\", STATIONDESC=\"%2\", SCHEDULENAME=\"%3\", LONGITUDE=\"%4\", LATITUDE=\"%5\" WHERE GUID=%6")
                    .arg(ptr->stationName())
                    .arg(ptr->stationDesc())
                    .arg(ptr->scheduleName())
                    .arg(ptr->longitude())
                    .arg(ptr->latitude())
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

bool DBStationInfoDAO::doDelete(const QString &stationName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM stationinfo WHERE STATIONNAME=\"%1\"")
                .arg(stationName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBStationInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM stationinfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='stationinfo'");
        bSucc = query.exec(sql);
        db.close();
        DBVoltClassInfoDAO dao;
        bSucc = dao.doClear();
        DBVirLoopConfigDAO daoVir;
        bSucc = daoVir.doClear();
        DBFibreOpticalDAO daoFib;
        bSucc = daoFib.doClear();
        DBOptPortDAO daoOpt;
        bSucc = daoOpt.doClear();
        DBSoftVersionDAO daoSoftVer;
        bSucc = daoSoftVer.doClear();
        DBPatrolDAO daoPatrol;
        bSucc = daoPatrol.doClear();
    }
    return bSucc;
}

bool DBStationInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS stationinfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "STATIONNAME CHAR(255) UNIQUE NOT NULL,"
                                  "STATIONDESC CHAR(255) NOT NULL,"
                                  "SCHEDULENAME CHAR(255) NOT NULL,"
                                  "LONGITUDE CHAR(255) NOT NULL,"
                                  "LATITUDE CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
