#ifndef DBIEDDATASETDAO_H
#define DBIEDDATASETDAO_H
#include <QSqlDatabase>
#include <QString>
#include "ieddataset.h"
#include "memoryfcda.h"
//#include "ied.h"
class DBIedDataSetDAO
{
public:
    DBIedDataSetDAO();
    ~DBIedDataSetDAO();
public:
    int select_guid(const QString &dataRef, bool *ok=0);
    IedDataSet::List doQuery(bool *ok=0);
    IedDataSet::List doQueryByDataRef(const QString &dataRef, bool *ok=0);
    IedDataSet::List doQueryByIedName(const QString &iedName, bool *ok=0);//根据iedName,查看该设备对应的数据信息
    IedDataSet::List doQueryByLDevice(const QString &iedName, const QString &LDevice, bool *ok=0);//查询设备指定节点下的数据信息
    IedDataSet::List doQueryByDataSet(const QString &iedName, const QString &dataSet, bool *ok=0);//查询设备指定数据集下的数据信息
    IedDataSet::List doQueryByDataType(const QString &iedName, const QString &dataType, bool *ok=0);//查询设备指定数据类型下的数据信息
    IedDataSet::List doQueryByDevName(const QString &devName, bool *ok=0);
    IedDataSet::List doQueryByEarlyWarningType(const QString &iedName, int earlyWarningType, bool *ok=0);
    IedDataSet::List doQuerySet(const QString &iedName, const QString &setType, bool *ok=0);//查询设备所有数据集名称
    //IedDataSet::List selectDataInfoBySetType(const QString &iedName, )
public:
    IedDataSet::List doQuery(QSqlDatabase db, bool *ok=0);
    IedDataSet::List doQueryByDataRef(QSqlDatabase db, const QString &dataRef, bool *ok=0);
    IedDataSet::List doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok=0);//根据iedName,查看该设备对应的数据信息
    IedDataSet::List doQueryByLDevice(QSqlDatabase db, const QString &iedName, const QString &LDevice, bool *ok=0);//查询设备指定节点下的数据信息
    IedDataSet::List doQueryByDataSet(QSqlDatabase db, const QString &iedName, const QString &dataSet, bool *ok=0);//查询设备指定数据集下的数据信息
    IedDataSet::List doQueryByDataType(QSqlDatabase db, const QString &iedName, const QString &dataType, bool *ok=0);//查询设备指定数据类型下的数据信息
    IedDataSet::List doQueryByEarlyWarningType(QSqlDatabase db, const QString &iedName, int earlyWarningType, bool *ok=0);
    IedDataSet::List doQueryByDevName(QSqlDatabase db, const QString &devName, bool *ok=0);
    IedDataSet::List doQuerySet(QSqlDatabase db, const QString &iedName, const QString &setType, bool *ok=0);//查询设备所有数据集名称
    MemoryFCDA::Hash doQueryMemoryFCDA(QSqlDatabase db, const QString &iedName, bool *ok=0);
public:
    bool doInsert(IedDataSet::List &lstIedDataSet);//将数据配置信息导入数据库
public:
    bool doUpdate(const IedDataSet::Ptr &iedDataSet);//更新一条数据配置信息
    bool doUpdate(IedDataSet::List &lstIedDataSet);//更新多条数据配置信息
    bool doUpdate(IedDataSet::List &lstIedDataSet, int type);
public:
    bool doDelete(int dataSetGUID);//根据数据GUID删除一条数据
    bool doDelete(QList<int> lstDataSetGUID);//根据数据GUID删除多条数据
    bool doDelete(const QString &iedName);//清空指定iedName的配置数据信息
    bool doDelete(QList<QString> &lstIedName);//清空多个iedName的配置数据信息
    bool doClear();//清空所有数据配置信息
    //bool doClear(IedDataSet::List &lstIedDataSet, int type);
    void doDeleteRelate(const QString &dataRef);
public:
    bool configBusiness();
public:
    bool doCreateTable();
private:
    IedDataSet::Hash doQueryByEarlyWarningTypeHash(const QString &iedName, int earlyWarningType, bool *ok=0);
private:
    QString m_connectionName;
};
#endif // DBIEDDATASETDAO_H
