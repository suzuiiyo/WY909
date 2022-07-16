#ifndef DBINSPECTIONRESULTDAO_H
#define DBINSPECTIONRESULTDAO_H
#include <QString>
#include "inspectionresult.h"
class DBInspectionResultDAO
{
public:
    DBInspectionResultDAO();
    ~DBInspectionResultDAO();
public:
    InspectionResult::List doQuery(bool *ok=0);
    InspectionResult::Ptr doQuery(const QString &iedName, bool *ok=0);
    InspectionResult::List doQuery(int result, bool *ok=0);
public:
    bool doUpdate(InspectionResult::List &lst);
public:
    bool doInsert(InspectionResult::List &lst);
private:
    QString m_connectionName;
};
#endif // DBINSPECTIONRESULTDAO_H
