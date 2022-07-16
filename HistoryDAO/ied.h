#ifndef IED_H
#define IED_H
#include <QString>
#include <QList>
#include <QHash>
#include <QSharedPointer>
#include "ieddataset.h"
#include "strap.h"
class Ied
{
public:
    typedef QSharedPointer<Ied> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    Ied();
    ~Ied();
public:
    int GUID() const;
    QString iedName() const;
    QString iedDesc() const;
    QString iedCateGory() const;
    QString iedType() const;
    QString typeDetail() const;
    QString setType() const;
    QString manufacturer() const;
    QString productType() const;
    QString configVersion() const;
    QString VTerminalCRC() const;
    QString protocol() const;
    QString isRemoteSettings() const;
    QString stationName() const;
    QString voltClass() const;
    QString voltage() const;
    QString bayName() const;
    QString criterionTrip() const;
    QString criterionLock() const;
    QString criterionMaintain() const;
    QString criterionAlarm() const;
    QString criterionRun() const;
    QString ipA() const;
    QString ipB() const;
    QString ipC() const;
    QString netType() const;
    QString belongAllBays() const;
    QString deliveryDate() const;
    QString iedNameComp() const;
    bool isConnected() const;
    int iedState() const;
    int shouldIedState() const;
    int hadGi() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setIedDesc(const QString &iedDesc);
    void setIedCateGory(const QString &iedCateGory);
    void setIedType(const QString &iedType);
    void setTypeDetail(const QString &typeDetail);
    void setSetType(const QString &setType);
    void setManufacturer(const QString &manufacturer);
    void setProductType(const QString &productType);
    void setConfigVersion(const QString &configVersion);
    void setVTerminalCRC(const QString &VTerminalCRC);
    void setProtocol(const QString &protocol);
    void setIsRemoteSettings(const QString &isRemoteSettings);
    void setStationName(const QString &stationName);
    void setVoltClass(const QString &voltClass);
    void setVoltage(const QString &voltage);
    void setBayName(const QString &bayName);
    void setCriterionTrip(const QString &criterionTrip);
    void setCriterionLock(const QString &criterionLock);
    void setCriterionMaintain(const QString &criterionMaintain);
    void setCriterionAlarm(const QString &criterionAlarm);
    void setCriterionRun(const QString &criterionRun);
    void setIpA(const QString &ipA);
    void setIpB(const QString &ipB);
    void setIpC(const QString &ipC);
    void setNetType(const QString &netType);
    void setBelongAllBays(const QString &belongAllBays);
    void setDeliveryDate(const QString &deliveryDate);
    void setIedNameComp(const QString &iedNameComp);
    void setIsConnected(bool isConnected);
    void setIedState(int iedState);
    void setShouldIedState(int shouldIedState);
    void setHadGi(int hadGi);
public:
    const QList<Strap*> & lstStrap() const;
    void addStrap(Strap *strap);
    void setLstStrap(QList<Strap*> &lstStrap);
    void removeStrap(Strap *strap);
    void clearStrap();
public:
    QString netTypeIp() const;
private:
    int m_GUID;
    QString m_iedName;
    QString m_iedDesc;
    QString m_iedCateGory;
    QString m_iedType;
    QString m_typeDetail;
    QString m_setType;
    QString m_manufacturer;
    QString m_productType;
    QString m_configVersion;
    QString m_VTerminalCRC;
    QString m_protocol;
    QString m_isRemoteSettings;
    QString m_stationName;
    QString m_voltClass;
    QString m_voltage;
    QString m_bayName;
    QString m_criterionTrip;
    QString m_criterionLock;
    QString m_criterionMaintain;
    QString m_criterionAlarm;
    QString m_criterionRun;
    QString m_ipA;
    QString m_ipB;
    QString m_ipC;
    QString m_netType;
    QString m_belongAllBays;
    QString m_deliveryDate;
    QString m_iedNameComp;
    bool m_isConnected;
    int m_iedState;
    int m_shouldIedState;
    int m_hadGi;
    QList<Strap*> m_lstStrap;
private:
    friend class DBIedInfoDAO;
    friend class DBIedDataSetDAO;
    friend class DBStrapLightPlateDAO;
};

inline int Ied::GUID() const
{ return m_GUID;}

inline void Ied::setGUID(int guid)
{ m_GUID = guid;}

inline QString Ied::iedName() const
{ return m_iedName;}

inline void Ied::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString Ied::iedDesc() const
{ return m_iedDesc;}

inline void Ied::setIedDesc(const QString &iedDesc)
{ m_iedDesc = iedDesc;}

inline QString Ied::iedCateGory() const
{ return m_iedCateGory;}

inline void Ied::setIedCateGory(const QString &iedCateGory)
{ m_iedCateGory = iedCateGory;}

inline QString Ied::iedType() const
{ return m_iedType;}

inline void Ied::setIedType(const QString &iedType)
{ m_iedType = iedType;}

inline QString Ied::typeDetail() const
{ return m_typeDetail;}

inline void Ied::setTypeDetail(const QString &typeDetail)
{ m_typeDetail = typeDetail;}

inline QString Ied::setType() const
{ return m_setType;}

inline void Ied::setSetType(const QString &setType)
{ m_setType = setType;}

