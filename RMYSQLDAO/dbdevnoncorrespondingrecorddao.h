#ifndef DBDEVNONCORRESPONDINGRECORDDAO_H
#define DBDEVNONCORRESPONDINGRECORDDAO_H
#include <QString>
#include <QSqlDatabase>
#include "devnoncorrespondingrecord.h"
#include "searchcondition.h"
class DBDevNonCorrespondingRecordDAO
{
public:
    DBDevNonCorrespondingRecordDAO();
    ~DBDevNonCorrespondingRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    DevNonCorrespondingRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool ackRecord(DevNonCorrespondingRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBDEVNONCORRESPONDINGRECORDDAO_H
