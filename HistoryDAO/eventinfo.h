#ifndef EVENTINFO_H
#define EVENTINFO_H
#include <QString>
#include <QSharedPointer>
#include <QVector>
#include <QList>
#include <QHash>
#include "dastruct.h"
class EventInfo
{
public:
    typedef QSharedPointer<EventInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    EventInfo();
    ~EventInfo();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataSet() const;
    QString dataSetDesc() const;
    QString eventType() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString  &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataSet(const QString &dataSet);
    void setDataSetDesc(const QString &dataSetDesc);
    void setEventType(const QString &eventType);
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
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dataSet;
    QString m_dataSetDesc;
    QString m_eventType;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBEventInfoDAO;
};

inline int EventInfo::GUID() const
{ return m_GUID;}

inline void EventInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString EventInfo::iedName() const
{ return m_iedName;}

inline void EventInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString EventInfo::dataRef() const
{ return m_dataRef;}

inline void EventInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString EventInfo::dataDesc() const
{ return m_dataDesc;}

inline void EventInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString EventInfo::dataSet() const
{ return m_dataSet;}

inline void EventInfo::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString EventInfo::dataSetDesc() const
{ return m_dataDesc;}

inline void EventInfo::setDataSetDesc(const QString &dataSetDesc)
{ m_dataSetDesc = dataSetDesc;}

inline QString EventInfo::eventType() const
{ return m_eventType;}

inline void EventInfo::setEventType(const QString &eventType)
{ m_eventType = eventType;}

inline const QStringList &EventInfo::lstDataValue() const
{ return m_lstDataValue;}

inline void EventInfo::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &EventInfo::lstDataType() const
{ return m_lstDataType;}

inline void EventInfo::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & EventInfo::lstDAStruct() const
{ return m_lstDAStruct;}

inline void EventInfo::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // EVENTINFO_H
