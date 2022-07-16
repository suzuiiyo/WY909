#include "virlooprecvied.h"
VirLoopRecvIed::VirLoopRecvIed()
    : m_pSelfStrap(0)
    , m_pSelfPort(0)
    , m_pLineIedToSwitch(0)
    , m_pGooseInfo(0)
    , m_pRecvIed(0)
    , m_pRecvStrap(0)
    , m_pRecvPort(0)
    , m_pLineSwitchToIed(0)
    , m_pGooseInst(0)
    , m_pRecvIedGooseLinkAlarm(0)
{

}

VirLoopRecvIed::~VirLoopRecvIed()
{
    delete m_pSelfStrap;
    delete m_pSelfPort;
    delete m_pLineIedToSwitch;
    delete m_pGooseInfo;
    delete m_pRecvIed;
    delete m_pRecvStrap;
    delete m_pRecvPort;
    delete m_pLineSwitchToIed;
    delete m_pGooseInst;
    delete m_pRecvIedGooseLinkAlarm;
    clearSwitchDevice();
}

SwitchDevice * VirLoopRecvIed::switchDev(const QString &iedName) const
{
    foreach (SwitchDevice *sDev, m_lstSwitchDevice) {
        if(sDev->iedName() == iedName)
            return sDev;
    }

    return NULL;
}

void VirLoopRecvIed::addSwitchDevice(SwitchDevice *dev)
{
    m_lstSwitchDevice.append(dev);
}

void VirLoopRecvIed::removeSwitchDevice(SwitchDevice *dev)
{
    m_lstSwitchDevice.removeAll(dev);
    delete dev;
}

void VirLoopRecvIed::clearSwitchDevice()
{
    qDeleteAll(m_lstSwitchDevice);
    m_lstSwitchDevice.clear();
}
