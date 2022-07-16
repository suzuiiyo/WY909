#ifndef LOOPPORTALARMRECORD_H
#define LOOPPORTALARMRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class LoopPortAlarmRecord
{
public:
    typedef QSharedPointer<LoopPortAlarmRecord> Ptr;
    typedef QList<Ptr> List;
public:
    LoopPortAlarmRecord();
    ~LoopPortAlarmRecord();
public:
    int GUID() const;
    QString iedName() const;
    QString port() const;
    QString lineRef() const;
    QString pdRef() const;
    QString gjValue() const;
    QString gjTime() const;
    QString hlType() const;
    QString phyLink() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setPort(const QString &port);
    void setLineRef(const QString &lineRef);
    void setPDRef(const QString &pdRef);
    void setGJValue(const QString &gjValue);
    void setGJTime(const QString &gjTime);
    void setHLType(const QString &hlType);
    void setPhyLink(const QString &phyLink);
    void setAckTip(int ackTip);
private:
    int m_GUID;
    QString m_iedName;
    QString m_port;
    QString m_lineRef;
    QString m_pdRef;
    QString m_gjValue;
    QString m_gjTime;
    QString m_hlType;
    QString m_phyLink;
    int     m_ackTip;
private:
    friend class DBLoopPortAlarmRecordDAO;
};

inline int LoopPortAlarmRecord::GUID() const
{ return m_GUID;}

inline void LoopPortAlarmRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString LoopPortAlarmRecord::iedName() const
{ return m_iedName;}

inline void LoopPortAlarmRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString LoopPortAlarmRecord::port() const
{ return m_port;}

inline void LoopPortAlarmRecord::setPort(const QString &port)
{ m_port = port;}

inline QString LoopPortAlarmRecord::lineRef() const
{ return m_lineRef;}

inline void LoopPortAlarmRecord::setLineRef(const QString &lineRef)
{ m_lineRef = lineRef;}

inline QString LoopPortAlarmRecord::pdRef() const
{ return m_pdRef;}

inline void LoopPortAlarmRecord::setPDRef(const QString &pdRef)
{ m_pdRef = pdRef;}

inline QString LoopPortAlarmRecord::gjValue() const
{ return m_gjValue;}

inline void LoopPortAlarmRecord::setGJValue(const QString &gjValue)
{ m_gjValue = gjValue;}

inline QString LoopPortAlarmRecord::gjTime() const
{ return m_gjTime;}

inline void LoopPortAlarmRecord::setGJTime(const QString &gjTime)
{ m_gjTime = gjTime;}

inline QString LoopPortAlarmRecord::hlType() const
{ return m_hlType;}

inline void LoopPortAlarmRecord::setHLType(const QString &hlType)
{ m_hlType = hlType;}

inline QString LoopPortAlarmRecord::phyLink() const
{ return m_phyLink;}

inline void LoopPortAlarmRecord::setPhyLink(const QString &phyLink)
{ m_phyLink = phyLink;}

inline int LoopPortAlarmRecord::ackTip() const
{ return m_ackTip;}

inline void LoopPortAlarmRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // LOOPPORTALARMRECORD_H
