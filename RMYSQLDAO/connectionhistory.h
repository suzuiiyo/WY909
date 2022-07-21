#ifndef CONECTIONHISTORY_H
#define CONECTIONHISTORY_H
#include <QList>
#include <QHash>
#include <QString>
#include <QSharedPointer>
class ConnectionHistory
{
public:
    typedef QSharedPointer<ConnectionHistory> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    ConnectionHistory();
    ~ConnectionHistory();
public:
    int     GUID() const;
    bool    dataValue() const;
    QString iedName() const;
    QString recordTime() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setDataValue(bool dataValue);
    void setIedName(const QString &iedName);
    void setRecordTime(const QString &recordTime);
    void setAckTip(int ackTip);
private:
    int     m_GUID;
    bool    m_dataValue;
    QString m_iedName;
    QString m_recordTime;
    int     m_ackTip;
private:
    friend class DBConnectionHistoryDAO;
};

inline int ConnectionHistory::GUID() const
{ return m_GUID;}

inline void ConnectionHistory::setGUID(int guid)
{ m_GUID = guid;}

inline bool ConnectionHistory::dataValue() const
{ return m_dataValue;}

inline void ConnectionHistory::setDataValue(bool dataValue)
{ m_dataValue = dataValue;}

inline QString ConnectionHistory::iedName() const
{ return m_iedName;}

inline void ConnectionHistory::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString ConnectionHistory::recordTime() const
{ return m_recordTime;}

inline void ConnectionHistory::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}

inline int ConnectionHistory::ackTip() const
{ return m_ackTip;}

inline void ConnectionHistory::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // CONECTIONHISTORY_H
