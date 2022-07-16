#include "alarminfo.h"
AlarmInfo::AlarmInfo()
{

}

AlarmInfo::~AlarmInfo()
{
    clearDAStruct();
}

void AlarmInfo::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void AlarmInfo::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void AlarmInfo::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void AlarmInfo::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void AlarmInfo::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
