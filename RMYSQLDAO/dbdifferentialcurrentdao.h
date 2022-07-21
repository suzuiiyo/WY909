#ifndef DBDIFFERENTIALCURRENTDAO_H
#define DBDIFFERENTIALCURRENTDAO_H
#include <QSqlDatabase>
#include <QString>
#include "differentialcurrent.h"
#include "searchcondition.h"
class DBDifferentialCurrentDAO
{
public:
    DBDifferentialCurrentDAO();
    ~DBDifferentialCurrentDAO();
public:
    int countRecord(const QString &iedName, bool *ok=0);
public:
    DifferentialCurrent::List doQuery(SearchCondition::List &lst, bool *ok=0);
    DifferentialCurrent::List doQuery(const QString &dataRef, qint64 startTime, qint64 endTime, bool *ok=0);
public:
    bool doInsert(DifferentialCurrent::List &lst);
    bool doInsert(QSqlDatabase db, DifferentialCurrent::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBDIFFERENTIALCURRENTDAO_H
