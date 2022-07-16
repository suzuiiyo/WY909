#ifndef SETTING_H
#define SETTING_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class Setting
{
public:
    typedef QSharedPointer<Setting> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    Setting();
    ~Setting();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataSet() const;
    QString dataSetDesc() const;
    QString dimension() const;
    QString settingType() const;
    float maxSetting() const;
    float minSetting() const;
    float referenceValue() const;
    float stepSize() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataSet(const QString &dataSet);
    void setDataSetDesc(const QString &dataSetDesc);
    void setDimension(const QString &dimension);
    void setSettingType(const QString &settingType);
    void setMaxSetting(float maxSetting);
    void setMinSetting(float minSetting);
    void setReferenceValue(float referenceValue);
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
    QString m_settingType;
    float m_maxSetting;
    float m_minSetting;
    float m_referenceValue;
    float m_stepSize;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBSettingDAO;
};

inline int Setting::GUID() const
{ return m_GUID;}

inline void Setting::setGUID(int guid)
{ m_GUID = guid;}

inline QString Setting::iedName() const
{ return m_iedName;}

inline void Setting::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString Setting::dataRef() const
{ return m_dataRef;}

inline void Setting::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString Setting::dataDesc() const
{ return m_dataDesc;}

inline void Setting::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString Setting::settingType() const
{ return m_settingType;}

inline void Setting::setSettingType(const QString &settingType)
{ m_settingType = settingType;}

inline QString Setting::dataSet() const
{ return m_dataSet;}

inline void Setting::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString Setting::dataSetDesc() const
{ return m_dataSetDesc;}

inline void Setting::setDataSetDesc(const QString &dataSetDesc)
{ m_dataSetDesc = dataSetDesc;}

inline QString Setting::dimension() const
{ return m_dimension;}

inline void Setting::setDimension(const QString &dimension)
{ m_dimension = dimension;}

inline float Setting::referenceValue() const
{ return m_referenceValue;}

inline void Setting::setReferenceValue(float referenceValue)
{ m_referenceValue = referenceValue;}

inline float Setting::maxSetting() const
{ return m_maxSetting;}

inline void Setting::setMaxSetting(float maxSetting)
{ m_maxSetting = maxSetting;}

inline float Setting::minSetting() const
{ return m_minSetting;}

inline void Setting::setMinSetting(float minSetting)
{ m_minSetting = minSetting;}

inline float Setting::stepSize() const
{ return m_stepSize;}

inline void Setting::setStepSize(float stepSize)
{ m_stepSize = stepSize;}

inline const QStringList &Setting::lstDataValue() const
{ return m_lstDataValue;}

inline void Setting::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &Setting::lstDataType() const
{ return m_lstDataType;}

inline void Setting::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & Setting::lstDAStruct() const
{ return m_lstDAStruct;}

inline void Setting::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // SETTING_H
