#ifndef DBCONNECTIONREAL_H
#define DBCONNECTIONREAL_H
class QSqlDatabase;
class QString;
class DBConnectionReal
{
public:
    static QSqlDatabase connection(const QString &connectionName, const QString &dbType, const QString &dbName);
    static void         releaseConnection();
protected:
    static QSqlDatabase createConnection(const QString &connectionName, const QString &dbType, const QString &dbName);
    //static QSqlDatabase * createConnectionP(const QString &connectionName, const QString &dbType, const QString &dbName);
};
#endif // DBCONNECTIONREAL_H
