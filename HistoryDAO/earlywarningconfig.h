#ifndef EARLYWARNINGCONFIG_H
#define EARLYWARNINGCONFIG_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class EarlyWarningConfig
{
public:
    typedef QSharedPointer<EarlyWarningConfig> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    EarlyWarningConfig();
    ~EarlyWarningConfig();
public:
    int GUID() const;
    int ewType() const;
    int storageCycle() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataUnit() const;
    int upLimitState() const;
    int downLimitState() const;
    int mutationState() const;
    int lastCycleULState() const;
    int lastCycleDLState() const;
    int trendULState() const;
    int trendDLState() const;
    int upLimitStateEnable() const;
    int downLimitStateEnable() const;
    int mutationStateEnable() const;
    int lastCycleULStateEnable() const;
    int lastCycleDLStateEnable() const;
    int trendULStateEnable() const;
    int trendDLStateEnable() const;
    float maxValue() const;
    float minValue() const;
    float mutationValue() const;
    int isMonitor() const;
public:
    void setGUID(int guid);
    void setEwType(int ewType);
    void setStorageCycle(int storageCycle);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataUnit(const QString &dataUnit);
    void setUpLimitState(int upLimitState);
    void setDownLimitState(int downLimitState);
    void setMutationState(int mutationState);
    void setLastCycleULState(int lastCycleULState);
    void setLastCycleDLState(int lastCycleDLState);
    void setTrendULState(int trendULState);
    void setTrendDLState(int trendDLState);
    void setUpLimitStateEnable(int upLimitStateEnable);
    void setDownLimitStateEnable(int downLimitStateEnable);
    void setMutationStateEnable(int mutationStateEnable);
    void setLastCycleULStateEnable(int lastCycleULStateEnable);
    void setLastCycleDLStateEnable(int lastCycleDLStateEnable);
    void setTrendULStateEnable(int trendULStateEnable);
    void setTrendDLStateEnable(int trendDLStateEnable);
    void setMaxValue(float maxValue);
    void setMinValue(float minValue);
    void setMutationValue(float mutationValue);
    void setIsMonitor(int isMonitor);
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
    int m_ewType;
    int m_storageCycle;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dataUnit;
    float m_maxValue;
    float m_minValue;
    float m_mutationValue;
    int m_upLimitState;
    int m_downLimitState;
    int m_mutationState;
    int m_lastCycleULState;
    int m_lastCycleDLState;
    int m_trendULState;
    int m_trendDLState;
    int m_upLimitStateEnable;
    int m_downLimitStateEnable;
    int m_mutationStateEnable;
    int m_lastCycleULStateEnable;
    int m_lastCycleDLStateEnable;
    int m_trendULStateEnable;
    int m_trendDLStateEnable;
    int m_isMonitor;
    QVector<DAStruct*> m_lstDAStruct;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
private:
    friend class DBEarlyWarningConfigDAO;
};

inline int EarlyWarningConfig::GUID() const
{ return m_GUID;}

inline void EarlyWarningConfig::setGUID(int guid)
{ m_GUID = guid;}

inline int EarlyWarningConfig::ewType() const
{ return m_ewType;}

inline void EarlyWarningConfig::setEwType(int ewType)
{ m_ewType = ewType;}

inline int EarlyWarningConfig::storageCycle() const
{ return m_storageCycle;}

inline void EarlyWarningConfig::setStorageCycle(int storageCycle)
{ m_storageCycle = storageCycle;}

inline QString EarlyWarningConfig::iedName() const
{ return m_iedName;}

inline void EarlyWarningConfig::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString EarlyWarningConfig::dataRef() const
{ return m_dataRef;}

inline void EarlyWarningConfig::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString EarlyWarningConfig::dataDesc() const
{ return m_dataDesc;}

inline void EarlyWarningConfig::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString EarlyWarningConfig::dataUnit() const
{ return m_dataUnit;}

inline void EarlyWarningConfig::setDataUnit(const QString &dataUnit)
{ m_dataUnit = dataUnit;}

inline int EarlyWarningConfig::upLimitState() const
{ return m_upLimitState;}

inline void EarlyWarningConfig::setUpLimitState(int upLimitState)
{ m_upLimitState = upLimitState;}

inline int EarlyWarningConfig::downLimitState() const
{ return m_downLimitState;}

