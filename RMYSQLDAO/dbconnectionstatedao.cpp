#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>
#include "connectionstate.h"
//#include "ied.h"
#include "dbconnectionreal.h"
//#include "dbiedinfodao.h"
#include "dbconnectionstatedao.h"
DBConnectionStateDAO::DBConnectionStateDAO()
    : m_connectionName("connectCState")
{

}

DBConnectionStateDAO::~DBConnectionStateDAO()
{

}

ConnectionState::List DBConnectionStateDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    ConnectionState::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("SELECT * FROM connectionstate");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                ConnectionState::Ptr ptr(new ConnectionState());
                ptr->m_dataValue = query.value("DATAVALUE").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

ConnectionState::Hash DBConnectionStateDAO::doQueryHash(bool *ok)
{
    bool bSucc = false;
    ConnectionState::Hash hsh;

    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("SELECT * FROM connectionstate");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                ConnectionState::Ptr ptr(new ConnectionState());
                ptr->m_dataValue = query.value("DATAVALUE").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
                QString iedName = ptr->iedName();
                hsh.insert(iedName, ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

ConnectionState::Hash DBConnectionStateDAO::doQueryHash(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    ConnectionState::Hash hsh;
    QSqlQuery query(db);

    QString sql = QObject::tr("SELECT * FROM connectionstate");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            ConnectionState::Ptr ptr(new ConnectionState());
            ptr->m_dataValue = query.value("DATAVALUE").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
            QString iedName = ptr->iedName();
            hsh.insert(iedName, ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

ConnectionState::Ptr DBConnectionStateDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("SELECT * FROM connectionstate WHERE IEDNAME='%1'")
                .arg(iedName);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                ConnectionState::Ptr ptr(new ConnectionState());
                ptr->m_dataValue = query.value("DATAVALUE").toInt();
                ptr->m_iedName = iedName;
                ptr->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
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

//bool DBConnectionStateDAO::doInit()
//{
//    bool bSucc = false;
//    DBIedInfoDAO dao_ied;
//    Ied::List lst_ied = dao_ied.doQuery();
//    if(lst_ied.size() == 0)
//        return bSucc;
//    ConnectionState::List lst_state;
//    Ied::List::iterator iter;
//    for(iter=lst_ied.begin(); iter!=lst_ied.end(); iter++)
//    {
//        Ied::Ptr ptr_ied(new Ied());
//        ptr_ied = *iter;
//        QString iedName = ptr_ied->iedName();
//        ConnectionState::Ptr ptr_state(new ConnectionState());
//        ptr_state->setIedName(iedName);
//        ptr_state->setDataValue(0);

//        QDateTime now_time = QDateTime::currentDateTime();
//        QString nowTime = now_time.toString("yyyy-MM-dd hh:mm:ss.zzz");
//        ptr_state->setLastUpdateTime(nowTime);
//        lst_state.append(ptr_state);
//    }
//    bSucc = doInsert(lst_state);
//    return bSucc;
//}

//bool DBConnectionStateDAO::doInit(QSqlDatabase db, QSqlDatabase dbR)
//{
//    bool bSucc = false;
//    DBIedInfoDAO dao_ied;
//    Ied::List lst_ied = dao_ied.doQuery(db);
//    if(lst_ied.size() == 0)
//        return bSucc;
//    ConnectionState::List lst_state;
//    Ied::List::iterator iter;
//    for(iter=lst_ied.begin(); iter!=lst_ied.end(); iter++)
//    {
//        Ied::Ptr ptr_ied(new Ied());
//        ptr_ied = *iter;
//        QString iedName = ptr_ied->iedName();
//        ConnectionState::Ptr ptr_state(new ConnectionState());
//        ptr_state->setIedName(iedName);
//        ptr_state->setDataValue(0);

//        QDateTime now_time = QDateTime::currentDateTime();
//        QString nowTime = now_time.toString("yyyy-MM-dd hh:mm:ss.zzz");
//        ptr_state->setLastUpdateTime(nowTime);
//        lst_state.append(ptr_state);
//    }
//    bSucc = doInsert(dbR, lst_state);
//    return bSucc;
//}

bool DBConnectionStateDAO::doUpdate(const ConnectionState::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("UPDATE connectionstate SET DATAVALUE=%1, LASTUPDATETIME='%2' WHERE IEDNAME='%3'")
                .arg(ptr->dataValue())
                .arg(ptr->lastUpdateTime())
                .arg(ptr->iedName());
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBConnectionStateDAO::doUpdate(QSqlDatabase db, const ConnectionState::Ptr &ptr)
{
    bool bSucc = false;
    //QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
//    if(db.isOpen() || db.open())
//    {

//        db.close();
//    }
    QSqlQuery query(db);

    QString sql = QObject::tr("UPDATE connectionstate SET DATAVALUE=%1, LASTUPDATETIME='%2' WHERE IEDNAME='%3'")
            .arg(ptr->dataValue())
            .arg(ptr->lastUpdateTime())
            .arg(ptr->iedName());
    bSucc = query.exec(sql);

    return bSucc;
}

bool DBConnectionStateDAO::doInsert(ConnectionState::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        ConnectionState::List::iterator iter;
        QString sql = "";
        query.exec("START TRANSACTION");
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            ConnectionState::Ptr ptr(new ConnectionState());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO connectionstate VALUES(NULL, '%1', %2, '%3')")
                    .arg(ptr->iedName())
                    .arg(ptr->dataValue())
                    .arg(ptr->lastUpdateTime());
            query.exec(sql);
        }

        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

bool DBConnectionStateDAO::doInsert(QSqlDatabase db, ConnectionState::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    //QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
//    if(db.isOpen() || db.open())
//    {

//        db.close();
//    }
    QSqlQuery query(db);
    ConnectionState::List::iterator iter;
    QString sql = "";
    query.exec("START TRANSACTION");
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        ConnectionState::Ptr ptr(new ConnectionState());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO connectionstate VALUES(NULL, '%1', %2, '%3')")
                .arg(ptr->iedName())
                .arg(ptr->dataValue())
                .arg(ptr->lastUpdateTime());
        query.exec(sql);
    }

    bSucc = query.exec("COMMIT");

    return bSucc;
}

bool DBConnectionStateDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS connectionstate("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAVALUE INT(11) NOT NULL,"
                                  "LASTUPDATETIME VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID),"
                                  "UNIQUE KEY UK_connectionstate_IEDNAME(IEDNAME))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBConnectionStateDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("TRUNCATE TABLE connectionstate");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBConnectionStateDAO::doClear(QSqlDatabase db)
{
    bool bSucc = false;
    //QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
//    if(db.isOpen() || db.open())
//    {

//        db.close();
//    }
    QSqlQuery query(db);

    QString sql = QObject::tr("TRUNCATE TABLE connectionstate");
    bSucc = query.exec(sql);

    return bSucc;
}
