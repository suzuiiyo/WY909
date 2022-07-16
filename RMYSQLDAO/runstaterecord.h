#ifndef RUNSTATERECORD_H
#define RUNSTATERECORD_H
#include <QString>
#include <QSharedPointer>
#include <QList>
class RunStateRecord
{
public:
    typedef QSharedPointer<RunStateRecord> Ptr;
    typedef QList<Ptr> List;
public:
    RunStateRecord();
    ~RunStateRecord();
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
    friend class DBRunStateRecordDAO;
};

inline int RunStateRecord::GUID() const
{ return m_GUID;}

inline void RunStateRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString RunStateRecord::iedName() const
{ return m_iedName;}

inline void RunStateRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString RunStateRecord::dataRef() const
{ return m_dataRef;}

inline void RunStateRecord::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString RunStateRecord::dataDesc() const
{ return m_dataDesc;}

inline void RunStateRecord::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int RunStateRecord::dataType() const
{ return m_dataType;}

inline void RunStateRecord::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString RunStateRecord::dataValue() const
{ return m_dataValue;}

inline void RunStateRecord::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString RunStateRecord::quality() const
{ return m_quality;}

inline void RunStateRecord::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString RunStateRecord::recordTime() const
{ return m_recordTime;}

inline void RunStateRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // RUNSTATERECORD_H
