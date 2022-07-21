#ifndef ACTEVENTINFO_H
#define ACTEVENTINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
class ActEventInfo
{
public:
    typedef QSharedPointer<ActEventInfo> Ptr;
    typedef QList<Ptr> List;
public:
    ActEventInfo();
    ~ActEventInfo();
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
    int     m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dataValue;
    QString m_quality;
    int     m_dataType;
    QString m_recordTime;
    int     m_ackTip;
private:
    friend class DBActionEventInfoDAO;
};

inline int ActEventInfo::GUID() const
{ return m_GUID;}

inline void ActEventInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString ActEventInfo::iedName() const
{ return m_iedName;}

inline void ActEventInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString ActEventInfo::dataRef() const
{ return m_dataRef;}

inline void ActEventInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString ActEventInfo::dataDesc() const
{ return m_dataDesc;}

inline void ActEventInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString ActEventInfo::dataValue() const
{ return m_dataValue;}

inline void ActEventInfo::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString ActEventInfo::quality() const
{ return m_quality;}

inline void ActEventInfo::setQuality(const QString &quality)
{ m_quality = quality;}

inline int ActEventInfo::dataType() const
{ return m_dataType;}

inline void ActEventInfo::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString ActEventInfo::recordTime() const
{ return m_recordTime;}

inline void ActEventInfo::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}

inline int ActEventInfo::ackTip() const
{ return m_ackTip;}

inline void ActEventInfo::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // ACTEVENTINFO_H
