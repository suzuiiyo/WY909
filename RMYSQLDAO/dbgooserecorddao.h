#ifndef DBGOOSERECORDDAO_H
#define DBGOOSERECORDDAO_H
#include <QString>
#include <QSqlDatabase>
#include "gooserecord.h"
class DBGooseRecordDAO
{
public:
    DBGooseRecordDAO();
    ~DBGooseRecordDAO();
public:
    bool doInsert(QSqlDatabase db, GooseRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBGOOSERECORDDAO_H
