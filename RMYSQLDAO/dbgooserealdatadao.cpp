#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QHash>
#include <QVariant>
#include "dbconnectionreal.h"
//#include "gooseinfo.h"
#include "gooserealdata.h"
//#include "dbgooseinfodao.h"
#include "dbgooserealdatadao.h"
DBGooseRealDataDAO::DBGooseRealDataDAO()
    : m_connectionName("connectGooseRealData")
{

}

DBGooseRealDataDAO::~DBGooseRealDataDAO()
{

}

quint32 DBGooseRealDataDAO::appIdInt(const QString &appId)
{
    quint32 x = appId.toInt(NULL, 10);
    return x;
}

QString DBGooseRealDataDAO::appIdString16(qint32 appId)
{
    QString str = QString::number(appId, 16);
    int addZ = 4 - str.size()%4;
    QString tmp = "0x";
    for(int i = 0; i < addZ; i++)
        tmp += "0";
    str = tmp + str;
    return str;
}

QString DBGooseRealDataDAO::appIdString(qint32 appId)
{
    QString str = QString::number(appId, 10);
    return str;
}

QHash<quint32, GooseRealData::Hash> DBGooseRealDataDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    QHash<quint32, GooseRealData::Hash> hashSet;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "goosedb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM gooserealdata");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                int GUID = query.value("GUID").toInt();
                QString appId_str = query.value("APPID").toString();
                quint32 appId = appIdInt(appId_str);
                QString dataRef = query.value("DATAREF").toString();
                QString iedName = query.value("IEDNAME").toString();
                int dataType = query.value("DATATYPE").toInt();
                QString dataValue = query.value("DATAVALUE").toString();
                QString updateTime = query.value("UPDATETIME").toString();
                if(!hashSet.contains(appId))
                {
                    GooseRealData::Hash gooseHash;
                    hashSet.insert(appId, gooseHash);
                }
                if(!hashSet.value(appId).contains(dataRef))
                {
                    GooseRealData::Ptr ptr(new GooseRealData());
                    ptr->m_GUID = GUID;
                    ptr->m_appId = appId;
                    ptr->m_dataRef = dataRef;
                    ptr->m_iedName = iedName;
                    ptr->m_dataType = dataType;
                    ptr->m_dataValue = dataValue;
                    ptr->m_updateTime = updateTime;
                    hashSet[appId].insert(dataRef, ptr);
                }
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hashSet;
}

QHash<quint32, GooseRealData::Hash> DBGooseRealDataDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    QHash<quint32, GooseRealData::Hash> hashSet;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM gooserealdata");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            int GUID = query.value("GUID").toInt();
            QString appId_str = query.value("APPID").toString();
            quint32 appId = appIdInt(appId_str);
            QString dataRef = query.value("DATAREF").toString();
            QString iedName = query.value("IEDNAME").toString();
            int dataType = query.value("DATATYPE").toInt();
            QString dataValue = query.value("DATAVALUE").toString();
            QString updateTime = query.value("UPDATETIME").toString();
            if(!hashSet.contains(appId))
            {
                GooseRealData::Hash gooseHash;
                hashSet.insert(appId, gooseHash);
            }
            if(!hashSet.value(appId).contains(dataRef))
            {
                GooseRealData::Ptr ptr(new GooseRealData());
                ptr->m_GUID = GUID;
                ptr->m_appId = appId;
                ptr->m_dataRef = dataRef;
                ptr->m_iedName = iedName;
                ptr->m_dataType = dataType;
                ptr->m_dataValue = dataValue;
                ptr->m_updateTime = updateTime;
                hashSet[appId].insert(dataRef, ptr);
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return hashSet;
}

