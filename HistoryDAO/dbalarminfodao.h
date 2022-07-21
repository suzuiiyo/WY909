#ifndef DBALARMINFODAO_H
#define DBALARMINFODAO_H
#include <QString>
#include <QSqlDatabase>
#include "alarminfo.h"
class DBAlarmInfoDAO
{
public:
    DBAlarmInfoDAO();
    ~DBAlarmInfoDAO();
public:
    AlarmInfo::List doQuery(bool *ok = Q_NULLPTR);
    AlarmInfo::Ptr doQueryByDataRef(const QString &dataRef, bool *ok = Q_NULLPTR);
    AlarmInfo::List doQuery(const QString &iedName, bool *ok = Q_NULLPTR);
    AlarmInfo::List doQuery(const QString &iedName, const QString &setType, bool *ok = Q_NULLPTR);
public:
    AlarmInfo::List doQuery(QSqlDatabase db, bool *ok = Q_NULLPTR);
    AlarmInfo::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok = Q_NULLPTR);
    AlarmInfo::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok = Q_NULLPTR);
    AlarmInfo::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok = Q_NULLPTR);
public:
    bool doInsert(AlarmInfo::List &lst);
public:
    bool doUpdate(const AlarmInfo::Ptr &ptr);
    bool doUpdate(AlarmInfo::List &lst);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBALARMINFODAO_H
