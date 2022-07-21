#include <QSqlQuery>
#include <QObject>
#include <QVariant>
#include <QString>
#include <QDateTime>
#include "dbconnectionreal.h"
#include "dbprotvoltagedao.h"
DBProtVoltageDAO::DBProtVoltageDAO()
    : m_connectionName("connectProtVoltage")
{

}

DBProtVoltageDAO::~DBProtVoltageDAO()
{

}

bool DBProtVoltageDAO::doInsert(QSqlDatabase db, ProtVoltage::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
      return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    ProtVoltage::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        ProtVoltage::Ptr ptr(new ProtVoltage());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO protvoltage(GUID, IEDNAME, DATAREF, DATADESC, DATATYPE1, DATAVALUE1, DATATYPE2, DATAVALUE2, QUALITY, RECORDTIME) VALUES(NULL, '%1', '%2', '%3', %4, '%5', %6, '%7', '%8', '%9', '')")
                .arg(ptr->iedName())     // 1
                .arg(ptr->dataRef())     // 2
                .arg(ptr->dataDesc())    // 3
                .arg(ptr->dataType1())   // 4
                .arg(ptr->dataValue1())  // 5
                .arg(ptr->dataType2())   // 6
                .arg(ptr->dataValue2())  // 7
                .arg(ptr->quality())     // 8
                .arg(ptr->recordTime()); // 9
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

bool DBProtVoltageDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QDateTime time = QDateTime::currentDateTime();
        QString time_str1 = time.addDays(+1).toString("yyyyMMdd");
        QString time_str2 = time.addDays(+1).toString("yyyy-MM-dd");
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS protvoltage("
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
                                  "DBTIME DATETIME NOT NULL DEFAULT NOW(),"
                                  "SCOPE VARCHAR(255) NOT NULL,"
                                  "PRIMARY KEY(GUID, DBTIME))"
                                  "PARTITION BY RANGE(TO_DAYS(DBTIME))("
                                  "PARTITION p%1 VALUES LESS THAN(TO_DAYS('%2')))")
                .arg(time_str1)
                .arg(time_str2);
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
