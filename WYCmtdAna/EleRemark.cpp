//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleRemark.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 标签类
//  备    注 : 
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-09-21		创建初始版本
//
//
//
//////////////////////////////////////////////////////////////////////////

#include "EleRemark.h"
#include <memory.h>
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEleRemark::CEleRemark()
{
    memset(m_chContent,0,sizeof(m_chContent));
    m_nCX = 0;
    m_nCY = 0;
    m_nPos = 0;
    m_wChanelId = 0;
    m_bAChanel = true;
    m_rectContent = QRect(0,0,0,0);
}

CEleRemark::~CEleRemark()
{

}

CEleRemark& CEleRemark::operator = (const CEleRemark& a_Remark)
{
    strcpy(m_chContent,a_Remark.m_chContent);
    m_nCX = a_Remark.m_nCX;
    m_nCY = a_Remark.m_nCY;
    m_nPos = a_Remark.m_nPos;
    m_wChanelId = a_Remark.m_wChanelId;
    m_rectContent = a_Remark.m_rectContent;
    m_bAChanel = a_Remark.m_bAChanel;
    return *this;
}
