#ifndef STRAPRECORD_H
#define STRAPRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QString>
class StrapRecord
{
public:
    typedef QSharedPointer<StrapRecord> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    StrapRecord();
    ~StrapRecord();
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
    friend class DBStrapRecordDAO;
};

inline int StrapRecord::GUID() const
{ return m_GUID;}

inline void StrapRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString StrapRecord::iedName() const
{ return m_iedName;}

inline void StrapRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString StrapRecord::dataRef() const
{ return m_dataRef;}

inline void StrapRecord::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString StrapRecord::dataDesc() const
{ return m_dataDesc;}

inline void StrapRecord::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int StrapRecord::dataType() const
{ return m_dataType;}

inline void StrapRecord::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString StrapRecord::dataValue() const
{ return m_dataValue;}

inline void StrapRecord::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString StrapRecord::quality() const
{ return m_quality;}

inline void StrapRecord::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString StrapRecord::recordTime() const
{ return m_recordTime;}

inline void StrapRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // STRAPRECORD_H
