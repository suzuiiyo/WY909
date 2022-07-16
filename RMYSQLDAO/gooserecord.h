#ifndef GOOSERECORD_H
#define GOOSERECORD_H
#include <QString>
#include <QSharedPointer>
#include <QList>
class GooseRecord
{
public:
    typedef QSharedPointer<GooseRecord> Ptr;
    typedef QList<Ptr> List;
public:
    GooseRecord();
    ~GooseRecord();
public:
    int GUID() const;
    int appId() const;
    QString dataRef() const;
    QString iedName() const;
    QString dataDesc() const;
    int dataType() const;
    QString dataValue() const;
    QString recordTime() const;
public:
    void setGUID(int guid);
    void setAppId(int appId);
    void setDataRef(const QString &dataRef);
    void setIedName(const QString &iedName);
    void setDataDesc(const QString &dataDesc);
    void setDataType(int dataType);
    void setDataValue(const QString &dataValue);
    void setRecordTime(const QString &recordTime);
private:
    int m_GUID;
    int m_appId;
    QString m_dataRef;
    QString m_iedName;
    QString m_dataDesc;
    int m_dataType;
    QString m_dataValue;
    QString m_recordTime;
private:
    friend class DBGooseRecordDAO;
};
inline int GooseRecord::GUID() const
{ return m_GUID;}

inline void GooseRecord::setGUID(int guid)
{ m_GUID = guid;}

inline int GooseRecord::appId() const
{ return m_appId;}

inline void GooseRecord::setAppId(int appId)
{ m_appId = appId;}

inline QString GooseRecord::dataRef() const
{ return m_dataRef;}

inline void GooseRecord::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString GooseRecord::iedName() const
{ return m_iedName;}

inline void GooseRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString GooseRecord::dataDesc() const
{ return m_dataDesc;}

inline void GooseRecord::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int GooseRecord::dataType() const
{ return m_dataType;}

inline void GooseRecord::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString GooseRecord::dataValue() const
{ return m_dataValue;}

inline void GooseRecord::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString GooseRecord::recordTime() const
{ return m_recordTime;}

inline void GooseRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // GOOSERECORD_H
