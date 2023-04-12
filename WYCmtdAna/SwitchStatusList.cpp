//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : SwitchStatusList.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 开关动作时序
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-09-13		创建初始版本
//
//
//
//////////////////////////////////////////////////////////////////////////

#include "SwitchStatusList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSwitchStatusList::CSwitchStatusList()
{
    Init();
}

CSwitchStatusList::~CSwitchStatusList()
{

}

void CSwitchStatusList::Init()
{
    m_arStatus.clear();
}

void CSwitchStatusList::AddStatus(int a_nTimePoint, unsigned short a_wID, bool a_bStatus, const char* a_lpstrName)
{
    CSwitchStatus ws;
    ws.m_nTimePoint = a_nTimePoint;
    ws.m_wID = a_wID;
    ws.m_bStatus = a_bStatus;
    strcpy(ws.m_chName,a_lpstrName);
    if(m_arStatus.count() <= 0)
    {
        m_arStatus.append(ws);
        return;
    }
    for(int i=0; i<m_arStatus.count(); i++)
    {
        if(m_arStatus[i] > ws)
        {
            m_arStatus.insert(i,1,ws);
            return;
        }
    }
    //没有比它大的了,加入尾部
    m_arStatus.append(ws);
}
