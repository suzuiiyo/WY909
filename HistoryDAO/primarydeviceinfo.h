#ifndef PRIMARYDEVICEINFO_H
#define PRIMARYDEVICEINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QStringList>
#include "gooseinfo.h"
class PrimaryDeviceInfo
{
public:
    typedef QSharedPointer<PrimaryDeviceInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    PrimaryDeviceInfo();
    ~PrimaryDeviceInfo();
public:
    int GUID() const;
    QString devName() const;
    QString devDesc() const;
    QString scheduleName() const;
    QString devType() const;
    QString stationName() const;
    QString voltClass() const;
    QString bayName() const;
public:
    void setGUID(int guid);
    void setDevName(const QString &devName);
    void setDevDesc(const QString &devDesc);
    void setScheduleName(const QString &scheduleName);
    void setDevType(const QString &devType);
    void setStationName(const QString &stationName);
    void setVoltClass(const QString &voltClass);
    void setBayName(const QString &bayName);
public:
    const QStringList & lstDataRef() const;
    void addDataRef(const QString &dataRef);
    void clearDataRef();
public:
    const QList<GooseInfo*> & lstGooseInfo() const;
    void addGooseInfo(GooseInfo *gooseInfo);
    void removeGooseInfo(GooseInfo *gooseInfo);
    void clearGooseInfo();
private:
    int m_GUID;
    QString m_devName;
    QString m_devDesc;
    QString m_scheduleName;
    QString m_devType;
    QString m_stationName;
    QString m_voltClass;
    QString m_bayName;
    QStringList m_lstDataRef;
    QList<GooseInfo*> m_lstGooseInfo;
private:
    friend class DBPrimaryDeviceInfoDAO;
};

inline int PrimaryDeviceInfo::GUID() const
{ return m_GUID;}

inline void PrimaryDeviceInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString PrimaryDeviceInfo::devName() const
{ return m_devName;}

inline void PrimaryDeviceInfo::setDevName(const QString &devName)
{ m_devName = devName;}

inline QString PrimaryDeviceInfo::devDesc() const
{ return m_devDesc;}

inline void PrimaryDeviceInfo::setDevDesc(const QString &devDesc)
{ m_devDesc = devDesc;}

inline QString PrimaryDeviceInfo::scheduleName() const
{ return m_scheduleName;}

inline void PrimaryDeviceInfo::setScheduleName(const QString &scheduleName)
{ m_scheduleName = scheduleName;}

inline QString PrimaryDeviceInfo::devType() const
{ return m_devType;}

inline void PrimaryDeviceInfo::setDevType(const QString &devType)
{ m_devType = devType;}

inline const QStringList & PrimaryDeviceInfo::lstDataRef() const
{ return m_lstDataRef;}

inline void PrimaryDeviceInfo::clearDataRef()
{ m_lstDataRef.clear();}

inline QString PrimaryDeviceInfo::stationName() const
{ return m_stationName;}

inline void PrimaryDeviceInfo::setStationName(const QString &stationName)
{ m_stationName = stationName;}

inline QString PrimaryDeviceInfo::voltClass() const
{ return m_voltClass;}

inline void PrimaryDeviceInfo::setVoltClass(const QString &voltClass)
{ m_voltClass = voltClass;}

inline QString PrimaryDeviceInfo::bayName() const
{ return m_bayName;}

inline void PrimaryDeviceInfo::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline const QList<GooseInfo*> & PrimaryDeviceInfo::lstGooseInfo() const
{ return m_lstGooseInfo;}
#endif // PRIMARYDEVICEINFO_H
