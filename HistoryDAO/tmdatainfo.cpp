#include "tmdatainfo.h"
TMDataInfo::TMDataInfo()
{

}

TMDataInfo::~TMDataInfo()
{
    clearDAStruct();
}

void TMDataInfo::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void TMDataInfo::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void TMDataInfo::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void TMDataInfo::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void TMDataInfo::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
