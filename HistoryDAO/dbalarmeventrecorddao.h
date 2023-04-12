#ifndef DBALARMEVENTRECORDDAO_H
#define DBALARMEVENTRECORDDAO_H
#include <QString>
#include "eventrecord.h"
class DBAlarmEventRecordDAO
{
public:
    DBAlarmEventRecordDAO();
    ~DBAlarmEventRecordDAO();
public:
    EventRecord::List doQuery(const QString &iedName);
public:
    bool doInsert(EventRecord::List &lst);
//public:
//    bool doUpdate(const EventRecord::Ptr &ptr);
//    bool doUpdate(EventRecord::List &lst);
private:
    QString m_connectionName;
};
#endif // DBALARMEVENTRECORDDAO_H
