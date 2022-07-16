#ifndef DBPILOTCHANNELOPTPOWERDAO_H
#define DBPILOTCHANNELOPTPOWERDAO_H
#include <QSqlDatabase>
#include <QString>
#include "pilotchanneloptpower.h"
#include "searchcondition.h"
class DBPilotChannelOptPowerDAO
{
public:
    DBPilotChannelOptPowerDAO();
    ~DBPilotChannelOptPowerDAO();
public:
    int countRecord(const QString &iedName, bool *ok=0);
public:
    PilotChannelOptPower::List doQuery(SearchCondition::List &lst, bool *ok=0);
    PilotChannelOptPower::List doQuery(const QString &dataRef, qint64 startTime, qint64 endTime, bool *ok=0);
public:
    bool doInsert(PilotChannelOptPower::List &lst);
    bool doInsert(QSqlDatabase db, PilotChannelOptPower::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBPILOTCHANNELOPTPOWERDAO_H
