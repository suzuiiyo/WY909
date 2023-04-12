#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QVariant>
#include <QString>
#include <QDateTime>
#include "initmariadb.h"
#include "dbconnectionreal.h"
InitMariaDB::InitMariaDB()
{
    this->initLstIedName();
}

InitMariaDB::~InitMariaDB()
{

}

bool InitMariaDB::initRealData()
{
    QSqlDatabase db = DBConnectionReal::connection("realData", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS realdata");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("realdata");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS realdata("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "DATAREF VARCHAR(255) NOT NULL,"
                          "IEDNAME VARCHAR(255) NOT NULL,"
                          "DATADESC VARCHAR(255) NOT NULL,"
                          "QUALITY VARCHAR(255) NOT NULL,"
                          "UPDATETIME VARCHAR(255) NOT NULL,"
                          "DATATYPE1 INT(11) NOT NULL,"
                          "DATAVALUE1 VARCHAR(255) NOT NULL,"
                          "DATATYPE2 INT(11) NOT NULL,"
                          "DATAVALUE2 VARCHAR(255) NOT NULL,"
                          "DATATYPE3 INT(11) NOT NULL,"
                          "DATAVALUE3 VARCHAR(255) NOT NULL,"
                          "DATATYPE4 INT(11) NOT NULL,"
                          "DATAVALUE4 VARCHAR(255) NOT NULL,"
                          "DATATYPE5 INT(11) NOT NULL,"
                          "DATAVALUE5 VARCHAR(255) NOT NULL,"
                          "BUSINESS VARCHAR(255) NOT NULL,"
                          "PRIMARY KEY(GUID),"
                          "UNIQUE KEY UK_realdata_DATAREF (DATAREF))");
        db.close();
    }

    return true;
}

bool InitMariaDB::initGooseRealData()
{
    QSqlDatabase db = DBConnectionReal::connection("gooseRealData", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS gooserealdata");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("gooserealdata");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS gooserealdata("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "APPID INT(11) NOT NULL,"
                          "DATAREF VARCHAR(255) NOT NULL,"
                          "IEDNAME VARCHAR(255) NOT NULL,"
                          "DATATYPE INT(11) NOT NULL,"
                          "DATAVALUE VARCHAR(255) NOT NULL,"
                          "UPDATETIME VARCHAR(255) NOT NULL,"
                          "PRIMARY KEY(GUID),"
                          "UNIQUE KEY UK_gooserealdata_DATAREFANDAPPID (APPID, DATAREF))");
        db.close();
    }

    return true;
}

