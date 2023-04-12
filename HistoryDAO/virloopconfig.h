#ifndef VIRLOOPCONFIG_H
#define VIRLOOPCONFIG_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class VirLoopConfig
{
public:
    typedef QSharedPointer<VirLoopConfig> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
    typedef QHash<QString, QList<Ptr>> HashL;
public:
    VirLoopConfig();
    ~VirLoopConfig();
public:
    int GUID() const;
    QString appId() const;
    QString recvIedName() const;
    QString recvPortId() const;
    QString recvStrapRef() const;
    QString gooseInst() const;
    QString gooseInstDesc() const;
    QString sendIedName() const;
    QString sendPortId() const;
    QString sendStrapRef() const;
    QString gooseRef() const;
    QString phyLink() const;
    QString gooseLinkAlarmRef() const;
    QString gooseDataExcep() const;
public:
    void setGUID(int guid);
    void setAppId(const QString &appId);
    void setRecvIedName(const QString &recvIedName);
    void setRecvPortId(const QString &recvPortId);
    void setRecvStrapRef(const QString &recvStrapRef);
    void setGooseInst(const QString &gooseInst);
    void setGooseInstDesc(const QString &gooseInstDesc);
    void setSendIedName(const QString &sendIedName);
    void setSendPortId(const QString &sendPortId);
    void setSendStrapRef(const QString &sendStrapRef);
    void setGooseRef(const QString &gooseRef);
    void setPhyLink(const QString &phyLink);
    void setGooseLinkAlarmRef(const QString &gooseLinkAlarmRef);
    void setGooseDataExcep(const QString &gooseDataExcep);
private:
    int m_GUID;
    QString m_appId;
    QString m_recvIedName;
    QString m_recvPortId;
    QString m_recvStrapRef;
    QString m_gooseInst;
    QString m_gooseInstDesc;
    QString m_sendIedName;
    QString m_sendPortId;
    QString m_sendStrapRef;
    QString m_gooseRef;
    QString m_phyLink;
    QString m_gooseLinkAlarmRef;
    QString m_gooseDataExcep;
private:
    friend class DBVirLoopConfigDAO;
};

inline int VirLoopConfig::GUID() const
{ return m_GUID;}

inline void VirLoopConfig::setGUID(int guid)
{ m_GUID = guid;}

inline QString VirLoopConfig::appId() const
{ return m_appId;}

inline void VirLoopConfig::setAppId(const QString &appId)
{ m_appId = appId;}

inline QString VirLoopConfig::recvIedName() const
{ return m_recvIedName;}

inline void VirLoopConfig::setRecvIedName(const QString &recvIedName)
{ m_recvIedName = recvIedName;}

inline QString VirLoopConfig::recvPortId() const
{ return m_recvPortId;}

inline void VirLoopConfig::setRecvPortId(const QString &recvPortId)
{ m_recvPortId = recvPortId;}

inline QString VirLoopConfig::recvStrapRef() const
{ return m_recvStrapRef;}

inline void VirLoopConfig::setRecvStrapRef(const QString &recvStrapRef)
{ m_recvStrapRef = recvStrapRef;}

inline QString VirLoopConfig::gooseInst() const
{ return m_gooseInst;}

inline void VirLoopConfig::setGooseInst(const QString &gooseInst)
{ m_gooseInst = gooseInst;}

inline QString VirLoopConfig::gooseInstDesc() const
{ return m_gooseInstDesc;}

inline void VirLoopConfig::setGooseInstDesc(const QString &gooseInstDesc)
{ m_gooseInstDesc = gooseInstDesc;}

inline QString VirLoopConfig::sendIedName() const
{ return m_sendIedName;}

inline void VirLoopConfig::setSendIedName(const QString &sendIedName)
{ m_sendIedName = sendIedName;}

inline QString VirLoopConfig::sendPortId() const
{ return m_sendPortId;}

inline void VirLoopConfig::setSendPortId(const QString &sendPortId)
{ m_sendPortId = sendPortId;}

inline QString VirLoopConfig::sendStrapRef() const
{ return m_sendStrapRef;}

inline void VirLoopConfig::setSendStrapRef(const QString &sendStrapRef)
{ m_sendStrapRef = sendStrapRef;}

inline QString VirLoopConfig::gooseRef() const
{ return m_gooseRef;}

inline void VirLoopConfig::setGooseRef(const QString &gooseRef)
{ m_gooseRef = gooseRef;}

inline QString VirLoopConfig::phyLink() const
{ return m_phyLink;}

inline void VirLoopConfig::setPhyLink(const QString &phyLink)
{ m_phyLink = phyLink;}

inline QString VirLoopConfig::gooseLinkAlarmRef() const
{ return m_gooseLinkAlarmRef;}

inline void VirLoopConfig::setGooseLinkAlarmRef(const QString &gooseLinkAlarmRef)
{ m_gooseLinkAlarmRef = gooseLinkAlarmRef;}

inline QString VirLoopConfig::gooseDataExcep() const
{ return m_gooseDataExcep;}

inline void VirLoopConfig::setGooseDataExcep(const QString &gooseDataExcep)
{ m_gooseDataExcep = gooseDataExcep;}
#endif // VIRLOOPCONFIG_H
