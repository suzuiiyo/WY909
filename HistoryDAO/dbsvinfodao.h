#ifndef DBSVINFODAO_H
#define DBSVINFODAO_H
#include <QString>
#include <QSqlDatabase>
#include "svinfo.h"
class DBSVInfoDAO
{
public:
    DBSVInfoDAO();
    ~DBSVInfoDAO();
public:
    SVInfo::List doQuery(bool *ok=0);
    SVInfo::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    SVInfo::List doQuery(const QString &iedName, bool *ok=0);
    SVInfo::List doQuery(const QString &iedName, const QString &setType, bool *ok=0);
public:
    SVInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    SVInfo::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    SVInfo::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    SVInfo::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
public:
    bool doInsert(SVInfo::List &lst);
public:
    bool doUpdate(const SVInfo::Ptr &ptr);
    bool doUpdate(SVInfo::List &svInfo);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBSVINFODAO_H
