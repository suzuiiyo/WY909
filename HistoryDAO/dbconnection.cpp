#include <QString>
#include <QObject>
#include <QSqlDatabase>
#include <QStringList>
#include <QDir>
#include "dbconnection.h"
#include "readconfig.h"

QSqlDatabase DBConnection::connection(const QString &connectionName, const QString &dbType, const QString &dbName)
{
    if(QSqlDatabase::contains(connectionName))
    {
        return QSqlDatabase::database(connectionName);
    }
    return createConnection(connectionName, dbType, dbName);
}

void DBConnection::releaseConnection()
{
    foreach(QString connectionName, QSqlDatabase::connectionNames())
    {
        QSqlDatabase::removeDatabase(connectionName);
    }
}

QSqlDatabase DBConnection::createConnection(const QString &connectionName, const QString &dbType, const QString &dbName)
{
    //db.setDatabaseName("/home/gdwy/sysconfigdb/SysConfig.db");
    QSqlDatabase db = QSqlDatabase::addDatabase(dbType, connectionName);
    //db.setDatabaseName("./config/db/SysConfig.db");
    ReadConfig readConfig;
    QString dbPath = readConfig.getConfigPath();
    db.setDatabaseName(dbPath);
    return db;
}
