//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : CmtdSegment.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 采样段实现
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
#include "CmtdSegment.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCmtdSegment::CCmtdSegment()
{
	m_nCount = 0;
	m_nWavePoints = 0;
	m_nStartPos = 0;
	m_nSecCount = 0;
}

CCmtdSegment::~CCmtdSegment()
{
}

CCmtdSegment& CCmtdSegment::operator=(const CCmtdSegment& a_Segment)
{
	m_nCount = a_Segment.m_nCount;
	m_nWavePoints = a_Segment.m_nWavePoints;
	m_nStartPos = a_Segment.m_nStartPos;
    m_nSecCount = a_Segment.m_nSecCount;
	return *this;
}
