#include "earlywarning.h"
EarlyWarning::EarlyWarning()
    : m_ewType(-1)
    , m_upLimitState(-1)
    , m_downLimitState(-1)
    , m_mutationState(-1)
    , m_lastCycleULState(-1)
    , m_lastCycleDLState(-1)
    , m_trendULState(-1)
    , m_trendDLState(-1)
    , m_upLimitStateEnable(-1)
    , m_downLimitStateEnable(-1)
    , m_mutationStateEnable(-1)
    , m_lastCycleULStateEnable(-1)
    , m_lastCycleDLStateEnable(-1)
    , m_trendULStateEnable(-1)
    , m_trendDLStateEnable(-1)
    , m_isMonitor(0)
{

}

EarlyWarning::~EarlyWarning()
{

}
