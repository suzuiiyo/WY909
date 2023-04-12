#include <QObject>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "dbdiagnosisofprotoperateconfigdao.h"
#include "dbconnection.h"
DBDiagnosisOfProtOperateConfigDAO::DBDiagnosisOfProtOperateConfigDAO()
    : m_connectionName("connectDOPC")
{

}

DBDiagnosisOfProtOperateConfigDAO::~DBDiagnosisOfProtOperateConfigDAO()
{

}

DiagnosisOfProtOperateConfig::List DBDiagnosisOfProtOperateConfigDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    DiagnosisOfProtOperateConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM diagnosisofprotoperateconfig");
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                DiagnosisOfProtOperateConfig::Ptr ptr(new DiagnosisOfProtOperateConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_opType = query.value("OPTYPE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_refIedName = query.value("REFIEDNAME").toString();
                ptr->m_refSource = query.value("REFSOURCE").toString();
                ptr->m_startTaskRef = query.value("STARTTASKREF").toString();
                ptr->m_groupOrder = query.value("GROUPORDER").toInt();
                ptr->m_itemOrder = query.value("ITEMORDER").toInt();
                ptr->m_appId = query.value("APPID").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_setType = query.value("SETTYPE").toString();
                ptr->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                ptr->m_eValue = query.value("EVALUE").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

DiagnosisOfProtOperateConfig::List DBDiagnosisOfProtOperateConfigDAO::doQuery(const QString &iedName, bool *ok)
{
    bool bSucc = false;
    DiagnosisOfProtOperateConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM diagnosisofprotoperateconfig WHERE IEDNAME=\"%1\"")
                .arg(iedName);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                DiagnosisOfProtOperateConfig::Ptr ptr(new DiagnosisOfProtOperateConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_opType = query.value("OPTYPE").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_refIedName = query.value("REFIEDNAME").toString();
                ptr->m_refSource = query.value("REFSOURCE").toString();
                ptr->m_startTaskRef = query.value("STARTTASKREF").toString();
                ptr->m_groupOrder = query.value("GROUPORDER").toInt();
                ptr->m_itemOrder = query.value("ITEMORDER").toInt();
                ptr->m_appId = query.value("APPID").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_setType = query.value("SETTYPE").toString();
                ptr->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                ptr->m_eValue = query.value("EVALUE").toString();
                ptr->m_standardValue = query.value("STANDARDVALUE").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

DiagnosisOfProtOperateConfig::List DBDiagnosisOfProtOperateConfigDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    DiagnosisOfProtOperateConfig::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM diagnosisofprotoperateconfig");
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            DiagnosisOfProtOperateConfig::Ptr ptr(new DiagnosisOfProtOperateConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_opType = query.value("OPTYPE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_refIedName = query.value("REFIEDNAME").toString();
            ptr->m_refSource = query.value("REFSOURCE").toString();
            ptr->m_startTaskRef = query.value("STARTTASKREF").toString();
            ptr->m_groupOrder = query.value("GROUPORDER").toInt();
            ptr->m_itemOrder = query.value("ITEMORDER").toInt();
            ptr->m_appId = query.value("APPID").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_setType = query.value("SETTYPE").toString();
            ptr->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            ptr->m_eValue = query.value("EVALUE").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

DiagnosisOfProtOperateConfig::List DBDiagnosisOfProtOperateConfigDAO::doQuery(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc = false;
    DiagnosisOfProtOperateConfig::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM diagnosisofprotoperateconfig WHERE IEDNAME=\"%1\"")
            .arg(iedName);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            DiagnosisOfProtOperateConfig::Ptr ptr(new DiagnosisOfProtOperateConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_opType = query.value("OPTYPE").toString();
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_refIedName = query.value("REFIEDNAME").toString();
            ptr->m_refSource = query.value("REFSOURCE").toString();
            ptr->m_startTaskRef = query.value("STARTTASKREF").toString();
            ptr->m_groupOrder = query.value("GROUPORDER").toInt();
            ptr->m_itemOrder = query.value("ITEMORDER").toInt();
            ptr->m_appId = query.value("APPID").toString();
            ptr->m_dataDesc = query.value("DATADESC").toString();
            ptr->m_setType = query.value("SETTYPE").toString();
            ptr->m_iedNameComp = query.value("IEDNAMECOMP").toString();
            ptr->m_eValue = query.value("EVALUE").toString();
            ptr->m_standardValue = query.value("STANDARDVALUE").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

bool DBDiagnosisOfProtOperateConfigDAO::doInsert(DiagnosisOfProtOperateConfig::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;

    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        DiagnosisOfProtOperateConfig::List::iterator iter;
        QSqlQuery query(db);
        query.exec("begin transaction");
        QString sql = "";

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            DiagnosisOfProtOperateConfig::Ptr ptr(new DiagnosisOfProtOperateConfig());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO diagnosisofprotoperateconfig VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", %7, %8, \"%9\", \"%10\", \"%11\", \"%12\", \"%13\", \"%14\")")
                    .arg(ptr->iedName())//1
                    .arg(ptr->opType())//2
                    .arg(ptr->dataRef())//3
                    .arg(ptr->refIedName())//4
                    .arg(ptr->refSource())//5
                    .arg(ptr->startTaskRef())//6
                    .arg(ptr->groupOrder())//7
                    .arg(ptr->itemOrder())//8
                    .arg(ptr->appId())//9
                    .arg(ptr->dataDesc())//10
                    .arg(ptr->setType())//11
                    .arg(ptr->iedNameComp())//12
                    .arg(ptr->eValue())//13
                    .arg(ptr->standardValue());//14
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

bool DBDiagnosisOfProtOperateConfigDAO::doUpdate(DiagnosisOfProtOperateConfig::List &lst)
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
        DiagnosisOfProtOperateConfig::List::iterator iter;
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            DiagnosisOfProtOperateConfig::Ptr ptr(new DiagnosisOfProtOperateConfig());
            ptr = *iter;
            sql = QObject::tr("UPDATE diagnosisofprotoperateconfig SET IEDNAME=\"%1\", OPTYPE=\"%2\", DATAREF=\"%3\", REFIEDNAME=\"%4\", REFSOURCE=\"%5\", STARTTASKREF=\"%6\", GROUPORDER=\"%7\", ITEMORDER=\"%8\", APPID=\"%9\", DATADESC=\"%10\", SETTYPE=\"%11\", IEDNAMECOMP=\"%12\", EVALUE=\"%13\", STANDARDVALUE=\"%14\" WHERE GUID=%15")
                    .arg(ptr->iedName())//1
                    .arg(ptr->opType())//2
                    .arg(ptr->dataRef())//3
                    .arg(ptr->refIedName())//4
                    .arg(ptr->refSource())//5
                    .arg(ptr->startTaskRef())//6
                    .arg(ptr->groupOrder())//7
                    .arg(ptr->itemOrder())//8
                    .arg(ptr->appId())//9
                    .arg(ptr->dataDesc())//10
                    .arg(ptr->setType())//11
                    .arg(ptr->iedNameComp())//12
                    .arg(ptr->eValue())//13
                    .arg(ptr->standardValue())//14
                    .arg(ptr->GUID());//15
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

bool DBDiagnosisOfProtOperateConfigDAO::doDelete(DiagnosisOfProtOperateConfig::List &lst)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        DiagnosisOfProtOperateConfig::List::iterator iter;
        QSqlQuery query(db);
        QString sql = "";
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            DiagnosisOfProtOperateConfig::Ptr ptr(new DiagnosisOfProtOperateConfig());
            ptr = *iter;
            sql = QObject::tr("DELETE * FROM diagnosisofprotoperateconfig WHERE GUID=%1")
                                .arg(ptr->GUID());
            bSucc = query.exec(sql);
        }
        db.close();
    }

    return bSucc;
}

bool DBDiagnosisOfProtOperateConfigDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM diagnosisofprotoperateconfig");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='diagnosisofprotoperateconfig'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBDiagnosisOfProtOperateConfigDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS dastruct("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "IEDNAME CHAR(255) NOT NULL,"
                                  "OPTYPE CHAR(255) NOT NULL,"
                                  "DATAREF CHAR(255) NOT NULL,"
                                  "REFIEDNAME CHAR(255) NOT NULL,"
                                  "REFSOURCE CHAR(255) NOT NULL,"
                                  "STARTTASKREF CHAR(255) NOT NULL,"
                                  "GROUPORDER INTEGER NOT NULL,"
                                  "ITEMORDER INTEGER NOT NULL,"
                                  "APPID CHAR(255) NOT NULL,"
                                  "DATADESC CHAR(255) NOT NULL,"
                                  "SETTYPE CHAR(255) NOT NULL,"
                                  "IEDNAMECOMP CHAR(255) NOT NULL,"
                                  "EVALUE CHAR(255) NOT NULL,"
                                  "STANDARDVALUE CHAR(255) NOT NULL");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

