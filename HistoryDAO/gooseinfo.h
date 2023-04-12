#ifndef GOOSEINFO_H
#define GOOSEINFO_H
#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class GooseInfo
{
public:
    typedef QSharedPointer<GooseInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    GooseInfo();
    ~GooseInfo();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataSet() const;
    QString dataSetRef() const;
    QString dataSetDesc() const;
    QString appId() const;
    QString dataDesc() const;
    QString dimension() const;
    QString referenceValue() const;
    QString devName() const;
    int dataType() const;
    QString dataValue() const;
    QString bayName() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataSet(const QString &dataSet);
    void setDataSetRef(const QString &dataSetRef);
    void setDataSetDesc(const QString &dataSetDesc);
    void setAppId(const QString &appId);
    void setDataDesc(const QString &dataDesc);
    void setDimension(const QString &dimension);
    void setReferenceValue(const QString &referenceValue);
    void setDevName(const QString &devName);
    void setDataType(int dataType);
    void setDataValue(const QString &dataValue);
    void setBayName(const QString &bayName);
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
    QString m_dataSet;
    QString m_dataSetRef;
    QString m_dataSetDesc;
    QString m_appId;
    QString m_dataDesc;
    QString m_dimension;
    QString m_referenceValue;
    QString m_devName;
    int m_dataType;
    QString m_dataValue;
    QString m_bayName;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBGooseInfoDAO;
};

inline int GooseInfo::GUID() const
{ return m_GUID;}

inline void GooseInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString GooseInfo::iedName() const
{ return m_iedName;}

inline void GooseInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString GooseInfo::dataRef() const
{ return m_dataRef;}

inline void GooseInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString GooseInfo::dataSet() const
{ return m_dataSet;}

inline void GooseInfo::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString GooseInfo::dataSetRef() const
{ return m_dataSetRef;}

inline void GooseInfo::setDataSetRef(const QString &dataSetRef)
{ m_dataSetRef = dataSetRef;}

inline QString GooseInfo::dataSetDesc() const
{ return m_dataDesc;}

inline void GooseInfo::setDataSetDesc(const QString &dataSetDesc)
{ m_dataSetDesc = dataSetDesc;}

inline QString GooseInfo::appId() const
{ return m_appId;}

inline void GooseInfo::setAppId(const QString &appId)
{ m_appId = appId;}

inline QString GooseInfo::dataDesc() const
{ return m_dataDesc;}

inline void GooseInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString GooseInfo::dimension() const
{ return m_dimension;}

inline void GooseInfo::setDimension(const QString &dimension)
{ m_dimension = dimension;}

inline QString GooseInfo::referenceValue() const
{ return m_referenceValue;}

inline void GooseInfo::setReferenceValue(const QString &referenceValue)
{ m_referenceValue = referenceValue;}

inline QString GooseInfo::devName() const
{ return m_devName;}

inline void GooseInfo::setDevName(const QString &devName)
{ m_devName = devName;}

inline int GooseInfo::dataType() const
{ return m_dataType;}

inline void GooseInfo::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString GooseInfo::dataValue() const
{ return m_dataValue;}

inline void GooseInfo::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString GooseInfo::bayName() const
{ return m_bayName;}

inline void GooseInfo::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline const QVector<DAStruct*> & GooseInfo::lstDAStruct() const
{ return m_lstDAStruct;}

inline void GooseInfo::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // GOOSEINFO_H