bool InitMariaDB::initActionEvent()
{
    QSqlDatabase db = DBConnectionReal::connection("actionevent", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS actionevent");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("actionevent");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initAlarmEvent()
{
    QSqlDatabase db = DBConnectionReal::connection("alarmevent", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS alarmevent");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("alarmevent");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initConnectionState()
{
    QSqlDatabase db = DBConnectionReal::connection("connectionState", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS connectionstate");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("connectionstate");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAVALUE INT(11) NOT NULL,"
                                  "LASTUPDATETIME VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID),"
                                  "UNIQUE KEY UK_%1_%2_IEDNAME(IEDNAME))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initConnectHistory()
{
    QSqlDatabase db = DBConnectionReal::connection("connectHistory", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS connecthistory");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("connecthistory");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAVALUE INT(11) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initDevtemperature()
{
    QSqlDatabase db = DBConnectionReal::connection("devTemperature", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS devtemperature");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("devtemperature");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "SCOPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initSendOptPower()
{
    QSqlDatabase db = DBConnectionReal::connection("sendOptPower", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS sendoptpower");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("sendoptpower");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "SCOPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initRecvOptPower()
{
    QSqlDatabase db = DBConnectionReal::connection("recvOptPower", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS recvoptpower");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("recvoptpower");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "SCOPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initPilotChannelOptPower()
{
    QSqlDatabase db = DBConnectionReal::connection("pilotChannelOptPower", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS pilotchanneloptpower");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("pilotchanneloptpower");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "SCOPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initPowerVoltage()
{
    QSqlDatabase db = DBConnectionReal::connection("powerVoltage", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS powervoltage");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("powervoltage");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "SCOPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initDifferentialCurrent()
{
    QSqlDatabase db = DBConnectionReal::connection("differentialCurrent", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS differentialcurrent");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("differentialcurrent");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE1 INT(11) NOT NULL,"
                                  "DATAVALUE1 VARCHAR(255) NOT NULL,"
                                  "DATATYPE2 INT(11) NOT NULL,"
                                  "DATAVALUE2 VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "SCOPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initEarlyWarning()
{
    QSqlDatabase db = DBConnectionReal::connection("earlyWarning", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS earlywarning");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("earlywarning");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS earlywarning("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "DATAREF VARCHAR(255) NOT NULL,"
                          "EWTYPE INT(11) NOT NULL,"
                          "UPLIMITSTATE INT(11) NOT NULL,"
                          "DOWNLIMITSTATE INT(11) NOT NULL,"
                          "MUTATIONSTATE INT(11) NOT NULL,"
                          "LASTCYCLEULSTATE INT(11) NOT NULL,"
                          "LASTCYCLEDLSTATE INT(11) NOT NULL,"
                          "TRENDULSTATE INT(11) NOT NULL,"
                          "TRENDDLSTATE INT(11) NOT NULL,"
                          "UPLIMITSTATEENABLE INT(11) NOT NULL,"
                          "DOWNLIMITSTATEENABLE INT(11) NOT NULL,"
                          "MUTATIONSTATEENABLE INT(11) NOT NULL,"
                          "LASTCYCLEULSTATEENABLE INT(11) NOT NULL,"
                          "LASTCYCLEDLSTATEENABLE INT(11) NOT NULL,"
                          "TRENDULSTATEENABLE INT(11) NOT NULL,"
                          "TRENDDLSTATEENABLE INT(11) NOT NULL,"
                          "ISMONITOR INT(11) NOT NULL,"
                          "PRIMARY KEY(GUID))");
        db.close();
    }

    return true;
}

bool InitMariaDB::initEarlyWarningRecord()
{
    QSqlDatabase db = DBConnectionReal::connection("earlyWarningRecord", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS earlywarningrecord");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("earlywarningrecord");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS earlywarningrecord("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "DATAREF VARCHAR(255) NOT NULL,"
                          "WARNINGTYPE INT(11) NOT NULL,"
                          "EWTYPE INT(11) NOT NULL,"
                          "DATAVALUE FLOAT(8,3) NOT NULL,"
                          "RECORDTIME VARCHAR(255) NOT NULL,"
                          "MAXDATA FLOAT(8,3) NOT NULL,"
                          "MINDATA FLOAT(8,3) NOT NULL,"
                          "MUTATIONVALUE FLOAT(8,3) NOT NULL,"
                          "PRIMARY KEY(GUID))");
        db.close();
    }

    return true;
}

bool InitMariaDB::initIedState()
{
    QSqlDatabase db = DBConnectionReal::connection("iedState", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS iedstate");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("iedstate");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS iedstate("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "IEDNAME VARCHAR(255) NOT NULL,"
                          "BAYNAME VARCHAR(255) NOT NULL,"
                          "STATE INT(11) NOT NULL,"
                          "UPDATETIME VARCHAR(255) NOT NULL,"
                          "SETTYPE VARCHAR(255) NOT NULL,"
                          "PRIMARY KEY(GUID),"
                          "UNIQUE KEY UK_iedstate_IEDNAME (IEDNAME))");
        db.close();
    }

    return true;
}

bool InitMariaDB::initBayState()
{
    QSqlDatabase db = DBConnectionReal::connection("bayState", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS baystate");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("baystate");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS baystate("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "BAYNAME VARCHAR(255) NOT NULL,"
                          "STATE INT(11) NOT NULL,"
                          "SETTYPE VARCHAR(255) NOT NULL,"
                          "UPDATETIME VARCHAR(255) NOT NULL,"
                          "DEVCORRESPONDINGSTATE INT(11) NOT NULL,"
                          "PRIMARY KEY(GUID),"
                          "UNIQUE KEY UK_baystate_BAYNAME (BAYNAME))");
        db.close();
    }

    return true;
}

bool InitMariaDB::initDevNonCorrespondingRecord()
{
    QSqlDatabase db = DBConnectionReal::connection("devNonCorrespondingRecord", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS devnoncorrespondingrecord");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("devnoncorrespondingrecord");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS devnoncorrespondingrecord("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "BAYNAME VARCHAR(255) NOT NULL,"
                          "BAYTYPE VARCHAR(255) NOT NULL,"
                          "SETTYPE VARCHAR(255) NOT NULL,"
                          "STATE INT(11) NOT NULL,"
                          "IEDNAME VARCHAR(255) NOT NULL,"
                          "IEDDESC VARCHAR(255) NOT NULL,"
                          "BAYCOMPCOD LONGTEXT,"
                          "IEDCOMPRLT LONGTEXT,"
                          "UPDATETIME VARCHAR(255) NOT NULL DEFAULT current_timestamp(),"
                          "REMARKS VARCHAR(255) NOT NULL,"
                          "PRIMARY KEY(GUID))");
        db.close();
    }

    return true;
}

bool InitMariaDB::initLoopPortAlarmRecord()
{
    QSqlDatabase db = DBConnectionReal::connection("loopLinkAlarmRecord", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS looplinkalarmrecord");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("looplinkalarmrecord");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS looplinkalarmrecord("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "LINEREF VARCHAR(255) NOT NULL,"
                          "RESULT VARCHAR(255) NOT NULL,"
                          "P1GUID VARCHAR(255) NOT NULL,"
                          "P2GUID INT(11) NOT NULL,"
                          "CFREF VARCHAR(255) NOT NULL,"
                          "PDTIME VARCHAR(255) NOT NULL,"
                          "XRESULT VARCHAR(255) NOT NULL,"
                          "YJAPPID VARCHAR(255) NOT NULL,"
                          "PRIMARY KEY(GUID))");
        db.close();
    }

    return true;
}

bool InitMariaDB::initLoopLinkAlarmRecord()
{
    QSqlDatabase db = DBConnectionReal::connection("loopLinkAlarmRecord", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS looplinkalarmrecord");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("looplinkalarmrecord");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS looplinkalarmrecord("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "LINEREF VARCHAR(255) NOT NULL,"
                          "RESULT VARCHAR(255) NOT NULL,"
                          "P1GUID VARCHAR(255) NOT NULL,"
                          "P2GUID INT(11) NOT NULL,"
                          "CFREF VARCHAR(255) NOT NULL,"
                          "PDTIME VARCHAR(255) NOT NULL,"
                          "XRESULT VARCHAR(255) NOT NULL,"
                          "YJAPPID VARCHAR(255) NOT NULL,"
                          "PRIMARY KEY(GUID))");
        db.close();
    }

    return true;
}

//bool InitMariaDB::initGooseRecord()
//{

//}

bool InitMariaDB::initRunStateRecord()
{
    QSqlDatabase db = DBConnectionReal::connection("runStateRecord", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS runstaterecord");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("runstaterecord");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "SCOPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initAnaRecord()
{
    QSqlDatabase db = DBConnectionReal::connection("anaRecord", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS anarecord");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("anarecord");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initStrapRecord()
{
    QSqlDatabase db = DBConnectionReal::connection("strapRecord", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS straprecord");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("straprecord");
    if(db.isOpen() || db.open())
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        QString year = currentTimeStr.mid(0, 4);
        if(!m_lstIedName.isEmpty())
        {
            QSqlQuery query(db);
            for(int i=0; i<m_lstIedName.size(); i++)
            {
                sql = QObject::tr("CREATE TABLE IF NOT EXISTS %1_%2("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "QUALITY VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "SCOPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))"
                                  "partition by range(unix_timestamp(RECORDTIME))("
                                  "partition p0 values less than (unix_timestamp('%2-01-31 23:59:59')),"
                                  "partition p1 values less than (unix_timestamp('%2-02-29 23:59:59')),"
                                  "partition p2 values less than (unix_timestamp('%2-03-31 23:59:59')),"
                                  "partition p3 values less than (unix_timestamp('%2-04-30 23:59:59')),"
                                  "partition p4 values less than (unix_timestamp('%2-05-31 23:59:59')),"
                                  "partition p5 values less than (unix_timestamp('%2-06-30 23:59:59')),"
                                  "partition p6 values less than (unix_timestamp('%2-07-31 23:59:59')),"
                                  "partition p7 values less than (unix_timestamp('%2-08-31 23:59:59')),"
                                  "partition p8 values less than (unix_timestamp('%2-09-30 23:59:59')),"
                                  "partition p9 values less than (unix_timestamp('%2-10-31 23:59:59')),"
                                  "partition p10 values less than (unix_timestamp('%2-11-30 23:59:59')),"
                                  "partition p11 values less than (unix_timestamp('%2-12-31 23:59:59'))")
                        .arg(m_lstIedName.at(i))//1
                        .arg(year);//2
                if(!query.exec(sql))
                    return false;
            }
        }
        db.close();
    }

    return true;
}

bool InitMariaDB::initTimeSynRecord()
{
    QSqlDatabase db = DBConnectionReal::connection("timeSynRecord", "QMYSQL", "");
    QString sql = QObject::tr("CREATE DATABASE IF NOT EXISTS timesynrecord");
    db.exec(sql);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");
    db.setDatabaseName("timesynrecord");
    if(db.isOpen() || db.open())
    {
        sql = QObject::tr("CREATE TABLE IF NOT EXISTS timesynrecord("
                          "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                          "IEDNAME VARCHAR(255) NOT NULL,"
                          "DATAREF VARCHAR(255) NOT NULL,"
                          "DATADESC VARCHAR(255) NOT NULL,"
                          "DATATYPE INT(11) NOT NULL,"
                          "DATAVALUE VARCHAR(255) NOT NULL,"
                          "QUALITY VARCHAR(255) NOT NULL,"
                          "RECORDTIME VARCHAR(255) NOT NULL,"
                          "PRIMARY KEY(GUID))");
        db.close();
    }

    return true;
}

void InitMariaDB::initLstIedName()
{
    QSqlDatabase db = DBConnectionReal::connection("selectIedInfo", "QSQLITE", "Sysconfig");
    if(db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("select IEDNAME from iedinfo");
        if(query.exec(sql))
        {
            while(query.next())
            {
                QString iedName = query.value("IEDNAME").toString();
                m_lstIedName.append(iedName);
            }
        }
        db.close();
    }
}

