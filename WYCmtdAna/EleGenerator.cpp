////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: EleGenerator
// Copyright 2016 gdwy
// Created : 2016/5/30 by
// History :
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "EleGenerator.h"
#include <memory.h>

CEleGenerator::CEleGenerator()
{
    m_wID = 1;
    memset(m_chName,0,sizeof(m_chName));
    m_wTrmSID = 0;
    m_eType = STEAM_TURBINE;
    m_fFreq = 50;
    m_fCapacity = 5000;
    m_fFactor = 0.9;
    m_fVRtg = 220;
    m_fRotorI = 5;
    m_fRotorV2 = 2;
    m_nNeutGroupNum = 0;
    m_nExciterMode = 0;
    m_nIgtDir = 0;
    m_fUfe = 220;
    m_fXd=m_fXq=m_fXd1=m_fXs = 0;
    m_wIAID=m_wIBID=m_wICID = 0;
    m_eDirA = dir_UNC;
    m_wZAID=m_wZBID=m_wZCID = 0;
    m_eDirZ = dir_UNC;
    m_wUAID=m_wUBID=m_wUCID = 0;
    m_wUfe = 0;
    m_wPosUfe = 0;
    m_wNegUfe = 0;
    m_wIfe = 0;
    m_wACV_Z0 = 0;
    m_wACV_ZZ0 = 0;
    m_wACC_Id0 = 0;
}

CEleGenerator::~CEleGenerator()
{
}
