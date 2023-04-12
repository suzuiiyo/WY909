#include <QObject>
#include <QString>
//#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QList>
#include "virloopconfig.h"
#include "virloopiedinfo.h"
#include "dbconnection.h"
#include "dbvirloopconfigdao.h"
#include "ied.h"
#include "strap.h"
#include "gooseinfo.h"
#include "gooseinst.h"
#include "optport.h"
#include "fibreoptical.h"
#include "virlooprecvied.h"
#include "virloopsendied.h"
#include "dbiedinfodao.h"
#include "dboptportdao.h"
#include "dbstraplightplatedao.h"
#include "dbgooseinfodao.h"
#include "dbfibreopticaldao.h"
#include "switchdevice.h"
#include "dbdevrunstatedao.h"
DBVirLoopConfigDAO::DBVirLoopConfigDAO()
    : m_connectionName("connectVirLoopConfig")
{

}

DBVirLoopConfigDAO::~DBVirLoopConfigDAO()
{

}

VirLoopConfig::List DBVirLoopConfigDAO::doQuery(bool *ok)
{
    bool bSucc = false;
    VirLoopConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM virloopconfig");
        QSqlQuery query(db);
        bSucc = query.exec(sql);

        if(bSucc)
        {
            while(query.next())
            {
                VirLoopConfig::Ptr ptr(new VirLoopConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_appId = query.value("APPID").toString();
                ptr->m_recvIedName = query.value("RECVIEDNAME").toString();
                ptr->m_recvPortId = query.value("RECVPORTID").toString();
                ptr->m_recvStrapRef = query.value("RECVSTRAPREF").toString();
                ptr->m_gooseInst = query.value("GOOSEINST").toString();
                ptr->m_gooseInstDesc = query.value("GOOSEINSTDESC").toString();
                ptr->m_sendIedName = query.value("SENDIEDNAME").toString();
                ptr->m_sendPortId = query.value("SENDPORTID").toString();
                ptr->m_sendStrapRef = query.value("SENDSTRAPREF").toString();
                ptr->m_gooseRef = query.value("GOOSEREF").toString();
                ptr->m_gooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
                ptr->m_gooseDataExcep = query.value("GOOSEDATAEXCEP").toString();
                ptr->m_phyLink = query.value("PHYLINK").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

VirLoopConfig::List DBVirLoopConfigDAO::doQueryByIedName(const QString &iedName, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = false;
    VirLoopConfig::List lst;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QString sql = QObject::tr("SELECT * FROM virloopconfig WHERE RECVIEDNAME=\"%1\"")
                .arg(iedName);
        QSqlQuery query(db);
        bSucc1 = query.exec(sql);

        if(bSucc1)
        {
            while(query.next())
            {
                VirLoopConfig::Ptr ptr(new VirLoopConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_appId = query.value("APPID").toString();
                ptr->m_recvIedName = query.value("RECVIEDNAME").toString();
                ptr->m_recvPortId = query.value("RECVPORTID").toString();
                ptr->m_recvStrapRef = query.value("RECVSTRAPREF").toString();
                ptr->m_gooseInst = query.value("GOOSEINST").toString();
                ptr->m_gooseInstDesc = query.value("GOOSEINSTDESC").toString();
                ptr->m_sendIedName = query.value("SENDIEDNAME").toString();
                ptr->m_sendPortId = query.value("SENDPORTID").toString();
                ptr->m_sendStrapRef = query.value("SENDSTRAPREF").toString();
                ptr->m_gooseRef = query.value("GOOSEREF").toString();
                ptr->m_gooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
                ptr->m_gooseDataExcep = query.value("GOOSEDATAEXCEP").toString();
                ptr->m_phyLink = query.value("PHYLINK").toString();
                lst.append(ptr);
            }
        }

        sql = QObject::tr("SELECT * FROM virloopconfig WHERE SENDIEDNAME=\"%1\"")
                .arg(iedName);
        bSucc2 = query.exec(sql);

        if(bSucc2)
        {
            while(query.next())
            {
                VirLoopConfig::Ptr ptr(new VirLoopConfig());
                ptr->m_GUID = query.value("GUID").toInt();
                ptr->m_appId = query.value("APPID").toString();
                ptr->m_recvIedName = query.value("RECVIEDNAME").toString();
                ptr->m_recvPortId = query.value("RECVPORTID").toString();
                ptr->m_recvStrapRef = query.value("RECVSTRAPREF").toString();
                ptr->m_gooseInst = query.value("GOOSEINST").toString();
                ptr->m_gooseInstDesc = query.value("GOOSEINSTDESC").toString();
                ptr->m_sendIedName = query.value("SENDIEDNAME").toString();
                ptr->m_sendPortId = query.value("SENDPORTID").toString();
                ptr->m_sendStrapRef = query.value("SENDSTRAPREF").toString();
                ptr->m_gooseRef = query.value("GOOSEREF").toString();
                ptr->m_gooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
                ptr->m_gooseDataExcep = query.value("GOOSEDATAEXCEP").toString();
                ptr->m_phyLink = query.value("PHYLINK").toString();
                lst.append(ptr);
            }
        }
        db.close();
    }
    if(ok)
    {
        if(bSucc1 && bSucc2)
            *ok = true;
        else
            *ok = false;
    }


    return lst;
}

VirLoopConfig::List DBVirLoopConfigDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool *ok)
{
    bool bSucc1 = false;
    bool bSucc2 = false;
    VirLoopConfig::List lst;
    QString sql = QObject::tr("SELECT * FROM virloopconfig WHERE RECVIEDNAME=\"%1\"")
            .arg(iedName);
    QSqlQuery query(db);
    bSucc1 = query.exec(sql);

    if(bSucc1)
    {
        while(query.next())
        {
            VirLoopConfig::Ptr ptr(new VirLoopConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_appId = query.value("APPID").toString();
            ptr->m_recvIedName = query.value("RECVIEDNAME").toString();
            ptr->m_recvPortId = query.value("RECVPORTID").toString();
            ptr->m_recvStrapRef = query.value("STRAPREF").toString();
            ptr->m_gooseInst = query.value("GOOSEINST").toString();
            ptr->m_gooseInstDesc = query.value("GOOSEINSTDESC").toString();
            ptr->m_sendIedName = query.value("SENDIEDNAME").toString();
            ptr->m_sendPortId = query.value("SENDPORTID").toString();
            ptr->m_sendStrapRef = query.value("SENDSTRAPREF").toString();
            ptr->m_gooseRef = query.value("GOOSEREF").toString();
            ptr->m_gooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
            ptr->m_gooseDataExcep = query.value("GOOSEDATAEXCEP").toString();
            ptr->m_phyLink = query.value("PHYLINK").toString();
            lst.append(ptr);
        }
    }

    sql = QObject::tr("SELECT * FROM virloopconfig WHERE SENDIEDNAME=\"%1\"")
            .arg(iedName);
    bSucc2 = query.exec(sql);

    if(bSucc2)
    {
        while(query.next())
        {
            VirLoopConfig::Ptr ptr(new VirLoopConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_appId = query.value("APPID").toString();
            ptr->m_recvIedName = query.value("RECVIEDNAME").toString();
            ptr->m_recvPortId = query.value("RECVPORTID").toString();
            ptr->m_recvStrapRef = query.value("STRAPREF").toString();
            ptr->m_gooseInst = query.value("GOOSEINST").toString();
            ptr->m_gooseInstDesc = query.value("GOOSEINSTDESC").toString();
            ptr->m_sendIedName = query.value("SENDIEDNAME").toString();
            ptr->m_sendPortId = query.value("SENDPORTID").toString();
            ptr->m_sendStrapRef = query.value("SENDSTRAPREF").toString();
            ptr->m_gooseRef = query.value("GOOSEREF").toString();
            ptr->m_gooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
            ptr->m_gooseDataExcep = query.value("GOOSEDATAEXCEP").toString();
            ptr->m_phyLink = query.value("PHYLINK").toString();
            lst.append(ptr);
        }
    }
    if(ok)
    {
        if(bSucc1 && bSucc2)
            *ok = true;
        else
            *ok = false;
    }

    return lst;
}

VirLoopIedInfo::Ptr DBVirLoopConfigDAO::doQueryByIedName(const QString &iedName, bool isLoopIedInfo)
{
    if(isLoopIedInfo != true)
        return NULL;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        //printf("isOpen!\n");
        QSqlQuery query(db);
        DBIedInfoDAO dao_ied;
        DBOptPortDAO dao_optPort;
        DBStrapLightPlateDAO dao_strap;
        DBGooseInfoDAO dao_gooseInfo;
        DBFibreOpticalDAO dao_line;
        DBDevRunStateDAO dao_runState;

        VirLoopIedInfo::Ptr ptr(new VirLoopIedInfo());
        Ied *ied = dao_ied.ied(iedName);
        if(!ied)
        {
            return NULL;
        }
        ptr->setIed(ied);

        QString sql = QObject::tr("SELECT * FROM virloopconfig WHERE RECVIEDNAME=\"%1\"")
                .arg(iedName);
        //printf("sql: %s\n", sql.toStdString().data());
        if(query.exec(sql))
        {
            while(query.next())
            {
                VirLoopSendIed *sendIed = new VirLoopSendIed();

                QString appId = query.value("APPID").toString();
                sendIed->setAppId(appId);
                //printf("appId: %s\n", appId.toStdString().data());

                QString selfStrapRef = query.value("RECVSTRAPREF").toString();
                //printf("selfStrapRef(select ): %s\n", selfStrapRef.toStdString().data());
                Strap *selfStrap = dao_strap.strap(selfStrapRef);
                sendIed->setSelfStrap(selfStrap);

                QString selfPortID = query.value("RECVPORTID").toString();
                OptPort *selfPort = dao_optPort.port(ied->iedName(), selfPortID);
                sendIed->setSelfPort(selfPort);

                QString gooseInst = query.value("GOOSEINST").toString();
                QString gooseInstDesc = query.value("GOOSEINSTDESC").toString();
                GooseInst *gseInst = new GooseInst();
                gseInst->m_gooseInst = gooseInst;
                gseInst->m_gooseInstDesc = gooseInstDesc;
                sendIed->setGooseInst(gseInst);

                QString selfGooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
                DevRunState *selfGooseLinkAlarm = dao_runState.devRunState(selfGooseLinkAlarmRef);
                sendIed->setSelfGooseLinkAlarm(selfGooseLinkAlarm);

                QString sendIedName = query.value("SENDIEDNAME").toString();
                Ied *sIed = dao_ied.ied(sendIedName);
                //printf("sendIedName: %s\n", sIed->iedName().toStdString().data());
                sendIed->setSendIed(sIed);

                QString sendStrapRef = query.value("SENDSTRAPREF").toString();
                Strap *sendStrap = dao_strap.strap(sendStrapRef);
                sendIed->setSendStrap(sendStrap);

                QString sendPortId = query.value("SENDPORTID").toString();
                OptPort *sendPort = dao_optPort.port(sIed->iedName(), sendPortId);
                sendIed->setSendPort(sendPort);

                QString gooseRef = query.value("GOOSEREF").toString();
                GooseInfo *gooseInfo = dao_gooseInfo.gooseInfo(gooseRef);
                sendIed->setGooseInfo(gooseInfo);

                QString phyLink = query.value("PHYLINK").toString();
                if(phyLink.contains("$"))
                {
                    QStringList lstPhyLink = phyLink.split("$");
                    for(int i = 0; i < lstPhyLink.size()-1; i++)
                    {
                        FibreOptical *lastLine = dao_line.line(lstPhyLink[i]);
                        SwitchDevice *switchDev = new SwitchDevice();
                        switchDev->setLastLine(lastLine);
                        if((i==0 && lastLine->iedName1()==ied->iedName()) || (lastLine->iedName1()==sendIed->lstSwitchDevice().at(sendIed->lstSwitchDevice().size()-1)->iedName()))
                        {
                            OptPort *lastLinePort = dao_optPort.port(lastLine->iedName2(), lastLine->port2());
                            switchDev->setLastLinePort(lastLinePort);
                            switchDev->setIedName(lastLine->iedName2());
                        }
                        else
                        {
                            OptPort *lastLinePort = dao_optPort.port(lastLine->iedName1(), lastLine->port1());
                            switchDev->setLastLinePort(lastLinePort);
                            switchDev->setIedName(lastLine->iedName1());
                        }
                        FibreOptical *nextLine = dao_line.line(lstPhyLink[i+1]);
                        switchDev->setNextLine(nextLine);
                        if(nextLine->iedName1() == switchDev->iedName())
                        {
                            OptPort *nextLinePort = dao_optPort.port(switchDev->iedName(), nextLine->port1());
                            switchDev->setNextLinePort(nextLinePort);
                        }
                        else
                        {
                            OptPort *nextLinePort = dao_optPort.port(switchDev->iedName(), nextLine->port2());
                            switchDev->setNextLinePort(nextLinePort);
                        }
//                        printf("%s %s |%s| %s %s\n", lastLine->lineRef().toStdString().data(), switchDev->lastLinePort()->portID().toStdString().data(), switchDev->iedName().toStdString().data(), nextLine->lineRef().toStdString().data(), switchDev->nextLinePort()->portID().toStdString().data());
                        sendIed->addSwitchDevice(switchDev);
                        if(i == 0)
                        {
                            FibreOptical *lineIedToSwitch = dao_line.line(lstPhyLink[i]);
                            sendIed->setLineIedToSwitch(lineIedToSwitch);
                        }
                        if(i == lstPhyLink.size()-2)
                        {
                            FibreOptical *lineSwitchToIed = dao_line.line(lstPhyLink[i]);
                            sendIed->setLineSwitchToIed(lineSwitchToIed);
                        }
                    }
                }else{
                    FibreOptical *lineSwitchToIed = dao_line.line(phyLink);
                    FibreOptical *lineIedToSwitch = dao_line.line(phyLink);
                    sendIed->setLineSwitchToIed(lineSwitchToIed);
                    sendIed->setLineIedToSwitch(lineIedToSwitch);
                }

                ptr->addSendIed(sendIed);
            }
        }

        sql = QObject::tr("SELECT * FROM virloopconfig WHERE SENDIEDNAME=\"%1\"")
                .arg(iedName);
        if(query.exec(sql))
        {
            while(query.next())
            {
                VirLoopRecvIed *recvIed = new VirLoopRecvIed();

                QString appId = query.value("APPID").toString();
                recvIed->setAppId(appId);

                QString selfStrapRef = query.value("SENDSTRAPREF").toString();
                Strap *selfStrap = dao_strap.strap(selfStrapRef);
                recvIed->setSelfStrap(selfStrap);

                QString selfPortID = query.value("SENDPORTID").toString();
                OptPort *selfPort = dao_optPort.port(ied->iedName(), selfPortID);

                recvIed->setSelfPort(selfPort);

                QString gooseRef = query.value("GOOSEREF").toString();
                GooseInfo *gooseInfo = dao_gooseInfo.gooseInfo(gooseRef);
                recvIed->setGooseInfo(gooseInfo);

                QString sendIedName = query.value("RECVIEDNAME").toString();
                Ied *sIed = dao_ied.ied(sendIedName);
                recvIed->setRecvIed(sIed);

                QString sendStrapRef = query.value("RECVSTRAPREF").toString();
                Strap *sendStrap = dao_strap.strap(sendStrapRef);
                recvIed->setRecvStrap(sendStrap);

                QString sendPortId = query.value("RECVPORTID").toString();
                OptPort *sendPort = dao_optPort.port(sIed->iedName(), sendPortId);
                recvIed->setRecvPort(sendPort);

                QString gooseInst = query.value("GOOSEINST").toString();
                QString gooseInstDesc = query.value("GOOSEINSTDESC").toString();
                GooseInst *gseInst = new GooseInst();
                gseInst->m_gooseInst = gooseInst;
                gseInst->m_gooseInstDesc = gooseInstDesc;
                recvIed->setGooseInst(gseInst);

                QString recvIedGooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
                DevRunState *recvIedGooseLinkAlarm = dao_runState.devRunState(recvIedGooseLinkAlarmRef);
                recvIed->setRecvIedGooseLinkAlarm(recvIedGooseLinkAlarm);

                QString phyLink = query.value("PHYLINK").toString();
                if(phyLink.contains("$"))
                {
                    QStringList lstPhyLink = phyLink.split("$");
                    for(int i=lstPhyLink.size()-1; i >= 1; i--)
                    {
                        FibreOptical *lastLine = dao_line.line(lstPhyLink[i]);
                        SwitchDevice *switchDev = new SwitchDevice();
                        switchDev->setLastLine(lastLine);
                        if((i==lstPhyLink.size()-1 && lastLine->iedName1()==ied->iedName()) || (lastLine->iedName1()==recvIed->lstSwitchDevice().at(recvIed->lstSwitchDevice().size()-1)->iedName()))
                        {
                            OptPort *lastLinePort = dao_optPort.port(lastLine->iedName2(), lastLine->port2());
                            switchDev->setLastLinePort(lastLinePort);
                            switchDev->setIedName(lastLine->iedName2());
                        }
                        else
                        {
                            OptPort *lastLinePort = dao_optPort.port(lastLine->iedName1(), lastLine->port1());
                            switchDev->setLastLinePort(lastLinePort);
                            switchDev->setIedName(lastLine->iedName1());
                        }
                        //switchDev->setLastLinePort(selfPort);
                        FibreOptical *nextLine = dao_line.line(lstPhyLink[i-1]);
                        switchDev->setNextLine(nextLine);
                        if(nextLine->iedName1() != switchDev->iedName())
                        {
                            OptPort *nextLinePort = dao_optPort.port(switchDev->iedName(), nextLine->port2());
                            switchDev->setNextLinePort(nextLinePort);
                        }
                        else
                        {
                            OptPort *nextLinePort = dao_optPort.port(switchDev->iedName(), nextLine->port1());
                            switchDev->setNextLinePort(nextLinePort);
                        }
                        recvIed->addSwitchDevice(switchDev);
                        if(i == lstPhyLink.size() - 1)
                        {
                            FibreOptical *lineIedToSwitch = dao_line.line(lstPhyLink[i]);
                            recvIed->setLineIedToSwitch(lineIedToSwitch);
                        }
                        if(i == 1)
                        {
                            FibreOptical *lineSwitchToIed = dao_line.line(lstPhyLink[i]);
                            recvIed->setLineSwitchToIed(lineSwitchToIed);
                        }
                    }
                }
                else
                {
                    FibreOptical *lineSwitchToIed = dao_line.line(phyLink);
                    FibreOptical *lineIedToSwitch = dao_line.line(phyLink);
                    recvIed->setLineSwitchToIed(lineSwitchToIed);
                    recvIed->setLineIedToSwitch(lineIedToSwitch);
                }

                ptr->addRecvIed(recvIed);
            }
        }
        db.close();
        return ptr;
    }

    return NULL;
}

VirLoopIedInfo::List DBVirLoopConfigDAO::doQueryByBayName(const QString &bayName, bool isLoopIedInfo)
{
    VirLoopIedInfo::List lst;
    if(isLoopIedInfo != true)
        return lst;
    DBIedInfoDAO dao_ied;
    Ied::List lst_ied = dao_ied.doQueryByBayName(bayName);
    Ied::List::iterator iter_ied;
    for(iter_ied=lst_ied.begin(); iter_ied!=lst_ied.end(); iter_ied++)
    {
        Ied::Ptr ptr(new Ied());
        ptr = *iter_ied;
        QString iedName = ptr->iedName();
        VirLoopIedInfo::Ptr ptrV = this->doQueryByIedName(iedName, true);
        lst.append(ptrV);
    }

    return lst;
}

VirLoopIedInfo::List DBVirLoopConfigDAO::doQueryByNetType(const QString &voltClass, int netType)
{
    VirLoopIedInfo::List lst;
    DBIedInfoDAO dao;
    Ied::List lst_ied = dao.doQueryByVoltAndPort(voltClass, netType);
    Ied::List::iterator iter;
    for(iter=lst_ied.begin(); iter!=lst_ied.end(); iter++)
    {
        Ied::Ptr ptr_ied(new Ied());
        ptr_ied = *iter;
        VirLoopIedInfo::Ptr ptr = this->doQueryByIedName(ptr_ied->iedName(), true);
        lst.append(ptr);
    }

    return lst;
}

VirLoopConfig::List DBVirLoopConfigDAO::doQuery(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    VirLoopConfig::List lst;
    QString sql = QObject::tr("SELECT * FROM virloopconfig");
    QSqlQuery query(db);
    bSucc = query.exec(sql);

    if(bSucc)
    {
        while(query.next())
        {
            VirLoopConfig::Ptr ptr(new VirLoopConfig());
            ptr->m_GUID = query.value("GUID").toInt();
            ptr->m_appId = query.value("APPID").toString();
            ptr->m_recvIedName = query.value("RECVIEDNAME").toString();
            ptr->m_recvPortId = query.value("RECVPORTID").toString();
            ptr->m_recvStrapRef = query.value("RECVSTRAPREF").toString();
            ptr->m_gooseInst = query.value("GOOSEINST").toString();
            ptr->m_gooseInstDesc = query.value("GOOSEINSTDESC").toString();
            ptr->m_sendIedName = query.value("SENDIEDNAME").toString();
            ptr->m_sendPortId = query.value("SENDPORTID").toString();
            ptr->m_sendStrapRef = query.value("SENDSTRAPREF").toString();
            ptr->m_gooseRef = query.value("GOOSEREF").toString();
            ptr->m_gooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
            ptr->m_gooseDataExcep = query.value("GOOSEDATAEXCEP").toString();
            ptr->m_phyLink = query.value("PHYLINK").toString();
            lst.append(ptr);
        }
    }
    if(ok)
        *ok = bSucc;

    return lst;
}

VirLoopIedInfo::Ptr DBVirLoopConfigDAO::doQueryByIedName(QSqlDatabase db, const QString &iedName, bool isLoopIedInfo)
{
    if(isLoopIedInfo != true)
        return NULL;
    QSqlQuery query(db);
    DBIedInfoDAO dao_ied;
    DBOptPortDAO dao_optPort;
    DBStrapLightPlateDAO dao_strap;
    DBGooseInfoDAO dao_gooseInfo;
    DBFibreOpticalDAO dao_line;
    DBDevRunStateDAO dao_runState;

    VirLoopIedInfo::Ptr ptr(new VirLoopIedInfo());
    Ied *ied = dao_ied.ied(db, iedName);
    if(!ied)
    {
        return NULL;
    }
    ptr->setIed(ied);

    QString sql = QObject::tr("SELECT * FROM virloopconfig WHERE RECVIEDNAME=\"%1\"")
            .arg(iedName);
    //printf("sql: %s\n", sql.toStdString().data());
    if(query.exec(sql))
    {
        while(query.next())
        {
            VirLoopSendIed *sendIed = new VirLoopSendIed();

            QString appId = query.value("APPID").toString();
            sendIed->setAppId(appId);
            //printf("appId: %s\n", appId.toStdString().data());

            QString selfStrapRef = query.value("RECVSTRAPREF").toString();
            //printf("selfStrapRef(select ): %s\n", selfStrapRef.toStdString().data());
            Strap *selfStrap = dao_strap.strap(db, selfStrapRef);
            sendIed->setSelfStrap(selfStrap);

            QString selfPortID = query.value("RECVPORTID").toString();
            OptPort *selfPort = dao_optPort.port(db, ied->iedName(), selfPortID);
            sendIed->setSelfPort(selfPort);

            QString gooseInst = query.value("GOOSEINST").toString();
            QString gooseInstDesc = query.value("GOOSEINSTDESC").toString();
            GooseInst *gseInst = new GooseInst();
            gseInst->m_gooseInst = gooseInst;
            gseInst->m_gooseInstDesc = gooseInstDesc;
            sendIed->setGooseInst(gseInst);

            QString selfGooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
            DevRunState *selfGooseLinkAlarm = dao_runState.devRunState(db, selfGooseLinkAlarmRef);
            sendIed->setSelfGooseLinkAlarm(selfGooseLinkAlarm);

            QString sendIedName = query.value("SENDIEDNAME").toString();
            Ied *sIed = dao_ied.ied(db, sendIedName);
            //printf("sendIedName: %s\n", sIed->iedName().toStdString().data());
            sendIed->setSendIed(sIed);

            QString sendStrapRef = query.value("SENDSTRAPREF").toString();
            Strap *sendStrap = dao_strap.strap(db, sendStrapRef);
            sendIed->setSendStrap(sendStrap);

            QString sendPortId = query.value("SENDPORTID").toString();
            OptPort *sendPort = dao_optPort.port(db, sIed->iedName(), sendPortId);
            sendIed->setSendPort(sendPort);

            QString gooseRef = query.value("GOOSEREF").toString();
            GooseInfo *gooseInfo = dao_gooseInfo.gooseInfo(db, gooseRef);
            sendIed->setGooseInfo(gooseInfo);

            QString phyLink = query.value("PHYLINK").toString();
            if(phyLink.contains("$"))
            {
                QStringList lstPhyLink = phyLink.split("$");
                for(int i = 0; i < lstPhyLink.size()-1; i++)
                {
                    FibreOptical *lastLine = dao_line.line(db, lstPhyLink[i]);
                    SwitchDevice *switchDev = new SwitchDevice();
                    switchDev->setLastLine(lastLine);
                    if((i==0 && lastLine->iedName1()==ied->iedName()) || (lastLine->iedName1()==sendIed->lstSwitchDevice().at(sendIed->lstSwitchDevice().size()-1)->iedName()))
                    {
                        OptPort *lastLinePort = dao_optPort.port(db, lastLine->iedName2(), lastLine->port2());
                        switchDev->setLastLinePort(lastLinePort);
                        switchDev->setIedName(lastLine->iedName2());
                    }
                    else
                    {
                        OptPort *lastLinePort = dao_optPort.port(db, lastLine->iedName1(), lastLine->port1());
                        switchDev->setLastLinePort(lastLinePort);
                        switchDev->setIedName(lastLine->iedName1());
                    }
                    FibreOptical *nextLine = dao_line.line(db, lstPhyLink[i+1]);
                    switchDev->setNextLine(nextLine);
                    if(nextLine->iedName1() == switchDev->iedName())
                    {
                        OptPort *nextLinePort = dao_optPort.port(db, switchDev->iedName(), nextLine->port1());
                        switchDev->setNextLinePort(nextLinePort);
                    }
                    else
                    {
                        OptPort *nextLinePort = dao_optPort.port(db, switchDev->iedName(), nextLine->port2());
                        switchDev->setNextLinePort(nextLinePort);
                    }
//                        printf("%s %s |%s| %s %s\n", lastLine->lineRef().toStdString().data(), switchDev->lastLinePort()->portID().toStdString().data(), switchDev->iedName().toStdString().data(), nextLine->lineRef().toStdString().data(), switchDev->nextLinePort()->portID().toStdString().data());
                    sendIed->addSwitchDevice(switchDev);
                    if(i == 0)
                    {
                        FibreOptical *lineIedToSwitch = dao_line.line(db, lstPhyLink[i]);
                        sendIed->setLineIedToSwitch(lineIedToSwitch);
                    }
                    if(i == lstPhyLink.size()-2)
                    {
                        FibreOptical *lineSwitchToIed = dao_line.line(db, lstPhyLink[i]);
                        sendIed->setLineSwitchToIed(lineSwitchToIed);
                    }
                }
            }else{
                FibreOptical *lineSwitchToIed = dao_line.line(db, phyLink);
                FibreOptical *lineIedToSwitch = dao_line.line(db, phyLink);
                sendIed->setLineSwitchToIed(lineSwitchToIed);
                sendIed->setLineIedToSwitch(lineIedToSwitch);
            }

            ptr->addSendIed(sendIed);
        }
    }
    else
        return NULL;

    sql = QObject::tr("SELECT * FROM virloopconfig WHERE SENDIEDNAME=\"%1\"")
            .arg(iedName);
    if(query.exec(sql))
    {
        while(query.next())
        {
            VirLoopRecvIed *recvIed = new VirLoopRecvIed();

            QString appId = query.value("APPID").toString();
            recvIed->setAppId(appId);

            QString selfStrapRef = query.value("SENDSTRAPREF").toString();
            Strap *selfStrap = dao_strap.strap(db, selfStrapRef);
            recvIed->setSelfStrap(selfStrap);

            QString selfPortID = query.value("SENDPORTID").toString();
            OptPort *selfPort = dao_optPort.port(db, ied->iedName(), selfPortID);

            recvIed->setSelfPort(selfPort);

            QString gooseRef = query.value("GOOSEREF").toString();
            GooseInfo *gooseInfo = dao_gooseInfo.gooseInfo(db, gooseRef);
            recvIed->setGooseInfo(gooseInfo);

            QString sendIedName = query.value("RECVIEDNAME").toString();
            Ied *sIed = dao_ied.ied(db, sendIedName);
            recvIed->setRecvIed(sIed);

            QString sendStrapRef = query.value("RECVSTRAPREF").toString();
            Strap *sendStrap = dao_strap.strap(db, sendStrapRef);
            recvIed->setRecvStrap(sendStrap);

            QString sendPortId = query.value("RECVPORTID").toString();
            OptPort *sendPort = dao_optPort.port(db, sIed->iedName(), sendPortId);
            recvIed->setRecvPort(sendPort);

            QString gooseInst = query.value("GOOSEINST").toString();
            QString gooseInstDesc = query.value("GOOSEINSTDESC").toString();
            GooseInst *gseInst = new GooseInst();
            gseInst->m_gooseInst = gooseInst;
            gseInst->m_gooseInstDesc = gooseInstDesc;
            recvIed->setGooseInst(gseInst);

            QString recvIedGooseLinkAlarmRef = query.value("GOOSELINKALARMREF").toString();
            DevRunState *recvIedGooseLinkAlarm = dao_runState.devRunState(db, recvIedGooseLinkAlarmRef);
            recvIed->setRecvIedGooseLinkAlarm(recvIedGooseLinkAlarm);

            QString phyLink = query.value("PHYLINK").toString();
            if(phyLink.contains("$"))
            {
                QStringList lstPhyLink = phyLink.split("$");
                for(int i=lstPhyLink.size()-1; i >= 1; i--)
                {
                    FibreOptical *lastLine = dao_line.line(db, lstPhyLink[i]);
                    SwitchDevice *switchDev = new SwitchDevice();
                    switchDev->setLastLine(lastLine);
                    if((i==lstPhyLink.size()-1 && lastLine->iedName1()==ied->iedName()) || (lastLine->iedName1()==recvIed->lstSwitchDevice().at(recvIed->lstSwitchDevice().size()-1)->iedName()))
                    {
                        OptPort *lastLinePort = dao_optPort.port(db, lastLine->iedName2(), lastLine->port2());
                        switchDev->setLastLinePort(lastLinePort);
                        switchDev->setIedName(lastLine->iedName2());
                    }
                    else
                    {
                        OptPort *lastLinePort = dao_optPort.port(db, lastLine->iedName1(), lastLine->port1());
                        switchDev->setLastLinePort(lastLinePort);
                        switchDev->setIedName(lastLine->iedName1());
                    }
                    //switchDev->setLastLinePort(selfPort);
                    FibreOptical *nextLine = dao_line.line(db, lstPhyLink[i-1]);
                    switchDev->setNextLine(nextLine);
                    if(nextLine->iedName1() != switchDev->iedName())
                    {
                        OptPort *nextLinePort = dao_optPort.port(db, switchDev->iedName(), nextLine->port2());
                        switchDev->setNextLinePort(nextLinePort);
                    }
                    else
                    {
                        OptPort *nextLinePort = dao_optPort.port(db, switchDev->iedName(), nextLine->port1());
                        switchDev->setNextLinePort(nextLinePort);
                    }
                    recvIed->addSwitchDevice(switchDev);
                    if(i == lstPhyLink.size() - 1)
                    {
                        FibreOptical *lineIedToSwitch = dao_line.line(db, lstPhyLink[i]);
                        recvIed->setLineIedToSwitch(lineIedToSwitch);
                    }
                    if(i == 1)
                    {
                        FibreOptical *lineSwitchToIed = dao_line.line(db, lstPhyLink[i]);
                        recvIed->setLineSwitchToIed(lineSwitchToIed);
                    }
                }
            }
            else
            {
                FibreOptical *lineSwitchToIed = dao_line.line(db, phyLink);
                FibreOptical *lineIedToSwitch = dao_line.line(db, phyLink);
                recvIed->setLineSwitchToIed(lineSwitchToIed);
                recvIed->setLineIedToSwitch(lineIedToSwitch);
            }

            ptr->addRecvIed(recvIed);
        }
    }
    else
        return NULL;

    return ptr;
}

VirLoopIedInfo::List DBVirLoopConfigDAO::doQueryByBayName(QSqlDatabase db, const QString &bayName, bool isLoopIedInfo)
{
    VirLoopIedInfo::List lst;
    if(isLoopIedInfo != true)
        return lst;
    DBIedInfoDAO dao_ied;
    Ied::List lst_ied = dao_ied.doQueryByBayName(db, bayName);
    Ied::List::iterator iter_ied;
    for(iter_ied=lst_ied.begin(); iter_ied!=lst_ied.end(); iter_ied++)
    {
        Ied::Ptr ptr(new Ied());
        ptr = *iter_ied;
        QString iedName = ptr->iedName();
        VirLoopIedInfo::Ptr ptrV = this->doQueryByIedName(db, iedName, true);
        lst.append(ptrV);
    }

    return lst;
}

VirLoopIedInfo::List DBVirLoopConfigDAO::doQueryByNetType(QSqlDatabase db, const QString &voltClass, int netType)
{
    VirLoopIedInfo::List lst;
    DBIedInfoDAO dao;
    Ied::List lst_ied = dao.doQueryByVoltAndPort(db, voltClass, netType);
    Ied::List::iterator iter;
    for(iter=lst_ied.begin(); iter!=lst_ied.end(); iter++)
    {
        Ied::Ptr ptr_ied(new Ied());
        ptr_ied = *iter;
        VirLoopIedInfo::Ptr ptr = this->doQueryByIedName(db, ptr_ied->iedName(), true);
        lst.append(ptr);
    }

    return lst;
}

QHash<QString, QList<int> > DBVirLoopConfigDAO::doQueryNetType(QSqlDatabase db, bool *ok)
{
    bool bSucc = false;
    DBOptPortDAO dao;
    QHash<QString, QList<int>> hsh = dao.doQueryNetType(db, &bSucc);
    if(ok)
        *ok = bSucc;
    return hsh;
}

QHash<QString, QList<int>> DBVirLoopConfigDAO::doQueryNetType(bool *ok)
{
    bool bSucc = false;
    DBOptPortDAO dao;
    QHash<QString, QList<int>> hsh = dao.doQueryNetType(&bSucc);
    if(ok)
        *ok = bSucc;
    return hsh;
}

//VirLoopIedInfo::List DBVirLoopConfigDAO::doQueryHash()
//{

//}

bool DBVirLoopConfigDAO::doInsert(VirLoopConfig::List &lst)
{
    bool bSucc = false;
    VirLoopConfig::List::iterator iter = lst.begin();
    int list_size = lst.size();
    if(list_size == 0)
        return true;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = "";
        query.exec("begin transaction");
        if(list_size <= 1000)
        {
            while(iter < lst.end())
            {
                VirLoopConfig::Ptr ptr(new VirLoopConfig());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO virloopconfig VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\", \"%9\", \"%10\", \"%11\", \"%12\", \"%13\")")
                        .arg(ptr->appId())//1
                        .arg(ptr->recvIedName())//2
                        .arg(ptr->recvPortId())//3
                        .arg(ptr->recvStrapRef())//4
                        .arg(ptr->gooseInst())//5
                        .arg(ptr->gooseInstDesc())//6
                        .arg(ptr->sendIedName())//7
                        .arg(ptr->sendPortId())//8
                        .arg(ptr->sendStrapRef())//9
                        .arg(ptr->gooseRef())//10
                        .arg(ptr->phyLink())//11
                        .arg(ptr->gooseLinkAlarmRef())//12
                        .arg(ptr->gooseDataExcep());//13
                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: %s", error_s.toStdString().data());
                    db.close();
                    return bSucc;
                }
                iter++;
            }
        }
        else
        {
            int count = 0;
            while(iter < lst.end())
            {
                VirLoopConfig::Ptr ptr(new VirLoopConfig());
                ptr = *iter;

                sql = QObject::tr("INSERT INTO virloopconfig VALUES(NULL, \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\", \"%9\", \"%10\", \"%11\", \"%12\", \"%13\")")
                        .arg(ptr->appId())//1
                        .arg(ptr->recvIedName())//2
                        .arg(ptr->recvPortId())//3
                        .arg(ptr->recvStrapRef())//4
                        .arg(ptr->gooseInst())//5
                        .arg(ptr->gooseInstDesc())//6
                        .arg(ptr->sendIedName())//7
                        .arg(ptr->sendPortId())//8
                        .arg(ptr->sendStrapRef())//9
                        .arg(ptr->gooseRef())//10
                        .arg(ptr->phyLink())//11
                        .arg(ptr->gooseLinkAlarmRef())//12
                        .arg(ptr->gooseDataExcep());//13
                if(!query.exec(sql))
                {
                    QString error_s = query.lastError().text();
                    printf("error: %s", error_s.toStdString().data());
                    db.close();
                    return bSucc;
                }
                count++;
                if(count == 1000)
                {
                    bSucc = query.exec("commit transaction");
                    if(!bSucc){
                        QString error_s = query.lastError().text();
                        printf("error: %s", error_s.toStdString().data());
                    }
                    query.exec("begin transaction");
                    count = 0;
                }
                iter++;
            }
        }
        bSucc = query.exec("commit transaction");
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }
    return bSucc;
}

bool DBVirLoopConfigDAO::doUpdate(const VirLoopConfig::Ptr &ptr)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("UPDATE virloopconfig SET APPID=\"%1\", RECVIEDNAME=\"%2\", RECVPORTID=\"%3\", RECVSTRAPREF=\"%4\", GOOSEINST=\"%5\", GOOSEINSTDESC=\"%6\", SENDIEDNAME=\"%7\", SENDPORTID=\"%8\", SENDSTRAPREF=\"%9\", GOOSEREF=\"%10\", PHYLINK=\"%11\", GOOSELINKALARMREF=\"%12\", GOOSEDATAEXCEP=\"%13\" WHERE GUID=%14")
                .arg(ptr->appId())//1
                .arg(ptr->recvIedName())//2
                .arg(ptr->recvPortId())//3
                .arg(ptr->recvStrapRef())//4
                .arg(ptr->gooseInst())//5
                .arg(ptr->gooseInstDesc())//6
                .arg(ptr->sendIedName())//7
                .arg(ptr->sendPortId())//8
                .arg(ptr->sendStrapRef())//9
                .arg(ptr->gooseRef())//10
                .arg(ptr->phyLink())//11
                .arg(ptr->gooseLinkAlarmRef())//12
                .arg(ptr->gooseDataExcep())//13
                .arg(ptr->GUID());//14
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBVirLoopConfigDAO::doUpdate(VirLoopConfig::List &lst)
{
    bool bSucc = false;
    VirLoopConfig::List::iterator iter = lst.begin();
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");

    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        query.exec("begin transaction");

        while(iter < lst.end())
        {
            VirLoopConfig::Ptr ptr(new VirLoopConfig());
            ptr = *iter;
            QString sql = QObject::tr("UPDATE virloopconfig SET APPID=\"%1\", RECVIEDNAME=\"%2\", RECVPORTID=\"%3\", RECVSTRAPREF=\"%4\", GOOSEINST=\"%5\", GOOSEINSTDESC=\"%6\", SENDIEDNAME=\"%7\", SENDPORTID=\"%8\", SENDSTRAPREF=\"%9\", GOOSEREF=\"%10\", PHYLINK=\"%11\", GOOSELINKALARMREF=\"%12\", GOOSEDATAEXCEP=\"%13\" WHERE GUID=%14")
                    .arg(ptr->appId())//1
                    .arg(ptr->recvIedName())//2
                    .arg(ptr->recvPortId())//3
                    .arg(ptr->recvStrapRef())//4
                    .arg(ptr->gooseInst())//5
                    .arg(ptr->gooseInstDesc())//6
                    .arg(ptr->sendIedName())//7
                    .arg(ptr->sendPortId())//8
                    .arg(ptr->sendStrapRef())//9
                    .arg(ptr->gooseRef())//10
                    .arg(ptr->phyLink())//11
                    .arg(ptr->gooseLinkAlarmRef())//12
                    .arg(ptr->gooseDataExcep())//13
                    .arg(ptr->GUID());//14
            if(!query.exec(sql))
            {
                QString error_s = query.lastError().text();
                printf("error: %s", error_s.toStdString().data());
                db.close();
                return bSucc;
            }
            iter++;
        }

        bSucc = query.exec("commit transaction");
        if(!bSucc){
            QString error_s = query.lastError().text();
            printf("error: %s", error_s.toStdString().data());
        }
        db.close();
    }
    return bSucc;
}

bool DBVirLoopConfigDAO::doDelete(int guid)
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM virloopconfig WHERE GUID=\"%1\"")
                .arg(guid);
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBVirLoopConfigDAO::doClear()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("DELETE FROM virloopconfig");
        bSucc = query.exec(sql);
        sql = QObject::tr("UPDATE sqlite_sequence SET seq=0 WHERE name='virloopconfig'");
        bSucc = query.exec(sql);
        db.close();
    }
    return bSucc;
}

bool DBVirLoopConfigDAO::doCreateTable()
{
    bool bSucc = false;
    QSqlDatabase db = DBConnection::connection(m_connectionName, "QSQLITE", "sys_config");
    if(db.isOpen() || db.open())
    {
        QSqlQuery query(db);
        QString sql = QObject::tr("CREATE TABLE IF NOT EXISTS virloopconfig("
                                  "GUID INTEGER PRIMARY KEY autoincrement NOT NULL,"
                                  "APPID CHAR(255) NOT NULL,"
                                  "RECVIEDNAME CHAR(255) NOT NULL,"
                                  "RECVPORTID CHAR(255) NOT NULL,"
                                  "RECVSTRAPREF CHAR(255) NOT NULL,"
                                  "GOOSEINST CHAR(255) NOT NULL,"
                                  "GOOSEINSTDESC CHAR(255) NOT NULL,"
                                  "SENDIEDNAME CHAR(255) NOT NULL,"
                                  "SENDPORTID CHAR(255) NOT NULL,"
                                  "SENDSTRAPREF CHAR(255) NOT NULL,"
                                  "GOOSEREF CHAR(255) NOT NULL,"
                                  "PHYLINK CHAR(255) NOT NULL,"
                                  "GOOSELINKALARMREF CHAR(255) NOT NULL,"
                                  "GOOSEDATAEXCEP CHAR(255) NOT NULL)");
        bSucc = query.exec(sql);
        db.close();
    }

    return bSucc;
}




