#ifndef QDBCONNECTIONREAL_H
#define QDBCONNECTIONREAL_H
#include <QString>
#include <QMutex>
#include <QHash>
class QSqlDatabase;
class QSqlError;
class QSqlQuery;
class QDBConnectionReal
{
public:
    QDBConnectionReal(const QString &type = "QMYSQL");
    ~QDBConnectionReal();
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
    Q_DISABLE_COPY(QDBConnectionReal)
};

inline void QDBConnectionReal::setDatabaseName(const QString &name)
{m_databaseName = name;}

inline void QDBConnectionReal::setUserName(const QString &name)
{m_userName = name;}

inline void QDBConnectionReal::setPassword(const QString &password)
{m_password = password;}

inline void QDBConnectionReal::setHostName(const QString &host)
{m_hostName = host;}

inline void QDBConnectionReal::setPort(int p)
{m_port = p;}

inline void QDBConnectionReal::setType(const QString &type)
{ m_type = type;}

inline void QDBConnectionReal::setConnectOptions(const QString &options)
{m_connectOptions = options;}

inline QString QDBConnectionReal::databaseName() const
{return m_databaseName;}

inline QString QDBConnectionReal::userName() const
{return m_userName;}

inline QString QDBConnectionReal::password() const
{return m_password;}

inline QString QDBConnectionReal::hostName() const
{return m_hostName;}

inline QString QDBConnectionReal::driverName() const
{return m_type;}

inline int QDBConnectionReal::port() const
{return m_port;}

inline QString QDBConnectionReal::type() const
{ return m_type;}

inline QString QDBConnectionReal::connectOptions() const
{return m_connectOptions;}

inline QString QDBConnectionReal::connectionName() const
{return m_connectionName;}
#endif // QDBCONNECTIONREAL_H
