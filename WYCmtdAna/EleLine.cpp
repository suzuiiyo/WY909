//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//
//	文 件 名 : EleLine.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 线路实现
//  备    注 :
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-06-12		创建初始版本
//ver 2.0       2016-05-10      DMF兼容
//
//
//////////////////////////////////////////////////////////////////////////

#include "EleLine.h"
#include <memory.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEleLine::CEleLine()
{
    m_pAChanel = NULL;
    m_pBChanel = NULL;
    m_pCChanel = NULL;
    m_pNChanel = NULL;
    memset(m_chName,0,sizeof(m_chName));
    m_dCT = 0;
    m_dLength = 20.0;
    m_dMaxI = 5;
    m_dR0 = (float)(0.8);
    m_dR1 = (float)(1.0);
    m_dRh = 0;
    m_dXh = 0;
    m_dX0 = (float)(0.6);
    m_dX1 = (float)(0.5);
    m_nHgLine = -1;
    m_nSwitchCount = 0;
    m_pBus = NULL;
    m_sGp1 = -1;
    m_sGp2 = -1;
    m_wID = 1;
    m_bDistance = true;
    m_wSysID = 0;
    m_wAID = 0;
    m_wBID = 0;
    m_wCID = 0;
    m_wNID = 0;
    m_dVoltage = 220.0;
    m_wBusId = 0;
    m_nBranNum = 1;
    m_fC0=m_fC1 = 0;
    m_fG1=m_fG0 = 0;
    m_fArtg = 5;
    m_wAID2=m_wBID2=m_wCID2=m_wNID2=0;
    m_eDir1 = dir_POS;
    m_eDir2 = dir_POS;
    m_fPx0 = 0;
    m_fPx1 = 0;
    m_arAChanel.clear();
    m_arDChanel.clear();
    m_nFaultVal = 0;
}

CEleLine::~CEleLine()
{

}

CEleLine& CEleLine::operator = (const CEleLine& a_Line)
{
    m_pAChanel = a_Line.m_pAChanel;
    m_pBChanel = a_Line.m_pBChanel;
    m_pCChanel = a_Line.m_pCChanel;
    m_pNChanel = a_Line.m_pNChanel;
    strcpy(m_chName,a_Line.m_chName);
    m_dCT = a_Line.m_dCT;
    m_dLength = a_Line.m_dLength;
    m_dMaxI = a_Line.m_dMaxI;
    m_dR0 = a_Line.m_dR0;
    m_dR1 = a_Line.m_dR1;
    m_dRh = a_Line.m_dRh;
    m_dXh = a_Line.m_dXh;
    m_dX0 = a_Line.m_dX0;
    m_dX1 = a_Line.m_dX1;
    m_nHgLine = a_Line.m_nHgLine;
    m_nSwitchCount = a_Line.m_nSwitchCount;
    m_arDChanel.clear();
    for(int i=0; i<a_Line.m_arDChanel.count(); i++)
    {
        m_arDChanel.append(a_Line.m_arDChanel[i]);
    }
    m_pBus = a_Line.m_pBus;
    m_sGp1 = a_Line.m_sGp1;
    m_sGp2 = a_Line.m_sGp2;
    m_wID = a_Line.m_wID;
    m_bDistance = a_Line.m_bDistance;
    m_wSysID = a_Line.m_wSysID;
    m_wAID = a_Line.m_wAID;
    m_wBID = a_Line.m_wBID;
    m_wCID = a_Line.m_wCID;
    m_wNID = a_Line.m_wNID;
    m_dVoltage = a_Line.m_dVoltage;
    m_wBusId = a_Line.m_wBusId;
    m_fC0 = a_Line.m_fC0;
    m_fC1 = a_Line.m_fC1;
    m_fG0 = a_Line.m_fG0;
    m_fG1 = a_Line.m_fG1;
    m_strSrcRef = a_Line.m_strSrcRef;
    m_nBranNum = a_Line.m_nBranNum;
    m_nFaultVal = a_Line.m_nFaultVal;
    int i = 0;
    for(i=0; i<m_arAChanel.count(); i++)
        m_arAChanel[i] = a_Line.m_arAChanel[i];
    for(i=0; i<m_arDChanel.count(); i++)
        m_arDChanel[i] = a_Line.m_arDChanel[i];
    return *this;
}

bool CEleLine::IsChanel_Full()
{
    if(m_pBus == NULL)
    {
        return false;
    }
    if((m_pBus->m_pAChanel == NULL)||(m_pBus->m_pBChanel == NULL)||(m_pBus->m_pCChanel == NULL)/*||(m_pBus->m_pNChanel == NULL)*/)
    {
        return false;
    }
    if((m_pAChanel == NULL)||/*(m_pBChanel == NULL)||*/(m_pCChanel == NULL)/*||(m_pNChanel == NULL)*/)
    {
        return false;
    }
    return true;
}
