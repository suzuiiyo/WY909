#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QVariant>
#include "ackrecord.h"
#include "dbconnectionreal.h"
AckRecord::AckRecord()
    : m_connectionName("connectAckRecord")
{

}

AckRecord::~AckRecord()
{

}

bool AckRecord::ackRecord(int type)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString tableName = "";
        switch (type)
        {
            case 0:
            {
                tableName = "transienttaskconclusionrecord";
                break;
            }
            case 1:
            {
                tableName = "earlywarningrecord";
                break;
            }
            case 2:
            {
                tableName = "devnoncorrespondingrecord";
                break;
            }
            case 3:
            {
                tableName = "diagnosisofprotoperaterecord";
                break;
            }
            case 4:
            {
                tableName = "looplinkalarmrecord";
                break;
            }
            case 5:
            {
                tableName = "loopportalarmrecord";
                break;
            }
            case 6:
            {
                tableName = "connectionhistory";
                break;
            }
            case 7:
            {
                tableName = "steadytasktmrecord";
                break;
            }
            case 8:
            {
                tableName = "steadytasktsrecord";
                break;
            }
            case 9:
            {
                tableName = "crcfiletaskrecord";
                break;
            }
            case 10:
            {
                tableName = "timesynrecord";
                break;
            }
            default:
                break;
        }
        if(tableName != "")
        {
            QString sql = QObject::tr("UPDATE %1 SET ACKTIP=1 WHERE ACKTIP=0")
                    .arg(tableName);
            bSucc = query.exec(sql);
        }
        db.close();
    }

    return bSucc;
}

bool AckRecord::ackRecord(int type, QList<int> &lst)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString tableName = "";
        switch (type)
        {
            case 0:
            {
                tableName = "transienttaskconclusionrecord";
                break;
            }
            case 1:
            {
                tableName = "earlywarningrecord";
                break;
            }
            case 2:
            {
                tableName = "devnoncorrespondingrecord";
                break;
            }
            case 3:
            {
                tableName = "diagnosisofprotoperaterecord";
                break;
            }
            case 4:
            {
                tableName = "looplinkalarmrecord";
                break;
            }
            case 5:
            {
                tableName = "loopportalarmrecord";
                break;
            }
            case 6:
            {
                tableName = "connectionhistory";
                break;
            }
            case 7:
            {
                tableName = "steadytasktmrecord";
                break;
            }
            case 8:
            {
                tableName = "steadytasktsrecord";
                break;
            }
            case 9:
            {
                tableName = "crcfiletaskrecord";
                break;
            }
            case 10:
            {
                tableName = "timesynrecord";
                break;
            }
            default:
                break;
        }
        if(tableName != "")
        {
            QString sql = "";
            query.exec("BEGIN");
            for(int i = 0; i < lst.size(); i++)
            {
                sql = QObject::tr("UPDATE %1 SET ACKTIP=1 WHERE GUID=%2")
                        .arg(tableName)
                        .arg(lst.at(i));
                if(!query.exec(sql))
                    return bSucc;
            }
            bSucc = query.exec("COMMIT");
        }
        db.close();
    }

    return bSucc;
}
