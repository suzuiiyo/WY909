#include "primarydeviceinfo.h"
PrimaryDeviceInfo::PrimaryDeviceInfo()
{

}

PrimaryDeviceInfo::~PrimaryDeviceInfo()
{
    clearGooseInfo();
}

void PrimaryDeviceInfo::addDataRef(const QString &dataRef)
{
    if(!m_lstDataRef.contains(dataRef))
        m_lstDataRef.append(dataRef);
}

void PrimaryDeviceInfo::addGooseInfo(GooseInfo *gooseInfo)
{
    m_lstGooseInfo.append(gooseInfo);
}


void PrimaryDeviceInfo::removeGooseInfo(GooseInfo *gooseInfo)
{
    m_lstGooseInfo.removeAll(gooseInfo);
    delete gooseInfo;
}


void PrimaryDeviceInfo::clearGooseInfo()
{
    qDeleteAll(m_lstGooseInfo);
    m_lstGooseInfo.clear();
}
