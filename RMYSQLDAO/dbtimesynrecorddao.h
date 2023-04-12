#ifndef DBTIMESYNRECORDDAO_H
#define DBTIMESYNRECORDDAO_H
#include <QString>
#include "timesynrecord.h"
#include "searchcondition.h"
class DBTimeSynRecordDAO
{
public:
    DBTimeSynRecordDAO();
    ~DBTimeSynRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    TimeSynRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool ackRecord(TimeSynRecord::List &lst);
private:
    QString m_connectionName;
};
#endif // DBTIMESYNRECORDDAO_H
