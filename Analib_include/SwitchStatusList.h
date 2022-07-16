//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : SwitchStatusList.h
//	文件类型 : h
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

#if !defined(FRCANA_SWITCHSTATUSLIST_H_)
#define FRCANA_SWITCHSTATUSLIST_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarDef.h"
#include <QVector>

class CSwitchStatus
{
public:
    CSwitchStatus()
    {
        m_nTimePoint = 0;
        m_bStatus = false;
        m_wID = 0;
        memset(m_chName,0,sizeof(m_chName));
    }
    ~CSwitchStatus()
    {
    }
    CSwitchStatus& operator = (const CSwitchStatus& wstatus)
    {
        m_nTimePoint = wstatus.m_nTimePoint;
        m_bStatus = wstatus.m_bStatus;
        m_wID = wstatus.m_wID;
        strcpy(m_chName,wstatus.m_chName);
        return *this;
    }
    bool operator > (const CSwitchStatus& wstatus)
    {
        return m_nTimePoint>wstatus.m_nTimePoint? true:false;
    }
    bool operator < (const CSwitchStatus& wstatus)
    {
        return m_nTimePoint>wstatus.m_nTimePoint? false:true;
    }
public:
    int    m_nTimePoint;		//时间
    bool   m_bStatus;			//状态
    unsigned short   m_wID;				//ID
    char   m_chName[MAX_CHANELNAME_LENGTH];
};

class CSwitchStatusList
{
public:
    CSwitchStatusList();
    virtual ~CSwitchStatusList();

public:
    void AddStatus(int a_nTimePoint,unsigned short a_wID,bool a_bStatus,const char* a_lpstrName);
    void Init();
    QVector<CSwitchStatus> m_arStatus;
};

#endif // !defined(FRCANA_SWITCHSTATUSLIST_H_)
