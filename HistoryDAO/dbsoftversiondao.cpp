#include <QSqlQuery>
#include <QObject>
#include <QVariant>
#include "ied.h"
#include "dbiedinfodao.h"
#include "dastruct.h"
#include "dbdastructdao.h"
#include "dbsoftversiondao.h"
#include "dbconnection.h"
#include "dastruct.h"
#include "dbdastructdao.h"
DBSoftVersionDAO::DBSoftVersionDAO()
    : m_connectionName("connectSoftVersion")
{
    m_relationHash = this->relation();
}

DBSoftVersionDAO::~DBSoftVersionDAO()
{

}

SoftVersion::List DBSoftVersionDAO::doQuery(bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM softversion");

        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }
        db.close();
    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByIedName(const QString &iedName, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM softversion WHERE IEDNAME=\"%1\"")
                .arg(iedName);

        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }
        db.close();
    }

    return lst;
}

SoftVersion::Ptr DBSoftVersionDAO::doQueryBySelfType(const QString &iedName, int selfType, bool needDAStruct)
{
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM softversion WHERE IEDNAME=\"%1\" AND SELFTYPE=%2")
                .arg(iedName)
                .arg(selfType);

        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                db.close();
                return ptr;
            }
        }
        db.close();
    }

    return NULL;
}

SoftVersion::List DBSoftVersionDAO::doQueryByBayName(const QString &bayName, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(type == -1)
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.IEDNAME=b.IEDNAME")
                        .arg(bayName);
        else
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.IEDNAME=b.IEDNAME AND a.SELFTYPE=%2")
                        .arg(bayName)
                        .arg(type);
        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }

//        if(type == -1)
//        {

//        }
//        else
//        {
//            int tmpType = type;
//            DBIedInfoDAO daoIed;
//            Ied::List lstIed = daoIed.doQueryByBayNameLike(db, bayName);
//            Ied::List::iterator iterIed;
//            DBDAStructDAO daoDAStruct;
//            for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//            {
//                Ied::Ptr ptrIed(new Ied());
//                ptrIed = *iterIed;
//                QString iedName = ptrIed->iedName();
//                QString iedCateGory = ptrIed->iedCateGory();
//                if(iedCateGory != "")
//                {
//                    if(iedCateGory == "Prot")
//                    {
//                        tmpType = m_relationHash[iedCateGory][type];
//                    }
//                    SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                    SoftVersion::List::iterator iter;
//                    bool tip = false;
//                    for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                    {
//                        SoftVersion::Ptr ptrTmp(new SoftVersion());
//                        ptrTmp = *iter;
//                        if(ptrTmp->type() == tmpType)
//                        {
//                            SoftVersion::Ptr ptr(new SoftVersion());
//                            ptr->m_GUID = ptrTmp->GUID();
//                            ptr->m_iedName = ptrTmp->iedName();
//                            ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                            ptr->m_type = ptrTmp->type();
//                            ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                            ptr->m_standardValue = ptrTmp->standardValue();
//                            ptr->m_defaultValue = ptrTmp->defaultValue();
//                            ptr->m_dataRef = ptrTmp->dataRef();
//                            ptr->m_dataType = ptrTmp->dataType();
//                            ptr->m_selfType = ptrTmp->selfType();
//                            if(needDAStruct)
//                                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                            lst.append(ptr);
//                            tip = true;
//                            break;
//                        }
//                    }
//                    if(!tip)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_iedName = iedName;
//                        ptr->m_iedCateGory = ptrIed->iedCateGory();
//                        ptr->m_type = tmpType;
//                        lst.append(ptr);
//                    }
//                }

//                else
//                {
//                    QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
//                            .arg(bayName);
//                    if(query.exec(sql))
//                    {
//                        DBDAStructDAO daoDAStruct;
//                        while(query.next())
//                        {
//                            SoftVersion::Ptr ptr(new SoftVersion());
//                            ptr->m_GUID = query.value("GUID").toInt();
//                            ptr->m_iedName = query.value("IEDNAME").toString();
//                            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
//                            ptr->m_type = query.value("TYPE").toInt();
//                            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
//                            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
//                            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
//                            ptr->m_dataRef = query.value("DATAREF").toString();
//                            ptr->m_selfType = query.value("SELFTYPE").toInt();
//                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                            lst.append(ptr);
//                        }
//                    }
//
    }
    db.close();

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByVoltage(const QString &voltage, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(type == -1)
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.IEDNAME=b.IEDNAME")
                            .arg(voltage);
        else
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.IEDNAME=b.IEDNAME AND a.SELFTYPE=%2")
                            .arg(voltage)
                            .arg(type);

        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }
//        if(type == -1)
//        {

//        }
//        else
//        {
//            int tmpType = type;
//            DBIedInfoDAO daoIed;
//            Ied::List lstIed = daoIed.doQueryByVoltage(db, voltage);
//            Ied::List::iterator iterIed;
//            DBDAStructDAO daoDAStruct;
//            for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//            {
//                Ied::Ptr ptrIed(new Ied());
//                ptrIed = *iterIed;
//                QString iedName = ptrIed->iedName();
//                QString iedCateGory = ptrIed->iedCateGory();
//                if(iedCateGory != "")
//                {
//                    if(iedCateGory == "Prot")
//                    {
//                        tmpType = m_relationHash[iedCateGory][type];
//                    }
//                    SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                    SoftVersion::List::iterator iter;
//                    bool tip = false;
//                    for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                    {
//                        SoftVersion::Ptr ptrTmp(new SoftVersion());
//                        ptrTmp = *iter;
//                        if(ptrTmp->type() == tmpType)
//                        {
//                            SoftVersion::Ptr ptr(new SoftVersion());
//                            ptr->m_GUID = ptrTmp->GUID();
//                            ptr->m_iedName = ptrTmp->iedName();
//                            ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                            ptr->m_type = ptrTmp->type();
//                            ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                            ptr->m_standardValue = ptrTmp->standardValue();
//                            ptr->m_defaultValue = ptrTmp->defaultValue();
//                            ptr->m_dataRef = ptrTmp->dataRef();
//                            ptr->m_dataType = ptrTmp->dataType();
//                            ptr->m_selfType = ptrTmp->selfType();
//                            if(needDAStruct)
//                                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                            lst.append(ptr);
//                            tip = true;
//                            break;
//                        }
//                    }
//                    if(!tip)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_iedName = iedName;
//                        ptr->m_iedCateGory = ptrIed->iedCateGory();
//                        ptr->m_type = tmpType;
//                        lst.append(ptr);
//                    }
//                }
////                else
////                {
////                    QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                            .arg(voltage)
////                            .arg(type);

