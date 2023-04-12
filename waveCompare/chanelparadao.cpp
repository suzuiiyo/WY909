#include "chanelparadao.h"
#include <QSet>
#include <QDebug>

ChanelParaDAO::ChanelParaDAO():
    dbInfoFlag(true)
{
}

ChanelParaDAO::~ChanelParaDAO()
{
}

bool ChanelParaDAO::init(const QString dbName)
{
    db = DBConnection::connection(dbName, "QSQLITE", "./config/db/SysConfig.db");
    if(db.isOpen() || db.open()){
        qDebug() << "配置库打开成功";
        return true;
    }else
    {
        qDebug() << "配置库打开失败";
        return false;
    }
}

bool ChanelParaDAO::getDbInfo()
{
    return dbInfoFlag;
}

QList<QStringList> ChanelParaDAO::getComtradeFactor()
{
    QList<QStringList> factorlistList;
    DBTransientTaskTMConfigDAO tmConfigDAO;
    TransientTaskTMConfig::List tmList = tmConfigDAO.doQuery();

    QSet<QString> lineNameSet;
    for(QSharedPointer<TransientTaskTMConfig> var : tmList){
        lineNameSet.insert(var->lineName());
    }

    foreach(const QSharedPointer<TransientTaskTMConfig> &varTm, tmList){
        QStringList factorList;
        foreach(const QString &value, lineNameSet){
            if(varTm->lineName() == value){
                //读取配置表的一行,写入QStringList,一一对应
                QString varName1 = varTm->iedName1();
                if(!varName1.isEmpty()){
                    factorList.append(varName1);
                }else{
                    dbInfoFlag = false;
                }

                QString ref1 = varTm->dataRef1();
                if(!ref1.isEmpty()){
                    factorList.append(ref1);
                }else{
                    dbInfoFlag = false;
                }

                QString ref2 = varTm->dataRef2();
                if(!ref2.isEmpty()){
                    factorList.append(ref2);
                }else{
                    factorList.append("");
                }

                //间隔区分
                QString varBayName = varTm->bayName();
                if(!varBayName.isEmpty()){
                    factorList.append(varBayName);
                }else{
                    dbInfoFlag = false;
                }

                //组别
                QString varItemName = varTm->itemName();
                if(!varItemName.isEmpty()){
                    factorList.append(varItemName);
                }else{
                    dbInfoFlag = false;
                }

                //通道类型
                //V or C
                QString itemType = varTm->itemType();
                if(!itemType.isEmpty()){
                    factorList.append(itemType);
                }else{
                    dbInfoFlag = false;
                }

                QString desc1 = varTm->dataDesc1();
                if(!desc1.isEmpty()){
                    factorList.append(desc1);
                }else{
                    dbInfoFlag = false;
                }

                QString phase = varTm->phase();
                if(!phase.isEmpty()){
                    factorList.append(phase);
                }else{
                    dbInfoFlag = false;
                }

                //套别
                QString setType = varTm->setType();
                if(!setType.isEmpty()){
                    factorList.append(setType);
                }else{
                    dbInfoFlag = false;
                }
            }
        }
        factorlistList.append(factorList);
    }
    return  factorlistList;
}

QString ChanelParaDAO::getStationName()
{
    DBStationInfoDAO stationInfoDAO;
    StationInfo::List stationList = stationInfoDAO.doQuery();
    QString stationScheduleName = stationList.at(0)->scheduleName();
    return stationScheduleName;
}

QString ChanelParaDAO::getBayName(const QString& varIedName)
{
    DBIedInfoDAO iedInfoDAO;
    Ied::List iedList = iedInfoDAO.doQuery();

    QString bayId;
    foreach(const QSharedPointer<Ied> &varIed, iedList){
       if(varIedName == varIed->iedName()){
          bayId = varIed->bayName();
       }
    }

    DBBayInfoDAO bayInfoDAO;
    BayInfo::Ptr varBay = bayInfoDAO.doQuery(bayId);
    QString bayScheduleName;
    if(!varBay.isNull()){
        bayScheduleName = varBay->scheduleName();
    }else{
        bayScheduleName = "";
    }

    return bayScheduleName;
}

