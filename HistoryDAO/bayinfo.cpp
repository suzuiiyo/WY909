#include "bayinfo.h"
BayInfo::BayInfo()
    : m_bayState(-1)
    , m_devCorrespondingState(-1)
{

}

BayInfo::~BayInfo()
{
    //clearChildBayInfo();
    clearIed();
    //clearPrimaryDeviceInfo();
}


void BayInfo::addIed(Ied *ied)
{
    m_lstIed.append(ied);
}

//void BayInfo::addPrimaryDeviceInfo(PrimaryDeviceInfo *primaryDeviceInfo)
//{
//    m_lstPrimaryDeviceInfo.append(primaryDeviceInfo);
//}

//void BayInfo::addChildBayInfo(BayInfo *childBayInfo)
//{
//    m_lstChildBayInfo.append(childBayInfo);
//}

void BayInfo::removeIed(Ied *ied)
{
    m_lstIed.removeAll(ied);
    delete ied;
}

//void BayInfo::removePrimaryDeviceInfo(PrimaryDeviceInfo *primaryDeviceInfo)
//{
//    m_lstPrimaryDeviceInfo.removeAll(primaryDeviceInfo);
//    delete primaryDeviceInfo;
//}

//void BayInfo::removeChildBayInfo(BayInfo *childBayInfo)
//{
//    m_lstChildBayInfo.removeAll(childBayInfo);
//    delete childBayInfo;
//}

void BayInfo::clearIed()
{
    qDeleteAll(m_lstIed);
    m_lstIed.clear();
}

//void BayInfo::clearPrimaryDeviceInfo()
//{
//    qDeleteAll(m_lstPrimaryDeviceInfo);
//    m_lstPrimaryDeviceInfo.clear();
//}

//void BayInfo::clearChildBayInfo()
//{
//    qDeleteAll(m_lstChildBayInfo);
//    m_lstChildBayInfo.clear();
//}
