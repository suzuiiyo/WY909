#ifndef ALARMINFO_H
#define ALARMINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class AlarmInfo
{
public:
    typedef QSharedPointer<AlarmInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    AlarmInfo();
    ~AlarmInfo();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataSet() const;
    QString dataSetDesc() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataSet(const QString &dataSet);
    void setDataSetDesc(const QString &dataSetDesc);
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
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBAlarmInfoDAO;
};

inline int AlarmInfo::GUID() const
{ return m_GUID;}

inline void AlarmInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString AlarmInfo::iedName() const
{ return m_iedName;}

inline void AlarmInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString AlarmInfo::dataRef() const
{ return m_dataRef;}

inline void AlarmInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString AlarmInfo::dataDesc() const
{ return m_dataDesc;}

inline void AlarmInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString AlarmInfo::dataSet() const
{ return m_dataSet;}

inline void AlarmInfo::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString AlarmInfo::dataSetDesc() const
{ return m_dataSetDesc;}

inline void AlarmInfo::setDataSetDesc(const QString &dataSetDesc)
{ m_dataSetDesc = dataSetDesc;}

inline const QStringList &AlarmInfo::lstDataValue() const
{ return m_lstDataValue;}

inline void AlarmInfo::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &AlarmInfo::lstDataType() const
{ return m_lstDataType;}

inline void AlarmInfo::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & AlarmInfo::lstDAStruct() const
{ return m_lstDAStruct;}

inline void AlarmInfo::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // ALARMINFO_H
