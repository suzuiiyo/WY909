#ifndef DBSTRAPRECORDDAO_H
#define DBSTRAPRECORDDAO_H
#include <QSqlDatabase>
#include <QString>
#include "straprecord.h"
class DBStrapRecordDAO
{
public:
    DBStrapRecordDAO();
    ~DBStrapRecordDAO();
public:
    bool doInsert(QSqlDatabase db, StrapRecord::List &lst);
public:
    bool doCreateTable();
public:
    QString m_connectionName;
};
#endif // DBSTRAPRECORDDAO_H