GooseRealData::Ptr DBGooseRealDataDAO::doQuery(const QString &dataRef, quint32 appId, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "goosedb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString appId_str = QString::number(appId, 10);
        QString sql = QObject::tr("SELECT * FROM gooserealdata WHERE APPID='%1' AND DATAREF='%2'")
                .arg(appId_str)
                .arg(dataRef);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                GooseRealData::Ptr ptr(new GooseRealData());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_appId = appId;
                ptr->m_dataRef = dataRef;
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                ptr->m_dataValue = query.value("DATAVALUE").toString();
                ptr->m_updateTime = query.value("UPDATETIME").toString();
                db.close();
                if(ok)
                    *ok = bSucc;
                return ptr;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

GooseRealData::Ptr DBGooseRealDataDAO::doQuery(QSqlDatabase db, const QString &dataRef, quint32 appId, bool *ok)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString appId_str = QString::number(appId, 10);
    QString sql = QObject::tr("SELECT * FROM gooserealdata WHERE APPID='%1' AND DATAREF='%2'")
            .arg(appId_str)
            .arg(dataRef);
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            GooseRealData::Ptr ptr(new GooseRealData());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_appId = appId;
            ptr->m_dataRef = dataRef;
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            ptr->m_dataValue = query.value("DATAVALUE").toString();
            ptr->m_updateTime = query.value("UPDATETIME").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

GooseRealData::List DBGooseRealDataDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    GooseRealData::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "goosedb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM gooserealdata WHERE IEDNAME='%1'")
                .arg(iedName);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                GooseRealData::Ptr ptr(new GooseRealData());
                ptr->m_GUID = query.value("GUID").toInt();
                QString appId_str = query.value("APPID").toString();
                ptr->m_appId = appIdInt(appId_str);
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                ptr->m_dataValue = query.value("DATAVALUE").toString();
                ptr->m_updateTime = query.value("UPDATETIME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

//bool DBGooseRealDataDAO::doInit()
//{
//    this->doClear();
//    DBGooseInfoDAO dao;
//    GooseInfo::List lst = dao.doQuery();
//    if(lst.size() == 0)
//        return false;

//    GooseInfo::List::iterator iter;
//    GooseRealData::List lstR;
//    for(iter=lst.begin(); iter!=lst.end(); iter++)
//    {
//        GooseInfo::Ptr ptr(new GooseInfo());
//        ptr = *iter;
//        GooseRealData::Ptr ptrR(new GooseRealData());
//        QString appId_str = ptr->appId();
//        quint32 appId = appIdInt(appId_str);
//        ptrR->m_appId =appId;
//        ptrR->m_dataRef = ptr->dataRef();
//        ptrR->m_iedName = ptr->iedName();
//        ptrR->m_dataType = 0;
//        lstR.append(ptrR);
//    }
//    if(this->doInsert(lstR))
//        return true;
//    else
//        return false;
//}

//bool DBGooseRealDataDAO::doInit(QSqlDatabase db, QSqlDatabase dbR)
//{

//}

bool DBGooseRealDataDAO::doInsert(GooseRealData::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "goosedb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        GooseRealData::List::iterator iter;
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            GooseRealData::Ptr ptr(new GooseRealData());
            ptr = *iter;
            QString appId = appIdString(ptr->appId());

            sql = QObject::tr("INSERT INTO gooserealdata VALUES(NULL, '%1', '%2', '%3', %4, '%5', '%6')")
                    .arg(appId)//1
                    .arg(ptr->dataRef())//2
                    .arg(ptr->iedName())//3
                    .arg(ptr->dataType())//4
                    .arg(ptr->dataValue())//5
                    .arg(ptr->updateTime());//6
           if(!query.exec(sql))
           {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return false;
           }
        }
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

bool DBGooseRealDataDAO::doInsert(QSqlDatabase db, GooseRealData::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "INSERT INTO gooserealdata VALUES";
    GooseRealData::List::iterator iter;
    int itemCount = 0;
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        GooseRealData::Ptr ptr(new GooseRealData());
        ptr = *iter;
        QString appId = appIdString(ptr->appId());

//        sql = QObject::tr("INSERT INTO gooserealdata VALUES(NULL, '%1', '%2', '%3', %4, '%5', '%6')")
//                .arg(appId)//1
//                .arg(ptr->dataRef())//2
//                .arg(ptr->iedName())//3
//                .arg(ptr->dataType())//4
//                .arg(ptr->dataValue())//5
//                .arg(ptr->updateTime());//6
        QString dataRef = ptr->dataRef();
        QString iedName = ptr->iedName();
        int dataType = ptr->dataType();
        QString dataTypeStr = QString::number(dataType);
        QString dataValue = ptr->dataValue();
        QString updateTime = ptr->updateTime();
        sql += "(NULL, '" + appId + "', '" + dataRef + "', '" + iedName + "', " + dataTypeStr + ", '" + dataValue + "', '" + updateTime + "')";
        if(itemCount != 999 && iter!=lst.end()-1)
        {
            sql += ",";
        }
        itemCount++;
        if(itemCount == 1000 || iter==lst.end()-1)
        {
            //printf("sql(goose): %s\n", sql.toStdString().data());
            QByteArray ba = sql.toUtf8();
            QString sqlMix = QObject::tr(ba.data());
            if(!query.exec(sqlMix))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                return false;
            }
            itemCount = 0;
            sql = "INSERT INTO gooserealdata VALUES";
        }
    }
    bSucc = query.exec("COMMIT");

    return bSucc;
}

