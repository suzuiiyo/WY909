#ifndef DBRCDFILEDAO_H
#define DBRCDFILEDAO_H
#include <QString>
#include <QSqlDatabase>
#include <QStringList>
#include "rcdfile.h"
#include "searchcondition.h"
class DBRcdFileDAO
{
public:
    DBRcdFileDAO();
    ~DBRcdFileDAO();
public:
    bool initWaveFileTable(QSqlDatabase db, const QStringList &lst);
public:
    RcdFile::List doQuery(const SearchCondition::Ptr &ptr);
    RcdFile::List doQuery(QSqlDatabase dbR, const SearchCondition::Ptr &ptr);
    RcdFile::List doQueryByIedName(QSqlDatabase dbR, const QString &iedName);
public:
    bool doInsert(RcdFile::List &lst);
    bool doInsert(QSqlDatabase dbR, RcdFile::List &lst);
public:
    bool doUpdate(RcdFile::List &lst);
    bool doUpdate(QSqlDatabase dbR, RcdFile::List &lst);
//public:
//    bool doDelete(RcdFile::List &lst);
//    bool doDelete(QSqlDatabase dbR, RcdFile::List &lst);
//    bool doDelete(const RcdFile::Ptr &ptr);
//    bool doDelete(QSqlDatabase dbR, const RcdFile::Ptr &ptr);
public:
    bool doClear();
    bool doClear(QSqlDatabase dbR);
private:
    QString m_connectionName;
};
#endif // DBRCDFILEDAO_H
