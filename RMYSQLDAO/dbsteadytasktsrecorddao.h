#ifndef DBSTEADYTASKTSRECORDDAO_H
#define DBSTEADYTASKTSRECORDDAO_H
#include <QString>
#include "steadytasktsrecord.h"
#include "searchcondition.h"
class DBSteadyTaskTSRecordDAO
{
public:
    DBSteadyTaskTSRecordDAO();
    ~DBSteadyTaskTSRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    SteadyTaskTSRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool ackRecord(SteadyTaskTSRecord::List &lst);
private:
    QString m_connectionName;
};
#endif // DBSTEADYTASKTSRECORDDAO_H
