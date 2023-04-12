#ifndef DBANACONFIGDAO_H
#define DBANACONFIGDAO_H
#include <QString>
#include <QSqlDatabase>
#include "anaconfig.h"
class DBAnaConfigDAO
{
public:
    DBAnaConfigDAO();
    ~DBAnaConfigDAO();
public:
    AnaConfig::Hash doQuery(QSqlDatabase db, bool *ok=0);
public:
    bool doInsert(AnaConfig::List &lst);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBANACONFIGDAO_H
