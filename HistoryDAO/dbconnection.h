#ifndef DBCONNECTION_H
#define DBCONNECTION_H

class QSqlDatabase;
class QString;
class DBConnection
{
public:
    static QSqlDatabase connection(const QString &connectionName, const QString &dbType, const QString &dbName);
    static void         releaseConnection();

protected:
    static QSqlDatabase createConnection(const QString &connectionName, const QString &dbType, const QString &dbName);
};
#endif // DBCONNECTION_H