inline QString Ied::manufacturer() const
{ return m_manufacturer;}

inline void Ied::setManufacturer(const QString &manufacturer)
{ m_manufacturer = manufacturer;}

inline QString Ied::productType() const
{ return m_productType;}

inline void Ied::setProductType(const QString &productType)
{ m_productType = productType;}

inline QString Ied::configVersion() const
{ return m_configVersion;}

inline void Ied::setConfigVersion(const QString &configVersion)
{ m_configVersion = configVersion;}

inline QString Ied::VTerminalCRC() const
{ return m_VTerminalCRC;}

inline void Ied::setVTerminalCRC(const QString &VTerminalCRC)
{ m_VTerminalCRC = VTerminalCRC;}

inline QString Ied::protocol() const
{ return m_protocol;}

inline void Ied::setProtocol(const QString &protocol)
{ m_protocol = protocol;}

inline QString Ied::isRemoteSettings() const
{ return m_isRemoteSettings;}

inline void Ied::setIsRemoteSettings(const QString &isRemoteSettings)
{ m_isRemoteSettings = isRemoteSettings;}

inline QString Ied::stationName() const
{ return m_stationName;}

inline void Ied::setStationName(const QString &stationName)
{ m_stationName = stationName;}

inline QString Ied::voltClass() const
{ return m_voltClass;}

inline void Ied::setVoltClass(const QString &voltClass)
{ m_voltClass = voltClass;}

inline QString Ied::voltage() const
{ return m_voltage;}

inline void Ied::setVoltage(const QString &voltage)
{ m_voltage = voltage;}

inline QString Ied::bayName() const
{ return m_bayName;}

inline void Ied::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString Ied::criterionTrip() const
{ return m_criterionTrip;}

inline void Ied::setCriterionTrip(const QString &criterionTrip)
{ m_criterionTrip = criterionTrip;}

inline QString Ied::criterionLock() const
{ return m_criterionLock;}

inline void Ied::setCriterionLock(const QString &criterionLock)
{ m_criterionLock = criterionLock;}

inline QString Ied::criterionMaintain() const
{ return m_criterionMaintain;}

inline void Ied::setCriterionMaintain(const QString &criterionMaintain)
{ m_criterionMaintain = criterionMaintain;}

inline QString Ied::criterionAlarm() const
{ return m_criterionAlarm;}

inline void Ied::setCriterionAlarm(const QString &criterionAlarm)
{ m_criterionAlarm = criterionAlarm;}

inline QString Ied::criterionRun() const
{ return m_criterionRun;}

inline void Ied::setCriterionRun(const QString &criterionRun)
{ m_criterionRun = criterionRun;}

inline QString Ied::ipA() const
{ return m_ipA;}

inline void Ied::setIpA(const QString &ipA)
{ m_ipA = ipA;}

inline QString Ied::ipB() const
{ return m_ipB;}

inline void Ied::setIpB(const QString &ipB)
{ m_ipB = ipB;}

inline QString Ied::ipC() const
{ return m_ipC;}

inline void Ied::setIpC(const QString &ipC)
{ m_ipC = ipC;}

inline QString Ied::netType() const
{ return m_netType;}

inline void Ied::setNetType(const QString &netType)
{ m_netType = netType;}

inline QString Ied::belongAllBays() const
{ return m_belongAllBays;}

inline void Ied::setBelongAllBays(const QString &belongAllBays)
{ m_belongAllBays = belongAllBays;}

inline QString Ied::deliveryDate() const
{ return m_deliveryDate;}

inline void Ied::setDeliveryDate(const QString &deliveryDate)
{ m_deliveryDate = deliveryDate;}

inline QString Ied::iedNameComp() const
{ return m_iedNameComp;}

inline void Ied::setIedNameComp(const QString &iedNameComp)
{ m_iedNameComp = iedNameComp;}

inline bool Ied::isConnected() const
{ return m_isConnected;}

inline void Ied::setIsConnected(bool isConnected)
{ m_isConnected = isConnected;}

inline int Ied::iedState() const
{ return m_iedState;}

inline void Ied::setIedState(int iedState)
{ m_iedState = iedState;}

inline int Ied::shouldIedState() const
{ return m_shouldIedState;}

inline void Ied::setShouldIedState(int shouldIedState)
{ m_shouldIedState = shouldIedState;}

inline int Ied::hadGi() const
{ return m_hadGi;}

inline void Ied::setHadGi(int hadGi)
{ m_hadGi = hadGi;}

inline const QList<Strap*> & Ied::lstStrap() const
{ return m_lstStrap;}

inline void Ied::setLstStrap(QList<Strap *> &lstStrap)
{ m_lstStrap = lstStrap;}

//inline const QStringList &Ied::lstDataRef() const
//{ return m_lstDataRef;}

//inline void Ied::clearDataRef()
//{ m_lstDataRef.clear();}

//inline const QStringList &Ied::lstDevName() const
//{ return m_lstDevName;}

//inline void Ied::clearDevName()
//{ m_lstDevName.clear();}

//inline const QStringList &Ied::lstDevScheduleName() const
//{ return m_lstDevScheduleName;}

//inline void Ied::clearDevSchedule()
//{ m_lstDevScheduleName.clear();}
#endif // IED_H
