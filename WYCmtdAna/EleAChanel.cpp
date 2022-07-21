//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleAChanel.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 模拟量通道实现
//  备    注 : 
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-06-12		创建初始版本
//
//
//
//////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include "EleAChanel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEleAChanel::CEleAChanel()
{
    m_pData.clear();
    m_bIsSelected = false;
    m_bReverse = false;
    m_bShow = false;
    memset(m_chName,0,sizeof(m_chName));
    memset(m_chUnit1,0,sizeof(m_chUnit1));
    memset(m_chUnit2,0,sizeof(m_chUnit2));
    m_crColor = 0xffffffff;
	m_da = 1.0;
	m_db = 0;
	m_dCT = 120;
	m_dFactor = 1.0;
	m_dMaxAbs = 0;
	m_dPT = 120;
	m_dSkew = 0;
	m_dXFactor = 1.0;
	m_dYFactor = 1.0;
    m_wID = 0;
	m_wPos = 0;
	m_wType = 0;
    m_fPrimary = 0;
    m_fSecondary = 0;
    m_fPMin = 0;
    m_fPMax = 0;
    m_fSMin = 0;
    m_fSMax = 0;
    m_fAU = 1;
    m_fBU = 0;
    m_fFreq = 50;
    m_eType = type_A;
    m_eFlag = flag_ACV;
    m_eSiUnit = unit_unknown;
    m_eMultiplier = multi_unknown;
    m_ePS = ps_S;
    m_wIdxRel = 0;
    m_ePhase = phs_Unc;
}

CEleAChanel::~CEleAChanel()
{
    m_pData.clear();
}
