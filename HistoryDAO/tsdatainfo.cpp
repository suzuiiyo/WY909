#include "tsdatainfo.h"
TSDataInfo::TSDataInfo()
{

}

TSDataInfo::~TSDataInfo()
{
    clearDAStruct();
}

void TSDataInfo::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void TSDataInfo::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void TSDataInfo::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void TSDataInfo::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void TSDataInfo::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
