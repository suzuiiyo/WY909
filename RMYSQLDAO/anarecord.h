#ifndef ANARECORD_H
#define ANARECORD_H
#include <QString>
#include <QSharedPointer>
#include <QList>
class AnaRecord
{
public:
    typedef QSharedPointer<AnaRecord> Ptr;
    typedef QList<Ptr> List;
public:
    AnaRecord();
    ~AnaRecord();
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
    friend class DBAnaRecordDAO;
};

inline int AnaRecord::GUID() const
{ return m_GUID;}

inline void AnaRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString AnaRecord::iedName() const
{ return m_iedName;}

inline void AnaRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString AnaRecord::dataRef() const
{ return m_dataRef;}

inline void AnaRecord::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString AnaRecord::dataDesc() const
{ return m_dataRef;}

inline void AnaRecord::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int AnaRecord::dataType() const
{ return m_dataType;}

inline void AnaRecord::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString AnaRecord::dataValue() const
{ return m_dataValue;}

inline void AnaRecord::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString AnaRecord::quality() const
{ return m_quality;}

inline void AnaRecord::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString AnaRecord::recordTime() const
{ return m_recordTime;}

inline void AnaRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // ANARECORD_H
