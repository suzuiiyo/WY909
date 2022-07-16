#ifndef INDICATORLAMP_H
#define INDICATORLAMP_H
#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class IndicatorLamp
{
public:
    typedef QSharedPointer<IndicatorLamp> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    IndicatorLamp();
    ~IndicatorLamp();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString lampDesc() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setLampDesc(const QString &lampDesc);
public:
    const QStringList & lstDataValue() const;
    const QList<int> & lstDataType() const;
    void addDataValue(const QString &dataValue);
    void addDataType(int dataType);
    void clearDataValue();
    void clearDataType();
public:
    const QVector<DAStruct*> & lstDAStruct() const;
    void addDAStruct(DAStruct *daStruct);
    void setLstDAStruct(QVector<DAStruct*> &lstDAStruct);
    void removeDAStruct(DAStruct *daStruct);
    void clearDAStruct();
private:
    int m_GUID;
    QString m_iedName;
    QString m_dataDesc;
    QString m_dataRef;
    QString m_lampDesc;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBIndicatorLampDAO;
};

inline int IndicatorLamp::GUID() const
{ return m_GUID;}

inline void IndicatorLamp::setGUID(int guid)
{ m_GUID = guid;}

inline QString IndicatorLamp::iedName() const
{ return m_iedName;}

inline void IndicatorLamp::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString IndicatorLamp::dataRef() const
{ return m_dataRef;}

inline void IndicatorLamp::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString IndicatorLamp::dataDesc() const
{ return m_dataDesc;}

inline void IndicatorLamp::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString IndicatorLamp::lampDesc() const
{ return m_lampDesc;}

inline void IndicatorLamp::setLampDesc(const QString &lampDesc)
{ m_lampDesc = lampDesc;}

inline const QStringList &IndicatorLamp::lstDataValue() const
{ return m_lstDataValue;}

inline void IndicatorLamp::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &IndicatorLamp::lstDataType() const
{ return m_lstDataType;}

inline void IndicatorLamp::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & IndicatorLamp::lstDAStruct() const
{ return m_lstDAStruct;}

inline void IndicatorLamp::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // INDICATORLAMP_H
