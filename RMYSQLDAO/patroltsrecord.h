#ifndef PATROLTSRECORD_H
#define PATROLTSRECORD_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class PatrolTSRecord
{
public:
    typedef QSharedPointer<PatrolTSRecord> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    PatrolTSRecord();
    ~PatrolTSRecord();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    int dataType() const;
    QString dataValue() const;
    QString quality() const;
    QString recordTime() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataType(int dataType);
    void setDataValue(const QString &dataValue);
    void setQuality(const QString &quality);
    void setRecordTime(const QString &recordTime);
private:
    int m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    int m_dataType;
    QString m_dataValue;
    QString m_quality;
    QString m_recordTime;
private:
    friend class DBPatrolTSRecordDAO;
};

inline int PatrolTSRecord::GUID() const
{ return m_GUID;}

inline void PatrolTSRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString PatrolTSRecord::iedName() const
{ return m_iedName;}

inline void PatrolTSRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString PatrolTSRecord::dataRef() const
{ return m_dataRef;}

inline void PatrolTSRecord::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString PatrolTSRecord::dataDesc() const
{ return m_dataDesc;}

inline void PatrolTSRecord::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int PatrolTSRecord::dataType() const
{ return m_dataType;}

inline void PatrolTSRecord::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString PatrolTSRecord::dataValue() const
{ return m_dataValue;}

inline void PatrolTSRecord::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString PatrolTSRecord::quality() const
{ return m_quality;}

inline void PatrolTSRecord::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString PatrolTSRecord::recordTime() const
{ return m_recordTime;}

inline void PatrolTSRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // PATROLTSRECORD_H
