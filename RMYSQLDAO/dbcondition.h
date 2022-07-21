#ifndef DBCONDITION_H
#define DBCONDITION_H
#include <QString>
#include <QSharedPointer>

class DBOrmOperation
{
public:
    typedef QSharedPointer<DBOrmOperation> Ptr;
    typedef QList<Ptr> List;
public:
    enum OpType
    {
        add,
        seq,
        reduce,
        likes,
        notSeq,
        lessThan,
        greaterThan,
        lessThanSeq,
        greaterThanSeq
    };
public:
    enum DataType
    {
        Unknown,
        Int,
        Int8,
        Int16,
        Int32,
        Int64,
        Char,
        Float,
        Double
    };
public:
    enum LinkType
    {
        NotHave,
        LP,
        And,
        Or,
        LPAnd,
        LPOr
    };
public:
    DBOrmOperation();
public:
    qint8   strToInt8();
    qint16  strToInt16();
    qint32  strToInt32();
    qint64  strToInt64();
    float   strToFloat();
    double  strToDouble();
public:
    void int8ToStr(qint8 data);
    void int16ToStr(qint16 data);
    void int32ToStr(qint32 data);
    void int64ToStr(qint64 data);
    void floatToStr(float data);
    void doubleToStr(double data);
    void setValue(const QString &value);
public:
    bool        isRp() const;
    int         dataId() const;
    DataType    dataType() const;
    QString     value() const;
    OpType      opType() const;
    QString     opStr();
    LinkType    linkType() const;
    QString     linkStr() const;
    QString     endStr() const;
public:
    void setIsRP(bool isRP);
    void setDataId(int dataId);
    void setDataType(const DataType &dataType);
    void setOpType(const OpType &opType);
    void setLinkType(const LinkType &linkType);
private:
    bool        m_isRP;
    int         m_dataId;
    DataType    m_dataType;
    QString     m_value;
    OpType      m_opType;
    LinkType    m_linkType;
private:
    QHash<OpType, QString>      m_lstOp;
    QHash<LinkType, QString>    m_lstLinkType;
};

inline bool DBOrmOperation::isRp() const
{ return m_isRP;}

inline void DBOrmOperation::setIsRP(bool isRP)
{ m_isRP = isRP;}

inline int DBOrmOperation::dataId() const
{ return m_dataId;}

inline void DBOrmOperation::setDataId(int dataId)
{ m_dataId = dataId;}

inline DBOrmOperation::DataType DBOrmOperation::dataType() const
{ return m_dataType;}

inline void DBOrmOperation::setDataType(const DBOrmOperation::DataType &dataType)
{ m_dataType = dataType;}

inline QString DBOrmOperation::value() const
{ return m_value;}

inline DBOrmOperation::OpType DBOrmOperation::opType() const
{ return m_opType;}

inline void DBOrmOperation::setOpType(const OpType &opType)
{ m_opType = opType;}

inline DBOrmOperation::LinkType DBOrmOperation::linkType() const
{ return m_linkType;}

inline void DBOrmOperation::setLinkType(const LinkType &linkType)
{ m_linkType = linkType;}

inline QString DBOrmOperation::endStr() const
{ return m_isRP ? ")" : "";}

inline void DBOrmOperation::setValue(const QString &value)
{ m_value = value;}

class DBCondition
{
public:
    enum DataType
    {
        Unknown,
        Int,
        Char
    };
public:
    DBCondition()
        : m_type(Unknown)
    {}
    ~DBCondition(){}
public:
    QString     name() const;
    DataType    type() const;
public:
    void setName(const QString &name);
    void setType(const DataType &dataType);
private:
    QString     m_name;
    DataType    m_type;
};

inline QString DBCondition::name() const
{ return m_name;}

inline void DBCondition::setName(const QString &name)
{ m_name = name;}

inline DBCondition::DataType DBCondition::type() const
{ return m_type;}

inline void DBCondition::setType(const DBCondition::DataType &type)
{ m_type = type;}
#endif // DBCONDITION_H
