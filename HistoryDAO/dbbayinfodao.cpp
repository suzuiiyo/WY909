#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDateTime>
#include "bayinfo.h"
#include "dbconnection.h"
#include "dbbayinfodao.h"
#include "dbprimarydeviceinfodao.h"
#include "dbiedinfodao.h"
//#include "baystate.h"
//#include "dbbaystatedao.h"
//#include "iedstate.h"
//#include "dbiedrealstatedao.h"
#include "strap.h"
#include "dbstraplightplatedao.h"
#include "dbgooseinfodao.h"
#include "baybranchrelation.h"
#include "dbbaybranchrelationdao.h"
DBBayInfoDAO::DBBayInfoDAO()
    : m_connectionName("connectBayInfo")
{
    doCreateTable();
}

DBBayInfoDAO::~DBBayInfoDAO()
{

}

BayInfo::Hash DBBayInfoDAO::doQueryHash(bool *ok)
{
    bool bSucc = false;
    BayInfo::Hash hashBayInfo;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM bayinfo");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                BayInfo::Ptr ptr(new BayInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_bayDesc = query.value("BAYDESC").toString();
                ptr->m_bayType = query.value("BAYTYPE").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
                ptr->m_stationName = query.value("STATIONNAME").toString();
                ptr->m_voltage= query.value("VOLTAGE").toString();
                hashBayInfo.insert(ptr->bayName(), ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hashBayInfo;
}

BayInfo::Hash DBBayInfoDAO::dOQueryAllBay(bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = false;
    bool bSucc3 = false;
    BayInfo::List lstBayInfo = this->doQuery(&bSucc1);
    BayInfo::Hash hshBayInfo = this->doQueryHash(&bSucc2);
    DBBayBranchRelationDAO dao;
    BayBranchRelation::Hash hashMakeupBay = dao.doQuery(0, &bSucc3);
    foreach (const QString &makeupBayName, hashMakeupBay.keys())
    {
        BayBranchRelation::Ptr ptrMakeupBay = hashMakeupBay[makeupBayName];
        BayInfo::Ptr ptr(new BayInfo());
        ptr->m_bayName = ptrMakeupBay->makeupBayName();
        ptr->m_bayType = ptrMakeupBay->makeupBayType();
        BayInfo::List::iterator iterBayInfo;
        for(iterBayInfo=lstBayInfo.begin(); iterBayInfo!=lstBayInfo.end(); iterBayInfo++)
        {
            BayInfo::Ptr ptrBayInfo(new BayInfo());
            ptrBayInfo = *iterBayInfo;
            if(ptrMakeupBay->makeupBayName() == ptrBayInfo->belongMakeupBay())
            {
                ptr->m_bayDesc = ptrBayInfo->bayDesc();
                break;
            }
        }
        hshBayInfo.insert(ptr->bayName(), ptr);
    }
    if(ok)
    {
        if(bSucc1 && bSucc2 && bSucc3)
            *ok = true;
        else
            *ok = false;
    }

    return hshBayInfo;
}

BayInfo::List DBBayInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    BayInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM bayinfo");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                BayInfo::Ptr ptr(new BayInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_bayDesc = query.value("BAYDESC").toString();
                ptr->m_bayType = query.value("BAYTYPE").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
                ptr->m_stationName = query.value("STATIONNAME").toString();
                ptr->m_voltage= query.value("VOLTAGE").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

BayInfo::Ptr DBBayInfoDAO::doQuery(const QString &bayName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM bayinfo WHERE BAYNAME='%1'")
                .arg(bayName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                BayInfo::Ptr ptr(new BayInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_bayDesc = query.value("BAYDESC").toString();
                ptr->m_bayType = query.value("BAYTYPE").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
                ptr->m_stationName = query.value("STATIONNAME").toString();
                ptr->m_voltage= query.value("VOLTAGE").toString();
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

BayInfo::List DBBayInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    BayInfo::List lst;
    QString sql = QObject::tr("SELECT * FROM bayinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            BayInfo::Ptr ptr(new BayInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_bayDesc = query.value("BAYDESC").toString();
            ptr->m_bayType = query.value("BAYTYPE").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
            ptr->m_stationName = query.value("STATIONNAME").toString();
            ptr->m_voltage= query.value("VOLTAGE").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

BayInfo::Ptr DBBayInfoDAO::doQuery(QSqlDatabase db, const QString &bayName, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM bayinfo WHERE BAYNAME='%1'")
            .arg(bayName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            BayInfo::Ptr ptr(new BayInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_bayDesc = query.value("BAYDESC").toString();
            ptr->m_bayType = query.value("BAYTYPE").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
            ptr->m_stationName = query.value("STATIONNAME").toString();
            ptr->m_voltage= query.value("VOLTAGE").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

BayInfo::List DBBayInfoDAO::doQueryByBayType(const QString &bayType, bool *ok)
{
    bool bSucc = false;
    BayInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM bayinfo WHERE BAYTYPE=\"%1\"")
                .arg(bayType);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                BayInfo::Ptr ptr(new BayInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_bayDesc = query.value("BAYDESC").toString();
                ptr->m_bayType = query.value("BAYTYPE").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
                ptr->m_stationName = query.value("STATIONNAME").toString();
                ptr->m_voltage= query.value("VOLTAGE").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

BayInfo::List DBBayInfoDAO::doQueryByBayType(QSqlDatabase db, const QString &bayType, bool *ok)
{
    bool bSucc = false;
    BayInfo::List lst;
    QString sql = QObject::tr("SELECT * FROM bayinfo WHERE BAYTYPE=\"%1\"")
            .arg(bayType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            BayInfo::Ptr ptr(new BayInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_bayDesc = query.value("BAYDESC").toString();
            ptr->m_bayType = query.value("BAYTYPE").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
            ptr->m_stationName = query.value("STATIONNAME").toString();
            ptr->m_voltage= query.value("VOLTAGE").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

BayInfo::Ptr DBBayInfoDAO::doQueryByBayName(QSqlDatabase db, const QString &bayName, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = false;
    bool bSucc3 = false;
    bool bSucc4 = false;
    bool bSucc5 = false;
    BayInfo::Hash hashBayInfo = this->doQueryHash(db, &bSucc1);
    DBBayBranchRelationDAO daoBayBranch;
    BayBranchRelation::Hash hashBayBranch = daoBayBranch.doQueryHash(db, &bSucc2);
    DBIedInfoDAO daoIed;

    BayInfo::Ptr ptrBayInfo = NULL;

    if(hashBayInfo.count(bayName) != 0)
        ptrBayInfo = this->doQuery(db, bayName, &bSucc3);

    if(hashBayBranch.count(bayName) != 0)
        ptrBayInfo = this->findRelationBay(db, bayName, &bSucc4);

    if(ptrBayInfo)
    {
        QList<Ied*> lstIed = daoIed.doQueryLstByBayName(db, bayName, &bSucc5);
        ptrBayInfo->setLstIed(lstIed);
    }

    if(ok)
    {
        if(bSucc1 && bSucc2 && bSucc3 && bSucc4 && bSucc5)
            *ok = true;
        else
            *ok = false;
    }

    return ptrBayInfo;
}

BayInfo::Hash DBBayInfoDAO::doQueryHash(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    BayInfo::Hash hashBayInfo;
    QString sql = QObject::tr("SELECT * FROM bayinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            BayInfo::Ptr ptr(new BayInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_bayDesc = query.value("BAYDESC").toString();
            ptr->m_bayType = query.value("BAYTYPE").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
            ptr->m_stationName = query.value("STATIONNAME").toString();
            ptr->m_voltage= query.value("VOLTAGE").toString();
            hashBayInfo.insert(ptr->bayName(), ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hashBayInfo;
}

BayInfo::Hash DBBayInfoDAO::doQueryAllBay(QSqlDatabase db, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = false;
    bool bSucc3 = false;
    BayInfo::List lstBayInfo = this->doQuery(db, &bSucc1);
    BayInfo::Hash hshBayInfo = this->doQueryHash(db, &bSucc2);
    DBBayBranchRelationDAO dao;
    BayBranchRelation::Hash hashMakeupBay = dao.doQuery(db, 0, &bSucc3);
    foreach (const QString &makeupBayName, hashMakeupBay.keys())
    {
        BayBranchRelation::Ptr ptrMakeupBay = hashMakeupBay[makeupBayName];
        BayInfo::Ptr ptr(new BayInfo());
        ptr->m_bayName = ptrMakeupBay->makeupBayName();
        ptr->m_bayType = ptrMakeupBay->makeupBayType();
        BayInfo::List::iterator iterBayInfo;
        for(iterBayInfo=lstBayInfo.begin(); iterBayInfo!=lstBayInfo.end(); iterBayInfo++)
        {
            BayInfo::Ptr ptrBayInfo(new BayInfo());
            ptrBayInfo = *iterBayInfo;
            if(ptrMakeupBay->makeupBayName() == ptrBayInfo->belongMakeupBay())
            {
                ptr->m_bayDesc = ptrBayInfo->bayDesc();
                break;
            }
        }
        hshBayInfo.insert(ptr->bayName(), ptr);
    }
    if(ok)
    {
        if(bSucc1 && bSucc2 && bSucc3)
            *ok = true;
        else
            *ok = false;
    }

    return hshBayInfo;
}

//BayInfo::Ptr DBBayInfoDAO::doQueryByBayName(const QString &bayName)
//{
//    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
//    if(db.isOpen() || db.open())
//    {
//        QString sql = QObject::tr("SELECT * FROM bayinfo WHERE BAYNAME=\"%1\"")
//                .arg(bayName);
//        QSqlQuery query(db);
//        if(query.exec(sql))
//        {
//            while(query.next())
//            {
//                BayInfo::Ptr ptr(new BayInfo());
//                ptr->m_GUID = query.value("GUID").toInt();
//                ptr->m_bayName = query.value("BAYNAME").toString();
//                ptr->m_bayDesc = query.value("BAYDESC").toString();
//                ptr->m_bayType = query.value("BAYTYPE").toString();
//                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
//                ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
//                db.close();
//                return ptr;
//            }
//        }
//        db.close();
//    }

//    return NULL;
//}

//BayInfo::Ptr DBBayInfoDAO::doQueryByBayName(QSqlDatabase db, const QString &bayName)
//{
//    QString sql = QObject::tr("SELECT * FROM bayinfo WHERE BAYNAME=\"%1\"")
//            .arg(bayName);
//    QSqlQuery query(db);
//    if(query.exec(sql))
//    {
//        while(query.next())
//        {
//            BayInfo::Ptr ptr(new BayInfo());
//            ptr->m_GUID = query.value("GUID").toInt();
//            ptr->m_bayName = query.value("BAYNAME").toString();
//            ptr->m_bayDesc = query.value("BAYDESC").toString();
//            ptr->m_bayType = query.value("BAYTYPE").toString();
//            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
//            ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
//            //db.close();
//            return ptr;
//        }
//    }

//    return NULL;
//}

//BayInfo::Ptr DBBayInfoDAO::doQueryByBayName(QSqlDatabase db, QSqlDatabase dbR, QSqlDatabase dbG, const QString &bayName)
//{
//    QString sql = QObject::tr("SELECT * FROM bayinfo WHERE BAYNAME=\"%1\"")
//            .arg(bayName);
//    QSqlQuery query(db);
//    if(query.exec(sql))
//    {
//        DBBayStateDAO daoBayState;
//        DBIedRealStateDAO daoIedRealState;
//        DBIedInfoDAO daoIedInfo;
//        //IedState::List lstIedState = daoIedState.doQuery(dbR);
//        IedState::Hash hshIedState = daoIedRealState.doQueryHash(dbR);
//        DBStrapLightPlateDAO daoStrap;
//        DBGooseInfoDAO daoGooseInfo;
//        //DBBayInfoDAO daoBayInfo;
//        while(query.next())
//        {
//            BayInfo::Ptr ptr(new BayInfo());
//            ptr->m_GUID = query.value("GUID").toInt();
//            ptr->m_bayName = query.value("BAYNAME").toString();
//            ptr->m_bayDesc = query.value("BAYDESC").toString();
//            ptr->m_bayType = query.value("BAYTYPE").toString();
//            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
//            ptr->m_childBay = query.value("CHILDBAY").toString();
//            BayState::Ptr ptrBayState = daoBayState.doQuery(dbR, ptr->bayName());
//            if(ptrBayState)
//            {
//                ptr->m_bayState = ptrBayState->bayState();
//                ptr->m_devCorrespondingState = ptrBayState->devCorrespondingState();
//            }
//            ptr->m_lstIed = daoIedInfo.doQueryLst(db);
//            QList<Ied*> lstIedFin;
//            QList<Ied*>::iterator iterIed;
//            for(iterIed=ptr->m_lstIed.begin(); iterIed!=ptr->m_lstIed.end(); iterIed++)
//            {
//                Ied *ied = *iterIed;
//                if(hshIedState.count(ied->iedName()) == 1)
//                {
//                    Ied::Ptr iedPtr(new Ied());
//                    iedPtr = hshIedState[ied->iedName()];
//                    ied->setShouldIedState(iedPtr->shouldIedState());
//                    ied->setShouldIedState(iedPtr->iedState());
//                    ied->m_lstStrap = daoStrap.doQueryLst(db, dbR, ied->iedName());
//                    lstIedFin.append(ied);
//                }
//            }
//            ptr->clearIed();
//            ptr->m_lstIed = lstIedFin;



//        }
//    }

//    return NULL;
//}

BayInfo::Ptr DBBayInfoDAO::doQueryByBayName(const QString &bayName, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = false;
    bool bSucc3 = false;
    bool bSucc4 = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        BayInfo::Hash hashBayInfo = this->doQueryHash(db, &bSucc1);
        DBBayBranchRelationDAO daoBayBranch;
        BayBranchRelation::Hash hashBayBranch = daoBayBranch.doQueryHash(db, &bSucc2);
        DBIedInfoDAO daoIed;
        BayInfo::Ptr ptrBayInfo = NULL;

        if(hashBayInfo.count(bayName) != 0)
            ptrBayInfo = hashBayInfo[bayName];

        if(hashBayBranch.count(bayName) != 0)
            ptrBayInfo = this->findRelationBay(db, bayName, &bSucc3);

        if(ptrBayInfo)
        {
            QList<Ied*> lstIed = daoIed.doQueryLstByBayName(db, bayName, &bSucc4);
            ptrBayInfo->setLstIed(lstIed);
        }
        if(ok)
        {
            if(bSucc1 && bSucc2 && bSucc3 && bSucc4)
                *ok = true;
            else
                *ok = false;
        }
        db.close();
        return ptrBayInfo;
    }

    if(ok)
    {
        if(bSucc1 && bSucc2 && bSucc3 && bSucc4)
            *ok = true;
        else
            *ok = false;
    }

    return NULL;
}

BayInfo::Ptr DBBayInfoDAO::findRelationBay(const QString makeupBayName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM bayinfo WHERE BELONGMAKEUPBAY='%1'")
                .arg(makeupBayName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                BayInfo::Ptr ptr(new BayInfo);
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_bayDesc = query.value("BAYDESC").toString();
                ptr->m_bayType = query.value("BAYTYPE").toString();
                ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
                ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
                ptr->m_stationName = query.value("STATIONNAME").toString();
                ptr->m_voltage= query.value("VOLTAGE").toString();
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

BayInfo::Ptr DBBayInfoDAO::findRelationBay(QSqlDatabase db, const QString makeupBayName, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM bayinfo WHERE BELONGMAKEUPBAY='%1'")
            .arg(makeupBayName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            BayInfo::Ptr ptr(new BayInfo);
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_bayDesc = query.value("BAYDESC").toString();
            ptr->m_bayType = query.value("BAYTYPE").toString();
            ptr->m_scheduleName = query.value("SCHEDULENAME").toString();
            ptr->m_belongMakeupBay = query.value("BELONGMAKEUPBAY").toString();
            ptr->m_stationName = query.value("STATIONNAME").toString();
            ptr->m_voltage= query.value("VOLTAGE").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

bool DBBayInfoDAO::doInsert(BayInfo::List &lst)
{
    bool bSucc = false;
    BayInfo::List::iterator iter = lst.begin();
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
                BayInfo::Ptr ptr(new BayInfo());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO bayinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\")")
                        .arg(ptr->bayName())//1
                        .arg(ptr->bayDesc())//2
                        .arg(ptr->bayType())//3
                        .arg(ptr->scheduleName())//4
                        .arg(ptr->belongMakeupBay())//5
                        .arg(ptr->stationName())//6
                        .arg(ptr->voltage());//7
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
                BayInfo::Ptr ptr(new BayInfo());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO bayinfo VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\")")
                        .arg(ptr->bayName())//1
                        .arg(ptr->bayDesc())//2
                        .arg(ptr->bayType())//3
                        .arg(ptr->scheduleName())//4
                        .arg(ptr->belongMakeupBay())//5
                        .arg(ptr->stationName())//6
                        .arg(ptr->voltage());//7
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

bool DBBayInfoDAO::doUpdate(const BayInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE bayinfo SET BAYNAME=\"%1\", BAYDESC=\"%2\", BAYTYPE=\"%3\", SCHEDULENAME=\"%4\", BELONGMAKEUPBAY=\"%5\", STATIONNAME=\"%6\", VOLTAGE=\"%7\" WHERE GUID=%8")
                .arg(ptr->bayName())//1
                .arg(ptr->bayDesc())//2
                .arg(ptr->bayType())//3
                .arg(ptr->scheduleName())//4
                .arg(ptr->belongMakeupBay())//5
                .arg(ptr->stationName())//6
                .arg(ptr->voltage())//7
                .arg(ptr->GUID());//8
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBBayInfoDAO::doUpdate(BayInfo::List &lst)
{
    bool bSucc = false;
    BayInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            BayInfo::Ptr ptr(new BayInfo());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE bayinfo SET BAYNAME=\"%1\", BAYDESC=\"%2\", BAYTYPE=\"%3\", SCHEDULENAME=\"%4\", BELONGMAKEUPBAY=\"%5\", STATIONNAME=\"%6\", VOLTAGE=\"%7\" WHERE GUID=%8")
                    .arg(ptr->bayName())//1
                    .arg(ptr->bayDesc())//2
                    .arg(ptr->bayType())//3
                    .arg(ptr->scheduleName())//4
                    .arg(ptr->belongMakeupBay())//5
                    .arg(ptr->stationName())//6
                    .arg(ptr->voltage())//7
                    .arg(ptr->GUID());//8
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

bool DBBayInfoDAO::doDelete(const QString &bayName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM bayinfo WHERE BAYNAME=\"%1\"")
                .arg(bayName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBBayInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM bayinfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='bayinfo'");
        bSucc = query.exec(sql);
        db.close();
        DBPrimaryDeviceInfoDAO dao_dev;
        dao_dev.doClear();
        DBIedInfoDAO dao_ied;
        dao_ied.doClear();
        DBBayBranchRelationDAO dao_bayBranch;
        dao_bayBranch.doClear();
    }
    return bSucc;
}

bool DBBayInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS ("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "BAYNAME CHAR(255) UNIQUE NOT NULL,"
                                  "BAYDESC CHAR(255) NOT NULL,"
                                  "BAYTYPE CHAR(255) NOT NULL,"
                                  "SCHEDULENAME CHAR(255) NOT NULL,"
                                  "BELONGMAKEUPBAY CHAR(255) NOT NULL,"
                                  "STATIONNAME CHAR(255) NOT NULL,"
                                  "VOLTAGE CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
