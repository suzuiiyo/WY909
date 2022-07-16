#ifndef DBPATROLFILEDAO_H
#define DBPATROLFILEDAO_H
#include <QString>
#include "patrolfile.h"
#include "searchcondition.h"
class DBPatrolFileDAO
{
public:
    DBPatrolFileDAO();
    ~DBPatrolFileDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    PatrolFile::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
private:
    QString m_connectionName;
};
#endif // DBPATROLFILEDAO_H
