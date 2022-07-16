#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include "dbdiagnosisofprotoperaterecorddao.h"
#include "dbconnectionreal.h"
DBDiagnosisOfProtOperateRecordDAO::DBDiagnosisOfProtOperateRecordDAO()
    : m_connectionName("connectDOPORecord")
{

}

DBDiagnosisOfProtOperateRecordDAO::~DBDiagnosisOfProtOperateRecordDAO()
{

}

int DBDiagnosisOfProtOperateRecordDAO::countRecord(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc = false;
    int count = 0;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->ackTip() != -1)
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM diagnosisofprotoperaterecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime())
                            .arg(ptr->ackTip());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' AND ACKTIP=%2")
                            .arg(ptr->iedName())
                            .arg(ptr->ackTip());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM diagnosisofprotoperaterecord WHERE ACKTIP=%1")
                            .arg(ptr->ackTip());
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3'")
                            .arg(ptr->iedName())
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM diagnosisofprotoperaterecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2'")
                            .arg(ptr->startTime())
                            .arg(ptr->endTime());
            }
            else
            {
                if(ptr->iedName() != "")
                    sql = QObject::tr("SELECT count(*) as ct FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1'")
                            .arg(ptr->iedName());
                else
                    sql = QObject::tr("SELECT count(*) as ct FROM diagnosisofprotoperaterecord");
            }
        }
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while (query.next())
            {
                count = query.value("ct").toInt();
                if(ok)
                    *ok = bSucc;
                db.close();
                return count;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return count;
}

DiagnosisOfProtOperateRecord::List DBDiagnosisOfProtOperateRecordDAO::doQuery(const SearchCondition::Ptr &ptr, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = true;
    DiagnosisOfProtOperateRecord::List lst_act;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if (db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        if(ptr->ackTip() != -1)
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC LIMIT %5, %6")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' AND ACKTIP=%4 ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' AND ACKTIP=%3 ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->ackTip());
                }
            }
            else
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->iedName())
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' AND ACKTIP=%2 ORDER BY GUID DESC")
                                .arg(ptr->iedName())
                                .arg(ptr->ackTip());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE ACKTIP=%1 ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->ackTip())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE ACKTIP=%1 ORDER BY GUID DESC")
                                .arg(ptr->ackTip());
                }
            }
        }
        else
        {
            if(ptr->startTime() != "" && ptr->endTime() != "")
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC LIMIT %4, %5")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' AND RECORDTIME >= '%2' AND RECORDTIME <= '%3' ORDER BY GUID DESC")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC LIMIT %3, %4")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE RECORDTIME >= '%1' AND RECORDTIME <= '%2' ORDER BY GUID DESC")
                                    .arg(ptr->startTime())
                                    .arg(ptr->endTime());
                }
            }
            else
            {
                if(ptr->iedName() != "")
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' ORDER BY GUID DESC LIMIT %2, %3")
                                    .arg(ptr->iedName())
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord WHERE IEDNAME='%1' ORDER BY GUID DESC")
                                .arg(ptr->iedName());
                }
                else
                {
                    if(ptr->startCount() > 0 && ptr->recordCount() > 0)
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord ORDER BY GUID DESC LIMIT %1, %2")
                                    .arg(ptr->startCount())
                                    .arg(ptr->recordCount());
                    else
                        sql = QObject::tr("SELECT * FROM diagnosisofprotoperaterecord ORDER BY GUID DESC");
                }
            }
        }
        if(sql != "")
        {
            bSucc1 = query.exec(sql);
            if (bSucc1)
            {
                while (query.next())
                {
                    DiagnosisOfProtOperateRecord::Ptr ptrDi(new DiagnosisOfProtOperateRecord());
                    ptrDi->m_GUID = query.value("GUID").toInt();
                    ptrDi->m_iedName = query.value("IEDNAME").toString();
                    ptrDi->m_opType = query.value("OPTYPE").toString();
                    ptrDi->m_conclusion = query.value("CONCLUSION").toString();
                    ptrDi->m_recordTime = query.value("RECORDTIME").toString();
                    ptrDi->m_criterion = query.value("CRITERION").toString();
                    ptrDi->m_process = query.value("PROCESS").toString();
                    ptrDi->m_iedNameComp = query.value("IEDNAMECOMP").toString();
                    ptrDi->m_isConsistent = query.value("ISCONSISTENT").toString();
                    ptrDi->m_relationIed = query.value("RELATIONIED").toString();
                    ptrDi->m_nonAnticipatoryOp = query.value("NONANTICIPATORYOP").toString();
                    ptrDi->m_anticipatoryOp = query.value("ANTICIPATORYOP").toString();
                    ptrDi->m_ackTip = query.value("ACKTIP").toInt();
                    lst_act.append(ptrDi);
                }
            }
            else
                bSucc2 = bSucc1;
        }
        db.close();
    }

    if(ok)
        *ok = bSucc2;

    return lst_act;
}

bool DBDiagnosisOfProtOperateRecordDAO::ackRecord(DiagnosisOfProtOperateRecord::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    DiagnosisOfProtOperateRecord::List::iterator iter;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            DiagnosisOfProtOperateRecord::Ptr ptr(new DiagnosisOfProtOperateRecord());
            ptr = *iter;

            QString sql = QObject::tr("UPDATE diagnosisofprotoperaterecord SET ACKTIP=%1 WHERE GUID=%2")
                    .arg(ptr->ackTip())
                    .arg(ptr->GUID());
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }
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

bool DBDiagnosisOfProtOperateRecordDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS diagnosisofprotoperaterecord("
                                  "GUID INT(11) NOT NULL AUTO_INCREMENT,"
                                  "IEDNAME VARCHAR(255) NOT NULL,"
                                  "OPTYPE VARCHAR(255) NOT NULL,"
                                  "CONCLUSION VARCHAR(255) DEFAULT NULL,"
                                  "RECORDTIME VARCHAR(255) DEFAULT NULL,"
                                  "CRITERION JSON,"
                                  "PROCESS JSON,"
                                  "IEDNAMECOMP VARCHAR(255) DEFAULT NULL,"
                                  "ISCONSISTENT VARCHAR(255) DEFAULT NULL,"
                                  "RELATIONIED VARCHAR(255) DEFAULT NULL,"
                                  "NONANTICIPATORYOP JSON,"
                                  "ANTICIPATORYOP JSON,"
                                  "ACKTIP INT(11) NOT NULL DEFAULT 0,"
                                  "PRIMARY KEY(GUID))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}
