#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QVariant>
#include "dbconnection.h"
#include "dbrcddevicedao.h"
DBRcdDeviceDAO::DBRcdDeviceDAO()
    : m_connectionName("connectRcdDevice")
{

}

DBRcdDeviceDAO::~DBRcdDeviceDAO()
{

}

RcdDevice::List DBRcdDeviceDAO::doQuery()
{
    RcdDevice::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM iedinfo WHERE IEDCATEGORY='Prot' OR IEDCATEGORY='SR'");

        if(query.exec(sql))
        {
            while(query.next())
            {
                int GUID = query.value("GUID").toInt();
                QString iedName = query.value("IEDNAME").toString();
                QString netType = query.value("NETTYPE").toString();
                QString iedCateGory = query.value("IEDCATEGORY").toString();
                QString ip = "";
                if(netType == "A")
                {
                    ip = query.value("IPA").toString();
                }
                else if(netType == "B")
                {
                    ip = query.value("IPB").toString();
                }
                else
                {
                    ip = query.value("IPC").toString();
                }
                RcdDevice::Ptr ptr(new RcdDevice(GUID, iedName, ip, iedCateGory));
                lst.append(ptr);
            }
        }
        db.close();
    }

    return lst;
}

RcdDevice::List DBRcdDeviceDAO::doQuery(QSqlDatabase db)
{
    RcdDevice::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM iedinfo WHERE IEDCATEGORY='Prot' OR IEDCATEGORY='SR'");

    if(query.exec(sql))
    {
        while(query.next())
        {
            int GUID = query.value("GUID").toInt();
            QString iedName = query.value("IEDNAME").toString();
            QString netType = query.value("NETTYPE").toString();
            QString iedCateGory = query.value("IEDCATEGORY").toString();
            QString ip = "";
            if(netType == "A")
            {
                ip = query.value("IPA").toString();
            }
            else if(netType == "B")
            {
                ip = query.value("IPB").toString();
            }
            else
            {
                ip = query.value("IPC").toString();
            }
            RcdDevice::Ptr ptr(new RcdDevice(GUID, iedName, ip, iedCateGory));
            lst.append(ptr);
        }
    }

    return lst;
}

