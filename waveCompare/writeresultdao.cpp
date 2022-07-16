#include "writeresultdao.h"
#include <QDebug>

WriteResultDAO::WriteResultDAO() :
    ttcr(new TransientTaskConclusionRecord())
{
}

WriteResultDAO::~WriteResultDAO()
{
}

bool WriteResultDAO::init()
{
    if(!ttcr.isNull()){
        return true;
    }else{
        return false;
    }
}

void WriteResultDAO::setBayName(const QString &var)
{
    ttcr->setBayName(var);
}

void WriteResultDAO::setItemName(const QString &var)
{
    ttcr->setItemName(var);
}

void WriteResultDAO::setItemType(const QString &var)
{
    ttcr->setIedTaskType(var);
}

void WriteResultDAO::setIedName(const QString &var)
{
    ttcr->setIedName(var);
}

void WriteResultDAO::setSetType(const QString &var)
{
    ttcr->setSetType(var);
}

void WriteResultDAO::setIedNameComp(const QString &var)
{
    ttcr->setIedNameComp(var);
}

void WriteResultDAO::setSetTypeComp(const QString &var)
{
    ttcr->setSetTypeComp(var);
}

void WriteResultDAO::setPhaseType(const QString &var)
{
    ttcr->setIedPhase(var);
}

void WriteResultDAO::setprotStartTime(const QString &var)
{
    ttcr->setProtStartTime(var);
}

void WriteResultDAO::setprotStartResetTime(const QString &var)
{
    ttcr->setProtStartResetTime(var);
}

void WriteResultDAO::setprotFaultNum(int var)
{	
    ttcr->setProtFaultNum(var);
}

void WriteResultDAO::setprotFaultValue(float var)
{
    ttcr->setProtFaultValue(var);
}

void WriteResultDAO::setSrIedAFileName(const QString &var)
{
    ttcr->setSRIedAFileName(var);
}

void WriteResultDAO::setSrIedBFileName(const QString &var)
{
    ttcr->setSRIedBFileName(var);
}

void WriteResultDAO::setSrTMDataType(int var)
{
	ttcr->setSRTMDataType(var);
}

void WriteResultDAO::setSrTMDataValue(float var)
{
    ttcr->setSRTMDataValue(var);
}

void WriteResultDAO::setSrTMThreshold(float var)
{
    ttcr->setSRTMThreshold(var);
}

void WriteResultDAO::setTaskFileName(const QString &var)
{
    ttcr->setTaskFileName(var);
}

void WriteResultDAO::setStandardFileName(const QString &var)
{
    ttcr->setStandardFileName(var);
}

void WriteResultDAO::setChannelType(const QString &var)
{
    ttcr->setChannelType(var);
}

void WriteResultDAO::setConclusion(const QString &var)
{
    ttcr->setConclusion(var);
}

void WriteResultDAO::setAbnormalThreshold(const QString &var)
{
    ttcr->setAbnormalThreshold(var);
}

void WriteResultDAO::setSeriousThreshold(const QString &var)
{
    ttcr->setSeriousThreshold(var);
}

void WriteResultDAO::setResult(const QString &var)
{
    ttcr->setResult(var);
}

void WriteResultDAO::setTaskChannelRef(int var)
{
    ttcr->setTaskChannelRef(var);
}

void WriteResultDAO::setTaskChanelDesc(const QString &var)
{
    ttcr->setTaskChannelDesc(var);
}

void WriteResultDAO::setTaskSamplesPointSeq(const QString &var)
{
    ttcr->setTaskSamplesPointSeq(var);
}

void WriteResultDAO::setTaskSamplesValue(const QString &var)
{
    ttcr->setTaskSamplesValue(var);
}

void WriteResultDAO::setStandardChannelRef(int var)
{
    ttcr->setStandardChannelRef(var);
}

void WriteResultDAO::setStandardChannelDesc(const QString &var)
{
    ttcr->setStandardChannelDesc(var);
}

void WriteResultDAO::setStandardSamplesValue(const QString &var)
{
    ttcr->setStandardSamplesValue(var);
}

void WriteResultDAO::setStandardSamplesPointSeq(const QString &var)
{
    ttcr->setStandardSamplesPointSeq(var);
}

void WriteResultDAO::setIedFaultType(const QString &var)
{
    ttcr->setIedFaultType(var);
}

void WriteResultDAO::setIedFaultInfo(const QString &var)
{
    ttcr->setFaultInfo(var);
}

void WriteResultDAO::setIedFaultInfoCom(const QString &var)
{
    ttcr->setFaultInfoComp(var);
}

void WriteResultDAO::setIedRanging(const QString &var)
{
    ttcr->setIedRanging(var);
}

void WriteResultDAO::setIedCompFaultType(const QString &var)
{
    ttcr->setIedCompFaultType(var);
}

void WriteResultDAO::setIedCompRing(const QString &var)
{
    ttcr->setIedCompRanging(var);
}

void WriteResultDAO::setRecordTime(const QString &var)
{
    ttcr->setRecordTime(var);
}

void WriteResultDAO::setPointRelativeError(const QString &var)
{
    ttcr->setPointRelativeError(var);
}

void WriteResultDAO::setPointAbsoluteError(const QString &var)
{
    ttcr->setPointAbsoluteError(var);
}

void WriteResultDAO::setPointColusion(const QString &var)
{
    ttcr->setPointConclusion(var);
}

TransientTaskConclusionRecord::Ptr WriteResultDAO::getTTCR()
{
    return ttcr;
}


