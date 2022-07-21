#include "otherdatainfo.h"
OtherDataInfo::OtherDataInfo()
{

}

OtherDataInfo::~OtherDataInfo()
{
    clearDAStruct();
}

void OtherDataInfo::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void OtherDataInfo::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void OtherDataInfo::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void OtherDataInfo::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void OtherDataInfo::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
