#ifndef MONITORINFO_H
#define MONITORINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
class MonitorInfo
{
public:
    typedef QSharedPointer<MonitorInfo> Ptr;
    typedef QList<Ptr> List;
public:
    MonitorInfo();
    ~MonitorInfo();
public:
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString dataUnit() const;
public:
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
    void setDataUnit(const QString &dataUnit);
private:
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_dataUnit;
private:
    friend class DBOnlineMonitorDAO;
};

inline QString MonitorInfo::iedName() const
{ return m_iedName;}

inline void MonitorInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString MonitorInfo::dataRef() const
{ return m_dataRef;}

inline void MonitorInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString MonitorInfo::dataDesc() const
{ return m_dataDesc;}

inline void MonitorInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString MonitorInfo::dataUnit() const
{ return m_dataUnit;}

inline void MonitorInfo::setDataUnit(const QString &dataUnit)
{ m_dataUnit = dataUnit;}
#endif // MONITORINFO_H
