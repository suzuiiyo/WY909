#ifndef DBPRIMARYDEVICEINFODAO_H
#define DBPRIMARYDEVICEINFODAO_H
#include <QString>
#include <QSqlDatabase>
#include "primarydeviceinfo.h"
class DBPrimaryDeviceInfoDAO
{
public:
    DBPrimaryDeviceInfoDAO();
    ~DBPrimaryDeviceInfoDAO();
public:
    PrimaryDeviceInfo::List doQuery(bool *ok=0);
    PrimaryDeviceInfo::List doQueryByBayName(const QString &bayName, bool *ok=0);
    PrimaryDeviceInfo::Hash doQueryLineRelation(bool *ok=0);
    PrimaryDeviceInfo::Ptr doQueryByScheduleName(const QString &scheduleName, bool *ok=0);
    PrimaryDeviceInfo::Ptr doQueryByDevName(const QString &devName, bool *ok=0);
public:
    PrimaryDeviceInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    PrimaryDeviceInfo::List doQueryByBayName(QSqlDatabase db, const QString &bayName, bool *ok=0);
    PrimaryDeviceInfo::Hash doQueryLineRelation(QSqlDatabase db, bool *ok=0);
    PrimaryDeviceInfo::Ptr doQueryByScheduleName(QSqlDatabase db, const QString &scheduleName, bool *ok=0);
    PrimaryDeviceInfo::Ptr doQueryByDevName(QSqlDatabase db, const QString &devName, bool *ok=0);
public:
    bool doInsert(PrimaryDeviceInfo::List &lst);
public:
    bool doUpdate(const PrimaryDeviceInfo::Ptr &ptr);
    bool doUpdate(PrimaryDeviceInfo::List &lst);
public:
    bool doDeleteByDevName(const QString &devName);
    bool doDeleteByScheduleName(const QString &scheduleName);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBPRIMARYDEVICEINFODAO_H
