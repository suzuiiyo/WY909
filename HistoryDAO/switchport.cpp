#include "switchport.h"
SwitchPort::SwitchPort()
    : m_dataType(0)
{

}

SwitchPort::~SwitchPort()
{
    clearDAStruct();
}

void SwitchPort::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void SwitchPort::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void SwitchPort::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
