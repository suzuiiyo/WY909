#ifndef TRANSIENTTASKCONCLUSIONRECORD_H
#define TRANSIENTTASKCONCLUSIONRECORD_H
#include <QSharedPointer>
#include <QString>
#include <QList>
class TransientTaskConclusionRecord
{
public:
    typedef QSharedPointer<TransientTaskConclusionRecord> Ptr;
    typedef QList<Ptr> List;
public:
    TransientTaskConclusionRecord();
    ~TransientTaskConclusionRecord();
public:
    int         GUID() const;
    QString     iedName() const;
    QString     setType() const;
    QString     iedNameComp() const;
    QString     setTypeComp() const;
    QString     protStartTime() const;
    QString     protStartResetTime() const;
    int         protFaultNum() const;
    float       protFaultValue() const;
    QString     srIedAFileName() const;
    QString     srIedBFileName() const;
    int         srTMDataType() const;
    float       srTMDataValue() const;
    float       srTMThreshold() const;
    QString     taskFileName() const;
    QString     standardFileName() const;
    QString     channelType() const;
    QString     conclusion() const;
    QString     abnormalThreshold() const;
    QString     seriousThreshold() const;
    QString     result() const;
    int         taskChannelRef() const;
    QString     taskChannelDesc() const;
    QString     taskSamplesValue() const;
    QString     taskSamplesValuePointSeq() const;
    int         standardChannelRef() const;
    QString     standardChannelDesc() const;
    QString     standardSamplesValue() const;
    QString     standardSamplesPointSeq() const;
    QString     iedFaultType() const;
    QString     iedRanging() const;
    QString     iedCompFaultType() const;
    QString     iedCompRanging() const;
    QString     recordTime() const;
    int         ackTip() const;
    QString     iedTaskType() const;
    QString     iedPhase() const;
    QString     bayName() const;
    QString     itemName() const;
    QString     faultInfo() const;
    QString     faultInfoComp() const;
    QString     pointRelativeError() const;
    QString     pointAbsoluteError() const;
    QString     pointColusion() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setSetType(const QString &setType);
    void setIedNameComp(const QString &iedNameComp);
    void setSetTypeComp(const QString &setTypeComp);
    void setProtStartTime(const QString &protStartTime);
    void setProtStartResetTime(const QString &protStartResetTime);
    void setProtFaultNum(int protFaultNum);
    void setProtFaultValue(float protFaultValue);
    void setSRIedAFileName(const QString &srIedAFileName);
    void setSRIedBFileName(const QString &srIedBFileName);
    void setSRTMDataType(int srTMDataType);
    void setSRTMDataValue(float srTMDataValue);
    void setSRTMThreshold(float srTMThreshold);
    void setTaskFileName(const QString &taskFileName);
    void setStandardFileName(const QString &standardFileName);
    void setChannelType(const QString &channelType);
    void setConclusion(const QString &conclusion);
    void setAbnormalThreshold(const QString &abnormalThreshold);
    void setSeriousThreshold(const QString &seriousThreshold);
    void setResult(const QString &result);
    void setTaskChannelRef(int taskChannelRef);
    void setTaskChannelDesc(const QString &taskChannelDesc);
    void setTaskSamplesValue(const QString &taskSamplesValue);
    void setTaskSamplesPointSeq(const QString &taskSamplesPointSeq);
    void setStandardChannelRef(int standardChannelRef);
    void setStandardChannelDesc(const QString &standardChannelDesc);
    void setStandardSamplesValue(const QString &standardSamplesValue);
    void setStandardSamplesPointSeq(const QString &standardSamplesPointSeq);
    void setIedFaultType(const QString &iedFaultType);
    void setIedRanging(const QString &iedRanging);
    void setIedCompFaultType(const QString &iedCompFaultType);
    void setIedCompRanging(const QString &iedCompRanging);
    void setRecordTime(const QString &recordTime);
    void setAckTip(int ackTip);
    void setIedTaskType(const QString &iedTaskType);
    void setIedPhase(const QString &iedPhase);
    void setBayName(const QString &bayName);
    void setItemName(const QString &itemName);
    void setFaultInfo(const QString &faultInfo);
    void setFaultInfoComp(const QString &faultInfoComp);
    void setPointRelativeError(const QString &pointRelativeError);
    void setPointAbsoluteError(const QString &pointAbsoluteError);
    void setPointConclusion(const QString &pointConclusion);
private:
    int             m_GUID;
    QString         m_iedName;
    QString         m_setType;
    QString         m_iedNameComp;
    QString         m_setTypeComp;
    QString         m_protStartTime;
    QString         m_protStartResetTime;
    int             m_protFaultNum;
    float           m_protFaultValue;
    QString         m_srIedAFileName;
    QString         m_srIedBFileName;
    int             m_srTMDataType;
    float           m_srTMDataValue;
    float           m_srTMThreshold;
    QString         m_taskFileName;
    QString         m_standardFileName;
    QString         m_channelType;
    QString         m_conclusion;
    QString         m_abnormalThreshold;
    QString         m_seriousThreshold;
    QString         m_result;
    int             m_taskChannelRef;
    QString         m_taskChannelDesc;
    QString         m_taskSamplesValue;
    QString         m_taskSamplesPointSeq;
    int             m_standardChannelRef;
    QString         m_standardChannelDesc;
    QString         m_standardSamplesValue;
    QString         m_standardSamplesPointSeq;
    QString         m_iedFaultType;
    QString         m_iedRanging;
    QString         m_iedCompFaultType;
    QString         m_iedCompRanging;
    QString         m_recordTime;
    int             m_ackTip;
    QString         m_iedTaskType;
    QString         m_iedPhase;
    QString         m_bayName;
    QString         m_itemName;
    QString         m_faultInfo;
    QString         m_faultInfoComp;
    QString         m_pointRelativeError;
    QString         m_pointAbsoluteError;
    QString         m_pointConclusion;
private:
    friend class DBTransientTaskConclusionRecordDAO;
};

