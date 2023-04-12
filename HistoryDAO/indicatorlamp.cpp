#include "indicatorlamp.h"
IndicatorLamp::IndicatorLamp()
{

}

IndicatorLamp::~IndicatorLamp()
{
    clearDAStruct();
}

void IndicatorLamp::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void IndicatorLamp::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void IndicatorLamp::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void IndicatorLamp::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void IndicatorLamp::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
