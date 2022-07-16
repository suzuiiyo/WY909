#include <QString>
#include <QSqlDatabase>
#include <QStringList>
#include "dbconnectionreal.h"
#include "parseconfig.h"
#include "dbconfig.h"
QSqlDatabase DBConnectionReal::connection(const QString &connectionName, const QString &dbType, const QString &dbName)
{
    if(QSqlDatabase::contains(connectionName))
    {
        return QSqlDatabase::database(connectionName);
    }
    return createConnection(connectionName, dbType, dbName);
}

void DBConnectionReal::releaseConnection(){
    foreach (QString connectionName, QSqlDatabase::connectionNames())
    {
        QSqlDatabase::removeDatabase(connectionName);
    }
}

QSqlDatabase DBConnectionReal::createConnection(const QString &connectionName, const QString &dbType, const QString &dbName)
{

    QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase(dbType, connectionName);
    if(dbType == "QMYSQL")
    {
        ParseConfig parseConfig;
        DBConfig::Ptr config = parseConfig.getConfigPath(0);
        if(dbName != "")
        {
            db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
            db.setDatabaseName(dbName);
        }

        if(config)
        {
            db.setHostName(config->hostName());
            db.setPort(config->port());
            db.setUserName(config->userName());
            db.setPassword(config->password());
        }
    }

    if(dbType == "QSQLITE")
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(dbType, connectionName);
        db.setDatabaseName("./config/db/SysConfig.db");
    }

    return db;
}

//QSqlDatabase * DBConnectionReal::createConnectionP(const QString &connectionName, const QString &dbType, const QString &dbName)
//{
//    if(dbType == "QMYSQL"){
//        QSqlDatabase::drivers();
//        QSqlDatabase *db = new QSqlDatabase::addDatabase(dbType, connectionName);
//        db->setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
//        db->setHostName("192.168.16.250");
//        db->setPort(3306);
//        db->setDatabaseName(dbName);
//        db->setUserName("root");
//        db->setPassword("mysql@2021");
//        return db;
//    }else{
//        QSqlDatabase *db = new QSqlDatabase::addDatabase(dbType, connectionName);
//        db->setDatabaseName("/home/gdwy/sysconfigdb/SysConfig.db");
//        return db;
//    }
//}
