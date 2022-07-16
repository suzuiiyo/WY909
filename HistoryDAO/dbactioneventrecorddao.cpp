#include <QString>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QObject>
#include <QVariant>
#include "dbconnection.h"
#include "eventrecord.h"
#include "dbactioneventrecorddao.h"
DBActionEventRecordDAO::DBActionEventRecordDAO()
    : m_connectionName("connectActionEventRecord")
{

}
DBActionEventRecordDAO::~DBActionEventRecordDAO()
{

}

EventRecord::List DBActionEventRecordDAO::doQuery(const QString &iedName, bool *ok)
{
    EventRecord::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.GUID, a.DATAREF, a.DATAVALUE, a.RECORDTIME, b.IEDNAME, b.DATADESC FROM actioneventrecord a, ieddataset b WHERE b.IEDNAME='%1' AND a.DATAREF=b.DATAREF")
                .arg(iedName);

        QSqlQuery query(db);

        if(query.exec(sql))
        {
            while(query.next())
            {
                EventRecord::Ptr ptr(new EventRecord());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_dataDesc = query.value("DATADESC").toString();
                ptr->m_dataValue = query.value("DATAVALUE").toString();
                ptr->m_recordTime = query.value("RECORDTIME").toString();
                lst.append(ptr);
            }
            *ok = true;
        }
        else
            *ok = false;
        db.close();
    }

    return lst;
}

bool DBActionEventRecordDAO::doInsert(EventRecord::List &lst)
{
    bool bSucc = false;

    EventRecord::List::iterator iter = lst.begin();

    QString sql_str = "INSERT INTO actioneventrecord VALUES";

    int list_size = lst.size();

    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        if(list_size <= 1000)
        {
            while(iter < lst.end())
            {
                QString sql_str_tmp = "";
                EventRecord::Ptr ptr(new EventRecord());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dataValue = ptr->dataValue();
                QString recordTime = ptr->recordTime();

                sql_str_tmp += "(NULL,'" + dataRef  + "','" + dataValue + "','" + recordTime + "')";
                if(iter < lst.end() - 1)
                    sql_str_tmp += ",";
                sql_str += sql_str_tmp;
                iter++;
            }

            QByteArray ba = sql_str.toUtf8();
            QString sql = QObject::tr(ba.data());
            bSucc = query.exec(sql);
            if(bSucc == false){
                return false;
            }
        }
        else
        {
            int count = 0;
            while(iter < lst.end())
            {
                QString sql_str_tmp = "";
                EventRecord::Ptr ptr(new EventRecord());
                ptr = *iter;

                QString dataRef = ptr->dataRef();
                QString dataValue = ptr->dataValue();
                QString recordTime = ptr->recordTime();

                sql_str_tmp += "(NULL,'" + dataRef  + "','" + dataValue + "','" + recordTime + "')";

                count++;
                if((count != 0 && count != 1000) && (iter < lst.end() - 1))
                    sql_str_tmp += ",";
                sql_str += sql_str_tmp;
                if(count == 1000)
                {
                    QByteArray ba = sql_str.toUtf8();
                    QString sql = QObject::tr(ba.data());
                    bSucc = query.exec(sql);
                    if(bSucc == false)
                    {
                        db.close();
                        return false;
                    }
                    sql_str = "INSERT INTO actioneventrecords VALUES";
                    count = 0;
                }
                iter++;
            }
            QByteArray ba = sql_str.toUtf8();
            QString sql = QObject::tr(ba.data());
            bSucc = query.exec(sql);
            if(bSucc == false)
            {
                db.close();
                return false;
            }
        }
        db.close();
    }
    return bSucc;
}
