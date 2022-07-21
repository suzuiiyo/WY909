#ifndef DBDEVTEMPERATUREDAO_H
#define DBDEVTEMPERATUREDAO_H
#include <QString>
#include <QSqlDatabase>
#include "devtemperature.h"
#include "searchcondition.h"
class DBDevTemperatureDAO
{
public:
    DBDevTemperatureDAO();
    ~DBDevTemperatureDAO();
public:
    int countRecord(const QString &iedName, bool *ok=0);
public:
    DevTemperature::List doQuery(SearchCondition::List &lst, bool *ok=0);
    DevTemperature::List doQuery(const QString &dataRef, qint64 startTime, qint64 endTime, bool *ok=0);
public:
    bool doInsert(DevTemperature::List &lst);
    bool doInsert(QSqlDatabase db, DevTemperature::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBDEVTEMPERATUREDAO_H
