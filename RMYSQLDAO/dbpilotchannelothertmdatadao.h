#ifndef DBPILOTCHANNELOTHERTMDATADAO_H
#define DBPILOTCHANNELOTHERTMDATADAO_H
#include <QSqlDatabase>
#include <QString>
#include "pilotchannelothertmdata.h"
class DBPilotChannelOtherTMDAO
{
public:
    DBPilotChannelOtherTMDAO();
    ~DBPilotChannelOtherTMDAO();
public:
    bool doInsert(QSqlDatabase db, PilotChannelOtherTMData::List &lst);
public:
    bool doCreateTable();
public:
    QString m_connectionName;
};
#endif // DBPILOTCHANNELOTHERTMDATADAO_H
