#ifndef DBAPPIDDAO_H
#define DBAPPIDDAO_H
#include <QString>
#include "appid.h"
class DBAppIdDAO
{
public:
    DBAppIdDAO();
    ~DBAppIdDAO();
public:
    AppId::List doQuery();
    AppId::List doQuery(const QString &iedName);
    AppId::Hash doQueryHash();
public:
    bool doInsert(AppId::List &lst);
public:
    bool doUpdate(const AppId::Ptr &ptr);
    bool doUpdate(AppId::List &lst);
public:
    bool doDelete(const QString &appId);
public:
    bool doClear();
private:
    QString m_connectionName;
};
#endif // DBAPPIDDAO_H
