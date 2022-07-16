#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include "ied.h"
#include "dbiedinfodao.h"
#include "dbconnection.h"
#include "dbiedconfighistorydao.h"
DBIedConfigHistoryDAO::DBIedConfigHistoryDAO()
    : m_connectionName("connectIedConfigHistory")
{

}

DBIedConfigHistoryDAO::~DBIedConfigHistoryDAO()
{

}

bool DBIedConfigHistoryDAO::syn()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        DBIedInfoDAO dao;
        QString configIed = dao.getAllIed();
        QDateTime currentTime = QDateTime::currentDateTime();
        QString timeTmp = currentTime.toString("yyyy-MM-dd HH:mm:ss.zzz");

        QSqlQuery query(db);
        QString sql = QObject::tr("INSERT INTO iedconfighistory VALUES(NULL, \"%1\", \"%2\")")
                .arg(configIed)//1
                .arg(timeTmp);//2
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
