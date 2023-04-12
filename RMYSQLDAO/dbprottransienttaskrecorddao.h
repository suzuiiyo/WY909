#ifndef DBPROTTRANSIENTTASKRECORDDAO_H
#define DBPROTTRANSIENTTASKRECORDDAO_H
#include <QSqlDatabase>
#include <QString>
#include "prottransienttaskrecord.h"
#include "searchcondition.h"
class DBProtTransientTaskRecordDAO
{
public:
    DBProtTransientTaskRecordDAO();
    ~DBProtTransientTaskRecordDAO();
public:
    int countRecord(bool *ok=0);
    int countRecord(QSqlDatabase db, bool *ok=0);
public:
    ProtTransientTaskRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
    ProtTransientTaskRecord::List doQuery(QSqlDatabase db, const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool doInsert(ProtTransientTaskRecord::List &lst);
    bool doInsert(QSqlDatabase db, ProtTransientTaskRecord::List &lst);
public:
    bool doUpdate(ProtTransientTaskRecord::List &lst);
    bool doUpdate(QSqlDatabase db, ProtTransientTaskRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBPROTTRANSIENTTASKRECORDDAO_H
