#ifndef DBSTRAPLIGHTPLATEDAO_H
#define DBSTRAPLIGHTPLATEDAO_H
#include <QString>
#include <QSqlDatabase>
#include <QList>
#include "strap.h"
class DBStrapLightPlateDAO
{
public:
    DBStrapLightPlateDAO();
    ~DBStrapLightPlateDAO();
public:
    Strap::List doQuery(bool *ok=0);
    Strap::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    Strap::List doQuery(const QString &iedName, bool *ok=0);
    Strap::List doQuery(const QString &iedName, const QString &setType, bool *ok=0);
    QList<Strap*> doQueryLst(const QString &iedName, bool *ok=0);
    Strap *strap(const QString &dataRef, bool *ok=0);
public:
    Strap::List doQuery(QSqlDatabase db, bool *ok=0);
    Strap::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    Strap::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
    Strap::List doQuery(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);
    QList<Strap*> doQueryLst(QSqlDatabase db, const QString &iedName, bool *ok=0);
    Strap *strap(QSqlDatabase db, const QString &dataRef, bool *ok=0);
public:
    bool doInsert(Strap::List &lstStrap);
public:
    bool doUpdate(const Strap::Ptr &strap);
    bool doUpdate(Strap::List &lstStrap);
    //bool doUpdate(Strap::List &lstStrap, int type);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool configStrapInfo();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBSTRAPLIGHTPLATETAB_H
