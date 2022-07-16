#ifndef DBSETTINGDAO_H
#define DBSETTINGDAO_H
#include <QSqlDatabase>
#include <QString>
#include "setting.h"
class DBSettingDAO
{
public:
    DBSettingDAO();
    ~DBSettingDAO();
public:
    Setting::List doQuery(bool *ok=0);
    Setting::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    Setting::List doQueryByIedName(const QString &iedName, bool *ok=0);
    Setting::List doQueryBySetType(const QString &iedName, const QString &setType, bool *ok=0);
public:
    Setting::List doQuery(QSqlDatabase db, bool *ok=0);
    Setting::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    Setting::List doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok=0);
    Setting::List doQueryBySetType(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
public:
    bool doInsert(Setting::List &lst);
public:
    bool doUpdate(const Setting::Ptr &ptr);
    bool doUpdate(Setting::List &lst);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBSETTINGDAO_H
