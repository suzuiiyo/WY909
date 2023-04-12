#ifndef DBDASTRUCTDAO_H
#define DBDASTRUCTDAO_H
#include <QSqlDatabase>
#include <QString>
#include <QVector>
#include <QHash>
#include "dastruct.h"
class DBDAStructDAO
{
public:
    DBDAStructDAO();
    ~DBDAStructDAO();
public:
    DAStruct::List doQuery(bool *ok=0);
    DAStruct::List doQueryByIedName(const QString &iedName, bool *ok=0);
    DAStruct::List doQueryByDataRef(const QString &dataRef, bool *ok=0);
    DAStruct::Ptr doQueryByAttributeRef(const QString &attributeRef, bool *ok=0);
    QVector<DAStruct*> doQueryVec(const QString &dataRef, bool *ok=0);
    QHash<QString, DAStruct::List> doQueryHash(const QStringList &lst, bool *ok=0);
public:
    DAStruct::List doQuery(QSqlDatabase db, bool *ok=0);
    DAStruct::List doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok=0);
    DAStruct::List doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    DAStruct::Ptr doQueryByAttributeRef(QSqlDatabase db, const QString &attributeRef, bool *ok=0);
    QVector<DAStruct*> doQueryVec(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    QHash<QString, DAStruct::List> doQueryHash(QSqlDatabase db, const QStringList &lst, bool *ok=0);
public:
    bool doInsert(DAStruct::List &lst);
public:
    bool doUpdate(const DAStruct::Ptr &ptr);
    bool doUpdate(DAStruct::List &lst);
public:
    bool doDeleteByIedName(const QString &iedName);
    bool doDeleteByDataRef(const QString &dataRef);
    bool doDeleteByDataAttributeRef(const QString &dataAttributeRef);
public:
    bool doClear();
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBDASTRUCTDAO_H
