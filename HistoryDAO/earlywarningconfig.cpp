#include "earlywarningconfig.h"
EarlyWarningConfig::EarlyWarningConfig()
    : m_ewType(-1)
    , m_storageCycle(0)
    , m_maxValue(0)
    , m_minValue(0)
    , m_mutationValue(0)
    , m_upLimitState(0)
    , m_downLimitState(0)
    , m_mutationState(0)
    , m_lastCycleULState(0)
    , m_lastCycleDLState(0)
    , m_trendULState(0)
    , m_trendDLState(0)
    , m_upLimitStateEnable(0)
    , m_downLimitStateEnable(0)
    , m_mutationStateEnable(0)
    , m_lastCycleULStateEnable(0)
    , m_lastCycleDLStateEnable(0)
    , m_trendULStateEnable(0)
    , m_trendDLStateEnable(0)
    , m_isMonitor(0)
{

}

EarlyWarningConfig::~EarlyWarningConfig()
{
    clearDAStruct();
}

void EarlyWarningConfig::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void EarlyWarningConfig::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void EarlyWarningConfig::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void EarlyWarningConfig::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void EarlyWarningConfig::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
