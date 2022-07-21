//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleDC.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 直流量定义
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

#if !defined(WYANALYZE_ELEDC_H_)
#define WYANALYZE_ELEDC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EleAChanel.h"

class CEleDC
{
public:
    CEleDC();
    virtual ~CEleDC();
    CEleDC& operator=(const CEleDC& a_DC);
public:
    CEleAChanel* m_pChanel;	//对应的模拟通道
    char m_chName[MAX_CHANELNAME_LENGTH];	//通道名称
    char m_chUnit1[MAX_ELEUNIT_LENGTH];		//一次侧单位
    char m_chUnit2[MAX_ELEUNIT_LENGTH];		//二次侧单位
    float m_dFactor;		//转换系数
    unsigned short m_wType;			//类型
    float m_dMaxValue;		//最大值
    char m_chKind[100];		//直流类型

    enum E_ZL_KIND
    {
        ZL_OTHER = 4,		//未知
        ZL_30V_GP = 5,		//高频
        ZL_5V_VOL = 6,		//直流5V电压
        ZL_300V_VOL = 7,	//直流300V电压
        ZL_2000V_VOL = 8,	//直流2000V电压
        ZL_200MV_VOL = 9,	//直流200mV电压
        ZL_4TO20MA_INF = 10,//直流4～20mA电流
        JL_57V_VOL = 11,	//交流57.74V电压
        JL_100V_VOL = 12,	//交流100V电压
        JL_5A_INF = 13,		//交流5A电流
        JL_1A_INF = 14,		//交流1A电流
        ZP_100V_VOL = 15,	//中频100V电压
        ZP_400V_VOL = 16,	//中频400V电压
        ZP_5A_INF = 17,		//中频5A电流
        ZL_PINLV = 18		//频率通道
    };
    int  m_nKind;			//直流类型

    //扩展直流配置
    bool m_bExternDC;		//是否为扩展类型
    float m_dMin_Two;		//变送器二侧最小值(4 mA)
    float m_dMax_Two;		//变送器二侧最大值(20 mA)
    float m_dMax_One;		//变送器一侧最大值(300 A)
    float m_dMin_One;		//变送器一侧最小值(0 A)

    unsigned short m_wID;				//ID
    unsigned short m_wSysID;			//系统编号
    unsigned short m_wChanelID;		//通道号
};

#endif // !defined(AFX_ELEDC_H__1FFAD622_44C9_4EEA_8C4B_1CE881940A4E__INCLUDED_)
