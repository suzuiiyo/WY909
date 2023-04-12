#include "qdbconnection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <QMutexLocker>
#include <QThread>
//#include "asynclogger.h"
QMutex  QDBConnection::m_mutex;
QHash<QString,int> QDBConnection::m_ref;
QDBConnection::QDBConnection(const QString &type)
    : m_connectionName(QString::number((qint64)QThread::currentThreadId()))
    , m_type(type)
    , m_port(0)
{
    QMutexLocker locker(&m_mutex);
    if (m_ref.contains(m_connectionName))
        m_ref[m_connectionName]++;
    else
        m_ref[m_connectionName] = 1;
}

QDBConnection::~QDBConnection()
{
    releaseConnection();
}

bool QDBConnection::isOpen() const
{
    QSqlDatabase db = connection();
    return db.isOpen();
}

bool QDBConnection::open()
{
    QSqlDatabase db = connection();
    if (db.isOpen())
        return true;
    return db.open();
}

void QDBConnection::close()
{
    QSqlDatabase db = connection();
    if (db.isOpen())
        connection().close();
}

QSqlError QDBConnection::lastError() const
{
    return connection().lastError();
}

bool QDBConnection::isValid() const
{
    return connection().isValid();
}

bool QDBConnection::transaction()
{
    return connection().transaction();
}

bool QDBConnection::commit()
{
    return connection().commit();
}

bool QDBConnection::rollback()
{
    return connection().rollback();
}

QSqlQuery QDBConnection::exec(const QString &query) const
{
    return connection().exec(query);
}

QDBConnection::operator QSqlDatabase() const
{
    return connection();
}

QSqlDatabase QDBConnection::connection() const
{
    QMutexLocker locker(&m_mutex);
    if (QSqlDatabase::contains(m_connectionName))
    {
        return  QSqlDatabase::database(m_connectionName,false);
    }
    QSqlDatabase db = QSqlDatabase::addDatabase(m_type, m_connectionName);
    db.setDatabaseName(m_databaseName);
    if(m_type == "QMYSQL")
    {
        db.setUserName(m_userName);
        db.setPassword(m_password);
        db.setHostName(m_hostName);
        db.setConnectOptions(m_connectOptions);
        db.setPort(m_port);
    }
    return db;
}

void QDBConnection::releaseConnection()
{
    QMutexLocker locker(&m_mutex);
    m_ref[m_connectionName]--;
    if (m_ref[m_connectionName] == 0)
    {
        if (QSqlDatabase::contains(m_connectionName))
        {
            QSqlDatabase::database(m_connectionName,false).close();
            QSqlDatabase::removeDatabase(m_connectionName);
        }
    }
}
