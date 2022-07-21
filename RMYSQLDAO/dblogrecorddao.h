#ifndef DBLOGRECORDDAO_H
#define DBLOGRECORDDAO_H
#include <QString>
#include "logrecord.h"
#include "searchcondition.h"
class DBLogRecordDAO
{
public:
    DBLogRecordDAO();
    ~DBLogRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, int logType, bool *ok=0);
public:
    LogRecord::List doQuery(const SearchCondition::Ptr &ptr, int logType, bool *ok=0);
public:
    bool doInsert(const QString &fileName, int logType);
private:
    QString m_connectionName;
};
#endif // DBLOGRECORDDAO_H