////                    if(query.exec(sql))
////                    {
////                        DBDAStructDAO daoDAStruct;
////                        while(query.next())
////                        {
////                            SoftVersion::Ptr ptr(new SoftVersion());
////                            ptr->m_GUID = query.value("GUID").toInt();
////                            ptr->m_iedName = query.value("IEDNAME").toString();
////                            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                            ptr->m_type = query.value("TYPE").toInt();
////                            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                            ptr->m_dataRef = query.value("DATAREF").toString();
////                            ptr->m_selfType = query.value("SELFTYPE").toInt();
////                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                            lst.append(ptr);
////                        }
////                    }
////                }
//            }
//        }
        db.close();
    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByVoltClass(const QString &voltClass, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(type == -1)
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.IEDNAME=b.IEDNAME")
                        .arg(voltClass);
        else
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.IEDNAME=b.IEDNAME AND a.SELFTYPE=%2")
                        .arg(voltClass)
                        .arg(type);

        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }
//        if(type == -1)
//        {

//        }
//        else
//        {
//            int tmpType = type;
//            DBIedInfoDAO daoIed;
//            Ied::List lstIed = daoIed.doQueryByVoltClass(db, voltClass);
//            Ied::List::iterator iterIed;
//            DBDAStructDAO daoDAStruct;
//            for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//            {
//                Ied::Ptr ptrIed(new Ied());
//                ptrIed = *iterIed;
//                QString iedName = ptrIed->iedName();
//                QString iedCateGory = ptrIed->iedCateGory();
//                if(iedCateGory != "")
//                {
//                    if(iedCateGory == "Prot")
//                    {
//                        tmpType = m_relationHash[iedCateGory][type];
//                    }
//                    SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                    SoftVersion::List::iterator iter;
//                    bool tip = false;
//                    for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                    {
//                        SoftVersion::Ptr ptrTmp(new SoftVersion());
//                        ptrTmp = *iter;
//                        if(ptrTmp->type() == tmpType)
//                        {
//                            SoftVersion::Ptr ptr(new SoftVersion());
//                            ptr->m_GUID = ptrTmp->GUID();
//                            ptr->m_iedName = ptrTmp->iedName();
//                            ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                            ptr->m_type = ptrTmp->type();
//                            ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                            ptr->m_standardValue = ptrTmp->standardValue();
//                            ptr->m_defaultValue = ptrTmp->defaultValue();
//                            ptr->m_dataRef = ptrTmp->dataRef();
//                            ptr->m_dataType = ptrTmp->dataType();
//                            ptr->m_selfType = ptrTmp->selfType();
//                            if(needDAStruct)
//                                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                            lst.append(ptr);
//                            tip = true;
//                            break;
//                        }
//                    }
//                    if(!tip)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_iedName = iedName;
//                        ptr->m_iedCateGory = ptrIed->iedCateGory();
//                        ptr->m_type = tmpType;
//                        lst.append(ptr);
//                    }
//                }
////                else
////                {
////                    QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                            .arg(voltClass)
////                            .arg(type);

////                    if(query.exec(sql))
////                    {
////                        DBDAStructDAO daoDAStruct;
////                        while(query.next())
////                        {
////                            SoftVersion::Ptr ptr(new SoftVersion());
////                            ptr->m_GUID = query.value("GUID").toInt();
////                            ptr->m_iedName = query.value("IEDNAME").toString();
////                            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                            ptr->m_type = query.value("TYPE").toInt();
////                            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                            ptr->m_dataRef = query.value("DATAREF").toString();
////                            ptr->m_selfType = query.value("SELFTYPE").toInt();
////                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                            lst.append(ptr);
////                        }
////                    }
////                }
//            }
//        }
        db.close();
    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByStationName(const QString &stationName, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(type == -1)
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.IEDNAME=b.IEDNAME")
                        .arg(stationName);
        else
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.IEDNAME=b.IEDNAME AND a.SELFTYPE=%2")
                        .arg(stationName)
                        .arg(type);

        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }
//        if(type == -1)
//        {

//        }
//        else
//        {
//            int tmpType = type;
//            DBIedInfoDAO daoIed;
//            Ied::List lstIed = daoIed.doQueryByStationName(db, stationName);
//            Ied::List::iterator iterIed;
//            DBDAStructDAO daoDAStruct;
//            for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//            {
//                Ied::Ptr ptrIed(new Ied());
//                ptrIed = *iterIed;
//                QString iedName = ptrIed->iedName();
//                QString iedCateGory = ptrIed->iedCateGory();
//                if(iedCateGory != "")
//                {
//                    if(iedCateGory == "Prot")
//                    {
//                        tmpType = m_relationHash[iedCateGory][type];
//                    }
//                    SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                    SoftVersion::List::iterator iter;
//                    bool tip = false;
//                    for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                    {
//                        SoftVersion::Ptr ptrTmp(new SoftVersion());
//                        ptrTmp = *iter;
//                        if(ptrTmp->type() == tmpType)
//                        {
//                            SoftVersion::Ptr ptr(new SoftVersion());
//                            ptr->m_GUID = ptrTmp->GUID();
//                            ptr->m_iedName = ptrTmp->iedName();
//                            ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                            ptr->m_type = ptrTmp->type();
//                            ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                            ptr->m_standardValue = ptrTmp->standardValue();
//                            ptr->m_defaultValue = ptrTmp->defaultValue();
//                            ptr->m_dataRef = ptrTmp->dataRef();
//                            ptr->m_dataType = ptrTmp->dataType();
//                            ptr->m_selfType = ptrTmp->selfType();
//                            if(needDAStruct)
//                                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                            lst.append(ptr);
//                            tip = true;
//                            break;
//                        }
//                    }
//                    if(!tip)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_iedName = iedName;
//                        ptr->m_iedCateGory = ptrIed->iedCateGory();
//                        ptr->m_type = tmpType;
//                        lst.append(ptr);
//                    }
//                }
////                else
////                {
////                    QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                            .arg(stationName)
////                            .arg(type);

////                    if(query.exec(sql))
////                    {
////                        DBDAStructDAO daoDAStruct;
////                        while(query.next())
////                        {
////                            SoftVersion::Ptr ptr(new SoftVersion());
////                            ptr->m_GUID = query.value("GUID").toInt();
////                            ptr->m_iedName = query.value("IEDNAME").toString();
////                            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                            ptr->m_type = query.value("TYPE").toInt();
////                            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                            ptr->m_dataRef = query.value("DATAREF").toString();
////                            ptr->m_selfType = query.value("SELFTYPE").toInt();
////                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                            lst.append(ptr);
////                        }
////                    }
////                }
//            }
//        }
        db.close();
    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByBayName(const QString &bayName, const QString &iedCateGory, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(type == -1)
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\"")
                        .arg(bayName)
                        .arg(iedCateGory);
        else
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\" AND a.SELFTYPE=%3")
                        .arg(bayName)
                        .arg(iedCateGory)
                        .arg(type);
        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }
//        if(type == -1)
//        {

