#ifndef OTHERDATAINFO_H
#define OTHERDATAINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class OtherDataInfo
{
public:
    typedef QSharedPointer<OtherDataInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    OtherDataInfo();
    ~OtherDataInfo();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataSet() const;
    QString dataSetDesc() const;
    QString dimension() const;
    float maxSetting() const;
    float minSetting() const;
    QString referenceValue() const;
    float stepSize() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataSet(const QString &dataSet);
    void setDataSetDesc(const QString &dataSetDesc);
    void setDimension(const QString &dimension);
    void setMaxSetting(float maxSetting);
    void setMinSetting(float minSetting);
    void setReferenceValue(const QString &referenceValue);
    void setStepSize(float stepSize);
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
    float m_maxSetting;
    float m_minSetting;
    QString m_referenceValue;
    float m_stepSize;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBOtherDataInfoDAO;
};

inline int OtherDataInfo::GUID() const
{ return m_GUID;}

inline void OtherDataInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString OtherDataInfo::iedName() const
{ return m_iedName;}

inline void OtherDataInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString OtherDataInfo::dataRef() const
{ return m_dataRef;}

inline void OtherDataInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString OtherDataInfo::dataDesc() const
{ return m_dataDesc;}

inline void OtherDataInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString OtherDataInfo::dataSet() const
{ return m_dataSet;}

inline void OtherDataInfo::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString OtherDataInfo::dataSetDesc() const
{ return m_dataSetDesc;}

inline void OtherDataInfo::setDataSetDesc(const QString &dataSetDesc)
{ m_dataSetDesc = dataSetDesc;}

inline QString OtherDataInfo::dimension() const
{ return m_dimension;}

inline void OtherDataInfo::setDimension(const QString &dimension)
{ m_dimension = dimension;}

inline float OtherDataInfo::maxSetting() const
{ return m_maxSetting;}

inline void OtherDataInfo::setMaxSetting(float maxSetting)
{ m_maxSetting = maxSetting;}

inline float OtherDataInfo::minSetting() const
{ return m_minSetting;}

inline void OtherDataInfo::setMinSetting(float minSetting)
{ m_minSetting = minSetting;}

inline QString OtherDataInfo::referenceValue() const
{ return m_referenceValue;}

inline void OtherDataInfo::setReferenceValue(const QString &referenceValue)
{ m_referenceValue = referenceValue;}

inline float OtherDataInfo::stepSize() const
{ return m_stepSize;}

inline void OtherDataInfo::setStepSize(float stepSize)
{ m_stepSize = stepSize;}

inline const QStringList &OtherDataInfo::lstDataValue() const
{ return m_lstDataValue;}

inline void OtherDataInfo::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &OtherDataInfo::lstDataType() const
{ return m_lstDataType;}

inline void OtherDataInfo::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & OtherDataInfo::lstDAStruct() const
{ return m_lstDAStruct;}

inline void OtherDataInfo::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // OTHERDATAINFO_H
