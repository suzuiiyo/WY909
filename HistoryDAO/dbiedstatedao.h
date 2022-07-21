#ifndef DBIEDSTATEDAO_H
#define DBIEDSTATEDAO_H
#include <QString>
#include "devstate.h"
class DBIedStateDAO
{
public:
    DBIedStateDAO();
    ~DBIedStateDAO();
public:
    DevState::List doQuery(const QString &stationName);
    DevState::List doQuery(const QString &station, const QString &voltClass);
    DevState::List doQuery(const QString &station, const QString &voltClass, const QString &bayName);
public:
    bool isInit();
private:
    QString m_connectionName;
};
#endif // DBIEDSTATEDAO_H
