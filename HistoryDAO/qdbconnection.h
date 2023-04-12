#ifndef QDBCONNECTION_H
#define QDBCONNECTION_H
#include <QString>
#include <QMutex>
#include <QHash>
class QSqlDatabase;
class QSqlError;
class QSqlQuery;
class QDBConnection
{
public:
    QDBConnection(const QString &type = "QMYSQL");
    ~QDBConnection();
public:
    bool         isOpen() const;
    bool         open();
    void         close();
public:
    QSqlQuery    exec(const QString& query = QString()) const;
    QSqlError    lastError() const;
    bool         isValid() const;

    bool         transaction();
    bool         commit();
    bool         rollback();

    void         setDatabaseName(const QString& name);
    void         setUserName(const QString& name);
    void         setPassword(const QString& password);
    void         setHostName(const QString& host);
    void         setPort(int p);
    void         setType(const QString &type);
    void         setConnectOptions(const QString& options = QString());
    QString      databaseName() const;
    QString      userName() const;
    QString      password() const;
    QString      hostName() const;
    QString      driverName() const;
    int          port() const;
    QString      type() const;
    QString      connectOptions() const;
    QString      connectionName() const;
public:
    operator     QSqlDatabase () const;
protected:
    QSqlDatabase connection() const;
    void         releaseConnection();
private:
    QString                               m_connectionName;
    QString                               m_type;
    QString                               m_databaseName;
    QString                               m_userName;
    QString                               m_password;
    QString                               m_hostName;
    QString                               m_connectOptions;
    int                                   m_port;
private:
    static QMutex                         m_mutex;
    static QHash<QString,int>             m_ref;
    Q_DISABLE_COPY(QDBConnection)
};

inline void QDBConnection::setDatabaseName(const QString &name)
{m_databaseName = name;}

inline void QDBConnection::setUserName(const QString &name)
{m_userName = name;}

inline void QDBConnection::setPassword(const QString &password)
{m_password = password;}

inline void QDBConnection::setHostName(const QString &host)
{m_hostName = host;}

inline void QDBConnection::setPort(int p)
{m_port = p;}

inline void QDBConnection::setType(const QString &type)
{ m_type = type;}

inline void QDBConnection::setConnectOptions(const QString &options)
{m_connectOptions = options;}

inline QString QDBConnection::databaseName() const
{return m_databaseName;}

inline QString QDBConnection::userName() const
{return m_userName;}

inline QString QDBConnection::password() const
{return m_password;}

inline QString QDBConnection::hostName() const
{return m_hostName;}

inline QString QDBConnection::driverName() const
{return m_type;}

inline int QDBConnection::port() const
{return m_port;}

inline QString QDBConnection::type() const
{ return m_type;}

inline QString QDBConnection::connectOptions() const
{return m_connectOptions;}

inline QString QDBConnection::connectionName() const
{return m_connectionName;}
#endif // QDBCONNECTION_H
