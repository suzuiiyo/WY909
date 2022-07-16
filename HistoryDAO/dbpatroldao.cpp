#include <QSqlQuery>
#include <QObject>
#include <QString>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include "dbconnection.h"
#include "dbpatroldao.h"
DBPatrolDAO::DBPatrolDAO()
    : m_connectionName("connectPatrol")
{

}

DBPatrolDAO::~DBPatrolDAO()
{

}

Patrol::List DBPatrolDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM patrol");
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                Patrol::Ptr ptr(new Patrol());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_dataDetail = query.value("DATADETAIL").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_purpose = query.value("PURPOSE").toString();
                ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
                ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
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

Patrol::List DBPatrolDAO::doQueryByIedName(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM patrol WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Patrol::Ptr ptr(new Patrol());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_dataDetail = query.value("DATADETAIL").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_purpose = query.value("PURPOSE").toString();
                ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
                ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
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

Patrol::List DBPatrolDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM patrol WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Patrol::Ptr ptr(new Patrol());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_dataDetail = query.value("DATADETAIL").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_purpose = query.value("PURPOSE").toString();
                ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
                ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
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

Patrol::List DBPatrolDAO::doQueryByDataType(const QString &dataType, bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM patrol WHERE DATATYPE=\"%1\"")
                .arg(dataType);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Patrol::Ptr ptr(new Patrol());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_dataDetail = query.value("DATADETAIL").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_purpose = query.value("PURPOSE").toString();
                ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
                ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
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

Patrol::List DBPatrolDAO::doQuery(const QString &iedName, const QString &dataType, bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM patrol WHERE IEDNAME=\"%1\" DATATYPE=\"%2\"")
                .arg(iedName)
                .arg(dataType);
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                Patrol::Ptr ptr(new Patrol());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                ptr->m_dataDetail = query.value("DATADETAIL").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                ptr->m_purpose = query.value("PURPOSE").toString();
                ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
                ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
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

Patrol::List DBPatrolDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QString sql = QObject::tr("SELECT * FROM patrol");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Patrol::Ptr ptr(new Patrol());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_dataDetail = query.value("DATADETAIL").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_purpose = query.value("PURPOSE").toString();
            ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
            ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
            ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Patrol::List DBPatrolDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QString sql = QObject::tr("SELECT * FROM patrol WHERE IEDNAME=\"%1\"")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Patrol::Ptr ptr(new Patrol());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_dataDetail = query.value("DATADETAIL").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_purpose = query.value("PURPOSE").toString();
            ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
            ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
            ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Patrol::List DBPatrolDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QString sql = QObject::tr("SELECT * FROM patrol WHERE DATAREF=\"%1\"")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Patrol::Ptr ptr(new Patrol());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_dataDetail = query.value("DATADETAIL").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_purpose = query.value("PURPOSE").toString();
            ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
            ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
            ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Patrol::List DBPatrolDAO::doQueryByDataType(QSqlDatabase db, const QString &dataType, bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QString sql = QObject::tr("SELECT * FROM patrol WHERE DATATYPE=\"%1\"")
            .arg(dataType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Patrol::Ptr ptr(new Patrol());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_dataDetail = query.value("DATADETAIL").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_purpose = query.value("PURPOSE").toString();
            ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
            ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
            ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

Patrol::List DBPatrolDAO::doQuery(QSqlDatabase db, const QString &iedName, const QString &dataType, bool *ok)
{
    bool bSucc = false;
    Patrol::List lst;
    QString sql = QObject::tr("SELECT * FROM patrol WHERE IEDNAME=\"%1\" DATATYPE=\"%2\"")
            .arg(iedName)
            .arg(dataType);
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            Patrol::Ptr ptr(new Patrol());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            ptr->m_dataDetail = query.value("DATADETAIL").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_standardValueType = query.value("STANDARDVALUETYPE").toInt();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            ptr->m_purpose = query.value("PURPOSE").toString();
            ptr->m_configDataType = query.value("CONFIGDATATYPE").toInt();
            ptr->m_configDataDetail = query.value("CONFIGDATADETAIL").toInt();
            ptr->m_unicodeDesc = query.value("UNICODEDESC").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBPatrolDAO::doInsert(Patrol::List &lst)
{
    bool bSucc = false;
    Patrol::List::iterator iter = lst.begin();
    int list_size = lst.size();
    if(list_size == 0)
        return true;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        query.exec("begin transaction");

        if(list_size <= 200)
        {
            while(iter < lst.end())
            {
                Patrol::Ptr ptr(new Patrol());
                ptr = *iter;

                sql = QObject::tr("REPLACE INTO patrol VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", %6, \"%7\", \"%8\", %9, %10, \"%11\")")
                        .arg(ptr->dataRef())//1
                        .arg(ptr->dataDesc())//2
                        .arg(ptr->dataType())//3
                        .arg(ptr->dataDetail())//4
                        .arg(ptr->iedName())//5
                        .arg(ptr->standardValueType())//6
                        .arg(ptr->standardValue())//7
                        .arg(ptr->purpose())//8
                        .arg(ptr->configDataType())//9
                        .arg(ptr->configDataDetail())//10
                        .arg(ptr->unicodeDesc());//11
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
                Patrol::Ptr ptr(new Patrol());
                ptr = *iter;

                sql = QObject::tr("REPLACE INTO patrol VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", %6, \"%7\", \"%8\", %9, %10, \"%11\")")
                        .arg(ptr->dataRef())//1
                        .arg(ptr->dataDesc())//2
                        .arg(ptr->dataType())//3
                        .arg(ptr->dataDetail())//4
                        .arg(ptr->iedName())//5
                        .arg(ptr->standardValueType())//6
                        .arg(ptr->standardValue())//7
                        .arg(ptr->purpose())//8
                        .arg(ptr->configDataType())//9
                        .arg(ptr->configDataDetail())//10
                        .arg(ptr->unicodeDesc());//11
                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: %s", error_s.toStdString().data());
                    db.close();
                    return bSucc;
                }
                count++;
                if(count == 200)
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

bool DBPatrolDAO::doUpdate(const Patrol::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE patrol SET DATAREF=\"%1\", DATADESC=\"%2\", DATATYPE=\"%3\", DATADETAIL=\"%4\", IEDNAME=\"%5\", STANDARDVALUETYPE=%6, STANDARDVALUE=\"%7\", PURPOSE=\"%8\", CONFIGDATATYPE=%9, CONFIGDATADETAIL=%10, UNICODEDESC=\"%11\" WHERE GUID=%12")
                .arg(ptr->dataRef())//1
                .arg(ptr->dataDesc())//2
                .arg(ptr->dataType())//3
                .arg(ptr->dataDetail())//4
                .arg(ptr->iedName())//5
                .arg(ptr->standardValueType())//6
                .arg(ptr->standardValue())//7
                .arg(ptr->purpose())//8
                .arg(ptr->configDataType())//9
                .arg(ptr->configDataDetail())//10
                .arg(ptr->unicodeDesc())//11
                .arg(ptr->GUID());//12
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBPatrolDAO::doUpdate(Patrol::List &lst)
{
    bool bSucc = false;
    Patrol::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            Patrol::Ptr ptr(new Patrol());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE patrol SET DATAREF=\"%1\", DATADESC=\"%2\", DATATYPE=\"%3\", DATADETAIL=\"%4\", IEDNAME=\"%5\", STANDARDVALUETYPE=%6, STANDARDVALUE=\"%7\", PURPOSE=\"%8\", CONFIGDATATYPE=%9, CONFIGDATADETAIL=%10, UNICODEDESC=\"%11\" WHERE GUID=%12")
                    .arg(ptr->dataRef())//1
                    .arg(ptr->dataDesc())//2
                    .arg(ptr->dataType())//3
                    .arg(ptr->dataDetail())//4
                    .arg(ptr->iedName())//5
                    .arg(ptr->standardValueType())//6
                    .arg(ptr->standardValue())//7
                    .arg(ptr->purpose())//8
                    .arg(ptr->configDataType())//9
                    .arg(ptr->configDataDetail())//10
                    .arg(ptr->unicodeDesc())//11
                    .arg(ptr->GUID());//12
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

bool DBPatrolDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE * FROM patrol WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBPatrolDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE * FROM patrol WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBPatrolDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM patrol");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='patrol'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBPatrolDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS patrol("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) NOT NULL,"
                                  "DATADESC CHAR(255) NOT NULL,"
                                  "DATATYPE CHAR(255) NOT NULL,"
                                  "DATADETAIL FLOAT(8,3) NOT NULL,"
                                  "IEDNAME CHAR(255) NOT NULL,"
                                  "STANDARDVALUETYPE INTEGER NOT NULL,"
                                  "STANDARDVALUE CHAR(255) NOT NULL,"
                                  "PURPOSE CHAR(255) NOT NULL,"
                                  "CONFIGDATATYPE CHAR(255) NOT NULL,"
                                  "CONFIGDATADETAIL CHAR(255) NOT NULL,"
                                  "UNICODEDESC CHAR(255) NOT NULL");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
