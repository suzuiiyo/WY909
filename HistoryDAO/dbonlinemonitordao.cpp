#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include "dbconnection.h"
#include "monitorinfo.h"
#include "dbonlinemonitordao.h"
DBOnlineMonitorDAO::DBOnlineMonitorDAO()
    : m_connectionName("connectOnlineMonitor")
{

}

DBOnlineMonitorDAO::~DBOnlineMonitorDAO()
{

}

//DBOnlineMonitorDAO::selectInfoByStation(const QString &stationName)
//{

//}