QList<QStringList> ChanelParaDAO::getIedInfoList()
{
    QList<QStringList> iedInfolistList;
    DBIedInfoDAO iedInfoDAO;
    Ied::List iedList = iedInfoDAO.doQuery();

    QSet<QString> iedInfoSet;
    for(QSharedPointer<Ied> var : iedList){
        iedInfoSet.insert(var->iedName());
    }

    foreach(const QSharedPointer<Ied> &varIed, iedList){
        QStringList iedDescList;
        foreach(const QString &value, iedInfoSet){
           if(value == varIed->iedName()){
              QString varIedDesc = varIed->iedDesc();
              if(!varIedDesc.isEmpty()){
                 iedDescList << value
                             << varIedDesc;
              }else{
                 iedDescList << value
                             << "";
              }
           }
        }
        iedInfolistList.append(iedDescList);
    }
    return iedInfolistList;
}

QStringList ChanelParaDAO::getIedInfo(const QString& varIedName)
{
    QStringList iedInfoList;
    DBIedInfoDAO iedInfoDAO;
    Ied::List iedList = iedInfoDAO.doQuery();

    foreach(const QSharedPointer<Ied> &varIed, iedList){
        if(varIedName == varIed->iedName()){
          QString varIedDesc = varIed->iedDesc();
          QString varIedNameComp = varIed->iedNameComp();
          if(!varIedNameComp.isEmpty()){
                iedInfoList << varIedName
                            << varIedDesc
                            << varIedNameComp;
             }else if(varIedNameComp.isEmpty()){
                iedInfoList << varIedName
                            << varIedDesc
                            << "";
             }
        }
    }
    return iedInfoList;
}

QList<QStringList> ChanelParaDAO::getSwitchComtradeFactor()
{
    QList<QStringList> factorlistList;
    DBTransientTaskTSConfigDAO tsConfigDAO;
    TransientTaskTSConfig::List tsList = tsConfigDAO.doQuery();

    QSet<QString> lineNameSet;
    for(QSharedPointer<TransientTaskTSConfig> var : tsList){
        lineNameSet.insert(var->lineName());
    }

    foreach(const QSharedPointer<TransientTaskTSConfig> &varTs, tsList){
        QStringList factorList;
        foreach (const QString &value, lineNameSet) {
            if(varTs->lineName() == value){
                //读取开关量配置表的一行,写入QStringList,一一对应
                QString varName1 = varTs->iedName1();
                if(!varName1.isEmpty()){
                    factorList.append(varName1);
                }else{
                    dbInfoFlag = false;
                }

                QString ref1 = varTs->dataRef1();
                if(!ref1.isEmpty()){
                    factorList.append(ref1);
                }else{
                    dbInfoFlag = false;
                }

                //间隔区分
                QString varBayName = varTs->bayName();
                if(!varBayName.isEmpty()){
                    factorList.append(varBayName);
                }else{
                    dbInfoFlag = false;
                }

                //组别
                QString varItemName = varTs->itemName();
                if(!varItemName.isEmpty()){
                    factorList.append(varItemName);
                }else{
                    dbInfoFlag = false;
                }

                //V or C
                QString itemType = varTs->itemType();
                if(!itemType.isEmpty()){
                    factorList.append(itemType);
                }else{
                    dbInfoFlag = false;
                }

                QString desc1 = varTs->dataDesc1();
                if(!desc1.isEmpty()){
                    factorList.append(desc1);
                }else{
                    dbInfoFlag = false;
                }

                QString phase = varTs->phase();
                if(!phase.isEmpty()){
                    factorList.append(phase);
                }else{
                    dbInfoFlag = false;
                }

                //套别
                QString setType = varTs->setType();
                if(!setType.isEmpty()){
                    factorList.append(setType);
                }else{
                    dbInfoFlag = false;
                }
            }
        }
        factorlistList.append(factorList);
    }
    return factorlistList;
}
