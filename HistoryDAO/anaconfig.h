#ifndef ANACONFIG_H
#define ANACONFIG_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class AnaConfig
{
public:
    typedef QSharedPointer<AnaConfig> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    AnaConfig();
    ~AnaConfig();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
private:
    int m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
private:
    friend class DBAnaConfigDAO;
};

inline int AnaConfig::GUID() const
{ return m_GUID;}

inline void AnaConfig::setGUID(int guid)
{ m_GUID = guid;}

inline QString AnaConfig::iedName() const
{ return m_iedName;}

inline void AnaConfig::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString AnaConfig::dataRef() const
{ return m_dataRef;}

inline void AnaConfig::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString AnaConfig::dataDesc() const
{ return m_dataDesc;}

inline void AnaConfig::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}
#endif // ANACONFIG_H
