#ifndef DBTSDATAINFODAO_H
#define DBTSDATAINFODAO_H
#include <QSqlDatabase>
#include <QString>
#include "tsdatainfo.h"
class DBTSDataInfoDAO
{
public:
    DBTSDataInfoDAO();
    ~DBTSDataInfoDAO();
public:
    TSDataInfo::List doQuery(bool *ok=0);
    TSDataInfo::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    TSDataInfo::List doQuery(const QString &iedName, bool *ok=0);
    TSDataInfo::List doQuery(const QString &iedName, const QString &setType, bool *ok=0);
public:
    TSDataInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    TSDataInfo::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    TSDataInfo::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    TSDataInfo::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
public:
    bool doInsert(TSDataInfo::List &lst);
public:
    bool doUpdate(const TSDataInfo::Ptr &ptr);
    bool doUpdate(TSDataInfo::List &lst);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBTSDATAINFODAO_H
