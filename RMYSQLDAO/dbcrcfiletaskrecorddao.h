#ifndef DBCRCFILETASKRECORDDAO_H
#define DBCRCFILETASKRECORDDAO_H
#include <QString>
#include "crcfiletaskrecord.h"
#include "searchcondition.h"
class DBCRCFileTaskRecordDAO
{
public:
    DBCRCFileTaskRecordDAO();
    ~DBCRCFileTaskRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    CRCFileTaskRecord::List doQuery(bool *ok=0);
    CRCFileTaskRecord::List doQuery(SearchCondition::List &lst, bool *ok=0);
    CRCFileTaskRecord::Ptr  doQueryDevNewest(const QString &iedName, bool *ok=0);
    CRCFileTaskRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool doInsert(CRCFileTaskRecord::List &lst);
public:
    bool ackRecord(CRCFileTaskRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBCRCFILETASKRECORDDAO_H
