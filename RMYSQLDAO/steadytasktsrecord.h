#ifndef STEADYTASKTSRECORD_H
#define STEADYTASKTSRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class SteadyTaskTSRecord
{
public:
    typedef QSharedPointer<SteadyTaskTSRecord> Ptr;
    typedef QList<Ptr> List;
public:
    SteadyTaskTSRecord();
    ~SteadyTaskTSRecord();
public:
    int     GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    int     dataType1() const;
    QString dataValue1() const;
    int     dataType2() const;
    QString dataValue2() const;
    QString quality() const;
    QString recordTime() const;
    QString scope() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataType1(int dataType1);
    void setDataValue1(const QString &dataValue1);
    void setDataType2(int dataType2);
    void setDataValue2(const QString &dataValue2);
    void setQuality(const QString &quality);
    void setRecordTime(const QString &recordTime);
    void setScope(const QString &scope);
    void setAckTip(int ackTip);
private:
    int     m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    int     m_dataType1;
    QString m_dataValue1;
    int     m_dataType2;
    QString m_dataValue2;
    QString m_quality;
    QString m_recordTime;
    QString m_scope;
    int     m_ackTip;
private:
    friend class DBSteadyTaskTSRecordDAO;
};

inline int SteadyTaskTSRecord::GUID() const
{ return m_GUID;}

inline void SteadyTaskTSRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString SteadyTaskTSRecord::iedName() const
{ return m_iedName;}

inline void SteadyTaskTSRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString SteadyTaskTSRecord::dataRef() const
{ return m_dataRef;}

inline void SteadyTaskTSRecord::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString SteadyTaskTSRecord::dataDesc() const
{ return m_dataDesc;}

inline void SteadyTaskTSRecord::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int SteadyTaskTSRecord::dataType1() const
{ return m_dataType1;}

inline void SteadyTaskTSRecord::setDataType1(int dataType1)
{ m_dataType1 = dataType1;}

inline QString SteadyTaskTSRecord::dataValue1() const
{ return m_dataValue1;}

inline void SteadyTaskTSRecord::setDataValue1(const QString &dataValue1)
{ m_dataValue1 = dataValue1;}

inline int SteadyTaskTSRecord::dataType2() const
{ return m_dataType2;}

inline void SteadyTaskTSRecord::setDataType2(int dataType2)
{ m_dataType2 = dataType2;}

inline QString SteadyTaskTSRecord::dataValue2() const
{ return m_dataValue2;}

inline void SteadyTaskTSRecord::setDataValue2(const QString &dataValue2)
{ m_dataValue2 = dataValue2;}

inline QString SteadyTaskTSRecord::quality() const
{ return m_quality;}

inline void SteadyTaskTSRecord::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString SteadyTaskTSRecord::recordTime() const
{ return m_recordTime;}

inline void SteadyTaskTSRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}

inline QString SteadyTaskTSRecord::scope() const
{ return m_scope;}

inline void SteadyTaskTSRecord::setScope(const QString &scope)
{ m_scope = scope;}

inline int SteadyTaskTSRecord::ackTip() const
{ return m_ackTip;}

inline void SteadyTaskTSRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // STEADYTASKTSRECORD_H
