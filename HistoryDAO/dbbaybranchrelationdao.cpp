#include <QSqlQuery>
#include <QVariant>
#include <QObject>
#include <QSqlError>
#include "dbconnection.h"
#include "bayinfo.h"
#include "dbbayinfodao.h"
//#include "baystate.h"
//#include "dbbaystatedao.h"
#include "baybranchrelation.h"
#include "dbbaybranchrelationdao.h"
DBBayBranchRelationDAO::DBBayBranchRelationDAO()
    : m_connectionName("connectBayBranchRelation")
{
    doCreateTable();
}

DBBayBranchRelationDAO::~DBBayBranchRelationDAO()
{

}

BayBranchRelation::List DBBayBranchRelationDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    BayBranchRelation::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM baybranchrelation");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                BayBranchRelation::Ptr ptr(new BayBranchRelation());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_makeupBayName = query.value("MAKEUPBAYNAME").toString();
                ptr->m_baseBayName = query.value("BASEBAYNAME").toString();
                ptr->m_makeupBayType = query.value("MAKEUPBAYTYPE").toString();
                ptr->m_branch = query.value("BRANCH").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

BayBranchRelation::List DBBayBranchRelationDAO::doQuery(const QString &makeupBayName, bool *ok)
{
    bool bSucc = false;
    BayBranchRelation::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM baybranchrelation WHERE MAKEUPBAYNAME=\"%1\"")
                .arg(makeupBayName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                BayBranchRelation::Ptr ptr(new BayBranchRelation());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_makeupBayName = query.value("MAKEUPBAYNAME").toString();
                ptr->m_baseBayName = query.value("BASEBAYNAME").toString();
                ptr->m_makeupBayType = query.value("MAKEUPBAYTYPE").toString();
                ptr->m_branch = query.value("BRANCH").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

BayBranchRelation::Ptr DBBayBranchRelationDAO::doQuery(const QString &makeupBayName, const QString &baseBayName, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM baybranchrelation WHERE MAKEUPBAYNAME=\"%1\" AND BASEBAYNAME=\"%2\"")
                .arg(makeupBayName)
                .arg(baseBayName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                BayBranchRelation::Ptr ptr(new BayBranchRelation());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_makeupBayName = query.value("MAKEUPBAYNAME").toString();
                ptr->m_baseBayName = query.value("BASEBAYNAME").toString();
                ptr->m_makeupBayType = query.value("MAKEUPBAYTYPE").toString();
                ptr->m_branch = query.value("BRANCH").toString();
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

QList<QList<QString>> DBBayBranchRelationDAO::doQueryBayList(bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = false;
    BayBranchRelation::List lst = this->doQuery(&bSucc1);
    BayBranchRelation::List::iterator iter;

    DBBayInfoDAO daoBayInfo;
    BayInfo::Hash hashBayInfo = daoBayInfo.doQueryHash(&bSucc2);
    QHash<QString, int> hashBayInfoUsed;
    QList<QList<QString>> lstBayLevel;

    QHash<QString, QHash<QString, QString>> hashBayLevel;
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        BayBranchRelation::Ptr ptr(new BayBranchRelation());
        ptr = *iter;
        QString makeupBayName = ptr->makeupBayName();
        QString baseBayName = ptr->baseBayName();
        QString makeupBayType = ptr->makeupBayType();

        if(hashBayInfo.count(baseBayName) != 0)
            hashBayInfoUsed.insert(baseBayName, 1);

        if(hashBayLevel.count(makeupBayName) == 0)
        {
            QHash<QString, QString> hashTmp;
            hashBayLevel.insert(makeupBayName, hashTmp);
        }
        hashBayLevel[makeupBayName].insert(baseBayName, makeupBayType);
    }
    foreach (const QString &makeupBayName, hashBayLevel.keys())
    {
        foreach (const QString &baseBayName, hashBayLevel[makeupBayName].keys())
        {
            BayInfo::Ptr ptrBayInfo = hashBayInfo[baseBayName];
            QString belongMakeupBay = ptrBayInfo->belongMakeupBay();
            if(belongMakeupBay != "")
            {
                QString baseBayType = ptrBayInfo->bayType();
                QString makeupBayType = hashBayLevel[makeupBayName][baseBayName];
                if(baseBayType != makeupBayType)
                {
                    if(hashBayLevel.count(belongMakeupBay) != 0)
                    {
                        foreach (const QString baseBayNameOther, hashBayLevel[belongMakeupBay].keys())
                        {
                            if(hashBayLevel[belongMakeupBay].count(baseBayNameOther) != 0)
                                hashBayLevel[makeupBayName].remove(hashBayLevel[makeupBayName].key(baseBayNameOther));
                        }
                        hashBayLevel[makeupBayName].insert(belongMakeupBay, "");
                    }
                }
            }
        }
    }

    foreach (const QString &makeupBayName, hashBayLevel.keys())
    {
        QList<QString> lstTmp;
        lstTmp.append(makeupBayName);
        foreach (const QString &baseBayName, hashBayLevel[makeupBayName].keys())
            lstTmp.append(baseBayName);
        lstBayLevel.append(lstTmp);
    }

    foreach (const QString &baseBayName, hashBayInfo.keys())
    {
        if(hashBayInfoUsed.count(baseBayName) == 0)
        {
            QList<QString> lstTmp;
            lstTmp.append(baseBayName);
            lstBayLevel.append(lstTmp);
        }
    }
    if(ok)
    {
        if(bSucc1 && bSucc2)
            *ok = true;
        else
            *ok = false;
    }

    return lstBayLevel;
}

BayBranchRelation::Hash DBBayBranchRelationDAO::doQueryHash(bool *ok)
{
    bool bSucc = false;
    BayBranchRelation::Hash hsh;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM baybranchrelation");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                BayBranchRelation::Ptr ptr(new BayBranchRelation());
                ptr->m_makeupBayName = query.value("MAKEUPBAYNAME").toString();
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_baseBayName = query.value("BASEBAYNAME").toString();
                ptr->m_makeupBayType = query.value("MAKEUPBAYTYPE").toString();
                ptr->m_branch = query.value("BRANCH").toString();
                hsh.insert(ptr->makeupBayName(), ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

BayBranchRelation::Hash DBBayBranchRelationDAO::doQuery(int type, bool *ok)
{
    bool bSucc = false;
    BayBranchRelation::Hash hashBayBranchRelation;
    if(type == 0)
    {
        BayBranchRelation::List lst = doQuery(&bSucc);
        BayBranchRelation::List::iterator iter;
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr = *iter;
            QString makeupBayName = ptr->makeupBayName();
            if(hashBayBranchRelation.count(makeupBayName) == 0)
                hashBayBranchRelation.insert(makeupBayName, ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hashBayBranchRelation;
}

//void DBBayBranchRelationDAO::dealBayLevel(const QString makeupName, QHash<QString, QHash<QString, QString>> &hashBayLevel)
//{
//    if(hashBayLevel.count(makeupName) == 0)
//        return;
//    else
//    {

//    }
//}

BayBranchRelation::List DBBayBranchRelationDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    BayBranchRelation::List lst;
    QString sql = QObject::tr("SELECT * FROM baybranchrelation");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_makeupBayName = query.value("MAKEUPBAYNAME").toString();
            ptr->m_baseBayName = query.value("BASEBAYNAME").toString();
            ptr->m_makeupBayType = query.value("MAKEUPBAYTYPE").toString();
            ptr->m_branch = query.value("BRANCH").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

BayBranchRelation::List DBBayBranchRelationDAO::doQuery(QSqlDatabase db, const QString &makeupBayName, bool *ok)
{
    bool bSucc = false;
    BayBranchRelation::List lst;
    QString sql = QObject::tr("SELECT * FROM baybranchrelation WHERE MAKEUPBAYNAME=\"%1\"")
            .arg(makeupBayName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_makeupBayName = query.value("MAKEUPBAYNAME").toString();
            ptr->m_baseBayName = query.value("BASEBAYNAME").toString();
            ptr->m_makeupBayType = query.value("MAKEUPBAYTYPE").toString();
            ptr->m_branch = query.value("BRANCH").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

BayBranchRelation::Ptr DBBayBranchRelationDAO::doQuery(QSqlDatabase db, const QString &makeupBayName, const QString &baseBayName, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM baybranchrelation WHERE MAKEUPBAYNAME=\"%1\" AND BASEBAYNAME=\"%2\"")
            .arg(makeupBayName)
            .arg(baseBayName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_makeupBayName = query.value("MAKEUPBAYNAME").toString();
            ptr->m_baseBayName = query.value("BASEBAYNAME").toString();
            ptr->m_makeupBayType = query.value("MAKEUPBAYTYPE").toString();
            ptr->m_branch = query.value("BRANCH").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

QList<QList<QString> > DBBayBranchRelationDAO::doQueryBayList(QSqlDatabase db, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = false;
    BayBranchRelation::List lst = this->doQuery(db, &bSucc1);
    BayBranchRelation::List::iterator iter;

    DBBayInfoDAO daoBayInfo;
    BayInfo::Hash hashBayInfo = daoBayInfo.doQueryHash(db, &bSucc2);
    QHash<QString, int> hashBayInfoUsed;
    QList<QList<QString>> lstBayLevel;

    QHash<QString, QHash<QString, QString>> hashBayLevel;
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        BayBranchRelation::Ptr ptr(new BayBranchRelation());
        ptr = *iter;
        QString makeupBayName = ptr->makeupBayName();
        QString baseBayName = ptr->baseBayName();
        QString makeupBayType = ptr->makeupBayType();

        if(hashBayInfo.count(baseBayName) != 0)
            hashBayInfoUsed.insert(baseBayName, 1);

        if(hashBayLevel.count(makeupBayName) == 0)
        {
            QHash<QString, QString> hashTmp;
            hashBayLevel.insert(makeupBayName, hashTmp);
        }
        hashBayLevel[makeupBayName].insert(baseBayName, makeupBayType);
    }
    foreach (const QString &makeupBayName, hashBayLevel.keys())
    {
        foreach (const QString &baseBayName, hashBayLevel[makeupBayName].keys())
        {
            BayInfo::Ptr ptrBayInfo = hashBayInfo[baseBayName];
            QString belongMakeupBay = ptrBayInfo->belongMakeupBay();
            if(belongMakeupBay != "")
            {
                QString baseBayType = ptrBayInfo->bayType();
                QString makeupBayType = hashBayLevel[makeupBayName][baseBayName];
                if(baseBayType != makeupBayType)
                {
                    if(hashBayLevel.count(belongMakeupBay) != 0)
                    {
                        foreach (const QString baseBayNameOther, hashBayLevel[belongMakeupBay].keys())
                        {
                            if(hashBayLevel[belongMakeupBay].count(baseBayNameOther) != 0)
                                hashBayLevel[makeupBayName].remove(hashBayLevel[makeupBayName].key(baseBayNameOther));
                        }
                        hashBayLevel[makeupBayName].insert(belongMakeupBay, "");
                    }
                }
            }
        }
    }

    foreach (const QString &makeupBayName, hashBayLevel.keys())
    {
        QList<QString> lstTmp;
        lstTmp.append(makeupBayName);
        foreach (const QString &baseBayName, hashBayLevel[makeupBayName].keys())
            lstTmp.append(baseBayName);
        lstBayLevel.append(lstTmp);
    }

    foreach (const QString &baseBayName, hashBayInfo.keys())
    {
        if(hashBayInfoUsed.count(baseBayName) == 0)
        {
            QList<QString> lstTmp;
            lstTmp.append(baseBayName);
            lstBayLevel.append(lstTmp);
        }
    }
    if(ok)
    {
        if(bSucc1 && bSucc2)
            *ok = true;
        else
            *ok = false;
    }

    return lstBayLevel;
}

BayBranchRelation::Hash DBBayBranchRelationDAO::doQueryHash(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    BayBranchRelation::Hash hsh;
    QString sql = QObject::tr("SELECT * FROM baybranchrelation");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr->m_makeupBayName = query.value("MAKEUPBAYNAME").toString();
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_baseBayName = query.value("BASEBAYNAME").toString();
            ptr->m_makeupBayType = query.value("MAKEUPBAYTYPE").toString();
            ptr->m_branch = query.value("BRANCH").toString();
            hsh.insert(ptr->makeupBayName(), ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

BayBranchRelation::Hash DBBayBranchRelationDAO::doQuery(QSqlDatabase db, int type, bool *ok)
{
    bool bSucc = false;
    BayBranchRelation::Hash hashBayBranchRelation;
    if(type == 0)
    {
        BayBranchRelation::List lst = this->doQuery(db, &bSucc);
        BayBranchRelation::List::iterator iter;
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr = *iter;
            QString makeupBayName = ptr->makeupBayName();
            if(hashBayBranchRelation.count(makeupBayName) == 0)
                hashBayBranchRelation.insert(makeupBayName, ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hashBayBranchRelation;
}

bool DBBayBranchRelationDAO::doInsert(BayBranchRelation::List &lst)
{
    bool bSucc = false;
    BayBranchRelation::List::iterator iter = lst.begin();
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
                BayBranchRelation::Ptr ptr(new BayBranchRelation());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO baybranchrelation VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\")")
                        .arg(ptr->makeupBayName())//1
                        .arg(ptr->baseBayName())//2
                        .arg(ptr->makeupBayType())//3
                        .arg(ptr->branch());//4
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
                BayBranchRelation::Ptr ptr(new BayBranchRelation());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO baybranchrelation VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\")")
                        .arg(ptr->makeupBayName())//1
                        .arg(ptr->baseBayName())//2
                        .arg(ptr->makeupBayType())//3
                        .arg(ptr->branch());//4
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

bool DBBayBranchRelationDAO::doInsert(QSqlDatabase db, BayBranchRelation::List &lst)
{
    bool bSucc = false;
    BayBranchRelation::List::iterator iter = lst.begin();
    int list_size = lst.size();
    if(list_size == 0)
        return true;
    QSqlQuery query(db);
    QString sql = "";
    query.exec("begin transaction");
    if(list_size <= 1000)
    {
        while(iter < lst.end())
        {
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr = *iter;

            sql = QObject::tr("INSERT INTO baybranchrelation VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\")")
                    .arg(ptr->makeupBayName())//1
                    .arg(ptr->baseBayName())//2
                    .arg(ptr->makeupBayType())//3
                    .arg(ptr->branch());//4
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
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
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr = *iter;

            sql = QObject::tr("INSERT INTO baybranchrelation VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\")")
                    .arg(ptr->makeupBayName())//1
                    .arg(ptr->baseBayName())//2
                    .arg(ptr->makeupBayType())//3
                    .arg(ptr->branch());//4
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
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

    return bSucc;
}

bool DBBayBranchRelationDAO::doUpdate(BayBranchRelation::List &lst)
{
    bool bSucc = false;
    BayBranchRelation::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE baybranchrelation SET MAKEUPBAYNAME=\"%1\", BASEBAYNAME=\"%2\", MAKEUPBAYTYPE=\"%3\", BRANCH=\"%4\" WHERE GUID=%5")
                    .arg(ptr->makeupBayName())//1
                    .arg(ptr->baseBayName())//2
                    .arg(ptr->makeupBayType())//3
                    .arg(ptr->branch())//4
                    .arg(ptr->GUID());//5
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

bool DBBayBranchRelationDAO::doUpdate(QSqlDatabase db, BayBranchRelation::List &lst)
{
    bool bSucc = false;
    BayBranchRelation::List::iterator iter = lst.begin();
    QSqlQuery query(db);
    query.exec("begin transaction");

    while(iter < lst.end())
    {
        BayBranchRelation::Ptr ptr(new BayBranchRelation());
        ptr = *iter;
        QString sql = QObject::tr("UPDATE baybranchrelation SET MAKEUPBAYNAME=\"%1\", BASEBAYNAME=\"%2\", MAKEUPBAYTYPE=\"%3\", BRANCH=\"%4\" WHERE GUID=%5")
                .arg(ptr->makeupBayName())//1
                .arg(ptr->baseBayName())//2
                .arg(ptr->makeupBayType())//3
                .arg(ptr->branch())//4
                .arg(ptr->GUID());//5
        if(!query.exec(sql))
        {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
            return bSucc;
        }
        iter++;
    }

    bSucc = query.exec("commit transaction");
    if(!bSucc){
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }
    return bSucc;
}

bool DBBayBranchRelationDAO::doDelete(BayBranchRelation::List &lst)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        BayBranchRelation::List::iterator iter;
        QSqlQuery query(db);
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            BayBranchRelation::Ptr ptr(new BayBranchRelation());
            ptr = *iter;
            QString sql = QObject::tr("DELETE FROM baybranchrelation WHERE MAKEUPBAYNAME=\"%1\" AND BASEBAYNAME=\"%2\"")
                            .arg(ptr->makeupBayName())
                            .arg(ptr->baseBayName());
            bSucc = query.exec(sql);
        }
        db.close();
    }
    return bSucc;
}

bool DBBayBranchRelationDAO::doDelete(QSqlDatabase db, BayBranchRelation::List &lst)
{
    bool bSucc = false;
    BayBranchRelation::List::iterator iter;
    QSqlQuery query(db);
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        BayBranchRelation::Ptr ptr(new BayBranchRelation());
        ptr = *iter;
        QString sql = QObject::tr("DELETE FROM baybranchrelation WHERE MAKEUPBAYNAME=\"%1\" AND BASEBAYNAME=\"%2\"")
                        .arg(ptr->makeupBayName())
                        .arg(ptr->baseBayName());
        bSucc = query.exec(sql);
    }
    return bSucc;
}

bool DBBayBranchRelationDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM baybranchrelation");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='baybranchrelation'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBBayBranchRelationDAO::doClear(QSqlDatabase db)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString sql = QObject::tr("DELETE FROM baybranchrelation");
    bSucc = query.exec(sql);
    sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='baybranchrelation'");
    bSucc = query.exec(sql);

    return bSucc;
}

bool DBBayBranchRelationDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS baybranchrelation("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "MAKEUPBAYNAME CHAR(255) NOT NULL,"
                                  "BASEBAYNAME CHAR(255) NOT NULL,"
                                  "MAKEUPBAYTYPE CHAR(255) NOT NULL,"
                                  "BRANCH CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}















