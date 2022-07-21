#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QDebug>
#include "dbconnectionreal.h"
#include "dbtransienttaskrecorddao.h"
DBTransientTaskRecordDAO::DBTransientTaskRecordDAO()
    : m_connectionName("connectTransientTaskRecord")
{

}

DBTransientTaskRecordDAO::~DBTransientTaskRecordDAO()
{

}

TransientTaskRecord::List DBTransientTaskRecordDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    TransientTaskRecord::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM transienttaskrecord");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_iedCateGory1 = query.value("IEDCATEGORY1").toString();
                ptr->m_waveFile1 = query.value("WAVEFILE1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_iedCateGory2 = query.value("IEDCATEGORY2").toString();
                ptr->m_waveFile2 = query.value("WAVEFILE2").toString();
                ptr->m_taskState = query.value("TASKSTATE").toInt();
                ptr->m_taskRequestTime = query.value("TASKREQUESTTIME").toString();
                ptr->m_taskRespondTime = query.value("TASKRESPONDTIME").toString();
                ptr->m_taskResult = query.value("TASKRESULT").toString();
                ptr->m_taskDataFileName = query.value("TASKDATAFILENAME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TransientTaskRecord::List DBTransientTaskRecordDAO::doQuery(int taskState, bool *ok)
{
    bool bSucc = false;
    TransientTaskRecord::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM transienttaskrecord WHERE TASKSTATE=%1")
                .arg(taskState);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_iedCateGory1 = query.value("IEDCATEGORY1").toString();
                ptr->m_waveFile1 = query.value("WAVEFILE1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_iedCateGory2 = query.value("IEDCATEGORY2").toString();
                ptr->m_waveFile2 = query.value("WAVEFILE2").toString();
                ptr->m_taskState = query.value("TASKSTATE").toInt();
                ptr->m_taskRequestTime = query.value("TASKREQUESTTIME").toString();
                ptr->m_taskRespondTime = query.value("TASKRESPONDTIME").toString();
                ptr->m_taskResult = query.value("TASKRESULT").toString();
                ptr->m_taskDataFileName = query.value("TASKDATAFILENAME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TransientTaskRecord::List DBTransientTaskRecordDAO::doQueryByIedName(const QString &iedName, int taskState, bool *ok)
{
    bool bSucc = false;
    TransientTaskRecord::List lst;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM transienttaskrecord WHERE (IEDNAME1='%1' AND TASKSTATE=%2) OR (IEDNAME2='%3' AND TASKSTATE=%4)")
                .arg(iedName)
                .arg(taskState)
                .arg(iedName)
                .arg(taskState);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
                ptr->m_iedName1 = query.value("IEDNAME1").toString();
                ptr->m_iedCateGory1 = query.value("IEDCATEGORY1").toString();
                ptr->m_waveFile1 = query.value("WAVEFILE1").toString();
                ptr->m_iedName2 = query.value("IEDNAME2").toString();
                ptr->m_iedCateGory2 = query.value("IEDCATEGORY2").toString();
                ptr->m_waveFile2 = query.value("WAVEFILE2").toString();
                ptr->m_taskState = query.value("TASKSTATE").toInt();
                ptr->m_taskRequestTime = query.value("TASKREQUESTTIME").toString();
                ptr->m_taskRespondTime = query.value("TASKRESPONDTIME").toString();
                ptr->m_taskResult = query.value("TASKRESULT").toString();
                ptr->m_taskDataFileName = query.value("TASKDATAFILENAME").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

//TransientTaskRecord::List DBTransientTaskRecordDAO::doQueryBySRIedName(const QString &srIedName, int taskState)
//{
//    TransientTaskRecord::List lst;
//    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
//    if (db.isOpen() || db.open())
//    {
//        QSqlQuery query(db);
//        QString sql = QObject::tr("SELECT * FROM transienttaskrecord WHERE SRIEDNAME='%1' AND TASKSTATE=%2")
//                .arg(srIedName)
//                .arg(taskState);
//        if(query.exec(sql))
//        {
//            while(query.next())
//            {
//                TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
//                ptr->m_iedName1 = query.value("IEDNAME1").toString();
//                ptr->m_iedCateGory1 = query.value("IEDCATEGORY1").toString();
//                ptr->m_waveFile1 = query.value("WAVEFILE1").toString();
//                ptr->m_iedName2 = query.value("IEDNAME2").toString();
//                ptr->m_iedCateGory2 = query.value("IEDCATEGORY2").toString();
//                ptr->m_waveFile2 = query.value("WAVEFILE2").toString();
//                ptr->m_taskState = query.value("TASKSTATE").toInt();
//                ptr->m_taskRequestTime = query.value("TASKREQUESTTIME").toString();
//                ptr->m_taskRespondTime = query.value("TASKRESPONDTIME").toString();
//                ptr->m_taskResult = query.value("TASKRESULT").toString();
//                ptr->m_taskDataFileName = query.value("TASKDATAFILENAME").toString();
//                lst.append(ptr);
//            }
//        }
//        db.close();
//    }

//    return lst;
//}



TransientTaskRecord::List DBTransientTaskRecordDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    TransientTaskRecord::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM transienttaskrecord");
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_iedCateGory1 = query.value("IEDCATEGORY1").toString();
            ptr->m_waveFile1 = query.value("WAVEFILE1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_iedCateGory2 = query.value("IEDCATEGORY2").toString();
            ptr->m_waveFile2 = query.value("WAVEFILE2").toString();
            ptr->m_taskState = query.value("TASKSTATE").toInt();
            ptr->m_taskRequestTime = query.value("TASKREQUESTTIME").toString();
            ptr->m_taskRespondTime = query.value("TASKRESPONDTIME").toString();
            ptr->m_taskResult = query.value("TASKRESULT").toString();
            ptr->m_taskDataFileName = query.value("TASKDATAFILENAME").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TransientTaskRecord::List DBTransientTaskRecordDAO::doQuery(QSqlDatabase db, int taskState, bool *ok)
{
    bool bSucc = false;
    TransientTaskRecord::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM transienttaskrecord WHERE TASKSTATE=%1")
            .arg(taskState);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_iedCateGory1 = query.value("IEDCATEGORY1").toString();
            ptr->m_waveFile1 = query.value("WAVEFILE1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_iedCateGory2 = query.value("IEDCATEGORY2").toString();
            ptr->m_waveFile2 = query.value("WAVEFILE2").toString();
            ptr->m_taskState = query.value("TASKSTATE").toInt();
            ptr->m_taskRequestTime = query.value("TASKREQUESTTIME").toString();
            ptr->m_taskRespondTime = query.value("TASKRESPONDTIME").toString();
            ptr->m_taskResult = query.value("TASKRESULT").toString();
            ptr->m_taskDataFileName = query.value("TASKDATAFILENAME").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

TransientTaskRecord::List DBTransientTaskRecordDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, int taskState, bool *ok)
{
    bool bSucc = false;
    TransientTaskRecord::List lst;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM transienttaskrecord WHERE (IEDNAME1='%1' AND TASKSTATE=%2) OR (IEDNAME2='%3' AND TASKSTATE=%4)")
            .arg(iedName)
            .arg(taskState)
            .arg(iedName)
            .arg(taskState);
    bSucc = query.exec(sql);
    if(bSucc)
    {
        while(query.next())
        {
            TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
            ptr->m_iedName1 = query.value("IEDNAME1").toString();
            ptr->m_iedCateGory1 = query.value("IEDCATEGORY1").toString();
            ptr->m_waveFile1 = query.value("WAVEFILE1").toString();
            ptr->m_iedName2 = query.value("IEDNAME2").toString();
            ptr->m_iedCateGory2 = query.value("IEDCATEGORY2").toString();
            ptr->m_waveFile2 = query.value("WAVEFILE2").toString();
            ptr->m_taskState = query.value("TASKSTATE").toInt();
            ptr->m_taskRequestTime = query.value("TASKREQUESTTIME").toString();
            ptr->m_taskRespondTime = query.value("TASKRESPONDTIME").toString();
            ptr->m_taskResult = query.value("TASKRESULT").toString();
            ptr->m_taskDataFileName = query.value("TASKDATAFILENAME").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

//TransientTaskRecord::List DBTransientTaskRecordDAO::doQueryBySRIedName(QSqlDatabase db, const QString &srIedName, int taskState)
//{
//    TransientTaskRecord::List lst;
//    QSqlQuery query(db);
//    QString sql = QObject::tr("SELECT * FROM transienttaskrecord WHERE SRIEDNAME='%1' AND TASKSTATE=%2")
//            .arg(srIedName)
//            .arg(taskState);
//    if(query.exec(sql))
//    {
//        while(query.next())
//        {
//            TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
//            ptr->m_iedName1 = query.value("IEDNAME1").toString();
//            ptr->m_iedCateGory1 = query.value("IEDCATEGORY1").toString();
//            ptr->m_waveFile1 = query.value("WAVEFILE1").toString();
//            ptr->m_iedName2 = query.value("IEDNAME2").toString();
//            ptr->m_iedCateGory2 = query.value("IEDCATEGORY2").toString();
//            ptr->m_waveFile2 = query.value("WAVEFILE2").toString();
//            ptr->m_taskState = query.value("TASKSTATE").toInt();
//            ptr->m_taskRequestTime = query.value("TASKREQUESTTIME").toString();
//            ptr->m_taskRespondTime = query.value("TASKRESPONDTIME").toString();
//            ptr->m_taskResult = query.value("TASKRESULT").toString();
//            ptr->m_taskDataFileName = query.value("TASKDATAFILENAME").toString();
//            lst.append(ptr);
//        }
//    }

//    return lst;
//}

bool DBTransientTaskRecordDAO::doInsert(TransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        TransientTaskRecord::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
            ptr = *iter;
            sql = QObject::tr("INSERT INTO transienttaskrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', %7, '%8', '', '', '')")
                    .arg(ptr->iedName1())            // 1
                    .arg(ptr->iedCateGory1())        // 2
                    .arg(ptr->waveFile1())           // 3
                    .arg(ptr->iedName2())            // 4
                    .arg(ptr->iedCateGory2())        // 5
                    .arg(ptr->waveFile2())           // 6
                    .arg(ptr->taskState())           // 7
                    .arg(ptr->taskRequestTime());    // 8
            if (!query.exec(sql))
            {
                db.close();
                return false;
            }
            count++;
            if (count == 200)
            {
                bSucc = query.exec("COMMIT");
                query.exec("START TRANSACTION");
                count = 0;
            }
        }
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

bool DBTransientTaskRecordDAO::doInsert(QSqlDatabase db, TransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    TransientTaskRecord::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
        ptr = *iter;
        sql = QObject::tr("INSERT INTO transienttaskrecord VALUES(NULL, '%1', '%2', '%3', '%4', '%5', '%6', %7, '%8', '', '', '')")
                .arg(ptr->iedName1())            // 1
                .arg(ptr->iedCateGory1())        // 2
                .arg(ptr->waveFile1())           // 3
                .arg(ptr->iedName2())            // 4
                .arg(ptr->iedCateGory2())        // 5
                .arg(ptr->waveFile2())           // 6
                .arg(ptr->taskState())           // 7
                .arg(ptr->taskRequestTime());    // 8
        if (!query.exec(sql))
        {
            db.close();
            return false;
        }
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

bool DBTransientTaskRecordDAO::doUpdate(TransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "";
        TransientTaskRecord::List::iterator iter;
        int count = 0;
        for (iter = lst.begin(); iter != lst.end(); iter++)
        {
            TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
            ptr = *iter;
            sql = QObject::tr("UPDATE transienttaskrecord SET TASKRESPONDTIME='%1', TASKRESULT='%2', TASKDATAFILENAME='%3' WHERE GUID=%4")
                    .arg(ptr->taskRespondTime())   // 1
                    .arg(ptr->taskResult())        // 2
                    .arg(ptr->taskDataFileName())  // 3
                    .arg(ptr->GUID());             // 4
            if (!query.exec(sql))
            {
                db.close();
                return false;
            }
            count++;
            if (count == 200)
            {
                bSucc = query.exec("COMMIT");
                query.exec("START TRANSACTION");
                count = 0;
            }
        }
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

bool DBTransientTaskRecordDAO::doUpdate(QSqlDatabase db, TransientTaskRecord::List &lst)
{
    bool bSucc = false;
    if (lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "";
    TransientTaskRecord::List::iterator iter;
    int count = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++)
    {
        TransientTaskRecord::Ptr ptr(new TransientTaskRecord());
        ptr = *iter;
        sql = QObject::tr("UPDATE transienttaskrecord SET TASKRESPONDTIME='%1', TASKRESULT='%2', TASKDATAFILENAME='%3' WHERE GUID=%4")
                .arg(ptr->taskRespondTime())   // 1
                .arg(ptr->taskResult())        // 2
                .arg(ptr->taskDataFileName())  // 3
                .arg(ptr->GUID());             // 4
        if (!query.exec(sql))
        {
            db.close();
            return false;
        }
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
