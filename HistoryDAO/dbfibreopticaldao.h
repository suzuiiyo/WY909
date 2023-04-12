#ifndef DBFIBREOPTICALDAO_H
#define DBFIBREOPTICALDAO_H
#include <QSqlDatabase>
#include <QString>
#include "fibreoptical.h"
class DBFibreOpticalDAO
{
public:
    DBFibreOpticalDAO();
    ~DBFibreOpticalDAO();
public:
    FibreOptical::List doQuery(bool *ok=0);
    FibreOptical::List doQueryByIedName(const QString &iedName, bool *ok=0);
    FibreOptical::Ptr doQueryByLineRef(const QString &lineRef, bool *ok=0);
    FibreOptical::Ptr doQueryByPortID(const QString &portID, bool *ok=0);
public:
    FibreOptical::List doQuery(QSqlDatabase db, bool *ok=0);
    FibreOptical::List doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok=0);
    FibreOptical::Ptr doQueryByLineRef(QSqlDatabase db, const QString &lineRef, bool *ok=0);
    FibreOptical::Ptr doQueryByPortID(QSqlDatabase db, const QString &portID, bool *ok=0);
public:
    FibreOptical *line(const QString &portID1, const QString &portID2, bool *ok=0);
    FibreOptical *line(const QString &lineRef, bool *ok=0);
    FibreOptical *line(QSqlDatabase db, const QString &portID1, const QString &portID2, bool *ok=0);
    FibreOptical *line(QSqlDatabase db, const QString &lineRef, bool *ok=0);
public:
    bool doInsert(FibreOptical::List &lst);
public:
    bool doUpdate(const FibreOptical::Ptr &ptr);
    bool doUpdate(FibreOptical::List &lst);
public:
    bool doDeleteByLineRef(const QString &lineRef);
    bool doDeleteByIedName(const QString &iedName);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBFIBREOPTICALDAO_H
