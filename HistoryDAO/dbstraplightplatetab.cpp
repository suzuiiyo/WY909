#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QVariant>
#include <QString>
#include <QList>
#include <QHash>
#include "dbconnection.h"
#include "strap.h"
#include "dbstraplightplatedao.h"
DBStrapLightPlateTab::DBStrapLightPlateTab()
    : m_connectionName("connectStrapLightPlate")
{

}

DBStrapLightPlateTab::~DBStrapLightPlateTab()
{

}

bool DBStrapLightPlateTab::insert_strapLightPlate(QList<Strap *> &lstStrap)
{
    bool bSucc = false;

    QList<Strap*>::iterator iter = lstStrap.begin();

    QString sql_str = "INSERT INTO straplightplate VALUES";

    int list_size = lstStrap.size();

    QSqlDatabase db = DBConnection::connection(m_connectionName, "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);

        if(list_size <= 1000){
            while(iter < lstStrap.end())
            {
                QString sql_str_tmp = "";

                Strap *&strap = *iter;
                QString iedName = strap->iedName();
                QString dataRef = strap->dataRef();
                QString strName = strap->strName();
                QString strapType = strap->strapType();

                sql_str_tmp += "(NULL,'" + iedName + "','" + dataRef + "','" + strName + "','" + strapType + "')";
                if(iter < lstStrap.end() - 1)
                    sql_str_tmp += ",";
                sql_str += sql_str_tmp;
                iter++;
            }
            QByteArray ba = sql_str.toLatin1();
            QString sql = QObject::tr(ba.data());
            bSucc = query.exec(sql);
            if(bSucc == false){
                return false;
            }
        }
        else
        {
            int count = 0;
            while(iter < lstStrap.end())
            {
                QString sql_str_tmp = "";

                Strap *&strap = *iter;
                QString iedName = strap->iedName();
                QString dataRef = strap->dataRef();
                QString strName = strap->strName();
                QString strapType = strap->strapType();

                sql_str_tmp += "(NULL,'" + iedName + "','" + dataRef + "','" + strName + "','" + strapType + "')";
                count++;
                if((count != 0 && count != 1000) && (iter < lstStrap.end() - 1))
                    sql_str_tmp += ",";
                sql_str += sql_str_tmp;
                if(count == 1000)
                {
                    QByteArray ba = sql_str.toLatin1();
                    QString sql = QObject::tr(ba.data());
                    bSucc = query.exec(sql);
                    if(bSucc == false)
                    {
                        db.close();
                        return false;
                    }
                    sql_str = "INSERT INTO straplightplate VALUES";
                    count = 0;
                }
                iter++;
            }
            QByteArray ba = sql_str.toLatin1();
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

QVector<QHash<QString, QString>> DBStrapLightPlateTab::select_strapLightPlate(const QString &iedName)
{
    QVector<QHash<QString, QString>> vecDevOC;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT a.DATAREF, a.STRNAME, a.STRAPTYPE, b.DATAVALUE FROM straplightplate a, tsreal b WHERE IEDNAME = '%1' AND a.DATAREF = b.DATAREF")
                .arg(iedName);

        QSqlQuery query(db);

        if(query.exec(sql))
        {
            while(query.next())
            {
                QHash<QString, QString> hashDevOC;
                QString dataRef = query.value("DATAREF").toString();
                QString strName = query.value("STRNAME").toString();
                QString dataValue = query.value("DATAVALUE").toString();
                QString strapType = query.value("STRAPTYPE").toString();
                hashDevOC.insert("dataRef", dataRef);
                hashDevOC.insert("strName", strName);
                hashDevOC.insert("dataValue", dataValue);
                hashDevOC.insert("strapType", strapType);
                vecDevOC.append(hashDevOC);
            }
            QHash<QString, QString> hashIedName;
            hashIedName.insert("iedName", iedName);
            vecDevOC.append(hashIedName);
            db.close();
        }
    }
    return vecDevOC;
}
