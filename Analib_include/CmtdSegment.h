//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : CmtdSegment.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 采样段定义
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

#if !defined(FRCANA_CMTDSEGMENT_H_)
#define FRCANA_CMTDSEGMENT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCmtdSegment
{
public:
	CCmtdSegment();
	virtual ~CCmtdSegment();
	CCmtdSegment& operator = (const CCmtdSegment& a_Segment);
public:
	int m_nWavePoints;	//每周波采样点数目
	int m_nCount;		//本段长度
	int m_nStartPos;	//起始点
	int m_nSecCount;	//每秒采样点数目
};

#endif // !defined(FRCANA_CMTDSEGMENT_H_)
