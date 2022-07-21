#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QHash>
#include "dbiedrealstatedao.h"
#include "dbconnectionreal.h"
//#include "gooseinfo.h"
//#include "dbgooseinfodao.h"
DBIedRealStateDAO::DBIedRealStateDAO()
    : m_connectionName("connectIedState")
{

}

DBIedRealStateDAO::~DBIedRealStateDAO()
{

}

IedState::Ptr DBIedRealStateDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM iedstate WHERE IEDNAME='%1'")
                .arg(iedName);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                IedState::Ptr ptr(new IedState());
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_iedState = query.value("STATE").toInt();
                ptr->m_updateTime = query.value("UPDATETIME").toString();
                ptr->m_setType = query.value("SETTYPE").toString();
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

IedState::List DBIedRealStateDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    IedState::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM iedstate");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                IedState::Ptr ptr(new IedState());
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_iedState = query.value("STATE").toInt();
                ptr->m_updateTime = query.value("UPDATETIME").toString();
                ptr->m_setType = query.value("SETTYPE").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;


    return lst;
}

IedState::List DBIedRealStateDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    IedState::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM iedstate");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            IedState::Ptr ptr(new IedState());
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_bayName = query.value("BAYNAME").toString();
            //ptr->m_shouldIedState = query.value("SHOULDIEDSTATE").toInt();
            ptr->m_iedState = query.value("STATE").toInt();
            //ptr->m_devCorrespondingState = query.value("DEVCORRESPONDINGSTATE").toInt();
            ptr->m_updateTime = query.value("UPDATETIME").toString();
            ptr->m_setType = query.value("SETTYPE").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

IedState::Hash DBIedRealStateDAO::doQueryHash(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    IedState::Hash hsh;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM iedstate");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            IedState::Ptr ptr(new IedState());
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_bayName = query.value("BAYNAME").toString();
            //ptr->m_shouldIedState = query.value("SHOULDIEDSTATE").toInt();
            ptr->m_iedState = query.value("STATE").toInt();
            //ptr->m_devCorrespondingState = query.value("DEVCORRESPONDINGSTATE").toInt();
            ptr->m_updateTime = query.value("UPDATETIME").toString();
            ptr->m_setType = query.value("SETTYPE").toString();
            hsh.insert(ptr->iedName(), ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

IedState::Ptr DBIedRealStateDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM iedstate WHERE IEDNAME='%1'")
            .arg(iedName);
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            IedState::Ptr ptr(new IedState());
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_bayName = query.value("BAYNAME").toString();
            //ptr->m_shouldIedState = query.value("SHOULDIEDSTATE").toInt();
            ptr->m_iedState = query.value("STATE").toInt();
            //ptr->m_devCorrespondingState = query.value("DEVCORRESPONDINGSTATE").toInt();
            ptr->m_updateTime = query.value("UPDATETIME").toString();
            ptr->m_setType = query.value("SETTYPE").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

//bool DBIedRealStateDAO::doInit(QSqlDatabase db, QSqlDatabase dbR)
//{
//    bool bSucc = false;
//    doClear(dbR);
//    QHash<QString, QString> hsh;
//    IedState::List lst;
//    DBGooseInfoDAO daoGooseInfo;
//    GooseInfo::List lstGooseInfo = daoGooseInfo.doQueryUsingIed(db);
//    GooseInfo::List::iterator iter;
//    for(iter=lstGooseInfo.begin(); iter!=lstGooseInfo.end(); iter++)
//    {
//        GooseInfo::Ptr ptr(new GooseInfo());
//        ptr = *iter;
//        QString iedName = ptr->iedName();
//        QString bayName = ptr->bayName();
//        if(hsh.count(iedName) == 0)
//        {
//            hsh.insert(iedName, bayName);
//            IedState::Ptr ptrState(new IedState());
//            ptrState->m_iedName = iedName;
//            ptrState->m_bayName = bayName;
//            lst.append(ptrState);
//        }
//    }
//    bSucc = doInsert(dbR, lst);

//    return bSucc;
//}

bool DBIedRealStateDAO::doInsert(QSqlDatabase db, IedState::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    IedState::List::iterator iter;
    int count = 0;
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        IedState::Ptr ptr(new IedState());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO iedstate VALUES(NULL, '%1', '%2', %3, '%4', '%5')")
                .arg(ptr->iedName())//1
                .arg(ptr->bayName())//2
                .arg(ptr->iedState())//3
                .arg(ptr->updateTime())//4
                .arg(ptr->setType());//5
        if(!query.exec(sql))
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
            return false;
        }
        count++;
    }
    bSucc = query.exec("COMMIT");

    return bSucc;
}

bool DBIedRealStateDAO::doClear(QSqlDatabase db)
{
    bool bSucc = false;
    QSqlQuery query(db);
    bSucc = query.exec("TRUNCATE TABLE iedstate");

    return bSucc;
}

bool DBIedRealStateDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS iedstate("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "BAYNAME VARCHAR(255) NOT NULL,"
                                  "STATE INT(11) NOT NULL,"
                                  "UPDATETIME VARCHAR(255) NOT NULL,"
                                  "SETTYPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID),"
                                  "UNIQUE KEY UK_iedstate_IEDNAME(IEDNAME))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}



