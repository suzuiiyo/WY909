#ifndef DBEARLYWARNINGRECORDDAO_H
#define DBEARLYWARNINGRECORDDAO_H
#include <QSqlDatabase>
#include <QString>
#include "earlywarningrecord.h"
#include "searchcondition.h"
class DBEarlyWarningRecordDAO
{
public:
    DBEarlyWarningRecordDAO();
    ~DBEarlyWarningRecordDAO();
public:
    int countRecord(const SearchCondition::Ptr &ptr, bool *ok=0);
public:
    EarlyWarningRecord::List doQuery(bool *ok=0);
    EarlyWarningRecord::List doQuery(QSqlDatabase db, bool *ok=0);
    EarlyWarningRecord::List doQuery(const SearchCondition::Ptr &ptr, bool *ok=0);
    //EarlyWarningRecord::List doQuery(QSqlDatabase db, SearchCondition::List &lst, bool *ok=0);
public:
    bool doUpdate(EarlyWarningRecord::List &lst);
    bool doUpdate(QSqlDatabase db, EarlyWarningRecord::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBEARLYWARNINGRECORDDAO_H
