#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "realdata.h"
#include "earlywarning.h"
#include "dbconnectionreal.h"
#include "dbearlywarningdao.h"
//#include "earlywarningconfig.h"
//#include "dbearlywarningconfigdao.h"
DBEarlyWarningDAO::DBEarlyWarningDAO()
    : m_connectionName("connectEW")
{

}

DBEarlyWarningDAO::~DBEarlyWarningDAO()
{

}

EarlyWarning::Hash DBEarlyWarningDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    EarlyWarning::Hash hsh;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM earlywarning");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                EarlyWarning::Ptr ptr(new EarlyWarning());
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_ewType = query.value("EWTYPE").toInt();
                ptr->m_upLimitState = query.value("UPLIMITSTATE").toInt();
                ptr->m_downLimitState = query.value("DOWNLIMITSTATE").toInt();
                ptr->m_mutationState = query.value("MUTATIONSTATE").toInt();
                ptr->m_lastCycleULState = query.value("LASTCYCLEULSTATE").toInt();
                ptr->m_lastCycleDLState = query.value("LASTCYCLEDLSTATE").toInt();
                ptr->m_trendULState = query.value("TRENDULSTATE").toInt();
                ptr->m_trendDLState = query.value("TRENDDLSTATE").toInt();
                ptr->m_upLimitStateEnable = query.value("UPLIMITSTATEENABLE").toInt();
                ptr->m_downLimitStateEnable = query.value("DOWNLIMITSTATEENABLE").toInt();
                ptr->m_mutationStateEnable = query.value("MUTATIONSTATEENABLE").toInt();
                ptr->m_lastCycleULStateEnable = query.value("LASTCYCLEULSTATEENABLE").toInt();
                ptr->m_lastCycleDLStateEnable = query.value("LASTCYCLEDLSTATEENABLE").toInt();
                ptr->m_trendULStateEnable = query.value("TRENDULSTATEENABLE").toInt();
                ptr->m_trendDLStateEnable = query.value("TRENDDLSTATEENABLE").toInt();
                ptr->m_isMonitor = query.value("ISMONITOR").toInt();
                QString dataRef = ptr->dataRef();
                if(!hsh.contains(dataRef))
                    hsh.insert(dataRef, ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

EarlyWarning::Hash DBEarlyWarningDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    EarlyWarning::Hash hsh;
    QSqlQuery query(db);

    QString sql = QObject::tr("SELECT * FROM earlywarning");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            EarlyWarning::Ptr ptr(new EarlyWarning());
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_ewType = query.value("EWTYPE").toInt();
            ptr->m_upLimitState = query.value("UPLIMITSTATE").toInt();
            ptr->m_downLimitState = query.value("DOWNLIMITSTATE").toInt();
            ptr->m_mutationState = query.value("MUTATIONSTATE").toInt();
            ptr->m_lastCycleULState = query.value("LASTCYCLEULSTATE").toInt();
            ptr->m_lastCycleDLState = query.value("LASTCYCLEDLSTATE").toInt();
            ptr->m_trendULState = query.value("TRENDULSTATE").toInt();
            ptr->m_trendDLState = query.value("TRENDDLSTATE").toInt();
            ptr->m_upLimitStateEnable = query.value("UPLIMITSTATEENABLE").toInt();
            ptr->m_downLimitStateEnable = query.value("DOWNLIMITSTATEENABLE").toInt();
            ptr->m_mutationStateEnable = query.value("MUTATIONSTATEENABLE").toInt();
            ptr->m_lastCycleULStateEnable = query.value("LASTCYCLEULSTATEENABLE").toInt();
            ptr->m_lastCycleDLStateEnable = query.value("LASTCYCLEDLSTATEENABLE").toInt();
            ptr->m_trendULStateEnable = query.value("TRENDULSTATEENABLE").toInt();
            ptr->m_trendDLStateEnable = query.value("TRENDDLSTATEENABLE").toInt();
            ptr->m_isMonitor = query.value("ISMONITOR").toInt();
            QString dataRef = ptr->dataRef();
            if(!hsh.contains(dataRef))
                hsh.insert(dataRef, ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

EarlyWarning::Ptr DBEarlyWarningDAO::doQuery(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM earlywarning WHERE DATAREF='%1'")
                .arg(dataRef);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                EarlyWarning::Ptr ptr(new EarlyWarning());
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_ewType = query.value("EWTYPE").toInt();
                ptr->m_upLimitState = query.value("UPLIMITSTATE").toInt();
                ptr->m_downLimitState = query.value("DOWNLIMITSTATE").toInt();
                ptr->m_mutationState = query.value("MUTATIONSTATE").toInt();
                ptr->m_lastCycleULState = query.value("LASTCYCLEULSTATE").toInt();
                ptr->m_lastCycleDLState = query.value("LASTCYCLEDLSTATE").toInt();
                ptr->m_trendULState = query.value("TRENDULSTATE").toInt();
                ptr->m_trendDLState = query.value("TRENDDLSTATE").toInt();
                ptr->m_upLimitStateEnable = query.value("UPLIMITSTATEENABLE").toInt();
                ptr->m_downLimitStateEnable = query.value("DOWNLIMITSTATEENABLE").toInt();
                ptr->m_mutationStateEnable = query.value("MUTATIONSTATEENABLE").toInt();
                ptr->m_lastCycleULStateEnable = query.value("LASTCYCLEULSTATEENABLE").toInt();
                ptr->m_lastCycleDLStateEnable = query.value("LASTCYCLEDLSTATEENABLE").toInt();
                ptr->m_trendULStateEnable = query.value("TRENDULSTATEENABLE").toInt();
                ptr->m_trendDLStateEnable = query.value("TRENDDLSTATEENABLE").toInt();
                ptr->m_isMonitor = query.value("ISMONITOR").toInt();
                db.close();
                if(ok)
                    *ok = bSucc;

                return ptr;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

EarlyWarning::Ptr DBEarlyWarningDAO::doQuery(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM earlywarning WHERE DATAREF='%1'")
            .arg(dataRef);
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            EarlyWarning::Ptr ptr(new EarlyWarning());
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_ewType = query.value("EWTYPE").toInt();
            ptr->m_upLimitState = query.value("UPLIMITSTATE").toInt();
            ptr->m_downLimitState = query.value("DOWNLIMITSTATE").toInt();
            ptr->m_mutationState = query.value("MUTATIONSTATE").toInt();
            ptr->m_lastCycleULState = query.value("LASTCYCLEULSTATE").toInt();
            ptr->m_lastCycleDLState = query.value("LASTCYCLEDLSTATE").toInt();
            ptr->m_trendULState = query.value("TRENDULSTATE").toInt();
            ptr->m_trendDLState = query.value("TRENDDLSTATE").toInt();
            ptr->m_upLimitStateEnable = query.value("UPLIMITSTATEENABLE").toInt();
            ptr->m_downLimitStateEnable = query.value("DOWNLIMITSTATEENABLE").toInt();
            ptr->m_mutationStateEnable = query.value("MUTATIONSTATEENABLE").toInt();
            ptr->m_lastCycleULStateEnable = query.value("LASTCYCLEULSTATEENABLE").toInt();
            ptr->m_lastCycleDLStateEnable = query.value("LASTCYCLEDLSTATEENABLE").toInt();
            ptr->m_trendULStateEnable = query.value("TRENDULSTATEENABLE").toInt();
            ptr->m_trendDLStateEnable = query.value("TRENDDLSTATEENABLE").toInt();
            ptr->m_isMonitor = query.value("ISMONITOR").toInt();
            if(ok)
                *ok = bSucc;
            //db.close();
            return ptr;
        }
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

bool DBEarlyWarningDAO::doInsert(EarlyWarning::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        //QString sql_str = "INSERT INTO realdata VALUES";
        EarlyWarning::List::iterator iter;
        //QString sql_str_tmp = "";
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            EarlyWarning::Ptr ptr(new EarlyWarning());
            ptr = *iter;

            sql = QObject::tr("INSERT INTO earlywarning VALUES(NULL, '%1', %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14, %15, %16, %17)")
                    .arg(ptr->dataRef())//1
                    .arg(ptr->ewType())//2
                    .arg(ptr->upLimitState())//3
                    .arg(ptr->downLimitState())//4
                    .arg(ptr->mutationState())//5
                    .arg(ptr->lastCycleULState())//6
                    .arg(ptr->lastCycleDLState())//7
                    .arg(ptr->trendULState())//8
                    .arg(ptr->trendDLState())//9
                    .arg(ptr->upLimitStateEnable())//10
                    .arg(ptr->downLimitStateEnable())//11
                    .arg(ptr->mutationStateEnable())//12
                    .arg(ptr->lastCycleULStateEnable())//13
                    .arg(ptr->lastCycleDLStateEnable())//14
                    .arg(ptr->trendULStateEnable())//15
                    .arg(ptr->trendDLStateEnable())//16
                    .arg(ptr->isMonitor());//17
           if(!query.exec(sql))
           {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return false;
           }
        }
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

bool DBEarlyWarningDAO::doInsert(QSqlDatabase db, EarlyWarning::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    EarlyWarning::List::iterator iter;
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        EarlyWarning::Ptr ptr(new EarlyWarning());
        ptr = *iter;

        sql = QObject::tr("INSERT INTO earlywarning VALUES(NULL, '%1', %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14, %15, %16, %17)")
                .arg(ptr->dataRef())//1
                .arg(ptr->ewType())//2
                .arg(ptr->upLimitState())//3
                .arg(ptr->downLimitState())//4
                .arg(ptr->mutationState())//5
                .arg(ptr->lastCycleULState())//6
                .arg(ptr->lastCycleDLState())//7
                .arg(ptr->trendULState())//8
                .arg(ptr->trendDLState())//9
                .arg(ptr->upLimitStateEnable())//10
                .arg(ptr->downLimitStateEnable())//11
                .arg(ptr->mutationStateEnable())//12
                .arg(ptr->lastCycleULStateEnable())//13
                .arg(ptr->lastCycleDLStateEnable())//14
                .arg(ptr->trendULStateEnable())//15
                .arg(ptr->trendDLStateEnable())//16
                .arg(ptr->isMonitor());//17
       if(!query.exec(sql))
       {
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
            return false;
       }
    }
    bSucc = query.exec("COMMIT");

    return bSucc;
}

bool DBEarlyWarningDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS earlywarning("
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
                                  "PRIMARY KEY(GUID),"
                                  "UNIQUE KEY UK_earlywarning_DATAREF(DATAREF))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}


//bool DBEarlyWarningDAO::doInit()
//{
//    bool bSucc = false;
//    DBEarlyWarningConfigDAO dao_ewConfig;
//    EarlyWarningConfig::List lst_ewConfig = dao_ewConfig.doQuery();
//    if(lst_ewConfig.size() == 0)
//        return bSucc;

//    QHash<QString, int> hsh;
//    EarlyWarning::List lst_ew;
//    EarlyWarningConfig::List::iterator iter;
//    for(iter=lst_ewConfig.begin(); iter!=lst_ewConfig.end(); iter++)
//    {
//        //EarlyWarningConfig::Ptr ptr_ewC(new EarlyWarningConfig());
//        EarlyWarningConfig::Ptr ptr_ewC(new EarlyWarningConfig());
//        ptr_ewC = *iter;
//        if(!hsh.contains(ptr_ewC->dataRef()))
//        {
//            EarlyWarning::Ptr ptr_ew(new EarlyWarning());
//            ptr_ew->setDataRef(ptr_ewC->dataRef());
//            ptr_ew->setEwType(ptr_ewC->ewType());
//            hsh.insert(ptr_ew->dataRef(), 1);
//            lst_ew.append(ptr_ew);
//        }
//    }
//    bSucc = doInsert(lst_ew);
//    return bSucc;
//}

//bool DBEarlyWarningDAO::doInit(QSqlDatabase db, QSqlDatabase dbR)
//{
//    bool bSucc = false;

//    return bSucc;
//}

bool DBEarlyWarningDAO::doUpdate(const EarlyWarning::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE earlywarning SET UPLIMITSTATE=%1, DOWNLIMITSTATE=%2, MUTATIONSTATE=%3, LASTCYCLEULSTATE=%4, LASTCYCLEDLSTATE=%5, TRENDULSTATE=%6, TRENDDLSTATE=%7, ISMONITOR=%8 WHERE DATAREF='%9'")
                .arg(ptr->upLimitState())//1
                .arg(ptr->downLimitState())//2
                .arg(ptr->mutationState())//3
                .arg(ptr->lastCycleULState())//4
                .arg(ptr->lastCycleDLState())//5
                .arg(ptr->trendULState())//6
                .arg(ptr->trendDLState())//7
                .arg(ptr->isMonitor())//8
                .arg(ptr->dataRef());//9
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBEarlyWarningDAO::doUpdate(EarlyWarning::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    EarlyWarning::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        while(iter < lst.end())
        {
            EarlyWarning::Ptr ptr(new EarlyWarning());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE earlywarning SET UPLIMITSTATE=%1, DOWNLIMITSTATE=%2, MUTATIONSTATE=%3, LASTCYCLEULSTATE=%4, LASTCYCLEDLSTATE=%5, TRENDULSTATE=%6, TRENDDLSTATE=%7, ISMONITOR=%8 WHERE DATAREF='%9'")
                    .arg(ptr->upLimitState())//1
                    .arg(ptr->downLimitState())//2
                    .arg(ptr->mutationState())//3
                    .arg(ptr->lastCycleULState())//4
                    .arg(ptr->lastCycleDLState())//5
                    .arg(ptr->trendULState())//6
                    .arg(ptr->trendDLState())//7
                    .arg(ptr->isMonitor())//8
                    .arg(ptr->dataRef());//9
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }
            iter++;
        }
        bSucc = query.exec("COMMIT");
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }
    return bSucc;
}

bool DBEarlyWarningDAO::doUpdate(const QString &dataRef, int type, int dataValue)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = " ";
        switch (type)
        {
            case 0:{
                sql = QObject::tr("UPDATE earlywarning SET UPLIMITSTATEENABLE=%1 WHERE DATAREF=%2")
                        .arg(dataValue)
                        .arg(dataRef);
                break;
            }
            case 1:
            {
                sql = QObject::tr("UPDATE earlywarning SET DOWNLIMITSTATEENABLE=%1 WHERE DATAREF=%2")
                        .arg(dataValue)
                        .arg(dataRef);
                break;
            }
            case 2:
            {
                sql = QObject::tr("UPDATE earlywarning SET MUTATIONSTATEENABLE=%1 WHERE DATAREF=%2")
                        .arg(dataValue)
                        .arg(dataRef);
                break;
            }
            case 3:
            {
                sql = QObject::tr("UPDATE earlywarning SET LASTCYCLEULSTATEENABLE=%1 WHERE DATAREF=%2")
                        .arg(dataValue)
                        .arg(dataRef);
                break;
            }
            case 4:
            {
                sql = QObject::tr("UPDATE earlywarning SET LASTCYCLEDLSTATEENABLE=%1 WHERE DATAREF=%2")
                        .arg(dataValue)
                        .arg(dataRef);
                break;
            }
            case 5:
            {
                sql = QObject::tr("UPDATE earlywarning SET TRENDULSTATEENABLE=%1 WHERE DATAREF=%2")
                        .arg(dataValue)
                        .arg(dataRef);
                break;
            }
            case 6:
            {
                sql = QObject::tr("UPDATE earlywarning SET TRENDDLSTATEENABLE=%1 WHERE DATAREF=%2")
                        .arg(dataValue)
                        .arg(dataRef);
                break;
            }
            default:
            {
                db.close();
                return bSucc;
            }
        }
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBEarlyWarningDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        bSucc = query.exec("TRUNCATE TABLE earlywarning");
        db.close();
    }

    return bSucc;
}

bool DBEarlyWarningDAO::doClear(QSqlDatabase db)
{
    bool bSucc = false;
    //QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
//    if(db.isOpen() || db.open())
//    {
//        QSqlQuery query(db);
//        bSucc = query.exec("TRUNCATE TABLE earlywarning");
//        db.close();
//    }
    QSqlQuery query(db);
    bSucc = query.exec("TRUNCATE TABLE earlywarning");

    return bSucc;
}
