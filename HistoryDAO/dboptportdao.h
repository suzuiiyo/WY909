#ifndef DBOPTPORTDAO_H
#define DBOPTPORTDAO_H
#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QList>
#include "optport.h"
class DBOptPortDAO
{
public:
    DBOptPortDAO();
    ~DBOptPortDAO();
public:
    OptPort::List doQuery(bool *ok=0);
    OptPort::List doQueryByLineRef(const QString &lineRef, bool *ok=0);
    OptPort::List doQueryByIedName(const QString &iedName, bool *ok=0);
    OptPort::Ptr doQueryByPortID(const QString &iedName, const QString &portID, bool *ok=0);
    OptPort *port(const QString &iedName, const QString &portID, bool *ok=0);
    QHash<QString, QList<int>> doQueryNetType(bool *ok=0);
    //OptPort::List doQueryBy
    //OptPort::List doQuery(const QString &iedName, const QString &setType);
public:
    OptPort::List doQuery(QSqlDatabase db, bool *ok=0);
    OptPort::List doQueryByLineRef(QSqlDatabase db, const QString &lineRef, bool *ok=0);
    OptPort::List doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok=0);
    OptPort::Ptr doQueryByPortID(QSqlDatabase db, const QString &iedName, const QString &portID, bool *ok=0);
    OptPort *port(QSqlDatabase db, const QString &iedName, const QString &portID, bool *ok=0);
    QHash<QString, QList<int>> doQueryNetType(QSqlDatabase db, bool *ok=0);
    QList<int> doQueryNetType(QSqlDatabase db, const QString &stationName, bool *ok=0);
public:
    bool doInsert(OptPort::List &lst);
public:
    bool doUpdate(const OptPort::Ptr &ptr);
    bool doUpdate(OptPort::List &lst);
public:
    bool doDeleteByLineRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doDeleteByPortID(const QString &portID);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBOPTPORTDAO_H