//        }
//        else
//        {
//            int tmpType = type;
//            DBIedInfoDAO daoIed;
//            Ied::List lstIed = daoIed.doQueryByBayNameLike(db, bayName);
//            Ied::List::iterator iterIed;
//            DBDAStructDAO daoDAStruct;
//            for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//            {
//                Ied::Ptr ptrIed(new Ied());
//                ptrIed = *iterIed;
//                QString iedName = ptrIed->iedName();
//                QString iedCateGoryTmp = ptrIed->iedCateGory();
//                if(iedCateGoryTmp != "" && iedCateGoryTmp == iedCateGory)
//                {
//                    if(iedCateGoryTmp == "Prot")
//                    {
//                        tmpType = m_relationHash[iedCateGory][type];
//                    }
//                    SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                    SoftVersion::List::iterator iter;
//                    bool tip = false;
//                    for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                    {
//                        SoftVersion::Ptr ptrTmp(new SoftVersion());
//                        ptrTmp = *iter;
//                        if(ptrTmp->type() == tmpType)
//                        {
//                            SoftVersion::Ptr ptr(new SoftVersion());
//                            ptr->m_GUID = ptrTmp->GUID();
//                            ptr->m_iedName = ptrTmp->iedName();
//                            ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                            ptr->m_type = ptrTmp->type();
//                            ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                            ptr->m_standardValue = ptrTmp->standardValue();
//                            ptr->m_defaultValue = ptrTmp->defaultValue();
//                            ptr->m_dataRef = ptrTmp->dataRef();
//                            ptr->m_dataType = ptrTmp->dataType();
//                            ptr->m_selfType = ptrTmp->selfType();
//                            if(needDAStruct)
//                                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                            lst.append(ptr);
//                            tip = true;
//                            break;
//                        }
//                    }
//                    if(!tip)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_iedName = iedName;
//                        ptr->m_iedCateGory = ptrIed->iedCateGory();
//                        ptr->m_type = tmpType;
//                        lst.append(ptr);
//                    }
//                }
////                else
////                {
////                    QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                            .arg(bayName);
////                    if(query.exec(sql))
////                    {
////                        DBDAStructDAO daoDAStruct;
////                        while(query.next())
////                        {
////                            SoftVersion::Ptr ptr(new SoftVersion());
////                            ptr->m_GUID = query.value("GUID").toInt();
////                            ptr->m_iedName = query.value("IEDNAME").toString();
////                            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                            ptr->m_type = query.value("TYPE").toInt();
////                            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                            ptr->m_dataRef = query.value("DATAREF").toString();
////                            ptr->m_selfType = query.value("SELFTYPE").toInt();
////                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                            lst.append(ptr);
////                        }
////                    }
////                }
//            }
//        }

        db.close();
    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByVoltage(const QString &voltage, const QString &iedCateGory, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(type == -1)
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\"")
                        .arg(voltage)
                        .arg(iedCateGory);
        else
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\" AND a.SELFTYPE=%3")
                        .arg(voltage)
                        .arg(iedCateGory)
                        .arg(type);

        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }
//        if(type == -1)
//        {

//        }
//        else
//        {
//            int tmpType = type;
//            DBIedInfoDAO daoIed;
//            Ied::List lstIed = daoIed.doQueryByVoltage(db, voltage);
//            Ied::List::iterator iterIed;
//            DBDAStructDAO daoDAStruct;
//            for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//            {
//                Ied::Ptr ptrIed(new Ied());
//                ptrIed = *iterIed;
//                QString iedName = ptrIed->iedName();
//                QString iedCateGoryTmp = ptrIed->iedCateGory();
//                if(iedCateGoryTmp != "" && iedCateGoryTmp == iedCateGory)
//                {
//                    if(iedCateGory == "Prot")
//                    {
//                        tmpType = m_relationHash[iedCateGory][type];
//                    }
//                    SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                    SoftVersion::List::iterator iter;
//                    bool tip = false;
//                    for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                    {
//                        SoftVersion::Ptr ptrTmp(new SoftVersion());
//                        ptrTmp = *iter;
//                        if(ptrTmp->type() == tmpType)
//                        {
//                            SoftVersion::Ptr ptr(new SoftVersion());
//                            ptr->m_GUID = ptrTmp->GUID();
//                            ptr->m_iedName = ptrTmp->iedName();
//                            ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                            ptr->m_type = ptrTmp->type();
//                            ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                            ptr->m_standardValue = ptrTmp->standardValue();
//                            ptr->m_defaultValue = ptrTmp->defaultValue();
//                            ptr->m_dataRef = ptrTmp->dataRef();
//                            ptr->m_dataType = ptrTmp->dataType();
//                            ptr->m_selfType = ptrTmp->selfType();
//                            if(needDAStruct)
//                                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                            lst.append(ptr);
//                            tip = true;
//                            break;
//                        }
//                    }
//                    if(!tip)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_iedName = iedName;
//                        ptr->m_iedCateGory = ptrIed->iedCateGory();
//                        ptr->m_type = tmpType;
//                        lst.append(ptr);
//                    }
//                }
////                else
////                {
////                    QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                            .arg(voltage)
////                            .arg(type);

////                    if(query.exec(sql))
////                    {
////                        DBDAStructDAO daoDAStruct;
////                        while(query.next())
////                        {
////                            SoftVersion::Ptr ptr(new SoftVersion());
////                            ptr->m_GUID = query.value("GUID").toInt();
////                            ptr->m_iedName = query.value("IEDNAME").toString();
////                            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                            ptr->m_type = query.value("TYPE").toInt();
////                            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                            ptr->m_dataRef = query.value("DATAREF").toString();
////                            ptr->m_selfType = query.value("SELFTYPE").toInt();
////                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                            lst.append(ptr);
////                        }
////                    }
////                }
//            }
//        }
        db.close();
    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByVoltClass(const QString &voltClass, const QString &iedCateGory, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(type == -1)
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\"")
                        .arg(voltClass)
                        .arg(iedCateGory);
        else
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\" AND a.SELFTYPE=%3")
                        .arg(voltClass)
                        .arg(iedCateGory)
                        .arg(type);

        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }
//        if(type == -1)
//        {

//        }
//        else
//        {
//            int tmpType = type;
//            DBIedInfoDAO daoIed;
//            Ied::List lstIed = daoIed.doQueryByVoltClass(db, voltClass);
//            Ied::List::iterator iterIed;
//            DBDAStructDAO daoDAStruct;
//            for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//            {
//                Ied::Ptr ptrIed(new Ied());
//                ptrIed = *iterIed;
//                QString iedName = ptrIed->iedName();
//                QString iedCateGoryTmp = ptrIed->iedCateGory();
//                if(iedCateGoryTmp != "" && iedCateGoryTmp == iedCateGory)
//                {
//                    if(iedCateGory == "Prot")
//                    {
//                        tmpType = m_relationHash[iedCateGory][type];
//                    }
//                    SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                    SoftVersion::List::iterator iter;
//                    bool tip = false;
//                    for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                    {
//                        SoftVersion::Ptr ptrTmp(new SoftVersion());
//                        ptrTmp = *iter;
//                        if(ptrTmp->type() == tmpType)
//                        {
//                            SoftVersion::Ptr ptr(new SoftVersion());
//                            ptr->m_GUID = ptrTmp->GUID();
//                            ptr->m_iedName = ptrTmp->iedName();
//                            ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                            ptr->m_type = ptrTmp->type();
//                            ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                            ptr->m_standardValue = ptrTmp->standardValue();
//                            ptr->m_defaultValue = ptrTmp->defaultValue();
//                            ptr->m_dataRef = ptrTmp->dataRef();
//                            ptr->m_dataType = ptrTmp->dataType();
//                            ptr->m_selfType = ptrTmp->selfType();
//                            if(needDAStruct)
//                                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                            lst.append(ptr);
//                            tip = true;
//                            break;
//                        }
//                    }
//                    if(!tip)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_iedName = iedName;
//                        ptr->m_iedCateGory = ptrIed->iedCateGory();
//                        ptr->m_type = tmpType;
//                        lst.append(ptr);
//                    }
//                }
////                else
////                {
////                    QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                            .arg(voltClass)
////                            .arg(type);

