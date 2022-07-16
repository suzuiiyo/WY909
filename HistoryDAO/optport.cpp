#include <QString>
#include "optport.h"
OptPort::OptPort()
    : m_sendMax(0)
    , m_sendMin(0)
    , m_recvMax(0)
    , m_recvMin(0)
    , m_netType(-1)
{

}

OptPort::OptPort(const QString &sendValue, const QString &recvValue, const QString &sendUpAlarmValue, const QString &sendDownAlarmValue, const QString &recvUpAlarmValue, const QString &recvDownAlarmValue)
{
    addDataType(11);
    addDataValue(sendValue);

    addDataType(11);
    addDataValue(recvValue);

    addDataType(1);
    addDataValue(sendUpAlarmValue);

    addDataType(1);
    addDataValue(sendDownAlarmValue);

    addDataType(1);
    addDataValue(recvUpAlarmValue);

    addDataType(1);
    addDataValue(recvDownAlarmValue);
}

OptPort::~OptPort()
{

}

void OptPort::addDataType(int dataType)
{
    m_lstDataType.append(dataType);
}

void OptPort::addDataValue(const QString &dataValue)
{
    m_lstDataValue.append(dataValue);
}

//void OptPort::addDAStruct(DAStruct *daStruct)
//{
//    m_lstDAStruct.append(daStruct);
//}

//void OptPort::removeDAStruct(DAStruct *daStruct)
//{
//    m_lstDAStruct.removeAll(daStruct);
//    delete daStruct;
//}

//void OptPort::clearDAStruct()
//{
//    qDeleteAll(m_lstDAStruct);
//    m_lstDAStruct.clear();
//}
