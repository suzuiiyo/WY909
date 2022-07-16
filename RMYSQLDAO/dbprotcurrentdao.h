#ifndef DBPROTCURRENTDAO_H
#define DBPROTCURRENTDAO_H
#include <QSqlDatabase>
#include <QString>
#include "protcurrent.h"
class DBProtCurrentDAO
{
public:
    DBProtCurrentDAO();
    ~DBProtCurrentDAO();
public:
    bool doInsert(QSqlDatabase db, ProtCurrent::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBPROTCURRENTDAO_H