////                    if(query.exec(sql))
////                    {
////                        DBDAStructDAO daoDAStruct;
////                        while(query.next())
////                        {
////                            SoftVersion::Ptr ptr(new SoftVersion());
////                            ptr->m_GUID = query.value("GUID").toInt();
////                            ptr->m_iedName = query.value("IEDNAME").toString();
////                            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                            ptr->m_type = query.value("TYPE").toInt();
////                            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                            ptr->m_dataRef = query.value("DATAREF").toString();
////                            ptr->m_selfType = query.value("SELFTYPE").toInt();
////                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                            lst.append(ptr);
////                        }
////                    }
////                }
//            }
//        }
        db.close();
    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByStationName(const QString &stationName, const QString &iedCateGory, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql  = "";
        if(type == -1)
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\"")
                            .arg(stationName)
                            .arg(iedCateGory);
        else
            sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\" AND a.SELFTYPE=%3")
                            .arg(stationName)
                            .arg(iedCateGory)
                            .arg(type);

        if(query.exec(sql))
        {
            DBDAStructDAO daoDAStruct;
            while(query.next())
            {
                SoftVersion::Ptr ptr(new SoftVersion());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
                ptr->m_type = query.value("TYPE").toInt();
                ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_selfType = query.value("SELFTYPE").toInt();
                if(needDAStruct)
                    ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
                lst.append(ptr);
            }
        }
//        if(type == -1)
//        {

//        }
//        else
//        {
//            int tmpType = type;
//            DBIedInfoDAO daoIed;
//            Ied::List lstIed = daoIed.doQueryByStationName(db, stationName);
//            Ied::List::iterator iterIed;
//            DBDAStructDAO daoDAStruct;
//            for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//            {
//                Ied::Ptr ptrIed(new Ied());
//                ptrIed = *iterIed;
//                QString iedName = ptrIed->iedName();
//                QString iedCateGoryTmp = ptrIed->iedCateGory();
//                if(iedCateGoryTmp != "" && iedCateGoryTmp == iedCateGory)
//                {
//                    if(iedCateGory == "Prot")
//                    {
//                        tmpType = m_relationHash[iedCateGory][type];
//                    }
//                    SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                    SoftVersion::List::iterator iter;
//                    bool tip = false;
//                    for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                    {
//                        SoftVersion::Ptr ptrTmp(new SoftVersion());
//                        ptrTmp = *iter;
//                        if(ptrTmp->type() == tmpType)
//                        {
//                            SoftVersion::Ptr ptr(new SoftVersion());
//                            ptr->m_GUID = ptrTmp->GUID();
//                            ptr->m_iedName = ptrTmp->iedName();
//                            ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                            ptr->m_type = ptrTmp->type();
//                            ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                            ptr->m_standardValue = ptrTmp->standardValue();
//                            ptr->m_defaultValue = ptrTmp->defaultValue();
//                            ptr->m_dataRef = ptrTmp->dataRef();
//                            ptr->m_dataType = ptrTmp->dataType();
//                            ptr->m_selfType = ptrTmp->selfType();
//                            if(needDAStruct)
//                                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                            lst.append(ptr);
//                            tip = true;
//                            break;
//                        }
//                    }
//                    if(!tip)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_iedName = iedName;
//                        ptr->m_iedCateGory = ptrIed->iedCateGory();
//                        ptr->m_type = tmpType;
//                        lst.append(ptr);
//                    }
//                }
////                else
////                {
////                    QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                            .arg(stationName)
////                            .arg(type);

////                    if(query.exec(sql))
////                    {
////                        DBDAStructDAO daoDAStruct;
////                        while(query.next())
////                        {
////                            SoftVersion::Ptr ptr(new SoftVersion());
////                            ptr->m_GUID = query.value("GUID").toInt();
////                            ptr->m_iedName = query.value("IEDNAME").toString();
////                            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                            ptr->m_type = query.value("TYPE").toInt();
////                            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                            ptr->m_dataRef = query.value("DATAREF").toString();
////                            ptr->m_selfType = query.value("SELFTYPE").toInt();
////                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                            lst.append(ptr);
////                        }
////                    }
////                }
//            }
//        }
        db.close();
    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQuery(QSqlDatabase db, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM softversion");
    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM softversion WHERE IEDNAME=\"%1\"")
            .arg(iedName);
    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }

    return lst;
}

SoftVersion::Ptr DBSoftVersionDAO::doQueryBySelfType(QSqlDatabase db, const QString &iedName, int selfType, bool needDAStruct)
{
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM softversion WHERE IEDNAME=\"%1\" AND SELFTYPE=%2")
            .arg(iedName)
            .arg(selfType);
    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            return ptr;
        }
    }

    return NULL;
}

SoftVersion::List DBSoftVersionDAO::doQueryByBayName(QSqlDatabase db, const QString &bayName, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql = "";
    if(type == -1)
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.IEDNAME=b.IEDNAME")
                    .arg(bayName);
    else
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.IEDNAME=b.IEDNAME AND a.SELFTYPE=%2")
                    .arg(bayName)
                    .arg(type);
    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }
//    if(type == -1)
//    {

//    }
//    else
//    {
//        int tmpType = type;
//        DBIedInfoDAO daoIed;
//        Ied::List lstIed = daoIed.doQueryByBayNameLike(db, bayName);
//        Ied::List::iterator iterIed;
//        DBDAStructDAO daoDAStruct;
//        for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//        {
//            Ied::Ptr ptrIed(new Ied());
//            ptrIed = *iterIed;
//            QString iedName = ptrIed->iedName();
//            QString iedCateGory = ptrIed->iedCateGory();
//            if(iedCateGory != "")
//            {
//                if(iedCateGory == "Prot")
//                {
//                    tmpType = m_relationHash[iedCateGory][type];
//                }
//                SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                SoftVersion::List::iterator iter;
//                bool tip = false;
//                for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                {
//                    SoftVersion::Ptr ptrTmp(new SoftVersion());
//                    ptrTmp = *iter;
//                    if(ptrTmp->type() == tmpType)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_GUID = ptrTmp->GUID();
//                        ptr->m_iedName = ptrTmp->iedName();
//                        ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                        ptr->m_type = ptrTmp->type();
//                        ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                        ptr->m_standardValue = ptrTmp->standardValue();
//                        ptr->m_defaultValue = ptrTmp->defaultValue();
//                        ptr->m_dataRef = ptrTmp->dataRef();
//                        ptr->m_dataType = ptrTmp->dataType();
//                        ptr->m_selfType = ptrTmp->selfType();
//                        if(needDAStruct)
//                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                        lst.append(ptr);
//                        tip = true;
//                        break;
//                    }
//                }
//                if(!tip)
//                {
//                    SoftVersion::Ptr ptr(new SoftVersion());
//                    ptr->m_iedName = iedName;
//                    ptr->m_iedCateGory = ptrIed->iedCateGory();
//                    ptr->m_type = tmpType;
//                    lst.append(ptr);
//                }
//            }
////            else
////            {
////                QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                        .arg(bayName)
////                        .arg(type);
////                if(query.exec(sql))
////                {
////                    DBDAStructDAO daoDAStruct;
////                    while(query.next())
////                    {
////                        SoftVersion::Ptr ptr(new SoftVersion());
////                        ptr->m_GUID = query.value("GUID").toInt();
////                        ptr->m_iedName = query.value("IEDNAME").toString();
////                        ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                        ptr->m_type = query.value("TYPE").toInt();
////                        ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                        ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                        ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                        ptr->m_dataRef = query.value("DATAREF").toString();
////                        ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                        lst.append(ptr);
////                    }
////                }
////            }
//        }
//    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByVoltage(QSqlDatabase db, const QString &voltage, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql = "";
    if(type == -1)
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.IEDNAME=b.IEDNAME")
                        .arg(voltage);
    else
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.IEDNAME=b.IEDNAME AND a.SELFTYPE=%2")
                        .arg(voltage)
                        .arg(type);

    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }
