#ifndef DBVOLTCLASSINFODAO_H
#define DBVOLTCLASSINFODAO_H
#include <QSqlDatabase>
#include <QString>
#include "voltclassinfo.h"
class DBVoltClassInfoDAO
{
public:
    DBVoltClassInfoDAO();
    ~DBVoltClassInfoDAO();
public:
    VoltClassInfo::List doQuery(bool *ok=0);
    VoltClassInfo::Ptr doQuery(const QString &voltClass, bool *ok=0);
    VoltClassInfo::Hash doQueryHash(bool *ok=0);
public:
    VoltClassInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    VoltClassInfo::Ptr doQuery(QSqlDatabase db, const QString &voltClass, bool *ok=0);
    VoltClassInfo::Hash doQueryHash(QSqlDatabase db, bool *ok=0);
public:
    bool doInsert(VoltClassInfo::List &lst);
public:
    bool doUpdate(const VoltClassInfo::Ptr &ptr);
    bool doUpdate(VoltClassInfo::List &lst);
public:
    bool doDelete(const QString &voltClass);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBVOLTCLASSINFODAO_H
