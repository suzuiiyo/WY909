#ifndef RCDINFO_H
#define RCDINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QVector>
class RCDInfo
{
public:
    typedef QSharedPointer<RCDInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    RCDInfo();
    ~RCDInfo();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dimension() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDimension(const QString &dimension);
private:
    int m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dimension;
private:
    friend class DBRCDInfoDAO;
};
inline int RCDInfo::GUID() const
{ return m_GUID;}

inline void RCDInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString RCDInfo::iedName() const
{ return m_iedName;}

inline void RCDInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString RCDInfo::dataRef() const
{ return m_dataRef;}

inline void RCDInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString RCDInfo::dataDesc() const
{ return m_dataDesc;}

inline void RCDInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString RCDInfo::dimension() const
{ return m_dimension;}

inline void RCDInfo::setDimension(const QString &dimension)
{ m_dimension = dimension;}
#endif // RCDINFO_H
