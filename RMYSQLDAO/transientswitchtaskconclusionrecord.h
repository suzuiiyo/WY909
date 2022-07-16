#ifndef TRANSIENTSWITCHTASKCONCLUSIONRECORD_H
#define TRANSIENTSWITCHTASKCONCLUSIONRECORD_H
#include <QSharedPointer>
#include <QString>
#include <QList>

class TransientSwitchTaskConclusionRecord
{
public:
    typedef QSharedPointer<TransientSwitchTaskConclusionRecord> Ptr;
    typedef QList<Ptr> List;

public:
    TransientSwitchTaskConclusionRecord();
    ~TransientSwitchTaskConclusionRecord();

public:
    int 	GUID() const;
    QString iedName() const;
    QString setType() const;
    QString iedNameComp() const;
    QString setTypeComp() const;
    QString recloseAckDelay() const;
    QString breakerAckDelay() const;
    QString faultZeroTime() const;
    QString srIedAFileName() const;
    QString srIedBFileName() const;
    QString taskFileName() const;
    QString standardFileName() const;
    QString channelType() const;
    QString conclusion() const;
    QString reclosingInnormalTime() const;
    QString reclosingSeriousTime() const;
    QString breakerInnormalTime() const;
    QString breakerSeriousTime() const;
    QString reclosingResult() const;
    QString breakerResult() const;
    int taskChannelRef() const;
    QString taskChannelDesc() const;
    int standardChannelRef() const;
    QString standardChannelDesc() const;
    QString recordTime() const;
    int ackTip() const;
    QString iedTaskType() const;
    QString iedPhase() const;
    QString bayName();
    QString itemName() const;

public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setSetType(const QString &setType);
    void setIedNameComp(const QString &iedNameComp);
    void setSetTypeComp(const QString &setTypeComp);
    void setRecloseAckDelay(const QString &recloseAckDelay);
    void setBreakerAckDelay(const QString &breakerAckDelay);
    void setFaultZeroTime(const QString &faultZeroTime);
    void setSrIedAFileName(const QString &srIedAFileName);
    void setSrIedBFileName(const QString &srIedBFileName);
    void setTaskFileName(const QString &taskFileName);
    void setStandardFileName(const QString &standardFileName);
    void setChannelType(const QString &channelType);
    void setConclusion(const QString &conclusion);
    void setReclosingInnormalTime(const QString &reclosingInnormalTime);
    void setReclosingSeriousTime(const QString &reclosingSeriousTime);
    void setBreakerInnormalTime(const QString &breakerInnormalTime);
    void setBreakerSeriousTime(const QString &breakerSeriousTime);
    void setReclosingResult(const QString &reclosingResult);
    void setBreakerResult(const QString &breakerResult);
    void setTaskChannelRef(int taskChannelRef);
    void setTaskChannelDesc(const QString &taskChannelDesc);
    void setStandChannelRef(int standChanelRef);
    void setStandChannelDesc(const QString &standardChannelDesc);
    void setRecordTime(const QString &recordTime);
    void setAckTip(int ackTip);
    void setIedTaskType(const QString &iedTaskType);
    void setIedPhase(const QString &iedPhase);
    void setBayName(const QString &bayName);
    void setItemName(const QString &itemName);
private:
    int 			m_GUID;
    QString 		m_iedName;
    QString 		m_setType;
    QString 		m_iedNameComp;
    QString 		m_setTypeComp;
    QString 		m_recloseAckDelay;
    QString 		m_breakerAckDelay;
    QString 		m_faultZeroTime;
    QString 		m_srIedAFileName;
    QString 		m_srIedBFileName;
    QString			m_taskFileName;
    QString 		m_standardFileName;
    QString			m_channelType;
    QString 		m_conclusion;
    QString 		m_reclosingInnormalTime;
    QString 		m_reclosingSeriousTime;
    QString 	    m_breakerInnormalTime;
    QString 		m_breakerSeriousTime;
    QString 		m_breakerResult;
    QString 		m_reclosingResult;
    int 			m_taskChannelRef;
    QString 		m_taskChannelDesc;
    int 			m_standardChannelRef;
    QString 		m_standardChannelDesc;
    QString 		m_recordTime;
    int 			m_ackTip;
    QString 		m_iedTaskType;
    QString 		m_iedPhase;
    QString 		m_bayName;
    QString 		m_itemName;

private:
    friend class DBTransientSwitchTaskConclusionRecordDAO;
};

