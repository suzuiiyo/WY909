#ifndef TMDATAINFO_H
#define TMDATAINFO_H
#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class TMDataInfo
{
public:
    typedef QSharedPointer<TMDataInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    TMDataInfo();
    ~TMDataInfo();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataSet() const;
    QString dataSetDesc() const;
    QString dimension() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataSet(const QString &dataSet);
    void setDataSetDesc(const QString &dataSetDesc);
    void setDimension(const QString &dimension);
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
    int m_dataType;
    QString m_dataValue;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dataSet;
    QString m_dataSetDesc;
    QString m_dimension;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBTMDataInfoDAO;
};

inline int TMDataInfo::GUID() const
{ return m_GUID;}

inline void TMDataInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString TMDataInfo::iedName() const
{ return m_iedName;}

inline void TMDataInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString TMDataInfo::dataRef() const
{ return m_dataRef;}

inline void TMDataInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString TMDataInfo::dataDesc() const
{ return m_dataDesc;}

inline void TMDataInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString TMDataInfo::dataSet() const
{ return m_dataSet;}

inline void TMDataInfo::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString TMDataInfo::dataSetDesc() const
{ return m_dataSetDesc;}

inline void TMDataInfo::setDataSetDesc(const QString &dataSetDesc)
{ m_dataSetDesc = dataSetDesc;}

inline QString TMDataInfo::dimension() const
{ return m_dimension;}

inline void TMDataInfo::setDimension(const QString &dimension)
{ m_dimension = dimension;}

inline const QStringList &TMDataInfo::lstDataValue() const
{ return m_lstDataValue;}

inline void TMDataInfo::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &TMDataInfo::lstDataType() const
{ return m_lstDataType;}

inline void TMDataInfo::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & TMDataInfo::lstDAStruct() const
{ return m_lstDAStruct;}

inline void TMDataInfo::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // TMDATAINFO_H
