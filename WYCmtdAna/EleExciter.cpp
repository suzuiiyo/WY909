////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: EleExciter
// Copyright 2016 gdwy
// Created : 2016/5/23 by
// History :
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "EleExciter.h"
#include <memory.h>

CEleExciter::CEleExciter()
{
    m_wIdx = 1;
    memset(m_chName,0,sizeof(m_chName));
    m_wGenSID = 0;
    m_eType = PRIMARY;
    m_fFreq = 50;
    m_fVRtg = 220;
    m_wUaIdx=m_wUbIdx=m_wUcIdx = 0;
    m_wIaIdx=m_wIbIdx=m_wIcIdx = 0;
    m_eDirI = dir_POS;
    m_wZIaIdx=m_wZIbIdx=m_wZIcIdx = 0;
    m_eDirZ = dir_POS;
}

CEleExciter::~CEleExciter()
{
}
