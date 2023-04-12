#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "realdata.h"
//#include "ieddataset.h"
//#include "dbieddatasetdao.h"
#include "dbconnectionreal.h"
#include "dbrealdatadao.h"
DBRealDataDAO::DBRealDataDAO()
    : m_connectionName("connectRealData")
{

}

DBRealDataDAO::~DBRealDataDAO()
{

}

RealData::Hash DBRealDataDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    RealData::Hash hsh;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM realdata");
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            RealData::Ptr ptr(new RealData());
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_quality = query.value("QUALITY").toString();
            ptr->m_updateTime = query.value("UPDATETIME").toString();
            ptr->m_business = query.value("BUSINESS").toString();
            QString dataRef = ptr->dataRef();
            int dataType1 = query.value("DATATYPE1").toInt();
            QString dataValue1 = query.value("DATAVALUE1").toString();
            int dataType2 = query.value("DATATYPE2").toInt();
            QString dataValue2 = query.value("DATAVALUE2").toString();
            int dataType3 = query.value("DATATYPE3").toInt();
            QString dataValue3 = query.value("DATAVALUE3").toString();
            int dataType4 = query.value("DATATYPE4").toInt();
            QString dataValue4 = query.value("DATAVALUE4").toString();
            int dataType5 = query.value("DATATYPE5").toInt();
            QString dataValue5 = query.value("DATAVALUE5").toString();

            if(dataValue1.size() != 0)
            {
                ptr->addDataType(dataType1);
                ptr->addDataValue(dataValue1);
                if(dataValue2.size() != 0)
                {
                    ptr->addDataType(dataType2);
                    ptr->addDataValue(dataValue2);
                    if(dataValue3.size() != 0)
                    {
                        ptr->addDataType(dataType3);
                        ptr->addDataValue(dataValue3);
                        if(dataValue4.size() != 0)
                        {
                            ptr->addDataType(dataType4);
                            ptr->addDataValue(dataValue4);
                            if(dataValue5.size() != 0)
                            {
                                ptr->addDataType(dataType5);
                                ptr->addDataValue(dataValue5);
                            }
                        }
                    }
                }
            }

            if(!hsh.contains(dataRef))
                hsh.insert(dataRef, ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return hsh;
}

RealData::Hash DBRealDataDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    RealData::Hash hsh;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM realdata");
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                RealData::Ptr ptr(new RealData());
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_quality = query.value("QUALITY").toString();
                ptr->m_updateTime = query.value("UPDATETIME").toString();
                ptr->m_business = query.value("BUSINESS").toString();
                QString dataRef = ptr->dataRef();
                int dataType1 = query.value("DATATYPE1").toInt();
                QString dataValue1 = query.value("DATAVALUE1").toString();
                int dataType2 = query.value("DATATYPE2").toInt();
                QString dataValue2 = query.value("DATAVALUE2").toString();
                int dataType3 = query.value("DATATYPE3").toInt();
                QString dataValue3 = query.value("DATAVALUE3").toString();
                int dataType4 = query.value("DATATYPE4").toInt();
                QString dataValue4 = query.value("DATAVALUE4").toString();
                int dataType5 = query.value("DATATYPE5").toInt();
                QString dataValue5 = query.value("DATAVALUE5").toString();

                if(dataValue1.size() != 0)
                {
                    ptr->addDataType(dataType1);
                    ptr->addDataValue(dataValue1);
                    if(dataValue2.size() != 0)
                    {
                        ptr->addDataType(dataType2);
                        ptr->addDataValue(dataValue2);
                        if(dataValue3.size() != 0)
                        {
                            ptr->addDataType(dataType3);
                            ptr->addDataValue(dataValue3);
                            if(dataValue4.size() != 0)
                            {
                                ptr->addDataType(dataType4);
                                ptr->addDataValue(dataValue4);
                                if(dataValue5.size() != 0)
                                {
                                    ptr->addDataType(dataType5);
                                    ptr->addDataValue(dataValue5);
                                }
                            }
                        }
                    }
                }

                if(!hsh.contains(dataRef))
                    hsh.insert(dataRef, ptr);
            }
        }
    }
    db.close();
    if(ok)
        *ok = bSucc;

    return hsh;
}

