#ifndef DBTRANSIENTTASKCONCLUSIONRECORDDAO_H
#define DBTRANSIENTTASKCONCLUSIONRECORDDAO_H
#include <QSqlDatabase>
#include <QString>
#include "transienttaskconclusionrecord.h"
#include "searchcondition.h"
#include "dborm.h"
#include "dbcondition.h"
class DBTransientTaskConclusionRecordDAO
{
public:
    DBTransientTaskConclusionRecordDAO();
    ~DBTransientTaskConclusionRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
    //int countRecord(const SearchCondition::Ptr &ptr, QSqlDatabase db, bool *ok=0);
public:
    TransientTaskConclusionRecord::List doQuery(bool *ok=0);
    TransientTaskConclusionRecord::List doQuery(QSqlDatabase db, bool *ok=0);
    TransientTaskConclusionRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    TransientTaskConclusionRecord::List doQuery(DBOrmOperation::List &lst, bool *ok=0);
    //TransientTaskConclusionRecord::List doQuery();
    //TransientTaskConclusionRecord::List doQuery(QSqlDatabase db, const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    bool doInsert(const TransientTaskConclusionRecord::Ptr &ptr);
    bool doInsert(QSqlDatabase db, const TransientTaskConclusionRecord::Ptr &ptr);
    bool doInsert(TransientTaskConclusionRecord::List &lst);
    bool doInsert(QSqlDatabase db, TransientTaskConclusionRecord::List &lst);
    bool doUpdate(TransientTaskConclusionRecord::List &lst);
public:
    bool ackRecord(TransientTaskConclusionRecord::List &lst);
public:
    bool doCreateTable();
//    bool doUpdate(QSqlDatabase db, TransientTaskConclusionRecord::List &lst);
private:
    QString     m_connectionName;
    DBOrm::Ptr  m_ptrOrm;
};
#endif // DBTRANSIENTTASKCONCLUSIONRECORDDAO_H
