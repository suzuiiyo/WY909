#ifndef DBLOOPPORTALARMRECORDDAO_H
#define DBLOOPPORTALARMRECORDDAO_H
#include <QString>
#include "loopportalarmrecord.h"
#include "searchcondition.h"
class DBLoopPortAlarmRecordDAO
{
public:
    DBLoopPortAlarmRecordDAO();
    ~DBLoopPortAlarmRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    LoopPortAlarmRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool ackRecord(LoopPortAlarmRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBLOOPPORTALARMRECORDDAO_H
