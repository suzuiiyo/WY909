//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleRemark.h
//	文件类型 : h
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

#if !defined(FRCANA_ELEREMARK_H)
#define FRCANA_ELEREMARK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_CONTENT 80
#include <QRect>

class CEleRemark
{
public:
    CEleRemark();
    virtual ~CEleRemark();
    CEleRemark& operator = (const CEleRemark& a_Remark);
public:
    unsigned short m_wChanelId;	//通道ID
    bool m_bAChanel;	//是否为模拟通道
    int  m_nPos;		//位置
    int m_nCX;			//左上角偏移位置
    int m_nCY;			//
    char m_chContent[MAX_CONTENT];	//标签内容
    QRect m_rectContent; //区域
};

#endif // !defined(FRCANA_ELEREMARK_H)
