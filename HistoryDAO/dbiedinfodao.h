#ifndef DBIEDINFODAO_H
#define DBIEDINFODAO_H
#include <QSqlDatabase>
#include <QString>
#include <QList>
#include "ied.h"
#include "memoryied.h"
class DBIedInfoDAO
{
public:
    DBIedInfoDAO();
    ~DBIedInfoDAO();
public:
    int select_guid(const QString &iedName, bool *ok=0);
    Ied::List doQuery(bool *ok=0);//检索所有二次设备信息
    Ied::List doQueryByStationName(const QString &stationName, bool *ok=0);//检索指定站下所有二次设备信息
    Ied::List doQueryByVoltClass(const QString &voltClass, bool *ok=0);//检索指定电压等级下二次设备信息
    Ied::List doQueryByVoltage(const QString &voltage, bool *ok=0);
    Ied::List doQueryByBayName(const QString &bayName, bool *ok=0);//检索指定间隔下二次设备信息
    Ied::Ptr doQuery(const QString &iedName, bool *ok=0);//检索指定二次设备信息
    Ied::List doQueryByVoltAndPort(const QString &voltClass, int portNetType, bool *ok=0);
    Ied *ied(const QString &iedName, bool *ok=0);
    QList<Ied*> doQueryLstByBayName(const QString &bayName, bool *ok=0);
    Ied::List doQueryByBayNameLike(const QString &bayName, bool *ok=0);//检索指定间隔下二次设备信息
    MemoryIed::Hash doQueryMemoryIed(bool *ok=0);
public:
    Ied::List doQuery(QSqlDatabase db, bool *ok=0);//检索所有二次设备信息
    Ied::List doQueryByStationName(QSqlDatabase db, const QString &stationName, bool *ok=0);//检索指定站下所有二次设备信息
    Ied::List doQueryByVoltClass(QSqlDatabase db, const QString &voltClass, bool *ok=0);//检索指定电压等级下二次设备信息
    Ied::List doQueryByVoltage(QSqlDatabase db, const QString &voltage, bool *ok=0);
    Ied::List doQueryByBayName(QSqlDatabase db, const QString &bayName, bool *ok=0);//检索指定间隔下二次设备信息
    Ied::Ptr doQuery(QSqlDatabase db, const QString &iedName, bool *ok=0);//检索指定二次设备信息
    Ied::List doQueryByVoltAndPort(QSqlDatabase db, const QString &voltClass, int portNetType, bool *ok=0);
    Ied *ied(QSqlDatabase db, const QString &iedName, bool *ok=0);
    QList<Ied*> doQueryLstByBayName(QSqlDatabase db, const QString &bayName, bool *ok=0);
    QList<Ied*> doQueryLst(QSqlDatabase db, bool *ok=0);
    Ied::List doQueryByBayNameLike(QSqlDatabase db, const QString &bayName, bool *ok=0);//检索指定间隔下二次设备信息
    MemoryIed::Hash doQueryMemoryIed(QSqlDatabase db, bool *ok=0);
public:
    QString getAllIed();
public:
    bool doInsert(Ied::List &lstIed);//插入多个二次设备信息
public:
    bool doUpdate(const Ied::Ptr &ied);//更新指定二次设备信息
    bool doUpdate(Ied::List &lstIed);//更新多个二次设备信息
    bool doUpdate(Ied::List &lst, int type);
public:
    bool doDelete(int iedGUID);//根据设备GUID删除指定二次设备信息
    bool doDelete(QList<int> lstIedGUID);//根据二次设备GUID删除多个二次设备信息
    bool doClear();//清空所有二次设备信息
    void doDeleteRelate(const QString &iedName);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBIEDINFODAO_H
