#ifndef DEVRUNSTATE_H
#define DEVRUNSTATE_H
#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QHash>
#include <QVector>
#include "dastruct.h"
#include "dbdastructdao.h"
//#include "dboperatingconditionsdao.h"
class DevRunState
{
public:
    typedef QSharedPointer<DevRunState> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    DevRunState();
    ~DevRunState();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
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
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBDevRunStateDAO;
};

inline int DevRunState::GUID() const
{ return GUID();}

inline void DevRunState::setGUID(int guid)
{ m_GUID = guid;}

inline QString DevRunState::iedName() const
{ return m_iedName;}

inline void DevRunState::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString DevRunState::dataRef() const
{ return m_dataRef;}

inline void DevRunState::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString DevRunState::dataDesc() const
{ return m_dataDesc;}

inline void DevRunState::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline const QStringList &DevRunState::lstDataValue() const
{ return m_lstDataValue;}

inline void DevRunState::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &DevRunState::lstDataType() const
{ return m_lstDataType;}

inline void DevRunState::clearDataType()
{ m_lstDataType.clear();}

inline const QVector<DAStruct*> & DevRunState::lstDAStruct() const
{ return m_lstDAStruct;}

inline void DevRunState::setLstDAStruct(QVector<DAStruct *> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // DEVRUNSTATE_H
