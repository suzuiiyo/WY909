#ifndef STEADYTASKTSCONFIG_H
#define STEADYTASKTSCONFIG_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class SteadyTaskTSConfig
{
public:
    typedef QSharedPointer<SteadyTaskTSConfig> Ptr;
    typedef QList<Ptr> List;
public:
    SteadyTaskTSConfig();
    ~SteadyTaskTSConfig();
public:
    int GUID() const;
    QString bayName() const;
    QString itemName() const;
    QString itemType() const;
    QString itemDesc() const;
    QString relationItem() const;
    QString phase() const;
    QString setType() const;
    QString iedName1() const;
    QString dataRef1() const;
    QString dataDesc1() const;
    QString iedName2() const;
    QString dataRef2() const;
    QString dataDesc2() const;
    QString lineName() const;
    QString unitName() const;
    QString projectName() const;
    QString businessType() const;
    QString standardValueType() const;
    QString standardValue() const;
    QString itemConfigType() const;
    QString unicodeDesc() const;
public:
    void setGUID(int guid);
    void setBayName(const QString &bayName);
    void setItemName(const QString &itemName);
    void setItemType(const QString &itemType);
    void setItemDesc(const QString &itemDesc);
    void setRelationItem(const QString &relationItem);
    void setPhase(const QString &phase);
    void setSetType(const QString &setType);
    void setIedName1(const QString &iedName1);
    void setDataRef1(const QString &dataRef1);
    void setDataDesc1(const QString &dataDesc1);
    void setIedName2(const QString &iedName2);
    void setDataRef2(const QString &dataRef2);
    void setDataDesc2(const QString &dataDesc2);
    void setLineName(const QString &lineName);
    void setUnitName(const QString &unitName);
    void setProjectName(const QString &projectName);
    void setBusinessType(const QString &businessType);
    void setStandardValueType(const QString &standardValueType);
    void setStandardValue(const QString &standardValue);
    void setItemConfigType(const QString &itemConfigType);
    void setUnicodeDesc(const QString &unicodeDesc);
private:
    int m_GUID;
    QString m_bayName;
    QString m_itemName;
    QString m_itemType;
    QString m_itemDesc;
    QString m_relationItem;
    QString m_phase;
    QString m_setType;
    QString m_iedName1;
    QString m_dataRef1;
    QString m_dataDesc1;
    QString m_iedName2;
    QString m_dataRef2;
    QString m_dataDesc2;
    QString m_lineName;
    QString m_unitName;
    QString m_projectName;
    QString m_businessType;
    QString m_standardValueType;
    QString m_standardValue;
    QString m_itemConfigType;
    QString m_unicodeDesc;
private:
    friend class DBSteadyTaskTSConfigDAO;
};

inline int SteadyTaskTSConfig::GUID() const
{ return m_GUID;}

inline void SteadyTaskTSConfig::setGUID(int guid)
{ m_GUID = guid;}

inline QString SteadyTaskTSConfig::bayName() const
{ return m_bayName;}

inline void SteadyTaskTSConfig::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString SteadyTaskTSConfig::itemName() const
{ return m_itemName;}

inline void SteadyTaskTSConfig::setItemName(const QString &itemName)
{ m_itemName = itemName;}

inline QString SteadyTaskTSConfig::itemType() const
{ return m_itemType;}

inline void SteadyTaskTSConfig::setItemType(const QString &itemType)
{ m_itemType = itemType;}

inline QString SteadyTaskTSConfig::itemDesc() const
{ return m_itemDesc;}

inline void SteadyTaskTSConfig::setItemDesc(const QString &itemDesc)
{ m_itemDesc = itemDesc;}

inline QString SteadyTaskTSConfig::relationItem() const
{ return m_relationItem;}

inline void SteadyTaskTSConfig::setRelationItem(const QString &relationItem)
{ m_relationItem = relationItem;}

inline QString SteadyTaskTSConfig::phase() const
{ return m_phase;}

inline void SteadyTaskTSConfig::setPhase(const QString &phase)
{ m_phase = phase;}

inline QString SteadyTaskTSConfig::setType() const
{ return m_setType;}

inline void SteadyTaskTSConfig::setSetType(const QString &setType)
{ m_setType = setType;}

inline QString SteadyTaskTSConfig::iedName1() const
{ return m_iedName1;}

inline void SteadyTaskTSConfig::setIedName1(const QString &iedName1)
{ m_iedName1 = iedName1;}

inline QString SteadyTaskTSConfig::dataRef1() const
{ return m_dataRef1;}

inline void SteadyTaskTSConfig::setDataRef1(const QString &dataRef1)
{ m_dataRef1 = dataRef1;}

inline QString SteadyTaskTSConfig::dataDesc1() const
{ return m_dataDesc1;}

inline void SteadyTaskTSConfig::setDataDesc1(const QString &dataDesc1)
{ m_dataDesc1 = dataDesc1;}

inline QString SteadyTaskTSConfig::iedName2() const
{ return m_iedName2;}

inline void SteadyTaskTSConfig::setIedName2(const QString &iedName2)
{ m_iedName2 = iedName2;}

inline QString SteadyTaskTSConfig::dataRef2() const
{ return m_dataRef2;}

inline void SteadyTaskTSConfig::setDataRef2(const QString &dataRef2)
{ m_dataRef2 = dataRef2;}

inline QString SteadyTaskTSConfig::dataDesc2() const
{ return m_dataDesc2;}

inline void SteadyTaskTSConfig::setDataDesc2(const QString &dataDesc2)
{ m_dataDesc2 = dataDesc2;}

inline QString SteadyTaskTSConfig::lineName() const
{ return m_lineName;}

inline void SteadyTaskTSConfig::setLineName(const QString &lineName)
{ m_lineName = lineName;}

inline QString SteadyTaskTSConfig::unitName() const
{ return m_unitName;}

inline void SteadyTaskTSConfig::setUnitName(const QString &unitName)
{ m_unitName = unitName;}

inline QString SteadyTaskTSConfig::projectName() const
{ return m_projectName;}

inline void SteadyTaskTSConfig::setProjectName(const QString &projectName)
{ m_projectName = projectName;}

inline QString SteadyTaskTSConfig::businessType() const
{ return m_businessType;}

inline void SteadyTaskTSConfig::setBusinessType(const QString &businessType)
{ m_businessType = businessType;}

inline QString SteadyTaskTSConfig::standardValueType() const
{ return m_standardValueType;}

inline void SteadyTaskTSConfig::setStandardValueType(const QString &standardValueType)
{ m_standardValueType = standardValueType;}

inline QString SteadyTaskTSConfig::standardValue() const
{ return m_standardValue;}

inline void SteadyTaskTSConfig::setStandardValue(const QString &standardValue)
{ m_standardValue = standardValue;}

inline QString SteadyTaskTSConfig::itemConfigType() const
{ return m_itemConfigType;}

inline void SteadyTaskTSConfig::setItemConfigType(const QString &itemConfigType)
{ m_itemConfigType = itemConfigType;}

inline QString SteadyTaskTSConfig::unicodeDesc() const
{ return m_unicodeDesc;}

inline void SteadyTaskTSConfig::setUnicodeDesc(const QString &unicodeDesc)
{ m_unicodeDesc = unicodeDesc;}
#endif // STEADYTASKTSCONFIG_H
