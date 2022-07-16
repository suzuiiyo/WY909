#ifndef DBRUNSTATERECORDDAO_H
#define DBRUNSTATERECORDDAO_H
#include <QSqlDatabase>
#include "runstaterecord.h"
class DBRunStateRecordDAO
{
public:
    DBRunStateRecordDAO();
    ~DBRunStateRecordDAO();
public:
    bool doInsert(QSqlDatabase db, RunStateRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBRUNSTATERECORDDAO_H
