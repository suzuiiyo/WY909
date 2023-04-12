#include "writeswitchresultdao.h"
#include <QDebug>

WriteSwitchResultDao::WriteSwitchResultDao() : 
    tscr(new TransientSwitchTaskConclusionRecord())
{
}

WriteSwitchResultDao::~WriteSwitchResultDao()
{

}

bool WriteSwitchResultDao::init()
{
    if(!tscr.isNull()){
        return true;
    }else{
        return false;
    }
}

void WriteSwitchResultDao::setIedName(const QString &var)
{
    tscr->setIedName(var);
}

void WriteSwitchResultDao::setSetType(const QString &var)
{
    tscr->setSetType(var);
}

void WriteSwitchResultDao::setIedNameComp(const QString &var)
{
    tscr->setIedNameComp(var);
}

void WriteSwitchResultDao::setSetTypeComp(const QString &var)
{
    tscr->setSetTypeComp(var);
}

void WriteSwitchResultDao::setRecloseAckDelay(const QString &var)
{
    tscr->setRecloseAckDelay(var);
}

void WriteSwitchResultDao::setBreakerAckDelay(const QString &var)
{
    tscr->setBreakerAckDelay(var);
}

void WriteSwitchResultDao::setFaultZeroTime(const QString &var)
{
    tscr->setFaultZeroTime(var);
}

void WriteSwitchResultDao::setSrIedAFileName(const QString &var)
{
    tscr->setSrIedAFileName(var);
}

void WriteSwitchResultDao::setSrIedBFileName(const QString &var)
{
    tscr->setSrIedBFileName(var);
}

void WriteSwitchResultDao::setTaskFileName(const QString &var)
{
    tscr->setTaskFileName(var);
}

void WriteSwitchResultDao::setStandardFileName(const QString &var)
{
    tscr->setStandardFileName(var);
}

void WriteSwitchResultDao::setChannelType(const QString &var)
{
    tscr->setChannelType(var);
}

void WriteSwitchResultDao::setConclusion(const QString& var)
{
    tscr->setConclusion(var);
}

void WriteSwitchResultDao::setRecloseConclusion(const float &var)
{
    tscr->setRecloseConclusion(var);
}

void WriteSwitchResultDao::setBreakerConclusion(const float &var)
{
    tscr->setBreakerConclusion(var);
}

void WriteSwitchResultDao::setReclosingInnormalTime(const QString& var)
{
    tscr->setReclosingInnormalTime(var);
}

void WriteSwitchResultDao::setReclosingSeriousTime(const QString& var)
{
    tscr->setReclosingSeriousTime(var);
}

void WriteSwitchResultDao::setbreakerInnormalTime(const QString & var)
{
    tscr->setBreakerInnormalTime(var);
}

void WriteSwitchResultDao::setbreakerSeriousTime(const QString & var)
{
    tscr->setBreakerSeriousTime(var);
}

void WriteSwitchResultDao::setReclosingResult(const int& var)
{
    tscr->setReclosingResult(var);
}

void WriteSwitchResultDao::setBreakerResult(const int& var)
{
    tscr->setBreakerResult(var);
}

void WriteSwitchResultDao::setTaskChannelRef(const int& var)
{
    tscr->setTaskChannelRef(var);
}

void WriteSwitchResultDao::setTaskChannelDesc(const QString & var)
{
    tscr->setTaskChannelDesc(var);
}

void WriteSwitchResultDao::setStandardChannelRef(const int & var)
{
    tscr->setStandChannelRef(var);
}

void WriteSwitchResultDao::setStandardChannelDesc(const QString &var)
{
    tscr->setStandChannelDesc(var);
}

void WriteSwitchResultDao::setRecordTime(const QString &var)
{
    tscr->setRecordTime(var);
}

void WriteSwitchResultDao::setAckTip(int &var)
{
    tscr->setAckTip(var);
}

void WriteSwitchResultDao::setIedTaskType(const QString &var)
{
    tscr->setIedTaskType(var);
}

void WriteSwitchResultDao::setIedPhase(const QString &var)
{
    tscr->setIedPhase(var);
}

void WriteSwitchResultDao::setBayName(const QString &var)
{
    tscr->setBayName(var);
}

void WriteSwitchResultDao::setItemName(const QString & var)
{
    tscr->setItemName(var);
}

TransientSwitchTaskConclusionRecord::Ptr WriteSwitchResultDao::getTSCR()
{
    return tscr;
}
