#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "primarydeviceinfo.h"
#include "dbconnection.h"
#include "dbprimarydeviceinfodao.h"
#include "ieddataset.h"
#include "dbieddatasetdao.h"
DBPrimaryDeviceInfoDAO::DBPrimaryDeviceInfoDAO()
    : m_connectionName("connectPrimaryDeviceInfo")
{
    doCreateTable();
}

DBPrimaryDeviceInfoDAO::~DBPrimaryDeviceInfoDAO()
{

}

PrimaryDeviceInfo::List DBPrimaryDeviceInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    PrimaryDeviceInfo::List lst;
    DBIedDataSetDAO dao;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM primarydeviceinfo");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_devName = query.value("DEVNAME").toString();
                ptr->m_devDesc = query.value("DEVDESC").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_devType = query.value("DEVTYPE").toString();
                IedDataSet::List lstData = dao.doQueryByDevName(ptr->devName());
                if(lstData.size() != 0)
                {
                    IedDataSet::List::iterator iterData;
                    for(iterData=lstData.begin(); iterData!=lstData.end(); iterData++)
                    {
                        IedDataSet::Ptr ptrData(new IedDataSet());
                        ptrData = *iterData;
                        ptr->addDataRef(ptrData->dataRef());
                    }
                }
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

PrimaryDeviceInfo::List DBPrimaryDeviceInfoDAO::doQueryByBayName(const QString &bayName, bool *ok)
{
    bool bSucc = false;
    PrimaryDeviceInfo::List lst;
    DBIedDataSetDAO dao;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DEVNAME, a.DEVDESC, a.SCHEDULENAME, a.DEVTYPE FROM primarydeviceinfo a, ieddataset b, iedinfo c WHERE a.DEVNAME=b.DEVNAME AND b.IEDNAME=a.IEDNAME AND a.BAYID=\"%1\"")
                .arg(bayName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_devName = query.value("DEVNAME").toString();
                ptr->m_devDesc = query.value("DEVDESC").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_devType = query.value("DEVTYPE").toString();
                IedDataSet::List lstData = dao.doQueryByDevName(ptr->devName());
                if(lstData.size() != 0)
                {
                    IedDataSet::List::iterator iterData;
                    for(iterData=lstData.begin(); iterData!=lstData.end(); iterData++)
                    {
                        IedDataSet::Ptr ptrData(new IedDataSet());
                        ptrData = *iterData;
                        ptr->addDataRef(ptrData->dataRef());
                    }
                }
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

PrimaryDeviceInfo::Hash DBPrimaryDeviceInfoDAO::doQueryLineRelation(bool *ok)
{
    bool bSucc = false;
    PrimaryDeviceInfo::Hash hsh;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.STATIONID, a.VOLTCLASSID, a.BAYID, c.DEVTYPE, b.DATAREF, c.DEVNAME, c.SCHEDULENAME FROM iedinfo a, ieddataset b, primarydeviceinfo c WHERE a.IEDNAME=b.IEDNAME AND b.DEVNAME=c.DEVNAME");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
                QString dataRef = query.value("DATAREF").toString();
                ptr->m_devName = query.value("DEVNAME").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_stationName = query.value("STATIONID").toString();
                ptr->m_voltClass = query.value("VOLTCLASSID").toString();
                ptr->m_bayName = query.value("BAYID").toString();
                ptr->m_devType = query.value("DEVTYPE").toString();
                if(!hsh.contains(dataRef))
                    hsh.insert(dataRef, ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

PrimaryDeviceInfo::Ptr DBPrimaryDeviceInfoDAO::doQueryByScheduleName(const QString &scheduleName, bool *ok)
{
    bool bSucc = false;
    DBIedDataSetDAO dao;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM primarydeviceinfo WHERE SCHEDULENAME=\"%1\"")
                .arg(scheduleName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_devName = query.value("DEVNAME").toString();
                ptr->m_devDesc = query.value("DEVDESC").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_devType = query.value("DEVTYPE").toString();
                IedDataSet::List lstData = dao.doQueryByDevName(ptr->devName());
                if(lstData.size() != 0)
                {
                    IedDataSet::List::iterator iterData;
                    for(iterData=lstData.begin(); iterData!=lstData.end(); iterData++)
                    {
                        IedDataSet::Ptr ptrData(new IedDataSet());
                        ptrData = *iterData;
                        ptr->addDataRef(ptrData->dataRef());
                    }
                }
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

PrimaryDeviceInfo::Ptr DBPrimaryDeviceInfoDAO::doQueryByDevName(const QString &devName, bool *ok)
{
    bool bSucc = false;
    DBIedDataSetDAO dao;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM primarydeviceinfo WHERE DEVNAME=\"%1\"")
                .arg(devName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_devName = query.value("DEVNAME").toString();
                ptr->m_devDesc = query.value("DEVDESC").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_devType = query.value("DEVTYPE").toString();
                IedDataSet::List lstData = dao.doQueryByDevName(ptr->devName());
                if(lstData.size() != 0)
                {
                    IedDataSet::List::iterator iterData;
                    for(iterData=lstData.begin(); iterData!=lstData.end(); iterData++)
                    {
                        IedDataSet::Ptr ptrData(new IedDataSet());
                        ptrData = *iterData;
                        ptr->addDataRef(ptrData->dataRef());
                    }
                }
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

PrimaryDeviceInfo::List DBPrimaryDeviceInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    PrimaryDeviceInfo::List lst;
    DBIedDataSetDAO dao;
    QString sql = QObject::tr("SELECT * FROM primarydeviceinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_devName = query.value("DEVNAME").toString();
            ptr->m_devDesc = query.value("DEVDESC").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_devType = query.value("DEVTYPE").toString();
            IedDataSet::List lstData = dao.doQueryByDevName(db, ptr->devName());
            if(lstData.size() != 0)
            {
                IedDataSet::List::iterator iterData;
                for(iterData=lstData.begin(); iterData!=lstData.end(); iterData++)
                {
                    IedDataSet::Ptr ptrData(new IedDataSet());
                    ptrData = *iterData;
                    ptr->addDataRef(ptrData->dataRef());
                }
            }
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

PrimaryDeviceInfo::List DBPrimaryDeviceInfoDAO::doQueryByBayName(QSqlDatabase db, const QString &bayName, bool *ok)
{
    bool bSucc = false;
    PrimaryDeviceInfo::List lst;
    DBIedDataSetDAO dao;
    QString sql = QObject::tr("SELECT a.GUID, a.DEVNAME, a.DEVDESC, a.SCHEDULENAME, a.DEVTYPE FROM primarydeviceinfo a, ieddataset b, iedinfo c WHERE a.DEVNAME=b.DEVNAME AND b.IEDNAME=a.IEDNAME AND a.BAYID=\"%1\"")
            .arg(bayName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_devName = query.value("DEVNAME").toString();
            ptr->m_devDesc = query.value("DEVDESC").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_devType = query.value("DEVTYPE").toString();
            IedDataSet::List lstData = dao.doQueryByDevName(db, ptr->devName());
            if(lstData.size() != 0)
            {
                IedDataSet::List::iterator iterData;
                for(iterData=lstData.begin(); iterData!=lstData.end(); iterData++)
                {
                    IedDataSet::Ptr ptrData(new IedDataSet());
                    ptrData = *iterData;
                    ptr->addDataRef(ptrData->dataRef());
                }
            }
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

PrimaryDeviceInfo::Hash DBPrimaryDeviceInfoDAO::doQueryLineRelation(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    PrimaryDeviceInfo::Hash hsh;
    QString sql = QObject::tr("SELECT a.STATIONID, a.VOLTCLASSID, a.BAYID, c.DEVTYPE, b.DATAREF, c.DEVNAME, c.SCHEDULENAME FROM iedinfo a, ieddataset b, primarydeviceinfo c WHERE a.IEDNAME=b.IEDNAME AND b.DEVNAME=c.DEVNAME");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
            QString dataRef = query.value("DATAREF").toString();
            ptr->m_devName = query.value("DEVNAME").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_stationName = query.value("STATIONID").toString();
            ptr->m_voltClass = query.value("VOLTCLASSID").toString();
            ptr->m_bayName = query.value("BAYID").toString();
            ptr->m_devType = query.value("DEVTYPE").toString();
            if(!hsh.contains(dataRef))
                hsh.insert(dataRef, ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

PrimaryDeviceInfo::Ptr DBPrimaryDeviceInfoDAO::doQueryByScheduleName(QSqlDatabase db, const QString &scheduleName, bool *ok)
{
    bool bSucc = false;
    DBIedDataSetDAO dao;
    QString sql = QObject::tr("SELECT * FROM primarydeviceinfo WHERE SCHEDULENAME=\"%1\"")
            .arg(scheduleName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_devName = query.value("DEVNAME").toString();
            ptr->m_devDesc = query.value("DEVDESC").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_devType = query.value("DEVTYPE").toString();
            IedDataSet::List lstData = dao.doQueryByDevName(db, ptr->devName());
            if(lstData.size() != 0)
            {
                IedDataSet::List::iterator iterData;
                for(iterData=lstData.begin(); iterData!=lstData.end(); iterData++)
                {
                    IedDataSet::Ptr ptrData(new IedDataSet());
                    ptrData = *iterData;
                    ptr->addDataRef(ptrData->dataRef());
                }
            }
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

PrimaryDeviceInfo::Ptr DBPrimaryDeviceInfoDAO::doQueryByDevName(QSqlDatabase db, const QString &devName, bool *ok)
{
    bool bSucc = false;
    DBIedDataSetDAO dao;
    QString sql = QObject::tr("SELECT * FROM primarydeviceinfo WHERE DEVNAME=\"%1\"")
            .arg(devName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_devName = query.value("DEVNAME").toString();
            ptr->m_devDesc = query.value("DEVDESC").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_devType = query.value("DEVTYPE").toString();
            IedDataSet::List lstData = dao.doQueryByDevName(db, ptr->devName());
            if(lstData.size() != 0)
            {
                IedDataSet::List::iterator iterData;
                for(iterData=lstData.begin(); iterData!=lstData.end(); iterData++)
                {
                    IedDataSet::Ptr ptrData(new IedDataSet());
                    ptrData = *iterData;
                    ptr->addDataRef(ptrData->dataRef());
                }
            }
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

bool DBPrimaryDeviceInfoDAO::doInsert(PrimaryDeviceInfo::List &lst)
{
    bool bSucc = false;
    PrimaryDeviceInfo::List::iterator iter = lst.begin();
    IedDataSet::List lst_iedData;
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
                PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO primarydeviceinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\")")
                        .arg(ptr->devName())
                        .arg(ptr->devDesc())
                        .arg(ptr->scheduleName())
                        .arg(ptr->devType());
                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: %s", error_s.toStdString().data());
                    db.close();
                    return bSucc;
                }

                foreach (QString ref, ptr->m_lstDataRef) {
                    IedDataSet::Ptr ptr_d(new IedDataSet());
                    ptr_d->setDataRef(ref);
                    ptr_d->setDevName(ptr->devName());
                    lst_iedData.append(ptr_d);
                }

                iter++;
            }
        }
        else
        {
            int count = 0;
            while(iter < lst.end())
            {
                PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO primarydeviceinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\")")
                        .arg(ptr->devName())
                        .arg(ptr->devDesc())
                        .arg(ptr->scheduleName())
                        .arg(ptr->devType());
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

                foreach (QString ref, ptr->m_lstDataRef) {
                    IedDataSet::Ptr ptr_d(new IedDataSet());
                    ptr_d->setDataRef(ref);
                    ptr_d->setDevName(ptr->devName());
                    lst_iedData.append(ptr_d);
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

        DBIedDataSetDAO dao_dataSet;
        bSucc = dao_dataSet.doUpdate(lst_iedData, 0);
    }
    return bSucc;
}

bool DBPrimaryDeviceInfoDAO::doUpdate(const PrimaryDeviceInfo::Ptr &ptr)
{
    bool bSucc = false;
    IedDataSet::List lst;
    DBIedDataSetDAO dao;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE primarydeviceinfo SET DEVNAME=\"%1\", DEVDESC=\"%2\", SCHEDULENAME=\"%3\", DEVTYPE=\"%4\" WHERE GUID=%5")
                .arg(ptr->devName())
                .arg(ptr->devDesc())
                .arg(ptr->scheduleName())
                .arg(ptr->devType())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();

        if(ptr->m_lstDataRef.size() != 0)
        {
            foreach (QString ref, ptr->m_lstDataRef) {
                IedDataSet::Ptr ptr_d(new IedDataSet());
                ptr_d->setDataRef(ref);
                ptr_d->setDevName(ptr->devName());
                lst.append(ptr_d);
            }
        }
        else
        {
            IedDataSet::Ptr ptr_d(new IedDataSet());
            ptr_d->setDevName(ptr->devName());
            ptr_d->setDataRef("");
            lst.append(ptr_d);
        }

        if(lst.size() != 0)
        {
            bSucc = dao.doUpdate(lst, 0);
        }
    }
    return bSucc;
}

bool DBPrimaryDeviceInfoDAO::doUpdate(PrimaryDeviceInfo::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    IedDataSet::List lstData;
    DBIedDataSetDAO dao;
    PrimaryDeviceInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            PrimaryDeviceInfo::Ptr ptr(new PrimaryDeviceInfo());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE primarydeviceinfo SET DEVNAME=\"%1\", DEVDESC=\"%2\", SCHEDULENAME=\"%3\", DEVTYPE=\"%4\" WHERE GUID=%5")
                    .arg(ptr->devName())
                    .arg(ptr->devDesc())
                    .arg(ptr->scheduleName())
                    .arg(ptr->devType())
                    .arg(ptr->GUID());

            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }
            if(ptr->m_lstDataRef.size() != 0)
            {
                foreach (QString ref, ptr->m_lstDataRef) {
                    IedDataSet::Ptr ptr_d(new IedDataSet());
                    ptr_d->setDataRef(ref);
                    ptr_d->setDevName(ptr->devName());
                    lstData.append(ptr_d);
                }
            }
            else
            {
                IedDataSet::Ptr ptr_d(new IedDataSet());
                ptr_d->setDevName(ptr->devName());
                ptr_d->setDataRef("");
                lstData.append(ptr_d);
            }
            iter++;
        }
        bSucc = query.exec("commit transaction");
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
        if(lstData.size() != 0)
            bSucc = dao.doUpdate(lstData, 0);
    }
    return bSucc;
}

bool DBPrimaryDeviceInfoDAO::doDeleteByDevName(const QString &devName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM primarydeviceinfo WHERE DEVNAME=\"%1\"")
                .arg(devName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBPrimaryDeviceInfoDAO::doDeleteByScheduleName(const QString &scheduleName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM primarydeviceinfo WHERE SCHEDULENAME=\"%1\"")
                .arg(scheduleName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBPrimaryDeviceInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM primarydeviceinfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='primarydeviceinfo'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBPrimaryDeviceInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS primarydeviceinfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DEVNAME CHAR(255) UNIQUE NOT NULL,"
                                  "DEVDESC CHAR(255) NOT NULL,"
                                  "SCHEDULENAME CHAR(255) NOT NULL,"
                                  "DEVTYPE CHAR(255) NOT NULL");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
