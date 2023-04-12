#ifndef DBSWITCHPORTDAO_H
#define DBSWITCHPORTDAO_H
#include <QSqlDatabase>
#include <QString>
#include "switchport.h"
class DBSwitchPortDAO
{
public:
    DBSwitchPortDAO();
    ~DBSwitchPortDAO();
public:
    SwitchPort::List doQuery(bool *ok=0);
    SwitchPort::List doQueryByLineRef(const QString &lineRef, bool *ok=0);
    SwitchPort::List doQueryByIedName(const QString &iedName, bool *ok=0);
    SwitchPort::Ptr doQueryByPortID(const QString &iedName, const QString &portID, bool *ok=0);
    SwitchPort *port(const QString &iedName, const QString &portID, bool *ok=0);
public:
    SwitchPort::List doQuery(QSqlDatabase db, bool *ok=0);
    SwitchPort::List doQueryByLineRef(QSqlDatabase db, const QString &lineRef, bool *ok=0);
    SwitchPort::List doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok=0);
    SwitchPort::Ptr doQueryByPortID(QSqlDatabase db, const QString &iedName, const QString &portID, bool *ok=0);
    SwitchPort *port(QSqlDatabase db, const QString &iedName, const QString &portID, bool *ok=0);
public:
    bool doInsert(SwitchPort::List &lst);
public:
    bool doUpdate(const SwitchPort::Ptr &ptr);
    bool doUpdate(SwitchPort::List &lst);
public:
    bool doDeleteByIedName(const QString &iedName);
    bool doDeleteByPortID(const QString &iedName, const QString &portID);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBSWITCHPORTDAO_H
