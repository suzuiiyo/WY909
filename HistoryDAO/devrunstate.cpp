#include "devrunstate.h"
DevRunState::DevRunState()
{

}

DevRunState::~DevRunState()
{
    clearDAStruct();
}


void DevRunState::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void DevRunState::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void DevRunState::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void DevRunState::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void DevRunState::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
