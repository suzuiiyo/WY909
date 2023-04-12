#include "gooseinfo.h"
GooseInfo::GooseInfo()
{

}

GooseInfo::~GooseInfo()
{
    clearDAStruct();
}

void GooseInfo::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void GooseInfo::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void GooseInfo::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
