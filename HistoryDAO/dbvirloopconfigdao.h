#ifndef DBVIRLOOPCONFIGDAO_H
#define DBVIRLOOPCONFIGDAO_H
#include <QSqlDatabase>
#include <QString>
#include <QHash>
#include <QList>
#include "virloopconfig.h"
#include "virloopiedinfo.h"
class DBVirLoopConfigDAO
{
public:
    DBVirLoopConfigDAO();
    ~DBVirLoopConfigDAO();
public:
    VirLoopConfig::List doQuery(bool *ok=0);
    VirLoopConfig::List doQueryByIedName(const QString &iedName, bool *ok=0);
    VirLoopIedInfo::Ptr doQueryByIedName(const QString &iedName, bool isLoopIedInfo);
    VirLoopIedInfo::List doQueryByBayName(const QString &bayName, bool isLoopIedInfo);
    VirLoopIedInfo::List doQueryByNetType(const QString &voltClass, int netType);
    QHash<QString, QList<int>> doQueryNetType(bool *ok=0);
public:
    VirLoopConfig::List doQuery(QSqlDatabase db, bool *ok=0);
    VirLoopConfig::List doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok=0);
    VirLoopIedInfo::Ptr doQueryByIedName(QSqlDatabase db, const QString &iedName, bool isLoopIedInfo);
    VirLoopIedInfo::List doQueryByBayName(QSqlDatabase db, const QString &bayName, bool isLoopIedInfo);
    VirLoopIedInfo::List doQueryByNetType(QSqlDatabase db, const QString &voltClass, int netType);
    QHash<QString, QList<int>> doQueryNetType(QSqlDatabase db, bool *ok=0);
public:
    bool doInsert(VirLoopConfig::List &lst);
public:
    bool doUpdate(const VirLoopConfig::Ptr &ptr);
    bool doUpdate(VirLoopConfig::List &lst);
public:
    bool doDelete(int guid);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBVIRLOOPCONFIGDAO_H
