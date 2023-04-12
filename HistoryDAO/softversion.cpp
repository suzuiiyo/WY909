#include "softversion.h"
SoftVersion::SoftVersion()
    : m_GUID(0)
    , m_type(255)
    , m_selfType(255)
{

}

SoftVersion::~SoftVersion()
{
    clearDAStruct();
}

void SoftVersion::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void SoftVersion::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void SoftVersion::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
