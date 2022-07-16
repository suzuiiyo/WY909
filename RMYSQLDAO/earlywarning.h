#ifndef EARLYWARNING_H
#define EARLYWARNING_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class EarlyWarning
{
public:
    typedef QSharedPointer<EarlyWarning> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    EarlyWarning();
    ~EarlyWarning();
public:
    QString dataRef() const;
    int ewType() const;
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
    int isMonitor() const;
public:
    void setDataRef(const QString &dataRef);
    void setEwType(int ewType);
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
    void setIsMoniter(int isMonitor);
private:
    QString m_dataRef;
    int m_ewType;
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
private:
    friend class DBEarlyWarningDAO;
};

inline QString EarlyWarning::dataRef() const
{ return m_dataRef;}

inline void EarlyWarning::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline int EarlyWarning::ewType() const
{ return m_ewType;}

inline void EarlyWarning::setEwType(int ewType)
{ m_ewType = ewType;}

inline int EarlyWarning::upLimitState() const
{ return m_upLimitState;}

inline void EarlyWarning::setUpLimitState(int upLimitState)
{ m_upLimitState = upLimitState;}

inline int EarlyWarning::downLimitState() const
{ return m_downLimitState;}

inline void EarlyWarning::setDownLimitState(int downLimitState)
{ m_downLimitState = downLimitState;}

inline int EarlyWarning::mutationState() const
{ return m_mutationState;}

inline void EarlyWarning::setMutationState(int mutationState)
{ m_mutationState = mutationState;}

inline int EarlyWarning::lastCycleULState() const
{ return m_lastCycleULState;}

inline void EarlyWarning::setLastCycleULState(int lastCycleULState)
{ m_lastCycleULState = lastCycleULState;}

inline int EarlyWarning::lastCycleDLState() const
{ return m_lastCycleDLState;}

inline void EarlyWarning::setLastCycleDLState(int lastCycleDLState)
{ m_lastCycleDLState = lastCycleDLState;}

inline int EarlyWarning::trendULState() const
{ return m_trendULState;}

inline void EarlyWarning::setTrendULState(int trendULState)
{ m_trendULState = trendULState;}

inline int EarlyWarning::trendDLState() const
{ return m_trendDLState;}

inline void EarlyWarning::setTrendDLState(int trendDLState)
{ m_trendDLState = trendDLState;}

inline int EarlyWarning::upLimitStateEnable() const
{ return m_upLimitStateEnable;}

inline void EarlyWarning::setUpLimitStateEnable(int upLimitStateEnable)
{ m_upLimitStateEnable = upLimitStateEnable;}

inline int EarlyWarning::downLimitStateEnable() const
{ return m_downLimitStateEnable;}

inline void EarlyWarning::setDownLimitStateEnable(int downLimitStateEnable)
{ m_downLimitStateEnable = downLimitStateEnable;}

inline int EarlyWarning::mutationStateEnable() const
{ return m_mutationStateEnable;}

inline void EarlyWarning::setMutationStateEnable(int mutationStateEnable)
{ m_mutationStateEnable = mutationStateEnable;}

inline int EarlyWarning::lastCycleULStateEnable() const
{ return m_lastCycleULStateEnable;}

inline void EarlyWarning::setLastCycleULStateEnable(int lastCycleULStateEnable)
{ m_lastCycleULStateEnable = lastCycleULStateEnable;}

inline int EarlyWarning::lastCycleDLStateEnable() const
{ return m_lastCycleDLStateEnable;}

inline void EarlyWarning::setLastCycleDLStateEnable(int lastCycleDLStateEnable)
{ m_lastCycleDLStateEnable = lastCycleDLStateEnable;}

inline int EarlyWarning::trendULStateEnable() const
{ return m_trendULStateEnable;}

inline void EarlyWarning::setTrendULStateEnable(int trendULStateEnable)
{ m_trendULStateEnable = trendULStateEnable;}

inline int EarlyWarning::trendDLStateEnable() const
{ return m_trendDLStateEnable;}

inline void EarlyWarning::setTrendDLStateEnable(int trendDLStateEnable)
{ m_trendDLStateEnable = trendDLStateEnable;}

inline int EarlyWarning::isMonitor() const
{ return m_isMonitor;}

inline void EarlyWarning::setIsMoniter(int isMonitor)
{ m_isMonitor = isMonitor;}
#endif // EARLYWARNING_H
