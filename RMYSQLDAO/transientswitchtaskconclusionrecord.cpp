#include "transientswitchtaskconclusionrecord.h"

TransientSwitchTaskConclusionRecord::TransientSwitchTaskConclusionRecord()
    : m_GUID(0)
    , m_reclosingInnormalTime("5ms")
    , m_reclosingSeriousTime("10ms")
    , m_breakerInnormalTime("100ms")
    , m_breakerSeriousTime("150ms")
    , m_taskChannelRef(0)
    , m_standardChannelRef(0)
    , m_ackTip(0)
{

}

TransientSwitchTaskConclusionRecord::~TransientSwitchTaskConclusionRecord()
{

}
