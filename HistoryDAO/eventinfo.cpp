#include "eventinfo.h"
EventInfo::EventInfo()
{

}

EventInfo::~EventInfo()
{
    clearDAStruct();
}

void EventInfo::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void EventInfo::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

void EventInfo::addDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.append(daStruct);
}

void EventInfo::removeDAStruct(DAStruct *daStruct)
{
    m_lstDAStruct.removeAll(daStruct);
    delete daStruct;
}

void EventInfo::clearDAStruct()
{
    qDeleteAll(m_lstDAStruct);
    m_lstDAStruct.clear();
}
