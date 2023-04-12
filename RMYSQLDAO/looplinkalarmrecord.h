#ifndef LOOPLINKALARMRECORD_H
#define LOOPLINKALARMRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class LoopLinkAlarmRecord
{
public:
    typedef QSharedPointer<LoopLinkAlarmRecord> Ptr;
    typedef QList<Ptr> List;
public:
    LoopLinkAlarmRecord();
    ~LoopLinkAlarmRecord();
public:
    int GUID() const;
    QString lineRef() const;
    QString result() const;
    QString p1GUID() const;
    QString p2GUID() const;
    QString cfRef() const;
    QString pdTime() const;
    QString xResult() const;
    QString yjAppID() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setLineRef(const QString &lineRef);
    void setResult(const QString &result);
    void setP1GUID(const QString &p1GUID);
    void setP2GUID(const QString &p2GUID);
    void setCFRef(const QString &cfRef);
    void setPDTime(const QString &pdTime);
    void setXResult(const QString &xResult);
    void setYJAppID(const QString &yjAppID);
    void setAckTip(int ackTip);
private:
    int m_GUID;
    QString m_lineRef;
    QString m_result;
    QString m_p1GUID;
    QString m_p2GUID;
    QString m_cfRef;
    QString m_pdTime;
    QString m_xResult;
    QString m_yjAppID;
    int     m_ackTip;
private:
    friend class DBLoopLinkAlarmRecordDAO;
};

inline int LoopLinkAlarmRecord::GUID() const
{ return m_GUID;}

inline void LoopLinkAlarmRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString LoopLinkAlarmRecord::lineRef() const
{ return m_lineRef;}

inline void LoopLinkAlarmRecord::setLineRef(const QString &lineRef)
{ m_lineRef = lineRef;}

inline QString LoopLinkAlarmRecord::result() const
{ return m_result;}

inline void LoopLinkAlarmRecord::setResult(const QString &result)
{ m_result = result;}

inline QString LoopLinkAlarmRecord::p1GUID() const
{ return m_p1GUID;}

inline void LoopLinkAlarmRecord::setP1GUID(const QString &p1GUID)
{ m_p1GUID = p1GUID;}

inline QString LoopLinkAlarmRecord::p2GUID() const
{ return m_p2GUID;}

inline void LoopLinkAlarmRecord::setP2GUID(const QString &p2GUID)
{ m_p2GUID = p2GUID;}

inline QString LoopLinkAlarmRecord::cfRef() const
{ return m_cfRef;}

inline void LoopLinkAlarmRecord::setCFRef(const QString &cfRef)
{ m_cfRef = cfRef;}

inline QString LoopLinkAlarmRecord::pdTime() const
{ return m_pdTime;}

inline void LoopLinkAlarmRecord::setPDTime(const QString &pdTime)
{ m_pdTime = pdTime;}

inline QString LoopLinkAlarmRecord::xResult() const
{ return m_xResult;}

inline void LoopLinkAlarmRecord::setXResult(const QString &xResult)
{ m_xResult = xResult;}

inline QString LoopLinkAlarmRecord::yjAppID() const
{ return m_yjAppID;}

inline void LoopLinkAlarmRecord::setYJAppID(const QString &yjAppID)
{ m_yjAppID = yjAppID;}

inline int LoopLinkAlarmRecord::ackTip() const
{ return m_ackTip;}

inline void LoopLinkAlarmRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // LOOPLINKALARMRECORD_H
