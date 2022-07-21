#ifndef TRANSIENTTASKTMCONFIG_H
#define TRANSIENTTASKTMCONFIG_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class TransientTaskTMConfig
{
public:
    typedef QSharedPointer<TransientTaskTMConfig> Ptr;
    typedef QList<Ptr> List;
public:
    TransientTaskTMConfig();
    ~TransientTaskTMConfig();
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
private:
    friend class DBTransientTaskTMConfigDAO;
};

inline int TransientTaskTMConfig::GUID() const
{ return m_GUID;}

inline void TransientTaskTMConfig::setGUID(int guid)
{ m_GUID = guid;}

inline QString TransientTaskTMConfig::bayName() const
{ return m_bayName;}

inline void TransientTaskTMConfig::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString TransientTaskTMConfig::itemName() const
{ return m_itemName;}

inline void TransientTaskTMConfig::setItemName(const QString &itemName)
{ m_itemName = itemName;}

inline QString TransientTaskTMConfig::itemType() const
{ return m_itemType;}

inline void TransientTaskTMConfig::setItemType(const QString &itemType)
{ m_itemType = itemType;}

inline QString TransientTaskTMConfig::itemDesc() const
{ return m_itemDesc;}

inline void TransientTaskTMConfig::setItemDesc(const QString &itemDesc)
{ m_itemDesc = itemDesc;}

inline QString TransientTaskTMConfig::relationItem() const
{ return m_relationItem;}

inline void TransientTaskTMConfig::setRelationItem(const QString &relationItem)
{ m_relationItem = relationItem;}

inline QString TransientTaskTMConfig::phase() const
{ return m_phase;}

inline void TransientTaskTMConfig::setPhase(const QString &phase)
{ m_phase = phase;}

inline QString TransientTaskTMConfig::setType() const
{ return m_setType;}

inline void TransientTaskTMConfig::setSetType(const QString &setType)
{ m_setType = setType;}

inline QString TransientTaskTMConfig::iedName1() const
{ return m_iedName1;}

inline void TransientTaskTMConfig::setIedName1(const QString &iedName1)
{ m_iedName1 = iedName1;}

inline QString TransientTaskTMConfig::dataRef1() const
{ return m_dataRef1;}

inline void TransientTaskTMConfig::setDataRef1(const QString &dataRef1)
{ m_dataRef1 = dataRef1;}

inline QString TransientTaskTMConfig::dataDesc1() const
{ return m_dataDesc1;}

inline void TransientTaskTMConfig::setDataDesc1(const QString &dataDesc1)
{ m_dataDesc1 = dataDesc1;}

inline QString TransientTaskTMConfig::iedName2() const
{ return m_iedName2;}

inline void TransientTaskTMConfig::setIedName2(const QString &iedName2)
{ m_iedName2 = iedName2;}

inline QString TransientTaskTMConfig::dataRef2() const
{ return m_dataRef2;}

inline void TransientTaskTMConfig::setDataRef2(const QString &dataRef2)
{ m_dataRef2 = dataRef2;}

inline QString TransientTaskTMConfig::dataDesc2() const
{ return m_dataDesc2;}

inline void TransientTaskTMConfig::setDataDesc2(const QString &dataDesc2)
{ m_dataDesc2 = dataDesc2;}

inline QString TransientTaskTMConfig::lineName() const
{ return m_lineName;}

inline void TransientTaskTMConfig::setLineName(const QString &lineName)
{ m_lineName = lineName;}

inline QString TransientTaskTMConfig::unitName() const
{ return m_unitName;}

inline void TransientTaskTMConfig::setUnitName(const QString &unitName)
{ m_unitName = unitName;}

inline QString TransientTaskTMConfig::projectName() const
{ return m_projectName;}

inline void TransientTaskTMConfig::setProjectName(const QString &projectName)
{ m_projectName = projectName;}

inline QString TransientTaskTMConfig::businessType() const
{ return m_businessType;}

inline void TransientTaskTMConfig::setBusinessType(const QString &businessType)
{ m_businessType = businessType;}

inline QString TransientTaskTMConfig::standardValueType() const
{ return m_standardValueType;}

inline void TransientTaskTMConfig::setStandardValueType(const QString &standardValueType)
{ m_standardValueType = standardValueType;}

inline QString TransientTaskTMConfig::standardValue() const
{ return m_standardValue;}

inline void TransientTaskTMConfig::setStandardValue(const QString &standardValue)
{ m_standardValue = standardValue;}

inline QString TransientTaskTMConfig::itemConfigType() const
{ return m_itemConfigType;}

inline void TransientTaskTMConfig::setItemConfigType(const QString &itemConfigType)
{ m_itemConfigType = itemConfigType;}
#endif // TRANSIENTTASKCONFIG_H
