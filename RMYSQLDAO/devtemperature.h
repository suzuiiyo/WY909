#ifndef DEVTEMPERATURE_H
#define DEVTEMPERATURE_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
class DevTemperature
{
public:
    typedef QSharedPointer<DevTemperature> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    DevTemperature();
    ~DevTemperature();
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
    friend class DBDevTemperatureDAO;
};

inline QString DevTemperature::iedName() const
{ return m_iedName;}

inline void DevTemperature::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString DevTemperature::dataRef() const
{ return m_dataRef;}

inline void DevTemperature::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString DevTemperature::dataDesc() const
{ return m_dataDesc;}

inline void DevTemperature::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int DevTemperature::dataType() const
{ return m_dataType;}

inline void DevTemperature::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString DevTemperature::dataValue() const
{ return m_dataValue;}

inline void DevTemperature::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString DevTemperature::quality() const
{ return m_quality;}

inline void DevTemperature::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString DevTemperature::recordTime() const
{ return m_recordTime;}

inline void DevTemperature::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // DEVTEMPERATURE_H
