//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleDC.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 直流量实现
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

#include "EleDC.h"
#include <memory.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEleDC::CEleDC()
{
    memset(m_chName,0,sizeof(m_chName));
    memset(m_chUnit1,0,sizeof(m_chUnit1));
    memset(m_chUnit2,0,sizeof(m_chUnit2));
    memset(m_chKind,0,sizeof(m_chKind));
	m_dFactor = 1.0;
	m_dMaxValue = 0;
	m_pChanel = NULL;
	m_wType = ZL_OTHER;
    m_bExternDC = false;
	m_dMin_Two = 0;
	m_dMax_Two = 20;
	m_dMax_One = 300;
	m_dMin_One = 0;
    m_wID = 0;
    m_wSysID = 0;
    m_wChanelID = 0;
}

CEleDC::~CEleDC()
{

}

CEleDC& CEleDC::operator =(const CEleDC& a_DC)
{
	strcpy(m_chKind,a_DC.m_chKind);
	strcpy(m_chName,a_DC.m_chName);
	strcpy(m_chUnit1,a_DC.m_chUnit1);
	strcpy(m_chUnit2,a_DC.m_chUnit2);
	m_dFactor = a_DC.m_dFactor;
	m_dMaxValue = a_DC.m_dMaxValue;
	m_pChanel = a_DC.m_pChanel;
	m_wType = a_DC.m_wType;
	m_bExternDC = a_DC.m_bExternDC;
	m_dMin_Two = a_DC.m_dMin_Two;
	m_dMax_Two = a_DC.m_dMax_Two;
	m_dMax_One = a_DC.m_dMax_One;
	m_dMin_One = a_DC.m_dMin_One;
    m_wID = a_DC.m_wID;
    m_wSysID = a_DC.m_wSysID;
    m_wChanelID = a_DC.m_wChanelID;
	m_nKind = a_DC.m_nKind;
	return *this;
}
