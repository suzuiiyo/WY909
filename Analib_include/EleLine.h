//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : EleLine.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 线路定义
//  备    注 : 
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-06-12		创建初始版本
//ver 2.0       2016-05-10      DMF兼容
//
//
//////////////////////////////////////////////////////////////////////////

#if !defined(WYANALYZE_ELELINE_H_)
#define WYANALYZE_ELELINE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EleAChanel.h"
#include "EleBus.h"

class CEleLine
{
public:
    CEleLine();
    virtual ~CEleLine();
    CEleLine& operator = (const CEleLine& a_Line);
public:
    enum e_dir
    {
        dir_POS = 1,
        dir_NEG = 2,
        dir_UNC = 3
    };

    bool IsChanel_Full();
    char m_chName[MAX_CHANELNAME_LENGTH];		//名称
    CEleAChanel* m_pAChanel;            //A相通道
    CEleAChanel* m_pBChanel;            //B相通道
    CEleAChanel* m_pCChanel;            //C相通道号
    CEleAChanel* m_pNChanel;            //N相通道号
    CEleBus* m_pBus;                    //母线
    float    m_dR1;                     //正序电阻
    float    m_dR0;                     //零序电阻
    float    m_dX1;                     //正序电抗
    float    m_dX0;                     //零序电抗
    float	  m_dCT;                    //CT变比
    float    m_dMaxI;                   //二次侧额定电流
    float    m_dLength;                 //线路长度
    short     m_sGp1;                   //高频1
    short     m_sGp2;                   //高频2
    short	  m_nSwitchCount;           //开关数目
    short     m_nHgLine;                //互感线路ID
    float    m_dRh;                     //互感电阻
    float    m_dXh;                     //互感电抗
    unsigned short	  m_wID;            //编号
    bool      m_bDistance;              //是否测距
    unsigned short      m_wSysID;		//系统编号
    unsigned short      m_wAID;         //各相通道号
    unsigned short      m_wBID;
    unsigned short      m_wCID;
    unsigned short      m_wNID;
    unsigned short      m_wBusId;
    e_dir m_eDir1;

    float    m_dVoltage;                //电压等级
    QString m_strSrcRef;
    int m_nBranNum;                     //分支数目 1：普通线路或3/2接线模式的双开关和电流的接入；2：3/2接线模式的双开关分电流的接入
    float m_fC1,m_fC0;                  //单位电容(uF/km)
    float m_fG1,m_fG0;                  //单位电导(S/km)
    float m_fArtg;
    float m_fPx1;                       //并联电抗器正负序电抗
    float m_fPx0;                       //并联电抗器中性点小电抗

    unsigned short      m_wAID2;         //各相通道号 3/2接线
    unsigned short      m_wBID2;
    unsigned short      m_wCID2;
    unsigned short      m_wNID2;
    e_dir m_eDir2;
    QVector<uint> m_arAChanel;
    QVector<uint> m_arDChanel;

    int m_nFaultVal;                    //判断故障的因子
};

#endif // !defined(AFX_ELELINE_H__E80ECE8A_301C_4D51_8F6F_B83E63BE4509__INCLUDED_)
