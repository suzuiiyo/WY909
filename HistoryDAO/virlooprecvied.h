#ifndef VIRLOOPRECVIED_H
#define VIRLOOPRECVIED_H
#include "ied.h"
#include "strap.h"
#include "optport.h"
#include "fibreoptical.h"
#include "gooseinfo.h"
#include "gooseinst.h"
#include "switchdevice.h"
#include "devrunstate.h"
class VirLoopRecvIed
{
public:
    typedef QList<VirLoopRecvIed*> List;
public:
    VirLoopRecvIed();
    ~VirLoopRecvIed();
public:
    //bool isP2P() const;
    QString appId() const;
    Strap *selfStrap() const;
    OptPort *selfPort() const;
    FibreOptical *lineIedToSwitch() const;
    GooseInfo *gooseInfo() const;
    Ied *recvIed() const;
    Strap *recvStrap() const;
    OptPort *recvPort() const;
    FibreOptical *lineSwitchToIed() const;
    GooseInst *gooseInst() const;
    DevRunState *recvIedGooseLinkAlarm() const;
public:
    //void setIsP2P(bool result);
    void setAppId(const QString &appId);
    void setSelfStrap(Strap *selfStrap);
    void setSelfPort(OptPort *selfPort);
    void setLineIedToSwitch(FibreOptical *lineIedToSwitch);
    void setGooseInfo(GooseInfo *gooseInfo);
    void setRecvIed(Ied *recvIed);
    void setRecvStrap(Strap *recvStrap);
    void setRecvPort(OptPort *port);
    void setLineSwitchToIed(FibreOptical *lineSwitchToIed);
    void setGooseInst(GooseInst *gooseInst);
    void setRecvIedGooseLinkAlarm(DevRunState *recvIedGooseLinkAlarm);
public:
    const SwitchDevice::List & lstSwitchDevice() const;
    SwitchDevice *switchDev(const QString &iedName) const;
    void addSwitchDevice(SwitchDevice *dev);
    void removeSwitchDevice(SwitchDevice *dev);
    void clearSwitchDevice();
private:
    //bool m_isP2P;
    QString m_appId;
    Strap *m_pSelfStrap;
    OptPort *m_pSelfPort;
    FibreOptical *m_pLineIedToSwitch;
    GooseInfo *m_pGooseInfo;
    Ied *m_pRecvIed;
    Strap *m_pRecvStrap;
    OptPort *m_pRecvPort;
    FibreOptical *m_pLineSwitchToIed;
    GooseInst *m_pGooseInst;
    DevRunState *m_pRecvIedGooseLinkAlarm;
    SwitchDevice::List m_lstSwitchDevice;
private:
    friend class VirLoopIedInfo;
};
//inline bool VirLoopRecvIed::isP2P() const
//{ return m_isP2P;}

//inline void VirLoopRecvIed::setIsP2P(bool result)
//{ m_isP2P = result;}


inline QString VirLoopRecvIed::appId() const
{ return m_appId;}

inline void VirLoopRecvIed::setAppId(const QString &appId)
{ m_appId = appId;}

inline Strap * VirLoopRecvIed::selfStrap() const
{ return m_pSelfStrap;}

inline void VirLoopRecvIed::setSelfStrap(Strap *selfStrap)
{ m_pSelfStrap = selfStrap;}

inline OptPort * VirLoopRecvIed::selfPort() const
{ return m_pSelfPort;}

inline void VirLoopRecvIed::setSelfPort(OptPort *selfPort)
{ m_pSelfPort = selfPort;}

inline FibreOptical * VirLoopRecvIed::lineIedToSwitch() const
{ return m_pLineIedToSwitch;}

inline void VirLoopRecvIed::setLineIedToSwitch(FibreOptical *lineIedToSwitch)
{ m_pLineIedToSwitch = lineIedToSwitch;}

inline GooseInfo * VirLoopRecvIed::gooseInfo() const
{ return m_pGooseInfo;}

inline void VirLoopRecvIed::setGooseInfo(GooseInfo *gooseInfo)
{ m_pGooseInfo = gooseInfo;}

inline Ied * VirLoopRecvIed::recvIed() const
{ return m_pRecvIed;}

inline void VirLoopRecvIed::setRecvIed(Ied *recvIed)
{ m_pRecvIed = recvIed;}

inline Strap * VirLoopRecvIed::recvStrap() const
{ return m_pRecvStrap;}

inline void VirLoopRecvIed::setRecvStrap(Strap *recvStrap)
{ m_pRecvStrap = recvStrap;}

inline OptPort * VirLoopRecvIed::recvPort() const
{ return m_pRecvPort;}

inline void VirLoopRecvIed::setRecvPort(OptPort *port)
{ m_pRecvPort = port;}

inline FibreOptical * VirLoopRecvIed::lineSwitchToIed() const
{ return m_pLineSwitchToIed;}

inline void VirLoopRecvIed::setLineSwitchToIed(FibreOptical *lineSwitchToIed)
{ m_pLineSwitchToIed = lineSwitchToIed;}

inline GooseInst * VirLoopRecvIed::gooseInst() const
{ return m_pGooseInst;}

inline void VirLoopRecvIed::setGooseInst(GooseInst *gooseInst)
{ m_pGooseInst = gooseInst;}

inline DevRunState * VirLoopRecvIed::recvIedGooseLinkAlarm() const
{ return m_pRecvIedGooseLinkAlarm;}

inline void VirLoopRecvIed::setRecvIedGooseLinkAlarm(DevRunState *recvIedGooseLinkAlarm)
{ m_pRecvIedGooseLinkAlarm = recvIedGooseLinkAlarm;}

inline const SwitchDevice::List & VirLoopRecvIed::lstSwitchDevice() const
{ return m_lstSwitchDevice;}
#endif // VIRLOOPRECVIED_H
