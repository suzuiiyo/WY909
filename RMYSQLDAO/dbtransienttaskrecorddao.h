#ifndef DBTRANSIENTTASKRECORDDAO_H
#define DBTRANSIENTTASKRECORDDAO_H
#include <QSqlDatabase>
#include <QString>
#include "transienttaskrecord.h"
class DBTransientTaskRecordDAO
{
public:
    DBTransientTaskRecordDAO();
    ~DBTransientTaskRecordDAO();
public:
    TransientTaskRecord::List doQuery(bool *ok=0);
    TransientTaskRecord::List doQuery(int taskState, bool *ok=0);
    TransientTaskRecord::List doQueryByIedName(const QString &iedName, int taskState, bool *ok=0);
    //TransientTaskRecord::List doQueryBySRIedName(const QString &srIedName, int taskState);
public:
    TransientTaskRecord::List doQuery(QSqlDatabase db, bool *ok=0);
    TransientTaskRecord::List doQuery(QSqlDatabase db, int taskState, bool *ok=0);
    TransientTaskRecord::List doQueryByIedName(QSqlDatabase db, const QString &iedName, int taskState, bool *ok=0);
    //TransientTaskRecord::List doQueryBySRIedName(QSqlDatabase db, const QString &srIedName, int taskState);
public:
    bool doInsert(TransientTaskRecord::List &lst);
    bool doInsert(QSqlDatabase db, TransientTaskRecord::List &lst);
public:
    bool doUpdate(TransientTaskRecord::List &lst);
    bool doUpdate(QSqlDatabase db, TransientTaskRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBTRANSIENTTASKRECORDDAO_H
