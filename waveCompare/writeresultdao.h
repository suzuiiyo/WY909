#ifndef WRITERESULTDAO_H
#define WRITERESULTDAO_H
#include <QString>
#include <QSqlDatabase>
#include "dbtransienttaskconclusionrecorddao.h"

class WriteResultDAO
{
public:
    WriteResultDAO();
    ~WriteResultDAO();

public:
    bool init();
    void setBayName(const QString &);
    void setItemName(const QString &);
    void setItemType(const QString &);
    void setIedName(const QString &);
    void setSetType(const QString &);
    void setPhaseType(const QString &);
    void setIedNameComp(const QString &);
    void setSetTypeComp(const QString &);

    void setprotStartTime(const QString &);
    void setprotStartResetTime(const QString &);
    void setprotFaultNum(int);
    void setprotFaultValue(float);
    
    void setSrIedAFileName(const QString &);
    void setSrIedBFileName(const QString &);
    void setSrTMDataType(int);
    void setSrTMDataValue(float);
    void setSrTMThreshold(float);
    
    void setTaskFileName(const QString &);
    void setStandardFileName(const QString &);
    void setChannelType(const QString &);
    void setConclusion(const QString &);
    void setAbnormalThreshold(const QString &);
    void setSeriousThreshold(const QString &);
    void setResult(const QString &);
    void setTaskChannelRef(int);
    void setTaskChanelDesc(const QString &);
    void setTaskSamplesValue(const QString &);
    void setTaskSamplesPointSeq(const QString &);
    void setStandardChannelRef(int);
    void setStandardChannelDesc(const QString &);
    void setStandardSamplesValue(const QString &);
    void setStandardSamplesPointSeq(const QString &);

    void setIedFaultType(const QString &);
    void setIedFaultInfo(const QString &);
    void setIedFaultInfoCom(const QString &);
    void setIedRanging(const QString &);
    void setIedCompFaultType(const QString &);
    void setIedCompRing(const QString &);
    void setRecordTime(const QString &);

    void setPointRelativeError(const QString&);
    void setPointAbsoluteError(const QString&);
    void setPointColusion(const QString&);

    TransientTaskConclusionRecord::Ptr getTTCR();
    
private:
    TransientTaskConclusionRecord::Ptr ttcr;

};

#endif // WRITERESULTDAO_H
