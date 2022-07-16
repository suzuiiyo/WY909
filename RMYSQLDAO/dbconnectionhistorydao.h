#ifndef DBCONNECTIONHISTORYDAO_H
#define DBCONNECTIONHISTORYDAO_H
#include <QString>
#include "connectionhistory.h"
#include "searchcondition.h"
class DBConnectionHistoryDAO
{
public:
    DBConnectionHistoryDAO();
    ~DBConnectionHistoryDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    ConnectionHistory::List doQuery(bool *ok=0);
    ConnectionHistory::List doQuery(const QString &iedName, bool *ok=0);
    ConnectionHistory::List doQuery(SearchCondition::List &lst, bool *ok=0);
    ConnectionHistory::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool doInsert(const ConnectionHistory::Ptr &ptr);
public:
    bool ackRecord(ConnectionHistory::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBCONNECTIONHISTORYDAO_H
