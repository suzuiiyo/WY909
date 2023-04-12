#include "virloopsendied.h"
VirLoopSendIed::VirLoopSendIed()
    : m_pSelfStrap(0)
    , m_pSelfPort(0)
    , m_pLineIedToSwitch(0)
    , m_pGooseInst(0)
    , m_pSelfGooseLinkAlarm(0)
    , m_pSendIed(0)
    , m_pSendStrap(0)
    , m_pSendPort(0)
    , m_pLineSwitchToIed(0)
    , m_pGooseInfo(0)
{

}

VirLoopSendIed::~VirLoopSendIed()
{
    delete m_pSelfStrap;
    delete m_pSelfPort;
    delete m_pLineIedToSwitch;
    delete m_pGooseInst;
    delete m_pSelfGooseLinkAlarm;
    delete m_pSendIed;
    delete m_pSendStrap;
    delete m_pSendPort;
    delete m_pLineSwitchToIed;
    delete m_pGooseInfo;
    clearSwitchDevice();
}

SwitchDevice * VirLoopSendIed::switchDev(const QString &iedName) const
{
    foreach (SwitchDevice *sDev, m_lstSwitchDevice) {
        if(sDev->iedName() == iedName)
            return sDev;
    }

    return NULL;
}

void VirLoopSendIed::addSwitchDevice(SwitchDevice *dev)
{
    m_lstSwitchDevice.append(dev);
}

void VirLoopSendIed::removeSwitchDevice(SwitchDevice *dev)
{
    m_lstSwitchDevice.removeAll(dev);
    delete dev;
}

void VirLoopSendIed::clearSwitchDevice()
{
    qDeleteAll(m_lstSwitchDevice);
    m_lstSwitchDevice.clear();
}
