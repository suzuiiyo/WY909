#include "memoryied.h"
MemoryIed::MemoryIed()
    : m_connectionState(-1)
{

}

MemoryIed::~MemoryIed()
{

}

void MemoryIed::addFCDA(MemoryFCDA *fcda)
{
    m_hashMemoryFCDA.insert(fcda->refName(), fcda);
}

//void MemoryIed::removeDAStruct(DAStruct *daStruct)
//{
//    m_lstDAStruct.removeAll(daStruct);
//    delete daStruct;
//}

void MemoryIed::clearFCDA()
{
    qDeleteAll(m_hashMemoryFCDA);
    m_hashMemoryFCDA.clear();
}
