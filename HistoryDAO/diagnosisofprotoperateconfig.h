#ifndef DIAGNOSISOFPROTOPERATECONFIG_H
#define DIAGNOSISOFPROTOPERATECONFIG_H
#include <QSharedPointer>
#include <QString>
#include <QList>
class DiagnosisOfProtOperateConfig
{
public:
    typedef QSharedPointer<DiagnosisOfProtOperateConfig> Ptr;
    typedef QList<Ptr> List;
public:
    DiagnosisOfProtOperateConfig();
    ~DiagnosisOfProtOperateConfig();
public:
    int         GUID() const;
    QString     iedName() const;
    QString     opType() const;
    QString     dataRef() const;
    QString     refIedName() const;
    QString     refSource() const;
    QString     startTaskRef() const;
    int         groupOrder() const;
    int         itemOrder() const;
    QString     appId() const;
    QString     dataDesc() const;
    QString     setType() const;
    QString     iedNameComp() const;
    QString     eValue() const;
    QString     standardValue() const;
public:
    void        setGUID(int guid);
    void        setIedName(const QString &iedName);
    void        setOpType(const QString &opType);
    void        setDataRef(const QString &dataRef);
    void        setRefIedName(const QString &refIedName);
    void        setRefSource(const QString &refSource);
    void        setStartTaskRef(const QString &startTaskRef);
    void        setGroupOrder(int groupOrder);
    void        setItemOrder(int itemOrder);
    void        setAppId(const QString &appId);
    void        setDataDesc(const QString &dataDesc);
    void        setSetType(const QString &setType);
    void        setIedNameComp(const QString &iedNameComp);
    void        setEValue(const QString &eValue);
    void        setStandardValue(const QString &standardValue);
private:
    int         m_GUID;
    QString     m_iedName;
    QString     m_opType;
    QString     m_dataRef;
    QString     m_refIedName;
    QString     m_refSource;
    QString     m_startTaskRef;
    int         m_groupOrder;
    int         m_itemOrder;
    QString     m_appId;
    QString     m_dataDesc;
    QString     m_setType;
    QString     m_iedNameComp;
    QString     m_eValue;
    QString     m_standardValue;
private:
    friend class DBDiagnosisOfProtOperateConfigDAO;
};

inline int DiagnosisOfProtOperateConfig::GUID() const
{ return m_GUID;}

inline void DiagnosisOfProtOperateConfig::setGUID(int guid)
{ m_GUID = guid;}

inline QString DiagnosisOfProtOperateConfig::iedName() const
{ return m_iedName;}

inline void DiagnosisOfProtOperateConfig::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString DiagnosisOfProtOperateConfig::opType() const
{ return m_opType;}

inline void DiagnosisOfProtOperateConfig::setOpType(const QString &opType)
{ m_opType = opType;}

inline QString DiagnosisOfProtOperateConfig::dataRef() const
{ return m_dataRef;}

inline void DiagnosisOfProtOperateConfig::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString DiagnosisOfProtOperateConfig::refIedName() const
{ return m_refIedName;}

inline void DiagnosisOfProtOperateConfig::setRefIedName(const QString &refIedName)
{ m_refIedName = refIedName;}

inline QString DiagnosisOfProtOperateConfig::refSource() const
{ return m_refSource;}

inline void DiagnosisOfProtOperateConfig::setRefSource(const QString &refSource)
{ m_refSource = refSource;}

inline QString DiagnosisOfProtOperateConfig::startTaskRef() const
{ return m_startTaskRef;}

inline void DiagnosisOfProtOperateConfig::setStartTaskRef(const QString &startTaskRef)
{ m_startTaskRef = startTaskRef;}

inline int DiagnosisOfProtOperateConfig::groupOrder() const
{ return m_groupOrder;}

inline void DiagnosisOfProtOperateConfig::setGroupOrder(int groupOrder)
{ m_groupOrder = groupOrder;}

inline int DiagnosisOfProtOperateConfig::itemOrder() const
{ return m_itemOrder;}

inline void DiagnosisOfProtOperateConfig::setItemOrder(int itemOrder)
{ m_itemOrder = itemOrder;}

inline QString DiagnosisOfProtOperateConfig::appId() const
{ return m_appId;}

inline void DiagnosisOfProtOperateConfig::setAppId(const QString &appId)
{ m_appId = appId;}

inline QString DiagnosisOfProtOperateConfig::dataDesc() const
{ return m_dataDesc;}

inline void DiagnosisOfProtOperateConfig::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString DiagnosisOfProtOperateConfig::setType() const
{ return m_setType;}

inline void DiagnosisOfProtOperateConfig::setSetType(const QString &setType)
{ m_setType = setType;}

inline QString DiagnosisOfProtOperateConfig::iedNameComp() const
{ return m_iedNameComp;}

inline void DiagnosisOfProtOperateConfig::setIedNameComp(const QString &iedNameComp)
{ m_iedNameComp = iedNameComp;}

inline QString DiagnosisOfProtOperateConfig::eValue() const
{ return m_eValue;}

inline void DiagnosisOfProtOperateConfig::setEValue(const QString &eValue)
{ m_eValue = eValue;}

inline QString DiagnosisOfProtOperateConfig::standardValue() const
{ return m_standardValue;}

inline void DiagnosisOfProtOperateConfig::setStandardValue(const QString &standardValue)
{ m_standardValue = standardValue;}
#endif // DIAGNOSISOFPROTOPERATECONFIG_H
