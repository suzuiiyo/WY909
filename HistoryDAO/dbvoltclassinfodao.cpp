#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QSqlError>
#include "voltclassinfo.h"
#include "dbconnection.h"
#include "dbvoltclassinfodao.h"
#include "dbbayinfodao.h"
DBVoltClassInfoDAO::DBVoltClassInfoDAO()
    : m_connectionName("connectVoltClassInfo")
{
    doCreateTable();
}

DBVoltClassInfoDAO::~DBVoltClassInfoDAO()
{

}

VoltClassInfo::List DBVoltClassInfoDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    VoltClassInfo::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM voltclassinfo");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                VoltClassInfo::Ptr ptr(new VoltClassInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_voltClass = query.value("VOLTCLASS").toString();
                ptr->m_voltage = query.value("VOLTAGE").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

VoltClassInfo::List DBVoltClassInfoDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    VoltClassInfo::List lst;
    QString sql = QObject::tr("SELECT * FROM voltclassinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            VoltClassInfo::Ptr ptr(new VoltClassInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_voltClass = query.value("VOLTCLASS").toString();
            ptr->m_voltage = query.value("VOLTAGE").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

VoltClassInfo::Ptr DBVoltClassInfoDAO::doQuery(const QString &voltClass, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM voltclassinfo WHERE VOLTCLASS=\"%1\"")
                .arg(voltClass);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                VoltClassInfo::Ptr ptr(new VoltClassInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_voltClass = query.value("VOLTCLASS").toString();
                ptr->m_voltage = query.value("VOLTAGE").toString();
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

VoltClassInfo::Hash DBVoltClassInfoDAO::doQueryHash(bool *ok)
{
    bool bSucc = false;
    VoltClassInfo::Hash hsh;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM voltclassinfo");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                VoltClassInfo::Ptr ptr(new VoltClassInfo());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_voltClass = query.value("VOLTCLASS").toString();
                ptr->m_voltage = query.value("VOLTAGE").toString();
                hsh.insert(ptr->voltage(), ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

VoltClassInfo::Ptr DBVoltClassInfoDAO::doQuery(QSqlDatabase db, const QString &voltClass, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM voltclassinfo WHERE VOLTCLASS=\"%1\"")
            .arg(voltClass);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            VoltClassInfo::Ptr ptr(new VoltClassInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_voltClass = query.value("VOLTCLASS").toString();
            ptr->m_voltage = query.value("VOLTAGE").toString();
            //db.close();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

VoltClassInfo::Hash DBVoltClassInfoDAO::doQueryHash(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    VoltClassInfo::Hash hsh;
    QString sql = QObject::tr("SELECT * FROM voltclassinfo");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            VoltClassInfo::Ptr ptr(new VoltClassInfo());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_voltClass = query.value("VOLTCLASS").toString();
            ptr->m_voltage = query.value("VOLTAGE").toString();
            hsh.insert(ptr->voltage(), ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

bool DBVoltClassInfoDAO::doInsert(VoltClassInfo::List &lst)
{
    bool bSucc = false;
    VoltClassInfo::List::iterator iter = lst.begin();
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
                VoltClassInfo::Ptr ptr(new VoltClassInfo());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO voltclassinfo VALUES(NULL, \"%1\", \"%2\")")
                        .arg(ptr->voltClass())
                        .arg(ptr->voltage());
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
                VoltClassInfo::Ptr ptr(new VoltClassInfo());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO voltclassinfo VALUES(NULL, \"%1\", \"%2\")")
                        .arg(ptr->voltClass())
                        .arg(ptr->voltage());
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

bool DBVoltClassInfoDAO::doUpdate(const VoltClassInfo::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE voltclassinfo SET VOLTCLASS=\"%1\", VOLTAGE=\"%2\" WHERE GUID=%3")
                .arg(ptr->voltClass())
                .arg(ptr->voltage())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBVoltClassInfoDAO::doUpdate(VoltClassInfo::List &lst)
{
    bool bSucc = false;
    VoltClassInfo::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            VoltClassInfo::Ptr ptr(new VoltClassInfo());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE voltclassinfo SET VOLTCLASS=\"%1\", VOLTAGE=\"%2\" WHERE GUID=%3")
                    .arg(ptr->voltClass())
                    .arg(ptr->voltage())
                    .arg(ptr->GUID());
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

bool DBVoltClassInfoDAO::doDelete(const QString &voltClass)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM voltclassinfo WHERE VOLTCLASS=\"%1\"")
                .arg(voltClass);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBVoltClassInfoDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM voltclassinfo");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='voltclassinfo'");
        bSucc = query.exec(sql);
        db.close();
        DBBayInfoDAO dao;
        bSucc = dao.doClear();
    }
    return bSucc;
}

bool DBVoltClassInfoDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS voltclassinfo("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "VOLTCLASS CHAR(255) NOT NULL,"
                                  "VOLTAGE CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
