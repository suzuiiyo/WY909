#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QObject>
#include "dbconnection.h"
#include "dbsteadytasktmconfigdao.h"
DBSteadyTaskTMConfigDAO::DBSteadyTaskTMConfigDAO()
    : m_connectionName("connectSteadyTaskTMConfig")
{

}

DBSteadyTaskTMConfigDAO::~DBSteadyTaskTMConfigDAO()
{

}

SteadyTaskTMConfig::List DBSteadyTaskTMConfigDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    SteadyTaskTMConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM steadytasktmconfig");
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_itemName = query.value("ITEMNAME").toString();
                ptr->m_itemType = query.value("ITEMTYPE").toString();
                ptr->m_itemDesc = query.value("ITEMDESC").toString();
                ptr->m_relationItem = query.value("RELATIONITEM").toString();
                ptr->m_phase = query.value("PHASE").toString();
                ptr->m_setType = query.value("SETTYPE").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_dataRef1 = query.value("DATAREF1").toString();
                ptr->m_dataDesc1 = query.value("DATADESC1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_dataRef2 = query.value("DATAREF2").toString();
                ptr->m_dataDesc2 = query.value("DATADESC2").toString();
                ptr->m_lineName = query.value("LINENAME").toString();
                ptr->m_unitName = query.value("UNITNAME").toString();
                ptr->m_projectName = query.value("PROJECTNAME").toString();
                ptr->m_businessType = query.value("BUSINESSTYPE").toString();
                ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_itemConfigType = query.value("ITEMCONFIGTYPE").toString();
                ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SteadyTaskTMConfig::List DBSteadyTaskTMConfigDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    SteadyTaskTMConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM steadytasktmconfig WHERE IEDNAME1=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_itemName = query.value("ITEMNAME").toString();
                ptr->m_itemType = query.value("ITEMTYPE").toString();
                ptr->m_itemDesc = query.value("ITEMDESC").toString();
                ptr->m_relationItem = query.value("RELATIONITEM").toString();
                ptr->m_phase = query.value("PHASE").toString();
                ptr->m_setType = query.value("SETTYPE").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_dataRef1 = query.value("DATAREF1").toString();
                ptr->m_dataDesc1 = query.value("DATADESC1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_dataRef2 = query.value("DATAREF2").toString();
                ptr->m_dataDesc2 = query.value("DATADESC2").toString();
                ptr->m_lineName = query.value("LINENAME").toString();
                ptr->m_unitName = query.value("UNITNAME").toString();
                ptr->m_projectName = query.value("PROJECTNAME").toString();
                ptr->m_businessType = query.value("BUSINESSTYPE").toString();
                ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_itemConfigType = query.value("ITEMCONFIGTYPE").toString();
                ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SteadyTaskTMConfig::List DBSteadyTaskTMConfigDAO::doQuery(const QString &iedName, const QString &itemName, bool *ok)
{
    bool bSucc = false;
    SteadyTaskTMConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM steadytasktmconfig WHERE IEDNAME1=\"%1\" AND ITEMNAME=\"%2\"")
                .arg(iedName)
                .arg(itemName);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_itemName = query.value("ITEMNAME").toString();
                ptr->m_itemType = query.value("ITEMTYPE").toString();
                ptr->m_itemDesc = query.value("ITEMDESC").toString();
                ptr->m_relationItem = query.value("RELATIONITEM").toString();
                ptr->m_phase = query.value("PHASE").toString();
                ptr->m_setType = query.value("SETTYPE").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_dataRef1 = query.value("DATAREF1").toString();
                ptr->m_dataDesc1 = query.value("DATADESC1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_dataRef2 = query.value("DATAREF2").toString();
                ptr->m_dataDesc2 = query.value("DATADESC2").toString();
                ptr->m_lineName = query.value("LINENAME").toString();
                ptr->m_unitName = query.value("UNITNAME").toString();
                ptr->m_projectName = query.value("PROJECTNAME").toString();
                ptr->m_businessType = query.value("BUSINESSTYPE").toString();
                ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_itemConfigType = query.value("ITEMCONFIGTYPE").toString();
                ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SteadyTaskTMConfig::List DBSteadyTaskTMConfigDAO::doQuery(const QString &iedName, const QString &itemName, const QString &itemType, bool *ok)
{
    bool bSucc = false;
    SteadyTaskTMConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM steadytasktmconfig WHERE IEDNAME1=\"%1\" AND ITEMNAME=\"%2\" AND ITEMTYPE=\"%3\"")
                .arg(iedName)
                .arg(itemName)
                .arg(itemType);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_bayName = query.value("BAYNAME").toString();
                ptr->m_itemName = query.value("ITEMNAME").toString();
                ptr->m_itemType = query.value("ITEMTYPE").toString();
                ptr->m_itemDesc = query.value("ITEMDESC").toString();
                ptr->m_relationItem = query.value("RELATIONITEM").toString();
                ptr->m_phase = query.value("PHASE").toString();
                ptr->m_setType = query.value("SETTYPE").toString();
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_dataRef1 = query.value("DATAREF1").toString();
                ptr->m_dataDesc1 = query.value("DATADESC1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_dataRef2 = query.value("DATAREF2").toString();
                ptr->m_dataDesc2 = query.value("DATADESC2").toString();
                ptr->m_lineName = query.value("LINENAME").toString();
                ptr->m_unitName = query.value("UNITNAME").toString();
                ptr->m_projectName = query.value("PROJECTNAME").toString();
                ptr->m_businessType = query.value("BUSINESSTYPE").toString();
                ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_itemConfigType = query.value("ITEMCONFIGTYPE").toString();
                ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SteadyTaskTMConfig::List DBSteadyTaskTMConfigDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    SteadyTaskTMConfig::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM steadytasktmconfig");
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_itemName = query.value("ITEMNAME").toString();
            ptr->m_itemType = query.value("ITEMTYPE").toString();
            ptr->m_itemDesc = query.value("ITEMDESC").toString();
            ptr->m_relationItem = query.value("RELATIONITEM").toString();
            ptr->m_phase = query.value("PHASE").toString();
            ptr->m_setType = query.value("SETTYPE").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_dataRef1 = query.value("DATAREF1").toString();
            ptr->m_dataDesc1 = query.value("DATADESC1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_dataRef2 = query.value("DATAREF2").toString();
            ptr->m_dataDesc2 = query.value("DATADESC2").toString();
            ptr->m_lineName = query.value("LINENAME").toString();
            ptr->m_unitName = query.value("UNITNAME").toString();
            ptr->m_projectName = query.value("PROJECTNAME").toString();
            ptr->m_businessType = query.value("BUSINESSTYPE").toString();
            ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_itemConfigType = query.value("ITEMCONFIGTYPE").toString();
            ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SteadyTaskTMConfig::List DBSteadyTaskTMConfigDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    SteadyTaskTMConfig::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM steadytasktmconfig WHERE IEDNAME1=\"%1\"")
            .arg(iedName);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_itemName = query.value("ITEMNAME").toString();
            ptr->m_itemType = query.value("ITEMTYPE").toString();
            ptr->m_itemDesc = query.value("ITEMDESC").toString();
            ptr->m_relationItem = query.value("RELATIONITEM").toString();
            ptr->m_phase = query.value("PHASE").toString();
            ptr->m_setType = query.value("SETTYPE").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_dataRef1 = query.value("DATAREF1").toString();
            ptr->m_dataDesc1 = query.value("DATADESC1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_dataRef2 = query.value("DATAREF2").toString();
            ptr->m_dataDesc2 = query.value("DATADESC2").toString();
            ptr->m_lineName = query.value("LINENAME").toString();
            ptr->m_unitName = query.value("UNITNAME").toString();
            ptr->m_projectName = query.value("PROJECTNAME").toString();
            ptr->m_businessType = query.value("BUSINESSTYPE").toString();
            ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_itemConfigType = query.value("ITEMCONFIGTYPE").toString();
            ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SteadyTaskTMConfig::List DBSteadyTaskTMConfigDAO::doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, bool *ok)
{
    bool bSucc = false;
    SteadyTaskTMConfig::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM steadytasktmconfig WHERE IEDNAME1=\"%1\" AND ITEMNAME=\"%2\"")
            .arg(iedName)
            .arg(itemName);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_itemName = query.value("ITEMNAME").toString();
            ptr->m_itemType = query.value("ITEMTYPE").toString();
            ptr->m_itemDesc = query.value("ITEMDESC").toString();
            ptr->m_relationItem = query.value("RELATIONITEM").toString();
            ptr->m_phase = query.value("PHASE").toString();
            ptr->m_setType = query.value("SETTYPE").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_dataRef1 = query.value("DATAREF1").toString();
            ptr->m_dataDesc1 = query.value("DATADESC1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_dataRef2 = query.value("DATAREF2").toString();
            ptr->m_dataDesc2 = query.value("DATADESC2").toString();
            ptr->m_lineName = query.value("LINENAME").toString();
            ptr->m_unitName = query.value("UNITNAME").toString();
            ptr->m_projectName = query.value("PROJECTNAME").toString();
            ptr->m_businessType = query.value("BUSINESSTYPE").toString();
            ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_itemConfigType = query.value("ITEMCONFIGTYPE").toString();
            ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

SteadyTaskTMConfig::List DBSteadyTaskTMConfigDAO::doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, const QString &itemType, bool *ok)
{
    bool bSucc = false;
    SteadyTaskTMConfig::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM steadytasktmconfig WHERE IEDNAME1=\"%1\" AND ITEMNAME=\"%2\" AND ITEMTYPE=\"%3\"")
            .arg(iedName)
            .arg(itemName)
            .arg(itemType);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_bayName = query.value("BAYNAME").toString();
            ptr->m_itemName = query.value("ITEMNAME").toString();
            ptr->m_itemType = query.value("ITEMTYPE").toString();
            ptr->m_itemDesc = query.value("ITEMDESC").toString();
            ptr->m_relationItem = query.value("RELATIONITEM").toString();
            ptr->m_phase = query.value("PHASE").toString();
            ptr->m_setType = query.value("SETTYPE").toString();
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_dataRef1 = query.value("DATAREF1").toString();
            ptr->m_dataDesc1 = query.value("DATADESC1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_dataRef2 = query.value("DATAREF2").toString();
            ptr->m_dataDesc2 = query.value("DATADESC2").toString();
            ptr->m_lineName = query.value("LINENAME").toString();
            ptr->m_unitName = query.value("UNITNAME").toString();
            ptr->m_projectName = query.value("PROJECTNAME").toString();
            ptr->m_businessType = query.value("BUSINESSTYPE").toString();
            ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_itemConfigType = query.value("ITEMCONFIGTYPE").toString();
            ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBSteadyTaskTMConfigDAO::doInsert(SteadyTaskTMConfig::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;

    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        SteadyTaskTMConfig::List::iterator iter;
        QSqlQuery query(db);
        query.exec("begin transaction");
        QString sql = "";

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO steadytasktmconfig VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\", \"%9\", \"%10\", \"%11\", \"%12\", \"%13\", \"%14\", \"%15\", \"%16\", \"%17\", \"%18\", \"%19\", \"%20\", \"%21\")")
                    .arg(ptr->bayName())//1
                    .arg(ptr->itemName())//2
                    .arg(ptr->itemType())//3
                    .arg(ptr->itemDesc())//4
                    .arg(ptr->relationItem())//5
                    .arg(ptr->phase())//6
                    .arg(ptr->setType())//7
                    .arg(ptr->iedName1())//8
                    .arg(ptr->dataRef1())//9
                    .arg(ptr->dataDesc1())//10
                    .arg(ptr->iedName2())//11
                    .arg(ptr->dataRef2())//12
                    .arg(ptr->dataDesc2())//13
                    .arg(ptr->lineName())//14
                    .arg(ptr->unitName())//15
                    .arg(ptr->projectName())//16
                    .arg(ptr->businessType())//17
                    .arg(ptr->standardValueType())//18
                    .arg(ptr->standardValue())//19
                    .arg(ptr->itemConfigType())//20
                    .arg(ptr->unicodeDesc());//21
            //printf("sql: %s\n", sql.toStdString().data());
            bSucc = query.exec(sql);
            if(!bSucc)
            {
                db.close();
                return bSucc;
            }
        }
        bSucc = query.exec("commit transaction");
        db.close();
    }

    return bSucc;
}

bool DBSteadyTaskTMConfigDAO::doUpdate(const SteadyTaskTMConfig::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE steadytasktmconfig SET BAYNAME=\"%1\", ITEMNAME=\"%2\", ITEMTYPE=\"%3\", ITEMDESC=\"%4\", RELATIONITEM=\"%5\", PHASE=\"%6\", SETTYPE=\"%7\", IEDNAME1=\"%8\", DATAREF1=\"%9\", DATADESC1=\"%10\", IEDNAME2=\"%11\", DATAREF2=\"%12\", DATADESC2=\"%13\", LINENAME=\"%14\", UNITNAME=\"%15\", PROJECTNAME=\"%16\", BUSINESSTYPE=\"%17\", STANDARDVALUETYPE=\"%18\", STANDARDVALUETYPE=\"%19\", ITEMCONFIGTYPE=\"%20\", UNICODEDESC=\"%21\" WHERE GUID=%22")
                .arg(ptr->bayName())//1
                .arg(ptr->itemName())//2
                .arg(ptr->itemType())//3
                .arg(ptr->itemDesc())//4
                .arg(ptr->relationItem())//5
                .arg(ptr->phase())//6
                .arg(ptr->setType())//7
                .arg(ptr->iedName1())//8
                .arg(ptr->dataRef1())//9
                .arg(ptr->dataDesc1())//10
                .arg(ptr->iedName2())//11
                .arg(ptr->dataRef2())//12
                .arg(ptr->dataDesc2())//13
                .arg(ptr->lineName())//14
                .arg(ptr->unitName())//15
                .arg(ptr->projectName())//16
                .arg(ptr->businessType())//17
                .arg(ptr->standardValueType())//18
                .arg(ptr->standardValue())//19
                .arg(ptr->itemConfigType())//20
                .arg(ptr->unicodeDesc())//21
                .arg(ptr->GUID());//22
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBSteadyTaskTMConfigDAO::doUpdate(SteadyTaskTMConfig::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;

    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");
        QString sql = "";
        SteadyTaskTMConfig::List::iterator iter;
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
            ptr = *iter;
            sql = QObject::tr("UPDATE steadytasktmconfig SET BAYNAME=\"%1\", ITEMNAME=\"%2\", ITEMTYPE=\"%3\", ITEMDESC=\"%4\", RELATIONITEM=\"%5\", PHASE=\"%6\", SETTYPE=\"%7\", IEDNAME1=\"%8\", DATAREF1=\"%9\", DATADESC1=\"%10\", IEDNAME2=\"%11\", DATAREF2=\"%12\", DATADESC2=\"%13\", LINENAME=\"%14\", UNITNAME=\"%15\", PROJECTNAME=\"%16\", BUSINESSTYPE=\"%17\", STANDARDVALUETYPE=\"%18\", STANDARDVALUETYPE=\"%19\", ITEMCONFIGTYPE=\"%20\", UNICODEDESC=\"%21\" WHERE GUID=%22")
                    .arg(ptr->bayName())//1
                    .arg(ptr->itemName())//2
                    .arg(ptr->itemType())//3
                    .arg(ptr->itemDesc())//4
                    .arg(ptr->relationItem())//5
                    .arg(ptr->phase())//6
                    .arg(ptr->setType())//7
                    .arg(ptr->iedName1())//8
                    .arg(ptr->dataRef1())//9
                    .arg(ptr->dataDesc1())//10
                    .arg(ptr->iedName2())//11
                    .arg(ptr->dataRef2())//12
                    .arg(ptr->dataDesc2())//13
                    .arg(ptr->lineName())//14
                    .arg(ptr->unitName())//15
                    .arg(ptr->projectName())//16
                    .arg(ptr->businessType())//17
                    .arg(ptr->standardValueType())//18
                    .arg(ptr->standardValue())//19
                    .arg(ptr->itemConfigType())//20
                    .arg(ptr->unicodeDesc())//21
                    .arg(ptr->GUID());//22
            if(!query.exec(sql))
            {
                db.close();
                return bSucc;
            }
        }
        bSucc = query.exec("commit transaction");
        db.close();
    }

    return bSucc;
}

