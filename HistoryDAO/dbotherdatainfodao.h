#ifndef DBOTHERDATAINFODAO_H
#define DBOTHERDATAINFODAO_H
#include <QSqlDatabase>
#include <QString>
#include "otherdatainfo.h"
class DBOtherDataInfoDAO
{
public:
    DBOtherDataInfoDAO();
    ~DBOtherDataInfoDAO();
public:
    OtherDataInfo::List doQuery(bool *ok=0);
    OtherDataInfo::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    OtherDataInfo::List doQuery(const QString &iedName, bool *ok=0);
    OtherDataInfo::List doQuery(const QString &iedName, const QString &setType, bool *ok=0);
public:
    OtherDataInfo::List doQuery(QSqlDatabase db, bool *ok=0);
    OtherDataInfo::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    OtherDataInfo::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    OtherDataInfo::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
public:
    bool doInsert(OtherDataInfo::List &lst);
public:
    bool doUpdate(const OtherDataInfo::Ptr &ptr);
    bool doUpdate(OtherDataInfo::List &lst);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBOTHERDATAINFODAO_H
