#ifndef DBBAYSTATEDAO_H
#define DBBAYSTATEDAO_H
#include <QSqlDatabase>
#include <QString>
#include "baystate.h"
class DBBayStateDAO
{
public:
    DBBayStateDAO();
    ~DBBayStateDAO();
public:
    BayState::Ptr doQuery(const QString &bayName, bool *ok=0);
    BayState::List doQuery(bool *ok=0);
public:
    BayState::Ptr doQuery(QSqlDatabase db, const QString &bayName, bool *ok=0);
    BayState::List doQuery(QSqlDatabase db, bool *ok=0);
//public:
//    bool doInit(QSqlDatabase db, QSqlDatabase dbR);
public:
    bool doInsert(BayState::List &lst);
    bool doInsert(QSqlDatabase db, BayState::List &lst);
    bool doClear(QSqlDatabase db);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBBAYSTATEDAO_H
