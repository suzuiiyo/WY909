#ifndef DBONLINEMONITORDAO_H
#define DBONLINEMONITORDAO_H
#include <QString>
#include "monitorinfo.h"
class DBOnlineMonitorDAO
{
public:
    DBOnlineMonitorDAO();
    ~DBOnlineMonitorDAO();
public:
    MonitorInfo::List selectInfo(const QString &iedName);
public:
    bool initInfo();
public:
    bool doUpdate(const MonitorInfo::Ptr &monitorInfo);
    bool doUpdate(MonitorInfo::List &lstMonitorInfo);
public:
    bool deleteByDataRef(const QString &dataRef);
    bool deleteByIedName(const QString &iedName);
    bool clearInfo();
private:
    QString m_connectionName;
};
#endif // DBONLINEMONITORDAO_H
