#ifndef PILOTCHANNELOTHERTMDATA_H
#define PILOTCHANNELOTHERTMDATA_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
class PilotChannelOtherTMData
{
public:
    typedef QSharedPointer<PilotChannelOtherTMData> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    PilotChannelOtherTMData();
    ~PilotChannelOtherTMData();
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
    friend class DBPilotChannelOtherTMDataDAO;
};

inline QString PilotChannelOtherTMData::iedName() const
{ return m_iedName;}

inline void PilotChannelOtherTMData::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString PilotChannelOtherTMData::dataRef() const
{ return m_dataRef;}

inline void PilotChannelOtherTMData::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString PilotChannelOtherTMData::dataDesc() const
{ return m_dataDesc;}

inline void PilotChannelOtherTMData::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int PilotChannelOtherTMData::dataType() const
{ return m_dataType;}

inline void PilotChannelOtherTMData::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString PilotChannelOtherTMData::dataValue() const
{ return m_dataValue;}

inline void PilotChannelOtherTMData::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString PilotChannelOtherTMData::quality() const
{ return m_quality;}

inline void PilotChannelOtherTMData::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString PilotChannelOtherTMData::recordTime() const
{ return m_recordTime;}

inline void PilotChannelOtherTMData::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // PILOTCHANNELOTHERTMDATA_H
