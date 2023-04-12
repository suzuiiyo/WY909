#ifndef BAYINFO_H
#define BAYINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include "ied.h"
#include "primarydeviceinfo.h"
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include "ied.h"
#include "primarydeviceinfo.h"
class BayInfo
{
public:
    typedef QSharedPointer<BayInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    BayInfo();
    ~BayInfo();
public:
    int GUID() const;
    QString bayName() const;
    QString bayDesc() const;
    QString bayType() const;
    QString scheduleName() const;
    int bayState() const;
    int devCorrespondingState() const;
    QString belongMakeupBay() const;
    QString stationName() const;
    QString voltage() const;
//    QString fatherBay() const;
//    QString childBay() const;
//    int belongBranch() const;
public:
    void setGUID(int guid);
    void setBayName(const QString &bayName);
    void setBayDesc(const QString &bayDesc);
    void setBayType(const QString &bayType);
    void setScheduleName(const QString &scheduleName);
    void setBayState(int bayState);
    void setDevCorrespondingState(int devCorrespondingState);
    void setBelongMakeupBay(const QString &belongMakeupBay);
    void setStationName(const QString &stationName);
    void setVoltage(const QString &voltClass);
//    void setFatherBay(const QString &fatherBay);
//    void setChildBay(const QString &childBay);
//    void setBelongBranch(int belongBranch);
public:
    const QList<Ied*> & lstIed() const;
    void setLstIed(QList<Ied*> &lstIed);
    void addIed(Ied *ied);
    void removeIed(Ied *ied);
    void clearIed();
//public:
//    const QList<PrimaryDeviceInfo*> & lstPrimaryDeviceInfo() const;
//    void addPrimaryDeviceInfo(PrimaryDeviceInfo *primaryDeviceInfo);
//    void removePrimaryDeviceInfo(PrimaryDeviceInfo *primaryDeviceInfo);
//    void clearPrimaryDeviceInfo();
//public:
//    const QList<BayInfo*> & lstChildBayInfo() const;
//    void addChildBayInfo(BayInfo *childBayInfo);
//    void removeChildBayInfo(BayInfo *childBayInfo);
//    void clearChildBayInfo();
private:
    int m_GUID;
    QString m_bayName;
    QString m_bayDesc;
    QString m_bayType;
    QString m_scheduleName;
    QString m_belongMakeupBay;
    int m_bayState;
    QString m_stationName;
    QString m_voltage;
    int m_devCorrespondingState;
    QList<Ied*> m_lstIed;
    //QList<PrimaryDeviceInfo*> m_lstPrimaryDeviceInfo;
    //QList<BayInfo*> m_lstChildBayInfo;
private:
    friend class DBBayInfoDAO;
};

inline int BayInfo::GUID() const
{ return m_GUID;}

inline void BayInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString BayInfo::bayName() const
{ return m_bayName;}

inline void BayInfo::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString BayInfo::bayDesc() const
{ return m_bayDesc;}

inline void BayInfo::setBayDesc(const QString &bayDesc)
{ m_bayDesc = bayDesc;}

inline QString BayInfo::bayType() const
{ return m_bayType;}

inline void BayInfo::setBayType(const QString &bayType)
{ m_bayType = bayType;}

inline QString BayInfo::scheduleName() const
{ return m_scheduleName;}

inline void BayInfo::setScheduleName(const QString &scheduleName)
{ m_scheduleName = scheduleName;}

inline int BayInfo::bayState() const
{ return m_bayState;}

inline void BayInfo::setBayState(int bayState)
{ m_bayState = bayState;}

inline QString BayInfo::stationName() const
{ return m_stationName;}

inline void BayInfo::setStationName(const QString &stationName)
{ m_stationName = stationName;}

inline QString BayInfo::voltage() const
{ return m_voltage;}

inline void BayInfo::setVoltage(const QString &voltage)
{ m_voltage = voltage;}

inline int BayInfo::devCorrespondingState() const
{ return m_devCorrespondingState;}

inline void BayInfo::setDevCorrespondingState(int devCorrespondingState)
{ m_devCorrespondingState = devCorrespondingState;}

//inline QString BayInfo::fatherBay() const
//{ return m_fatherBay;}

//inline void BayInfo::setFatherBay(const QString &fatherBay)
//{ m_fatherBay = fatherBay;}

//inline QString BayInfo::childBay() const
//{ return m_childBay;}

//inline void BayInfo::setChildBay(const QString &childBay)
//{ m_childBay = childBay;}

//inline int BayInfo::belongBranch() const
//{ return m_belongBranch;}

//inline void BayInfo::setBelongBranch(int belongBranch)
//{ m_belongBranch = belongBranch;}

inline QString BayInfo::belongMakeupBay() const
{ return m_belongMakeupBay;}

inline void BayInfo::setBelongMakeupBay(const QString &belongMakeupBay)
{ m_belongMakeupBay = belongMakeupBay;}

inline const QList<Ied*> & BayInfo::lstIed() const
{ return m_lstIed;}

inline void BayInfo::setLstIed(QList<Ied *> &lstIed)
{ m_lstIed = lstIed;}
//inline const QList<PrimaryDeviceInfo*> & BayInfo::lstPrimaryDeviceInfo() const
//{ return m_lstPrimaryDeviceInfo;}

//inline const QList<BayInfo*> & BayInfo::lstChildBayInfo() const
//{ return m_lstChildBayInfo;}
#endif // BAYINFO_H
