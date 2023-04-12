#ifndef DBGOOSEINFODAO_H
#define DBGOOSEINFODAO_H
#include <QString>
#include <QSqlDatabase>
#include "gooseinfo.h"
class DBGooseInfoDAO
{
public:
    DBGooseInfoDAO();
    ~DBGooseInfoDAO();
public:
    GooseInfo::List doQuery(bool *ok=0);
    GooseInfo::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    GooseInfo::List doQuery(const QString &iedName, bool *ok=0);
    GooseInfo::List doQuery(const QString &iedName, const QString &setType, bool *ok=0);
    GooseInfo *gooseInfo(const QString &dataRef, bool *ok=0);
public:
    GooseInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    GooseInfo::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    GooseInfo::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    GooseInfo::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
    GooseInfo *gooseInfo(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    GooseInfo::List doQueryUsingIed(QSqlDatabase db, bool *ok=0);
public:
    bool doInsert(GooseInfo::List &lst);
public:
    bool doUpdate(const GooseInfo::Ptr &ptr);
    bool doUpdate(GooseInfo::List &lst);
    bool doUpdate(GooseInfo::List &lst, int type);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool configGooseInfo();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBGOOSEINFODAO_H
