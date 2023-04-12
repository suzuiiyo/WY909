#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include "dbconnection.h"
#include "ied.h"
#include "dbiedinfodao.h"
#include "devstate.h"
#include "dbiedstatedao.h"
DBIedStateDAO::DBIedStateDAO()
    : m_connectionName("connectIedState")
{

}

DBIedStateDAO::~DBIedStateDAO()
{

}

DevState::List DBIedStateDAO::doQuery(const QString &stationName)
{
    DevState::List lstDevState;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT a.IEDNAME, a.CONSTATE, a.VOLTSTATE, a.TEMPERATURESTATE, a.LISTATE, a.DCSTATE, a.SETTINGSTATE, a.CRCSTATE, a.CLOCKOFFSET, a.LASTUPDATETIME, b.IEDDESC FROM iedstate a, iedinfo b WHERE b.STATIONID='%1' AND a.IEDNAME=b.IEDNAME")
                .arg(stationName);
        //printf("sql : %s\n", sql.toStdString().data());
        if(query.exec(sql))
        {
            while(query.next())
            {
                DevState::Ptr devState(new DevState());
                devState->m_iedName = query.value("IEDNAME").toString();
                devState->m_iedDesc = query.value("IEDDESC").toString();
                devState->m_connectionState = query.value("CONSTATE").toInt();
                devState->m_voltState = query.value("VOLTSTATE").toInt();
                devState->m_temperatureState = query.value("TEMPERATURESTATE").toInt();
                devState->m_LIState = query.value("LISTATE").toInt();
                devState->m_DCState = query.value("DCSTATE").toInt();
                devState->m_settingState = query.value("SETTINGSTATE").toInt();
                devState->m_CRCState = query.value("CRCSTATE").toInt();
                devState->m_clockOffset = query.value("CLOCKOFFSET").toInt();
                devState->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
                lstDevState.append(devState);
            }
        }
        db.close();
    }
    return lstDevState;
}

DevState::List DBIedStateDAO::doQuery(const QString &stationName, const QString &voltClass)
{
    DevState::List lstDevState;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT a.IEDNAME, a.CONSTATE, a.VOLTSTATE, a.TEMPERATURESTATE, a.LISTATE, a.DCSTATE, a.SETTINGSTATE, a.CRCSTATE, a.CLOCKOFFSET, a.LASTUPDATETIME, b.IEDDESC FROM iedstate a, iedinfo b WHERE b.STATIONID='%1' AND b.VOLTCLASSID='%2' AND a.IEDNAME=b.IEDNAME")
                .arg(stationName)
                .arg(voltClass);
        if(query.exec(sql))
        {
            while(query.next())
            {
                DevState::Ptr devState(new DevState());
                devState->m_iedName = query.value("IEDNAME").toString();
                devState->m_iedDesc = query.value("IEDDESC").toString();
                devState->m_connectionState = query.value("CONSTATE").toInt();
                devState->m_voltState = query.value("VOLTSTATE").toInt();
                devState->m_temperatureState = query.value("TEMPERATURESTATE").toInt();
                devState->m_LIState = query.value("LISTATE").toInt();
                devState->m_DCState = query.value("DCSTATE").toInt();
                devState->m_settingState = query.value("SETTINGSTATE").toInt();
                devState->m_CRCState = query.value("CRCSTATE").toInt();
                devState->m_clockOffset = query.value("CLOCKOFFSET").toInt();
                devState->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
                lstDevState.append(devState);
            }
        }
        db.close();
    }
    return lstDevState;
}

DevState::List DBIedStateDAO::doQuery(const QString &stationName, const QString &voltClass, const QString &bayName)
{
    DevState::List lstDevState;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT a.IEDNAME, a.CONSTATE, a.VOLTSTATE, a.TEMPERATURESTATE, a.LISTATE, a.DCSTATE, a.SETTINGSTATE, a.CRCSTATE, a.CLOCKOFFSET, a.LASTUPDATETIME, b.IEDDESC FROM iedstate a, iedinfo b WHERE b.STATIONID='%1' AND b.VOLTCLASSID='%2' AND b.BAYID='%3' AND a.IEDNAME=b.IEDNAME")
                .arg(stationName)
                .arg(voltClass)
                .arg(bayName);
        //printf("sql : %s\n", sql.toStdString().data());
        if(query.exec(sql))
        {
            while(query.next())
            {
                DevState::Ptr devState(new DevState());
                devState->m_iedName = query.value("IEDNAME").toString();
                devState->m_iedDesc = query.value("IEDDESC").toString();
                devState->m_connectionState = query.value("CONSTATE").toInt();
                devState->m_voltState = query.value("VOLTSTATE").toInt();
                devState->m_temperatureState = query.value("TEMPERATURESTATE").toInt();
                devState->m_LIState = query.value("LISTATE").toInt();
                devState->m_DCState = query.value("DCSTATE").toInt();
                devState->m_settingState = query.value("SETTINGSTATE").toInt();
                devState->m_CRCState = query.value("CRCSTATE").toInt();
                devState->m_clockOffset = query.value("CLOCKOFFSET").toInt();
                devState->m_lastUpdateTime = query.value("LASTUPDATETIME").toString();
                lstDevState.append(devState);
            }
        }
        db.close();
    }
    return lstDevState;
}

bool DBIedStateDAO::isInit()
{
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        //printf("db open\n");
        QSqlQuery query(db);
        QString sql_s = QObject::tr("TRUNCATE TABLE iedstate");
        query.exec(sql_s);
        DBIedInfoDAO iedDAO;
        Ied::List lstIed = iedDAO.doQuery();
        Ied::List::iterator iter = lstIed.begin();
        int list_size = lstIed.size();
        //printf("list_size: %d\n", list_size);
        QString sql_str = "INSERT INTO iedstate VALUES";
        if(list_size <= 1000)
        {
            //printf("yes size < 1000\n");
            while(iter < lstIed.end())
            {
                QString sql_str_tmp = "";
                Ied::Ptr ied(new Ied());
                ied = *iter;
                QString iedName = ied->iedName();
                sql_str_tmp += "(NULL,'" + iedName + "', -1, -1, -1, -1, -1, -1, -1, 0.000, '-')";
                if(iter < lstIed.end() - 1)
                    sql_str_tmp += ",";
                sql_str += sql_str_tmp;
                iter++;
            }
            //printf("sql = %s", sql_str.toStdString().data());
            QByteArray ba = sql_str.toUtf8();
            QString sql = QObject::tr(ba.data());
            if(!query.exec(sql)){
                db.close();
                return false;
            }
        }
        else
        {
            int count = 0;
            while(iter < lstIed.end())
            {
                QString sql_str_tmp = "";
                Ied::Ptr ied(new Ied());
                ied = *iter;
                QString iedName = ied->iedName();
                sql_str_tmp += "(NULL,'" + iedName + "', -1, -1, -1, -1, -1, -1, -1, 0.000, '-')";

                count++;
                if((count != 0 && count != 1000) && (iter < lstIed.end() - 1))
                    sql_str_tmp += ",";
                sql_str += sql_str_tmp;
                if(count == 1000)
                {
                    QByteArray ba = sql_str.toUtf8();
                    //printf("sql = %s", sql_str.toStdString().data());
                    QString sql = QObject::tr(ba.data());
                    if(!query.exec(sql))
                    {
                        db.close();
                        return false;
                    }
                    sql_str = "INSERT INTO iedstate VALUES";
                    count = 0;
                }
                iter++;
            }
            //printf("sql = %s", sql_str.toStdString().data());
            QByteArray ba = sql_str.toUtf8();
            QString sql = QObject::tr(ba.data());
            if(!query.exec(sql))
            {
                db.close();
                return false;
            }
        }
        db.close();
    }else{
        return false;
    }
    return true;
}
