//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleAChanel.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 模拟量通道定义
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
#if !defined(WYANALYZE_ELEACHANEL_H_)
#define WYANALYZE_ELEACHANEL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarDef.h"
#include <QVector>
#include <QString>

class CEleAChanel
{
public:
    CEleAChanel();
    virtual ~CEleAChanel();
public:
    enum e_type
    {
        type_A = 1,
        type_D = 2,
        type_O = 3
    };
    enum e_flag
    {
        flag_ACV = 1,           //电压
        flag_ACC = 2,           //电流
        flag_HF = 3,            //高频
        flag_FQ = 4,            //频率
        flag_AG = 5,            //相位
        flag_AMP = 6,           //幅值
        flag_PW = 7,            //功率
        flag_ZX = 8,            //阻抗
        flag_CONST = 9          //常量
    };
    enum e_siunit
    {
        unit_unknown = 0,
        unit_A = 1,
        unit_V = 2,
        unit_Hz = 3,
        unit_O = 4,
        unit_W = 5,
        unit_Var = 6
    };
    enum e_multiplier
    {
        multi_unknown = 0,
        multi_m = 1,
        multi_k = 2,
        multi_M = 3
    };
    enum e_PS
    {
        ps_P = 1,
        ps_S = 2
    };
    enum e_phase
    {
        phs_Ua = 1,
        phs_Ub = 2,
        phs_Uc = 3,
        phs_3U0 = 4,
        phs_Ia = 5,
        phs_Ib = 6,
        phs_Ic = 7,
        phs_3I0 = 8,
        phs_Unc = 9
    };

    char m_chName[MAX_CHANELNAME_LENGTH];	//名称
    unsigned short m_wID;								//ID
    uint m_wIdxOrg;
    uint m_wIdxRel;                         //双AD
    char m_chUnit1[MAX_ELEUNIT_LENGTH];		//一次侧单位
    char m_chUnit2[MAX_ELEUNIT_LENGTH];		//二次侧单位
    float m_da;			//系数a
    float m_db;			//系数b
    float m_dSkew;		//刻度
    float m_dCT;		//CT变比
    float m_dPT;		//PT变比
    float m_dFactor;		//系数
    float m_dMaxAbs;		//最大值
    QVector<float> m_pData;     //采样值
    unsigned short   m_wPos;	//显示位置
    bool   m_bShow;		//是否显示
    bool   m_bIsSelected;	//是否被选中
    bool   m_bReverse;		//是否反相
    float m_dXFactor;		//横向系数
    float m_dYFactor;		//纵向系数
    unsigned short   m_wType;	//电压(1)or电流(2)or直流(3)
    long m_crColor;		//颜色

    //
    QString m_strph;
    QString m_strccbm;
    QString m_struu;
    int m_nmin;
    int m_nmax;
    float m_fPrimary;
    float m_fSecondary;

    float m_fPMin,m_fPMax;
    float m_fSMin,m_fSMax;
    float m_fAU,m_fBU;          //斜率和截距
    float m_fFreq;
    e_type m_eType;
    e_flag m_eFlag;
    e_siunit m_eSiUnit;
    e_multiplier m_eMultiplier;
    e_PS m_ePS;
    QString m_strSrcRef;

    e_phase m_ePhase;
};

#endif // !defined(AFX_ELEACHANEL_H__E3A7FF48_42AA_4F40_85F2_6F624C0C9A04__INCLUDED_)
