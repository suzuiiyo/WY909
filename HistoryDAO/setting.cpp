#include "setting.h"
Setting::Setting()
    : m_maxSetting(0)
    , m_minSetting(0)
    , m_referenceValue(0)
    , m_stepSize(0)
{

}

Setting::~Setting()
{
    clearDAStruct();
}

void Setting::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void Setting::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void Setting::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void Setting::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void Setting::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