inline int TransientTaskConclusionRecord::GUID() const
{ return m_GUID;}

inline void TransientTaskConclusionRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString TransientTaskConclusionRecord::iedName() const
{ return m_iedName;}

inline void TransientTaskConclusionRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString TransientTaskConclusionRecord::setType() const
{ return m_setType;}

inline void TransientTaskConclusionRecord::setSetType(const QString &setType)
{ m_setType = setType;}

inline QString TransientTaskConclusionRecord::iedNameComp() const
{ return m_iedNameComp;}

inline void TransientTaskConclusionRecord::setIedNameComp(const QString &iedNameComp)
{ m_iedNameComp = iedNameComp;}

inline QString TransientTaskConclusionRecord::setTypeComp() const
{ return m_setTypeComp;}

inline void TransientTaskConclusionRecord::setSetTypeComp(const QString &setTypeComp)
{ m_setTypeComp = setTypeComp;}

inline QString TransientTaskConclusionRecord::protStartTime() const
{ return m_protStartTime;}

inline void TransientTaskConclusionRecord::setProtStartTime(const QString &protStartTime)
{ m_protStartTime = protStartTime;}

inline QString TransientTaskConclusionRecord::protStartResetTime() const
{ return m_protStartResetTime;}

inline void TransientTaskConclusionRecord::setProtStartResetTime(const QString &protStartResetTime)
{ m_protStartResetTime = protStartResetTime;}

inline int TransientTaskConclusionRecord::protFaultNum() const
{ return m_protFaultNum;}

inline void TransientTaskConclusionRecord::setProtFaultNum(int protFaultNum)
{ m_protFaultNum = protFaultNum;}

inline float TransientTaskConclusionRecord::protFaultValue() const
{ return m_protFaultValue;}

inline void TransientTaskConclusionRecord::setProtFaultValue(float protFaultValue)
{ m_protFaultValue = protFaultValue;}

inline QString TransientTaskConclusionRecord::srIedAFileName() const
{ return m_srIedAFileName;}

inline void TransientTaskConclusionRecord::setSRIedAFileName(const QString &srIedAFileName)
{ m_srIedAFileName = srIedAFileName;}

inline QString TransientTaskConclusionRecord::srIedBFileName() const
{ return m_srIedBFileName;}