//    if(type == -1)
//    {

//    }
//    else
//    {
//        int tmpType = type;
//        DBIedInfoDAO daoIed;
//        Ied::List lstIed = daoIed.doQueryByVoltage(db, voltage);
//        Ied::List::iterator iterIed;
//        DBDAStructDAO daoDAStruct;
//        for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//        {
//            Ied::Ptr ptrIed(new Ied());
//            ptrIed = *iterIed;
//            QString iedName = ptrIed->iedName();
//            QString iedCateGory = ptrIed->iedCateGory();
//            if(iedCateGory != "")
//            {
//                if(iedCateGory == "Prot")
//                {
//                    tmpType = m_relationHash[iedCateGory][type];
//                }
//                SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                SoftVersion::List::iterator iter;
//                bool tip = false;
//                for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                {
//                    SoftVersion::Ptr ptrTmp(new SoftVersion());
//                    ptrTmp = *iter;
//                    if(ptrTmp->type() == tmpType)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_GUID = ptrTmp->GUID();
//                        ptr->m_iedName = ptrTmp->iedName();
//                        ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                        ptr->m_type = ptrTmp->type();
//                        ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                        ptr->m_standardValue = ptrTmp->standardValue();
//                        ptr->m_defaultValue = ptrTmp->defaultValue();
//                        ptr->m_dataRef = ptrTmp->dataRef();
//                        ptr->m_dataType = ptrTmp->dataType();
//                        ptr->m_selfType = ptrTmp->selfType();
//                        if(needDAStruct)
//                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                        lst.append(ptr);
//                        tip = true;
//                        break;
//                    }
//                }
//                if(!tip)
//                {
//                    SoftVersion::Ptr ptr(new SoftVersion());
//                    ptr->m_iedName = iedName;
//                    ptr->m_iedCateGory = ptrIed->iedCateGory();
//                    ptr->m_type = tmpType;
//                    lst.append(ptr);
//                }
//            }
////            else
////            {
////                QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                        .arg(voltage)
////                        .arg(type);

////                if(query.exec(sql))
////                {
////                    DBDAStructDAO daoDAStruct;
////                    while(query.next())
////                    {
////                        SoftVersion::Ptr ptr(new SoftVersion());
////                        ptr->m_GUID = query.value("GUID").toInt();
////                        ptr->m_iedName = query.value("IEDNAME").toString();
////                        ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                        ptr->m_type = query.value("TYPE").toInt();
////                        ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                        ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                        ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                        ptr->m_dataRef = query.value("DATAREF").toString();
////                        ptr->m_selfType = query.value("SELFTYPE").toInt();
////                        ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                        lst.append(ptr);
////                    }
////                }
////            }
//        }
//    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByVoltClass(QSqlDatabase db, const QString &voltClass, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql = "";
    if(type == -1)
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.IEDNAME=b.IEDNAME")
                    .arg(voltClass);
    else
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.IEDNAME=b.IEDNAME AND a.SELFTYPE=%2")
                    .arg(voltClass)
                    .arg(type);

    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }
//    if(type == -1)
//    {

//    }
//    else
//    {
//        int tmpType = type;
//        DBIedInfoDAO daoIed;
//        Ied::List lstIed = daoIed.doQueryByVoltClass(db, voltClass);
//        Ied::List::iterator iterIed;
//        DBDAStructDAO daoDAStruct;
//        for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//        {
//            Ied::Ptr ptrIed(new Ied());
//            ptrIed = *iterIed;
//            QString iedName = ptrIed->iedName();
//            QString iedCateGory = ptrIed->iedCateGory();
//            if(iedCateGory != "")
//            {
//                if(iedCateGory == "Prot")
//                {
//                    tmpType = m_relationHash[iedCateGory][type];
//                }
//                SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                SoftVersion::List::iterator iter;
//                bool tip = false;
//                for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                {
//                    SoftVersion::Ptr ptrTmp(new SoftVersion());
//                    ptrTmp = *iter;
//                    if(ptrTmp->type() == tmpType)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_GUID = ptrTmp->GUID();
//                        ptr->m_iedName = ptrTmp->iedName();
//                        ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                        ptr->m_type = ptrTmp->type();
//                        ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                        ptr->m_standardValue = ptrTmp->standardValue();
//                        ptr->m_defaultValue = ptrTmp->defaultValue();
//                        ptr->m_dataRef = ptrTmp->dataRef();
//                        ptr->m_dataType = ptrTmp->dataType();
//                        ptr->m_selfType = ptrTmp->selfType();
//                        if(needDAStruct)
//                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                        lst.append(ptr);
//                        tip = true;
//                        break;
//                    }
//                }
//                if(!tip)
//                {
//                    SoftVersion::Ptr ptr(new SoftVersion());
//                    ptr->m_iedName = iedName;
//                    ptr->m_iedCateGory = ptrIed->iedCateGory();
//                    ptr->m_type = tmpType;
//                    lst.append(ptr);
//                }
//            }
////            else
////            {
////                QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                        .arg(voltClass)
////                        .arg(type);

////                if(query.exec(sql))
////                {
////                    DBDAStructDAO daoDAStruct;
////                    while(query.next())
////                    {
////                        SoftVersion::Ptr ptr(new SoftVersion());
////                        ptr->m_GUID = query.value("GUID").toInt();
////                        ptr->m_iedName = query.value("IEDNAME").toString();
////                        ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                        ptr->m_type = query.value("TYPE").toInt();
////                        ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                        ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                        ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                        ptr->m_dataRef = query.value("DATAREF").toString();
////                        ptr->m_selfType = query.value("SELFTYPE").toInt();
////                        ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                        lst.append(ptr);
////                    }
////                }
////            }
//        }
//    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByStationName(QSqlDatabase db, const QString &stationName, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql = "";
    if(type == -1)
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.IEDNAME=b.IEDNAME")
                    .arg(stationName);
    else
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.IEDNAME=b.IEDNAME AND a.SELFTYPE=%2")
                    .arg(stationName)
                    .arg(type);

    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }
