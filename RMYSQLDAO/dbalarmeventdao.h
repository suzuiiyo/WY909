#ifndef DBALARMEVENTDAO_H
#define DBALARMEVENTDAO_H
#include <QString>
#include <QSqlDatabase>
#include "alarmeventinfo.h"
#include "searchcondition.h"
class DBAlarmEventDAO
{
public:
    DBAlarmEventDAO();
    ~DBAlarmEventDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    AlarmEventInfo::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool doInsert(AlarmEventInfo::List &lst);
    bool doInsert(QSqlDatabase db, AlarmEventInfo::List &lst);
public:
    bool ackRecord(AlarmEventInfo::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBALARMEVENTDAO_H
