#include <QString>
#include "ied.h"
Ied::Ied()
    : m_GUID(0)
    , m_isConnected(false)
    , m_iedState(0)
    , m_shouldIedState(0)
    , m_hadGi(0)
{

}

Ied::~Ied()
{
    clearStrap();
}

void Ied::addStrap(Strap *strap)
{
    m_lstStrap.append(strap);
}


void Ied::removeStrap(Strap *strap)
{
    m_lstStrap.removeAll(strap);
    delete strap;
}

void Ied::clearStrap()
{
    qDeleteAll(m_lstStrap);
    m_lstStrap.clear();
}

QString Ied::netTypeIp() const
{
    QString ipTmp = "";
    if(m_netType == "A")
        ipTmp = m_ipA;
    else if(m_netType == "B")
        ipTmp = m_ipB;
    else
        ipTmp = m_ipC;

    return ipTmp;
}

//void Ied::addDataRef(const QString &dataRef)
//{
//    m_lstDataRef.append(dataRef);
//}

//void Ied::addDevName(const QString &devName)
//{
//    m_lstDevName.append(devName);
//}

//void Ied::addDevScheduleName(const QString &devScheduleName)
//{
//    m_lstDevScheduleName.append(devScheduleName);
//}
