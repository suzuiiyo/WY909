//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleTrans.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 主变实现
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

#include "EleTrans.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEleTrans::CEleTrans()
{
    memset(m_chName,0,sizeof(m_chName));
    m_dDeltaI = 0.065;
    for(int i=0; i<MAX_BRA_COUNT; i++)
    {
        m_dFactor[i] = 1.0;
        m_dMaxI[i] = 1;
        m_nType[i] = 0;
        m_pLine[i] = NULL;
        m_bInvert[i] = false;
        m_wBraID[i] = 0;
    }
    m_dIcd = 0.065;
    m_dIr1 = 0.5;
    m_dIr2 = 6;
    m_dIsd = 20.0;
    m_dK1 = (float)(0.2);
    m_dK2 = (float)(0.5);
    m_dK3 = (float)(0.35);
    m_dIe = (float)(3.5);
    m_nKind = 1;
    m_nPj = 1;
    m_wID = 0;
    m_nLineCount = 3;
    m_wHBraCount = 1;
    m_wMBraCount = 1;
    m_wLBraCount = 1;
    m_wSysID = 0;
    m_fPwrRtg = 1000;
}

CEleTrans::~CEleTrans()
{
}

CEleTrans& CEleTrans:: operator = (const CEleTrans& a_EleTrans)
{
    strcpy(m_chName,a_EleTrans.m_chName);
    m_dDeltaI = a_EleTrans.m_dDeltaI;
    for(int i=0; i<MAX_BRA_COUNT; i++)
    {
        m_dFactor[i] = a_EleTrans.m_dFactor[i];
        m_dMaxI[i] = a_EleTrans.m_dMaxI[i];
        m_nType[i] = a_EleTrans.m_nType[i];
        m_pLine[i] = a_EleTrans.m_pLine[i];
        m_bInvert[i] = a_EleTrans.m_bInvert[i];
        m_wBraID[i] = a_EleTrans.m_wBraID[i];
    }
    m_dIcd = a_EleTrans.m_dIcd;
    m_dIr1 = a_EleTrans.m_dIr1;
    m_dIr2 = a_EleTrans.m_dIr2;
    m_dIsd = a_EleTrans.m_dIsd;
    m_dK1 = a_EleTrans.m_dK1;
    m_dK2 = a_EleTrans.m_dK2;
    m_dK3 = a_EleTrans.m_dK3;
    m_nKind = a_EleTrans.m_nKind;
    m_nPj = a_EleTrans.m_nPj;
    m_wID = a_EleTrans.m_wID;
    m_dIe = a_EleTrans.m_dIe;
    m_nLineCount = a_EleTrans.m_nLineCount;
    m_wHBraCount = a_EleTrans.m_wHBraCount;
    m_wMBraCount = a_EleTrans.m_wMBraCount;
    m_wLBraCount = a_EleTrans.m_wLBraCount;
    m_wSysID = a_EleTrans.m_wSysID;
    return *this;
}
