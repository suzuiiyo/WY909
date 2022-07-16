#ifndef SQLITEDBCONFIG_H
#define SQLITEDBCONFIG_H
#include <QSharedPointer>
#include <QString>
#include <QList>
class SqliteDBConfig
{
public:
    typedef QSharedPointer<SqliteDBConfig> Ptr;
public:
    SqliteDBConfig();
    ~SqliteDBConfig();
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

inline QString SqliteDBConfig::hostName() const
{ return m_hostName;}

inline void SqliteDBConfig::setHostName(const QString &hostName)
{ m_hostName = hostName;}

inline int SqliteDBConfig::port() const
{ return m_port;}

inline void SqliteDBConfig::setPort(int port)
{ m_port = port;}

inline QString SqliteDBConfig::userName() const
{ return m_userName;}

inline void SqliteDBConfig::setUserName(const QString &userName)
{ m_userName = userName;}

inline QString SqliteDBConfig::password() const
{ return m_password;}

inline void SqliteDBConfig::setPassword(const QString &password)
{ m_password = password;}

inline QString SqliteDBConfig::sqlitePath() const
{ return m_sqlitePath;}

inline void SqliteDBConfig::setSqlitePath(const QString &sqlitePath)
{ m_sqlitePath = sqlitePath;}
#endif // SQLITEDBCONFIG_H
