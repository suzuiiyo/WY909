#ifndef DBPATROLDAO_H
#define DBPATROLDAO_H
#include <QString>
#include <QSqlDatabase>
#include "patrol.h"
class DBPatrolDAO
{
public:
    DBPatrolDAO();
    ~DBPatrolDAO();
public:
    Patrol::List doQuery(bool *ok=0);
    Patrol::List doQueryByIedName(const QString &iedName, bool *ok=0);
    Patrol::List doQueryByDataRef(const QString &dataRef, bool *ok=0);
    Patrol::List doQueryByDataType(const QString &dataType, bool *ok=0);
    Patrol::List doQuery(const QString &iedName, const QString &dataType, bool *ok=0);
public:
    Patrol::List doQuery(QSqlDatabase db, bool *ok=0);
    Patrol::List doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok=0);
    Patrol::List doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    Patrol::List doQueryByDataType(QSqlDatabase db, const QString &dataType, bool *ok=0);
    Patrol::List doQuery(QSqlDatabase db, const QString &iedName, const QString &dataType, bool *ok=0);
public:
    bool doInsert(Patrol::List &lst);
public:
    bool doUpdate(const Patrol::Ptr &ptr);
    bool doUpdate(Patrol::List &lst);
public:
    bool doDeleteByIedName(const QString &iedName);
    bool doDeleteByDataRef(const QString &dataRef);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBPATROLDAO_H
