#ifndef DBTMDATAINFODAO_H
#define DBTMDATAINFODAO_H
#include <QSqlDatabase>
#include <QString>
#include "tmdatainfo.h"
class DBTMDataInfoDAO
{
public:
    DBTMDataInfoDAO();
    ~DBTMDataInfoDAO();
public:
    TMDataInfo::List doQuery(bool *ok=0);
    TMDataInfo::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    TMDataInfo::List doQuery(const QString &iedName, bool *ok=0);
    TMDataInfo::List doQuery(const QString &iedName, const QString &setType, bool *ok=0);
public:
    TMDataInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    TMDataInfo::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    TMDataInfo::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    TMDataInfo::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
public:
    bool doInsert(TMDataInfo::List &lst);
public:
    bool doUpdate(const TMDataInfo::Ptr &ptr);
    bool doUpdate(TMDataInfo::List &lst);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBTMDATAINFODAO_H
