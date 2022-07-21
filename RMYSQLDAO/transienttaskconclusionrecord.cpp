#include "transienttaskconclusionrecord.h"
TransientTaskConclusionRecord::TransientTaskConclusionRecord()
    : m_GUID(0)
    , m_protFaultNum(0)
    , m_protFaultValue(0)
    , m_srTMDataType(0)
    , m_srTMDataValue(0)
    , m_srTMThreshold(0)
    , m_abnormalThreshold("5%")
    , m_seriousThreshold("10%")
    , m_taskChannelRef(0)
    , m_standardChannelRef(0)
    , m_ackTip(0)
{

}

TransientTaskConclusionRecord::~TransientTaskConclusionRecord()
{

}
