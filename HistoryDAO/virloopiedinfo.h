#ifndef VIRLOOPIEDINFO_H
#define VIRLOOPIEDINFO_H
#include <QList>
#include "ied.h"
#include "virlooprecvied.h"
#include "virloopsendied.h"
class VirLoopIedInfo
{
public:
    typedef QSharedPointer<VirLoopIedInfo> Ptr;
    typedef QHash<QString, Ptr> Hash;
    typedef QList<Ptr> List;
public:
    VirLoopIedInfo();
    ~VirLoopIedInfo();
public:
    bool isAimIed(const QString &iedName);
    Ied *ied() const;
    void setIed(Ied *ied);
public:
    const VirLoopRecvIed::List & lstRecvIed() const;
    //VirLoopRecvIed *recvIed(const QString &iedName) const;
    void addRecvIed(VirLoopRecvIed *recvIed);
    void removeRecvIed(VirLoopRecvIed *recvIed);
    void clearRecvIed();
public:
    const VirLoopSendIed::List & lstSendIed() const;
    //VirLoopSendIed *sendIed(const QString &iedName) const;
    void addSendIed(VirLoopSendIed *sendIed);
    void removeSendIed(VirLoopSendIed *sendIed);
    void clearSendIed();
private:
    Ied *m_pIed;
    VirLoopSendIed::List m_lstSendIed;
    VirLoopRecvIed::List m_lstRecvIed;
private:
    friend class DBVirLoopConfigDAO;
};

inline Ied * VirLoopIedInfo::ied() const
{ return m_pIed;}

inline void VirLoopIedInfo::setIed(Ied *pIed)
{ m_pIed = pIed;}

inline const VirLoopSendIed::List & VirLoopIedInfo::lstSendIed() const
{ return m_lstSendIed;}

inline const VirLoopRecvIed::List & VirLoopIedInfo::lstRecvIed() const
{ return m_lstRecvIed;}
#endif // VIRLOOPIEDINFO_H
