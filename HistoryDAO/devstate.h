#ifndef DEVSTATE_H
#define DEVSTATE_H
#include <QString>
#include <QList>
#include <QSharedPointer>
class DevState
{
public:
    typedef QSharedPointer<DevState> Ptr;
    typedef QList<Ptr> List;
public:
    DevState();
    ~DevState();
public:
    QString iedName() const;
    QString iedDesc() const;
    int connectionState() const;
    int voltState() const;
    int temperatureState() const;
    int LIState() const;
    int DCState() const;
    int settingState() const;
    int CRCState() const;
    float clockOffset() const;
    QString lastUpdateTime() const;
public:
    void setIedName(const QString &iedName);
    void setIedDesc(const QString &iedDesc);
    void setConnectionState(int connectionState);
    void setVoltState(int voltState);
    void setTemperatureState(int temperatureState);
    void setLIState(int LIState);
    void setDCState(int DCState);
    void setSettingState(int settingState);
    void setCRCState(int CRCState);
    void setClockOffset(float clockOffset);
    void setLastUpdateTime(const QString &lastUpdateTime);
private:
    QString m_iedName;
    QString m_iedDesc;
    int m_connectionState;
    int m_voltState;
    int m_temperatureState;
    int m_LIState;
    int m_DCState;
    int m_settingState;
    int m_CRCState;
    float m_clockOffset;
    QString m_lastUpdateTime;
private:
    friend class DBIedStateDAO;
};

inline QString DevState::iedName() const
{ return m_iedName;}

inline void DevState::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString DevState::iedDesc() const
{ return m_iedDesc;}

inline void DevState::setIedDesc(const QString &iedDesc)
{ m_iedDesc = iedDesc;}

inline int DevState::connectionState() const
{ return m_connectionState;}

inline void DevState::setConnectionState(int connectionState)
{ m_connectionState = connectionState;}

inline int DevState::voltState() const
{ return m_voltState;}

inline void DevState::setVoltState(int voltState)
{ m_voltState = voltState;}

inline int DevState::temperatureState() const
{ return m_temperatureState;}

inline void DevState::setTemperatureState(int temperatureState)
{ m_temperatureState = temperatureState;}

inline int DevState::LIState() const
{ return m_LIState;}

inline void DevState::setLIState(int LIState)
{ m_LIState = LIState;}

inline int DevState::DCState() const
{ return m_DCState;}

inline void DevState::setDCState(int DCState)
{ m_DCState = DCState;}

inline int DevState::settingState() const
{ return m_settingState;}

inline void DevState::setSettingState(int settingState)
{ m_settingState = settingState;}

inline int DevState::CRCState() const
{ return m_CRCState;}

inline void DevState::setCRCState(int CRCState)
{ m_CRCState = CRCState;}

inline float DevState::clockOffset() const
{ return m_clockOffset;}

inline void DevState::setClockOffset(float clockOffset)
{ m_clockOffset = clockOffset;}

inline QString DevState::lastUpdateTime() const
{ return m_lastUpdateTime;}

inline void DevState::setLastUpdateTime(const QString &lastUpdateTime)
{ m_lastUpdateTime = lastUpdateTime;}
#endif // DEVSTATE_H
