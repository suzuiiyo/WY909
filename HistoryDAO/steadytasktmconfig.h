#ifndef STEADYTASKTMCONFIG_H
#define STEADYTASKTMCONFIG_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class SteadyTaskTMConfig
{
public:
    typedef QSharedPointer<SteadyTaskTMConfig> Ptr;
    typedef QList<Ptr> List;
public:
    SteadyTaskTMConfig();
    ~SteadyTaskTMConfig();
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
    friend class DBSteadyTaskTMConfigDAO;
};

inline int SteadyTaskTMConfig::GUID() const
{ return m_GUID;}

inline void SteadyTaskTMConfig::setGUID(int guid)
{ m_GUID = guid;}

inline QString SteadyTaskTMConfig::bayName() const
{ return m_bayName;}

inline void SteadyTaskTMConfig::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString SteadyTaskTMConfig::itemName() const
{ return m_itemName;}

inline void SteadyTaskTMConfig::setItemName(const QString &itemName)
{ m_itemName = itemName;}

inline QString SteadyTaskTMConfig::itemType() const
{ return m_itemType;}

inline void SteadyTaskTMConfig::setItemType(const QString &itemType)
{ m_itemType = itemType;}

inline QString SteadyTaskTMConfig::itemDesc() const
{ return m_itemDesc;}

inline void SteadyTaskTMConfig::setItemDesc(const QString &itemDesc)
{ m_itemDesc = itemDesc;}

inline QString SteadyTaskTMConfig::relationItem() const
{ return m_relationItem;}

inline void SteadyTaskTMConfig::setRelationItem(const QString &relationItem)
{ m_relationItem = relationItem;}

inline QString SteadyTaskTMConfig::phase() const
{ return m_phase;}

inline void SteadyTaskTMConfig::setPhase(const QString &phase)
{ m_phase = phase;}

inline QString SteadyTaskTMConfig::setType() const
{ return m_setType;}

inline void SteadyTaskTMConfig::setSetType(const QString &setType)
{ m_setType = setType;}

inline QString SteadyTaskTMConfig::iedName1() const
{ return m_iedName1;}

inline void SteadyTaskTMConfig::setIedName1(const QString &iedName1)
{ m_iedName1 = iedName1;}

inline QString SteadyTaskTMConfig::dataRef1() const
{ return m_dataRef1;}

inline void SteadyTaskTMConfig::setDataRef1(const QString &dataRef1)
{ m_dataRef1 = dataRef1;}

inline QString SteadyTaskTMConfig::dataDesc1() const
{ return m_dataDesc1;}

inline void SteadyTaskTMConfig::setDataDesc1(const QString &dataDesc1)
{ m_dataDesc1 = dataDesc1;}

inline QString SteadyTaskTMConfig::iedName2() const
{ return m_iedName2;}

inline void SteadyTaskTMConfig::setIedName2(const QString &iedName2)
{ m_iedName2 = iedName2;}

inline QString SteadyTaskTMConfig::dataRef2() const
{ return m_dataRef2;}

inline void SteadyTaskTMConfig::setDataRef2(const QString &dataRef2)
{ m_dataRef2 = dataRef2;}

inline QString SteadyTaskTMConfig::dataDesc2() const
{ return m_dataDesc2;}

inline void SteadyTaskTMConfig::setDataDesc2(const QString &dataDesc2)
{ m_dataDesc2 = dataDesc2;}

inline QString SteadyTaskTMConfig::lineName() const
{ return m_lineName;}

inline void SteadyTaskTMConfig::setLineName(const QString &lineName)
{ m_lineName = lineName;}

inline QString SteadyTaskTMConfig::unitName() const
{ return m_unitName;}

inline void SteadyTaskTMConfig::setUnitName(const QString &unitName)
{ m_unitName = unitName;}

inline QString SteadyTaskTMConfig::projectName() const
{ return m_projectName;}

inline void SteadyTaskTMConfig::setProjectName(const QString &projectName)
{ m_projectName = projectName;}

inline QString SteadyTaskTMConfig::businessType() const
{ return m_businessType;}

inline void SteadyTaskTMConfig::setBusinessType(const QString &businessType)
{ m_businessType = businessType;}

inline QString SteadyTaskTMConfig::standardValueType() const
{ return m_standardValueType;}

inline void SteadyTaskTMConfig::setStandardValueType(const QString &standardValueType)
{ m_standardValueType = standardValueType;}

inline QString SteadyTaskTMConfig::standardValue() const
{ return m_standardValue;}

inline void SteadyTaskTMConfig::setStandardValue(const QString &standardValue)
{ m_standardValue = standardValue;}

inline QString SteadyTaskTMConfig::itemConfigType() const
{ return m_itemConfigType;}

inline void SteadyTaskTMConfig::setItemConfigType(const QString &itemConfigType)
{ m_itemConfigType = itemConfigType;}

inline QString SteadyTaskTMConfig::unicodeDesc() const
{ return m_unicodeDesc;}

inline void SteadyTaskTMConfig::setUnicodeDesc(const QString &unicodeDesc)
{ m_unicodeDesc = unicodeDesc;}
#endif // STEADYTASKTMCONFIG_H
