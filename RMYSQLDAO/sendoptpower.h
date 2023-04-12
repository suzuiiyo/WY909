#ifndef SENDOPTPOWER_H
#define SENDOPTPOWER_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
class SendOptPower
{
public:
    typedef QSharedPointer<SendOptPower> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    SendOptPower();
    ~SendOptPower();
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
    friend class DBSendOptPowerDAO;
};

inline QString SendOptPower::iedName() const
{ return m_iedName;}

inline void SendOptPower::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString SendOptPower::dataRef() const
{ return m_dataRef;}

inline void SendOptPower::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString SendOptPower::dataDesc() const
{ return m_dataDesc;}

inline void SendOptPower::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int SendOptPower::dataType() const
{ return m_dataType;}

inline void SendOptPower::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString SendOptPower::dataValue() const
{ return m_dataValue;}

inline void SendOptPower::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString SendOptPower::quality() const
{ return m_quality;}

inline void SendOptPower::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString SendOptPower::recordTime() const
{ return m_recordTime;}

inline void SendOptPower::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // SENDOPTPOWER_H
