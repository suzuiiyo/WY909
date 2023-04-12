#include <QString>
#include "ieddataset.h"
IedDataSet::IedDataSet()
{

}

IedDataSet::IedDataSet(int earlyWarningType)
    : m_earlyWarningType(earlyWarningType)
{

}

IedDataSet::IedDataSet(const QString &iedName, const QString &dataRef, const QString &dataDesc, const QString &LDevice, const QString &dataType, const QString &dataUnit)
    : m_iedName(iedName), m_dataRef(dataRef), m_dataDesc(dataDesc), m_LDevice(LDevice), m_dataType(dataType), m_dataUnit(dataUnit), m_earlyWarningType(-1)
{

}

IedDataSet::~IedDataSet()
{
    this->clearDAStruct();
}

void IedDataSet::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void IedDataSet::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void IedDataSet::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}


