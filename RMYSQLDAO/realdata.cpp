#include "realdata.h"
RealData::RealData()
    : m_GUID(0)
{

}

RealData::~RealData()
{

}


void RealData::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void RealData::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}
