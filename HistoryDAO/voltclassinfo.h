#ifndef VOLTCLASSINFO_H
#define VOLTCLASSINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class VoltClassInfo
{
public:
    typedef QSharedPointer<VoltClassInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    VoltClassInfo();
    ~VoltClassInfo();
public:
    int GUID() const;
    QString voltClass() const;
    QString voltage() const;
public:
    void setGUID(int guid);
    void setVoltClass(const QString &voltClass);
    void setVoltage(const QString &voltage);
private:
    int m_GUID;
    QString m_voltClass;
    QString m_voltage;
private:
    friend class DBVoltClassInfoDAO;
};

inline int VoltClassInfo::GUID() const
{ return m_GUID;}

inline void VoltClassInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString VoltClassInfo::voltClass() const
{ return m_voltClass;}

inline void VoltClassInfo::setVoltClass(const QString &voltClass)
{ m_voltClass = voltClass;}

inline QString VoltClassInfo::voltage() const
{ return m_voltage;}

inline void VoltClassInfo::setVoltage(const QString &voltage)
{ m_voltage = voltage;}
#endif // VOLTCLASSINFO_H
