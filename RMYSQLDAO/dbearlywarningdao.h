#ifndef DBEARLYWARNINGDAO_H
#define DBEARLYWARNINGDAO_H
#include <QString>
#include <QSqlDatabase>
#include "earlywarning.h"
class DBEarlyWarningDAO
{
public:
    DBEarlyWarningDAO();
    ~DBEarlyWarningDAO();
public:
    EarlyWarning::Hash doQuery(bool *ok=0);
    EarlyWarning::Ptr doQuery(const QString &dataRef, bool *ok=0);
public:
    EarlyWarning::Hash doQuery(QSqlDatabase db, bool *ok=0);
    EarlyWarning::Ptr doQuery(QSqlDatabase db, const QString &dataRef, bool *ok=0);
public:
    bool doUpdate(const EarlyWarning::Ptr &ptr);
    bool doUpdate(EarlyWarning::List &lst);
    bool doUpdate(const QString &dataRef, int type, int dataValue);
public:
    bool doClear();
    bool doClear(QSqlDatabase db);
public:
    bool doInsert(EarlyWarning::List &lst);
    bool doInsert(QSqlDatabase db, EarlyWarning::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBEARLYWARNINGDAO_H
