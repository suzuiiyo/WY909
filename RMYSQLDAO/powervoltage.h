#ifndef POWERVOLTAGE_H
#define POWERVOLTAGE_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
class PowerVoltage
{
public:
    typedef QSharedPointer<PowerVoltage> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    PowerVoltage();
    ~PowerVoltage();
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
    friend class DBPowerVoltageDAO;
};

inline QString PowerVoltage::iedName() const
{ return m_iedName;}

inline void PowerVoltage::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString PowerVoltage::dataRef() const
{ return m_dataRef;}

inline void PowerVoltage::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString PowerVoltage::dataDesc() const
{ return m_dataDesc;}

inline void PowerVoltage::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int PowerVoltage::dataType() const
{ return m_dataType;}

inline void PowerVoltage::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString PowerVoltage::dataValue() const
{ return m_dataValue;}

inline void PowerVoltage::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString PowerVoltage::quality() const
{ return m_quality;}

inline void PowerVoltage::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString PowerVoltage::recordTime() const
{ return m_recordTime;}

inline void PowerVoltage::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // POWERVOLTAGE_H
