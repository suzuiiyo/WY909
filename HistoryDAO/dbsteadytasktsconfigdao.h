#ifndef DBSTEADYTASKTSCONFIGDAO_H
#define DBSTEADYTASKTSCONFIGDAO_H
#include <QString>
#include <QSqlDatabase>
#include "steadytasktsconfig.h"
class DBSteadyTaskTSConfigDAO
{
public:
    DBSteadyTaskTSConfigDAO();
    ~DBSteadyTaskTSConfigDAO();
public:
    SteadyTaskTSConfig::List doQuery(bool *ok=0);
    SteadyTaskTSConfig::List doQuery(const QString &iedName, bool *ok=0);
    SteadyTaskTSConfig::List doQuery(const QString &iedName, const QString &itemName, bool *ok=0);
    SteadyTaskTSConfig::List doQuery(const QString &iedName, const QString &itemName, const QString &itemType, bool *ok=0);
public:
    SteadyTaskTSConfig::List doQuery(QSqlDatabase db, bool *ok=0);
    SteadyTaskTSConfig::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    SteadyTaskTSConfig::List doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, bool *ok=0);
    SteadyTaskTSConfig::List doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, const QString &itemType, bool *ok=0);
public:
    bool doInsert(SteadyTaskTSConfig::List &lst);
public:
    bool doUpdate(const SteadyTaskTSConfig::Ptr &ptr);
    bool doUpdate(SteadyTaskTSConfig::List &lst);
public:
    bool doDelete(SteadyTaskTSConfig::List &lst);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBSTEADYTASKTSCONFIGDAO_H
