#include <QString>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "dbconnection.h"
#include "dboption.h"
DBOption::DBOption()
    : m_connectionName("ConnectDBOption")
{

}

DBOption::~DBOption()
{

}

bool DBOption::openFastInsertPattern()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QMYSQL", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("ALTER TABLE iedinfo DROP PRIMARY KEY");
        bSucc = query.exec(sql);
        if(bSucc == false)
        {
            return bSucc;
        }
        sql = QObject::tr("ALTER TABLE ieddataset DROP PRIMARY KEY");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBOption::closeFastInsertPattern()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QMYSQL", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("ALTER TABLE iedinfo ADD PRIMARY KEY(IEDNAME)");
        bSucc = query.exec(sql);
        if(bSucc == false)
        {
            return bSucc;
        }
        sql = QObject::tr("ALTER TABLE ieddataset ADD PRIMARY KEY(DATAREF)");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}