inline int TransientSwitchTaskConclusionRecord::GUID() const
{ return m_GUID; }

inline void TransientSwitchTaskConclusionRecord::setGUID(int guid)
{ m_GUID = guid; }

inline QString TransientSwitchTaskConclusionRecord::iedName() const
{ return m_iedName; }

inline void TransientSwitchTaskConclusionRecord::setIedName(const QString &iedName)
{ m_iedName = iedName; }

inline QString TransientSwitchTaskConclusionRecord::setType() const
{ return m_setType;}

inline void TransientSwitchTaskConclusionRecord::setSetType(const QString &setType)
{ m_setType = setType; }

inline QString TransientSwitchTaskConclusionRecord::iedNameComp() const
{ return m_iedNameComp; }

inline QString TransientSwitchTaskConclusionRecord::setTypeComp() const
{ return m_setTypeComp; }

inline QString TransientSwitchTaskConclusionRecord::recloseAckDelay() const
{ return m_recloseAckDelay; }

inline QString TransientSwitchTaskConclusionRecord::breakerAckDelay() const
{	return m_breakerAckDelay;}

inline QString TransientSwitchTaskConclusionRecord::faultZeroTime() const
{
    return m_faultZeroTime;
}

inline QString TransientSwitchTaskConclusionRecord::srIedAFileName() const
{	return m_srIedAFileName; }

inline QString TransientSwitchTaskConclusionRecord::srIedBFileName() const
{	return m_srIedBFileName; }

inline QString TransientSwitchTaskConclusionRecord::taskFileName() const
{	return m_taskFileName;  }

inline QString TransientSwitchTaskConclusionRecord::standardFileName() const
{	return m_standardFileName; }

inline QString TransientSwitchTaskConclusionRecord::channelType() const
{	return m_channelType; }

inline QString TransientSwitchTaskConclusionRecord::conclusion() const
{   return m_conclusion; }

inline QString TransientSwitchTaskConclusionRecord::reclosingInnormalTime() const
{
    return m_reclosingInnormalTime;
}

inline QString TransientSwitchTaskConclusionRecord::reclosingSeriousTime() const
{
    return m_reclosingSeriousTime;
}

inline QString TransientSwitchTaskConclusionRecord::breakerInnormalTime() const
{
    return m_breakerInnormalTime;
}

inline QString TransientSwitchTaskConclusionRecord::breakerSeriousTime() const
{
    return m_breakerSeriousTime;
}

inline QString TransientSwitchTaskConclusionRecord::reclosingResult() const
{
    return m_reclosingResult;
}

inline int TransientSwitchTaskConclusionRecord::taskChannelRef() const
{	return m_taskChannelRef; }

inline QString TransientSwitchTaskConclusionRecord::taskChannelDesc() const
{	return m_taskChannelDesc; }

inline int TransientSwitchTaskConclusionRecord::standardChannelRef() const
{	return m_standardChannelRef; }

inline QString TransientSwitchTaskConclusionRecord::standardChannelDesc() const
{	return m_standardChannelDesc; }

inline QString TransientSwitchTaskConclusionRecord::recordTime() const
{	return m_recordTime; }

inline int TransientSwitchTaskConclusionRecord::ackTip() const
{	return m_ackTip;  }

inline QString TransientSwitchTaskConclusionRecord::iedTaskType() const
{	return m_iedTaskType;	}

inline QString TransientSwitchTaskConclusionRecord::iedPhase() const
{	return m_iedPhase;  }

inline QString TransientSwitchTaskConclusionRecord::bayName()
{	return m_bayName; }

inline QString TransientSwitchTaskConclusionRecord::itemName() const
{	return m_itemName; }

inline void TransientSwitchTaskConclusionRecord::setIedNameComp(const QString &iedNameComp)
{  m_iedNameComp = iedNameComp; }

inline void TransientSwitchTaskConclusionRecord::setSetTypeComp(const QString &setTypeComp)
{  m_setType = setTypeComp; }

