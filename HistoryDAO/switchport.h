#ifndef SWITCHPORT_H
#define SWITCHPORT_H
#include <QSharedPointer>
#include <QList>
#include <QString>
#include <QVector>
#include "dastruct.h"
class SwitchPort
{
public:
    typedef QSharedPointer<SwitchPort> Ptr;
    typedef QList<Ptr> List;
public:
    SwitchPort();
    ~SwitchPort();
public:
    int GUID() const;
    QString iedName() const;
    QString port() const;
    int dataType() const;
    QString dataRef() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setPort(const QString &port);
    void setDataType(int dataType);
    void setDataRef(const QString &dataRef);
public:
    const QVector<DAStruct*> & lstDAStruct() const;
    void addDAStruct(DAStruct *daStruct);
    void setLstDAStruct(QVector<DAStruct*> &lstDAStruct);
    void removeDAStruct(DAStruct *daStruct);
    void clearDAStruct();
private:
    int m_GUID;
    QString m_iedName;
    QString m_port;
    int m_dataType;
    QString m_dataRef;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBSwitchPortDAO;
};

inline int SwitchPort::GUID() const
{ return m_GUID;}

inline void SwitchPort::setGUID(int guid)
{ m_GUID = guid;}

inline QString SwitchPort::iedName() const
{ return m_iedName;}

inline void SwitchPort::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString SwitchPort::port() const
{ return m_port;}

inline void SwitchPort::setPort(const QString &port)
{ m_port = port;}

inline int SwitchPort::dataType() const
{ return m_dataType;}

inline void SwitchPort::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString SwitchPort::dataRef() const
{ return m_dataRef;}

inline void SwitchPort::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline const QVector<DAStruct*> & SwitchPort::lstDAStruct() const
{ return m_lstDAStruct;}

inline void SwitchPort::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // SWITCHPORT_H
