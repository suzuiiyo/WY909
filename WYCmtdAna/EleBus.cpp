//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleBus.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 母线类实现
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

#include "EleBus.h"
#include <memory.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CEleBus::CEleBus()
{
    memset(m_chName,0,sizeof(m_chName));
	strcpy(m_chName,"母线");
	m_dVoltage = 220.0;
	m_pAChanel = NULL;
	m_pBChanel = NULL;
	m_pCChanel = NULL;
	m_pNChanel = NULL;
    m_pLChanel = NULL;
    m_wID = 0;
    m_wAID = 0;
    m_wBID = 0;
    m_wCID = 0;
    m_wNID = 0;
    m_wLID = 0;
    m_wSysID = 0;
    m_eTvPos = e_tv_bus;
    m_wULIdx = 0;
    m_fVrtgSnd = 220;
    m_fVrtg = 220;
}

CEleBus::~CEleBus()
{

}

CEleBus& CEleBus::operator = (const CEleBus& a_Bus)
{
	strcpy(m_chName,a_Bus.m_chName);
	m_dVoltage = a_Bus.m_dVoltage;
	m_pAChanel = a_Bus.m_pAChanel;
	m_pBChanel = a_Bus.m_pBChanel;
	m_pCChanel = a_Bus.m_pCChanel;
	m_pNChanel = a_Bus.m_pNChanel;
    m_wID = a_Bus.m_wID;
    m_wAID = a_Bus.m_wAID;
    m_wBID = a_Bus.m_wBID;
    m_wCID = a_Bus.m_wCID;
    m_wNID = a_Bus.m_wNID;
    m_wSysID = a_Bus.m_wSysID;
    m_eTvPos = a_Bus.m_eTvPos;
    m_arAChanel.clear();
    m_arDChanel.clear();
    int i = 0;
    for(i=0; i<m_arAChanel.count(); i++)
        m_arAChanel[i] = a_Bus.m_arAChanel[i];
    for(i=0; i<m_arDChanel.count(); i++)
        m_arDChanel[i] = a_Bus.m_arDChanel[i];
	return* this;
}
