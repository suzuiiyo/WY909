//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleTrans.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 主变定义
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

#if !defined(WYANALYZE_ELETRANS_H_)
#define WYANALYZE_ELETRANS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EleLine.h"
#include "EleTransWiding.h"

class CEleTrans
{
public:
    CEleTrans();
    virtual ~CEleTrans();
    CEleTrans& operator = (const CEleTrans& a_EleTrans);
public:
    enum
    {
        MAX_BRA_COUNT = 4
    };
    int m_nLineCount;		//出线数目
    float m_dDeltaI;		//差流越限启动值(默认为1)
    char m_chName[MAX_CHANELNAME_LENGTH];	//主变名称
    CEleLine* m_pLine[MAX_BRA_COUNT];
    int m_nType[MAX_BRA_COUNT];
    float m_dFactor[MAX_BRA_COUNT];
    float m_dMaxI[MAX_BRA_COUNT];
    bool m_bInvert[MAX_BRA_COUNT];
    unsigned short m_wBraID[MAX_BRA_COUNT];

    unsigned short	m_wID;		//编号
    int   m_nKind;		//=1自耦;=2双绕组;=3三绕组
    float m_dIsd;		//速断电流
    int   m_nPj;		//判据方法 =1南自;=2南瑞;四方
    float m_dIcd;		//差流越限值
    float m_dK1;		//第一段折线斜率
    float m_dK2;		//第二段折线斜率
    float m_dK3;		//第三段折线斜率
    float m_dIr1;		//第一折点对应制流
    float m_dIr2;		//第二折点对应制流
    float m_dIe;		//高压二次侧额定电流

    unsigned short m_wHBraCount;			//高压侧分支数
    unsigned short m_wMBraCount;			//低压侧分支数
    unsigned short m_wLBraCount;			//低压侧分支数
    unsigned short m_wSysID;				//系统内编号

    QString m_strSrcRef;
    float m_fPwrRtg;
    QVector<CEleTransWiding*> m_arWiding;
    QVector<uint> m_arAChanel;
    QVector<uint> m_arDChanel;
};

#endif // !defined(AFX_ELETRANS_H__D739726C_EE17_49CC_9FE0_E3E1E068106C__INCLUDED_)
