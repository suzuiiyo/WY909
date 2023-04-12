#include "memoryfcda.h"
MemoryFCDA::MemoryFCDA()
{

}

MemoryFCDA::~MemoryFCDA()
{
    clearDAStruct();
}

void MemoryFCDA::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void MemoryFCDA::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void MemoryFCDA::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
