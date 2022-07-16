#ifndef CONNECTIONSTATE_H
#define CONNECTIONSTATE_H
#include <QList>
#include <QHash>
#include <QString>
#include <QSharedPointer>
class ConnectionState
{
public:
    typedef QSharedPointer<ConnectionState> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    ConnectionState();
    ~ConnectionState();
public:
    bool dataValue() const;
    QString iedName() const;
    QString lastUpdateTime() const;
public:
    void setDataValue(bool dataValue);
    void setIedName(const QString &iedName);
    void setLastUpdateTime(const QString &recordTime);
private:
    bool m_dataValue;
    QString m_iedName;
    QString m_lastUpdateTime;
private:
    friend class DBConnectionStateDAO;
};

inline bool ConnectionState::dataValue() const
{ return m_dataValue;}

inline void ConnectionState::setDataValue(bool dataValue)
{ m_dataValue = dataValue;}

inline QString ConnectionState::iedName() const
{ return m_iedName;}

inline void ConnectionState::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString ConnectionState::lastUpdateTime() const
{ return m_lastUpdateTime;}

inline void ConnectionState::setLastUpdateTime(const QString &lastUpdateTime)
{ m_lastUpdateTime = lastUpdateTime;}
#endif // CONNECTIONSTATE_H
