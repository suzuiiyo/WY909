#ifndef TRANSIENTTASKTSCONFIG_H
#define TRANSIENTTASKTSCONFIG_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class TransientTaskTSConfig
{
public:
    typedef QSharedPointer<TransientTaskTSConfig> Ptr;
    typedef QList<Ptr> List;
public:
   TransientTaskTSConfig();
    ~TransientTaskTSConfig();
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
    friend class DBTransientTaskTSConfigDAO;
};

inline int TransientTaskTSConfig::GUID() const
{ return m_GUID;}

inline void TransientTaskTSConfig::setGUID(int guid)
{ m_GUID = guid;}

inline QString TransientTaskTSConfig::bayName() const
{ return m_bayName;}

inline void TransientTaskTSConfig::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString TransientTaskTSConfig::itemName() const
{ return m_itemName;}

inline void TransientTaskTSConfig::setItemName(const QString &itemName)
{ m_itemName = itemName;}

inline QString TransientTaskTSConfig::itemType() const
{ return m_itemType;}

inline void TransientTaskTSConfig::setItemType(const QString &itemType)
{ m_itemType = itemType;}

inline QString TransientTaskTSConfig::itemDesc() const
{ return m_itemDesc;}

inline void TransientTaskTSConfig::setItemDesc(const QString &itemDesc)
{ m_itemDesc = itemDesc;}

inline QString TransientTaskTSConfig::relationItem() const
{ return m_relationItem;}

inline void TransientTaskTSConfig::setRelationItem(const QString &relationItem)
{ m_relationItem = relationItem;}

inline QString TransientTaskTSConfig::phase() const
{ return m_phase;}

inline void TransientTaskTSConfig::setPhase(const QString &phase)
{ m_phase = phase;}

inline QString TransientTaskTSConfig::setType() const
{ return m_setType;}

inline void TransientTaskTSConfig::setSetType(const QString &setType)
{ m_setType = setType;}

inline QString TransientTaskTSConfig::iedName1() const
{ return m_iedName1;}

inline void TransientTaskTSConfig::setIedName1(const QString &iedName1)
{ m_iedName1 = iedName1;}

inline QString TransientTaskTSConfig::dataRef1() const
{ return m_dataRef1;}

inline void TransientTaskTSConfig::setDataRef1(const QString &dataRef1)
{ m_dataRef1 = dataRef1;}

inline QString TransientTaskTSConfig::dataDesc1() const
{ return m_dataDesc1;}

inline void TransientTaskTSConfig::setDataDesc1(const QString &dataDesc1)
{ m_dataDesc1 = dataDesc1;}

inline QString TransientTaskTSConfig::iedName2() const
{ return m_iedName2;}

inline void TransientTaskTSConfig::setIedName2(const QString &iedName2)
{ m_iedName2 = iedName2;}

inline QString TransientTaskTSConfig::dataRef2() const
{ return m_dataRef2;}

inline void TransientTaskTSConfig::setDataRef2(const QString &dataRef2)
{ m_dataRef2 = dataRef2;}

inline QString TransientTaskTSConfig::dataDesc2() const
{ return m_dataDesc2;}

inline void TransientTaskTSConfig::setDataDesc2(const QString &dataDesc2)
{ m_dataDesc2 = dataDesc2;}

inline QString TransientTaskTSConfig::lineName() const
{ return m_lineName;}

inline void TransientTaskTSConfig::setLineName(const QString &lineName)
{ m_lineName = lineName;}

inline QString TransientTaskTSConfig::unitName() const
{ return m_unitName;}

inline void TransientTaskTSConfig::setUnitName(const QString &unitName)
{ m_unitName = unitName;}

inline QString TransientTaskTSConfig::projectName() const
{ return m_projectName;}

inline void TransientTaskTSConfig::setProjectName(const QString &projectName)
{ m_projectName = projectName;}

inline QString TransientTaskTSConfig::businessType() const
{ return m_businessType;}

inline void TransientTaskTSConfig::setBusinessType(const QString &businessType)
{ m_businessType = businessType;}

inline QString TransientTaskTSConfig::standardValueType() const
{ return m_standardValueType;}

inline void TransientTaskTSConfig::setStandardValueType(const QString &standardValueType)
{ m_standardValueType = standardValueType;}

inline QString TransientTaskTSConfig::standardValue() const
{ return m_standardValue;}

inline void TransientTaskTSConfig::setStandardValue(const QString &standardValue)
{ m_standardValue = standardValue;}

inline QString TransientTaskTSConfig::itemConfigType() const
{ return m_itemConfigType;}

inline void TransientTaskTSConfig::setItemConfigType(const QString &itemConfigType)
{ m_itemConfigType = itemConfigType;}
#endif // TRANSIENTTASKTSCONFIG_H
