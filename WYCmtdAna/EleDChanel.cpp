//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleDChanel.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 开关量通道实现
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

#include "EleDChanel.h"
#include <memory.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEleDChanel::CEleDChanel()
{
    memset(m_chName,0,sizeof(m_chName));
    m_pData.clear();
    m_crColor = 0xffffffff;
    m_sLineNum = -1;
    m_wID = 0;
    m_bAct = false;
    m_wIdxOrg = 0;
    m_eType = Other;
    m_strFlag = QString("general");
    m_eContact = NormallyOpen;
    m_nSWTimes = 0;
    m_nCHG = 0;
}

CEleDChanel::~CEleDChanel()
{
    m_pData.clear();
}

CEleDChanel& CEleDChanel::operator=(const CEleDChanel& a_DChanel)
                                   {
    strcpy(m_chName,a_DChanel.m_chName);
    m_sLineNum = a_DChanel.m_sLineNum;
    m_eType = a_DChanel.m_eType;
    m_strFlag = a_DChanel.m_strFlag;
    m_wID = a_DChanel.m_wID;
    m_crColor = a_DChanel.m_crColor;
    m_bAct = a_DChanel.m_bAct;
    m_nSWTimes = a_DChanel.m_nSWTimes;
    m_nCHG = a_DChanel.m_nCHG;
    return *this;
}
