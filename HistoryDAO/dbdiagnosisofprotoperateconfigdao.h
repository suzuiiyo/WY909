#ifndef DBDIAGNOSISOFPROTOPERATECONFIGDAO_H
#define DBDIAGNOSISOFPROTOPERATECONFIGDAO_H
#include <QString>
#include <QSqlDatabase>
#include "diagnosisofprotoperateconfig.h"
class DBDiagnosisOfProtOperateConfigDAO
{
public:
    DBDiagnosisOfProtOperateConfigDAO();
    ~DBDiagnosisOfProtOperateConfigDAO();
public:
    DiagnosisOfProtOperateConfig::List doQuery(bool *ok=0);
    DiagnosisOfProtOperateConfig::List doQuery(const QString &iedName, bool *ok=0);
public:
    DiagnosisOfProtOperateConfig::List doQuery(QSqlDatabase db, bool *ok=0);
    DiagnosisOfProtOperateConfig::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
public:
    bool doInsert(DiagnosisOfProtOperateConfig::List &lst);
public:
    bool doUpdate(DiagnosisOfProtOperateConfig::List &lst);
public:
    bool doDelete(DiagnosisOfProtOperateConfig::List &lst);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBDIAGNOSISOFPROTOPERATECONFIGDAO_H
