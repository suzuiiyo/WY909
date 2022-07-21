#ifndef DBCONFIG_H
#define DBCONFIG_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class DBConfig
{
public:
    typedef QSharedPointer<DBConfig> Ptr;
    typedef QList<Ptr> List;
public:
    DBConfig();
    ~DBConfig();
public:
    QString hostName() const;
    int port() const;
    QString userName() const;
    QString password() const;
    QString sqlitePath() const;
public:
    void setHostName(const QString &hostName);
    void setPort(int port);
    void setUserName(const QString &userName);
    void setPassword(const QString &password);
    void setSqlitePath(const QString &sqlitePath);
private:
    QString m_hostName;
    int m_port;
    QString m_userName;
    QString m_password;
    QString m_sqlitePath;
};

inline QString DBConfig::hostName() const
{ return m_hostName;}

inline void DBConfig::setHostName(const QString &hostName)
{ m_hostName = hostName;}

inline int DBConfig::port() const
{ return m_port;}

inline void DBConfig::setPort(int port)
{ m_port = port;}

inline QString DBConfig::userName() const
{ return m_userName;}

inline void DBConfig::setUserName(const QString &userName)
{ m_userName = userName;}

inline QString DBConfig::password() const
{ return m_password;}

inline void DBConfig::setPassword(const QString &password)
{ m_password = password;}

inline QString DBConfig::sqlitePath() const
{ return m_sqlitePath;}

inline void DBConfig::setSqlitePath(const QString &sqlitePath)
{ m_sqlitePath = sqlitePath;}
#endif // DBCONFIG_H
