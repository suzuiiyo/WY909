#ifndef DBDIAGNOSISOFPROTOPERATERECORDDAO_H
#define DBDIAGNOSISOFPROTOPERATERECORDDAO_H
#include "diagnosisofprotoperaterecord.h"
#include "searchcondition.h"
class DBDiagnosisOfProtOperateRecordDAO
{
public:
    DBDiagnosisOfProtOperateRecordDAO();
    ~DBDiagnosisOfProtOperateRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    DiagnosisOfProtOperateRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool ackRecord(DiagnosisOfProtOperateRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBDIAGNOSISOFPROTOPERATERECORDDAO_H
