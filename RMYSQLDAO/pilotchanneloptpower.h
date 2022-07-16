#ifndef PILOTCHANNELOPTPOWER_H
#define PILOTCHANNELOPTPOWER_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
class PilotChannelOptPower
{
public:
    typedef QSharedPointer<PilotChannelOptPower> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    PilotChannelOptPower();
    ~PilotChannelOptPower();
public:
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    int dataType() const;
    QString dataValue() const;
    QString quality() const;
    QString recordTime() const;
public:
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataType(int dataType);
    void setDataValue(const QString &dataValue);
    void setQuality(const QString &quality);
    void setRecordTime(const QString &recordTime);
private:
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    int m_dataType;
    QString m_dataValue;
    QString m_quality;
    QString m_recordTime;
private:
    friend class DBPilotChannelOptPowerDAO;
};

inline QString PilotChannelOptPower::iedName() const
{ return m_iedName;}

inline void PilotChannelOptPower::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString PilotChannelOptPower::dataRef() const
{ return m_dataRef;}

inline void PilotChannelOptPower::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString PilotChannelOptPower::dataDesc() const
{ return m_dataDesc;}

inline void PilotChannelOptPower::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int PilotChannelOptPower::dataType() const
{ return m_dataType;}

inline void PilotChannelOptPower::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString PilotChannelOptPower::dataValue() const
{ return m_dataValue;}

inline void PilotChannelOptPower::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString PilotChannelOptPower::quality() const
{ return m_quality;}

inline void PilotChannelOptPower::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString PilotChannelOptPower::recordTime() const
{ return m_recordTime;}

inline void PilotChannelOptPower::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // PILOTCHANNELOPTPOWER_H
