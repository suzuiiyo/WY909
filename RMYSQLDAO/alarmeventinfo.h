#ifndef ALARMEVENTINFO_H
#define ALARMEVENTINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
class AlarmEventInfo
{
public:
    typedef QSharedPointer<AlarmEventInfo> Ptr;
    typedef QList<Ptr> List;
public:
    AlarmEventInfo();
    ~AlarmEventInfo();
public:
    int     GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataValue() const;
    QString quality() const;
    int     dataType() const;
    QString recordTime() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataValue(const QString &dataValue);
    void setQuality(const QString &quality);
    void setDataType(int dataType);
    void setRecordTime(const QString &recordTime);
    void setAckTip(int ackTip);
private:
    int m_GUID;
    int m_dataType;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dataValue;
    QString m_quality;
    QString m_recordTime;
    int     m_ackTip;
private:
    friend class DBAlarmEventInfoDAO;
};

inline int AlarmEventInfo::GUID() const
{ return m_GUID;}

inline void AlarmEventInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString AlarmEventInfo::iedName() const
{ return m_iedName;}

inline void AlarmEventInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString AlarmEventInfo::dataRef() const
{ return m_dataRef;}

inline void AlarmEventInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString AlarmEventInfo::dataDesc() const
{ return m_dataDesc;}

inline void AlarmEventInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString AlarmEventInfo::dataValue() const
{ return m_dataValue;}

inline void AlarmEventInfo::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString AlarmEventInfo::quality() const
{ return m_quality;}

inline void AlarmEventInfo::setQuality(const QString &quality)
{ m_quality = quality;}

inline int AlarmEventInfo::dataType() const
{ return m_dataType;}

inline void AlarmEventInfo::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString AlarmEventInfo::recordTime() const
{ return m_recordTime;}

inline void AlarmEventInfo::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}

inline int AlarmEventInfo::ackTip() const
{ return m_ackTip;}

inline void AlarmEventInfo::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // ALARMEVENTINFO_H
