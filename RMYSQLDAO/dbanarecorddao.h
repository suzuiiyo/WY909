#ifndef DBANARECORDDAO_H
#define DBANARECORDDAO_H
#include <QSqlDatabase>
#include <QString>
#include "anarecord.h"
class DBAnaRecordDAO
{
public:
    DBAnaRecordDAO();
    ~DBAnaRecordDAO();
public:
    bool doInsert(QSqlDatabase db, AnaRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBANARECORDDAO_H
