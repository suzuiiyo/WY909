#ifndef TIMESYNRECORD_H
#define TIMESYNRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class TimeSynRecord
{
public:
    typedef QSharedPointer<TimeSynRecord> Ptr;
    typedef QList<Ptr> List;
public:
    TimeSynRecord();
    ~TimeSynRecord();
public:
    int     GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    int     dataType() const;
    QString dataValue() const;
    QString quality() const;
    QString recordTime() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataType(int dataType);
    void setDataValue(const QString &dataValue);
    void setQuality(const QString &quality);
    void setRecordTime(const QString &recordTime);
    void setAckTip(int ackTip);
private:
    int     m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    int     m_dataType;
    QString m_dataValue;
    QString m_quality;
    QString m_recordTime;
    int     m_ackTip;
private:
    friend class DBTimeSynRecordDAO;
};

inline int TimeSynRecord::GUID() const
{ return m_GUID;}

inline void TimeSynRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString TimeSynRecord::iedName() const
{ return m_iedName;}

inline void TimeSynRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString TimeSynRecord::dataRef() const
{ return m_dataRef;}

inline void TimeSynRecord::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString TimeSynRecord::dataDesc() const
{ return m_dataDesc;}

inline void TimeSynRecord::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int TimeSynRecord::dataType() const
{ return m_dataType;}

inline void TimeSynRecord::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString TimeSynRecord::dataValue() const
{ return m_dataValue;}

inline void TimeSynRecord::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString TimeSynRecord::quality() const
{ return m_quality;}

inline void TimeSynRecord::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString TimeSynRecord::recordTime() const
{ return m_recordTime;}

inline void TimeSynRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}

inline int TimeSynRecord::ackTip() const
{ return m_ackTip;}

inline void TimeSynRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // TIMESYNRECORD_H
