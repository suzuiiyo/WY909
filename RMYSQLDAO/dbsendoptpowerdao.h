#ifndef DBSENDOPTPOWERDAO_H
#define DBSENDOPTPOWERDAO_H
#include <QSqlDatabase>
#include <QString>
#include "sendoptpower.h"
#include "searchcondition.h"
class DBSendOptPowerDAO
{
public:
    DBSendOptPowerDAO();
    ~DBSendOptPowerDAO();
public:
    int countRecord(const QString &iedName, bool *ok=0);
public:
    SendOptPower::List doQuery(SearchCondition::List &lst, bool *ok=0);
    SendOptPower::List doQuery(const QString &dataRef, qint64 startTime, qint64 endTime, bool *ok=0);
public:
    bool doInsert(SendOptPower::List &lst);
    bool doInsert(QSqlDatabase db, SendOptPower::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBSENDOPTPOWERDAO_H
