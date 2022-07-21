#ifndef DBEARLYWARNINGCONFIGDAO_H
#define DBEARLYWARNINGCONFIGDAO_H
#include <QString>
#include <QSqlDatabase>
#include "earlywarningconfig.h"
class DBEarlyWarningConfigDAO
{
public:
    DBEarlyWarningConfigDAO();
    ~DBEarlyWarningConfigDAO();
public:
    EarlyWarningConfig::List doQuery(bool *ok=0);
    EarlyWarningConfig::List doQuery(const QString &iedName, bool *ok=0);
    EarlyWarningConfig::List doQuery(const QString &iedName, int ewType, bool *ok=0);
    EarlyWarningConfig::Hash doQueryHash(bool *ok=0);
    EarlyWarningConfig::Hash doQueryHash(const QString &iedName, int ewType, bool *ok=0);
    EarlyWarningConfig::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
public:
    EarlyWarningConfig::List doQuery(QSqlDatabase db, bool *ok=0);
    EarlyWarningConfig::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    EarlyWarningConfig::List doQuery(QSqlDatabase db, const QString &iedName, int ewType, bool *ok=0);
    EarlyWarningConfig::Hash doQueryHash(QSqlDatabase db, bool *ok=0);
    EarlyWarningConfig::Hash doQueryHash(QSqlDatabase db, const QString &iedName, int ewType, bool *ok=0);
    EarlyWarningConfig::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
public:
    bool doInsert(EarlyWarningConfig::List &lst);
public:
    bool doUpdate(const EarlyWarningConfig::Ptr &ptr);
    bool doUpdate(EarlyWarningConfig::List &lst);
    bool doUpdateSP(EarlyWarningConfig::List &lst);
    bool updateEnable(EarlyWarningConfig::List &lst);
public:
    bool doDelete(const QString &dataRef);
    bool doDelete(EarlyWarningConfig::List &lst);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBEARLYWARNINGCONFIGDAO_H
