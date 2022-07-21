#ifndef RECVOPTPOWER_H
#define RECVOPTPOWER_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
class RecvOptPower
{
public:
    typedef QSharedPointer<RecvOptPower> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    RecvOptPower();
    ~RecvOptPower();
public:
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    int dataType() const;
    QString dataValue() const;
    QString quality() const;
    QString recordTime() const;
public:
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataType(int dataType);
    void setDataValue(const QString &dataValue);
    void setQuality(const QString &quality);
    void setRecordTime(const QString &recordTime);
private:
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    int m_dataType;
    QString m_dataValue;
    QString m_quality;
    QString m_recordTime;
private:
    friend class DBRecvOptPowerDAO;
};

inline QString RecvOptPower::iedName() const
{ return m_iedName;}

inline void RecvOptPower::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString RecvOptPower::dataRef() const
{ return m_dataRef;}

inline void RecvOptPower::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString RecvOptPower::dataDesc() const
{ return m_dataDesc;}

inline void RecvOptPower::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int RecvOptPower::dataType() const
{ return m_dataType;}

inline void RecvOptPower::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString RecvOptPower::dataValue() const
{ return m_dataValue;}

inline void RecvOptPower::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString RecvOptPower::quality() const
{ return m_quality;}

inline void RecvOptPower::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString RecvOptPower::recordTime() const
{ return m_recordTime;}

inline void RecvOptPower::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // RECVOPTPOWER_H
