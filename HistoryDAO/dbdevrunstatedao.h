#ifndef DBDEVRUNSTATEDAO_H
#define DBDEVRUNSTATEDAO_H
#include <QSqlDatabase>
#include <QString>
#include "devrunstate.h"
class DBDevRunStateDAO
{
public:
    DBDevRunStateDAO();
    ~DBDevRunStateDAO();
public:
    DevRunState::List doQuery(bool *ok=0);
    DevRunState::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    DevRunState::List doQuery(const QString &iedName, bool *ok=0);
    DevRunState::List doQuery(const QString &iedName, const QString &setType, bool *ok=0);
    DevRunState * devRunState(const QString &dataRef, bool *ok=0);
public:
    DevRunState::List doQuery(QSqlDatabase db, bool *ok=0);
    DevRunState::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    DevRunState::List doQuery(QSqlDatabase db, const QString &iedNam, bool *ok=0);
    DevRunState::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
    DevRunState * devRunState(QSqlDatabase db, const QString &dataRef, bool *ok=0);
public:
    bool doInsert(DevRunState::List &lst);
public:
    bool doUpdate(const DevRunState::Ptr &ptr);
    bool doUpdate(DevRunState::List &lst);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBDEVRUNSTATEDAO_H
