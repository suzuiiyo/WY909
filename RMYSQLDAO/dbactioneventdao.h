#ifndef DBACTIONEVENTDAO_H
#define DBACTIONEVENTDAO_H
#include <QString>
#include <QSqlDatabase>
#include "acteventinfo.h"
#include "searchcondition.h"
class DBActionEventDAO
{
public:
    DBActionEventDAO();
    ~DBActionEventDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    ActEventInfo::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool doInsert(ActEventInfo::List &lst);
    bool doInsert(QSqlDatabase db, ActEventInfo::List &lst);
public:
    bool ackRecord(ActEventInfo::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBACTIONEVENTDAO_H