//    if(type == -1)
//    {

//    }
//    else
//    {
//        int tmpType = type;
//        DBIedInfoDAO daoIed;
//        Ied::List lstIed = daoIed.doQueryByStationName(db, stationName);
//        Ied::List::iterator iterIed;
//        DBDAStructDAO daoDAStruct;
//        for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//        {
//            Ied::Ptr ptrIed(new Ied());
//            ptrIed = *iterIed;
//            QString iedName = ptrIed->iedName();
//            QString iedCateGory = ptrIed->iedCateGory();
//            if(iedCateGory != "")
//            {
//                if(iedCateGory == "Prot")
//                {
//                    tmpType = m_relationHash[iedCateGory][type];
//                }
//                SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                SoftVersion::List::iterator iter;
//                bool tip = false;
//                for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                {
//                    SoftVersion::Ptr ptrTmp(new SoftVersion());
//                    ptrTmp = *iter;
//                    if(ptrTmp->type() == tmpType)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_GUID = ptrTmp->GUID();
//                        ptr->m_iedName = ptrTmp->iedName();
//                        ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                        ptr->m_type = ptrTmp->type();
//                        ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                        ptr->m_standardValue = ptrTmp->standardValue();
//                        ptr->m_defaultValue = ptrTmp->defaultValue();
//                        ptr->m_dataRef = ptrTmp->dataRef();
//                        ptr->m_dataType = ptrTmp->dataType();
//                        ptr->m_selfType = ptrTmp->selfType();
//                        if(needDAStruct)
//                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                        lst.append(ptr);
//                        tip = true;
//                        break;
//                    }
//                }
//                if(!tip)
//                {
//                    SoftVersion::Ptr ptr(new SoftVersion());
//                    ptr->m_iedName = iedName;
//                    ptr->m_iedCateGory = ptrIed->iedCateGory();
//                    ptr->m_type = tmpType;
//                    lst.append(ptr);
//                }
//            }
////            else
////            {
////                QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                        .arg(stationName)
////                        .arg(type);
////                if(query.exec(sql))
////                {
////                    DBDAStructDAO daoDAStruct;
////                    while(query.next())
////                    {
////                        SoftVersion::Ptr ptr(new SoftVersion());
////                        ptr->m_GUID = query.value("GUID").toInt();
////                        ptr->m_iedName = query.value("IEDNAME").toString();
////                        ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                        ptr->m_type = query.value("TYPE").toInt();
////                        ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                        ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                        ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                        ptr->m_dataRef = query.value("DATAREF").toString();
////                        ptr->m_selfType = query.value("SELFTYPE").toInt();
////                        ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                        lst.append(ptr);
////                    }
////                }
////            }
//        }
//    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByBayName(QSqlDatabase db, const QString &bayName, const QString &iedCateGory, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql = "";
    if(type == -1)
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\"")
                    .arg(bayName)
                    .arg(iedCateGory);
    else
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\" AND a.SELFTYPE=%3")
                    .arg(bayName)
                    .arg(iedCateGory)
                    .arg(type);
    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }
//    if(type == -1)
//    {

//    }
//    else
//    {
//        int tmpType = type;
//        DBIedInfoDAO daoIed;
//        Ied::List lstIed = daoIed.doQueryByBayNameLike(db, bayName);
//        Ied::List::iterator iterIed;
//        DBDAStructDAO daoDAStruct;
//        for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//        {
//            Ied::Ptr ptrIed(new Ied());
//            ptrIed = *iterIed;
//            QString iedName = ptrIed->iedName();
//            QString iedCateGoryTmp = ptrIed->iedCateGory();
//            if(iedCateGoryTmp != "" && iedCateGoryTmp==iedCateGory)
//            {
//                if(iedCateGory == "Prot")
//                {
//                    tmpType = m_relationHash[iedCateGory][type];
//                }
//                SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                SoftVersion::List::iterator iter;
//                bool tip = false;
//                for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                {
//                    SoftVersion::Ptr ptrTmp(new SoftVersion());
//                    ptrTmp = *iter;
//                    if(ptrTmp->type() == tmpType)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_GUID = ptrTmp->GUID();
//                        ptr->m_iedName = ptrTmp->iedName();
//                        ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                        ptr->m_type = ptrTmp->type();
//                        ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                        ptr->m_standardValue = ptrTmp->standardValue();
//                        ptr->m_defaultValue = ptrTmp->defaultValue();
//                        ptr->m_dataRef = ptrTmp->dataRef();
//                        ptr->m_dataType = ptrTmp->dataType();
//                        ptr->m_selfType = ptrTmp->selfType();
//                        if(needDAStruct)
//                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                        lst.append(ptr);
//                        tip = true;
//                        break;
//                    }
//                }
//                if(!tip)
//                {
//                    SoftVersion::Ptr ptr(new SoftVersion());
//                    ptr->m_iedName = iedName;
//                    ptr->m_iedCateGory = ptrIed->iedCateGory();
//                    ptr->m_type = tmpType;
//                    lst.append(ptr);
//                }
//            }
////            else
////            {
////                QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE (b.BELONGALLBAYS LIKE \"%%1\" OR b.BELONGALLBAYS LIKE \"%%1|%\") AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                        .arg(bayName)
////                        .arg(type);
////                if(query.exec(sql))
////                {
////                    DBDAStructDAO daoDAStruct;
////                    while(query.next())
////                    {
////                        SoftVersion::Ptr ptr(new SoftVersion());
////                        ptr->m_GUID = query.value("GUID").toInt();
////                        ptr->m_iedName = query.value("IEDNAME").toString();
////                        ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                        ptr->m_type = query.value("TYPE").toInt();
////                        ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                        ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                        ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                        ptr->m_dataRef = query.value("DATAREF").toString();
////                        ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                        lst.append(ptr);
////                    }
////                }
////            }
//        }
//    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByVoltage(QSqlDatabase db, const QString &voltage, const QString &iedCateGory, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql = "";
    if(type == -1)
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\"")
                    .arg(voltage)
                    .arg(iedCateGory);
    else
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\" AND a.SELFTYPE=%3")
                    .arg(voltage)
                    .arg(iedCateGory)
                    .arg(type);

    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }
//    if(type == -1)
//    {

