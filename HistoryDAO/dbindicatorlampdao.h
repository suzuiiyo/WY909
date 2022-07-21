#ifndef DBINDICATORLAMPDAO_H
#define DBINDICATORLAMPDAO_H
#include <QSqlDatabase>
#include <QString>
#include "indicatorlamp.h"
class DBIndicatorLampDAO
{
public:
    DBIndicatorLampDAO();
    ~DBIndicatorLampDAO();
public:
    IndicatorLamp::List doQuery(bool *ok=0);
    IndicatorLamp::Ptr doQueryByDataRef(const QString &dataRef, bool *ok=0);
    IndicatorLamp::List doQuery(const QString &iedName, bool *ok=0);
public:
    IndicatorLamp::List doQuery(QSqlDatabase db, bool *ok=0);
    IndicatorLamp::Ptr doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    IndicatorLamp::List doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);
public:
    bool doInsert(IndicatorLamp::List &lst);
public:
    bool doUpdate(const IndicatorLamp::Ptr &ptr);
    bool doUpdate(IndicatorLamp::List &lst);
public:
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByIedName(const QString &iedName);
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBINDICATORLAMPDAO_H
