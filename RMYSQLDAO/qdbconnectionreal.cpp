#include "qdbconnectionreal.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <QMutexLocker>
#include <QThread>
//#include "asynclogger.h"
QMutex  QDBConnectionReal::m_mutex;
QHash<QString,int> QDBConnectionReal::m_ref;
QDBConnectionReal::QDBConnectionReal(const QString &type)
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

QDBConnectionReal::~QDBConnectionReal()
{
    releaseConnection();
}

bool QDBConnectionReal::isOpen() const
{
    QSqlDatabase db = connection();
    return db.isOpen();
}

bool QDBConnectionReal::open()
{
    QSqlDatabase db = connection();
    if (db.isOpen())
        return true;
    return db.open();
}

void QDBConnectionReal::close()
{
    QSqlDatabase db = connection();
    if (db.isOpen())
        connection().close();
}

QSqlError QDBConnectionReal::lastError() const
{
    return connection().lastError();
}

bool QDBConnectionReal::isValid() const
{
    return connection().isValid();
}

bool QDBConnectionReal::transaction()
{
    return connection().transaction();
}

bool QDBConnectionReal::commit()
{
    return connection().commit();
}

bool QDBConnectionReal::rollback()
{
    return connection().rollback();
}

QSqlQuery QDBConnectionReal::exec(const QString &query) const
{
    return connection().exec(query);
}

QDBConnectionReal::operator QSqlDatabase() const
{
    return connection();
}

QSqlDatabase QDBConnectionReal::connection() const
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

void QDBConnectionReal::releaseConnection()
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
