#ifndef DBTRANSIENTTASKTMCONFIGDAO_H
#define DBTRANSIENTTASKTMCONFIGDAO_H
#include <QString>
#include <QSqlDatabase>
#include "transienttasktmconfig.h"
class DBTransientTaskTMConfigDAO
{
public:
    DBTransientTaskTMConfigDAO();
    ~DBTransientTaskTMConfigDAO();
public:
    TransientTaskTMConfig::List doQuery(bool *ok=0);
    TransientTaskTMConfig::List doQuery(const QString &iedName, bool *ok=0);
    TransientTaskTMConfig::List doQuery(const QString &iedName, const QString &itemName, bool *ok=0);
    TransientTaskTMConfig::List doQuery(const QString &iedName, const QString &itemName, const QString &itemType, bool *ok=0);
public:
    TransientTaskTMConfig::List doQuery(QSqlDatabase db, bool *ok=0);
    TransientTaskTMConfig::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    TransientTaskTMConfig::List doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, bool *ok=0);
    TransientTaskTMConfig::List doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, const QString &itemType, bool *ok=0);
public:
    bool doInsert(TransientTaskTMConfig::List &lst);
public:
    bool doUpdate(const TransientTaskTMConfig::Ptr &ptr);
    bool doUpdate(TransientTaskTMConfig::List &lst);
public:
    bool doDelete(TransientTaskTMConfig::List &lst);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBTRANSIENTTASKTMCONFIGDAO_H
