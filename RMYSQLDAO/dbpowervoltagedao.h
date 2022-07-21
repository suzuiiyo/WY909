#ifndef DBPOWERVOLTAGEDAO_H
#define DBPOWERVOLTAGEDAO_H
#include <QSqlDatabase>
#include <QString>
#include "powervoltage.h"
#include "searchcondition.h"
class DBPowerVoltageDAO
{
public:
    DBPowerVoltageDAO();
    ~DBPowerVoltageDAO();
public:
    int countRecord(const QString &iedName, bool *ok=0);
public:
    PowerVoltage::List doQuery(SearchCondition::List &lst, bool *ok=0);
    PowerVoltage::List doQuery(const QString &dataRef, qint64 startTime, qint64 endTime, bool *ok=0);
public:
    bool doInsert(PowerVoltage::List &lst);
    bool doInsert(QSqlDatabase db, PowerVoltage::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBPOWERVOLTAGEDAO_H
