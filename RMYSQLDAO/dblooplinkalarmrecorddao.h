#ifndef DBLOOPLINKALARMRECORDDAO_H
#define DBLOOPLINKALARMRECORDDAO_H
#include <QString>
#include "looplinkalarmrecord.h"
#include "searchcondition.h"
class DBLoopLinkAlarmRecordDAO
{
public:
    DBLoopLinkAlarmRecordDAO();
    ~DBLoopLinkAlarmRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    LoopLinkAlarmRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool ackRecord(LoopLinkAlarmRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBLOOPLINKALARMRECORDDAO_H
