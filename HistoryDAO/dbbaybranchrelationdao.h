#ifndef DBBAYBRANCHRELATIONDAO_H
#define DBBAYBRANCHRELATIONDAO_H
#include <QSqlDatabase>
#include <QString>
#include <QList>
#include "baybranchrelation.h"
class DBBayBranchRelationDAO
{
public:
    DBBayBranchRelationDAO();
    ~DBBayBranchRelationDAO();
public:
    BayBranchRelation::List doQuery(bool *ok=0);
    BayBranchRelation::List doQuery(const QString &makeupBayName, bool *ok=0);
    BayBranchRelation::Ptr doQuery(const QString &makeupBayName, const QString &baseBayName, bool *ok=0);
    QList<QList<QString>> doQueryBayList(bool *ok=0);
    BayBranchRelation::Hash doQueryHash(bool *ok=0);
    BayBranchRelation::Hash doQuery(int type, bool *ok=0);
public:
    BayBranchRelation::List doQuery(QSqlDatabase db, bool *ok=0);
    BayBranchRelation::List doQuery(QSqlDatabase db, const QString &makeupBayName, bool *ok=0);
    BayBranchRelation::Ptr doQuery(QSqlDatabase db, const QString &makeupBayName, const QString &baseBayName, bool *ok=0);
    QList<QList<QString>> doQueryBayList(QSqlDatabase db, bool *ok=0);
    BayBranchRelation::Hash doQueryHash(QSqlDatabase db, bool *ok=0);
    BayBranchRelation::Hash doQuery(QSqlDatabase db, int type, bool *ok=0);
public:
    bool doInsert(BayBranchRelation::List &lst);
    bool doInsert(QSqlDatabase db, BayBranchRelation::List &lst);
public:
    bool doUpdate(BayBranchRelation::List &lst);
    bool doUpdate(QSqlDatabase db, BayBranchRelation::List &lst);
public:
    bool doDelete(BayBranchRelation::List &lst);
    bool doDelete(QSqlDatabase db, BayBranchRelation::List &lst);
public:
    bool doClear();
    bool doClear(QSqlDatabase db);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBBAYBRANCHRELATIONDAO_H
