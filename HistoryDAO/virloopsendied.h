#ifndef VIRLOOPSENDIED_H
#define VIRLOOPSENDIED_H
#include "ied.h"
#include "strap.h"
#include "optport.h"
#include "fibreoptical.h"
#include "gooseinfo.h"
#include "gooseinst.h"
#include "switchdevice.h"
#include "devrunstate.h"
class VirLoopSendIed
{
public:
    typedef QList<VirLoopSendIed*> List;
public:
    VirLoopSendIed();
    ~VirLoopSendIed();
public:
    //bool isP2P() const;
    QString appId() const;
    Strap *selfStrap() const;
    OptPort *selfPort() const;
    FibreOptical *lineIedToSwitch() const;
    GooseInst *gooseInst() const;
    DevRunState *selfGooseLinkAlarm() const;
    Ied *sendIed() const;
    Strap *sendStrap() const;
    OptPort *sendPort() const;
    FibreOptical *lineSwitchToIed() const;
    GooseInfo *gooseInfo() const;
public:
    //void setIsP2P(bool result);
    void setAppId(const QString &appId);
    void setSelfStrap(Strap *selfStrap);
    void setSelfPort(OptPort *selfPort);
    void setLineIedToSwitch(FibreOptical *lineIedToSwitch);
    void setGooseInst(GooseInst *gooseInst);
    void setSelfGooseLinkAlarm(DevRunState *selfGooseLinkAlarm);
    void setSendIed(Ied *sendIed);
    void setSendStrap(Strap *sendStrap);
    void setSendPort(OptPort *port);
    void setLineSwitchToIed(FibreOptical *lineSwitchToIed);
    void setGooseInfo(GooseInfo *gooseInfo);
public:
    const SwitchDevice::List & lstSwitchDevice() const;
    SwitchDevice *switchDev(const QString &iedName) const;
    void addSwitchDevice(SwitchDevice *dev);
    void removeSwitchDevice(SwitchDevice *dev);
    void clearSwitchDevice();
private:
    QString m_appId;
    Strap *m_pSelfStrap;
    OptPort *m_pSelfPort;
    FibreOptical *m_pLineIedToSwitch;
    GooseInst *m_pGooseInst;
    DevRunState *m_pSelfGooseLinkAlarm;
    Ied *m_pSendIed;
    Strap *m_pSendStrap;
    OptPort *m_pSendPort;
    FibreOptical *m_pLineSwitchToIed;
    GooseInfo *m_pGooseInfo;
    SwitchDevice::List m_lstSwitchDevice;
private:
    friend class VirLoopIedInfo;
};
//inline bool VirLoopSendIed::isP2P() const
//{ return m_isP2P;}

//inline void VirLoopSendIed::setIsP2P(bool result)
//{ m_isP2P = result;}



inline QString VirLoopSendIed::appId() const
{ return m_appId;}

inline void VirLoopSendIed::setAppId(const QString &appId)
{ m_appId = appId;}

inline Strap * VirLoopSendIed::selfStrap() const
{ return m_pSelfStrap;}

inline void VirLoopSendIed::setSelfStrap(Strap *selfStrap)
{ m_pSelfStrap = selfStrap;}

inline OptPort * VirLoopSendIed::selfPort() const
{ return m_pSelfPort;}

inline void VirLoopSendIed::setSelfPort(OptPort *selfPort)
{ m_pSelfPort = selfPort;}

inline FibreOptical * VirLoopSendIed::lineIedToSwitch() const
{ return m_pLineIedToSwitch;}

inline void VirLoopSendIed::setLineIedToSwitch(FibreOptical *lineIedToSwitch)
{ m_pLineIedToSwitch = lineIedToSwitch;}

inline GooseInst * VirLoopSendIed::gooseInst() const
{ return m_pGooseInst;}

inline void VirLoopSendIed::setGooseInst(GooseInst *gooseInst)
{ m_pGooseInst = gooseInst;}

inline DevRunState * VirLoopSendIed::selfGooseLinkAlarm() const
{ return m_pSelfGooseLinkAlarm;}

inline void VirLoopSendIed::setSelfGooseLinkAlarm(DevRunState *selfGooseLinkAlarm)
{ m_pSelfGooseLinkAlarm = selfGooseLinkAlarm;}

inline Ied * VirLoopSendIed::sendIed() const
{ return m_pSendIed;}

inline void VirLoopSendIed::setSendIed(Ied *sendIed)
{ m_pSendIed = sendIed;}

inline Strap * VirLoopSendIed::sendStrap() const
{ return m_pSendStrap;}

inline void VirLoopSendIed::setSendStrap(Strap *sendStrap)
{ m_pSendStrap = sendStrap;}

inline OptPort * VirLoopSendIed::sendPort() const
{ return m_pSendPort;}

inline void VirLoopSendIed::setSendPort(OptPort *port)
{ m_pSendPort = port;}

inline FibreOptical * VirLoopSendIed::lineSwitchToIed() const
{ return m_pLineSwitchToIed;}

inline void VirLoopSendIed::setLineSwitchToIed(FibreOptical *lineSwitchToIed)
{ m_pLineSwitchToIed = lineSwitchToIed;}

inline GooseInfo * VirLoopSendIed::gooseInfo() const
{ return m_pGooseInfo;}

inline void VirLoopSendIed::setGooseInfo(GooseInfo *gooseInfo)
{ m_pGooseInfo = gooseInfo;}

inline const SwitchDevice::List & VirLoopSendIed::lstSwitchDevice() const
{ return m_lstSwitchDevice;}
#endif // VIRLOOPSENDIED_H
