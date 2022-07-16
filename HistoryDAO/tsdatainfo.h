#ifndef TSDATAINFO_H
#define TSDATAINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class TSDataInfo
{
public:
    typedef QSharedPointer<TSDataInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    TSDataInfo();
    ~TSDataInfo();
public:
    int GUID() const;
//    int dataType() const;
//    QString dataValue() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataSet() const;
    QString dataSetDesc() const;
public:
    void setGUID(int guid);
//    void setDataType(int dataType);
//    void setDataValue(const QString &dataValue);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataSet(const QString &dataSet);
    void setDataSetDesc(const QString &dataSetDesc);
public:
    const QStringList & lstDataValue() const;
    const QList<int> & lstDataType() const;
    void addDataValue(const QString &dataValue);
    void addDataType(int dataType);
    void clearDataValue();
    void clearDataType();
public:
    const QVector<DAStruct*> & lstDAStruct() const;
    void addDAStruct(DAStruct *daStruct);
    void setLstDAStruct(QVector<DAStruct*> &lstDAStruct);
    void removeDAStruct(DAStruct *daStruct);
    void clearDAStruct();
private:
    int m_GUID;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dataSet;
    QString m_dataSetDesc;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBTSDataInfoDAO;
};

inline int TSDataInfo::GUID() const
{ return m_GUID;}

inline void TSDataInfo::setGUID(int guid)
{ m_GUID = guid;}

//inline int TSDataInfo::dataType() const
//{ return m_dataType;}

//inline void TSDataInfo::setDataType(int dataType)
//{ m_dataType = dataType;}

//inline QString TSDataInfo::dataValue() const
//{ return m_dataValue;}

//inline void TSDataInfo::setDataValue(const QString &dataValue)
//{ m_dataValue = dataValue;}

inline QString TSDataInfo::iedName() const
{ return m_iedName;}

inline void TSDataInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString TSDataInfo::dataRef() const
{ return m_dataRef;}

inline void TSDataInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString TSDataInfo::dataDesc() const
{ return m_dataDesc;}

inline void TSDataInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString TSDataInfo::dataSet() const
{ return m_dataSet;}

inline void TSDataInfo::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString TSDataInfo::dataSetDesc() const
{ return m_dataSetDesc;}

inline void TSDataInfo::setDataSetDesc(const QString &dataSetDesc)
{ m_dataSetDesc = dataSetDesc;}

inline const QStringList &TSDataInfo::lstDataValue() const
{ return m_lstDataValue;}

inline void TSDataInfo::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &TSDataInfo::lstDataType() const
{ return m_lstDataType;}

inline void TSDataInfo::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & TSDataInfo::lstDAStruct() const
{ return m_lstDAStruct;}

inline void TSDataInfo::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // TSDATAINFO_H
