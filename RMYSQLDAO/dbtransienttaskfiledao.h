#ifndef DBTRANSIENTTASKFILEDAO_H
#define DBTRANSIENTTASKFILEDAO_H
#include <QString>
#include "searchcondition.h"
#include "transienttaskfile.h"
class DBTransientTaskFileDAO
{
public:
    DBTransientTaskFileDAO();
    ~DBTransientTaskFileDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    TransientTaskFile::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool doInsert(const QString &fileName);
private:
    QString m_connectionName;
};
#endif // DBTRANSIENTTASKFILEDAO_H
