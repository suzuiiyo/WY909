#ifndef DBCONNECTIONSTATEDAO_H
#define DBCONNECTIONSTATEDAO_H
#include <QString>
#include <QSqlDatabase>
#include "connectionstate.h"
class DBConnectionStateDAO
{
public:
    DBConnectionStateDAO();
    ~DBConnectionStateDAO();
public:
    ConnectionState::List doQuery(bool *ok=0);
    ConnectionState::Hash doQueryHash(bool *ok=0);
    ConnectionState::Hash doQueryHash(QSqlDatabase db, bool *ok=0);
    ConnectionState::Ptr doQuery(const QString &iedName, bool *ok=0);
public:
    bool doClear();
    bool doClear(QSqlDatabase db);
public:
    bool doUpdate(const ConnectionState::Ptr &ptr);
    bool doUpdate(QSqlDatabase db, const ConnectionState::Ptr &ptr);
public:
    bool doInsert(ConnectionState::List &lst);
    bool doInsert(QSqlDatabase db, ConnectionState::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBCONNECTIONSTATEDAO_H
