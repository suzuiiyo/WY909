//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2006 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : WyCal.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 常用计算类定义
//  备    注 : 
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-06-13		创建初始版本
//              2009-10-10      加入计算角度函数(为计算功角)
//
//
//////////////////////////////////////////////////////////////////////////

#if !defined(WYANALYZE_WYCAL_H_)
#define WYANALYZE_WYCAL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "CmtdFile.h"

class CWyCal
{
public:
    CWyCal();
    virtual ~CWyCal();
public:
    //----------------------------------------------------------------------------------------------------------------
    //差流计算相关函数
    //----------------------------------------------------------------------------------------------------------------
    float Cal_Chaliu_A(int a_nNum,float a_pData[12],float a_pFactor[4],int a_pKind[4]);//A相差流
    float Cal_Chaliu_B(int a_nNum,float a_pData[12],float a_pFactor[4],int a_pKind[4]);//B相差流
    float Cal_Chaliu_C(int a_nNum,float a_pData[12],float a_pFactor[4],int a_pKind[4]);//C相差流
//    void  Cal_Factor(int a_nNum,float a_pCT[4],float a_pMaxI[4]);//平衡系数
    float Param_Phase_SI(float* a_pData,int a_nPhase);//Δ1相位修正
    float Param_Phase_SII(float* a_pData,int a_nPhase);//Δ11相位修正
    float Formula_Fun_DeltaId(int a_nPhase, int a_nNum,float* a_pData,float* a_pFactor,int* a_pKind);//计算差流
    //----------------------------------------------------------------------------------------------------------------
    //序分量计算相关函数
    //----------------------------------------------------------------------------------------------------------------
    void Cal_FXFL(float a_dAr,float a_dAx,float a_dBr,float a_dBx,float a_dCr,float a_dCx,float& a_dR2,float& a_dX2,int a_nFlag=0);//计算负序分量
    void Cal_ZXFL(float a_dAr,float a_dAx,float a_dBr,float a_dBx,float a_dCr,float a_dCx,float& a_dR1,float& a_dX1,int a_nFlag=0);//计算正序分量
    void Cal_LXFL(float a_dAr,float a_dAx,float a_dBr,float a_dBx,float a_dCr,float a_dCx,float& a_dR0,float& a_dX0);//计算零序分量
    void Cal_XFL(CCmtdFile* pCmtd,unsigned short usID[],float* a_pAData,float* a_pBData,float* a_pCData,int a_nCurPos,int a_nWavePoints,int a_nFlag,float* a_pData0,float* a_pData1,float* a_pData2);//计算序分量
    //----------------------------------------------------------------------------------------------------------------
    //有效值、谐波计算相关函数
    //----------------------------------------------------------------------------------------------------------------
    float Cal_Rms_Segma(float *a_pData, int a_nWavePoints);
    float Cal_Rms_Result_Sub(float *a_pData, int a_nStartPos, int a_nWavePoints,float& a_dAng,int a_nHarm=1);
    float Cal_Rms_Result(float* a_pData,int a_nStartPos,int a_nWavePoints,float& a_dAng,int a_nHarm=1);                 //计算有效值(各次谐波)
    float Cal_Rms_Result_Ex(float* a_pData,int a_nStartPos,int a_nWavePoints,float& a_dAng);              //高精度计算有效值
    float Cal_True_Rms(float* a_pData,int a_nStartPos,int a_nWavePoints);//计算真有效值(方均根值)
    float DFT_CalHarm(float *a_pData,int a_nWavePoints,float &a_dAng,int a_nHarm,int nstep=1);  //计算谐波
    float DFT_Rms_Ex(float *a_pData,int a_nWavePoints,float &a_dAng);
    float DFT_Rms(float* a_pData,int a_nWavePoints,float& a_dAng);                  //计算有效值
    void  DFT_Rms(float* a_pData,int a_nWavePoints,float& fR,float& fX);            //有效值
    float DFT_CalRms(float *a_pData, int a_nWavePoints, float &a_dAng);
    float Cal_Rms_ZP(float* a_pData,int a_nWavePoints);							//计算中频有效值

    void Filter_Para(int a_nHarm,float* a_pRe,float* a_pIm,int a_nWavePoints);//匹配滤波器
    void Filter_Sub(float* a_pData,float* a_dData,int a_nWaveCount,int a_nHarm);//差分滤波
    float Cal_Ang(float* a_pData,int a_nStartPos,int a_nWavePoints);
    float DFT_Rms_Sub(float* a_pData,int a_nWavePoints,float& a_dAng,int a_nHarm=1);	//差分傅氏算法
    float DFT_CalHarm0_5(float* a_pData,int a_nWavePoints,float& a_dAng,int a_nHarm);//0.5次谐波
    //----------------------------------------------------------------------------------------------------------------
    //自产零序函数
    //----------------------------------------------------------------------------------------------------------------
    void Cal_zichan_lingxv(float* a_pData,float* a_pAData,float* a_pBData,float* a_pCData,int a_nDotCounts);//计算零序
    //----------------------------------------------------------------------------------------------------------------
    //辅助函数
    //----------------------------------------------------------------------------------------------------------------
    int DoubleToInt(float a_dx);//双精度到整型的转换(处理四舍五入)
    //----------------------------------------------------------------------------------------------------------------
    //其他常用函数
    //----------------------------------------------------------------------------------------------------------------
    float Cal_Avg(float* a_pData,int a_nStartPos,int a_nWavePoints);	//计算平均值
    float Cal_Avg(float* a_pData,int a_nPoints);
    float Cal_Junfanggen(float* a_pData, int a_nStart, int a_nEnd);//计算方均根值
    float GetMaxValue(float *a_pData, int a_nStartPos, int a_nWavePoints);
    float GetMaxValue_Ex(float* a_pData, int a_nStartPos,int a_nWavePoints);
    //----------------------------------------------------------------------------------------------------------------
    //计算阻抗
    //----------------------------------------------------------------------------------------------------------------
    int Dist_CalRXEx_PP(float* a_pDataU,float* a_pDataI,float& a_dR,float& a_dX);
    int Dist_CalRX_PG4(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float a_dR0,float a_dR1,float a_dX0,float a_dX1,float& a_dR,float& a_dX);
    void Dist_WaveFilter(float* a_pData,int a_nPoints,int a_nWavePoints,float* a_pParam,int a_nCount,float* a_pResult,bool a_bConvert = false);
    int Dist_CalRX(float* a_pDataU1,float* a_pDataU2,float* a_pDataI1,float* a_pDataI2,float *a_pDataI0,int a_nWavePoints,float a_dRX[4],float& a_dR,float& a_dX,bool a_bPhasePhase = false);
    int Dist_CalRX3(float* a_pDataU1,float* a_pDataU2,float* a_pDataI1,float* a_pDataI2,float *a_pDataI0,int a_nWavePoints,float a_dRX[4],float& a_dR,float& a_dX,bool a_bPhasePhase = false);
    //----------------------------------------------------------------------------------------------------------------
    //计算频率
    //----------------------------------------------------------------------------------------------------------------
    float Dist_CalFreq(float* a_pData,int a_nWavePoints,float a_dFreq);
    float DFT_CalFreq(float *a_pData, int a_nWavePoints, float a_dFreq=50);
    float Freq_Param(float a_fFreq);
    //----------------------------------------------------------------------------------------------------------------
    //计算衰减常数
    //----------------------------------------------------------------------------------------------------------------
    float Cal_DeltaT(float* a_pData,int a_nWavePoints); //计算衰减常数
    float Cal_DeltaT_Ex(float *a_pData, int a_nCalPos, int a_nSegPoints, int a_nWavePoints);    //
    float Cal_DeExcitT(float *a_pData, int a_nSegPoints, int a_nWavePoints);
public:	    
    //-------------------------------------------------------------
    //计算用常量
    //-------------------------------------------------------------
    float m_dsqt2;			//根下2
    float m_dsqt3;			//根下3
private:
    //----------------------------------------------------------------------------------------------------------------
    //计算阻抗用的变量
    //----------------------------------------------------------------------------------------------------------------
    float m_dParam[21];	//滤波参数
    float m_dPI;        //PI
    int    m_nFreq;		//频率
    float m_dUData[50];	//电压数据
    float m_dIData[50];	//电流数据
    float m_dUtmp[50];
    float m_dItmp[50];
    float m_dIn[50];
    //////////////////////////////////////////////////////////////////////////
    //计算用到的中间变量
    float m_dData[200];
    float m_dRe[200];
    float m_dIm[200];

    float m_dRealA;
    float m_dRealB;
    float m_dRealC;
    float m_dImgA;
    float m_dImgB;
    float m_dImgC;
    float m_dRmsA;
    float m_dAngA;
    float m_dRmsB;
    float m_dAngB;
    float m_dRmsC;
    float m_dAngC;

    //计算差流时使用
    float m_pDataI[3];
    float m_pDataII[3];
    float m_pDataIII[3];
    float m_pDataIV[3];

    float m_dTmp;
};

#endif // !defined(WYANALYZE_WYCAL_H_)
