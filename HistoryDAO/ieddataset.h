#ifndef IEDDATASET_H
#define IEDDATASET_H
#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QVector>
#include "dastruct.h"
class IedDataSet
{
public:
    typedef QSharedPointer<IedDataSet> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    IedDataSet();
    IedDataSet(int earlyWarningType);
    IedDataSet(const QString &iedName, const QString &dataRef, const QString &dataDesc, const QString &LDevice, const QString &dataType, const QString &dataUnit);
    ~IedDataSet();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString LDevice() const;
    QString dataSet() const;
    QString dataSetDesc() const;
    QString dataType() const;
    QString dataUnit() const;
    int earlyWarningType() const;
    QString devName() const;
    QString business() const;
    QString dataValueType() const;
public:
    void setGUID(int GUID);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setLDevice(const QString &LDevice);
    void setDataSet(const QString &dataSet);
    void setDataSetDesc(const QString &dataSetDesc);
    void setDataType(const QString &dataType);
    void setDataUnit(const QString &dataUnit);
    void setEarlyWarningType(int earlyWarningType);
    void setDevName(const QString &devName);
    void setBusiness(const QString &business);
    void setDataValueType(const QString &dataValueType);
public:
    const QVector<DAStruct*> & lstDAStruct() const;
    void addDAStruct(DAStruct *daStruct);
    void setLstDAStruct(QVector<DAStruct*> &lstDAStruct);
    void removeDAStruct(DAStruct *daStruct);
    void clearDAStruct();
private:
    int m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_LDevice;
    QString m_dataSet;
    QString m_dataSetDesc;
    QString m_dataType;
    QString m_dataUnit;
    int m_earlyWarningType;
    QString m_devName;
    QString m_business;
    QString m_dataValueType;
private:
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBIedDataSetDAO;
};

inline int IedDataSet::GUID() const
{ return m_GUID;}

inline void IedDataSet::setGUID(int GUID)
{ m_GUID = GUID;}

inline QString IedDataSet::iedName() const
{ return m_iedName;}

inline void IedDataSet::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString IedDataSet::dataRef() const
{ return m_dataRef;}

inline void IedDataSet::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString IedDataSet::dataDesc() const
{ return m_dataDesc;}

inline void IedDataSet::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString IedDataSet::LDevice() const
{ return m_LDevice;}

inline void IedDataSet::setLDevice(const QString &LDevice)
{ m_LDevice = LDevice;}

inline QString IedDataSet::dataSet() const
{ return m_dataSet;}

inline void IedDataSet::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString IedDataSet::dataSetDesc() const
{ return m_dataSetDesc;}

inline void IedDataSet::setDataSetDesc(const QString &dataSetDesc)
{ m_dataSetDesc = dataSetDesc;}

inline QString IedDataSet::dataType() const
{ return m_dataType;}

inline void IedDataSet::setDataType(const QString &dataType)
{ m_dataType = dataType;}

inline QString IedDataSet::dataUnit() const
{ return m_dataUnit;}

inline void IedDataSet::setDataUnit(const QString &dataUnit)
{ m_dataUnit = dataUnit;}

inline int IedDataSet::earlyWarningType() const
{ return m_earlyWarningType;}

inline void IedDataSet::setEarlyWarningType(int earlyWarningType)
{ m_earlyWarningType = earlyWarningType;}

inline QString IedDataSet::devName() const
{ return m_devName;}

inline void IedDataSet::setDevName(const QString &devName)
{ m_devName = devName;}

inline QString IedDataSet::business() const
{ return m_business;}

inline void IedDataSet::setBusiness(const QString &business)
{ m_business = business;}

inline QString IedDataSet::dataValueType() const
{ return m_dataValueType;}

inline void IedDataSet::setDataValueType(const QString &dataValueType)
{ m_dataValueType = dataValueType;}

inline const QVector<DAStruct*> & IedDataSet::lstDAStruct() const
{ return m_lstDAStruct;}

inline void IedDataSet::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // IEDDATASET_H
