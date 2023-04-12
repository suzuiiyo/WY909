#ifndef DBEVENTINFODAO_H
#define DBEVENTINFODAO_H
#include <QString>
#include <QSqlDatabase>
#include "eventinfo.h"
class DBEventInfoDAO
{
public:
    DBEventInfoDAO();
    ~DBEventInfoDAO();
public:
    EventInfo::List doQuery(bool *ok=0);
    EventInfo::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    EventInfo::List doQuery(const QString &iedName, bool *ok=0);
    EventInfo::List doQuery(const QString &iedName, const QString &setType, bool *ok=0);
public:
    EventInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    EventInfo::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    EventInfo::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    EventInfo::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
public:
    bool doInsert(EventInfo::List &lst);
public:
    bool doUpdate(const EventInfo::Ptr &ptr);
    bool doUpdate(EventInfo::List &lst);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBEVENTINFODAO_H
