#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "dastruct.h"
#include "dbconnection.h"
#include "dbdastructdao.h"
DBDAStructDAO::DBDAStructDAO()
    : m_connectionName("connectDAStruct")
{
    doCreateTable();
}

DBDAStructDAO::~DBDAStructDAO()
{

}

DAStruct::List DBDAStructDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    DAStruct::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM dastruct");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                DAStruct::Ptr ptr(new DAStruct());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

DAStruct::List DBDAStructDAO::doQueryByIedName(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    DAStruct::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DATATYPE, a.ATTRIBUTEREF FROM dastruct a, ieddataset b WHERE b.IEDNAME=\"%1\" AND b.DATAREF=a.DATAREF")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                DAStruct::Ptr ptr(new DAStruct());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

DAStruct::List DBDAStructDAO::doQueryByDataRef(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    DAStruct::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM dastruct WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                DAStruct::Ptr ptr(new DAStruct());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

DAStruct::Ptr DBDAStructDAO::doQueryByAttributeRef(const QString &attributeRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM dastruct WHERE ATTRIBUTEREF=\"%1\"")
                .arg(attributeRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                DAStruct::Ptr ptr(new DAStruct());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
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

QVector<DAStruct *> DBDAStructDAO::doQueryVec(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QVector<DAStruct *> vec;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM dastruct WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        QSqlQuery query(db);
        bSucc = query.exec(sql);
        if(bSucc)
        {
            while(query.next())
            {
                DAStruct *ptr = new DAStruct();
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
                vec.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return vec;
}

QHash<QString, DAStruct::List> DBDAStructDAO::doQueryHash(const QStringList &lst, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    QHash<QString, DAStruct::List> hsh;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        for(int i=0; i<lst.size(); i++)
        {
            QString sql = QObject::tr("SELECT * FROM dastruct WHERE DATAREF=\"%1\"")
                    .arg(lst.at(i));
            bSucc1 = query.exec(sql);
            if(!bSucc1)
                bSucc2 = bSucc1;
            if(bSucc1)
            {
                while(query.next())
                {
                    DAStruct::Ptr ptr(new DAStruct());
                    ptr->m_GUID = query.value("GUID").toInt();
                    ptr->m_dataRef = query.value("DATAREF").toString();
                    ptr->m_dataType = query.value("DATATYPE").toInt();
                    ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
                    if(hsh.count(ptr->dataRef()) == 0)
                    {
                        DAStruct::List lstTmp;
                        hsh.insert(ptr->dataRef(), lstTmp);
                    }
                    hsh[ptr->dataRef()].append(ptr);
                }
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc2;

    return hsh;
}

DAStruct::List DBDAStructDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    DAStruct::List lst;
    QString sql = QObject::tr("SELECT * FROM dastruct");
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            DAStruct::Ptr ptr(new DAStruct());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

DAStruct::List DBDAStructDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    DAStruct::List lst;
    QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DATATYPE, a.ATTRIBUTEREF FROM dastruct a, ieddataset b WHERE b.IEDNAME=\"%1\" AND b.DATAREF=a.DATAREF")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            DAStruct::Ptr ptr(new DAStruct());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

DAStruct::List DBDAStructDAO::doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    DAStruct::List lst;
    QString sql = QObject::tr("SELECT * FROM dastruct WHERE DATAREF=\"%1\"")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            DAStruct::Ptr ptr(new DAStruct());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

DAStruct::Ptr DBDAStructDAO::doQueryByAttributeRef(QSqlDatabase db, const QString &attributeRef, bool *ok)
{
    bool bSucc = false;
    QString sql = QObject::tr("SELECT * FROM dastruct WHERE ATTRIBUTEREF=\"%1\"")
            .arg(attributeRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            DAStruct::Ptr ptr(new DAStruct());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
            if(ok)
                *ok = bSucc;
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

QVector<DAStruct *> DBDAStructDAO::doQueryVec(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QVector<DAStruct *> vec;
    QString sql = QObject::tr("SELECT * FROM dastruct WHERE DATAREF=\"%1\"")
            .arg(dataRef);
    QSqlQuery query(db);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            DAStruct *ptr = new DAStruct();
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_dataType = query.value("DATATYPE").toInt();
            ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
            vec.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return vec;
}

QHash<QString, DAStruct::List> DBDAStructDAO::doQueryHash(QSqlDatabase db, const QStringList &lst, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    QHash<QString, DAStruct::List> hsh;
    QSqlQuery query(db);
    for(int i=0; i<lst.size(); i++)
    {
        QString sql = QObject::tr("SELECT * FROM dastruct WHERE DATAREF=\"%1\"")
                .arg(lst.at(i));
        bSucc1 = query.exec(sql);
        if(!bSucc1)
            bSucc2 = bSucc1;
        if(bSucc1)
        {
            while(query.next())
            {
                DAStruct::Ptr ptr(new DAStruct());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataType = query.value("DATATYPE").toInt();
                ptr->m_attributeRef = query.value("ATTRIBUTEREF").toString();
                if(hsh.count(ptr->dataRef()) == 0)
                {
                    DAStruct::List lstTmp;
                    hsh.insert(ptr->dataRef(), lstTmp);
                }
                hsh[ptr->dataRef()].append(ptr);
            }
        }
    }
    if(ok)
        *ok = bSucc2;

    return hsh;
}

bool DBDAStructDAO::doInsert(DAStruct::List &lst)
{
    bool bSucc = false;
    DAStruct::List::iterator iter = lst.begin();
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
                DAStruct::Ptr ptr(new DAStruct());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO dastruct VALUES (NULL, \"%1\", \"%2\", \"%3\")")
                        .arg(ptr->dataRef())
                        .arg(ptr->attributeRef())
                        .arg(ptr->dataType());
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
                DAStruct::Ptr ptr(new DAStruct());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO dastruct VALUES (NULL, \"%1\", \"%2\", \"%3\")")
                        .arg(ptr->dataRef())
                        .arg(ptr->attributeRef())
                        .arg(ptr->dataType());
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

bool DBDAStructDAO::doUpdate(const DAStruct::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE dastruct SET DATAREF=\"%1\", ATTRIBUTEREF=\"%2\", DATATYPE=\"%3\" WHERE GUID=%4")
                .arg(ptr->dataRef())
                .arg(ptr->attributeRef())
                .arg(ptr->dataType())
                .arg(ptr->GUID());
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBDAStructDAO::doUpdate(DAStruct::List &lst)
{
    bool bSucc = false;
    DAStruct::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        while(iter < lst.end())
        {
            DAStruct::Ptr ptr(new DAStruct());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE dastruct SET DATAREF=\"%1\", ATTRIBUTEREF=\"%2\", DATATYPE=\"%3\" WHERE GUID=%4")
                    .arg(ptr->dataRef())
                    .arg(ptr->attributeRef())
                    .arg(ptr->dataType())
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

bool DBDAStructDAO::doDeleteByIedName(const QString &iedName)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE a FROM dastruct a, ieddataset b WHERE b.IEDNAME=\"%1\" AND a.DATAREF=b.DATAREF")
                .arg(iedName);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBDAStructDAO::doDeleteByDataRef(const QString &dataRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE * FROM dastruct WHERE DATAREF=\"%1\"")
                .arg(dataRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBDAStructDAO::doDeleteByDataAttributeRef(const QString &dataAttributeRef)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE * FROM dastruct WHERE ATTRIBUTEREF=\"%1\"")
                .arg(dataAttributeRef);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBDAStructDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM dastruct");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='dastruct'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBDAStructDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS dastruct("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "DATAREF CHAR(255) NOT NULL,"
                                  "ATTRIBUTEREF CHAR(255) NOT NULL,"
                                  "DATATYPE CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
