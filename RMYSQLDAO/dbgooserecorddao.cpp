#include <QObject>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include "dbconnectionreal.h"
#include "dbgooserecorddao.h"
DBGooseRecordDAO::DBGooseRecordDAO()
    : m_connectionName("connectGooseRecord")
{

}

DBGooseRecordDAO::~DBGooseRecordDAO()
{

}

bool DBGooseRecordDAO::doInsert(QSqlDatabase db, GooseRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    GooseRecord::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        GooseRecord::Ptr ptr(new GooseRecord());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO gooserecord VALUES(NULL, %1, '%2', '%3', '%4', %5, '%6', '%7')")
                    .arg(ptr->appId())          // 1
                    .arg(ptr->dataRef())        // 2
                    .arg(ptr->iedName())        // 3
                    .arg(ptr->dataDesc())       // 4
                    .arg(ptr->dataType())       // 5
                    .arg(ptr->dataValue())      // 6
                    .arg(ptr->recordTime());    // 7
        if (!query.exec(sql))
            return false;
        count++;
        if (count == 200)
        {
            bSucc = query.exec("COMMIT");
            query.exec("START TRANSACTION");
            count = 0;
        }
    }
    bSucc = query.exec("COMMIT");

    return bSucc;
}

bool DBGooseRecordDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "goosedb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS gooserecord("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "APPID INT(11) NOT NULL,"
                                  "DATAREF VARCHAR(255) NOT NULL,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "DATADESC VARCHAR(255) NOT NULL,"
                                  "DATATYPE INT(11) NOT NULL,"
                                  "DATAVALUE VARCHAR(255) NOT NULL,"
                                  "RECORDTIME VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