bool DBGooseRealDataDAO::doUpdate(GooseRealData::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    GooseRealData::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "goosedb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        while(iter < lst.end())
        {
            GooseRealData::Ptr ptr(new GooseRealData());
            ptr = *iter;
            QString appId = appIdString(ptr->appId());

            QString sql = QObject::tr("UPDATE gooserealdata SET DATATYPE=%1, DATAVALUE='%2', UPDATETIME='%3' WHERE APPID='%4' AND DATAREF='%5'")
                    .arg(ptr->dataType())//1
                    .arg(ptr->dataValue())//2
                    .arg(ptr->updateTime())//3
                    .arg(appId)//4
                    .arg(ptr->dataRef());//5
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }
            iter++;
        }
        bSucc = query.exec("COMMIT");
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }
    return bSucc;
}

bool DBGooseRealDataDAO::doUpdate(QSqlDatabase db, GooseRealData::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    GooseRealData::List::iterator iter = lst.begin();
    QSqlQuery query(db);
    query.exec("START TRANSACTION");

    while(iter < lst.end())
    {
        GooseRealData::Ptr ptr(new GooseRealData());
        ptr = *iter;
        QString appId = appIdString(ptr->appId());

        QString sql = QObject::tr("UPDATE gooserealdata SET DATATYPE=%1, DATAVALUE='%2', UPDATETIME='%3' WHERE APPID='%4' AND DATAREF='%5'")
                .arg(ptr->dataType())//1
                .arg(ptr->dataValue())//2
                .arg(ptr->updateTime())//3
                .arg(appId)//4
                .arg(ptr->dataRef());//5
        if(!query.exec(sql))
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
            return bSucc;
        }
        iter++;
    }
    bSucc = query.exec("COMMIT");
    if(!bSucc){
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }

    return bSucc;
}


bool DBGooseRealDataDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "goosedb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        bSucc = query.exec("TRUNCATE TABLE gooserealdata");
        db.close();
    }

    return bSucc;
}

bool DBGooseRealDataDAO::doClear(QSqlDatabase db)
{
    bool bSucc = false;
    QSqlQuery query(db);
    bSucc = query.exec("TRUNCATE TABLE gooserealdata");

    return bSucc;
}

bool DBGooseRealDataDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "goosedb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS gooserealdata("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "APPID INT(11) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "UPDATETIME VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID),"
                                  "UNIQUE KEY UK_gooserealdata_DATAREFANDAPPID(APPID, DATAREF))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
