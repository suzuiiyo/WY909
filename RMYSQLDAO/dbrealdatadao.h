#ifndef DBREALDATADAO_H
#define DBREALDATADAO_H
#include <QString>
#include <QSqlDatabase>
#include "realdata.h"
class DBRealDataDAO
{
public:
    DBRealDataDAO();
    ~DBRealDataDAO();
public:
    RealData::Hash doQuery(bool *ok=0);
    RealData::Hash doQuery(QSqlDatabase db, bool *ok=0);
    RealData::Ptr doQuery(const QString &dataRef, bool *ok=0);
    RealData::Ptr doQuery(QSqlDatabase db, const QString &dataRef, bool *ok=0);
//    bool doInit();
//    bool doInit(QSqlDatabase db, QSqlDatabase dbR);
public:
    bool doUpdate(const RealData::Ptr &ptr);
    bool doUpdate(RealData::List &lst);
    bool doUpdate(QSqlDatabase db, RealData::List &lst);
    bool doClear();
    bool doClear(QSqlDatabase db);
public:
    bool doInsert(RealData::List &lst);
    bool doInsert(QSqlDatabase db, RealData::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBREALDATADAO_H
