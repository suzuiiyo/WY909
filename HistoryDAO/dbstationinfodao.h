#ifndef DBSTATIONINFODAO_H
#define DBSTATIONINFODAO_H
#include <QSqlDatabase>
#include <QString>
#include "stationinfo.h"
class DBStationInfoDAO
{
public:
    DBStationInfoDAO();
    ~DBStationInfoDAO();
public:
    StationInfo::List doQuery(bool *ok=0);
    StationInfo::Ptr doQuery(const QString &stationName, bool *ok=0);
    StationInfo::Hash doQueryHash(bool *ok=0);
public:
    StationInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    StationInfo::Ptr doQuery(QSqlDatabase db, const QString &stationName, bool *ok=0);
    StationInfo::Hash doQueryHash(QSqlDatabase db, bool *ok=0);
public:
    bool doInsert(StationInfo::List &lst);
public:
    bool doUpdate(const StationInfo::Ptr &ptr);
    bool doUpdate(StationInfo::List &lst);
public:
    bool doDelete(const QString &stationName);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBSTATIONINFODAO_H
