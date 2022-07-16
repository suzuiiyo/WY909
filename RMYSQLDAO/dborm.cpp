#include "dborm.h"

TransientTaskConclusionRecordORM::TransientTaskConclusionRecordORM()
{
    DBCondition ptr_GUID;
    ptr_GUID.setName("GUID");
    ptr_GUID.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(GUID, ptr_GUID);

    DBCondition ptr_IedName;
    ptr_IedName.setName("IEDNAME");
    ptr_IedName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedName, ptr_IedName);

    DBCondition ptr_setType;
    ptr_setType.setName("SETTYPE");
    ptr_setType.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(setType, ptr_setType);

    DBCondition ptr_iedNameComp;
    ptr_iedNameComp.setName("IEDNAMECOMP");
    ptr_iedNameComp.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedNameComp, ptr_iedNameComp);

    DBCondition ptr_setTypeComp;
    ptr_setTypeComp.setName("SETTYPECOMP");
    ptr_setTypeComp.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(setTypeComp, ptr_setTypeComp);

    DBCondition ptr_protStartTime;
    ptr_protStartTime.setName("PROTSTARTTIME");
    ptr_protStartTime.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(protStartTime, ptr_protStartTime);

    DBCondition ptr_protStartResetTime;
    ptr_protStartResetTime.setName("PROTSTARTRESETTIME");
    ptr_protStartResetTime.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(protStartResetTime, ptr_protStartResetTime);

    DBCondition ptr_protFaultNum;
    ptr_protFaultNum.setName("PROTFAULTNUM");
    ptr_protFaultNum.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(protFaultNum, ptr_protFaultNum);

    DBCondition ptr_protFaultValue;
    ptr_protFaultValue.setName("PROTFAULTVALUE");
    ptr_protFaultValue.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(protFaultValue, ptr_protFaultValue);

    DBCondition ptr_srIedAFileName;
    ptr_srIedAFileName.setName("SRIEDAFILENAME");
    ptr_srIedAFileName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(srIedAFileName, ptr_srIedAFileName);

    DBCondition ptr_srIedBFileName;
    ptr_srIedBFileName.setName("SRIEDBFILENAME");
    ptr_srIedBFileName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(srIedBFileName, ptr_srIedBFileName);

    DBCondition ptr_srTMDataType;
    ptr_srTMDataType.setName("SRTMDATATYPE");
    ptr_srTMDataType.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(srTMDataType, ptr_srTMDataType);

    DBCondition ptr_srTMDataValue;
    ptr_srTMDataValue.setName("SRTMDATAVALUE");
    ptr_srTMDataValue.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(srTMDataValue, ptr_srTMDataValue);

    DBCondition ptr_srTMThreshold;
    ptr_srTMThreshold.setName("SRTMTHRESHOLD");
    ptr_srTMThreshold.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(srTMThreshold, ptr_srTMThreshold);

    DBCondition ptr_taskFileName;
    ptr_taskFileName.setName("TASKFILENAME");
    ptr_taskFileName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(taskFileName, ptr_taskFileName);

    DBCondition ptr_standardFileName;
    ptr_standardFileName.setName("STANDARDFILENAME");
    ptr_standardFileName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(standardFileName, ptr_standardFileName);

    DBCondition ptr_channelType;
    ptr_channelType.setName("CHANNELTYPE");
    ptr_channelType.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(channelType, ptr_channelType);

    DBCondition ptr_conclusion;
    ptr_conclusion.setName("CONCLUSION");
    ptr_conclusion.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(conclusion, ptr_conclusion);

    DBCondition ptr_abnormalThreshold;
    ptr_abnormalThreshold.setName("ABNORMALTHRESHOLD");
    ptr_abnormalThreshold.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(abnormalThreshold, ptr_abnormalThreshold);

    DBCondition ptr_seriousThreshold;
    ptr_seriousThreshold.setName("SERIOUSTHRESHOLD");
    ptr_seriousThreshold.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(seriousThreshold, ptr_seriousThreshold);

    DBCondition ptr_result;
    ptr_result.setName("RESULT");
    ptr_result.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(result, ptr_result);

    DBCondition ptr_taskChannelRef;
    ptr_taskChannelRef.setName("TASKCHANNELREF");
    ptr_taskChannelRef.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(taskChannelRef, ptr_taskChannelRef);

    DBCondition ptr_taskChannelDesc;
    ptr_taskChannelDesc.setName("TASKCHANNELDESC");
    ptr_taskChannelDesc.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(taskChannelDesc, ptr_taskChannelDesc);

    DBCondition ptr_taskSamplesValue;
    ptr_taskSamplesValue.setName("TASKSAMPLESVALUE");
    ptr_taskSamplesValue.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(taskSamplesValue, ptr_taskSamplesValue);

    DBCondition ptr_taskSamplesPointSeq;
    ptr_taskSamplesPointSeq.setName("TASKSAMPLESPOINTSEQ");
    ptr_taskSamplesPointSeq.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(taskSamplesPointSeq, ptr_taskSamplesPointSeq);

    DBCondition ptr_standardChannelRef;
    ptr_standardChannelRef.setName("STANDARDCHANNELREF");
    ptr_standardChannelRef.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(standardChannelRef, ptr_standardChannelRef);

    DBCondition ptr_standardChannelDesc;
    ptr_standardChannelDesc.setName("STANDARDCHANNELDESC");
    ptr_standardChannelDesc.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(standardChannelDesc, ptr_standardChannelDesc);

    DBCondition ptr_standardSamplesValue;
    ptr_standardSamplesValue.setName("STANDARDSAMPLESVALUE");
    ptr_standardSamplesValue.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(standardSamplesValue, ptr_standardSamplesValue);

    DBCondition ptr_standardSamplesPointSeq;
    ptr_standardSamplesPointSeq.setName("STANDARDSAMPLESPOINTSEQ");
    ptr_standardSamplesPointSeq.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(standardSamplesPointSeq, ptr_standardSamplesPointSeq);

    DBCondition ptr_iedFaultType;
    ptr_iedFaultType.setName("IEDFAULTTYPE");
    ptr_iedFaultType.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedFaultType, ptr_iedFaultType);

    DBCondition ptr_iedRanging;
    ptr_iedRanging.setName("IEDRANGING");
    ptr_iedRanging.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedRanging, ptr_iedRanging);

    DBCondition ptr_iedCompFaultType;
    ptr_iedCompFaultType.setName("IEDCOMPFAULTTYPE");
    ptr_iedCompFaultType.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedCompFaultType, ptr_iedCompFaultType);

    DBCondition ptr_iedCompRanging;
    ptr_iedCompRanging.setName("IEDCOMPRANGING");
    ptr_iedCompRanging.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedCompRanging, ptr_iedCompRanging);

    DBCondition ptr_recordTime;
    ptr_recordTime.setName("RECORDTIME");
    ptr_recordTime.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(recordTime, ptr_recordTime);

    DBCondition ptr_ackTip;
    ptr_ackTip.setName("ACKTIP");
    ptr_ackTip.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(ackTip, ptr_ackTip);

    DBCondition ptr_iedTaskType;
    ptr_iedTaskType.setName("IEDTASKTYPE");
    ptr_iedTaskType.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedTaskType, ptr_iedTaskType);

    DBCondition ptr_iedPhase;
    ptr_iedPhase.setName("IEDPHASE");
    ptr_iedPhase.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedPhase, ptr_iedPhase);

    DBCondition ptr_bayName;
    ptr_bayName.setName("BAYNAME");
    ptr_bayName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(bayName, ptr_bayName);

    DBCondition ptr_itemName;
    ptr_itemName.setName("ITEMNAME");
    ptr_itemName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(itemName, ptr_itemName);

    DBCondition ptr_faultInfo;
    ptr_faultInfo.setName("FAULTINFO");
    ptr_faultInfo.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(faultInfo, ptr_faultInfo);

    DBCondition ptr_faultInfoComp;
    ptr_faultInfoComp.setName("FAULTINFOCOMP");
    ptr_faultInfoComp.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(faultInfoComp, ptr_faultInfoComp);

    DBCondition ptr_pointRelativeError;
    ptr_faultInfoComp.setName("POINTRELATIVEERROR");
    ptr_faultInfoComp.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(pointRelativeError, ptr_pointRelativeError);

    DBCondition ptr_pointAbsoluteError;
    ptr_faultInfoComp.setName("POINTABSOLUTEERROR");
    ptr_faultInfoComp.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(pointAbsoluteError, ptr_pointAbsoluteError);

    DBCondition ptr_pointConclusion;
    ptr_faultInfoComp.setName("POINTCONCLUSION");
    ptr_faultInfoComp.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(pointConclusion, ptr_pointConclusion);
}


