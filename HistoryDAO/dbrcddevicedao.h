#ifndef DBRCDDEVICEDAO_H
#define DBRCDDEVICEDAO_H
#include <QString>
#include <QSqlDatabase>
#include "rcddevice.h"
class DBRcdDeviceDAO
{
public:
    DBRcdDeviceDAO();
    ~DBRcdDeviceDAO();
public:
    RcdDevice::List doQuery();
public:
    RcdDevice::List doQuery(QSqlDatabase db);
//public:
//    bool doUpdate(const RcdDevice::Ptr &ptr);
private:
    QString m_connectionName;
};
#endif // DBRCDDEVICEDAO_H