//    }
//    else
//    {
//        int tmpType = type;
//        DBIedInfoDAO daoIed;
//        Ied::List lstIed = daoIed.doQueryByVoltage(db, voltage);
//        Ied::List::iterator iterIed;
//        DBDAStructDAO daoDAStruct;
//        for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//        {
//            Ied::Ptr ptrIed(new Ied());
//            ptrIed = *iterIed;
//            QString iedName = ptrIed->iedName();
//            QString iedCateGoryTmp = ptrIed->iedCateGory();
//            if(iedCateGoryTmp != "" && iedCateGoryTmp==iedCateGory)
//            {
//                if(iedCateGory == "Prot")
//                {
//                    tmpType = m_relationHash[iedCateGory][type];
//                }
//                SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                SoftVersion::List::iterator iter;
//                bool tip = false;
//                for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                {
//                    SoftVersion::Ptr ptrTmp(new SoftVersion());
//                    ptrTmp = *iter;
//                    if(ptrTmp->type() == tmpType)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_GUID = ptrTmp->GUID();
//                        ptr->m_iedName = ptrTmp->iedName();
//                        ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                        ptr->m_type = ptrTmp->type();
//                        ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                        ptr->m_standardValue = ptrTmp->standardValue();
//                        ptr->m_defaultValue = ptrTmp->defaultValue();
//                        ptr->m_dataRef = ptrTmp->dataRef();
//                        ptr->m_dataType = ptrTmp->dataType();
//                        ptr->m_selfType = ptrTmp->selfType();
//                        if(needDAStruct)
//                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                        lst.append(ptr);
//                        tip = true;
//                        break;
//                    }
//                }
//                if(!tip)
//                {
//                    SoftVersion::Ptr ptr(new SoftVersion());
//                    ptr->m_iedName = iedName;
//                    ptr->m_iedCateGory = ptrIed->iedCateGory();
//                    ptr->m_type = tmpType;
//                    lst.append(ptr);
//                }
//            }
////            else
////            {
////                QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTAGE=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                        .arg(voltage)
////                        .arg(type);

////                if(query.exec(sql))
////                {
////                    DBDAStructDAO daoDAStruct;
////                    while(query.next())
////                    {
////                        SoftVersion::Ptr ptr(new SoftVersion());
////                        ptr->m_GUID = query.value("GUID").toInt();
////                        ptr->m_iedName = query.value("IEDNAME").toString();
////                        ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                        ptr->m_type = query.value("TYPE").toInt();
////                        ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                        ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                        ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                        ptr->m_dataRef = query.value("DATAREF").toString();
////                        ptr->m_selfType = query.value("SELFTYPE").toInt();
////                        ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                        lst.append(ptr);
////                    }
////                }
////            }
//        }
//    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByVoltClass(QSqlDatabase db, const QString &voltClass, const QString &iedCateGory, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql = "";
    if(type == -1)
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\"")
                    .arg(voltClass)
                    .arg(iedCateGory);
    else
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\" AND a.SELFTYPE=%3")
                    .arg(voltClass)
                    .arg(iedCateGory)
                    .arg(type);

    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }
//    if(type == -1)
//    {

//    }
//    else
//    {
//        int tmpType = type;
//        DBIedInfoDAO daoIed;
//        Ied::List lstIed = daoIed.doQueryByVoltClass(db, voltClass);
//        Ied::List::iterator iterIed;
//        DBDAStructDAO daoDAStruct;
//        for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//        {
//            Ied::Ptr ptrIed(new Ied());
//            ptrIed = *iterIed;
//            QString iedName = ptrIed->iedName();
//            QString iedCateGoryTmp = ptrIed->iedCateGory();
//            if(iedCateGoryTmp != "" && iedCateGoryTmp==iedCateGory)
//            {
//                if(iedCateGory == "Prot")
//                {
//                    tmpType = m_relationHash[iedCateGory][type];
//                }
//                SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                SoftVersion::List::iterator iter;
//                bool tip = false;
//                for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                {
//                    SoftVersion::Ptr ptrTmp(new SoftVersion());
//                    ptrTmp = *iter;
//                    if(ptrTmp->type() == tmpType)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_GUID = ptrTmp->GUID();
//                        ptr->m_iedName = ptrTmp->iedName();
//                        ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                        ptr->m_type = ptrTmp->type();
//                        ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                        ptr->m_standardValue = ptrTmp->standardValue();
//                        ptr->m_defaultValue = ptrTmp->defaultValue();
//                        ptr->m_dataRef = ptrTmp->dataRef();
//                        ptr->m_dataType = ptrTmp->dataType();
//                        ptr->m_selfType = ptrTmp->selfType();
//                        if(needDAStruct)
//                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                        lst.append(ptr);
//                        tip = true;
//                        break;
//                    }
//                }
//                if(!tip)
//                {
//                    SoftVersion::Ptr ptr(new SoftVersion());
//                    ptr->m_iedName = iedName;
//                    ptr->m_iedCateGory = ptrIed->iedCateGory();
//                    ptr->m_type = tmpType;
//                    lst.append(ptr);
//                }
//            }
////            else
////            {
////                QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.VOLTCLASSID=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                        .arg(voltClass)
////                        .arg(type);

////                if(query.exec(sql))
////                {
////                    DBDAStructDAO daoDAStruct;
////                    while(query.next())
////                    {
////                        SoftVersion::Ptr ptr(new SoftVersion());
////                        ptr->m_GUID = query.value("GUID").toInt();
////                        ptr->m_iedName = query.value("IEDNAME").toString();
////                        ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                        ptr->m_type = query.value("TYPE").toInt();
////                        ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                        ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                        ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                        ptr->m_dataRef = query.value("DATAREF").toString();
////                        ptr->m_selfType = query.value("SELFTYPE").toInt();
////                        ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                        lst.append(ptr);
////                    }
////                }
////            }
//        }
//    }

    return lst;
}

SoftVersion::List DBSoftVersionDAO::doQueryByStationName(QSqlDatabase db, const QString &stationName, const QString &iedCateGory, int type, bool needDAStruct)
{
    SoftVersion::List lst;
    QSqlQuery query(db);
    QString sql  = "";
    if(type == -1)
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\"")
                        .arg(stationName)
                        .arg(iedCateGory);
    else
        sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.DATATYPE, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.IEDNAME=b.IEDNAME AND b.IEDCATEGORY=\"%2\" AND a.SELFTYPE=%3")
                        .arg(stationName)
                        .arg(iedCateGory)
                        .arg(type);

    if(query.exec(sql))
    {
        DBDAStructDAO daoDAStruct;
        while(query.next())
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
            ptr->m_type = query.value("TYPE").toInt();
            ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_selfType = query.value("SELFTYPE").toInt();
            if(needDAStruct)
                ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
            lst.append(ptr);
        }
    }
//    if(type == -1)
//    {