TransientSwitchTaskConclusionRecordORM::TransientSwitchTaskConclusionRecordORM()
{
    DBCondition ptr_GUID;
    ptr_GUID.setName("GUID");
    ptr_GUID.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(GUID, ptr_GUID);

    DBCondition ptr_IedName;
    ptr_IedName.setName("IEDNAME");
    ptr_IedName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedName, ptr_IedName);

    DBCondition ptr_setType;
    ptr_setType.setName("SETTYPE");
    ptr_setType.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(setType, ptr_setType);

    DBCondition ptr_iedNameComp;
    ptr_iedNameComp.setName("IEDNAMECOMP");
    ptr_iedNameComp.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedNameComp, ptr_iedNameComp);

    DBCondition ptr_setTypeComp;
    ptr_setTypeComp.setName("SETTYPECOMP");
    ptr_setTypeComp.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(setTypeComp, ptr_setTypeComp);

    DBCondition ptr_faultZeroTime;
    ptr_faultZeroTime.setName("FAULTZEROTIME");
    ptr_faultZeroTime.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(faultZeroTime, ptr_faultZeroTime);

    DBCondition ptr_recloseAckDelay;
    ptr_recloseAckDelay.setName("RECLOSEACKDELAY");
    ptr_recloseAckDelay.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(recloseAckDelay, ptr_recloseAckDelay);

    DBCondition ptr_breakerAckDelay;
    ptr_breakerAckDelay.setName("BREAKEACKDELAY");
    ptr_breakerAckDelay.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(breakerAckDelay, ptr_breakerAckDelay);

    DBCondition ptr_srIedAFileName;
    ptr_srIedAFileName.setName("SRIEDAFILENAME");
    ptr_srIedAFileName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(srIedAFileName, ptr_srIedAFileName);

    DBCondition ptr_srIedBFileName;
    ptr_srIedBFileName.setName("SRIEDBFILENAME");
    ptr_srIedBFileName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(srIedBFileName, ptr_srIedBFileName);

    DBCondition ptr_taskFileName;
    ptr_taskFileName.setName("TASKFILENAME");
    ptr_taskFileName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(taskFileName, ptr_taskFileName);

    DBCondition ptr_standardFileName;
    ptr_standardFileName.setName("STANDARDFILENAME");
    ptr_standardFileName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(standardFileName, ptr_standardFileName);

    DBCondition ptr_channelType;
    ptr_channelType.setName("CHANNELTYPE");
    ptr_channelType.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(channelType, ptr_channelType);

    DBCondition ptr_conclusion;
    ptr_conclusion.setName("CONCLUSION");
    ptr_conclusion.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(conclusion, ptr_conclusion);

    DBCondition ptr_reclosingResult;
    ptr_reclosingResult.setName("reclosingResult");
    ptr_reclosingResult.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(reclosingResult, ptr_reclosingResult);

    DBCondition ptr_breakerResult;
    ptr_breakerResult.setName("corrPhaseCurentResult");
    ptr_breakerResult.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(breakerResult, ptr_breakerResult);

    DBCondition ptr_reclosingInnormalTime;
    ptr_reclosingInnormalTime.setName("reclosingInnormalTime");
    ptr_reclosingInnormalTime.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(reclosingInnormalTime, ptr_reclosingInnormalTime);

    DBCondition ptr_reclosingSeriousTime;
    ptr_reclosingSeriousTime.setName("reclosingSeriousTime");
    ptr_reclosingSeriousTime.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(reclosingSeriousTime, ptr_reclosingSeriousTime);

    DBCondition ptr_breakerInnormalTime;
    ptr_breakerInnormalTime.setName("breakerInnormalTime");
    ptr_breakerInnormalTime.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(breakerInnormalTime, ptr_breakerInnormalTime);

    DBCondition ptr_breakerSeriousTime;
    ptr_breakerSeriousTime.setName("breakerSeriousTime");
    ptr_breakerSeriousTime.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(breakerSeriousTime, ptr_breakerSeriousTime);

    DBCondition ptr_taskChannelRef;
    ptr_taskChannelRef.setName("TASKCHANNELREF");
    ptr_taskChannelRef.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(taskChannelRef, ptr_taskChannelRef);

    DBCondition ptr_taskChannelDesc;
    ptr_taskChannelDesc.setName("TASKCHANNELDESC");
    ptr_taskChannelDesc.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(taskChannelDesc, ptr_taskChannelDesc);

    DBCondition ptr_standardChannelRef;
    ptr_standardChannelRef.setName("STANDARDCHANNELREF");
    ptr_standardChannelRef.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(standardChannelRef, ptr_standardChannelRef);

    DBCondition ptr_standardChannelDesc;
    ptr_standardChannelDesc.setName("STANDARDCHANNELDESC");
    ptr_standardChannelDesc.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(standardChannelDesc, ptr_standardChannelDesc);

    DBCondition ptr_recordTime;
    ptr_recordTime.setName("RECORDTIME");
    ptr_recordTime.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(recordTime, ptr_recordTime);

    DBCondition ptr_ackTip;
    ptr_ackTip.setName("ACKTIP");
    ptr_ackTip.setType(DBCondition::DataType::Int);
    m_columnInfo.insert(ackTip, ptr_ackTip);

    DBCondition ptr_iedTaskType;
    ptr_iedTaskType.setName("IEDTASKTYPE");
    ptr_iedTaskType.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedTaskType, ptr_iedTaskType);

    DBCondition ptr_iedPhase;
    ptr_iedPhase.setName("IEDPHASE");
    ptr_iedPhase.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(iedPhase, ptr_iedPhase);

    DBCondition ptr_bayName;
    ptr_bayName.setName("BAYNAME");
    ptr_bayName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(bayName, ptr_bayName);

    DBCondition ptr_itemName;
    ptr_itemName.setName("ITEMNAME");
    ptr_itemName.setType(DBCondition::DataType::Char);
    m_columnInfo.insert(itemName, ptr_itemName);
}
