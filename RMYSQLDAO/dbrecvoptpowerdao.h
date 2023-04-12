#ifndef DBRECVOPTPOWERDAO_H
#define DBRECVOPTPOWERDAO_H
#include <QString>
#include <QSqlDatabase>
#include "recvoptpower.h"
#include "searchcondition.h"
class DBRecvOptPowerDAO
{
public:
    DBRecvOptPowerDAO();
    ~DBRecvOptPowerDAO();
public:
    int countRecord(const QString &iedName, bool *ok=0);
public:
    RecvOptPower::List doQuery(SearchCondition::List &lst, bool *ok=0);
    RecvOptPower::List doQuery(const QString &dataRef, qint64 startTime, qint64 endTime, bool *ok=0);
public:
    bool doInsert(RecvOptPower::List &lst);
    bool doInsert(QSqlDatabase db, RecvOptPower::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBRECVOPTPOWERDAO_H
