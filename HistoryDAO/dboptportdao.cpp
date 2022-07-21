#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
#include <QHash>
#include "dbconnection.h"
#include "optport.h"
#include "dboptportdao.h"
#include "dastruct.h"
#include "dbdastructdao.h"
//#include "realdata.h"
//#include "dbrealdatadao.h"
DBOptPortDAO::DBOptPortDAO()
    : m_connectionName("connectOptPort")
{

}

DBOptPortDAO::~DBOptPortDAO()
{

}

OptPort::List DBOptPortDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    OptPort::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM optport");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                OptPort::Ptr ptr(new OptPort("0", "0", "-1", "-1", "-1", "-1"));
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_portID = query.value("PORTID").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_portDesc = query.value("PORTDESC").toString();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
                ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
                ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
                ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
                ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
                ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
                ptr->m_sendMax = query.value("SENDMAX").toFloat();
                ptr->m_sendMin = query.value("SENDMIN").toFloat();
                ptr->m_recvMax = query.value("RECVMAX").toFloat();
                ptr->m_recvMin = query.value("RECVMIN").toFloat();
                ptr->m_netType = query.value("NETTYPE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

OptPort::List DBOptPortDAO::doQueryByLineRef(const QString &lineRef, bool *ok)
{
    bool bSucc = false;
    OptPort::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM optport WHERE LINEREF=\"%1\"")
                .arg(lineRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                OptPort::Ptr ptr(new OptPort());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_portID = query.value("PORTID").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_portDesc = query.value("PORTDESC").toString();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
                ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
                ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
                ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
                ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
                ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
                ptr->m_sendMax = query.value("SENDMAX").toFloat();
                ptr->m_sendMin = query.value("SENDMIN").toFloat();
                ptr->m_recvMax = query.value("RECVMAX").toFloat();
                ptr->m_recvMin = query.value("RECVMIN").toFloat();
                ptr->m_netType = query.value("NETTYPE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

OptPort::List DBOptPortDAO::doQueryByIedName(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    OptPort::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM optport WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                OptPort::Ptr ptr(new OptPort());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_portID = query.value("PORTID").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_portDesc = query.value("PORTDESC").toString();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
                ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
                ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
                ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
                ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
                ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
                ptr->m_sendMax = query.value("SENDMAX").toFloat();
                ptr->m_sendMin = query.value("SENDMIN").toFloat();
                ptr->m_recvMax = query.value("RECVMAX").toFloat();
                ptr->m_recvMin = query.value("RECVMIN").toFloat();
                ptr->m_netType = query.value("NETTYPE").toInt();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

OptPort::Ptr DBOptPortDAO::doQueryByPortID(const QString &iedName, const QString &portID, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM optport WHERE IEDNAME=\"%1\" AND PORTID=\"%2\"")
                .arg(iedName)
                .arg(portID);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                OptPort::Ptr ptr(new OptPort());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_portID = query.value("PORTID").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_portDesc = query.value("PORTDESC").toString();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
                ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
                ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
                ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
                ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
                ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
                ptr->m_sendMax = query.value("SENDMAX").toFloat();
                ptr->m_sendMin = query.value("SENDMIN").toFloat();
                ptr->m_recvMax = query.value("RECVMAX").toFloat();
                ptr->m_recvMin = query.value("RECVMIN").toFloat();
                ptr->m_netType = query.value("NETTYPE").toInt();
                if(ok)
                    *ok = bSucc;
                db.close();
                return ptr;
            }
            db.close();
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

OptPort *DBOptPortDAO::port(QSqlDatabase db, const QString &iedName, const QString &portID, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM optport WHERE IEDNAME=\"%1\" AND PORTID=\"%2\"")
            .arg(iedName)
            .arg(portID);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            OptPort *ptr = new OptPort();
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_portID = query.value("PORTID").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_portDesc = query.value("PORTDESC").toString();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
            ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
            ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
            ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
            ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
            ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
            ptr->m_sendMax = query.value("SENDMAX").toFloat();
            ptr->m_sendMin = query.value("SENDMIN").toFloat();
            ptr->m_recvMax = query.value("RECVMAX").toFloat();
            ptr->m_recvMin = query.value("RECVMIN").toFloat();
            ptr->m_netType = query.value("NETTYPE").toInt();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

QHash<QString, QList<int> > DBOptPortDAO::doQueryNetType(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    QHash<QString, QHash<int, int>> qHashTemp;
    QHash<QString, QList<int>> qHash;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT a.NETTYPE, b.VOLTCLASSID FROM optport a, iedinfo b WHERE a.IEDNAME=b.IEDNAME");
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            QString voltClass = query.value("VOLTCLASSID").toString();
            int portNetType = query.value("NETTYPE").toInt();
            if(qHashTemp.count(voltClass) == 0)
            {
                QHash<int, int> qHashTemp2;
                qHashTemp.insert(voltClass, qHashTemp2);
                QList<int> qList;
                qHash.insert(voltClass, qList);
            }
            if(qHashTemp[voltClass].count(portNetType) == 0)
            {
                qHashTemp[voltClass].insert(portNetType, 1);
                qHash[voltClass].append(portNetType);
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return qHash;
}

OptPort * DBOptPortDAO::port(const QString &iedName, const QString &portID, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM optport WHERE IEDNAME=\"%1\" AND PORTID=\"%2\"")
                .arg(iedName)
                .arg(portID);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                OptPort *ptr = new OptPort();
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_portID = query.value("PORTID").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_portDesc = query.value("PORTDESC").toString();
                ptr->m_lineRef = query.value("LINEREF").toString();
                ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
                ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
                ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
                ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
                ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
                ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
                ptr->m_sendMax = query.value("SENDMAX").toFloat();
                ptr->m_sendMin = query.value("SENDMIN").toFloat();
                ptr->m_recvMax = query.value("RECVMAX").toFloat();
                ptr->m_recvMin = query.value("RECVMIN").toFloat();
                ptr->m_netType = query.value("NETTYPE").toInt();
                if(ok)
                    *ok = bSucc;
                db.close();
                return ptr;
            }
            db.close();
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

QHash<QString, QList<int>> DBOptPortDAO::doQueryNetType(bool *ok)
{
    bool bSucc = false;
    QHash<QString, QHash<int, int>> qHashTemp;
    QHash<QString, QList<int>> qHash;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT a.NETTYPE, b.VOLTCLASSID FROM optport a, iedinfo b WHERE a.IEDNAME=b.IEDNAME");
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                QString voltClass = query.value("VOLTCLASSID").toString();
                int portNetType = query.value("NETTYPE").toInt();
                if(qHashTemp.count(voltClass) == 0)
                {
                    QHash<int, int> qHashTemp2;
                    qHashTemp.insert(voltClass, qHashTemp2);
                    QList<int> qList;
                    qHash.insert(voltClass, qList);
                }
                if(qHashTemp[voltClass].count(portNetType) == 0)
                {
                    qHashTemp[voltClass].insert(portNetType, 1);
                    qHash[voltClass].append(portNetType);
                }
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return qHash;
}

OptPort::List DBOptPortDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    OptPort::List lst;
    QString sql = QObject::tr("SELECT * FROM optport");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            OptPort::Ptr ptr(new OptPort("0", "0", "-1", "-1", "-1", "-1"));
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_portID = query.value("PORTID").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_portDesc = query.value("PORTDESC").toString();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
            ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
            ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
            ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
            ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
            ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
            ptr->m_sendMax = query.value("SENDMAX").toFloat();
            ptr->m_sendMin = query.value("SENDMIN").toFloat();
            ptr->m_recvMax = query.value("RECVMAX").toFloat();
            ptr->m_recvMin = query.value("RECVMIN").toFloat();
            ptr->m_netType = query.value("NETTYPE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

OptPort::List DBOptPortDAO::doQueryByLineRef(QSqlDatabase db, const QString &lineRef, bool *ok)
{
    bool bSucc = false;
    OptPort::List lst;
    QString sql = QObject::tr("SELECT * FROM optport WHERE LINEREF=\"%1\"")
            .arg(lineRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            OptPort::Ptr ptr(new OptPort());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_portID = query.value("PORTID").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_portDesc = query.value("PORTDESC").toString();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
            ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
            ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
            ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
            ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
            ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
            ptr->m_sendMax = query.value("SENDMAX").toFloat();
            ptr->m_sendMin = query.value("SENDMIN").toFloat();
            ptr->m_recvMax = query.value("RECVMAX").toFloat();
            ptr->m_recvMin = query.value("RECVMIN").toFloat();
            ptr->m_netType = query.value("NETTYPE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

OptPort::List DBOptPortDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    OptPort::List lst;
    QString sql = QObject::tr("SELECT * FROM optport WHERE IEDNAME=\"%1\"")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            OptPort::Ptr ptr(new OptPort());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_portID = query.value("PORTID").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_portDesc = query.value("PORTDESC").toString();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
            ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
            ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
            ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
            ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
            ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
            ptr->m_sendMax = query.value("SENDMAX").toFloat();
            ptr->m_sendMin = query.value("SENDMIN").toFloat();
            ptr->m_recvMax = query.value("RECVMAX").toFloat();
            ptr->m_recvMin = query.value("RECVMIN").toFloat();
            ptr->m_netType = query.value("NETTYPE").toInt();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

OptPort::Ptr DBOptPortDAO::doQueryByPortID(QSqlDatabase db, const QString &iedName, const QString &portID, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM optport WHERE IEDNAME=\"%1\" AND PORTID=\"%2\"")
            .arg(iedName)
            .arg(portID);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            OptPort::Ptr ptr(new OptPort());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_portID = query.value("PORTID").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_portDesc = query.value("PORTDESC").toString();
            ptr->m_lineRef = query.value("LINEREF").toString();
            ptr->m_sendValueRef = query.value("SENDVALUEREF").toString();
            ptr->m_recvValueRef = query.value("RECVVALUEREF").toString();
            ptr->m_sendUpAlarmRef = query.value("SENDUPALARMREF").toString();
            ptr->m_sendDownAlarmRef = query.value("SENDDOWNALARMREF").toString();
            ptr->m_recvUpAlarmRef = query.value("RECVUPALARMREF").toString();
            ptr->m_recvDownAlarmRef = query.value("RECVDOWNALARMREF").toString();
            ptr->m_sendMax = query.value("SENDMAX").toFloat();
            ptr->m_sendMin = query.value("SENDMIN").toFloat();
            ptr->m_recvMax = query.value("RECVMAX").toFloat();
            ptr->m_recvMin = query.value("RECVMIN").toFloat();
            ptr->m_netType = query.value("NETTYPE").toInt();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

QList<int> DBOptPortDAO::doQueryNetType(QSqlDatabase db, const QString &stationName, bool *ok)
{
    bool bSucc = false;
    QList<int> lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT a.NETTYPE FROM optport a, iedinfo b WHERE a.IEDNAME=b.IEDNAME AND b.STATIONID=\"%1\"")
            .arg(stationName);
    QHash<int, int> qHash;
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            int portNetType = query.value("NETTYPE").toInt();
            if(qHash.count(portNetType) == 0)
            {
                qHash.insert(portNetType, 0);
                lst.append(portNetType);
            }
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBOptPortDAO::doInsert(OptPort::List &lst)
{
    bool bSucc = false;
    OptPort::List::iterator iter = lst.begin();
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
                OptPort::Ptr ptr(new OptPort());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO optport VALUES (NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\", \"%9\", \"%10\", %11, %12, %13, %14, %15)")
                        .arg(ptr->m_portID)//1
                        .arg(ptr->m_iedName)//2
                        .arg(ptr->m_portDesc)//3
                        .arg(ptr->m_lineRef)//4
                        .arg(ptr->m_sendValueRef)//5
                        .arg(ptr->m_recvValueRef)//6
                        .arg(ptr->m_sendUpAlarmRef)//7
                        .arg(ptr->m_sendDownAlarmRef)//8
                        .arg(ptr->m_recvUpAlarmRef)//9
                        .arg(ptr->m_recvDownAlarmRef)//10
                        .arg(ptr->m_sendMax)//11
                        .arg(ptr->m_sendMin)//12
                        .arg(ptr->m_recvMax)//13
                        .arg(ptr->m_recvMin)//14
                        .arg(ptr->m_netType);//15
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
                OptPort::Ptr ptr(new OptPort());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO optport VALUES (NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\", \"%9\", \"%10\", %11, %12, %13, %14, %15)")
                        .arg(ptr->m_portID)//1
                        .arg(ptr->m_iedName)//2
                        .arg(ptr->m_portDesc)//3
                        .arg(ptr->m_lineRef)//4
                        .arg(ptr->m_sendValueRef)//5
                        .arg(ptr->m_recvValueRef)//6
                        .arg(ptr->m_sendUpAlarmRef)//7
                        .arg(ptr->m_sendDownAlarmRef)//8
                        .arg(ptr->m_recvUpAlarmRef)//9
                        .arg(ptr->m_recvDownAlarmRef)//10
                        .arg(ptr->m_sendMax)//11
                        .arg(ptr->m_sendMin)//12
                        .arg(ptr->m_recvMax)//13
                        .arg(ptr->m_recvMin)//14
                        .arg(ptr->m_netType);//15
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

bool DBOptPortDAO::doUpdate(const OptPort::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE optport SET PORTID=\"%1\", IEDNAME=\"%2\", PORTDESC=\"%3\", LINEREF=\"%4\", SENDVALUEREF=\"%5\", RECVVALUEREF=\"%6\", SENDUPALARMREF=\"%7\", SENDDOWNALARMREF=\"%8\", RECVUPALARMREF=\"%9\", RECVDOWNALARMREF=\"%10\", SENDMAX=%11, SENDMIN=%12, RECVMAX=%13, RECVMIN=%14, NETTYPE=%15 WHERE GUID=%16")
                .arg(ptr->portID())//1
                .arg(ptr->iedName())//2
                .arg(ptr->portDesc())//3
                .arg(ptr->lineRef())//4
                .arg(ptr->sendValueRef())//5
                .arg(ptr->recvValueRef())//6
                .arg(ptr->sendUpAlarmRef())//7
                .arg(ptr->sendDownAlarmRef())//8
                .arg(ptr->recvUpAlarmRef())//9
                .arg(ptr->recvDownAlarmRef())//10
                .arg(ptr->sendMax())//11
                .arg(ptr->sendMin())//12
                .arg(ptr->recvMax())//13
                .arg(ptr->recvMin())//14
                .arg(ptr->netType())//15
                .arg(ptr->GUID());//16
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOptPortDAO::doUpdate(OptPort::List &lst)
{
    bool bSucc = false;
    OptPort::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            OptPort::Ptr ptr(new OptPort());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE optport SET PORTID=\"%1\", IEDNAME=\"%2\", PORTDESC=\"%3\", LINEREF=\"%4\", SENDVALUEREF=\"%5\", RECVVALUEREF=\"%6\", SENDUPALARMREF=\"%7\", SENDDOWNALARMREF=\"%8\", RECVUPALARMREF=\"%9\", RECVDOWNALARMREF=\"%10\", SENDMAX=%11, SENDMIN=%12, RECVMAX=%13, RECVMIN=%14, NETTYPE=%15 WHERE GUID=%16")
                    .arg(ptr->portID())//1
                    .arg(ptr->iedName())//2
                    .arg(ptr->portDesc())//3
                    .arg(ptr->lineRef())//4
                    .arg(ptr->sendValueRef())//5
                    .arg(ptr->recvValueRef())//6
                    .arg(ptr->sendUpAlarmRef())//7
                    .arg(ptr->sendDownAlarmRef())//8
                    .arg(ptr->recvUpAlarmRef())//9
                    .arg(ptr->recvDownAlarmRef())//10
                    .arg(ptr->sendMax())//11
                    .arg(ptr->sendMin())//12
                    .arg(ptr->recvMax())//13
                    .arg(ptr->recvMin())//14
                    .arg(ptr->netType())//15
                    .arg(ptr->GUID());//16
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

bool DBOptPortDAO::doDeleteByLineRef(const QString &lineRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM optport WHERE LINEREF=\"%1\"")
                .arg(lineRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOptPortDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM optport WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOptPortDAO::doDeleteByPortID(const QString &portID)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM optport WHERE PORTID=\"%1\"")
                .arg(portID);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOptPortDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM optport");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='optport'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOptPortDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS optport("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "PORTID CHAR(255) NOT NULL,"
                                  "IEDNAME CHAR(255) NOT NULL,"
                                  "PORTDESC CHAR(255) NOT NULL,"
                                  "LINEREF CHAR(255) NOT NULL,"
                                  "SENDVALUEREF CHAR(255) NOT NULL,"
                                  "RECVVALUEREF CHAR(255) NOT NULL,"
                                  "SENDUPALARMREF CHAR(255) NOT NULL,"
                                  "SENDDOWNALARMREF CHAR(255) NOT NULL,"
                                  "RECVUPALARMREF CHAR(255) NOT NULL,"
                                  "RECVDOWNALARMREF CHAR(255) NOT NULL,"
                                  "SENDMAX FLOAT(8,3) NOT NULL,"
                                  "SENDMIN FLOAT(8,3) NOT NULL,"
                                  "RECVDMAX FLOAT(8,3) NOT NULL,"
                                  "RECVMIN FLOAT(8,3) NOT NULL,"
                                  "NETTYPE INTEGER NOT NULL,"
                                  "UNIQUE(IEDNAME, PORTID)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