inline void TransientTaskConclusionRecord::setSRIedBFileName(const QString &srIedBFileName)
{ m_srIedBFileName = srIedBFileName;}

inline int TransientTaskConclusionRecord::srTMDataType() const
{ return m_srTMDataType;}

inline void TransientTaskConclusionRecord::setSRTMDataType(int srTMDataType)
{ m_srTMDataType = srTMDataType;}

inline float TransientTaskConclusionRecord::srTMDataValue() const
{ return m_srTMDataValue;}

inline void TransientTaskConclusionRecord::setSRTMDataValue(float srTMDataValue)
{ m_srTMDataValue = srTMDataValue;}

inline float TransientTaskConclusionRecord::srTMThreshold() const
{ return m_srTMThreshold;}

inline void TransientTaskConclusionRecord::setSRTMThreshold(float srTMThreshold)
{ m_srTMThreshold = srTMThreshold;}

inline QString TransientTaskConclusionRecord::taskFileName() const
{ return m_taskFileName;}

inline void TransientTaskConclusionRecord::setTaskFileName(const QString &taskFileName)
{ m_taskFileName = taskFileName;}

inline QString TransientTaskConclusionRecord::standardFileName() const
{ return m_standardFileName;}

inline void TransientTaskConclusionRecord::setStandardFileName(const QString &standardFileName)
{ m_standardFileName = standardFileName;}

inline QString TransientTaskConclusionRecord::channelType() const
{ return m_channelType;}

inline void TransientTaskConclusionRecord::setChannelType(const QString &channelType)
{ m_channelType = channelType;}

inline QString TransientTaskConclusionRecord::conclusion() const
{ return m_conclusion;}

inline void TransientTaskConclusionRecord::setConclusion(const QString &conclusion)
{ m_conclusion = conclusion;}

inline QString TransientTaskConclusionRecord::abnormalThreshold() const
{ return m_abnormalThreshold;}

inline void TransientTaskConclusionRecord::setAbnormalThreshold(const QString &abnormalThreshold)
{ m_abnormalThreshold = abnormalThreshold;}

inline QString TransientTaskConclusionRecord::seriousThreshold() const
{ return m_seriousThreshold;}

inline void TransientTaskConclusionRecord::setSeriousThreshold(const QString &seriousThreshold)
{ m_seriousThreshold = seriousThreshold;}

inline QString TransientTaskConclusionRecord::result() const
{ return m_result;}

inline void TransientTaskConclusionRecord::setResult(const QString &result)
{ m_result = result;}

inline int TransientTaskConclusionRecord::taskChannelRef() const
{ return m_taskChannelRef;}

inline void TransientTaskConclusionRecord::setTaskChannelRef(int taskChannelRef)
{ m_taskChannelRef = taskChannelRef;}

inline QString TransientTaskConclusionRecord::taskChannelDesc() const
{ return m_taskChannelDesc;}

inline void TransientTaskConclusionRecord::setTaskChannelDesc(const QString &taskChannelDesc)
{ m_taskChannelDesc = taskChannelDesc;}

inline QString TransientTaskConclusionRecord::taskSamplesValue() const
{ return m_taskSamplesValue;}

inline void TransientTaskConclusionRecord::setTaskSamplesValue(const QString &taskSamplesValue)
{ m_taskSamplesValue = taskSamplesValue;}

inline QString TransientTaskConclusionRecord::taskSamplesValuePointSeq() const
{ return  m_taskSamplesPointSeq;}

inline void TransientTaskConclusionRecord::setTaskSamplesPointSeq(const QString &taskSamplesPointSeq)
{ m_taskSamplesPointSeq = taskSamplesPointSeq;}

inline int TransientTaskConclusionRecord::standardChannelRef() const
{ return m_standardChannelRef;}

inline void TransientTaskConclusionRecord::setStandardChannelRef(int standardChannelRef)
{ m_standardChannelRef = standardChannelRef;}

inline QString TransientTaskConclusionRecord::standardChannelDesc() const
{ return m_standardChannelDesc;}

inline void TransientTaskConclusionRecord::setStandardChannelDesc(const QString &standardChannelDesc)
{ m_standardChannelDesc = standardChannelDesc;}

