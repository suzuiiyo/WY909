#ifndef EVENTRECORD_H
#define EVENTRECORD_H
#include <QString>
#include <QList>
#include <QSharedPointer>
class EventRecord
{
public:
    typedef QSharedPointer<EventRecord> Ptr;
    typedef QList<Ptr> List;
public:
    EventRecord();
    ~EventRecord();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataValue() const;
    QString recordTime() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataValue(const QString &dataValue);
    void setRecordTime(const QString &recordTime);
private:
    int m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dataValue;
    QString m_recordTime;
private:
    friend class DBAlarmEventRecordDAO;
    friend class DBActionEventRecordDAO;
};

inline int EventRecord::GUID() const
{ return m_GUID;}

inline void EventRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString EventRecord::iedName() const
{ return m_iedName;}

inline void EventRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString EventRecord::dataRef() const
{ return m_dataRef;}

inline void EventRecord::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString EventRecord::dataDesc() const
{ return m_dataDesc;}

inline void EventRecord::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString EventRecord::dataValue() const
{ return m_dataValue;}

inline void EventRecord::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString EventRecord::recordTime() const
{ return m_recordTime;}

inline void EventRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // EVENTRECORD_H
