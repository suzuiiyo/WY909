#ifndef DASTRUCT_H
#define DASTRUCT_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class DAStruct
{
public:
    typedef QSharedPointer<DAStruct> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    enum {
        UNKNOWNTYPE,
        BOOLEAN,
        BIT_STRING,
        INTEGER8,
        INTEGER16,
        INTEGER32,
        INTEGER64,
        UNSIGNED8,
        UNSIGNED16,
        UNSIGNED32,
        UNSIGNED64,
        FLOAT,
        DOUBLE,
        OCTET_STRING,
        VISIBLE_STRING,
        GENERAL_TIME,
        BINARY_TIME4,
        BINARY_TIME6,
        BCD1,
        BCD2,
        BCD4,
        UTCTIME,
        UTF8_STRING,
        ARRAY
    };
public:
    DAStruct();
    ~DAStruct();
public:
    int GUID() const;
    QString dataRef() const;
    QString attributeRef() const;
    QString dataType() const;
    QString dataValue() const;
public:
    void setGUID(int guid);
    void setDataRef(const QString &dataRef);
    void setAttributeRef(const QString &attributeRef);
    void setDataType(const QString &dataType);
    void setDataValue(const QString &dataValue);
private:
    int m_GUID;
    QString m_dataRef;
    QString m_attributeRef;
    QString m_dataType;
    QString m_dataValue;
private:
    friend class DBDAStructDAO;
};

inline int DAStruct::GUID() const
{ return m_GUID;}

inline void DAStruct::setGUID(int guid)
{ m_GUID = guid;}

inline QString DAStruct::dataRef() const
{ return m_dataRef;}

inline void DAStruct::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString DAStruct::attributeRef() const
{ return m_attributeRef;}

inline void DAStruct::setAttributeRef(const QString &attributeRef)
{ m_attributeRef = attributeRef;}

inline QString DAStruct::dataType() const
{ return m_dataType;}

inline void DAStruct::setDataType(const QString &dataType)
{ m_dataType = dataType;}

inline QString DAStruct::dataValue() const
{ return m_dataValue;}

inline void DAStruct::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}
#endif // DASTRUCT_H
