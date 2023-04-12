#ifndef DBPATROLCONCLUSIONRECORDDAO_H
#define DBPATROLCONCLUSIONRECORDDAO_H
#include "patrolconclusionrecord.h"
#include "searchcondition.h"
class DBPatrolConclusionRecordDAO
{
public:
    DBPatrolConclusionRecordDAO();
    ~DBPatrolConclusionRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    PatrolConclusionRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool ackRecord(PatrolConclusionRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBPATROLCONCLUSIONRECORDDAO_H