inline void TransientSwitchTaskConclusionRecord::setRecloseAckDelay(const QString &recloseAckDelay)
{ m_recloseAckDelay = recloseAckDelay; }

inline void TransientSwitchTaskConclusionRecord::setBreakerAckDelay(const QString &breakerAckDelay)
{ m_breakerAckDelay = breakerAckDelay; }

inline void TransientSwitchTaskConclusionRecord::setFaultZeroTime(const QString &faultZeroTime)
{
    m_faultZeroTime = faultZeroTime;
}

inline void TransientSwitchTaskConclusionRecord::setSrIedAFileName(const QString &srIedAFileName)
{ m_srIedAFileName = srIedAFileName; }

inline void TransientSwitchTaskConclusionRecord::setSrIedBFileName(const QString &srIedBFileName)
{ m_srIedBFileName = srIedBFileName; }

inline void TransientSwitchTaskConclusionRecord::setTaskFileName(const QString &taskFileName)
{ m_taskFileName = taskFileName; }

inline void TransientSwitchTaskConclusionRecord::setStandardFileName(const QString &standardFileName)
{ m_standardFileName = standardFileName; }

inline void TransientSwitchTaskConclusionRecord::setChannelType(const QString &channelType)
{ m_channelType = channelType; }

inline void TransientSwitchTaskConclusionRecord::setConclusion(const QString &conclusion)
{ m_conclusion = conclusion; }

inline void TransientSwitchTaskConclusionRecord::setReclosingInnormalTime(const QString &reclosingInnormalTime)
{
  m_reclosingInnormalTime = reclosingInnormalTime;
}

inline void TransientSwitchTaskConclusionRecord::setReclosingSeriousTime(const QString &reclosingSeriousTime)
{
  m_reclosingSeriousTime = reclosingSeriousTime;
}

inline void TransientSwitchTaskConclusionRecord::setBreakerInnormalTime(const QString &breakerInnormalTime)
{
  m_breakerInnormalTime = breakerInnormalTime;
}

inline void TransientSwitchTaskConclusionRecord::setBreakerSeriousTime(const QString &breakerSeriousTime)
{
  m_breakerSeriousTime = breakerSeriousTime;
}

inline void TransientSwitchTaskConclusionRecord::setReclosingResult(const QString &reclosingResult)
{
  m_reclosingResult = reclosingResult;
}

inline void TransientSwitchTaskConclusionRecord::setBreakerResult(const QString &breakerResult)
{
  m_breakerResult = breakerResult;
}

inline void TransientSwitchTaskConclusionRecord::setTaskChannelRef(int taskChannelRef)
{ m_taskChannelRef = taskChannelRef; }

inline void TransientSwitchTaskConclusionRecord::setTaskChannelDesc(const QString &taskChannelDesc)
{
  m_taskChannelDesc = taskChannelDesc;
}

inline void TransientSwitchTaskConclusionRecord::setStandChannelRef(int standardChannelRef)
{
  m_standardChannelRef = standardChannelRef;
}

inline void TransientSwitchTaskConclusionRecord::setStandChannelDesc(const QString &standardChannelDesc)
{
  m_standardChannelDesc = standardChannelDesc;
}

inline void TransientSwitchTaskConclusionRecord::setRecordTime(const QString &recordTime)
{
   m_recordTime = recordTime;
}

inline void TransientSwitchTaskConclusionRecord::setAckTip(int ackTip)
{
   m_ackTip = ackTip;
}

inline void TransientSwitchTaskConclusionRecord::setIedTaskType(const QString &iedTaskType)
{
   m_iedTaskType = iedTaskType;
}

inline void TransientSwitchTaskConclusionRecord::setIedPhase(const QString &iedPhase)
{
   m_iedPhase = iedPhase;
}

inline void TransientSwitchTaskConclusionRecord::setBayName(const QString &bayName)
{
   m_bayName = bayName;
}

inline void TransientSwitchTaskConclusionRecord::setItemName(const QString &itemName)
{
   m_itemName = itemName;
}

#endif // TRANSIENTSWITCHTASKCONCLUSIONRECORD_H
