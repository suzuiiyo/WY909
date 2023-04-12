#ifndef PROTVOLTAGE_H
#define PROTVOLTAGE_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QString>
class ProtVoltage
{
public:
    typedef QSharedPointer<ProtVoltage> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    ProtVoltage();
    ~ProtVoltage();
public:
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    int dataType1() const;
    QString dataValue1() const;
    int dataType2() const;
    QString dataValue2() const;
    QString quality() const;
    QString recordTime() const;
public:
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataType1(int dataType1);
    void setDataValue1(const QString &dataValue1);
    void setDataType2(int dataType2);
    void setDataValue2(const QString &dataValue2);
    void setQuality(const QString &quality);
    void setRecordTime(const QString &recordTime);
private:
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    int m_dataType1;
    QString m_dataValue1;
    int m_dataType2;
    QString m_dataValue2;
    QString m_quality;
    QString m_recordTime;
private:
    friend class DBProtVoltageDAO;
};

inline QString ProtVoltage::iedName() const
{ return m_iedName;}

inline void ProtVoltage::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString ProtVoltage::dataRef() const
{ return m_dataRef;}

inline void ProtVoltage::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString ProtVoltage::dataDesc() const
{ return m_dataDesc;}

inline void ProtVoltage::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int ProtVoltage::dataType1() const
{ return m_dataType1;}

inline void ProtVoltage::setDataType1(int dataType1)
{ m_dataType1 = dataType1;}

inline QString ProtVoltage::dataValue1() const
{ return m_dataValue1;}

inline void ProtVoltage::setDataValue1(const QString &dataValue1)
{ m_dataValue1 = dataValue1;}

inline int ProtVoltage::dataType2() const
{ return m_dataType2;}

inline void ProtVoltage::setDataType2(int dataType2)
{ m_dataType2 = dataType2;}

inline QString ProtVoltage::dataValue2() const
{ return m_dataValue2;}

inline void ProtVoltage::setDataValue2(const QString &dataValue2)
{ m_dataValue2 = dataValue2;}

inline QString ProtVoltage::quality() const
{ return m_quality;}

inline void ProtVoltage::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString ProtVoltage::recordTime() const
{ return m_recordTime;}

inline void ProtVoltage::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // PROTVOLTAGE_H
