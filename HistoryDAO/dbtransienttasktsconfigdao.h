#ifndef DBTRANSIENTTASKTSCONFIGDAO_H
#define DBTRANSIENTTASKTSCONFIGDAO_H
#include <QString>
#include <QSqlDatabase>
#include "transienttasktsconfig.h"
class DBTransientTaskTSConfigDAO
{
public:
    DBTransientTaskTSConfigDAO();
    ~DBTransientTaskTSConfigDAO();
public:
    TransientTaskTSConfig::List doQuery(bool *ok=0);
    TransientTaskTSConfig::List doQuery(const QString &iedName, bool *ok=0);
    TransientTaskTSConfig::List doQuery(const QString &iedName, const QString &itemName, bool *ok=0);
    TransientTaskTSConfig::List doQuery(const QString &iedName, const QString &itemName, const QString &itemType, bool *ok=0);
public:
    TransientTaskTSConfig::List doQuery(QSqlDatabase db, bool *ok=0);
    TransientTaskTSConfig::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    TransientTaskTSConfig::List doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, bool *ok=0);
    TransientTaskTSConfig::List doQuery(QSqlDatabase db, const QString &iedName, const QString &itemName, const QString &itemType, bool *ok=0);
public:
    bool doInsert(TransientTaskTSConfig::List &lst);
public:
    bool doUpdate(const TransientTaskTSConfig::Ptr &ptr);
    bool doUpdate(TransientTaskTSConfig::List &lst);
public:
    bool doDelete(TransientTaskTSConfig::List &lst);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBTRANSIENTTASKTSCONFIGDAO_H