//    }
//    else
//    {
//        int tmpType = type;
//        DBIedInfoDAO daoIed;
//        Ied::List lstIed = daoIed.doQueryByStationName(db, stationName);
//        Ied::List::iterator iterIed;
//        DBDAStructDAO daoDAStruct;
//        for(iterIed=lstIed.begin(); iterIed!=lstIed.end(); iterIed++)
//        {
//            Ied::Ptr ptrIed(new Ied());
//            ptrIed = *iterIed;
//            QString iedName = ptrIed->iedName();
//            QString iedCateGoryTmp = ptrIed->iedCateGory();
//            if(iedCateGoryTmp != "" && iedCateGoryTmp==iedCateGory)
//            {
//                if(iedCateGory == "Prot")
//                {
//                    tmpType = m_relationHash[iedCateGory][type];
//                }
//                SoftVersion::List lstTmp = this->doQueryByIedName(db, iedName);
//                SoftVersion::List::iterator iter;
//                bool tip = false;
//                for(iter=lstTmp.begin(); iter!=lstTmp.end(); iter++)
//                {
//                    SoftVersion::Ptr ptrTmp(new SoftVersion());
//                    ptrTmp = *iter;
//                    if(ptrTmp->type() == tmpType)
//                    {
//                        SoftVersion::Ptr ptr(new SoftVersion());
//                        ptr->m_GUID = ptrTmp->GUID();
//                        ptr->m_iedName = ptrTmp->iedName();
//                        ptr->m_iedCateGory = ptrTmp->iedCateGory();
//                        ptr->m_type = ptrTmp->type();
//                        ptr->m_softVerDesc = ptrTmp->softVerDesc();
//                        ptr->m_standardValue = ptrTmp->standardValue();
//                        ptr->m_defaultValue = ptrTmp->defaultValue();
//                        ptr->m_dataRef = ptrTmp->dataRef();
//                        ptr->m_dataType = ptrTmp->dataType();
//                        ptr->m_selfType = ptrTmp->selfType();
//                        if(needDAStruct)
//                            ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
//                        lst.append(ptr);
//                        tip = true;
//                        break;
//                    }
//                }
//                if(!tip)
//                {
//                    SoftVersion::Ptr ptr(new SoftVersion());
//                    ptr->m_iedName = iedName;
//                    ptr->m_iedCateGory = ptrIed->iedCateGory();
//                    ptr->m_type = tmpType;
//                    lst.append(ptr);
//                }
//            }
////            else
////            {
////                QString sql = QObject::tr("SELECT a.GUID, a.IEDNAME, a.IEDCATEGORY, a.TYPE, a.SOFTVERDESC, a.STANDARDVALUE, a.DEFAULTVALUE, a.DATAREF, a.SELFTYPE FROM softversion a, iedinfo b WHERE b.STATIONID=\"%1\" AND a.SELFTYPE=%2 AND a.IEDNAME=b.IEDNAME")
////                        .arg(stationName)
////                        .arg(type);
////                if(query.exec(sql))
////                {
////                    DBDAStructDAO daoDAStruct;
////                    while(query.next())
////                    {
////                        SoftVersion::Ptr ptr(new SoftVersion());
////                        ptr->m_GUID = query.value("GUID").toInt();
////                        ptr->m_iedName = query.value("IEDNAME").toString();
////                        ptr->m_iedCateGory = query.value("IEDCATEGORY").toString();
////                        ptr->m_type = query.value("TYPE").toInt();
////                        ptr->m_softVerDesc = query.value("SOFTVERDESC").toString();
////                        ptr->m_standardValue = query.value("STANDARDVALUE").toString();
////                        ptr->m_defaultValue = query.value("DEFAULTVALUE").toString();
////                        ptr->m_dataRef = query.value("DATAREF").toString();
////                        ptr->m_selfType = query.value("SELFTYPE").toInt();
////                        ptr->m_lstDAStruct = daoDAStruct.doQueryVec(db, ptr->dataRef());
////                        lst.append(ptr);
////                    }
////                }
////            }
//        }
//    }

    return lst;
}

bool DBSoftVersionDAO::doInsert(SoftVersion::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;

    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        SoftVersion::List::iterator iter;
        QSqlQuery query(db);
        query.exec("begin transaction");
        QString sql = "";

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO softversion VALUES(NULL, \"%1\", \"%2\", %3, \"%4\", \"%5\", \"%6\", \"%7\", \"%8\", %9)")
                    .arg(ptr->iedName())//1
                    .arg(ptr->iedCateGory())//2
                    .arg(ptr->type())//3
                    .arg(ptr->softVerDesc())//4
                    .arg(ptr->standardValue())//5
                    .arg(ptr->defaultValue())//6
                    .arg(ptr->dataRef())//7
                    .arg(ptr->dataType())//8
                    .arg(ptr->selfType());//9
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

bool DBSoftVersionDAO::doUpdate(SoftVersion::List &lst)
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
        SoftVersion::List::iterator iter;
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr = *iter;
            sql = QObject::tr("UPDATE softversion SET IEDNAME=\"%1\", TYPE=%2, SOFTVERDESC=\"%3\", STANDARDVALUE=\"%4\", DEFAULTVALUE=\"%5\", IEDCATEGORY=\"%6\", DATAREF=\"%7\", DATATYPE=\"%8\", SELFTYPE=%9 WHERE GUID=%10")
                    .arg(ptr->iedName())
                    .arg(ptr->type())
                    .arg(ptr->softVerDesc())
                    .arg(ptr->standardValue())
                    .arg(ptr->defaultValue())
                    .arg(ptr->iedCateGory())
                    .arg(ptr->dataRef())
                    .arg(ptr->dataType())
                    .arg(ptr->selfType())
                    .arg(ptr->GUID());
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

bool DBSoftVersionDAO::doUpdate(const QString &iedName, int type, const QString &dataValue)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE softversion SET STANDARDVALUE=\"%1\" WHERE IEDNAME=\"%2\" AND TYPE=%3")
                .arg(dataValue)
                .arg(iedName)
                .arg(type);
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBSoftVersionDAO::doDelete(SoftVersion::List &lst)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        SoftVersion::List::iterator iter;
        query.exec("begin transaction");
        QString sql = "";
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            SoftVersion::Ptr ptr(new SoftVersion());
            ptr = *iter;
            sql = QObject::tr("DELETE * FROM softversion WHERE GUID=%1")
                    .arg(ptr->GUID());
            if(query.exec(sql))
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

bool DBSoftVersionDAO::doDelete(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE * FROM softversion WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBSoftVersionDAO::doDelete(const QString &iedName, int type)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE * FROM softversion WHERE IEDNAME=\"%1\" AND TYPE=%2")
                .arg(iedName)
                .arg(type);
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

bool DBSoftVersionDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM softversion");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='softversion'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBSoftVersionDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS softversion("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "IEDNAME CHAR(255) UNIQUE NOT NULL,"
                                  "IEDCATEGORY CHAR(255) NOT NULL,"
                                  "TYPE INTEGER NOT NULL,"
                                  "SOFTVERDESC CHAR(255) NOT NULL,"
                                  "STANDARDVALUE CHAR(255) NOT NULL,"
                                  "DEFAULTVALUE CHAR(255) NOT NULL,"
                                  "DATAREF CHAR(255) NOT NULL,"
                                  "DATATYPE CHAR(255) NOT NULL,"
                                  "SELFTYPE INTEGER NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

QHash<QString, QHash<int, int> > DBSoftVersionDAO::relation()
{
    QHash<QString, QHash<int, int>> hashRelation;
    QHash<int, int> protHash;
    protHash.insert(1, 0);
    protHash.insert(4, 1);
    protHash.insert(5, 2);
    protHash.insert(6, 3);
    protHash.insert(7, 4);
    protHash.insert(8, 5);
    protHash.insert(9, 6);
    protHash.insert(10, 7);
    protHash.insert(11, 8);
    protHash.insert(12, 9);
    protHash.insert(13, 10);
    protHash.insert(14, 11);
    hashRelation.insert("Prot", protHash);
    return hashRelation;
}
