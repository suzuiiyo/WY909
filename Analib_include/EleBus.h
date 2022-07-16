//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleBus.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 母线定义
//  备    注 : 
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-06-12		创建初始版本
//
//
//ver 1.1       2008-03-28		增加通道ID定义,便于读取分文件
//ver 2.0       2016-05-10      DMF兼容
//////////////////////////////////////////////////////////////////////////

#if !defined(WYANALYZE_ELEBUS_H_)
#define WYANALYZE_ELEBUS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EleAChanel.h"

#include <QVector>

class CEleBus
{
public:
	CEleBus();
	virtual ~CEleBus();
	CEleBus& operator = (const CEleBus& a_Bus);
public:
	char m_chName[MAX_CHANELNAME_LENGTH];		//母线名称
	CEleAChanel* m_pAChanel;					//Ua
	CEleAChanel* m_pBChanel;					//Ub
	CEleAChanel* m_pCChanel;					//Uc
	CEleAChanel* m_pNChanel;					//3U0
    CEleAChanel* m_pLChanel;                    //线电压
    float m_dVoltage;							//电压等级
    unsigned short m_wID;									//ID
    unsigned short m_wAID;								//各相通道号
    unsigned short m_wBID;
    unsigned short m_wCID;
    unsigned short m_wNID;
    unsigned short m_wLID;                      //线电压通道号
    unsigned short m_wSysID;								//系统编号

    unsigned short m_wULIdx;
    QVector<uint> m_arAChanel;                  //相关的独立通道（模拟量）
    QVector<uint> m_arDChanel;                  //相关的开关力量通道

    enum TV_POS
    {
        e_tv_bus = 1,
        e_tv_line = 2
    };
    TV_POS m_eTvPos;                            //TV安装位置
    QString m_strSrcRef;
    float m_fVrtgSnd;
    float m_fVrtg;
};

#endif // !defined(AFX_ELEBUS_H__2EEC46B5_560D_4FCC_B51F_40711E67A256__INCLUDED_)
