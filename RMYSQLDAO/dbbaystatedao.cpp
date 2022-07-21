#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include "dbconnectionreal.h"
#include "baystate.h"
//#include "bayinfo.h"
//#include "dbbayinfodao.h"
#include "dbbaystatedao.h"
DBBayStateDAO::DBBayStateDAO()
    : m_connectionName("connectBayState")
{

}

DBBayStateDAO::~DBBayStateDAO()
{

}

BayState::Ptr DBBayStateDAO::doQuery(const QString &bayName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("SELECT * FROM baystate WHERE BAYNAME='%1'")
                .arg(bayName);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                BayState::Ptr ptr(new BayState());
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_bayState = query.value("STATE").toInt();
                ptr->m_setType = query.value("SETTYPE").toString();
                ptr->m_updateTime = query.value("UPDATETIME").toString();
                ptr->m_devCorrespondingState = query.value("DEVCORRESPONDINGSTATE").toInt();
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

BayState::List DBBayStateDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    BayState::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        QString sql = QObject::tr("SELECT * FROM baystate");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                BayState::Ptr ptr(new BayState());
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_bayState = query.value("STATE").toInt();
                ptr->m_setType = query.value("SETTYPE").toString();
                ptr->m_updateTime = query.value("UPDATETIME").toString();
                ptr->m_devCorrespondingState = query.value("DEVCORRESPONDINGSTATE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}


BayState::Ptr DBBayStateDAO::doQuery(QSqlDatabase db, const QString &bayName, bool *ok)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM baystate WHERE BAYNAME='%1'")
            .arg(bayName);
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            BayState::Ptr ptr(new BayState());
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_bayState = query.value("STATE").toInt();
            ptr->m_setType = query.value("SETTYPE").toString();
            ptr->m_updateTime = query.value("UPDATETIME").toString();
            ptr->m_devCorrespondingState = query.value("DEVCORRESPONDINGSTATE").toInt();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

BayState::List DBBayStateDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    BayState::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM baystate");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            BayState::Ptr ptr(new BayState());
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_bayState = query.value("STATE").toInt();
            ptr->m_setType = query.value("SETTYPE").toString();
            ptr->m_updateTime = query.value("UPDATETIME").toString();
            ptr->m_devCorrespondingState = query.value("DEVCORRESPONDINGSTATE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBBayStateDAO::doInsert(BayState::List &lst)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        query.exec("START TRANSACTION");
        QString sql = "";
        BayState::List::iterator iter;
        int count = 0;
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            BayState::Ptr ptr(new BayState());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO baystate VALUES(NULL, '%1', %2, '%3', '%4', %5)")
                    .arg(ptr->bayName())//1
                    .arg(ptr->bayState())//2
                    .arg(ptr->setType())//3
                    .arg(ptr->updateTime())//4
                    .arg(ptr->devCorrespondingState());//5
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return false;
            }
            count++;
        }
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

//bool DBBayStateDAO::doInit(QSqlDatabase db, QSqlDatabase dbR)
//{
//    bool bSucc = false;
//    doClear(dbR);
//    DBBayInfoDAO daoBayInfo;
//    BayInfo::List lstBayInfo = daoBayInfo.doQuery(db);
//    BayInfo::List::iterator iterBayInfo;
//    BayState::List lst;
//    for(iterBayInfo=lstBayInfo.begin(); iterBayInfo!=lstBayInfo.end(); iterBayInfo++)
//    {
//        BayInfo::Ptr ptrBayInfo(new BayInfo());
//        ptrBayInfo = *iterBayInfo;
//        QString bayName = ptrBayInfo->bayName();
//        BayState::Ptr ptr(new BayState());
//        ptr->m_bayName = bayName;
//        lst.append(ptr);
//    }

//    bSucc = doInsert(dbR, lst);

//    return bSucc;
//}

bool DBBayStateDAO::doInsert(QSqlDatabase db, BayState::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    BayState::List::iterator iter;
    int count = 0;
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        BayState::Ptr ptr(new BayState());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO baystate VALUES(NULL, '%1', %2, '%3', '%4', %5)")
                .arg(ptr->bayName())//1
                .arg(ptr->bayState())//2
                .arg(ptr->setType())//3
                .arg(ptr->updateTime())//4
                .arg(ptr->devCorrespondingState());//5
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

bool DBBayStateDAO::doClear(QSqlDatabase db)
{
    bool bSucc = false;
    QSqlQuery query(db);
    bSucc = query.exec("TRUNCATE TABLE baystate");

    return bSucc;
}

bool DBBayStateDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS baystate("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "BAYNAME VARCHAR(255) NOT NULL,"
                                  "STATE INT(11) NOT NULL,"
                                  "SETTYPE VARCHAR(255) NOT NULL,"
                                  "UPDATETIME VARCHAR(255) NOT NULL,"
                                  "DEVCORRESPONDINGSTATE INT(11) NOT NULL,"
                                  "PRIMARY KEY(GUID),"
                                  "UNIQUE KEY UK_baystate_BAYNAME(BAYNAME))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
