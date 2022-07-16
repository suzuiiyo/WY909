#ifndef STRAP_H
#define STRAP_H
#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class Strap
{
public:
    typedef QSharedPointer<Strap> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    Strap();
    ~Strap();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString strapType() const;
    QString strapTypeDetail() const;
    QString signalType() const;
    QString bayName() const;
    QString dataSet() const;
    QString dataSetDesc() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setStrapType(const QString &strapType);
    void setStrapTypeDetail(const QString &strapTypeDetail);
    void setSignalType(const QString &signalType);
    void setBayName(const QString &bayName);
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
    int m_dataType;
    QString m_dataValue;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_strapType;
    QString m_strapTypeDetail;
    QString m_signalType;
    QString m_bayName;
    QString m_dataSet;
    QString m_dataSetDesc;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBStrapLightPlateDAO;
};

inline int Strap::GUID() const
{ return m_GUID;}

inline void Strap::setGUID(int guid)
{ m_GUID = guid;}

inline QString Strap::iedName() const
{ return m_iedName;}

inline void Strap::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString Strap::dataRef() const
{ return m_dataRef;}

inline void Strap::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString Strap::dataDesc() const
{ return m_dataDesc;}

inline void Strap::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString Strap::strapType() const
{ return m_strapType;}

inline void Strap::setStrapType(const QString &strapType)
{ m_strapType = strapType;}

inline QString Strap::strapTypeDetail() const
{ return m_strapTypeDetail;}

inline void Strap::setStrapTypeDetail(const QString &strapTypeDetail)
{ m_strapTypeDetail = strapTypeDetail;}

inline QString Strap::signalType() const
{ return m_signalType;}

inline void Strap::setSignalType(const QString &signalType)
{ m_signalType = signalType;}

inline QString Strap::bayName() const
{ return m_bayName;}

inline void Strap::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString Strap::dataSet() const
{ return m_dataSet;}

inline void Strap::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString Strap::dataSetDesc() const
{ return m_dataSetDesc;}

inline void Strap::setDataSetDesc(const QString &dataSetDesc)
{ m_dataSetDesc = dataSetDesc;}

inline const QStringList &Strap::lstDataValue() const
{ return m_lstDataValue;}

inline void Strap::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &Strap::lstDataType() const
{ return m_lstDataType;}

inline void Strap::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & Strap::lstDAStruct() const
{ return m_lstDAStruct;}

inline void Strap::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // STRAP_H
