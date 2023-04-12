#ifndef DBSOFTVERSIONDAO_H
#define DBSOFTVERSIONDAO_H
#include <QString>
#include <QSqlDatabase>
#include <QHash>
#include "softversion.h"
class DBSoftVersionDAO
{
public:
    DBSoftVersionDAO();
    ~DBSoftVersionDAO();
public:
    SoftVersion::List doQuery(bool needDAStruct=false);
    SoftVersion::List doQueryByIedName(const QString &iedName, bool needDAStruct=false);
    SoftVersion::Ptr doQueryBySelfType(const QString &iedName, int type, bool needDAStruct=false);
    SoftVersion::List doQueryByBayName(const QString &bayName, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByVoltage(const QString &voltage, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByVoltClass(const QString &voltClass, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByStationName(const QString &stationName, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByBayName(const QString &bayName, const QString &iedCateGory, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByVoltage(const QString &voltage, const QString &iedCateGory, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByVoltClass(const QString &voltClass, const QString &iedCateGory,  int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByStationName(const QString &stationName, const QString &iedCateGory,  int type = -1, bool needDAStruct=false);
public:
    SoftVersion::List doQuery(QSqlDatabase db, bool needDAStruct=false);
    SoftVersion::List doQueryByIedName(QSqlDatabase db, const QString &iedName, bool needDAStruct=false);
    SoftVersion::Ptr doQueryBySelfType(QSqlDatabase db, const QString &iedName, int type, bool needDAStruct=false);
    SoftVersion::List doQueryByBayName(QSqlDatabase db, const QString &bayName, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByVoltage(QSqlDatabase db, const QString &voltage, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByVoltClass(QSqlDatabase db, const QString &voltClass, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByStationName(QSqlDatabase db, const QString &stationName, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByBayName(QSqlDatabase db, const QString &bayName, const QString &iedCateGory, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByVoltage(QSqlDatabase db, const QString &voltage, const QString &iedCateGory, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByVoltClass(QSqlDatabase db, const QString &voltClass, const QString &iedCateGory, int type = -1, bool needDAStruct=false);
    SoftVersion::List doQueryByStationName(QSqlDatabase db, const QString &stationName, const QString &iedCateGory, int type = -1, bool needDAStruct=false);
public:
    bool doInsert(SoftVersion::List &lst);
public:
    bool doUpdate(SoftVersion::List &lst);
    bool doUpdate(const QString &iedName, int type, const QString &dataValue);
public:
    bool doDelete(SoftVersion::List &lst);
    bool doDelete(const QString &iedName);
    bool doDelete(const QString &iedName, int type);
public:
    bool doClear();
public:
    bool doCreateTable();
public:
    QHash<QString, QHash<int, int>> relation();
private:
    QHash<QString, QHash<int, int>> m_relationHash;
    QString m_connectionName;
};
#endif // DBSOFTVERSIONDAO_H
