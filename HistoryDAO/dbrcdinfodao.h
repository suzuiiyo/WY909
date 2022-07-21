#ifndef DBRCDINFODAO_H
#define DBRCDINFODAO_H
#include <QString>
#include <QSqlDatabase>
#include "rcdinfo.h"
class DBRCDInfoDAO
{
public:
    DBRCDInfoDAO();
    ~DBRCDInfoDAO();
public:
    RCDInfo::List doQuery(bool *ok=0);
    RCDInfo::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    RCDInfo::List doQuery(const QString &iedName, bool *ok=0);
    RCDInfo::List doQuery(const QString &iedName, const QString &setType, bool *ok=0);
public:
    RCDInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    RCDInfo::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    RCDInfo::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    RCDInfo::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
public:
    bool doInsert(RCDInfo::List &lst);
public:
    bool doUpdate(const RCDInfo::Ptr &ptr);
    bool doUpdate(RCDInfo::List &lst);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBRCDINFODAO_H
