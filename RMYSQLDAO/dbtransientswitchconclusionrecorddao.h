#ifndef DBTRANSIENTSWITCHCONCLUSIONRECORDDAO_H
#define DBTRANSIENTSWITCHCONCLUSIONRECORDDAO_H
#include <QSqlDatabase>
#include <QString>
#include "transientswitchtaskconclusionrecord.h"
#include "searchcondition.h"
#include "dborm.h"
#include "dbcondition.h"
class DBTransientSwitchConclusionRecordDAO
{
public:
    DBTransientSwitchConclusionRecordDAO();
    ~DBTransientSwitchConclusionRecordDAO();

public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
    //int countReord(const SearchCondition::Ptr &ptr, QSqlDatabase db, bool *ok=0);

public:
    TransientSwitchTaskConclusionRecord::List doQuery(bool *ok=0);
    TransientSwitchTaskConclusionRecord::List doQuery(QSqlDatabase db, bool *ok=0);
    TransientSwitchTaskConclusionRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);

public:
    TransientSwitchTaskConclusionRecord::List doQuery(DBOrmOperation::List &lst, bool *ok=0);
    //TransientSwitchTaskConclusionRecord::List doQuery();
    //TransientSwitchTaskConclusionRecord::List doQuery(QSqlDatabase db, const SearchCondition::Ptr &ptr, bool *ok=0);

public:
    bool doInsert(const TransientSwitchTaskConclusionRecord::Ptr &ptr);
    bool doInsert(QSqlDatabase db, const TransientSwitchTaskConclusionRecord::Ptr &ptr);
    bool doInsert(TransientSwitchTaskConclusionRecord::List &lst);
    bool doInsert(QSqlDatabase db, const TransientSwitchTaskConclusionRecord::List &lst);
    bool doUpdate(const TransientSwitchTaskConclusionRecord::List &lst);

public:
    bool ackRecord(TransientSwitchTaskConclusionRecord::List &lst);
public:
    bool doCreateTable();
//    bool doUpdate(QSqlDatabase db, TransientSwitchTaskConclusionRecord::List &lst);
private:
    QString m_connectionName;
    DBOrm::Ptr m_ptrOrm;
};

#endif // DBTRANSIENTSWITCHCONCLUSIONRECORDDAO_H
