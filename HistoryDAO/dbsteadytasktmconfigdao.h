#ifndef DBSTEADYTASKTMCONFIGDAO_H
#define DBSTEADYTASKTMCONFIGDAO_H
#include <QString>
#include <QSqlDatabase>
#include "steadytasktmconfig.h"
class DBSteadyTaskTMConfigDAO
{
public:
    DBSteadyTaskTMConfigDAO();
    ~DBSteadyTaskTMConfigDAO();
public:
    SteadyTaskTMConfig::List doQuery(bool *ok=0);
    SteadyTaskTMConfig::List doQuery(const QString &iedName, bool *ok=0);
    SteadyTaskTMConfig::List doQuery(const QString &iedName, const QString &itemName, bool *ok=0);
    SteadyTaskTMConfig::List doQuery(const QString &iedName, const QString &itemName, const QString &itemType, bool *ok=0);
public:
    SteadyTaskTMConfig::List doQuery(QSqlDatabase db, bool *ok=0);
    SteadyTaskTMConfig::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    SteadyTaskTMConfig::List doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, bool *ok=0);
    SteadyTaskTMConfig::List doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, const QString &itemType, bool *ok=0);
public:
    bool doInsert(SteadyTaskTMConfig::List &lst);
public:
    bool doUpdate(const SteadyTaskTMConfig::Ptr &ptr);
    bool doUpdate(SteadyTaskTMConfig::List &lst);
public:
    bool doDelete(SteadyTaskTMConfig::List &lst);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBSTEADYTASKTMCONFIGDAO_H
