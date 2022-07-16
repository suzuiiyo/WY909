#ifndef DBORM_H
#define DBORM_H
#include <QHash>
#include <QSharedPointer>
#include "dbcondition.h"

class DBOrm
{
public:
    typedef QSharedPointer<DBOrm> Ptr;
public:
    virtual ~DBOrm(){}
public:
    virtual int type() const = 0;
};

class DefaultOrm : public DBOrm
{
public:
    DefaultOrm() : DBOrm() {}
public:
    QHash<int, DBCondition> & columnInfo();
protected:
    QHash<int, DBCondition> m_columnInfo;
};

inline QHash<int, DBCondition> & DefaultOrm::columnInfo()
{ return m_columnInfo;}

class TransientTaskConclusionRecordORM : public DefaultOrm
{
public:
    enum{Type=1};
public:
    TransientTaskConclusionRecordORM();
public:
    enum
    {
        GUID,
        iedName,
        setType,
        iedNameComp,
        setTypeComp,
        protStartTime,
        protStartResetTime,
        protFaultNum,
        protFaultValue,
        srIedAFileName,
        srIedBFileName,
        srTMDataType,
        srTMDataValue,
        srTMThreshold,
        taskFileName,
        standardFileName,
        channelType,
        conclusion,
        abnormalThreshold,
        seriousThreshold,
        result,
        taskChannelRef,
        taskChannelDesc,
        taskSamplesValue,
        taskSamplesPointSeq,
        standardChannelRef,
        standardChannelDesc,
        standardSamplesValue,
        standardSamplesPointSeq,
        iedFaultType,
        iedRanging,
        iedCompFaultType,
        iedCompRanging,
        recordTime,
        ackTip,
        iedTaskType,
        iedPhase,
        bayName,
        itemName,
        faultInfo,
        faultInfoComp,
        pointRelativeError,
        pointAbsoluteError,
        pointConclusion
    };

public:
    virtual int type() const{ return Type;}
//private:
//    QHash<int, DBCondition::Ptr> m_columnInfo;
private:
    friend class DBTransientTaskConclusionRecordDAO;
};

class TransientSwitchTaskConclusionRecordORM : public DefaultOrm
{
public:
    enum{Type=2};
public:
    TransientSwitchTaskConclusionRecordORM();
public:
    enum
    {
        GUID,
        iedName,
        setType,
        iedNameComp,
        setTypeComp,
        faultZeroTime,
        recloseAckDelay,
        breakerAckDelay,
        srIedAFileName,
        srIedBFileName,
        taskFileName,
        standardFileName,
        channelType,
        conclusion,
        reclosingInnormalTime,
        reclosingSeriousTime,
        breakerInnormalTime,
        breakerSeriousTime,
        breakerResult,
        reclosingResult,
        taskChannelRef,
        taskChannelDesc,
        standardChannelRef,
        standardChannelDesc,
        recordTime,
        ackTip,
        iedTaskType,
        iedPhase,
        bayName,
        itemName,
    };

public:
    virtual int type() const{ return Type;}
//private:
//    QHash<int, DBCondition::Ptr> m_columnInfo;
private:
    friend class DBTransientSwitchTaskConclusionRecordDAO;
};

#endif // DBORM_H
