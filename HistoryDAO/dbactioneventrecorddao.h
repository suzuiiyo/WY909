#ifndef DBACTIONEVENTRECORDDAO_H
#define DBACTIONEVENTRECORDDAO_H
#include <QString>
#include "eventrecord.h"
class DBActionEventRecordDAO
{
public:
    DBActionEventRecordDAO();
    ~DBActionEventRecordDAO();
public:
    EventRecord::List doQuery(const QString &iedName, bool *ok = Q_NULLPTR);
public:
    bool doInsert(EventRecord::List &lst, bool *ok = Q_NULLPTR);
public:
    QString m_connectionName;
};
#endif // DBACTIONEVENTRECORDDAO_H
