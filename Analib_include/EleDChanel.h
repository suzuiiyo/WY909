//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleDChanel.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 开关量通道定义
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

#if !defined(AFX_ELEDCHANEL_H__F773C9BF_A1AD_403A_86F6_1499E7C89CDA__INCLUDED_)
#define AFX_ELEDCHANEL_H__F773C9BF_A1AD_403A_86F6_1499E7C89CDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <QVector>
#include "VarDef.h"
#include <QString>

class CEleDChanel
{
public:
    CEleDChanel();
    virtual ~CEleDChanel();
    CEleDChanel& operator=(const CEleDChanel& a_DChanel);
public:
    enum e_type
    {
        Relay = 1,
        Breaker = 2,
        Switch = 3,
        Warning = 4,
        Other = 5
    };

    enum e_flag
    {
        general = 1,
        //type=Relay
        Tr = 2,             //保护跳闸
        TrPhsA = 3,         //
        TrPhsB = 4,
        TrPhsC = 5,
        OpTP = 6,           //三跳
        RecOpCls = 7,       //重合闸
        BlkRec = 8,         //永跳信号
        ProtTx = 9,         //发信
        ProtRv = 10,        //收信

        //type=Breaker
        HWJ = 21,
        TWJ = 22,
        HWJPhsA = 23,
        HWJPhsB = 24,
        HWJPhsC = 25,
        TWJPhsA = 26,
        TWJPhsB = 27,
        TWJPhsC = 28,
        HWJHight = 29,      //变压器高压侧断路器合位
        HWJMedium = 30,
        HWJLow = 31,
        TWJHight = 32,
        TWJMedium = 33,
        TWJLow = 34,
        //type=Warning
        WarnVT = 50,
        WarnCT = 51,
        WarnComm = 52,
        WarnGeneral = 53
    };

    enum e_contact
    {
        NormallyOpen = 1,
        NormallyClosed = 2
    };


    char m_chName[MAX_CHANELNAME_LENGTH];			//通道名称
    unsigned short m_wID;                           //通道ID
//    unsigned short m_wKind;						//类型0:一般,1:A跳,2:B跳,3:C跳,4:三跳,5:重合闸
    bool m_bAct;
    short m_sLineNum;								//连接线路
    unsigned long m_crColor;						//颜色
    QVector<unsigned char> m_pData;					//采样值

    uint m_wIdxOrg;
    QString m_strSrcRef;
    e_type m_eType;
    QString m_strFlag;
    e_contact m_eContact;

    int m_nSWTimes;                     //变位次数(非准确值)
    int m_nCHG;                         //变为次数(准确值)
};

#endif // !defined(AFX_ELEDCHANEL_H__F773C9BF_A1AD_403A_86F6_1499E7C89CDA__INCLUDED_)