inline void EarlyWarningConfig::setDownLimitState(int downLimitState)
{ m_downLimitState = downLimitState;}

inline int EarlyWarningConfig::mutationState() const
{ return m_mutationState;}

inline void EarlyWarningConfig::setMutationState(int mutationState)
{ m_mutationState = mutationState;}

inline int EarlyWarningConfig::lastCycleULState() const
{ return m_lastCycleULState;}

inline void EarlyWarningConfig::setLastCycleULState(int lastCycleULState)
{ m_lastCycleULState = lastCycleULState;}

inline int EarlyWarningConfig::lastCycleDLState() const
{ return m_lastCycleDLState;}

inline void EarlyWarningConfig::setLastCycleDLState(int lastCycleDLState)
{ m_lastCycleDLState = lastCycleDLState;}

inline int EarlyWarningConfig::trendULState() const
{ return m_trendULState;}

inline void EarlyWarningConfig::setTrendULState(int trendULState)
{ m_trendULState = trendULState;}

inline int EarlyWarningConfig::trendDLState() const
{ return m_trendDLState;}

inline void EarlyWarningConfig::setTrendDLState(int trendDLState)
{ m_trendDLState = trendDLState;}

inline float EarlyWarningConfig::maxValue() const
{ return m_maxValue;}

inline void EarlyWarningConfig::setMaxValue(float maxValue)
{ m_maxValue = maxValue;}

inline float EarlyWarningConfig::minValue() const
{ return m_minValue;}

inline void EarlyWarningConfig::setMinValue(float minValue)
{ m_minValue = minValue;}

inline float EarlyWarningConfig::mutationValue() const
{ return m_mutationValue;}

inline void EarlyWarningConfig::setMutationValue(float mutationValue)
{ m_mutationValue = mutationValue;}

inline int EarlyWarningConfig::upLimitStateEnable() const
{ return m_upLimitStateEnable;}

inline void EarlyWarningConfig::setUpLimitStateEnable(int upLimitStateEnable)
{ m_upLimitStateEnable = upLimitStateEnable;}

inline int EarlyWarningConfig::downLimitStateEnable() const
{ return m_downLimitStateEnable;}

inline void EarlyWarningConfig::setDownLimitStateEnable(int downLimitStateEnable)
{ m_downLimitStateEnable = downLimitStateEnable;}

inline int EarlyWarningConfig::mutationStateEnable() const
{ return m_mutationStateEnable;}

inline void EarlyWarningConfig::setMutationStateEnable(int mutationStateEnable)
{ m_mutationStateEnable = mutationStateEnable;}

inline int EarlyWarningConfig::lastCycleULStateEnable() const
{ return m_lastCycleULStateEnable;}

inline void EarlyWarningConfig::setLastCycleULStateEnable(int lastCycleULStateEnable)
{ m_lastCycleULStateEnable = lastCycleULStateEnable;}

inline int EarlyWarningConfig::lastCycleDLStateEnable() const
{ return m_lastCycleDLStateEnable;}

inline void EarlyWarningConfig::setLastCycleDLStateEnable(int lastCycleDLStateEnable)
{ m_lastCycleDLStateEnable = lastCycleDLStateEnable;}

inline int EarlyWarningConfig::trendULStateEnable() const
{ return m_trendULStateEnable;}

inline void EarlyWarningConfig::setTrendULStateEnable(int trendULStateEnable)
{ m_trendULStateEnable = trendULStateEnable;}

inline int EarlyWarningConfig::trendDLStateEnable() const
{ return m_trendDLStateEnable;}

inline void EarlyWarningConfig::setTrendDLStateEnable(int trendDLStateEnable)
{ m_trendDLStateEnable = trendDLStateEnable;}

inline int EarlyWarningConfig::isMonitor() const
{ return m_isMonitor;}

inline void EarlyWarningConfig::setIsMonitor(int isMonitor)
{ m_isMonitor = isMonitor;}

inline const QStringList &EarlyWarningConfig::lstDataValue() const
{ return m_lstDataValue;}

inline void EarlyWarningConfig::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &EarlyWarningConfig::lstDataType() const
{ return m_lstDataType;}

inline void EarlyWarningConfig::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & EarlyWarningConfig::lstDAStruct() const
{ return m_lstDAStruct;}

inline void EarlyWarningConfig::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // EARLYWARNINGCONFIG_H
