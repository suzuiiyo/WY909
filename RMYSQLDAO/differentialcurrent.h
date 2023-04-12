#ifndef DIFFERENTIALCURRENT_H
#define DIFFERENTIALCURRENT_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
class DifferentialCurrent
{
public:
    typedef QSharedPointer<DifferentialCurrent> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    DifferentialCurrent();
    ~DifferentialCurrent();
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
    friend class DBDifferentialCurrentDAO;
};

inline QString DifferentialCurrent::iedName() const
{ return m_iedName;}

inline void DifferentialCurrent::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString DifferentialCurrent::dataRef() const
{ return m_dataRef;}

inline void DifferentialCurrent::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString DifferentialCurrent::dataDesc() const
{ return m_dataDesc;}

inline void DifferentialCurrent::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline int DifferentialCurrent::dataType1() const
{ return m_dataType1;}

inline void DifferentialCurrent::setDataType1(int dataType1)
{ m_dataType1 = dataType1;}

inline QString DifferentialCurrent::dataValue1() const
{ return m_dataValue1;}

inline void DifferentialCurrent::setDataValue1(const QString &dataValue1)
{ m_dataValue1 = dataValue1;}

inline int DifferentialCurrent::dataType2() const
{ return m_dataType2;}

inline void DifferentialCurrent::setDataType2(int dataType2)
{ m_dataType2 = dataType2;}

inline QString DifferentialCurrent::dataValue2() const
{ return m_dataValue2;}

inline void DifferentialCurrent::setDataValue2(const QString &dataValue2)
{ m_dataValue2 = dataValue2;}

inline QString DifferentialCurrent::quality() const
{ return m_quality;}

inline void DifferentialCurrent::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString DifferentialCurrent::recordTime() const
{ return m_recordTime;}

inline void DifferentialCurrent::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // DIFFERENTIALCURRENT_H
