#ifndef DBIEDSTATEDAO_H
#define DBIEDSTATEDAO_H
#include <QString>
#include <QSqlDatabase>
#include "iedstate.h"
class DBIedRealStateDAO
{
public:
    DBIedRealStateDAO();
    ~DBIedRealStateDAO();
public:
    IedState::Ptr doQuery(const QString &iedName, bool *ok=0);
    IedState::List doQuery(bool *ok=0);
public:
    IedState::Ptr doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    IedState::List doQuery(QSqlDatabase db, bool *ok=0);
    IedState::Hash doQueryHash(QSqlDatabase db, bool *ok=0);
//public:
//    bool doInit(QSqlDatabase db, QSqlDatabase dbR);
public:
    bool doInsert(QSqlDatabase db, IedState::List &lst);
    bool doClear(QSqlDatabase db);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBIEDSTATEDAO_H
