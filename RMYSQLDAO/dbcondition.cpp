#include "dbcondition.h"

DBOrmOperation::DBOrmOperation()
    : m_isRP(false)
    , m_dataId(-1)
{
    m_lstOp.insert(OpType::add, "+");
    m_lstOp.insert(OpType::seq, "=");
    m_lstOp.insert(OpType::reduce, "-");
    m_lstOp.insert(OpType::likes, " likes ");
    m_lstOp.insert(OpType::notSeq, "!=");
    m_lstOp.insert(OpType::lessThan, "<");
    m_lstOp.insert(OpType::greaterThan, ">");
    m_lstOp.insert(OpType::lessThanSeq, "<=");
    m_lstOp.insert(OpType::greaterThanSeq, ">=");

    m_lstLinkType.insert(LinkType::NotHave, " ");
    m_lstLinkType.insert(LinkType::LP, " (");
    m_lstLinkType.insert(LinkType::And, " AND ");
    m_lstLinkType.insert(LinkType::Or, " OR ");
    m_lstLinkType.insert(LinkType::LPAnd, " AND (");
    m_lstLinkType.insert(LinkType::LPOr, " OR (");
}

qint8 DBOrmOperation::strToInt8()
{
    return m_value.toInt();
}

qint16 DBOrmOperation::strToInt16()
{
    return m_value.toInt();
}

qint32 DBOrmOperation::strToInt32()
{
    return m_value.toInt();
}

qint64 DBOrmOperation::strToInt64()
{
    return m_value.toInt();
}

float DBOrmOperation::strToFloat()
{
    return m_value.toFloat();
}

double DBOrmOperation::strToDouble()
{
    return m_value.toDouble();
}

void DBOrmOperation::int8ToStr(qint8 data)
{
    m_value = QString::number(data);
}

void DBOrmOperation::int16ToStr(qint16 data)
{
    m_value = QString::number(data);
}

void DBOrmOperation::int32ToStr(qint32 data)
{
    m_value = QString::number(data);
}

void DBOrmOperation::int64ToStr(qint64 data)
{
    m_value = QString::number(data);
}

void DBOrmOperation::floatToStr(float data)
{
    m_value = QString::number(data);
}

void DBOrmOperation::doubleToStr(double data)
{
    m_value = QString::number(data);
}

QString DBOrmOperation::opStr()
{
    if(m_lstOp.contains(m_opType))
        return m_lstOp[m_opType];

    return "";
}

QString DBOrmOperation::linkStr() const
{
    if(m_lstLinkType.contains(m_linkType))
        return m_lstLinkType[m_linkType];

    return " ";
}
