#ifndef DBGOOSEREALDATADAO_H
#define DBGOOSEREALDATADAO_H
#include <QHash>
#include <QSqlDatabase>
//#include "gooseinfo.h"
#include "gooserealdata.h"
class DBGooseRealDataDAO
{
public:
    DBGooseRealDataDAO();
    ~DBGooseRealDataDAO();
public:
    quint32 appIdInt(const QString &appId);
    QString appIdString16(qint32 appId);
    QString appIdString(qint32 appId);
//    quint32 appIdStr16ToInt10(const QString &str);
//    quint32 appIdInt10ToStr16(qint32 appId);
public:
    QHash<quint32, GooseRealData::Hash> doQuery(bool *ok=0);
    QHash<quint32, GooseRealData::Hash> doQuery(QSqlDatabase db, bool *ok=0);
    GooseRealData::Ptr doQuery(const QString &dataRef, quint32 appId, bool *ok=0);
    GooseRealData::Ptr doQuery(QSqlDatabase db, const QString &dataRef, quint32 appId, bool *ok=0);
    GooseRealData::List doQuery(const QString &iedName, bool *ok=0);
public:
//    bool doInit();
//    bool doInit(QSqlDatabase db, QSqlDatabase dbR);
    bool doUpdate(GooseRealData::List &lst);
    bool doUpdate(QSqlDatabase db, GooseRealData::List &lst);
public:
    bool doInsert(GooseRealData::List &lst);
    bool doInsert(QSqlDatabase db, GooseRealData::List &lst);
    bool doClear();
    bool doClear(QSqlDatabase db);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBGOOSEREALDATADAO_H
