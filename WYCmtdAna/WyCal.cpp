//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2006 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : WyCal.cpp
//	文件类型 : cpp
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 常用计算类实现
//  备    注 : 
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-06-13		创建初始版本
//
//
//
//////////////////////////////////////////////////////////////////////////

#include "WyCal.h"
#include <memory.h>
#include <math.h>
#include "VarDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//static double m_gRealParam[20] = {409.6,389.6,331.4,240.8,126.6,0,-126.6,-240.8,-331.4,-389.6,-409.6,-389.6,-331.4,-240.8,-126.6,0,126.6,240.8,331.4,389.6};
//static double m_gImgParam[20] = {0,126.6,240.8,331.4,389.6,409.6,389.6,331.4,240.8,126.6,0,-126.6,-240.8,-331.4,-389.6,-409.6,-389.6,-331.4,-240.8,-126.6};
static double g_dCos200[200] = {1.0000,0.9995,0.9980,0.9956,0.9921,0.9877,0.9823,0.9759,0.9686,0.9603,0.9511,0.9409,0.9298,0.9178,0.9048,0.8910,0.8763,0.8607,0.8443,0.8271,0.8090,0.7902,0.7705,0.7501,0.7290,0.7071,0.6845,0.6613,0.6374,0.6129,0.5878,0.5621,0.5358,0.5090,0.4818,0.4540,0.4258,0.3971,0.3681,0.3387,0.3090,0.2790,0.2487,0.2181,0.1874,0.1564,0.1253,0.0941,0.0628,0.0314,0.0000,-0.0314,-0.0628,-0.0941,-0.1253,-0.1564,-0.1874,-0.2181,-0.2487,-0.2790,-0.3090,-0.3387,-0.3681,-0.3971,-0.4258,-0.4540,-0.4818,-0.5090,-0.5358,-0.5621,-0.5878,-0.6129,-0.6374,-0.6613,-0.6845,-0.7071,-0.7290,-0.7501,-0.7705,-0.7902,-0.8090,-0.8271,-0.8443,-0.8607,-0.8763,-0.8910,-0.9048,-0.9178,-0.9298,-0.9409,-0.9511,-0.9603,-0.9686,-0.9759,-0.9823,-0.9877,-0.9921,-0.9956,-0.9980,-0.9995,-1.0000,-0.9995,-0.9980,-0.9956,-0.9921,-0.9877,-0.9823,-0.9759,-0.9686,-0.9603,-0.9511,-0.9409,-0.9298,-0.9178,-0.9048,-0.8910,-0.8763,-0.8607,-0.8443,-0.8271,-0.8090,-0.7902,-0.7705,-0.7501,-0.7290,-0.7071,-0.6845,-0.6613,-0.6374,-0.6129,-0.5878,-0.5621,-0.5358,-0.5090,-0.4818,-0.4540,-0.4258,-0.3971,-0.3681,-0.3387,-0.3090,-0.2790,-0.2487,-0.2181,-0.1874,-0.1564,-0.1253,-0.0941,-0.0628,-0.0314,-0.0000,0.0314,0.0628,0.0941,0.1253,0.1564,0.1874,0.2181,0.2487,0.2790,0.3090,0.3387,0.3681,0.3971,0.4258,0.4540,0.4818,0.5090,0.5358,0.5621,0.5878,0.6129,0.6374,0.6613,0.6845,0.7071,0.7290,0.7501,0.7705,0.7902,0.8090,0.8271,0.8443,0.8607,0.8763,0.8910,0.9048,0.9178,0.9298,0.9409,0.9511,0.9603,0.9686,0.9759,0.9823,0.9877,0.9921,0.9956,0.9980,0.9995};
static double g_dSin200[200] = {0.0000,0.0314,0.0628,0.0941,0.1253,0.1564,0.1874,0.2181,0.2487,0.2790,0.3090,0.3387,0.3681,0.3971,0.4258,0.4540,0.4818,0.5090,0.5358,0.5621,0.5878,0.6129,0.6374,0.6613,0.6845,0.7071,0.7290,0.7501,0.7705,0.7902,0.8090,0.8271,0.8443,0.8607,0.8763,0.8910,0.9048,0.9178,0.9298,0.9409,0.9511,0.9603,0.9686,0.9759,0.9823,0.9877,0.9921,0.9956,0.9980,0.9995,1.0000,0.9995,0.9980,0.9956,0.9921,0.9877,0.9823,0.9759,0.9686,0.9603,0.9511,0.9409,0.9298,0.9178,0.9048,0.8910,0.8763,0.8607,0.8443,0.8271,0.8090,0.7902,0.7705,0.7501,0.7290,0.7071,0.6845,0.6613,0.6374,0.6129,0.5878,0.5621,0.5358,0.5090,0.4818,0.4540,0.4258,0.3971,0.3681,0.3387,0.3090,0.2790,0.2487,0.2181,0.1874,0.1564,0.1253,0.0941,0.0628,0.0314,0.0000,-0.0314,-0.0628,-0.0941,-0.1253,-0.1564,-0.1874,-0.2181,-0.2487,-0.2790,-0.3090,-0.3387,-0.3681,-0.3971,-0.4258,-0.4540,-0.4818,-0.5090,-0.5358,-0.5621,-0.5878,-0.6129,-0.6374,-0.6613,-0.6845,-0.7071,-0.7290,-0.7501,-0.7705,-0.7902,-0.8090,-0.8271,-0.8443,-0.8607,-0.8763,-0.8910,-0.9048,-0.9178,-0.9298,-0.9409,-0.9511,-0.9603,-0.9686,-0.9759,-0.9823,-0.9877,-0.9921,-0.9956,-0.9980,-0.9995,-1.0000,-0.9995,-0.9980,-0.9956,-0.9921,-0.9877,-0.9823,-0.9759,-0.9686,-0.9603,-0.9511,-0.9409,-0.9298,-0.9178,-0.9048,-0.8910,-0.8763,-0.8607,-0.8443,-0.8271,-0.8090,-0.7902,-0.7705,-0.7501,-0.7290,-0.7071,-0.6845,-0.6613,-0.6374,-0.6129,-0.5878,-0.5621,-0.5358,-0.5090,-0.4818,-0.4540,-0.4258,-0.3971,-0.3681,-0.3387,-0.3090,-0.2790,-0.2487,-0.2181,-0.1874,-0.1564,-0.1253,-0.0941,-0.0628,-0.0314,};
static double g_dPI = 3.1415926;
CWyCal::CWyCal()
{
    int i = 0;
    m_dsqt2 = (float)(sqrt(2));
    m_dsqt3 = (float)(sqrt(3));
    for(i=0; i<200; i++)
    {
        m_dRe[i] = 0;
        m_dIm[i] = 0;
    }

    for(i=0; i<3; i++)
    {
        m_pDataI[i] = 0;
        m_pDataII[i] = 0;
        m_pDataIII[i] = 0;
        m_pDataIV[i] = 0;
    }

    m_dPI = (float)(3.1415926);
    m_nFreq = 50;
    m_dParam[0] = (float)(0.05);
    m_dParam[1] = (float)(0.0951);
    m_dParam[2] = (float)(0.0809);
    m_dParam[3] = (float)(0.0588);
    m_dParam[4] = (float)(0.0309);
    m_dParam[5] = 0;
    m_dParam[6] = (float)(-0.0309);
    m_dParam[7] = (float)(-0.0588);
    m_dParam[8] = (float)(-0.0809);
    m_dParam[9] = (float)(-0.0951);
    m_dParam[10] = (float)(-0.1);
    m_dParam[11] = (float)(-0.0951);
    m_dParam[12] = (float)(-0.0809);
    m_dParam[13] = (float)(-0.0588);
    m_dParam[14] = (float)(-0.0309);
    m_dParam[15] = 0;
    m_dParam[16] = (float)(0.0309);
    m_dParam[17] = (float)(0.0588);
    m_dParam[18] = (float)(0.0809);
    m_dParam[19] = (float)(0.0951);
    m_dParam[20] = (float)(0.05);

    memset(m_dUData,0,sizeof(m_dUData));
    memset(m_dIData,0,sizeof(m_dIData));
    memset(m_dUtmp,0,sizeof(m_dUtmp));
    memset(m_dItmp,0,sizeof(m_dItmp));
    memset(m_dIn,0,sizeof(m_dIn));

    //	float dang = atan2(-0.9094,-0.7217);
    //	float dx = dang/m_dPI * 180;
}

CWyCal::~CWyCal()
{

}

//////////////////////////////////////////////////////////////////////////
//功	能: 差分滤波 i(k)' = [i(k)-i(k-1)]/[2*sin(n*pi/N)]		   
//			分母为修正系数		n:谐波次数  N:采样率
//参	数: 
//			a_pData 源数据
//			a_dData	输出结果
//			a_nWaveCount 每周波采样点个数
//			a_nHarm	谐波次数
//返 回	值:
//备	注:
//创建日期: 2007-02-13  wangpengfei
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CWyCal::Filter_Sub(float *a_pData, float *a_dData, int a_nWaveCount, int a_nHarm)
{
    a_dData[0] = a_pData[0];
    for(int i=1; i<a_nWaveCount; i++)
    {
        a_dData[i] = (float)((a_pData[i]-a_pData[i-1])/(2.*sin(a_nHarm*g_dPI/a_nWaveCount)));
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 20点DFT变换,计算有效值
//参	数: 
//			a_pData 输入数据数据
//返 回	值: 返回有效值
//备	注:
//创建日期: 2007-02-13  wangpengfei
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::DFT_Rms(float* a_pData,int a_nWavePoints,float& a_dAng)
{
    float drms = 0.0;
    if(a_nWavePoints < 20)
    {
        for(int i=0; i<a_nWavePoints; i++)
        {
            if(drms < fabs(a_pData[i]))
                drms = (float)(fabs(a_pData[i]));
        }
        drms /= m_dsqt2;
        return drms;
    }

    /*
	float dreal = 0.0;
	float dimg = 0.0;
	int nsg = a_nWavePoints*50/1000;
	for(int i=0; i<20; i++)
	{
		dreal += a_pData[i*nsg]*m_gRealParam[20-i-1];
		dimg += a_pData[i*nsg]*m_gImgParam[20-i-1];
	}
        a_dAng = atan2(dimg,dreal) + g_dPI/2.0;
	if(a_dAng < 0.0000001)
	{
                a_dAng += 2.0*g_dPI;
	}
	dreal /= 4096.0;
	dimg /= 4096.0;
	drms = sqrt(dreal*dreal+dimg*dimg);
	drms /= m_dsqt2;
	*/
    drms = DFT_CalHarm(a_pData,a_nWavePoints,a_dAng,1);
    return drms;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 傅氏算法,计算谐波
//参	数: 
//			a_pData			输入数据数据
//			a_nWavePoints	每周波采样点数
//			a_nHarm			谐波次数
//			a_dAng			相位
//返 回	值: 
//备	注:
//公式: r =  2/N * [Segma_1_n(x[k]*cos(nk*2*pi/N))];
//      x = -2/N * [Segma_1_n(x[k]*sin(nk*2*pi/N))];
//创建日期: 2007-02-26  wpf
//修改记录: 
//			2009-10-10		修改谐波算法，采用基本公式计算
//          2018-08-29      增加步进（跳点计算,10k修正）
//////////////////////////////////////////////////////////////////////////
float CWyCal::DFT_CalHarm(float *a_pData, int a_nWavePoints, float &a_dAng, int a_nHarm,int nstep/*=1*/)
{
    float dRms = 0;
    //计算谐波
    if(a_nWavePoints < 20)
    {
        dRms = 0;
        a_dAng = 0;
        return dRms;
    }
    float segmaa = 0.0;
    float segmab = 0.0;
    //////////////////////////////////////////////////////////////////////////
    //2009-10-10 修改
    /*
	Filter_Para(a_nHarm,m_dRe,m_dIm,a_nWavePoints);
	for(int i=0; i<a_nWavePoints; i++)
	{
	segmaa += a_pData[i] * m_dRe[a_nWavePoints-i-1];
	segmab += a_pData[i] * m_dIm[a_nWavePoints-i-1];
	}
	dRms = sqrt(segmaa*segmaa + segmab*segmab);
	dRms /= m_dsqt2;
	a_dAng = atan2(segmab,segmaa);
	*/
    a_nWavePoints /= nstep;
    for(int i=0; i<a_nWavePoints*nstep; i+=nstep)
    {
        segmaa += (float)(a_pData[i] * cos(a_nHarm*(i/nstep)*2.0*g_dPI/(float)(a_nWavePoints)));
        segmab += (float)(a_pData[i] * sin(a_nHarm*(i/nstep)*2.0*g_dPI/(float)(a_nWavePoints)));
    }
    dRms = (float)(sqrt(segmaa*segmaa + segmab*segmab)/m_dsqt2/((float)a_nWavePoints/2.0));
    a_dAng = (float)(atan2(-segmab,segmaa));
    a_dAng += (float)(g_dPI/2.0);
    //	TRACE("%.2f\n",a_dAng*180.0/g_dPI);
    return dRms;
}

float CWyCal::DFT_Rms_Ex(float *a_pData, int a_nWavePoints, float &a_dAng)
{
    double dRms = 0;
    //计算谐波
    if(a_nWavePoints < 20)
    {
        dRms = 0;
        a_dAng = 0;
        return dRms;
    }

    float freq = Dist_CalFreq(a_pData,a_nWavePoints,50);
    freq = Freq_Param(freq);
//    int nind = (int)(freq*100-3900);
//    nind = 100;
//    if((nind<0)||(nind>1700))
//    {
//        return DFT_CalHarm(a_pData,a_nWavePoints,a_dAng,1);
//    }

    double segmaa = 0.0;
    double segmab = 0.0;
    a_nWavePoints = (int)(a_nWavePoints*50/freq+0.5);
    for(int i=0; i<a_nWavePoints; i++)
    {
        segmaa += (double)(a_pData[i] * cos(i*2.0*g_dPI/(double)(a_nWavePoints)));
        segmab += (double)(a_pData[i] * sin(i*2.0*g_dPI/(double)(a_nWavePoints)));
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////
//    矢量补偿算法
//[[
//    for(int i=1; i<a_nWavePoints; i++)
//    {
//        segmaa += (double)(a_pData[i] * cos(i*2.0*g_dPI/(double)(a_nWavePoints)));
//    }
//    segmaa += (a_pData[0]+a_pData[a_nWavePoints])/a_nWavePoints/2;
//    for(int i=1; i<a_nWavePoints+1; i++)
//    {
//        segmab += (double)(a_pData[i] * sin(i*2.0*g_dPI/(double)(a_nWavePoints)));
//    }
//    const double f230 = pow(2,30);
//    segmab *= adj_freq_mod[nind][0]/f230;
//    segmaa *= adj_freq_mod[nind][1]/f230;
//]]

    dRms = (double)(sqrt(segmaa*segmaa + segmab*segmab)/m_dsqt2/((double)a_nWavePoints/2.0));
    a_dAng = (double)(atan2(-segmab,segmaa));
    a_dAng += (double)(g_dPI/2.0);
//    qDebug("a=%.5f b=%.5f rmsb=%.5f",segmaa,segmab,dRms);
//    qDebug("rmsdd = %.5f\n",dRms);
    return (float)dRms;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算有效值
//参	数:
//			a_pData			输入数据数据
//			a_nWavePoints	每周波采样点数
//返 回	值: 返回有效值
//备	注:
//创建日期: 2007-03-01  wpf
//修改记录:
//////////////////////////////////////////////////////////////////////////
void CWyCal::DFT_Rms(float* a_pData,int a_nWavePoints,float& fR,float& fX)
{
    //计算谐波
    if(a_nWavePoints < 20)
    {
        fR = 0;
        fX = 0;
        return;
    }
    float dRms,dAng;
    dRms = DFT_CalHarm(a_pData,a_nWavePoints,dAng,1);
    fR = (float)(dRms*cos(dAng));
    fX = (float)(dRms*sin(dAng));
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算真有效值(取20点计算均方根和)
//参	数: 
//			a_pData			输入数据数据
//			a_nStartPoint	计算起始点
//			a_nWavePoints	每周波采样点数
//返 回	值: 返回有效值
//备	注:
//创建日期: 2007-03-01  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_True_Rms(float *a_pData, int a_nStartPos, int a_nWavePoints)
{
    float drms = 0.0;
    int nsg = a_nWavePoints/20;
    if(nsg < 1)
    {
        for(int i=0; i<a_nWavePoints; i++)
        {
            if(drms < fabs(a_pData[a_nStartPos+i]))
                drms = (float)(fabs(a_pData[a_nStartPos+i]));
        }
        drms /= m_dsqt2;
        return drms;
    }
    float segma = 0.0;
    for(int i=0; i<20; i++)
    {
        segma += (float)(fabs(a_pData[a_nStartPos+i*nsg]*a_pData[a_nStartPos+i*nsg]));
    }
    segma /= 20;
    drms = (float)(sqrt(segma));
    return drms;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算自产零序
//参	数: 
//			a_pData			计算结果
//			a_pAData		A相数据
//			a_pBData		B相数据
//			a_pCData		C相数据
//			a_nDotCounts	点个数
//返 回	值: 
//备	注:
//创建日期: 2007-03-20		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CWyCal::Cal_zichan_lingxv(float *a_pData, float *a_pAData, float *a_pBData, float *a_pCData, int a_nDotCounts)
{
    for(int i=0; i<a_nDotCounts; i++)
    {
        a_pData[i] = a_pAData[i]+a_pBData[i]+a_pCData[i];
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 匹配滤波器
//参	数: 
//			a_nHarm			谐波次数
//			a_pRe			参数的实部
//			a_pIm			参数的虚部
//			a_nWavePoints	每周波点个数
//返 回	值: 
//备	注:
//创建日期: 2007-03-22		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CWyCal::Filter_Para(int a_nHarm, float *a_pRe, float *a_pIm, int a_nWavePoints)
{
    int i = 0;
    float fi = 0.0;
    int dotNum = a_nWavePoints/20;
    for(i=0; i<a_nWavePoints; i++)
    {
        fi = (float)(g_dPI/180.0*(18.0*a_nHarm/dotNum)*i);
        a_pRe[i] = (float)(cos(fi)/10.0/dotNum);
        a_pIm[i] = (float)(sin(fi)/10.0/dotNum);
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 数值类型转换(float to int)
//参	数: 
//				a_dx		实数
//返 回	值:		整数(实现四舍五入)
//备	注:
//创建日期: 2007-03-22		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int CWyCal::DoubleToInt(float a_dx)
{
    return (int)(a_dx+0.5001);
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算序分量
//参	数: 
//			a_pAData			A相数据
//			a_pBData			B相数据
//			a_pCData			B相数据
//			a_nCurPos			计算开始点
//			a_nWavePoints		每周波点个数
//			a_nFlag				特殊相, = 0 A相为特殊相
//									   = 1 B相为特殊相
//									   = 2 C相为特殊相
//			a_pData0[2]			零序分量,实部、虚部	
//			a_pData1[2]			正序分量,实部、虚部	
//			a_pData2[2]			负序分量,实部、虚部			
//返 回	值: 
//备	注:
//创建日期: 2007-03-22		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CWyCal::Cal_XFL(CCmtdFile* pCmtd,unsigned short usID[],float *a_pAData, float *a_pBData, float *a_pCData,
                     int a_nCurPos, int a_nWavePoints, int a_nFlag, float *a_pData0, float *a_pData1, float *a_pData2)
{
    //先计算三相的实部和虚部
    m_dRmsA = DFT_Rms(a_pAData+a_nCurPos,a_nWavePoints,m_dAngA);
    pCmtd->ParamPhase(usID[0],m_dAngA);
    m_dRealA = (float)(m_dRmsA * cos(m_dAngA));
    m_dImgA = (float)(m_dRmsA * sin(m_dAngA));
    m_dRmsB = DFT_Rms(a_pBData+a_nCurPos,a_nWavePoints,m_dAngB);
    pCmtd->ParamPhase(usID[1],m_dAngB);
    m_dRealB = (float)(m_dRmsB * cos(m_dAngB));
    m_dImgB = (float)(m_dRmsB * sin(m_dAngB));
    m_dRmsC = DFT_Rms(a_pCData+a_nCurPos,a_nWavePoints,m_dAngC);
    pCmtd->ParamPhase(usID[2],m_dAngC);
    m_dRealC = (float)(m_dRmsC * cos(m_dAngC));
    m_dImgC = (float)(m_dRmsC * sin(m_dAngC));
    //调用函数计算序分量
    Cal_LXFL(m_dRealA,m_dImgA,m_dRealB,m_dImgB,m_dRealC,m_dImgC,a_pData0[0],a_pData0[1]);
    Cal_ZXFL(m_dRealA,m_dImgA,m_dRealB,m_dImgB,m_dRealC,m_dImgC,a_pData1[0],a_pData1[1],a_nFlag);
    Cal_FXFL(m_dRealA,m_dImgA,m_dRealB,m_dImgB,m_dRealC,m_dImgC,a_pData2[0],a_pData2[1],a_nFlag);
}


//////////////////////////////////////////////////////////////////////////
//功	能: 计算零序分量
//参	数: 
//			a_dAr				A相实部
//			a_dAx				A相虚部
//			a_dBr				B相实部
//			a_dBx				B相虚部
//			a_dCr				C相实部
//			a_dCx				C相虚部
//			a_dR0				零序分量实部
//			a_dX0				零序分量虚部		
//返 回	值: 
//备	注:
//创建日期: 2007-03-27		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CWyCal::Cal_LXFL(float a_dAr, float a_dAx, float a_dBr, float a_dBx, 
                      float a_dCr, float a_dCx, float &a_dR0, float &a_dX0)
{
    a_dR0 = (float)((a_dAr + a_dBr + a_dCr)/3.);
    a_dX0 = (float)((a_dAx + a_dBx + a_dCx)/3.);
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算正序分量
//参	数: 
//			a_dAr				A相实部
//			a_dAx				A相虚部
//			a_dBr				B相实部
//			a_dBx				B相虚部
//			a_dCr				C相实部
//			a_dCx				C相虚部
//			a_dR1				正序分量实部
//			a_dX1				正序分量虚部
//			a_nFlag				特殊相, =0 A; =1 B; =2 C;		
//返 回	值: 
//说	明:
//备	注:
//创建日期: 2007-03-27		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CWyCal::Cal_ZXFL(float a_dAr, float a_dAx, float a_dBr, float a_dBx, 
                      float a_dCr, float a_dCx, float &a_dR1, float &a_dX1, int a_nFlag/*=0*/)
{
    a_dR1 = (float)((a_dAr - 0.5*(a_dBr+a_dCr) - 0.866*(a_dBx-a_dCx))/3.0);
    a_dX1 = (float)((a_dAx - 0.5*(a_dBx+a_dCx) + 0.866*(a_dBr-a_dCr))/3.0);
    if(a_nFlag == 0)
    {
        return;
    }
    float dFa1r = 0.0;
    float dFa1x = 0.0;
    if(a_nFlag == 1)		//B为特殊相
    {
        dFa1r = a_dR1;
        dFa1x = a_dX1;
        a_dR1 = -dFa1r/2 + dFa1x * m_dsqt3/2;
        a_dX1 = -dFa1x/2 - dFa1r * m_dsqt3/2;
    }
    else if(a_nFlag == 2)	//C为特殊相
    {
        dFa1r = a_dR1;
        dFa1x = a_dX1;
        a_dR1 = -dFa1r - dFa1x * m_dsqt3/2;
        a_dX1 = -dFa1x + dFa1r * m_dsqt3/2;
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算负序分量
//参	数: 
//			a_dAr				A相实部
//			a_dAx				A相虚部
//			a_dBr				B相实部
//			a_dBx				B相虚部
//			a_dCr				C相实部
//			a_dCx				C相虚部
//			a_dR2				负序分量实部
//			a_dX2				负序分量虚部
//			a_nFlag				特殊相, =0 A; =1 B; =2 C;		
//返 回	值: 
//备	注:
//创建日期: 2007-03-27		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CWyCal::Cal_FXFL(float a_dAr, float a_dAx, float a_dBr, float a_dBx, float a_dCr, float a_dCx, float &a_dR2, float &a_dX2, int a_nFlag)
{
    a_dR2 = (float)((a_dAr - 0.5*(a_dBr+a_dCr) + 0.866*(a_dBx-a_dCx))/3.0);
    a_dX2 = (float)((a_dAx - 0.5*(a_dBx+a_dCx) - 0.866*(a_dBr-a_dCr))/3.0);
    if(a_nFlag == 0)
    {
        return;
    }
    float dFa2r = 0.0;
    float dFa2x = 0.0;
    if(a_nFlag == 1)	//B为特殊相
    {
        dFa2r = a_dR2;
        dFa2x = a_dX2;
        a_dR2 = (float)(-dFa2r - dFa2x * m_dsqt3/2.);
        a_dX2 = (float)(-dFa2x + dFa2r * m_dsqt3/2.);
    }
    else if(a_nFlag == 2)//C为特殊相
    {
        dFa2r = a_dR2;
        dFa2x = a_dX2;
        a_dR2 = (float)(-dFa2r + dFa2x * m_dsqt3/2.);
        a_dX2 = (float)(-dFa2x - dFa2r * m_dsqt3/2.);
    }
}


//////////////////////////////////////////////////////////////////////////
//功	能: Δ11相位修正
//参	数: 
//			a_pData				A、B、C三相数据
//			a_nPhase			要修正的相		
//返 回	值: 修正结果
//备	注:
//创建日期: 2007-04-09		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::Param_Phase_SII(float *a_pData, int a_nPhase)
{
    float dres = 0.0;
    if(a_nPhase == 0)//A相
    {
        dres = (a_pData[0] - a_pData[2])/m_dsqt3;
    }
    else if(a_nPhase == 1)//B相
    {
        dres = (a_pData[1] - a_pData[0])/m_dsqt3;
    }
    else if(a_nPhase == 2)//C相
    {
        dres = (a_pData[2] - a_pData[1])/m_dsqt3;
    }
    return dres;
}

//////////////////////////////////////////////////////////////////////////
//功	能: Δ1相位修正
//参	数: 
//			a_pData				A、B、C三相数据
//			a_nPhase			要修正的相		
//返 回	值: 修正结果
//备	注:
//创建日期: 2007-04-09		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::Param_Phase_SI(float *a_pData, int a_nPhase)
{
    float dres = 0.0;
    if(a_nPhase == 0)		//A相
    {
        dres = (a_pData[0] - a_pData[1])/m_dsqt3;
    }
    else if(a_nPhase == 1)	//B相
    {
        dres = (a_pData[1] - a_pData[2])/m_dsqt3;
    }
    else if(a_nPhase == 2)	//C相
    {
        dres = (a_pData[2] - a_pData[0])/m_dsqt3;
    }
    return dres;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算平衡系数
//参	数: 
//			a_pCT				四侧的CT变比
//			a_pMaxI				四侧的额定电流
//			a_bIII				是否有III侧
//			a_bIb				是否有IV侧		
//返 回	值: 修正结果
//备	注:
//创建日期: 2007-04-09		wpf
//修改记录: 
//			2007-07-17		wpf		把是否有III,IV侧的判断改为侧数
//			2007-10-18		wpf		平衡系数错误
//////////////////////////////////////////////////////////////////////////
//void CWyCal::Cal_Factor(int a_nNum, float a_pCT[], float a_pMaxI[])
//{
//    float dFactorII;
//    float dFactorIII;
//    float dFactorIV;
//    dFactorII = (a_pMaxI[1]*a_pCT[1])/(a_pMaxI[0]*a_pCT[0]);
//    dFactorIII = 1;
//    dFactorIV = 1;
//    if(a_nNum > 2)
//    {
//        dFactorIII = (a_pMaxI[2]*a_pCT[2])/(a_pMaxI[0]*a_pCT[0]);
//    }
//    else
//    {
//        dFactorIII = 1.0;
//    }
//    if(a_nNum > 3)
//    {
//        dFactorIV = (a_pMaxI[3]*a_pCT[3])/(a_pMaxI[0]*a_pCT[0]);
//    }
//    else
//    {
//        dFactorIV = 1.0;
//    }
//}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算A相差流
//参	数: 
//			a_nNum				侧数
//			a_pData				各侧数据
//			a_pFactor			平衡系数
//			a_pKind				各侧的接线方式	
//返 回	值: A相差流
//备	注:	调用此函数前先计算平衡系数,然后修正相位(Δ—>Y),最后各侧相加
//创建日期: 2007-04-09		wpf
//修改记录: 2007-07-17		wpf		把是否有III,IV侧的判断改为侧数
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_Chaliu_A(int a_nNum, float a_pData[], float a_pFactor[], int a_pKind[])
{
    //////////////////////////////////////////////////////////////////////////
    //I侧相位修正
    float dres = 0;
    if(a_pKind[0] == 2)		//I侧接线方式为Δ11
    {
        m_pDataI[0] = Param_Phase_SII(a_pData,0);
    }
    else if(a_pKind[0] == 3)//Δ1
    {
        m_pDataI[0] = Param_Phase_SI(a_pData,0);
    }
    else
    {
        m_pDataI[0] = a_pData[0];
    }

    //////////////////////////////////////////////////////////////////////////
    //II侧相位修正
    if(a_pKind[1] == 2)
    {
        m_pDataII[0] = Param_Phase_SII(a_pData+3,0);
    }
    else if(a_pKind[1] == 3)
    {
        m_pDataII[0] = Param_Phase_SI(a_pData+3,0);
    }
    else
    {
        m_pDataII[0] = a_pData[3];
    }
    m_pDataII[0] *= a_pFactor[1];

    //////////////////////////////////////////////////////////////////////////
    //如果有III侧,相位修正
    if(a_nNum > 2)
    {
        if(a_pKind[2] == 2)
        {
            m_pDataIII[0] = Param_Phase_SII(a_pData+6,0);
        }
        else if(a_pKind[2] == 3)
        {
            m_pDataIII[0] = Param_Phase_SI(a_pData+6,0);
        }
        else
        {
            m_pDataIII[0] = a_pData[6];
        }
        m_pDataIII[0] *= a_pFactor[2];
    }
    else
    {
        m_pDataIII[0] = 0;
    }

    //////////////////////////////////////////////////////////////////////////
    //如果有IV侧,相位修正
    if(a_nNum > 3)
    {
        if(a_pKind[3] == 2)
        {
            m_pDataIV[0] = Param_Phase_SII(a_pData+9,0);
        }
        else if(a_pKind[3] == 3)
        {
            m_pDataIV[0] = Param_Phase_SI(a_pData+9,0);
        }
        else
        {
            m_pDataIV[0] = a_pData[9];
        }
        m_pDataIV[0] *= a_pFactor[3];
    }
    else
    {
        m_pDataIV[0] = 0;
    }

    //计算结果
    dres = m_pDataI[0] + m_pDataII[0] + m_pDataIII[0] + m_pDataIV[0];
//    dres = dres*a_pParamab[0]+a_pParamab[1];
    return dres;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算B相差流
//参	数: 
//			a_nNum				侧数
//			a_pData				各侧数据
//			a_pKind				各侧的接线方式
//			a_pFactor			各侧平衡系数
//返 回	值: B相差流
//备	注:
//创建日期: 2007-04-09		wpf
//修改记录: 2007-07-17		把是否有III,IV侧的判断改为侧数
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_Chaliu_B(int a_nNum, float a_pData[], float a_pFactor[], int a_pKind[])
{
    float dres = 0;
    if(a_pKind[0] == 2)
    {
        m_pDataI[1] = Param_Phase_SII(a_pData,1);
    }
    else if(a_pKind[0] == 3)
    {
        m_pDataI[1] = Param_Phase_SI(a_pData,1);
    }
    else
    {
        m_pDataI[1] = a_pData[1];
    }

    if(a_pKind[1] == 2)
    {
        m_pDataII[1] = Param_Phase_SII(a_pData+3,1);
    }
    else if(a_pKind[1] == 3)
    {
        m_pDataII[1] = Param_Phase_SI(a_pData+3,1);
    }
    else
    {
        m_pDataII[1] = a_pData[4];
    }
    m_pDataII[1] *= a_pFactor[1];

    if(a_nNum > 2)
    {
        if(a_pKind[2] == 2)
        {
            m_pDataIII[1] = Param_Phase_SII(a_pData+6,1);
        }
        else if(a_pData[2] == 3)
        {
            m_pDataIII[1] = Param_Phase_SI(a_pData+6,1);
        }
        else
        {
            m_pDataIII[1] = a_pData[7];
        }
        m_pDataIII[1] *= a_pFactor[2];
    }
    else
        m_pDataIII[1] = 0;

    if(a_nNum > 3)
    {
        if(a_pKind[3] == 2)
        {
            m_pDataIV[1] = Param_Phase_SII(a_pData+9,1);
        }
        else if(a_pKind[3] == 3)
        {
            m_pDataIV[1] = Param_Phase_SI(a_pData+9,1);
        }
        else
        {
            m_pDataIV[1] = a_pData[10];
        }
        m_pDataIV[1] *= a_pFactor[3];
    }
    else
    {
        m_pDataIV[1] = 0;
    }

    dres = m_pDataI[1] + m_pDataII[1] + m_pDataIII[1] + m_pDataIV[1];
//    dres = dres*a_pParamab[2]+a_pParamab[3];
    return dres;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算C相差流
//参	数: 
//			a_nNum				共有几侧
//			a_pData				各侧数据
//			a_pKind				各侧的接线方式	
//返 回	值: C相差流
//备	注:
//创建日期: 2007-04-09		wpf
//修改记录: 2007-07-17		把是否有III,IV侧的标志改为侧数a_nNum
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_Chaliu_C(int a_nNum, float a_pData[], float a_pFactor[], int a_pKind[])
{
    float dres = 0;
    if(a_pKind[0] == 2)
    {
        m_pDataI[2] = Param_Phase_SII(a_pData,2);
    }
    else if(a_pKind[0] == 3)
    {
        m_pDataI[2] = Param_Phase_SI(a_pData,2);
    }
    else
    {
        m_pDataI[2] = a_pData[2];
    }

    if(a_pKind[1] == 2)
    {
        m_pDataII[2] = Param_Phase_SII(a_pData+3,2);
    }
    else if(a_pKind[1] == 3)
    {
        m_pDataII[2] = Param_Phase_SI(a_pData+3,2);
    }
    else
    {
        m_pDataII[2] = a_pData[5];
    }
    m_pDataII[2] *= a_pFactor[1];

    if(a_nNum > 2)
    {
        if(a_pKind[2] == 2)
        {
            m_pDataIII[2] = Param_Phase_SII(a_pData+6,2);
        }
        else if(a_pData[2] == 3)
        {
            m_pDataIII[2] = Param_Phase_SI(a_pData+6,2);
        }
        else
        {
            m_pDataIII[2] = a_pData[8];
        }
        m_pDataIII[2] *= a_pFactor[2];
    }
    else
    {
        m_pDataIII[2] = 0;
    }

    if(a_nNum > 3)
    {
        if(a_pKind[3] == 2)
        {
            m_pDataIV[2] = Param_Phase_SII(a_pData+9,2);
        }
        else if(a_pKind[3] == 3)
        {
            m_pDataIV[2] = Param_Phase_SI(a_pData+9,2);
        }
        else
        {
            m_pDataIV[2] = a_pData[11];
        }
        m_pDataIV[2] *= a_pFactor[3];
    }
    else
    {
        m_pDataIV[2] = 0;
    }

    dres = m_pDataI[2] + m_pDataII[2] + m_pDataIII[2] + m_pDataIV[2];
//    dres = dres*a_pParamab[4]+a_pParamab[5];
    return dres;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算均方根
//参	数: 
//			a_pData				数据
//			a_nStart			计算开始位置
//			a_nEnd				计算结束位置	
//返 回	值: C相差流
//备	注:
//创建日期: 2007-04-09		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_Junfanggen(float *a_pData, int a_nStart, int a_nEnd)
{
    float dres = 0.0;
    float dvalue = 0.0;
    int nstart = fmin(a_nStart,a_nEnd);
    int nend = fmax(a_nStart,a_nEnd);
    for(int i=nstart; i<=nend; i++)
    {
        dvalue += a_pData[i]*a_pData[i];
    }
    if(nend-nstart+1 == 0)
    {
        return 0;
    }
    dvalue /= nend-nstart+1;
    dres = (float)(sqrt(dvalue));
    return dres;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算某时刻差流
//参	数: 
//a_nPhase			差流相别
//a_nNum				共有几侧
//a_ppData			各侧数据.分别为各侧各相数据(最多12个数)
//a_pCT				各侧CT变比
//a_pMaxI				各侧额定电流
//a_nKind				各侧接线方式
//a_pFactor			各侧平衡系数
//返 回	值: 差流
//备	注: 先计算平衡系数，然后调用Cal_Chaliu_A/Cal_Chaliu_B/Cal_Chaliu_C
//创建日期: 2007-07-17		wpf
//修改记录: 
//		  2007-10-18		wpf		输入参数由CT/MAXI改为平衡系数
//////////////////////////////////////////////////////////////////////////
float CWyCal::Formula_Fun_DeltaId(int a_nPhase, int a_nNum,float* a_pData,float* a_pFactor,int* a_pKind)
{
    //	Cal_Factor(a_nNum,a_pCT,a_pMaxI);

    if((a_nPhase<0)||(a_nPhase>2))		//相不合理,默认为A相
    {
        a_nPhase = 0;
    }

    if(a_nPhase == 0)		//A相差流
    {
        return Cal_Chaliu_A(a_nNum,a_pData,a_pFactor,a_pKind);
    }
    else if(a_nPhase == 1)	//B相差流
    {
        return Cal_Chaliu_B(a_nNum,a_pData,a_pFactor,a_pKind);
    }
    else if(a_nPhase == 2)	//C相差流
    {
        return Cal_Chaliu_C(a_nNum,a_pData,a_pFactor,a_pKind);
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算频率
//参	数: 
//			a_pData				通道数据
//			a_nTotalPoints		点数目
//			a_nWavePoints		每周波点数
//			a_dFreq				标称频率
//返 回	值: 
//备	注: 
//创建日期: 2007-07-17		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
//DEL float CWyCal::Formula_Fun_Freq(float *a_pData, int a_nWavePoints, float a_dFreq/*=50*/)
//DEL {
//DEL 	float f0 = a_dFreq;
//DEL 	float fj = f0;
//DEL 
//DEL 	int nM = a_nWavePoints/10;
//DEL 	float dang,drms;
//DEL 	float dr[200];	//实部
//DEL 	float di[200];	//虚部
//DEL 	float dre=0,dim=0;
//DEL 	int nj;
//DEL 	int n0 = a_nWavePoints;
//DEL 
//DEL 	float ds[500] = {0};	//采样值(这里要反复插值)
//DEL 	for(int i=0; i<nM; i++)
//DEL 	{
//DEL 		drms = DFT_CalRms(a_pData+i,a_nWavePoints,dang);
//DEL 		dr[i] = (float)(drms * cos(dang));
//DEL 		di[i] = (float)(drms * sin(dang));
//DEL 	}
//DEL 	for(i=1; i<nM; i++)
//DEL 	{
//DEL 		dre += (float)(fabs(dr[i]*dr[i] - dr[i-1]*dr[i-1]));
//DEL 		dim += (float)(fabs(di[i]*di[i] - di[i-1]*di[i-1]));
//DEL 	}
//DEL 	fj = (float)(f0*sqrt(dim/dre));
//DEL 	if(fabs(fj-f0) < 0.02)
//DEL 	{
//DEL 		return fj;
//DEL 	}
//DEL 	
//DEL 	//开始迭代
//DEL 	int j = 1;
//DEL 	ZeroMemory(ds,sizeof(ds));
//DEL 	for(i=0; i<a_nWavePoints*2+nM; i++)
//DEL 	{
//DEL 		ds[i] = a_pData[i];
//DEL 	}
//DEL 
//DEL 	while((fabs(fj-f0)>0.02)&&(j<5))
//DEL 	{
//DEL 		nj = DoubleToInt(a_nWavePoints*(fj/50.));
//DEL 		
//DEL 		if(nj <= n0*f0/fj)
//DEL 		{
//DEL 			float dc = (50*a_nWavePoints)/(fj*nj);
//DEL 			for(int i=1; i<nj*2+nM; i++)
//DEL 			{
//DEL 				ds[i] = ds[i] + (ds[i]-ds[i-1])*i*(dc-1);
//DEL 			}
//DEL 		}
//DEL 		else
//DEL 		{
//DEL 			float dc = (50*a_nWavePoints)/(fj*nj);
//DEL 			for(int i=1; i<nj+nM; i++)
//DEL 			{
//DEL 				ds[i] = ds[i-1] + (ds[i]-ds[i-1])*(i*dc-i+1);
//DEL 			}
//DEL 		}
//DEL 		f0 = fj;
//DEL 		
//DEL 		nM = nj/10;
//DEL 		for(i=0; i<nM; i++)
//DEL 		{
//DEL 			drms = DFT_CalHarm(ds+i,nj,dang,1);
//DEL 			dr[i] = (float)(drms * cos(dang));
//DEL 			di[i] = (float)(drms * sin(dang));
//DEL 		}
//DEL 		dre = 0;
//DEL 		dim = 0;
//DEL 		for(i=1; i<nM; i++)
//DEL 		{
//DEL 			dre += (float)(fabs(dr[i]*dr[i] - dr[i-1]*dr[i-1]));
//DEL 			dim += (float)(fabs(di[i]*di[i] - di[i-1]*di[i-1]));
//DEL 		}
//DEL 		fj = (float)(f0*sqrt(dim/dre));		
//DEL 	}
//DEL 	return fj;
//DEL }

//////////////////////////////////////////////////////////////////////////
//功	能: 求信号在一个周期内的算术平均值
//参	数: 
//			a_pData				通道数据
//			a_nStartPos			计算开始位置
//			a_nWavePoints		每周波点数
//返 回	值: 
//备	注: 
//创建日期: 2007-07-23		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_Avg(float *a_pData, int a_nStartPos, int a_nWavePoints)
{
    m_dTmp = 0;
    for(int i=0; i<a_nWavePoints; i++)
    {
        m_dTmp += a_pData[a_nStartPos+i];
    }
    m_dTmp /= a_nWavePoints;
    return m_dTmp;
}


//////////////////////////////////////////////////////////////////////////
//功	能: 滤波
//参	数: 
//			a_pData				输入数据
//			a_nPoints			输入数据长度
//			a_nWavePoints		每周波点数目
//			a_pParam			滤波系数
//			a_nCount			滤波系数数目
//			a_pResult			输出结果
//			a_bConvert			是否反相
//返 回	值: 
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CWyCal::Dist_WaveFilter(float *a_pData, int a_nPoints, int a_nWavePoints, float *a_pParam, int a_nCount, float *a_pResult, bool a_bConvert)
{
    int ndots = a_nWavePoints/20;
    for(int i=a_nCount-1; i<a_nPoints; i++)
    {
        a_pResult[i-(a_nCount-1)] = 0.;
        for(int k=i-(a_nCount-1);k<i+1;k++)
        {
            a_pResult[i-(a_nCount-1)]+=(a_bConvert?(-1):1)*a_pData[ndots*k]*a_pParam[i-k];
        }
    }
}

int CWyCal::Dist_CalRX_PG4(float *a_pDataU, float *a_pDataI, float *a_pDataI0, float a_dR0, float a_dR1, float a_dX0, float a_dX1, float &a_dR, float &a_dX)
{
    float u1,u2,i1,i2,d1,d2,det;
    float kr = (float)((a_dR0-a_dR1)/3./a_dR1);
    float kl = (float)((a_dX0-a_dX1)/3./a_dX1);
    float rlbl = (float)(a_dR1*2*m_dPI*m_nFreq/a_dX1);

    float ivalue = (float)(sqrt(a_pDataI[0]*a_pDataI[0] + a_pDataI[5]*a_pDataI[5]));
    if(a_pDataI[1] > (0.9* ivalue))
        return 0;

    u1=a_pDataU[1];
    u2=a_pDataU[2];
    
    i1=a_pDataI0[1];
    i2=a_pDataI0[2];

    d1=(float)(rlbl*(a_pDataI[1]+kr*a_pDataI0[1])+2*m_dPI*m_nFreq*(a_pDataI[2]+kl*a_pDataI0[2]-a_pDataI[0]-kl*a_pDataI0[0])/(2.*sin(0.1*m_dPI)));
    d2=(float)(rlbl*(a_pDataI[2]+kr*a_pDataI0[2])+2*m_dPI*m_nFreq*(a_pDataI[3]+kl*a_pDataI0[3]-a_pDataI[1]-kl*a_pDataI0[1])/(2.*sin(0.1*m_dPI)));

    det=i2*d1-i1*d2;

    if(det)
    {
        a_dX=(u1*i2-u2*i1)/det;
        a_dR=(u2*d1-u1*d2)/det;
        a_dX=(float)(2.*m_dPI*m_nFreq*a_dX);
        return 1;
    }
    else
    {
        return 0;
    }
}

int CWyCal::Dist_CalRXEx_PP(float *a_pDataU, float *a_pDataI, float &a_dR, float &a_dX)
{
    float u1,u2,i1,i2,d1,d2,det;

    float ivalue = (float)(sqrt(a_pDataI[0]*a_pDataI[0] + a_pDataI[5]*a_pDataI[5]));

    if(a_pDataI[1]>(0.9*ivalue))
    {
        return 0;
    }

    i1=a_pDataI[1];//0，1，2是否按20点采样？
    i2=a_pDataI[2];

    u1=a_pDataU[1];
    u2=a_pDataU[2];

    d1=(float)(2*m_dPI*m_nFreq*(a_pDataI[2]-a_pDataI[0])/(2.*sin(0.1*m_dPI)));
    d2=(float)(2*m_dPI*m_nFreq*(a_pDataI[3]-a_pDataI[1])/(2.*sin(0.1*m_dPI)));

    det=i2*d1-i1*d2;
    if(det)
    {
        a_dX=(u1*i2-u2*i1)/det;
        a_dR=(u2*d1-u1*d2)/det;

        a_dX=(float)(2.*m_dPI*m_nFreq*a_dX);
	
        return 1;
    }
    else
    {
        return 0;
    }
}

int CWyCal::Dist_CalRX(float *a_pDataU1, float *a_pDataU2, float *a_pDataI1, float *a_pDataI2, float *a_pDataI0, int a_nWavePoints, float a_dRX[], float &a_dR, float &a_dX, bool a_bPhasePhase)
{
    int tmp = 0;
    int filterlen = 21;

    Dist_WaveFilter(a_pDataU1,26,a_nWavePoints,m_dParam,filterlen,m_dUData);
    Dist_WaveFilter(a_pDataI1,26,a_nWavePoints,m_dParam,filterlen,m_dIData);

    //相间阻抗,需要另一组电压电流
    if(a_bPhasePhase)
    {
        Dist_WaveFilter(a_pDataU2,26,a_nWavePoints,m_dParam,filterlen,m_dUtmp);
        Dist_WaveFilter(a_pDataI2,26,a_nWavePoints,m_dParam,filterlen,m_dItmp);
        for(int i=0; i<10; i++)
        {
            m_dUData[i] -= m_dUtmp[i];
            m_dIData[i] -= m_dItmp[i];
        }
        tmp = Dist_CalRXEx_PP(m_dUData,m_dIData,a_dR,a_dX);
    }
    else
    {
        Dist_WaveFilter(a_pDataI0,26,a_nWavePoints,m_dParam,filterlen,m_dIn);
        tmp = Dist_CalRX_PG4(m_dUData,m_dIData,m_dIn,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dR,a_dX);
    }

    return tmp;
}

int CWyCal::Dist_CalRX3(float *a_pDataU1, float *a_pDataU2, float *a_pDataI1, float *a_pDataI2, float *a_pDataI0, int a_nWavePoints, float a_dRX[], float &a_dR, float &a_dX, bool a_bPhasePhase)
{
    int tmp=0;

    float u1Filter[50] = {0};
    float u2Filter[50] = {0};
    float i1Filter[50]={0},i2Filter[50]={0},i0Filter[50]={0};

    float uuFilter[50] = {0},iiFilter[50] = {0};

    int i=0;
    int filterlen = 21;
    if(a_bPhasePhase)
    {
        Dist_WaveFilter(a_pDataU1,26,a_nWavePoints,m_dParam,filterlen,u1Filter);
        Dist_WaveFilter(a_pDataU2,26,a_nWavePoints,m_dParam,filterlen,u2Filter);
        Dist_WaveFilter(a_pDataI1,26,a_nWavePoints,m_dParam,filterlen,i1Filter);
        Dist_WaveFilter(a_pDataI2,26,a_nWavePoints,m_dParam,filterlen,i2Filter);
        for(i=0;i<10;i++)
        {
            uuFilter[i] = u1Filter[i]-u2Filter[i];
            iiFilter[i] = i1Filter[i]-i2Filter[i];
        }
        tmp = Dist_CalRXEx_PP(uuFilter,iiFilter,a_dR,a_dX);
    }
    else
    {
        Dist_WaveFilter(a_pDataU1,26,a_nWavePoints,m_dParam,filterlen,u1Filter);
        Dist_WaveFilter(a_pDataI1,26,a_nWavePoints,m_dParam,filterlen,i1Filter);
        Dist_WaveFilter(a_pDataI0,26,a_nWavePoints,m_dParam,filterlen,i0Filter);
        tmp = Dist_CalRX_PG4(u1Filter,i1Filter,i0Filter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dR,a_dX);
    }
    return tmp;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算频率
//参	数: 
//			a_pData				通道数据
//			a_nWavePints		每周波点数目
//返 回	值: 频率
//备	注: 
//创建日期: 2007-09-11		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::Dist_CalFreq(float *a_pData, int a_nWavePoints,float a_dFreq)
{
    float dfreq = a_dFreq;
    float ds1 = 0;
    float ds2 = 0;
    int ndots = a_nWavePoints/20;

    float fMax = GetMaxValue(a_pData,0,a_nWavePoints);
    if(fMax<0.5)
    {
        fMax = 0.5;
    }

    ds1=-a_pData[0*ndots] + a_pData[10*ndots] + a_pData[20*ndots] - a_pData[30*ndots];
    ds2=-a_pData[5*ndots] + a_pData[15*ndots] + a_pData[15*ndots] - a_pData[25*ndots];
    float fsm = 0;
    for(int i=0; i<a_nWavePoints; i+=ndots)
    {
        if(a_pData[i] > 0)
            fsm += a_pData[i];
    }
    const float fEpslon = 0.5;

    if((ds2>fMax)||(ds2<-fMax))
    {
        dfreq = (float)(50. - (ds1*16.0/ds2));
    }
    else
    {
        ds1 = -a_pData[5*ndots] + a_pData[15*ndots] + a_pData[25*ndots] - a_pData[35*ndots];
        ds2 = -a_pData[10*ndots] + a_pData[20*ndots] + a_pData[20*ndots] - a_pData[30*ndots];

        if((ds2>fMax)||(ds2<-fMax))
        {
            dfreq = (float)(50. - (ds1*16.0/ds2));
        }
        else
        {
            ds1 = -a_pData[10*ndots] + a_pData[20*ndots] + a_pData[30*ndots] - a_pData[40*ndots];
            ds2 = -a_pData[15*ndots] + a_pData[25*ndots] + a_pData[25*ndots] - a_pData[35*ndots];
            if((ds2>fMax)||(ds2<-fMax))
                dfreq=(float)(50.-(ds1*16.0/ds2));
            else if(fsm < fEpslon)
                dfreq = 0;
            else
                dfreq = 50;
        }
    }
    return dfreq;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 统计峰值
//参	数: 
//			a_pData				通道数据
//			a_nStartPos			开始计算的偏移位置
//			a_nWavePints		每周波点数目
//返 回	值: 峰值
//备	注: 
//创建日期: 2007-09-26			wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::GetMaxValue(float *a_pData, int a_nStartPos, int a_nWavePoints)
{
    float dmax = (float)(fabs(a_pData[a_nStartPos]));
    for(int i=a_nStartPos; i<a_nStartPos+a_nWavePoints; i++)
    {
        if(fabs(dmax) < fabs(a_pData[i]))
        {
            dmax = a_pData[i];
        }
    }
    return dmax;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 统计峰值(考虑正负号)
//参	数:
//			a_pData				通道数据
//			a_nStartPos			开始计算的偏移位置
//			a_nWavePints		每周波点数目
//返 回	值: 峰值
//备	注:
//创建日期: 2010-10-25			wpf
//修改记录:
//////////////////////////////////////////////////////////////////////////
float CWyCal::GetMaxValue_Ex(float* a_pData, int a_nStartPos,int a_nWavePoints)
{
    float dmax = fabs(a_pData[a_nStartPos]);
    for(int i=a_nStartPos; i<a_nStartPos+a_nWavePoints; i++)
    {
        if(fabs(dmax) < fabs(a_pData[i]))
        {
            dmax = fabs(a_pData[i]);
        }
    }
    return dmax;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算角度
//参	数: 
//			a_pData			原始数据
//			a_nStartPos		计算开始位置
//			a_nWavePOints	每周波采样点数目
//返 回	值: 返回角度
//备	注: 
//创建日期: 2009-10-10  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_Ang(float* a_pData,int a_nStartPos,int a_nWavePoints)
{
    float dAng = 0;
    DFT_Rms(a_pData+a_nStartPos,a_nWavePoints,dAng);
    return dAng;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算有效值
//参	数: 
//			a_pData			原始数据
//			a_nStartPos		计算开始位置
//			a_nWavePOints	每周波采样点数目
//			a_dAng			角度
//          a_nHarm         谐波次数，1为基波
//返 回	值: 返回有效值
//备	注: 当前点之后5个点的有效值取平均
//			调用时确保数据窗足够
//创建日期: 2007-10-18  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_Rms_Result(float *a_pData, int a_nStartPos, int a_nWavePoints,float& a_dAng,int a_nHarm)
{
    float dresult = 0;
    if(a_nHarm == 1)	//计算有效值
    {
        float dAng = 0;
        float drms = DFT_CalRms(a_pData+a_nStartPos,a_nWavePoints,a_dAng);
        //		TRACE("%.2f\n",a_dAng*180.0/g_dPI);
        float dmin = drms;
        float dmax = drms;
        dresult = drms;
        for(int i=1; i<5; i++)
        {
            drms = DFT_CalRms(a_pData+a_nStartPos+i,a_nWavePoints,dAng);
            if(drms < dmin)
            {
                dmin = drms;
            }
            if(drms > dmax)
            {
                dmax = drms;
            }
            dresult += drms;
        }
        dresult -= dmin;
        dresult -= dmax;
        dresult /= 3.0;
        static const float dda = (float)(2.0*g_dPI);
        if(a_dAng < 0)
        {
            a_dAng += dda;
        }
        if(a_dAng > 2.0*g_dPI)
        {
            a_dAng -= (float)(2.0*g_dPI);
        }
    }
    else			//计算谐波
    {
        if(a_nWavePoints == 200)
        {
            if(a_nStartPos %2 != 0)
            {
                a_nStartPos += 1;
            }
            dresult = DFT_CalHarm(a_pData+a_nStartPos,a_nWavePoints,a_dAng,a_nHarm,2);
        }
        else
            dresult = DFT_CalHarm(a_pData+a_nStartPos,a_nWavePoints,a_dAng,a_nHarm,1);
        /*
        if((a_nHarm>19)&&(a_nWavePoints!=80))
        {
            dresult *= (float)(1.0+(0.08/13.0)*(a_nHarm-19));
        }
        if(a_nWavePoints == 200)    //10K修正
        {
            if((a_nHarm>1)&&(a_nHarm<17))
            {
                dresult += (float)((0.36/16)*(a_nHarm-1));
            }
            if((a_nHarm>16)&&(a_nHarm<=20))
            {
                dresult += (float)((0.52/19)*(a_nHarm-1));
            }
        }
        */
    }
    return dresult;
}

float CWyCal::Cal_Rms_Result_Ex(float *a_pData, int a_nStartPos, int a_nWavePoints,float& a_dAng)
{
    float dresult = 0;
//    float dAng = 0;
    float drms = DFT_Rms_Ex(a_pData+a_nStartPos,a_nWavePoints,a_dAng);
    //		TRACE("%.2f\n",a_dAng*180.0/g_dPI);
//    float dmin = drms;
//    float dmax = drms;
    dresult = drms;
//    for(int i=1; i<5; i++)
//    {
//        drms = DFT_Rms_Ex(a_pData+a_nStartPos+i,a_nWavePoints,dAng);
//        if(drms < dmin)
//        {
//            dmin = drms;
//        }
//        if(drms > dmax)
//        {
//            dmax = drms;
//        }
//        dresult += drms;
//    }
//    dresult -= dmin;
//    dresult -= dmax;
//    dresult /= 3.0;
    static const float dda = (float)(2.0*g_dPI);
    if(a_dAng < 0)
    {
        a_dAng += dda;
    }
    if(a_dAng > 2.0*g_dPI)
    {
        a_dAng -= (float)(2.0*g_dPI);
    }

    return dresult;
}

float CWyCal::Cal_Rms_Segma(float *a_pData, int a_nWavePoints)
{
    float segmaa = 0.0;
    float segmab = 0.0;
    float dRms = 0;
    int n = 0;
    for(n=0; n<5; n++)
    {
        segmaa = 0;
        segmab = 0;
        for(int i=n; i<a_nWavePoints+n; i++)
        {
            segmaa += (float)(a_pData[i] * cos(i*2.0*m_gPI/(float)(a_nWavePoints)));
            segmab += (float)(a_pData[i] * sin(i*2.0*m_gPI/(float)(a_nWavePoints)));
        }
        dRms += (float)(sqrt(segmaa*segmaa + segmab*segmab)/m_dsqt2/((float)a_nWavePoints/2.0));
    }
    dRms /= 5.;

    return dRms;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算有效值及各次谐波(差分傅氏算法)
//参	数: 
//			a_pData			原始数据
//			a_nWavePOints	每周波采样点数目
//			a_dAng			角度
//			a_nHarm			谐波次数
//返 回	值: 返回有效值
//备	注: 需要一周波+1个点计算,调用时保证数据窗足够
//创建日期: 2009-10-12  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::DFT_Rms_Sub(float* a_pData,int a_nWavePoints,float& a_dAng,int a_nHarm/*=1*/)
{
    float drms = 0.0;
    if(a_nWavePoints < 20)
    {
        for(int i=0; i<a_nWavePoints; i++)
        {
            if(drms < fabs(a_pData[i]))
                drms = (float)(fabs(a_pData[i]));
        }
        drms /= m_dsqt2;
        return drms;
    }
    float dreal = 0.0;
    float dimg = 0.0;

    for(int i=1; i<a_nWavePoints+1; i++)
    {
        dreal += (float)((a_pData[i]-a_pData[i-1])*cos(2.0*i*a_nHarm*g_dPI/a_nWavePoints));
        dimg  += (float)((a_pData[i]-a_pData[i-1])*sin(2.0*i*a_nHarm*g_dPI/a_nWavePoints));
    }


    drms = (float)(sqrt(dreal*dreal+dimg*dimg)*2.0/a_nWavePoints);
    drms /= m_dsqt2;

    float r_param = (float)(2.0*sin(g_dPI/a_nWavePoints));
    float a_param = (float)(g_dPI*0.5-g_dPI/a_nWavePoints);
    //	float a_param = (float)(0.5*(g_dPI-2.0*g_dPI/a_nWavePoints));
    drms /= r_param;
    a_dAng = (float)(atan2(-dimg,dreal) + g_dPI/2.0);
    a_dAng -= a_param;
    if(a_dAng < 0.0000001)
    {
        a_dAng += 2*g_dPI;
    }
    return drms;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 差分算法计算有效值
//参	数: 
//			a_pData			原始数据
//			a_nStartPos		计算开始位置
//			a_nWavePOints	每周波采样点数目
//			a_dAng			角度
//返 回	值: 返回有效值
//备	注: 当前点之后5个点的有效值取平均
//			调用时确保数据窗足够
//创建日期: 2007-10-18  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_Rms_Result_Sub(float *a_pData, int a_nStartPos, int a_nWavePoints, float &a_dAng, int a_nHarm)
{
    float dresult = 0;
    if(a_nHarm == 1)	//计算有效值
    {
        float dAng = 0;
        float drms = DFT_Rms_Sub(a_pData+a_nStartPos,a_nWavePoints,a_dAng);
        float dmin = drms;
        float dmax = drms;
        dresult = drms;
        for(int i=1; i<5; i++)
        {
            drms = DFT_Rms_Sub(a_pData+a_nStartPos+i,a_nWavePoints,dAng);
            if(drms < dmin)
            {
                dmin = drms;
            }
            if(drms > dmax)
            {
                dmax = drms;
            }
            dresult += drms;
        }
        dresult -= dmin;
        dresult -= dmax;
        dresult /= 3.0;
        static const float dda = (float)(2.0*3.1415926);
        if(a_dAng < 0)
        {
            a_dAng += dda;
        }
        if(a_dAng > 2.0*3.1415926)
        {
            a_dAng -= (float)(2.0*3.1415926);
        }
    }
    else			//计算谐波
    {
        dresult = DFT_Rms_Sub(a_pData,a_nWavePoints,a_dAng,a_nHarm);
        if((a_nHarm>19)&&(a_nWavePoints!=80))
        {
            dresult *= (float)(1.0+(0.18/13.0)*(a_nHarm-19));
        }
    }
    return dresult;
}

float CWyCal::DFT_CalRms(float *a_pData, int a_nWavePoints, float &a_dAng)
{
    float dRms = 0;
    //计算谐波
    if(a_nWavePoints < 20)
    {
        dRms = a_pData[0]/m_dsqt2;
        a_dAng = 0;
        return dRms;
    }
    float segmaa = 0.0;
    float segmab = 0.0;
    if(200%a_nWavePoints != 0)
    {
        for(int i=0; i<a_nWavePoints; i++)
        {
            segmaa += (float)(a_pData[i] * cos(i*2.0*m_gPI/(float)(a_nWavePoints)));
            segmab += (float)(a_pData[i] * sin(i*2.0*m_gPI/(float)(a_nWavePoints)));
        }
    }
    else
    {
        int nbs = 200/a_nWavePoints;
        for(int i=0; i<a_nWavePoints; i++)
        {
            segmaa += (float)(a_pData[i] * g_dCos200[i*nbs]);
            segmab += (float)(a_pData[i] * g_dSin200[i*nbs]);
        }
    }
    dRms = (float)(sqrt(segmaa*segmaa + segmab*segmab)/m_dsqt2/((float)a_nWavePoints/2.0));
    a_dAng = (float)(atan2(-segmab,segmaa));
    a_dAng += (float)(g_dPI/2.0);
    return dRms;
}

float CWyCal::Cal_DeltaT(float *a_pData, int a_nWavePoints)
{
    if(a_nWavePoints < 20)
    {
        return 0;
    }
    float dang = 0;
    if(DFT_CalRms(a_pData,a_nWavePoints,dang) < 0.05)
    {
        return 0;
    }

    float dDeltaT = 0.0;
    int ndots = a_nWavePoints/20;
    float di1 = Cal_Avg(a_pData+20*ndots,ndots)-Cal_Avg(a_pData,ndots);
    float di2 = Cal_Avg(a_pData+40*ndots,ndots)-Cal_Avg(a_pData+20*ndots,ndots);

    if(fabs(fabs(di1)-fabs(di2)) < 0.005)
    {
        return 0;
    }
    if((fabs(di1)<0.001)||(fabs(di2)<0.001))
    {
        return 0;
    }

    dDeltaT = (float)(log(fabs(di2/di1)));
    if(dDeltaT < 0)
    {
        dDeltaT = (float)(log(fabs(di1/di2)));
    }
    if(dDeltaT > 0)
    {
        dDeltaT = (float)(20.0/dDeltaT);
    }
    else
    {
        dDeltaT = 0;
    }
    //	TRACE("%.2f,%.2f,%.2f\n",di1,di2,dDeltaT);
    return dDeltaT;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算衰减时间常数
//参	数:
//			a_pData			原始数据
//			a_nCalPos		计算开始位置
//			a_nSegPoints	本采样段采样点数目
//			a_nWavePoints	每周波采样点数目
//返 回	值: 时间常数
//备	注:
//创建日期: 2010-10-25  wpf
//修改记录:
//////////////////////////////////////////////////////////////////////////
float CWyCal::Cal_DeltaT_Ex(float *a_pData, int a_nCalPos, int a_nSegPoints, int a_nWavePoints)
{
    if(a_nWavePoints < 20)
    {
        return 0;
    }
    float dang = 0;
    if(DFT_CalRms(a_pData+a_nCalPos,a_nWavePoints,dang) < 0.05)
    {
        return 0;
    }
    int nwcount = a_nSegPoints/a_nWavePoints;
    if(nwcount<2)
    {
        return 0;
    }

    float fDeltaT = 0;
    float fnn = GetMaxValue_Ex(a_pData,(nwcount-1)*a_nWavePoints,a_nWavePoints);	//最后一周波的峰值
    float fd1 = GetMaxValue_Ex(a_pData,a_nCalPos,a_nWavePoints);					//当前点所在周波峰值
    float fd2 = GetMaxValue_Ex(a_pData,a_nCalPos+a_nWavePoints,a_nWavePoints);		//下一周波峰值

    if(fd1/fnn > 5)		//周期分量不对,查找最接近的值
    {
        for(int i=nwcount-2; i>0; i--)
        {
            fnn = GetMaxValue_Ex(a_pData,i*a_nWavePoints,a_nWavePoints);
            if(fd1/fnn < 5)
            {
                break;
            }
        }
    }

    if(fabs(fd1)+fabs(fd2) < 1)
    {
        return 0;
    }
    fd1 -= fnn;
    fd2 -= fnn;
    fDeltaT = (float)(log(fabs(fd1/fd2)));
    if(fDeltaT < 0)
    {
        fDeltaT = (float)(log(fabs(fd2/fd1)));
    }
    if(fDeltaT > 0)
    {
//        fDeltaT = (float)(20*5./fDeltaT);
        fDeltaT = (float)(20/fDeltaT);
    }
    else
    {
        fDeltaT = 0;
    }
    return fDeltaT;
}

float CWyCal::Cal_DeExcitT(float *a_pData,int a_nSegPoints, int a_nWavePoints)
{
    if(a_nWavePoints < 20)
    {
        return 0;
    }
    float dang = 0;
    if(DFT_CalRms(a_pData,a_nWavePoints,dang) < 0.05)
    {
        return 0;
    }
    int nwcount = a_nSegPoints/a_nWavePoints;
    if(nwcount<20)
    {
        return 0;
    }


    float fd1 = GetMaxValue_Ex(a_pData,0,a_nWavePoints);
    float fd = 0;
    int i = 0;
    /* 10% 时间作为灭磁常数(不再采用)
    float fResult = 0;
    for(i=a_nWavePoints; i<a_nSegPoints; i+=a_nWavePoints)
    {
        fd = GetMaxValue_Ex(a_pData,i,a_nWavePoints);
        if(fd/fd1 < 0.1)
        {
            fResult = (i/a_nWavePoints)*20./1000.;
            break;
        }
    }
    if(fResult > 0.1)
        return fResult;
    */

    for(i=a_nWavePoints; i<a_nSegPoints; i+=a_nWavePoints)
    {
        fd = GetMaxValue_Ex(a_pData,i,a_nWavePoints);
        if((fd1-fd)/fd1 > 0.01)
        {
            fd1 = fd;
            break;
        }
    }

    float fd2 = GetMaxValue_Ex(a_pData,5*a_nWavePoints+i,a_nWavePoints);
    float fDeltaT = (float)(log(fabs(fd1/fd2)));
    if(fDeltaT < 0)
    {
        fDeltaT = (float)(log(fabs(fd2/fd1)));
    }

    if(fDeltaT < 0.0001)
        fDeltaT = 11.3;

    fDeltaT = (float)(20*5./fDeltaT)/1000.;
    return fDeltaT;
}

float CWyCal::Cal_Avg(float *a_pData, int a_nPoints)
{
//    ASSERT(a_nPoints > 0);
//    ASSERT(a_pData != NULL);
    //	int ndots = a_nPoints/20;
    float dresult = 0;
    for(int i=0; i<a_nPoints; i++)
    {
        dresult += a_pData[i];
    }
    dresult /= a_nPoints;
    return dresult;
}

float CWyCal::Freq_Param(float a_fFreq)
{
    float fResult = a_fFreq;
    double k = 0;
    double vo = 0;
    double vm = 0;
    double fparam = 0;
    if((a_fFreq>38)&&(a_fFreq<39.951))
    {
        k = (0.217-0.118)/(38.217-39.918);
        vo = 38.217;
        vm = 0.217;
    }
    else if((a_fFreq>39.95)&&(a_fFreq<41.311))
    {
        k = (0.115-0.06)/(40.015-41.26);
        vo = 40.015;
        vm = 0.115;
    }
    else if((a_fFreq>41.31)&&(a_fFreq<42.471))
    {
        k = (0.061-0.028)/(41.361-42.428);
        vo = 41.361;
        vm = 0.061;
    }
    else if((a_fFreq>42.47)&&(a_fFreq<44.351))
    {
        k = (0.027-0)/(42.527-44.2);
        vo = 42.527;
        vm = 0.027;
    }
    else if((a_fFreq>44.35)&&(a_fFreq<44.541))
    {
        k = (-0.003+0.01)/(44.397-45.49);
        vo = 44.397;
        vm = -0.003;
    }
    else if((a_fFreq>44.54)&&(a_fFreq<48.11))
    {
        k = 0;
        vo = 45.591;
        vm = -0.01;
    }
    else if((a_fFreq>48.1)&&(a_fFreq<51.451))
    {
        k = (-0.008-0.008)/(48.192-51.408);
        vo = 48.192;
        vm = -0.008;
    }
    else if((a_fFreq>51.45)&&(a_fFreq<54.851))
    {
        k = 0;
        vo = 51.508;
        vm = 0.011;
    }
    else if((a_fFreq>54.85)&&(a_fFreq<56.1))
    {
        k = (0.008+0.002)/(54.908-55.898);
        vo = 54.908;
        vm = 0.008;
    }
    fparam = vm+(a_fFreq-vo)*k;
    fResult -=  fparam;
    return fResult;
}

float CWyCal::DFT_CalFreq(float *a_pData, int a_nWavePoints, float a_dFreq)
{
    float f0 = a_dFreq;
    float fj = f0;

    int nM = a_nWavePoints/10;
    float dang,drms;
    float dr[200]={0};	//实部
    float di[200]={0};	//虚部
    float dre=0,dim=0;
    int nj = 0;
//    int n0 = a_nWavePoints;
    int i = 0;

    for(i=0; i<nM; i++)
    {
        drms = DFT_CalRms(a_pData+i,a_nWavePoints,dang);
        dr[i] = (float)(drms * cos(dang));
        di[i] = (float)(drms * sin(dang));
    }
    for(i=1; i<nM; i++)
    {
        dre += (float)(fabs(dr[i]*dr[i] - dr[i-1]*dr[i-1]));
        dim += (float)(fabs(di[i]*di[i] - di[i-1]*di[i-1]));
    }
    fj = (float)(f0*sqrt(dim/dre));
    if(fabs(fj-f0) < 0.02)
    {
        return fj;
    }
    nj = DoubleToInt(50*a_nWavePoints/fj);
    fj = Dist_CalFreq(a_pData,nj,fj);
    return fj;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 分数次谐波计算
//参	数: 
//			a_pData			输入数据数据
//			a_nWavePoints	每周波采样点数
//			a_nHarm			谐波次数*2
//			a_dAng			相位
//返 回	值: 
//备	注:
//创建日期: 2010-07-14  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CWyCal::DFT_CalHarm0_5(float *a_pData, int a_nWavePoints, float &a_dAng, int a_nHarm)
{
    unsigned int s = a_nWavePoints*2;
    unsigned int i = 0;
    float r=0,x=0,z=0;

    for(i=0;i<s;i++)
    {
        z = a_pData[i];
        r += (float)(z*sin(a_nHarm* i/(float)s*2*3.1415926));
        x += (float)(z*cos(a_nHarm* i/(float)s*2*3.1415926));
    }

    a_dAng = (float)(atan(x/r));		//????
    if(r<0)
    {
        if(x>0)
            a_dAng += (float)(3.1415926);
        else
            a_dAng -= (float)(3.1415926);
    }
    if(r==0)
        a_dAng=0;

    r = r*r;
    x = x*x;
    z = (float)(sqrt(r+x)/1.414214/(s/2));
    return z;
}

float CWyCal::Cal_Rms_ZP(float* a_pData,int a_nWavePoints)
{
    float fMax = a_pData[0];
    float fMin = a_pData[0];
    for(int i=0; i<a_nWavePoints; i++)
    {
        if(a_pData[i] > fMax)
            fMax = a_pData[i];
        if(a_pData[i] < fMin)
            fMin = a_pData[i];
    }
    float fResult = (fMax-fMin)/2/m_dsqt2;
    return fResult;
}