bool DBSteadyTaskTMConfigDAO::doDelete(SteadyTaskTMConfig::List &lst)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        SteadyTaskTMConfig::List::iterator iter;
        QSqlQuery query(db);
        QString sql = "";
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            SteadyTaskTMConfig::Ptr ptr(new SteadyTaskTMConfig());
            ptr = *iter;
            sql = QObject::tr("DELETE * FROM steadytasktmconfig WHERE GUID=%1")
                                .arg(ptr->GUID());
            bSucc = query.exec(sql);
        }
        db.close();
    }

    return bSucc;
}

bool DBSteadyTaskTMConfigDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM steadytasktmconfig");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='steadytasktmconfig'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSteadyTaskTMConfigDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS steadytasktmconfig("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "BAYNAME CHAR(255) NOT NULL,"
                                  "ITEMNAME CHAR(255) NOT NULL,"
                                  "ITEMTYPE CHAR(255) NOT NULL,"
                                  "ITEMDESC CHAR(255) NOT NULL,"
                                  "RELATIONITEM CHAR(255) NOT NULL,"
                                  "PHASE CHAR(255) NOT NULL,"
                                  "SETTYPE CHAR(255) NOT NULL,"
                                  "IEDNAME1 CHAR(255) NOT NULL,"
                                  "DATAREF1 CHAR(255) NOT NULL,"
                                  "DATADESC1 CHAR(255) NOT NULL,"
                                  "IEDNAME2 CHAR(255) NOT NULL,"
                                  "DATAREF2 CHAR(255) NOT NULL,"
                                  "DATADESC2 CHAR(255) NOT NULL,"
                                  "LINENAME CHAR(255) NOT NULL,"
                                  "UNITNAME CHAR(255) NOT NULL,"
                                  "PROJECTNAME CHAR(255) NOT NULL,"
                                  "BUSINESSTYPE CHAR(255) NOT NULL,"
                                  "STANDARDVALUETYPE CHAR(255) NOT NULL,"
                                  "STANDARDVALUE CHAR(255) NOT NULL,"
                                  "ITEMCONFIGTYPE CHAR(255) NOT NULL,"
                                  "UNICODEDESC CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}