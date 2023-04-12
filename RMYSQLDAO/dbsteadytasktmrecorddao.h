#ifndef DBSTEADYTASKTMRECORDDAO_H
#define DBSTEADYTASKTMRECORDDAO_H
#include <QString>
#include "steadytasktmrecord.h"
#include "searchcondition.h"
class DBSteadyTaskTMRecordDAO
{
public:
    DBSteadyTaskTMRecordDAO();
    ~DBSteadyTaskTMRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    SteadyTaskTMRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool ackRecord(SteadyTaskTMRecord::List &lst);
private:
    QString m_connectionName;
};
#endif // DBSTEADYTASKTMRECORDDAO_H