inline QString TransientTaskConclusionRecord::standardSamplesValue() const
{ return m_standardSamplesValue;}

inline void TransientTaskConclusionRecord::setStandardSamplesValue(const QString &standardSamplesValue)
{ m_standardSamplesValue = standardSamplesValue;}

inline QString TransientTaskConclusionRecord::standardSamplesPointSeq() const
{ return m_standardSamplesPointSeq;}

inline void TransientTaskConclusionRecord::setStandardSamplesPointSeq(const QString &standardSamplesPointSeq)
{ m_standardSamplesPointSeq = standardSamplesPointSeq;}

inline QString TransientTaskConclusionRecord::iedFaultType() const
{ return m_iedFaultType;}

inline void TransientTaskConclusionRecord::setIedFaultType(const QString &iedFaultType)
{ m_iedFaultType = iedFaultType;}

inline QString TransientTaskConclusionRecord::iedRanging() const
{ return m_iedRanging;}

inline void TransientTaskConclusionRecord::setIedRanging(const QString &iedRanging)
{ m_iedRanging = iedRanging;}

inline QString TransientTaskConclusionRecord::iedCompFaultType() const
{ return m_iedCompFaultType;}

inline void TransientTaskConclusionRecord::setIedCompFaultType(const QString &iedCompFaultType)
{ m_iedCompFaultType = iedCompFaultType;}

inline QString TransientTaskConclusionRecord::iedCompRanging() const
{ return m_iedCompRanging;}

inline void TransientTaskConclusionRecord::setIedCompRanging(const QString &iedCompRanging)
{ m_iedCompRanging = iedCompRanging;}

inline QString TransientTaskConclusionRecord::recordTime() const
{ return m_recordTime;}

inline void TransientTaskConclusionRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}

inline int TransientTaskConclusionRecord::ackTip() const
{ return m_ackTip;}

inline void TransientTaskConclusionRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}

inline QString TransientTaskConclusionRecord::iedTaskType() const
{ return m_iedTaskType;}

inline void TransientTaskConclusionRecord::setIedTaskType(const QString &iedTaskType)
{ m_iedTaskType = iedTaskType;}

inline QString TransientTaskConclusionRecord::iedPhase() const
{ return m_iedPhase;}

inline void TransientTaskConclusionRecord::setIedPhase(const QString &iedPhase)
{ m_iedPhase = iedPhase;}

inline QString TransientTaskConclusionRecord::bayName() const
{ return m_bayName;}

inline void TransientTaskConclusionRecord::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString TransientTaskConclusionRecord::itemName() const
{ return m_itemName;}

inline void TransientTaskConclusionRecord::setItemName(const QString &itemName)
{ m_itemName = itemName;}

inline QString TransientTaskConclusionRecord::faultInfo() const
{ return m_faultInfo;}

inline void TransientTaskConclusionRecord::setFaultInfo(const QString &faultInfo)
{ m_faultInfo = faultInfo;}

inline QString TransientTaskConclusionRecord::faultInfoComp() const
{ return m_faultInfoComp;}

inline void TransientTaskConclusionRecord::setFaultInfoComp(const QString &faultInfoComp)
{ m_faultInfoComp = faultInfoComp;}

inline QString TransientTaskConclusionRecord::pointRelativeError() const
{ return m_pointRelativeError;}

inline void TransientTaskConclusionRecord::setPointRelativeError(const QString &pointRelativeError)
{ m_pointRelativeError = pointRelativeError;}

inline QString TransientTaskConclusionRecord::pointAbsoluteError() const
{ return m_pointAbsoluteError;}

inline void TransientTaskConclusionRecord::setPointAbsoluteError(const QString &pointAbsoluteError)
{ m_pointAbsoluteError = pointAbsoluteError;}

inline QString TransientTaskConclusionRecord::pointColusion() const
{ return m_pointConclusion;}

inline void TransientTaskConclusionRecord::setPointConclusion(const QString &pointConclusion)
{ m_pointConclusion = pointConclusion;}
#endif // TRANSIENTTASKCONCLUSIONRECORD_H
