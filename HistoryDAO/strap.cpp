#include "strap.h"
Strap::Strap()
{

}

Strap::~Strap()
{
    clearDAStruct();
}

void Strap::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void Strap::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void Strap::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void Strap::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void Strap::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
