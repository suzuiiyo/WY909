#ifndef DBPROTVOLTAGEDAO_H
#define DBPROTVOLTAGEDAO_H
#include <QSqlDatabase>
#include <QString>
#include "protvoltage.h"
class DBProtVoltageDAO
{
public:
    DBProtVoltageDAO();
    ~DBProtVoltageDAO();
public:
    bool doInsert(QSqlDatabase db, ProtVoltage::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBPROTVOLTAGEDAO_H
