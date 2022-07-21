#ifndef DBSRTRANSIENTTASKRECORDDAO_H
#define DBSRTRANSIENTTASKRECORDDAO_H
#include <QSqlDatabase>
#include <QString>
#include "srtransienttaskrecord.h"
#include "searchcondition.h"
class DBSRTransientTaskRecordDAO
{
public:
    DBSRTransientTaskRecordDAO();
    ~DBSRTransientTaskRecordDAO();
public:
    int countRecord(bool *ok=0);
    int countRecord(QSqlDatabase db, bool *ok=0);
public:
    SRTransientTaskRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
    SRTransientTaskRecord::List doQuery(QSqlDatabase db, const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool doInsert(SRTransientTaskRecord::List &lst);
    bool doInsert(QSqlDatabase db, SRTransientTaskRecord::List &lst);
public:
    bool doUpdate(SRTransientTaskRecord::List &lst);
    bool doUpdate(QSqlDatabase db, SRTransientTaskRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBSRTRANSIENTTASKRECORDDAO_H