RealData::Ptr DBRealDataDAO::doQuery(const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("SELECT * FROM realdata WHERE DATAREF='%1'")
                .arg(dataRef);
        query.setForwardOnly(true);
        bSucc = query.exec(sql);
        if (bSucc)
        {
            while(query.next())
            {
                RealData::Ptr ptr(new RealData());
                ptr->m_dataRef = query.value("DATAREF").toString();
                ptr->m_iedName = query.value("IEDNAME").toString();
                ptr->m_quality = query.value("QUALITY").toString();
                ptr->m_updateTime = query.value("UPDATETIME").toString();
                ptr->m_business = query.value("BUSINESS").toString();
                int dataType1 = query.value("DATATYPE1").toInt();
                QString dataValue1 = query.value("DATAVALUE1").toString();
                int dataType2 = query.value("DATATYPE2").toInt();
                QString dataValue2 = query.value("DATAVALUE2").toString();
                int dataType3 = query.value("DATATYPE3").toInt();
                QString dataValue3 = query.value("DATAVALUE3").toString();
                int dataType4 = query.value("DATATYPE4").toInt();
                QString dataValue4 = query.value("DATAVALUE4").toString();
                int dataType5 = query.value("DATATYPE5").toInt();
                QString dataValue5 = query.value("DATAVALUE5").toString();
                if(dataValue1.size() != 0)
                {
                    ptr->addDataType(dataType1);
                    ptr->addDataValue(dataValue1);
                    if(dataValue2.size() != 0)
                    {
                        ptr->addDataType(dataType2);
                        ptr->addDataValue(dataValue2);
                        if(dataValue3.size() != 0)
                        {
                            ptr->addDataType(dataType3);
                            ptr->addDataValue(dataValue3);
                            if(dataValue4.size() != 0)
                            {
                                ptr->addDataType(dataType4);
                                ptr->addDataValue(dataValue4);
                                if(dataValue5.size() != 0)
                                {
                                    ptr->addDataType(dataType5);
                                    ptr->addDataValue(dataValue5);
                                }
                            }
                        }
                    }
                }
                if(ok)
                    *ok = bSucc;
                db.close();
                return ptr;
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return NULL;
}

RealData::Ptr DBRealDataDAO::doQuery(QSqlDatabase db, const QString &dataRef, bool *ok)
{
    bool bSucc = false;
    QSqlQuery query(db);
    QString sql = QObject::tr("SELECT * FROM realdata WHERE DATAREF='%1'")
            .arg(dataRef);
    bSucc = query.exec(sql);
    if (bSucc)
    {
        while(query.next())
        {
            RealData::Ptr ptr(new RealData());
            ptr->m_dataRef = query.value("DATAREF").toString();
            ptr->m_iedName = query.value("IEDNAME").toString();
            ptr->m_quality = query.value("QUALITY").toString();
            ptr->m_updateTime = query.value("UPDATETIME").toString();
            ptr->m_business = query.value("BUSINESS").toString();
            int dataType1 = query.value("DATATYPE1").toInt();
            QString dataValue1 = query.value("DATAVALUE1").toString();
            int dataType2 = query.value("DATATYPE2").toInt();
            QString dataValue2 = query.value("DATAVALUE2").toString();
            int dataType3 = query.value("DATATYPE3").toInt();
            QString dataValue3 = query.value("DATAVALUE3").toString();
            int dataType4 = query.value("DATATYPE4").toInt();
            QString dataValue4 = query.value("DATAVALUE4").toString();
            int dataType5 = query.value("DATATYPE5").toInt();
            QString dataValue5 = query.value("DATAVALUE5").toString();
            if(dataValue1.size() != 0)
            {
                ptr->addDataType(dataType1);
                ptr->addDataValue(dataValue1);
                if(dataValue2.size() != 0)
                {
                    ptr->addDataType(dataType2);
                    ptr->addDataValue(dataValue2);
                    if(dataValue3.size() != 0)
                    {
                        ptr->addDataType(dataType3);
                        ptr->addDataValue(dataValue3);
                        if(dataValue4.size() != 0)
                        {
                            ptr->addDataType(dataType4);
                            ptr->addDataValue(dataValue4);
                            if(dataValue5.size() != 0)
                            {
                                ptr->addDataType(dataType5);
                                ptr->addDataValue(dataValue5);
                            }
                        }
                    }
                }
            }
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

bool DBRealDataDAO::doInsert(RealData::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");
        QString sql = "INSERT INTO realdata VALUES";
        RealData::List::iterator iter;
        int itemCount = 0;
        for(iter=lst.begin(); iter!=lst.end(); iter++)
        {
            RealData::Ptr ptr(new RealData());
            ptr = *iter;
            int dataType1 = 0;
            QString dataValue1 = "";
            int dataType2 = 0;
            QString dataValue2 = "";
            int dataType3 = 0;
            QString dataValue3 = "";
            int dataType4 = 0;
            QString dataValue4 = "";
            int dataType5 = 0;
            QString dataValue5 = "";
            int count1 = 0;
            while(count1<ptr->lstDataType().size())
            {
                switch (count1) {
                case 0:
                {
                    dataType1 = ptr->lstDataType()[0];
                    dataValue1 = ptr->lstDataValue()[0];
                    break;
                }
                case 1:
                {
                    dataType2 = ptr->lstDataType()[1];
                    dataValue2 = ptr->lstDataValue()[1];
                    break;
                }
                case 2:
                {
                    dataType3 = ptr->lstDataType()[2];
                    dataValue3 = ptr->lstDataValue()[2];
                    break;
                }
                case 3:
                {
                    dataType4 = ptr->lstDataType()[3];
                    dataValue4 = ptr->lstDataValue()[3];
                    break;
                }
                case 4:
                {
                    dataType5 = ptr->lstDataType()[4];
                    dataValue5 = ptr->lstDataValue()[4];
                    break;
                }
                default:
                    break;
                }
                count1++;
            }
//            QString quality = ptr->quality();
//            QString updateTime = ptr->updateTime();
//            QString iedName = ptr->iedName();
//            QString dataRef = ptr->dataRef();
//            QString dataDesc = ptr->dataDesc();
//            QString business = ptr->business();
//            sql = QObject::tr("INSERT INTO realdata VALUES(NULL, '%1', '%2', '%3', '%4', '%5', %6, '%7', %8, '%9', %10, '%11', %12, '%13', %14, '%15', '%16')")
//                    .arg(dataRef)//1
//                    .arg(iedName)//2
//                    .arg(dataDesc)//3
//                    .arg(quality)//4
//                    .arg(updateTime)//5
//                    .arg(dataType1)//6
//                    .arg(dataValue1)//7
//                    .arg(dataType2)//8
//                    .arg(dataValue2)//9
//                    .arg(dataType3)//10
//                    .arg(dataValue3)//11
//                    .arg(dataType4)//12
//                    .arg(dataValue4)//13
//                    .arg(dataType5)//14
//                    .arg(dataValue5)//15
//                    .arg(business);//16
            QString quality = ptr->quality();
            QString updateTime = ptr->updateTime();
            QString iedName = ptr->iedName();
            QString dataRef = ptr->dataRef();
            QString dataDesc = ptr->dataDesc();
            QString business = ptr->business();
            QString dataType1Str = QString::number(dataType1);
            QString dataType2Str = QString::number(dataType2);
            QString dataType3Str = QString::number(dataType3);
            QString dataType4Str = QString::number(dataType4);
            QString dataType5Str = QString::number(dataType5);
            sql += "(NULL, '" + dataRef + "', '" + iedName + "', '" + dataDesc + "', '" + quality + "', '" + updateTime + "', " + dataType1Str + ", '" + dataValue1 + "', " + dataType2Str + ", '" + dataValue2 + "', " +dataType3Str + ", '" +dataValue3 + "', " +dataType4Str + ", '" + dataValue4 + "', " +dataType5Str + ", '" + dataValue5 + "', '" + business + "')";
            if(itemCount != 499 && iter!=lst.end()-1)
            {
                sql += ",";
            }
            itemCount++;
            if(itemCount == 500 || iter==lst.end()-1)
            {
                QByteArray ba = sql.toUtf8();
                QString sqlMix = QObject::tr(ba.data());
                if(!query.exec(sqlMix))
                {
                    QString error_s = query.lastError().text();
                    printf("error: %s", error_s.toStdString().data());
                    return false;
                }
                itemCount = 0;
                sql = "INSERT INTO realdata VALUES";
            }
        }
        bSucc = query.exec("COMMIT");
        db.close();
    }

    return bSucc;
}

bool DBRealDataDAO::doInsert(QSqlDatabase db, RealData::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");
    QString sql = "INSERT INTO realdata VALUES";
    RealData::List::iterator iter;
    int itemCount = 0;
    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        RealData::Ptr ptr(new RealData());
        ptr = *iter;
        int dataType1 = 0;
        QString dataValue1 = "";
        int dataType2 = 0;
        QString dataValue2 = "";
        int dataType3 = 0;
        QString dataValue3 = "";
        int dataType4 = 0;
        QString dataValue4 = "";
        int dataType5 = 0;
        QString dataValue5 = "";
        int count1 = 0;
        while(count1<ptr->lstDataType().size())
        {
            switch (count1) {
            case 0:
            {
                dataType1 = ptr->lstDataType()[0];
                dataValue1 = ptr->lstDataValue()[0];
                break;
            }
            case 1:
            {
                dataType2 = ptr->lstDataType()[1];
                dataValue2 = ptr->lstDataValue()[1];
                break;
            }
            case 2:
            {
                dataType3 = ptr->lstDataType()[2];
                dataValue3 = ptr->lstDataValue()[2];
                break;
            }
            case 3:
            {
                dataType4 = ptr->lstDataType()[3];
                dataValue4 = ptr->lstDataValue()[3];
                break;
            }
            case 4:
            {
                dataType5 = ptr->lstDataType()[4];
                dataValue5 = ptr->lstDataValue()[4];
                break;
            }
            default:
                break;
            }
            count1++;
        }
        QString quality = ptr->quality();
        QString updateTime = ptr->updateTime();
        QString iedName = ptr->iedName();
        QString dataRef = ptr->dataRef();
        QString dataDesc = ptr->dataDesc();
        QString business = ptr->business();
        QString dataType1Str = QString::number(dataType1);
        QString dataType2Str = QString::number(dataType2);
        QString dataType3Str = QString::number(dataType3);
        QString dataType4Str = QString::number(dataType4);
        QString dataType5Str = QString::number(dataType5);
        sql += "(NULL, '" + dataRef + "', '" + iedName + "', '" + dataDesc + "', '" + quality + "', '" + updateTime + "', " + dataType1Str + ", '" + dataValue1 + "', " + dataType2Str + ", '" + dataValue2 + "', " +dataType3Str + ", '" +dataValue3 + "', " +dataType4Str + ", '" + dataValue4 + "', " +dataType5Str + ", '" + dataValue5 + "', '" + business + "')";
        if(itemCount != 499 && iter!=lst.end()-1)
        {
            sql += ",";
        }
        itemCount++;
        if(itemCount == 500 || iter==lst.end()-1)
        {
            QByteArray ba = sql.toUtf8();
            QString sqlMix = QObject::tr(ba.data());
            if(!query.exec(sqlMix))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                return false;
            }
            itemCount = 0;
            sql = "INSERT INTO realdata VALUES";
        }
    }
    bSucc = query.exec("COMMIT");

    return bSucc;
}

bool DBRealDataDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS realdata("
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
                                  "UNIQUE KEY UK_realdata_DATAREF(DATAREF))");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}

//bool DBRealDataDAO::doInit()
//{
//    bool bSucc = false;
//    DBIedDataSetDAO dao_dataSet;
//    IedDataSet::List lst_dataSet = dao_dataSet.doQuery();
//    if(lst_dataSet.size() == 0)
//        return bSucc;
//    QHash<QString, int> hsh;
//    RealData::List lst_realData;
//    IedDataSet::List::iterator iter;
//    for(iter=lst_dataSet.begin(); iter!=lst_dataSet.end(); iter++)
//    {
//        IedDataSet::Ptr ptr_dataSet(new IedDataSet());
//        ptr_dataSet = *iter;
//        QString dataRef = ptr_dataSet->dataRef();
//        QString dataDesc = ptr_dataSet->dataDesc();
//        QString iedName = ptr_dataSet->iedName();
//        QString business = ptr_dataSet->business();
//        if(!hsh.contains(dataRef))
//        {
//            RealData::Ptr ptr_realData(new RealData());
//            ptr_realData->setDataRef(dataRef);
//            ptr_realData->setDataDesc(dataDesc);
//            ptr_realData->setIedName(iedName);
//            ptr_realData->setBusiness(business);
//            lst_realData.append(ptr_realData);
//            hsh.insert(dataRef, 1);
//        }
//    }
//    bSucc = doInsert(lst_realData);
//    return bSucc;
//}

//bool DBRealDataDAO::doInit(QSqlDatabase db, QSqlDatabase dbR)
//{
//    bool bSucc = false;
//    DBIedDataSetDAO dao_dataSet;
//    IedDataSet::List lst_dataSet = dao_dataSet.doQuery(db);
//    if(lst_dataSet.size() == 0)
//        return bSucc;
//    QHash<QString, int> hsh;
//    RealData::List lst_realData;
//    IedDataSet::List::iterator iter;
//    for(iter=lst_dataSet.begin(); iter!=lst_dataSet.end(); iter++)
//    {
//        IedDataSet::Ptr ptr_dataSet(new IedDataSet());
//        ptr_dataSet = *iter;
//        QString dataRef = ptr_dataSet->dataRef();
//        QString dataDesc = ptr_dataSet->dataDesc();
//        QString iedName = ptr_dataSet->iedName();
//        QString business = ptr_dataSet->business();
//        if(!hsh.contains(dataRef))
//        {
//            RealData::Ptr ptr_realData(new RealData());
//            ptr_realData->setDataRef(dataRef);
//            ptr_realData->setDataDesc(dataDesc);
//            ptr_realData->setIedName(iedName);
//            ptr_realData->setBusiness(business);
//            lst_realData.append(ptr_realData);
//            hsh.insert(dataRef, 1);
//        }
//    }
//    bSucc = doInsert(dbR, lst_realData);
//    return bSucc;
//}

bool DBRealDataDAO::doUpdate(const RealData::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        int dataType1 = 0;
        QString dataValue1 = "";
        int dataType2 = 0;
        QString dataValue2 = "";
        int dataType3 = 0;
        QString dataValue3 = "";
        int dataType4 = 0;
        QString dataValue4 = "";
        int dataType5 = 0;
        QString dataValue5 = "";
        int count1 = 0;
        while(count1<ptr->lstDataType().size())
        {
            switch (count1) {
            case 0:
            {
                dataType1 = ptr->lstDataType()[0];
                dataValue1 = ptr->lstDataValue()[0];
                break;
            }
            case 1:
            {
                dataType2 = ptr->lstDataType()[1];
                dataValue2 = ptr->lstDataValue()[1];
                break;
            }
            case 2:
            {
                dataType3 = ptr->lstDataType()[2];
                dataValue3 = ptr->lstDataValue()[2];
                break;
            }
            case 3:
            {
                dataType4 = ptr->lstDataType()[3];
                dataValue4 = ptr->lstDataValue()[3];
                break;
            }
            case 4:
            {
                dataType5 = ptr->lstDataType()[4];
                dataValue5 = ptr->lstDataValue()[4];
                break;
            }
            default:
                break;
            }
            count1++;
        }
        QString sql = QObject::tr("UPDATE realdata SET DATAREF='%1', IEDNAME='%2', DATADESC='%3', QUALITY='%4', UPDATETIME='%5', DATATYPE1=%6, DATAVALUE1='%7', DATATYPE2=%8, DATAVALUE2='%9', DATATYPE3=%10, DATAVALUE3='%11', DATATYPE4=%12, DATAVALUE4='%13', DATATYPE5=%14, DATAVALUE5='%15' WHERE GUID=%16")
                .arg(ptr->dataRef())//1
                .arg(ptr->iedName())//2
                .arg(ptr->dataDesc())//3
                .arg(ptr->quality())//4
                .arg(ptr->updateTime())//5
                .arg(dataType1)//6
                .arg(dataValue1)//7
                .arg(dataType2)//8
                .arg(dataValue2)//9
                .arg(dataType3)//10
                .arg(dataValue3)//11
                .arg(dataType4)//12
                .arg(dataValue4)//13
                .arg(dataType5)//14
                .arg(dataValue5)//15
                .arg(ptr->GUID());//16
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBRealDataDAO::doUpdate(RealData::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    RealData::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("START TRANSACTION");

        while(iter < lst.end())
        {
            RealData::Ptr ptr(new RealData());
            ptr = *iter;
            int dataType1 = 0;
            QString dataValue1 = "";
            int dataType2 = 0;
            QString dataValue2 = "";
            int dataType3 = 0;
            QString dataValue3 = "";
            int dataType4 = 0;
            QString dataValue4 = "";
            int dataType5 = 0;
            QString dataValue5 = "";
            int count1 = 0;
            while(count1<ptr->lstDataType().size())
            {
                switch (count1) {
                case 0:
                {
                    dataType1 = ptr->lstDataType()[0];
                    dataValue1 = ptr->lstDataValue()[0];
                    break;
                }
                case 1:
                {
                    dataType2 = ptr->lstDataType()[1];
                    dataValue2 = ptr->lstDataValue()[1];
                    break;
                }
                case 2:
                {
                    dataType3 = ptr->lstDataType()[2];
                    dataValue3 = ptr->lstDataValue()[2];
                    break;
                }
                case 3:
                {
                    dataType4 = ptr->lstDataType()[3];
                    dataValue4 = ptr->lstDataValue()[3];
                    break;
                }
                case 4:
                {
                    dataType5 = ptr->lstDataType()[4];
                    dataValue5 = ptr->lstDataValue()[4];
                    break;
                }
                default:
                    break;
                }
                count1++;
            }
            QString sql = QObject::tr("UPDATE realdata SET QUALITY='%1', UPDATETIME='%2', DATATYPE1=%3, DATAVALUE1='%4', DATATYPE2=%5, DATAVALUE2='%6', DATATYPE3=%7, DATAVALUE3='%8', DATATYPE4=%9, DATAVALUE4='%10', DATATYPE5=%11, DATAVALUE5='%12' WHERE DATAREF='%13'")
                    .arg(ptr->quality())//1
                    .arg(ptr->updateTime())//2
                    .arg(dataType1)//3
                    .arg(dataValue1)//4
                    .arg(dataType2)//5
                    .arg(dataValue2)//6
                    .arg(dataType3)//7
                    .arg(dataValue3)//8
                    .arg(dataType4)//9
                    .arg(dataValue4)//10
                    .arg(dataType5)//11
                    .arg(dataValue5)//12
                    .arg(ptr->dataRef());//13
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

bool DBRealDataDAO::doUpdate(QSqlDatabase db, RealData::List &lst)
{
    bool bSucc = false;
    if(lst.size() == 0)
        return bSucc;
    RealData::List::iterator iter;
    QSqlQuery query(db);
    query.exec("START TRANSACTION");

    for(iter=lst.begin(); iter!=lst.end(); iter++)
    {
        RealData::Ptr ptr(new RealData());
        ptr = *iter;
        int dataType1 = 0;
        QString dataValue1 = "";
        int dataType2 = 0;
        QString dataValue2 = "";
        int dataType3 = 0;
        QString dataValue3 = "";
        int dataType4 = 0;
        QString dataValue4 = "";
        int dataType5 = 0;
        QString dataValue5 = "";
        int count1 = 0;
        while(count1<ptr->lstDataType().size())
        {
            switch (count1) {
            case 0:
            {
                dataType1 = ptr->lstDataType()[0];
                dataValue1 = ptr->lstDataValue()[0];
                break;
            }
            case 1:
            {
                dataType2 = ptr->lstDataType()[1];
                dataValue2 = ptr->lstDataValue()[1];
                break;
            }
            case 2:
            {
                dataType3 = ptr->lstDataType()[2];
                dataValue3 = ptr->lstDataValue()[2];
                break;
            }
            case 3:
            {
                dataType4 = ptr->lstDataType()[3];
                dataValue4 = ptr->lstDataValue()[3];
                break;
            }
            case 4:
            {
                dataType5 = ptr->lstDataType()[4];
                dataValue5 = ptr->lstDataValue()[4];
                break;
            }
            default:
                break;
            }
            count1++;
        }
        QString sql = QObject::tr("UPDATE realdata SET QUALITY='%1', UPDATETIME='%2', DATATYPE1=%3, DATAVALUE1='%4', DATATYPE2=%5, DATAVALUE2='%6', DATATYPE3=%7, DATAVALUE3='%8', DATATYPE4=%9, DATAVALUE4='%10', DATATYPE5=%11, DATAVALUE5='%12' WHERE DATAREF='%13'")
                .arg(ptr->quality())//1
                .arg(ptr->updateTime())//2
                .arg(dataType1)//3
                .arg(dataValue1)//4
                .arg(dataType2)//5
                .arg(dataValue2)//6
                .arg(dataType3)//7
                .arg(dataValue3)//8
                .arg(dataType4)//9
                .arg(dataValue4)//10
                .arg(dataType5)//11
                .arg(dataValue5)//12
                .arg(ptr->dataRef());//13
        if(!query.exec(sql))
        {
//            printf("sql: %s\n", sql.toStdString().data());
//            printf("num: %d update dataRef: %s false...\n", num, ptr->dataRef().toStdString().data());
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
            //db.close();
            return bSucc;
        }
    }
    bSucc = query.exec("COMMIT");
    if(!bSucc){
        QString error_s = query.lastError().text();
        printf("error: %s", error_s.toStdString().data());
    }
    return bSucc;
}

bool DBRealDataDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnectionReal::connection(m_connectionName, "QMYSQL", "mmsdb");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        bSucc = query.exec("TRUNCATE TABLE realdata");
        db.close();
    }

    return bSucc;
}

bool DBRealDataDAO::doClear(QSqlDatabase db)
{
    bool bSucc = false;
    QSqlQuery query(db);
    bSucc = query.exec("TRUNCATE TABLE realdata");

    return bSucc;
}

