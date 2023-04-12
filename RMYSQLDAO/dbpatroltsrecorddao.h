#ifndef DBPATROLTSRECORDDAO_H
#define DBPATROLTSRECORDDAO_H
#include <QSqlDatabase>
#include <QString>
#include "patroltsrecord.h"
class DBPatrolTSRecordDAO
{
public:
    DBPatrolTSRecordDAO();
    ~DBPatrolTSRecordDAO();
public:
    bool doInsert(QSqlDatabase db, PatrolTSRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBPATROLTSRECORDDAO_H
