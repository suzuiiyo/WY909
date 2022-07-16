#include <QString>
#include "virloopiedinfo.h"
#include "gooseinst.h"
VirLoopIedInfo::VirLoopIedInfo()
    : m_pIed(0)
{

}

VirLoopIedInfo::~VirLoopIedInfo()
{
    delete m_pIed;
    clearRecvIed();
    clearSendIed();
}

//VirLoopRecvIed *VirLoopIedInfo::recvIed(const QString &iedName) const
//{
//    foreach (VirLoopRecvIed *recvIed, m_lstRecvIed)
//    {
//        if(recvIed->m_pRecvIed->iedName() == iedName)
//            return recvIed;
//    }

//    return NULL;
//}

//VirLoopSendIed *VirLoopIedInfo::sendIed(const QString &iedName) const
//{
//    foreach (VirLoopSendIed *sendIed, m_lstSendIed)
//    {
//        if(sendIed->m_pSendIed->iedName() == iedName)
//            return sendIed;
//    }

//    return NULL;
//}

void VirLoopIedInfo::addRecvIed(VirLoopRecvIed *recvIed)
{
    m_lstRecvIed.append(recvIed);
}

void VirLoopIedInfo::addSendIed(VirLoopSendIed *sendIed)
{
    m_lstSendIed.append(sendIed);
}

void VirLoopIedInfo::removeRecvIed(VirLoopRecvIed *recvIed)
{
    m_lstRecvIed.removeAll(recvIed);
    delete recvIed;
}

void VirLoopIedInfo::removeSendIed(VirLoopSendIed *sendIed)
{
    m_lstSendIed.removeAll(sendIed);
    delete sendIed;
}

void VirLoopIedInfo::clearRecvIed()
{
    qDeleteAll(m_lstRecvIed);
    m_lstRecvIed.clear();
}

void VirLoopIedInfo::clearSendIed()
{
    qDeleteAll(m_lstSendIed);
    m_lstSendIed.clear();
}
