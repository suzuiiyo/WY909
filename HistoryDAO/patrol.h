#ifndef PATROL_H
#define PATROL_H
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QString>
class Patrol
{
public:
    typedef QSharedPointer<Patrol> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    Patrol();
    ~Patrol();
public:
    int GUID() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataType() const;
    QString dataDetail() const;
    QString iedName() const;
    int standardValueType() const;
    QString standardValue() const;
    QString purpose() const;
    int configDataType() const;
    int configDataDetail() const;
    QString unicodeDesc() const;
public:
    void setGUID(int guid);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataType(const QString &dataType);
    void setDataDetail(const QString &dataDetail);
    void setIedName(const QString &iedName);
    void setStandardValueType(int standardValueType);
    void setStandardValue(const QString &standardValue);
    void setPurpose(const QString &purpose);
    void setConfigDataType(int configDataType);
    void setConfigDataDetail(int configDataDetail);
    void setUnicodeDesc(const QString &unicodeDesc);
private:
    int         m_GUID;
    QString     m_dataRef;
    QString     m_dataDesc;
    QString     m_dataType;
    QString     m_dataDetail;
    QString     m_iedName;
    int         m_standardValueType;
    QString     m_standardValue;
    QString     m_purpose;
    int         m_configDataType;
    int         m_configDataDetail;
    QString     m_unicodeDesc;

private:
    friend class DBPatrolDAO;
};

inline int Patrol::GUID() const
{ return m_GUID;}

inline void Patrol::setGUID(int guid)
{ m_GUID = guid;}

inline QString Patrol::dataRef() const
{ return m_dataRef;}

inline void Patrol::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString Patrol::dataDesc() const
{ return m_dataDesc;}

inline void Patrol::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString Patrol::dataType() const
{ return m_dataType;}

inline void Patrol::setDataType(const QString &dataType)
{ m_dataType = dataType;}

inline QString Patrol::dataDetail() const
{ return m_dataDetail;}

inline void Patrol::setDataDetail(const QString &dataDetail)
{ m_dataDetail = dataDetail;}

inline QString Patrol::iedName() const
{ return m_iedName;}

inline void Patrol::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline int Patrol::standardValueType() const
{ return m_standardValueType;}

inline void Patrol::setStandardValueType(int standardValueType)
{ m_standardValueType = standardValueType;}

inline QString Patrol::standardValue() const
{ return m_standardValue;}

inline void Patrol::setStandardValue(const QString &standardValue)
{ m_standardValue = standardValue;}

inline QString Patrol::purpose() const
{ return m_purpose;}

inline void Patrol::setPurpose(const QString &purpose)
{ m_purpose = purpose;}

inline int Patrol::configDataType() const
{ return m_configDataType;}

inline void Patrol::setConfigDataType(int configDataType)
{ m_configDataType = configDataType;}

inline int Patrol::configDataDetail() const
{ return m_configDataDetail;}

inline void Patrol::setConfigDataDetail(int configDataDetail)
{ m_configDataDetail = configDataDetail;}

inline QString Patrol::unicodeDesc() const
{ return m_unicodeDesc;}

inline void Patrol::setUnicodeDesc(const QString &unicodeDesc)
{ m_unicodeDesc = unicodeDesc;}
#endif // PATROL_H
