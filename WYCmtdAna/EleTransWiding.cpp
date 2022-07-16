//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//
//	文 件 名 : EleLine.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 变压器分支
//  备    注 :
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2016-05-10 		创建初始版本
//
//
//////////////////////////////////////////////////////////////////////////

#include "EleTransWiding.h"

CEleTransWiding::CEleTransWiding()
{
    m_eLocation = High;
    m_fVRtg = 220;
    m_fARtg = 1;
    m_nBranNum = 1;

    m_wUaIdx=m_wUbIdx=m_wUcIdx = 0;
    m_wZgapIdx = 0;
    m_wZsgapIdx = 0;
    m_eWGA = wG_Y;
    m_nWGB = 0;
}

CEleTransWiding::~CEleTransWiding()
{
}
