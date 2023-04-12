#ifndef DEVPARAMETER_H
#define DEVPARAMETER_H
#include <QString>
#include <QList>
#include <QSharedPointer>
class DevParameter
{
public:
    typedef QSharedPointer<DevParameter> Ptr;
    typedef QList<Ptr> List;
public:
    DevParameter();
    ~DevParameter();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dimension() const;
    float maxValue() const;
    float minValue() const;
    float stepSize() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDimension(const QString &dimension);
    void setMaxValue(float maxValue);
    void setMinValue(float minValue);
    void setStepSize(float stepSize);
private:
    int m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dimension;
    float m_maxValue;
    float m_minValue;
    float m_stepSize;
private:
    friend class DBDevParameterDAO;
};

inline int DevParameter::GUID() const
{ return m_GUID;}

inline void DevParameter::setGUID(int guid)
{ m_GUID = guid;}

inline QString DevParameter::iedName() const
{ return m_iedName;}

inline void DevParameter::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString DevParameter::dataRef() const
{ return m_dataRef;}

inline void DevParameter::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString DevParameter::dataDesc() const
{ return m_dataDesc;}

inline void DevParameter::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString DevParameter::dimension() const
{ return m_dimension;}

inline void DevParameter::setDimension(const QString &dimension)
{ m_dimension = dimension;}

inline float DevParameter::maxValue() const
{ return m_maxValue;}

inline void DevParameter::setMaxValue(float maxValue)
{ m_maxValue = maxValue;}

inline float DevParameter::minValue() const
{ return m_minValue;}

inline void DevParameter::setMinValue(float minValue)
{ m_minValue = minValue;}

inline float DevParameter::stepSize() const
{ return m_stepSize;}

inline void DevParameter::setStepSize(float stepSize)
{ m_stepSize = stepSize;}
#endif // DEVPARAMETER_H
