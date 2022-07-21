#ifndef DEVNONCORRESPONDINGRECORD_H
#define DEVNONCORRESPONDINGRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class DevNonCorrespondingRecord
{
public:
    typedef QSharedPointer<DevNonCorrespondingRecord> Ptr;
    typedef QList<Ptr> List;
public:
    DevNonCorrespondingRecord();
    ~DevNonCorrespondingRecord();
public:
    int GUID() const;
    QString bayName() const;
    QString bayType() const;
    QString setType() const;
    int state() const;
    QString iedName() const;
    QString iedDesc() const;
    QString updateTime() const;
    QString remarks() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setBayName(const QString &bayName);
    void setBayType(const QString &bayType);
    void setSetType(const QString &setType);
    void setState(int state);
    void setIedName(const QString &iedName);
    void setIedDesc(const QString &iedDesc);
    void setUpdateTime(const QString &updateTime);
    void setRemarks(const QString &remarks);
    void setAckTip(int ackTip);
private:
    int m_GUID;
    QString m_bayName;
    QString m_bayType;
    QString m_setType;
    int m_state;
    QString m_iedName;
    QString m_iedDesc;
    QString m_updateTime;
    QString m_remarks;
    int     m_ackTip;
private:
    friend class DBDevNonCorrespondingRecordDAO;
};

inline int DevNonCorrespondingRecord::GUID() const
{ return m_GUID;}

inline void DevNonCorrespondingRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString DevNonCorrespondingRecord::bayName() const
{ return m_bayName;}

inline void DevNonCorrespondingRecord::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString DevNonCorrespondingRecord::bayType() const
{ return m_bayType;}

inline void DevNonCorrespondingRecord::setBayType(const QString &bayType)
{ m_bayType = bayType;}

inline QString DevNonCorrespondingRecord::setType() const
{ return m_setType;}

inline void DevNonCorrespondingRecord::setSetType(const QString &setType)
{ m_setType = setType;}

inline int DevNonCorrespondingRecord::state() const
{ return m_state;}

inline void DevNonCorrespondingRecord::setState(int state)
{ m_state = state;}

inline QString DevNonCorrespondingRecord::iedName() const
{ return m_iedName;}

inline void DevNonCorrespondingRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString DevNonCorrespondingRecord::iedDesc() const
{ return m_iedDesc;}

inline void DevNonCorrespondingRecord::setIedDesc(const QString &iedDesc)
{ m_iedDesc = iedDesc;}

inline QString DevNonCorrespondingRecord::updateTime() const
{ return m_updateTime;}

inline void DevNonCorrespondingRecord::setUpdateTime(const QString &updateTime)
{ m_updateTime = updateTime;}

inline QString DevNonCorrespondingRecord::remarks() const
{ return m_remarks;}

inline void DevNonCorrespondingRecord::setRemarks(const QString &remarks)
{ m_remarks = remarks;}

inline int DevNonCorrespondingRecord::ackTip() const
{ return m_ackTip;}

inline void DevNonCorrespondingRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // DEVNONCORRESPONDINGRECORD_H
