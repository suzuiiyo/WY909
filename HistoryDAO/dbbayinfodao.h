#ifndef DBBAYINFODAO_H
#define DBBAYINFODAO_H
#include <QSqlDatabase>
#include <QString>
#include "bayinfo.h"
class DBBayInfoDAO
{
public:
    DBBayInfoDAO();
    ~DBBayInfoDAO();
public:
    BayInfo::List doQuery(bool *ok=0);
    BayInfo::Ptr doQuery(const QString &bayName, bool *ok=0);
    BayInfo::List doQueryByBayType(const QString &bayType, bool *ok=0);
    BayInfo::Ptr doQueryByBayName(const QString &bayName, bool *ok=0);
    BayInfo::Hash doQueryHash(bool *ok=0);
    BayInfo::Hash dOQueryAllBay(bool *ok=0);
public:
    BayInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    BayInfo::Ptr doQuery(QSqlDatabase db, const QString &bayName, bool *ok=0);
    BayInfo::List doQueryByBayType(QSqlDatabase db, const QString &bayType, bool *ok=0);
    BayInfo::Ptr doQueryByBayName(QSqlDatabase db, const QString &bayName, bool *ok=0);
    BayInfo::Hash doQueryHash(QSqlDatabase db, bool *ok=0);
    BayInfo::Hash doQueryAllBay(QSqlDatabase db, bool *ok=0);
    //BayInfo::Ptr doQueryByBayName(QSqlDatabase db, const QString &bayName);
    //BayInfo::Ptr doQueryByBayName(const QString &bayName);
public:
    BayInfo::Ptr findRelationBay(const QString makeupBayName, bool *ok=0);
    BayInfo::Ptr findRelationBay(QSqlDatabase db, const QString makeupBayName, bool *ok=0);
public:
    bool doInsert(BayInfo::List &lst);
public:
    bool doUpdate(const BayInfo::Ptr &ptr);
    bool doUpdate(BayInfo::List &lst);
public:
    bool doDelete(const QString &bayName);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBBAYINFODAO_H
