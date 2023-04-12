//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : AnaResult.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 故障分析接口
//  备    注 : 分析录波文件,生成故障报告
//				
//
//---------------------------------------------------------------
//版本历史:
//---------------------------------------------------------------
//ver 1.0		2007-09-13		创建初始版本
//ver 2.0		2008-08-10		删除浙江录波XML简报相关代码
//								和通信软件中的分析部分彻底分开
//
//
//////////////////////////////////////////////////////////////////////////

#include "GenerateReport.h"
#include "WyCal.h"
#include "VarDef.h"
#include <QFile>
#include "CnCodec.h"
#include <time.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CGenerateReport::CGenerateReport()
{
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
    m_strFaultType[0] = "区内无故障";
    m_strFaultType[1] = "A相接地";
    m_strFaultType[2] = "B相接地";
    m_strFaultType[3] = "C相接地";
    m_strFaultType[4] = "AB两相短路";
    m_strFaultType[5] = "BC两相短路";
    m_strFaultType[6] = "CA两相短路";
    m_strFaultType[7] = "AB两相接地";
    m_strFaultType[8] = "BC两相接地";
    m_strFaultType[9] = "CA两相接地";
    m_strFaultType[10] = "ABC三相短路";
    m_strFaultType[11] = "";
    m_strFaultType[12] = "未定义";
    memset(m_chFaultLine,0,sizeof(m_chFaultLine));
    m_uFpt = 0;
    m_uJpt = 0;
    m_fFaultDistance = 0;
    m_uDpi = 0;
    m_wChzTime = 0;
    memset(&m_cpStartTime,0,sizeof(m_cpStartTime));
    m_dwFileSize = 0;
    m_nChanelCount = 0;

    memset(m_chRecName,0,sizeof(m_chRecName));
    strcpy(m_chRecName,"WY9系列录波器");
    memset(m_chStationName,0,sizeof(m_chStationName));
    memset(m_chFilePath,0,sizeof(m_chFilePath));
    memset(m_chStartTime,0,sizeof(m_chStartTime));
    m_dTimeLong = 0;
    memset(m_chErrorInfo,0,sizeof(m_chErrorInfo));
    m_pFaultLine = NULL;
    m_pFaultTrans = NULL;

    m_arLineInfo = new tagLineInfo[MAX_TBLINE_COUNT];
    m_arTransInfo = new tagTransInfo[MAX_TRANSCOUNT];
    m_arChanelInfo = new tagChanelInfo[MAX_ACHANELCOUNT];
}

CGenerateReport::~CGenerateReport()
{
    delete []m_arLineInfo;
    delete []m_arTransInfo;
    delete []m_arChanelInfo;
}

bool CGenerateReport::AnalysisLine(int a_nLineIndex)
{
    InitData();
    GenerateBasicInfo();	//获取基本信息
    GenerateSwitchList();	//获取开关动作时序
    m_nTbLineCount = 0;

    m_arLineInfo[m_nTbLineCount].m_bFault = false;
    m_arLineInfo[m_nTbLineCount].InitData();
    m_arLineInfo[m_nTbLineCount].m_nLineIndex = a_nLineIndex;
    if((m_pCmtd->m_arLine[a_nLineIndex]->m_pBus==NULL)||(m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel==NULL)||(m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel == NULL))
    {
        return false;
    }
    //首先选相测距
    bool btb = AnalysisLine(a_nLineIndex,&(m_arLineInfo[m_nTbLineCount]));
    if(btb)
    {
        m_nTbLineCount++;
    }
    else	//本线路是否有开关动作
    {
        bool bSwitch = false;
        for(int i=0; i<m_SwitchList.m_arStatus.count(); i++)
        {
            for(int n=0; n<m_pCmtd->m_arLine[a_nLineIndex]->m_arDChanel.count(); n++)
            {
                if(m_pCmtd->m_arLine[a_nLineIndex]->m_arDChanel[n] == m_SwitchList.m_arStatus[i].m_wID)
                {
                    bSwitch = true;
                    break;
                }
            }
            if(bSwitch)
            {
                break;
            }
        }
        if(bSwitch)
        {
            IsLines_Inf_Overflow(&(m_arLineInfo[m_nTbLineCount]),m_pCmtd->m_arLine[a_nLineIndex]);
            GetLineValue_Cyc(&(m_arLineInfo[0]),m_pCmtd->m_arLine[a_nLineIndex]);
            m_nTbLineCount++;
        }
    }
    //本线路是否有电流突变
    if(m_nTbLineCount <= 0)
    {
        m_arLineInfo[m_nTbLineCount].m_bFault = false;
        m_arLineInfo[m_nTbLineCount].InitData();
        m_arLineInfo[m_nTbLineCount].m_nLineIndex = a_nLineIndex;
        if(IsLines_Inf_Overflow(&(m_arLineInfo[m_nTbLineCount]),m_pCmtd->m_arLine[a_nLineIndex]))
        {
            m_nTbLineCount++;
            GetLineValue_Cyc(&(m_arLineInfo[0]),m_pCmtd->m_arLine[a_nLineIndex]);
        }
    }

    //选相失败、无开关动作、无电流突变，报告内容为空
    if((!btb)&&(m_nTbLineCount <= 0))
    {
        return false;
    }

    //-------------------------------------------------------------------
    //进行一次合理性分析
    //-------------------------------------------------------------------
//    bool bFault = false;
    int nFaultLine = m_arLineInfo[0].m_nLineIndex;
    int nStartIndex = 0;
    float dLineLength = m_pCmtd->m_arLine[nFaultLine]->m_dLength;
    float dDistanceI = m_arLineInfo[0].m_dDistanceI;
    float dDistanceII = m_arLineInfo[0].m_dDistanceII;
    float dStartTime = (float)(m_pCmtd->m_pSampleTime[m_arLineInfo[nStartIndex].m_nStartPoint]/1000.0);
    float dTimeLong = (float)(m_pCmtd->m_pSampleTime[m_arLineInfo[nStartIndex].m_nEndPoint]/1000.0);
    dTimeLong -= dStartTime;
    // 如果是-5以内的负数,认为合理 [1/23/2008]
    if((dDistanceI<0)&&(dDistanceI>-5))
    {
        dDistanceI = -dDistanceI;
        m_arLineInfo[0].m_dDistanceI = dDistanceI;
    }
    if((dDistanceII<0)&&(dDistanceII>-5))
    {
        dDistanceII = -dDistanceII;
        m_arLineInfo[0].m_dDistanceII = dDistanceII;
    }
    
    if((dDistanceI>=0)&&(dDistanceI <= 1.2*dLineLength)&&(dTimeLong > 0.0001)&&(dLineLength > 0.5))
    {
//        bFault = true;
        m_arLineInfo[nStartIndex].m_bFault = true;
    }
    if((dDistanceII>=0)&&(dDistanceII <= 1.2*dLineLength)&&(dTimeLong > 0.0001)&&(dLineLength > 0.5))
    {
//        bFault = true;
        m_arLineInfo[nStartIndex].m_bFault = true;
    }
    m_pFaultLine = &(m_arLineInfo[nStartIndex]);

    //-------------------------------------------------------------------------
    //整理开关量信息,去掉不是本线路的开关信息
    //-------------------------------------------------------------------------
    bool bCorrect = false;
    int nSize = m_SwitchList.m_arStatus.count();
    for(int i=nSize-1; i>=0; i--)
    {
        bCorrect = false;
        for(int j=0; j<m_pCmtd->m_arLine[nFaultLine]->m_arDChanel.count(); j++)
        {
            if(m_SwitchList.m_arStatus[i].m_wID == m_pCmtd->m_arLine[nFaultLine]->m_arDChanel[j])
            {
                bCorrect = true;
                break;
            }
        }
        if(!bCorrect)
        {
            m_SwitchList.m_arStatus.remove(i);
        }
    }
//    m_SwitchList.m_arStatus.clear();

    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 基于正弦量计算幅值(有效值??)
//参	数: 
//			a_pData				通道数据
//			a_nWavePoints		每周波采样点数目
//////////////////////////////////////////////////////////////////////////
float CGenerateReport::Dist_CalAmp(float* a_pData,int a_nWavePoints)
{
    int ndots = a_nWavePoints/20;//每周波抽20点抽样间隔
    return (float)(sqrt(0.5*(a_pData[0]*a_pData[0] + a_pData[5*ndots]*a_pData[5*ndots])));
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算平均值
//参	数: 
//			a_pData				通道数据
//			a_nPoints			需计算的点数目
//返 回	值: 平均值
//备	注: 
//创建日期: 2007-09-11		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CGenerateReport::Dist_CalAvg(float* a_pData,int a_nPoints)
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

//////////////////////////////////////////////////////////////////////////
//功	能: 计算平均值(去掉第一个点,去掉最大/最小值)
//参	数: 
//			a_pData				通道数据
//			a_nPoints			需计算的点数目
//返 回	值: 平均值
//备	注: 
//创建日期: 2007-09-11		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CGenerateReport::Dist_CalAvgEx(float* a_pData,int a_nPoints)
{
    //    ASSERT(a_pData != NULL);
    //    ASSERT(a_nPoints > 2);
    float dresult = a_pData[0];
    float dmax = a_pData[0];
    float dmin = a_pData[0];
    for(int i=1; i<a_nPoints; i++)
    {
        if(a_pData[i] > dmax)
        {
            dmax = a_pData[i];
        }
        if(a_pData[i] < dmin)
        {
            dmin = a_pData[i];
        }
        dresult += a_pData[i];
    }
    dresult /= a_nPoints-2;
    return dresult;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算衰减时间常数
//参	数: 
//			a_pData				通道数据
//			a_nWavePints		每周波点数目
//返 回	值: 时间常数
//备	注: 
//创建日期: 2007-09-11		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CGenerateReport::Dist_CalDeltaT_Result(float* a_pData,int a_nWavePoints)
{
    float dDeltaT = 0.0;
    int ndots = a_nWavePoints/20;
    float di1 = Dist_CalAvg(a_pData+20*ndots,ndots)-Dist_CalAvg(a_pData,ndots);
    float di2 = Dist_CalAvg(a_pData+40*ndots,ndots)-Dist_CalAvg(a_pData+20*ndots,ndots);
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
    return dDeltaT;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算衰减时间常数
//参	数: 
//			a_pData				通道数据
//			a_nWavePints		每周波点数目
//返 回	值: 时间常数
//备	注: 
//创建日期: 2007-09-11		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CGenerateReport::Dist_CalDeltaT(float* a_pIa,float* a_pIb,float* a_pIc,int a_nWavePoints,int a_nFaultType)
{
    //80表示4个周波
    float dIab[80] = {0};
    float dIbc[80] = {0};
    float dIca[80] = {0};
    int i;
    int ndots = a_nWavePoints/20;

    //-----------------------------------------------------------------------------
    //计算相电流值(基于20点采样)
    //-----------------------------------------------------------------------------
    for(i=0;i<80;i++)
    {
        dIab[i] = Dist_CalAvg(a_pIa+i*ndots,ndots) - Dist_CalAvg(a_pIb+i*ndots,ndots);
        dIbc[i] = Dist_CalAvg(a_pIb+i*ndots,ndots) - Dist_CalAvg(a_pIc+i*ndots,ndots);
        dIca[i] = Dist_CalAvg(a_pIc+i*ndots,ndots) - Dist_CalAvg(a_pIa+i*ndots,ndots);
    }

    //-----------------------------------------------------------------------------
    //计算衰减时间常数
    //-----------------------------------------------------------------------------
    float dDeltaT = 0.0;
    /*
    switch (a_nFaultType)
	{
	case  FAULT_AN:
		dDeltaT = Dist_CalDeltaT(a_pIa,a_nWavePoints);
		break;
	case  FAULT_BN:
		dDeltaT = Dist_CalDeltaT(a_pIb,a_nWavePoints);
		break;
	case  FAULT_CN:
		dDeltaT = Dist_CalDeltaT(a_pIc,a_nWavePoints);
		break;
	case  FAULT_AB:
		dDeltaT = Dist_CalDeltaT(dIab,20);
		break;
	case  FAULT_BC:
		dDeltaT = Dist_CalDeltaT(dIbc,20);
		break;
	case  FAULT_CA:
		dDeltaT = Dist_CalDeltaT(dIca,20);
		break;
	case  FAULT_ABN:
		dDeltaT = Dist_CalDeltaT(dIab,20);
		break;
	case  FAULT_BCN:
		dDeltaT = Dist_CalDeltaT(dIbc,20);
		break;
	case  FAULT_CAN:
		dDeltaT = Dist_CalDeltaT(dIca,20);
		break;
	case  FAULT_ABC:
		dDeltaT = Dist_CalDeltaT(dIab,20);
		break;
    }
	*/
    switch (a_nFaultType)
    {
    case  FAULT_AN:
        dDeltaT = Dist_CalDeltaT_Ex(a_pIa,a_nWavePoints);
        break;
    case  FAULT_BN:
        dDeltaT = Dist_CalDeltaT_Ex(a_pIb,a_nWavePoints);
        break;
    case  FAULT_CN:
        dDeltaT = Dist_CalDeltaT_Ex(a_pIc,a_nWavePoints);
        break;
    case  FAULT_AB:
        dDeltaT = Dist_CalDeltaT_Ex(dIab,20);
        break;
    case  FAULT_BC:
        dDeltaT = Dist_CalDeltaT_Ex(dIbc,20);
        break;
    case  FAULT_CA:
        dDeltaT = Dist_CalDeltaT_Ex(dIca,20);
        break;
    case  FAULT_ABN:
        dDeltaT = Dist_CalDeltaT_Ex(dIab,20);
        break;
    case  FAULT_BCN:
        dDeltaT = Dist_CalDeltaT_Ex(dIbc,20);
        break;
    case  FAULT_CAN:
        dDeltaT = Dist_CalDeltaT_Ex(dIca,20);
        break;
    case  FAULT_ABC:
        dDeltaT = Dist_CalDeltaT_Ex(dIab,20);
        break;
    }
    return dDeltaT;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算频率
//参	数: 
//			a_pData				通道数据
//			a_nWavePints		每周波点数目
//			a_dFreq				标称频率
//返 回	值: 频率
//备	注: 
//创建日期: 2007-09-11		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CGenerateReport::Dist_CalFreq(float* a_pData,int a_nWavePoints)
{
    float dfreq = 50.0;
    float ds1 = 0;
    float ds2 = 0;
    int ndots = a_nWavePoints/20;

    ds1=-a_pData[0*ndots] + a_pData[10*ndots] + a_pData[20*ndots] - a_pData[30*ndots];
    ds2=-a_pData[5*ndots] + a_pData[15*ndots] + a_pData[15*ndots] - a_pData[25*ndots];

    if(fabs(ds2) > 100)
    {
        dfreq = (float)(50.0 - (ds1*16.0/ds2));
    }
    else
    {
        ds1 = -a_pData[5*ndots] + a_pData[15*ndots] + a_pData[25*ndots] - a_pData[35*ndots];
        ds2 = -a_pData[10*ndots] + a_pData[20*ndots] + a_pData[20*ndots] - a_pData[30*ndots];

        if(fabs(ds2) > 100)
        {
            dfreq = (float)(50.0 - (ds1*16.0/ds2));
        }
        else
        {
            dfreq = 0;
        }
    }
    return dfreq;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 傅氏变换
//参	数: 
//			a_pData				通道数据
//			a_nWavePints		每周波点数目
//			a_pParamRe			计算系数的实部
//			a_pParamIm			计算系数的虚部
//			a_nPoints			计算系数的数目
//			a_dRe				计算结果的实部
//			a_dIm				计算结果的实部
//返 回	值: 
//备	注: 
//创建日期: 2007-09-11		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CGenerateReport::Dist_DFT(float* a_pData,int a_nWavePoints,float* a_pParamRe,float* a_pParamIm,int a_nPoints,float& a_dRe,float& a_dIm)
{
    float y_real = 0;
    float y_imag = 0;

    int ndots = a_nWavePoints/20;
    for(int i=0; i<a_nPoints; i++)
    {
        y_real += a_pData[i*ndots]*a_pParamRe[a_nPoints-i-1];
        y_imag += a_pData[i*ndots]*a_pParamIm[a_nPoints-i-1];
    }
    a_dRe = (float)(y_real/1.4142);
    a_dIm = (float)(y_imag/1.4142);
}

//////////////////////////////////////////////////////////////////////////
//功	能: 匹配滤波器
//参	数: 
//			a_nHarm				谐波次数
//			m_pParamRe			计算系数的实部
//			m_pParamIm			计算系数的虚部
//			a_nWavePoints		每周波点数目
//返 回	值: 
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CGenerateReport::Dist_FilterPara(int a_nHarm,float* a_pParamRe,float* a_pParamIm,int a_nWavePoints/*=20*/)
{
    float dfi;
    int ndots = a_nWavePoints/20;
    for(int i=0; i<20*ndots; i++)
    {
        dfi = (float)(m_dPI/180. * (18.0/ndots*a_nHarm) * i);
        a_pParamRe[i] = (float)(cos(dfi)/10./ndots);
        a_pParamIm[i] = (float)(sin(dfi)/10./ndots);
    }
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
void CGenerateReport::Dist_WaveFilter(float* a_pData,int a_nPoints,int a_nWavePoints,float* a_pParam,int a_nCount,float* a_pResult,bool a_bConvert/* = false*/)
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

//////////////////////////////////////////////////////////////////////////
//功	能: 计算突变点
//参	数: 
//			a_dMaxI				额定电流
//			a_pIa				A相电流
//			a_pIb				B相电流
//			a_pIc				C相电流
//			a_nWavePoints		每周波点数目
//			a_pStarttype		结果
//返 回	值: 突变次数;不满足突变条件时返回0
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int	CGenerateReport::Dist_FindStartPoint(float a_dMaxI,float* a_pIa,float* a_pIb,float* a_pIc,int a_nWavePoints,tagStarttype* a_pStarttype)
{
    float IQD=(float)(0.2*a_dMaxI);		//突变的门槛值//是否可靠??
    float temp1,temp2,temp3,temp4,temp5;
    int ndots = a_nWavePoints/20;
    //PAB
    temp1 = (float)(fabs(a_pIa[20*ndots] - a_pIa[0*ndots]));
    temp2 = (float)(fabs(a_pIb[20*ndots] - a_pIb[0*ndots]));
    temp3 = (float)(fabs(temp1-temp2));
    temp1 = (float)(fabs(a_pIa[40*ndots] - a_pIa[20*ndots]));
    temp2 = (float)(fabs(a_pIb[40*ndots] - a_pIb[20*ndots]));
    temp4 = (float)(fabs(temp1-temp2));
    temp5 = (float)(fabs(temp3-temp4));
    if(temp5 >= IQD)
    {
        a_pStarttype->nabStartPoints++;
        a_pStarttype->nStartFlag = 1;
    }
    //PBC
    temp1 = (float)(fabs(a_pIb[20*ndots] - a_pIb[0*ndots]));
    temp2 = (float)(fabs(a_pIc[20*ndots] - a_pIc[0*ndots]));
    temp3 = (float)(fabs(temp1-temp2));
    temp1 = (float)(fabs(a_pIb[40*ndots] - a_pIb[20*ndots]));
    temp2 = (float)(fabs(a_pIc[40*ndots] - a_pIc[20*ndots]));
    temp4 = (float)(fabs(temp1-temp2));
    temp5 = (float)(fabs(temp3-temp4));
    if(temp5>=IQD)
    {
        a_pStarttype->nbcStartPoints++;
        a_pStarttype->nStartFlag = 1;
    }
    //PCA
    temp1 = (float)(fabs(a_pIc[20*ndots] - a_pIc[0*ndots]));
    temp2 = (float)(fabs(a_pIa[20*ndots] - a_pIa[0*ndots]));
    temp3 = (float)(fabs(temp1-temp2));
    temp1 = (float)(fabs(a_pIc[40*ndots] - a_pIc[20*ndots]));
    temp2 = (float)(fabs(a_pIa[40*ndots] - a_pIa[20*ndots]));
    temp4 = (float)(fabs(temp1-temp2));
    temp5 = (float)(fabs(temp3-temp4));
    if(temp5>=IQD)
    {
        a_pStarttype->ncaStartPoints++;
        a_pStarttype->nStartFlag = 1;
    }

    if(a_pStarttype->nStartFlag==1)
    {
        a_pStarttype->nabcStartPoints++;

        if(a_pStarttype->nabcStartPoints < 8)
        {
            if((a_pStarttype->nabStartPoints>=4)||(a_pStarttype->nbcStartPoints>=4)||(a_pStarttype->ncaStartPoints>=4))
            {
                return a_pStarttype->nabcStartPoints;
            }
        }
        else
        {
            if(a_pStarttype->nabcStartPoints < 16)
            {
            	if((a_pStarttype->nabStartPoints>=8)||(a_pStarttype->nbcStartPoints>=8)||(a_pStarttype->ncaStartPoints>=8))
                {
                    return a_pStarttype->nabcStartPoints;
                }
            }
            else
            {
                a_pStarttype->nStartFlag = 0;
                a_pStarttype->nabcStartPoints = 0;
                a_pStarttype->nabStartPoints = 0;
                a_pStarttype->nbcStartPoints = 0;
                a_pStarttype->ncaStartPoints = 0;
            }
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算相间阻抗
//参	数: 
//			a_pDataU			相电压数据
//			a_pDataI			相电流数据
//			a_dR				计算结果(电阻)
//			a_dX				计算结果(电抗)
//返 回	值: 
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CGenerateReport::Dist_CalRX_PP(float* a_pDataU,float* a_pDataI,float& a_dR,float& a_dX)
{
    float u1,u2,i1,i2,d1,d2,det;

    i1=(float)(0.5*(a_pDataI[0] + a_pDataI[1]));//0，1，2是否按20点采样？
    i2=(float)(0.5*(a_pDataI[1] + a_pDataI[2]));
    u1=(float)(0.5*(a_pDataU[0] + a_pDataU[1]));
    u2=(float)(0.5*(a_pDataU[1] + a_pDataU[2]));
    d1=(float)((a_pDataI[1]-a_pDataI[0])/0.001);
    d2=(float)((a_pDataI[2]-a_pDataI[1])/0.001);
    det=(float)(i2*d1-i1*d2);
    if(det)
    {
        a_dX = (u1*i2-u2*i1)/det;
        a_dR = (u2*d1-u1*d2)/det;

        a_dX = (float)(2.*m_dPI*m_nFreq*a_dX);
    }
    return;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算相间阻抗
//参	数: 
//			a_pDataU			相电压数据
//			a_pDataI			相电流数据
//			a_dR				计算结果(电阻)
//			a_dX				计算结果(电抗)
//返 回	值: 0:失败;1:成功
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_CalRXEx_PP(float* a_pDataU,float* a_pDataI,float& a_dR,float& a_dX)
{
    double u1,u2,i1,i2,d1,d2,det;

    float ivalue = (float)(sqrt(a_pDataI[0]*a_pDataI[0] + a_pDataI[5]*a_pDataI[5]));

    if(a_pDataI[1]>(0.9*ivalue))
    {
        return 0;
    }

    i1=a_pDataI[1];//0，1，2是否按20点采样？
    i2=a_pDataI[2];

    u1=a_pDataU[1];
    u2=a_pDataU[2];

    d1=(2.0*m_dPI*m_nFreq*(a_pDataI[2]-a_pDataI[0])/(2.*sin(0.1*m_dPI)));
    d2=(2.0*m_dPI*m_nFreq*(a_pDataI[3]-a_pDataI[1])/(2.*sin(0.1*m_dPI)));

    det=i2*d1-i1*d2;
    if(det)
    {
        a_dX=(float)((u1*i2-u2*i1)/det);
        a_dR=(float)((u2*d1-u1*d2)/det);

        a_dX=(float)((2.*m_dPI*m_nFreq*a_dX));
	
        return 1;
    }
    else
    {
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算单相对地阻抗
//参	数: 
//			a_pDataU			相电压数据
//			a_pDataI			相电流数据
//			a_pDataI0			零序电流数据 
//			a_dFactor			计算参数
//			a_dR				计算结果(电阻)
//			a_dRe				计算结果(电抗)
//返 回	值: 0:失败;1:成功
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_CalRX_PG1(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float a_dFactor,float& a_dR,float& a_dX)
{
    float u1,u2,i1,i2,d1,d2,det;

    float ivalue = (float)(sqrt(a_pDataI[0]*a_pDataI[0] + a_pDataI[5]*a_pDataI[5]));
    if(a_pDataI[1] > (0.9* ivalue))
        return 0;

    i1=a_pDataI[1]+a_dFactor*a_pDataI0[1];
    i2=a_pDataI[2]+a_dFactor*a_pDataI0[2];

    u1=a_pDataU[1];
    u2=a_pDataU[2];

    d1=(float)((2.0*m_dPI*m_nFreq*((a_pDataI[2]-a_pDataI[0])+a_dFactor*(a_pDataI0[2]-a_pDataI0[0]))/(2.*sin(0.1*m_dPI))));
    d2=(float)((2.0*m_dPI*m_nFreq*((a_pDataI[3]-a_pDataI[1])+a_dFactor*(a_pDataI0[3]-a_pDataI0[1]))/(2.*sin(0.1*m_dPI))));

    det=i2*d1-i1*d2;

    if(det)
    {
        a_dX=(float)((u1*i2-u2*i1)/det);
        a_dR=(float)((u2*d1-u1*d2)/det);

        a_dX=(float)((2.*m_dPI*m_nFreq*a_dX));
	
        return 1;
    }
    else
    {
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算单相对地阻抗
//参	数: 
//			a_pDataU			相电压数据
//			a_pDataI			相电流数据
//			a_pDataI0			零序电流数据 
//			a_dFactor			计算参数
//			a_dR				计算结果(电阻)
//			a_dRe				计算结果(电抗)
//返 回	值:
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CGenerateReport::Dist_CalRX_PG2(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float a_dFactor,float& a_dR,float& a_dX)
{
    float u1,u2,i1,i2,d1,d2,det;

    i1=(float)(0.5*((a_pDataI[1]+a_pDataI[0])+a_dFactor*(a_pDataI0[0]+a_pDataI0[1])));
    i2=(float)(0.5*((a_pDataI[2]+a_pDataI[1])+a_dFactor*(a_pDataI0[1]+a_pDataI0[2])));

    u1=(float)(0.5*(a_pDataU[0]+a_pDataU[1]));
    u2=(float)(0.5*(a_pDataU[1]+a_pDataU[2]));

    d1=(float)(((a_pDataI[1]-a_pDataI[0])+a_dFactor*(a_pDataI0[1]-a_pDataI0[0]))/0.001);
    d2=(float)(((a_pDataI[2]-a_pDataI[1])+a_dFactor*(a_pDataI0[2]-a_pDataI0[1]))/0.001);

    det=i2*d1-i1*d2;

    if(det)
    {
        a_dX=(float)((u1*i2-u2*i1)/det);
        a_dR=(float)((u2*d1-u1*d2)/det);

        a_dX=(float)(2.*m_dPI*m_nFreq*a_dX);
    }
    return;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算单相对地阻抗
//参	数: 
//			a_pDataU			相电压数据
//			a_pDataI			相电流数据
//			a_pDataI0			零序电流数据 
//			a_dFactor			计算参数
//			a_dR0				零序电阻
//			a_dR1				正序电阻
//			a_dX0				零序电抗
//			a_dX1				正序电抗
//			a_dR				计算结果(电阻)
//			a_dX				计算结果(电抗)
//返 回	值: 0:失败;1:成功
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_CalRX_PG3(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float a_dR0,float a_dR1,float a_dX0,float a_dX1,float& a_dR,float& a_dX)
{
    float u1,u2,i1,i2,d1,d2,det;

    float kr = (float)((a_dR0-a_dR1)/3./a_dR1);
    float kl = (float)((a_dX0-a_dX1)/3./a_dX1);
    float rlbl = (float)(a_dR1*2*m_dPI*m_nFreq/a_dX1);
    float ivalue = (float)(sqrt(a_pDataI[0]*a_pDataI[0] + a_pDataI[5]*a_pDataI[5]));
    if(a_pDataI[1] > (0.9* ivalue))
    {
        return 0;
    }

    u1=(float)(0.5*(a_pDataU[0]+a_pDataU[1]));
    u2=(float)(0.5*(a_pDataU[1]+a_pDataU[2]));
    
    i1=(float)(0.5*(a_pDataI0[0]+a_pDataI0[1]));
    i2=(float)(0.5*(a_pDataI0[1]+a_pDataI0[2]));

    d1=(float)(0.5*rlbl*(a_pDataI[0]+kr*a_pDataI0[0]+a_pDataI[1]+kr*a_pDataI0[1])+(a_pDataI[1]+kl*a_pDataI0[1]-a_pDataI[0]-kl*a_pDataI0[0])/0.001);
    d2=(float)(0.5*rlbl*(a_pDataI[1]+kr*a_pDataI0[1]+a_pDataI[2]+kr*a_pDataI0[2])+(a_pDataI[2]+kl*a_pDataI0[2]-a_pDataI[1]-kl*a_pDataI0[1])/0.001);

    det=i2*d1-i1*d2;

    if(det)
    {
        a_dX=(float)((u1*i2-u2*i1)/det);
        a_dR=(float)((u2*d1-u1*d2)/det);

        a_dX=(float)(2.*m_dPI*m_nFreq*a_dX);
	
        return 1;
    }
    else
    {
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算单相对地阻抗
//参	数: 
//			a_pDataU			相电压数据
//			a_pDataI			相电流数据
//			a_pDataI0			零序电流数据 
//			a_dFactor			计算参数
//			a_dR0				零序电阻
//			a_dR1				正序电阻
//			a_dX0				零序电抗
//			a_dX1				正序电抗
//			a_dR				计算结果(电阻)
//			a_dX				计算结果(电抗)
//返 回	值: 0:失败;1:成功
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_CalRX_PG4(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float a_dR0,float a_dR1,float a_dX0,float a_dX1,float& a_dR,float& a_dX)
{
    //基本公式：Ua=Ud+(Ia+k3I0)LZ1
    float u1,u2,i1,i2,d1,d2,det;
    float kr = (float)((a_dR0-a_dR1)/3./a_dR1);			//零序补偿系数
    float kl = (float)((a_dX0-a_dX1)/3./a_dX1);			//
    float rlbl = (float)(a_dR1*2*m_dPI*m_nFreq/a_dX1);	//2*PI*f*R1/X1=r1/l1

    //////////////////////////////////////////////////////////////////////////
    //这里是否是判断一个计算盲点?(根据有效值和下一点瞬时值判断)
    float ivalue = (float)(sqrt(a_pDataI[0]*a_pDataI[0] + a_pDataI[5]*a_pDataI[5]));	//有效值
    if(a_pDataI[1] > (0.9* ivalue))
    {
        return 0;
    }

    u1=a_pDataU[1];
    u2=a_pDataU[2];
    
    i1=a_pDataI0[1];
    i2=a_pDataI0[2];

    d1=(float)(rlbl*(a_pDataI[1]+kr*a_pDataI0[1])+2.*m_dPI*m_nFreq*(a_pDataI[2]+kl*a_pDataI0[2]-a_pDataI[0]-kl*a_pDataI0[0])/(2.*sin(0.1*m_dPI)));
    d2=(float)(rlbl*(a_pDataI[2]+kr*a_pDataI0[2])+2.*m_dPI*m_nFreq*(a_pDataI[3]+kl*a_pDataI0[3]-a_pDataI[1]-kl*a_pDataI0[1])/(2.*sin(0.1*m_dPI)));

    det=i2*d1-i1*d2;

    if(det)
    {
        a_dX=(float)((u1*i2-u2*i1)/det);
        a_dR=(float)((u2*d1-u1*d2)/det);

        a_dX=(float)(2.*m_dPI*m_nFreq*a_dX);
	
        return 1;
    }
    else
    {
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 测距
//参	数: 
//			a_pDataU[3]			分别为Ua、Ub、Uc数据(原始数据)
//			a_pDataI[4]			分别为Ia、Ib、Ic、In数据(原始数据)
//			a_nCalPos			计算位置在原始数据中的偏移
//			a_nWavePoints		每周波点数目
//			a_dFactor			测距系数
//			a_nFaultKind		故障类型(选相结果)
//			a_dR				电阻(结果)
//			a_dX				电抗
//返 回	值: 1成功,0失败
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_CalDistance1(float* a_pDataU[3],float* a_pDataI[4],int a_nCalPos,int a_nWavePoints,float a_dFactor,int a_nFaultKind,float& a_dR,float& a_dX)
{
    int tmp=0;

    float uaFilter[50],ubFilter[50],ucFilter[50];
    float iaFilter[50],ibFilter[50],icFilter[50],i0Filter[50];
    float uabFilter[50],ubcFilter[50],ucaFilter[50];
    float iabFilter[50],ibcFilter[50],icaFilter[50];

    float uaFilter2[50],ubFilter2[50],ucFilter2[50];
    float iaFilter2[50],ibFilter2[50],icFilter2[50],i0Filter2[50];
    int i=0;
    
    int filterlen = 21;
    Dist_WaveFilter(a_pDataU[0]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,uaFilter2);
    Dist_WaveFilter(a_pDataU[1]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,ubFilter2);
    Dist_WaveFilter(a_pDataU[2]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,ucFilter2);

    Dist_WaveFilter(uaFilter2,26,a_nWavePoints,m_dParam,filterlen,uaFilter);
    Dist_WaveFilter(ubFilter2,26,a_nWavePoints,m_dParam,filterlen,ubFilter);
    Dist_WaveFilter(ucFilter2,26,a_nWavePoints,m_dParam,filterlen,ucFilter);
    
    Dist_WaveFilter(a_pDataI[0]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,iaFilter2);
    Dist_WaveFilter(a_pDataI[1]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,ibFilter2);
    Dist_WaveFilter(a_pDataI[2]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,icFilter2);
    Dist_WaveFilter(a_pDataI[3]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,i0Filter2);

    Dist_WaveFilter(iaFilter2,26,a_nWavePoints,m_dParam,filterlen,iaFilter);
    Dist_WaveFilter(ibFilter2,26,a_nWavePoints,m_dParam,filterlen,ibFilter);
    Dist_WaveFilter(icFilter2,26,a_nWavePoints,m_dParam,filterlen,icFilter);
    Dist_WaveFilter(i0Filter2,26,a_nWavePoints,m_dParam,filterlen,i0Filter);

    //float icvalue = sqrt(0.5*(icFilter[0]*icFilter[0] + icFilter[5]*icFilter[5]));
    //float i0value = sqrt(0.5*(i0Filter[0]*i0Filter[0] + i0Filter[5]*i0Filter[5]));

    for(i=0; i<10; i++)
    {
        uabFilter[i] = uaFilter[i] - ubFilter[i];
        ubcFilter[i] = ubFilter[i] - ucFilter[i];
        ucaFilter[i] = ucFilter[i] - uaFilter[i];
        iabFilter[i] = iaFilter[i] - ibFilter[i];
        ibcFilter[i] = ibFilter[i] - icFilter[i];
        icaFilter[i] = icFilter[i] - iaFilter[i];
    }

    switch (a_nFaultKind)
    {
    case  FAULT_AN:
        tmp = Dist_CalRX_PG1(uaFilter,iaFilter,i0Filter,a_dFactor,a_dR,a_dX);
        break;
    case  FAULT_BN:
        tmp = Dist_CalRX_PG1(ubFilter,ibFilter,i0Filter,a_dFactor,a_dR,a_dX);
        break;
    case  FAULT_CN:
        tmp = Dist_CalRX_PG1(ucFilter,icFilter,i0Filter,a_dFactor,a_dR,a_dX);
        break;
    case  FAULT_AB:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BC:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CA:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABN:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BCN:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CAN:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABC:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    }

#ifndef GDWY_JIANCE
    if(a_dX < 0)
        a_dX = -a_dX;
#endif
    return tmp;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 测距
//参	数: 
//			a_pDataU[3]			分别为Ua、Ub、Uc数据
//			a_pDataI[4]			分别为Ia、Ib、Ic、In数据
//			a_nCalPos			计算位置在原始数据中的偏移
//			a_nWavePoints		每周波点数目
//			a_dRX[4]			分别为r0,r1,x0,x1
//			a_nFaultKind		故障类型(选相结果)
//			a_dR				电阻(结果)
//			a_dX				电抗
//			a_bConvert			是否为零序反相
//返 回	值: 1成功,0失败
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 2016-12-27        修正尾端经过渡电阻接地
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_CalDistance2(float* a_pDataU[3],float* a_pDataI[4],int a_nCalPos,int a_nWavePoints,float a_dRX[4],int a_nFaultKind,float& a_dR,float& a_dX,float fLineX,bool a_bConvert/* = false*/)
{
    int tmp=0;

    float uaFilter[50],ubFilter[50],ucFilter[50];
    float iaFilter[50],ibFilter[50],icFilter[50],i0Filter[50];
    float uabFilter[50],ubcFilter[50],ucaFilter[50];
    float iabFilter[50],ibcFilter[50],icaFilter[50];

    float uaFilter2[50],ubFilter2[50],ucFilter2[50];
    float iaFilter2[50],ibFilter2[50],icFilter2[50],i0Filter2[50];
    int i=0;
    int filterlen = 21;

    ///////////////////////////////////////////////////////////////////////////////////////
    //三相电压经过两次滤波
    //输入Ua,ub,uc,输出: uaFilter,ubFilter,ucFilter
    //[[
    Dist_WaveFilter(a_pDataU[0]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,uaFilter2);
    Dist_WaveFilter(a_pDataU[1]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,ubFilter2);
    Dist_WaveFilter(a_pDataU[2]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,ucFilter2);

    Dist_WaveFilter(uaFilter2,26,20,m_dParam,filterlen,uaFilter);
    Dist_WaveFilter(ubFilter2,26,20,m_dParam,filterlen,ubFilter);
    Dist_WaveFilter(ucFilter2,26,20,m_dParam,filterlen,ucFilter);
    //]]
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    //电流滤波
    //输入Ia,Ib,Ic,I0，输出: iaFilter,ibFilter,icFilter,i0Filter
    //[[
    Dist_WaveFilter(a_pDataI[0]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,iaFilter2);
    Dist_WaveFilter(a_pDataI[1]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,ibFilter2);
    Dist_WaveFilter(a_pDataI[2]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,icFilter2);
    Dist_WaveFilter(a_pDataI[3]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,i0Filter2,a_bConvert);

    Dist_WaveFilter(iaFilter2,26,20,m_dParam,filterlen,iaFilter);
    Dist_WaveFilter(ibFilter2,26,20,m_dParam,filterlen,ibFilter);
    Dist_WaveFilter(icFilter2,26,20,m_dParam,filterlen,icFilter);
    Dist_WaveFilter(i0Filter2,26,20,m_dParam,filterlen,i0Filter);
    //]]

    //float icvalue = sqrt(0.5*(icFilter[0]*icFilter[0] + icFilter[5]*icFilter[5]));
    //float i0value = sqrt(0.5*(i0Filter[0]*i0Filter[0] + i0Filter[5]*i0Filter[5]));

    //////////////////////////////////////////////////////////////////////////
    //计算uab,ubc,uca,iab,ibc,ica
    //[[
    for(i=0;i<10;i++)
    {
        uabFilter[i] = uaFilter[i] - ubFilter[i];
        ubcFilter[i] = ubFilter[i] - ucFilter[i];
        ucaFilter[i] = ucFilter[i] - uaFilter[i];
        iabFilter[i] = iaFilter[i] - ibFilter[i];
        ibcFilter[i] = ibFilter[i] - icFilter[i];
        icaFilter[i] = icFilter[i] - iaFilter[i];
    }
    //]]

    //////////////////////////////////////////////////////////////////////////
    //调用测距函数计算阻抗
    //[[
    const float fRg = 10;                   //判断是否经过渡电阻接地 (2016-12-27加)
    const float fXe = fLineX*.75;    //线路总电抗*.7
    float fRX = a_dRX[1]/a_dRX[3];          //r1/x1
    switch (a_nFaultKind)
    {
    case  FAULT_AN:
        {
            tmp = Dist_CalRX_PG4(uaFilter,iaFilter,i0Filter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,iaFilter,ibFilter,icFilter,i0Filter,fRX);
            }
//            if(a_dX > 0.86*fLineX)
//            {
//                a_dX = 0.987432*fLineX;
//            }
        }
        break;
    case  FAULT_BN:
        {
            tmp = Dist_CalRX_PG4(ubFilter,ibFilter,i0Filter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dR,a_dX);          
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,ibFilter,icFilter,iaFilter,i0Filter,fRX);
            }
//            if(a_dX > 0.86*fLineX)
//            {
//                a_dX = 0.987432*fLineX;
//            }
        }

        break;
    case  FAULT_CN:
        {
            tmp = Dist_CalRX_PG4(ucFilter,icFilter,i0Filter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,icFilter,iaFilter,ibFilter,i0Filter,fRX);
            }
//            if(a_dX > 0.86*fLineX)
//            {
//                a_dX = 0.987432*fLineX;
//            }
        }
        break;
    case  FAULT_AB:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BC:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CA:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABN:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BCN:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CAN:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABC:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    }
    //]]

#ifndef GDWY_JIANCE
    if(a_dX < 0)
        a_dX = -a_dX;
#endif

    return tmp;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 测距
//参	数: 
//			a_pDataU[3]			分别为Ua、Ub、Uc数据
//			a_pDataI[4]			分别为Ia、Ib、Ic、In数据
//			a_nCalPos			计算位置在原始数据中的偏移
//			a_nWavePoints		每周波点数目
//			a_dRX[4]			分别为r0,r1,x0,x1
//			a_nFaultKind		故障类型(选相结果)
//			a_dR				电阻(结果)
//			a_dX				电抗
//			a_bConvert			是否为零序反相
//返 回	值: 1成功,0失败
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//修改记录: 2016-12-27        修正尾端经过渡电阻接地
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_CalDistance3(float* a_pDataU[3],float* a_pDataI[4],int a_nCalPos,int a_nWavePoints,float a_dRX[4],int a_nFaultKind,float& a_dR,float& a_dX,float fLineX,bool a_bConvert/* = false*/)
{
    int tmp=0;

    float uaFilter[50] = {0};
    float ubFilter[50] = {0};
    float ucFilter[50] = {0};
    float iaFilter[50],ibFilter[50],icFilter[50],i0Filter[50];
    float uabFilter[50],ubcFilter[50],ucaFilter[50];
    float iabFilter[50],ibcFilter[50],icaFilter[50];
    int i=0;
    int filterlen = 21;

    Dist_WaveFilter(a_pDataU[0]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,uaFilter);
    Dist_WaveFilter(a_pDataU[1]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,ubFilter);
    Dist_WaveFilter(a_pDataU[2]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,ucFilter);

    Dist_WaveFilter(a_pDataI[0]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,iaFilter);
    Dist_WaveFilter(a_pDataI[1]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,ibFilter);
    Dist_WaveFilter(a_pDataI[2]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,icFilter);
    Dist_WaveFilter(a_pDataI[3]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,i0Filter,a_bConvert);

    //float icvalue = sqrt(0.5*(icFilter[0]*icFilter[0] + icFilter[5]*icFilter[5]));
    //float i0value = sqrt(0.5*(i0Filter[0]*i0Filter[0] + i0Filter[5]*i0Filter[5]));

    for(i=0;i<10;i++)
    {
        uabFilter[i] = uaFilter[i] - ubFilter[i];
        ubcFilter[i] = ubFilter[i] - ucFilter[i];
        ucaFilter[i] = ucFilter[i] - uaFilter[i];
        iabFilter[i] = iaFilter[i] - ibFilter[i];
        ibcFilter[i] = ibFilter[i] - icFilter[i];
        icaFilter[i] = icFilter[i] - iaFilter[i];
    }

    //2016-12-27
    const float fRg = 10;                   //判断是否经过渡电阻接地 (2016-12-27加)
    const float fXe = fLineX*.75;    //线路总电抗*.7
    float fRX = a_dRX[1]/a_dRX[3];          //r1/x1

    switch (a_nFaultKind)
    {
    case  FAULT_AN:
        {
            tmp = Dist_CalRX_PG4(uaFilter,iaFilter,i0Filter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,iaFilter,ibFilter,icFilter,i0Filter,fRX);
            }
        }
        break;
    case  FAULT_BN:
        {
            tmp = Dist_CalRX_PG4(ubFilter,ibFilter,i0Filter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,ibFilter,icFilter,iaFilter,i0Filter,fRX);
            }
        }
        break;
    case  FAULT_CN:
        {
            tmp = Dist_CalRX_PG4(ucFilter,icFilter,i0Filter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,icFilter,iaFilter,ibFilter,i0Filter,fRX);
            }
        }
        break;
    case  FAULT_AB:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BC:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CA:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABN:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BCN:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CAN:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABC:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    }

#ifndef GDWY_JIANCE
    if(a_dX < 0)
        a_dX = -a_dX;
#endif

    return tmp;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 10点求和
//参	数: 
//			a_pData			输入数据
//返 回	值: 和
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CGenerateReport::Dist_CalSum(float* a_pData)
{
    float dsum = 0;
    for(int i=0; i<10; i++)
    {
        dsum += (float)(fabs(a_pData[i]));
    }
    return dsum;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 10点求和
//参	数: 
//			a_pDataI		输入数据
//			a_pDataII		输入数据
//返 回	值: 和
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CGenerateReport::Dist_CalSum(float* a_pDataI,float* a_pDataII)
{
    float dsum=0;
    for(int i=0; i<10; i++)
    {
        dsum += (float)(fabs(a_pDataI[i] - a_pDataII[i]));
    }
    return dsum;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 选相
//参	数: 
//			a_dMaxI			额定电流
//			a_pData			Ia、Ib、Ic数据(已经在计算位置)
//			a_nWavePoints	每周波点数目
//			a_nPoints		数据长度
//			a_nFaultType	上次计算的结果
//			a_nFaultPos		突变位置
//返 回	值: 
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 2008-01-21		wpf		将此处额定电流统一取1A
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_FindFaultType_Inf(float a_dMaxI,float* a_pIa,float* a_pIb,float* a_pIc,int a_nWavePoints,int a_nPoints,int a_nFaultType,int& a_nFaultPos)
{
    int faulttype = FAULT_NOTDF;
    tagStarttype tblqd;
    float *iatemp, *ibtemp, *ictemp;
    int i, backpoints, faultp;
    float iaVector0[2], ibVector0[2], icVector0[2];
    float iaVector1[2], ibVector1[2], icVector1[2];
    float iaVector2[2], ibVector2[2], icVector2[2];
    float detIbc, detIca, detIab, detIa, detIb, detIc;
    float detIbcT, detIcaT, detIabT, detIaT, detIbT, detIcT;
    float MAXdetI;
    float maxDetff,midDetff,minDetff;
    Q_UNUSED(midDetff);
    float re20[20] = {0};
    float img20[20] = {0};
    float Ia1,Ib1,Ic1,Ia2,Ib2,Ic2,Iab1,Ibc1,Ica1,Iab2,Ibc2,Ica2;
    float I00, II0;
    // wpf 固定而定电流为1[1/21/2008]
    // wpf 如果额定电流>1时修改
    if(a_dMaxI > 1)
    {
        a_dMaxI = 1;
    }

    //wpf 2020-1-10修改为0.3倍
//    float IXX=(float)(0.2*a_dMaxI);
    float IXX=(float)(0.3*a_dMaxI);
    int ndots = a_nWavePoints/20;

    tblqd.nStartFlag = 0;
    tblqd.nabcStartPoints = 0;
    tblqd.nabStartPoints = 0;
    tblqd.nbcStartPoints=0;
    tblqd.ncaStartPoints=0;

    iatemp = a_pIa;
    ibtemp = a_pIb;
    ictemp = a_pIc;

    //判故障点
    for(i=0; i<a_nPoints-40*ndots; i+=ndots)
    {
        backpoints = Dist_FindStartPoint(a_dMaxI, iatemp,ibtemp,ictemp,a_nWavePoints,&tblqd);
        if(backpoints > 0)
        {
            break;
        }
        iatemp += ndots;
        ibtemp += ndots;
        ictemp += ndots;
    }

    //判故障，工频变化量方法
    if(i>=a_nPoints - 40*ndots)
    {
        a_nFaultPos = a_nPoints-40*ndots;
        return FAULT_NONE;
    }

    faultp = (int)(iatemp-a_pIa)+(40-backpoints)*ndots;
    a_nFaultPos = faultp;

    //计算
    if(faultp>=40*ndots)
    {
        iatemp = a_pIa+(faultp-40*ndots);
        ibtemp = a_pIb+(faultp-40*ndots);
        ictemp = a_pIc+(faultp-40*ndots);
    }
    else
    {
        iatemp = a_pIa;
        ibtemp = a_pIb;
        ictemp = a_pIc;
    }
    Dist_FilterPara(1, re20, img20);
    Dist_DFT(iatemp,a_nWavePoints,re20,img20,20,iaVector0[0],iaVector0[1]);
    Dist_DFT(ibtemp,a_nWavePoints,re20,img20,20,ibVector0[0],ibVector0[1]);
    Dist_DFT(ictemp,a_nWavePoints,re20,img20,20,icVector0[0],icVector0[1]);

    iatemp = a_pIa+(faultp-20*ndots);
    ibtemp = a_pIb+(faultp-20*ndots);
    ictemp = a_pIc+(faultp-20*ndots);

    Dist_DFT(iatemp,a_nWavePoints, re20, img20, 20,iaVector1[0],iaVector1[1]);
    Dist_DFT(ibtemp,a_nWavePoints, re20, img20, 20,ibVector1[0],ibVector1[1]);
    Dist_DFT(ictemp,a_nWavePoints, re20, img20, 20,icVector1[0],icVector1[1]);

    iatemp = a_pIa+faultp;
    ibtemp = a_pIb+faultp;
    ictemp = a_pIc+faultp;
    //i0temp = i0+faultp;

    Dist_DFT(iatemp,a_nWavePoints, re20, img20, 20,iaVector2[0],iaVector2[1]);
    Dist_DFT(ibtemp,a_nWavePoints, re20, img20, 20,ibVector2[0],ibVector2[1]);
    Dist_DFT(ictemp,a_nWavePoints, re20, img20, 20,icVector2[0],icVector2[1]);
    //Dft(i0temp, i0Vector2, re20, img20, 20);
    //	qDebug("ia0  %g   %g\n",iaVector0[0],iaVector0[1]);
    //	qDebug("ia1  %g   %g\n",iaVector1[0],iaVector1[1]);
    //	qDebug("ib0  %g   %g\n",ibVector0[0],ibVector0[1]);
    //	qDebug("ib1  %g   %g\n",ibVector1[0],ibVector1[1]);
    //	qDebug("ic0  %g   %g\n",icVector0[0],icVector0[1]);
    //	qDebug("ic1  %g   %g\n",icVector1[0],icVector1[1]);

    //单相幅值
    Ia1 = (float)(sqrt(iaVector1[0]*iaVector1[0] + iaVector1[1]*iaVector1[1]));
    Ib1 = (float)(sqrt(ibVector1[0]*ibVector1[0] + ibVector1[1]*ibVector1[1]));
    Ic1 = (float)(sqrt(icVector1[0]*icVector1[0] + icVector1[1]*icVector1[1]));

    //相间幅值
    Iab1 = (float)(sqrt((iaVector1[0]-ibVector1[0]) * (iaVector1[0]-ibVector1[0])
                        +(iaVector1[1]-ibVector1[1]) * (iaVector1[1]-ibVector1[1])));
    Ibc1 = (float)(sqrt((ibVector1[0]-icVector1[0]) * (ibVector1[0]-icVector1[0])
                        +(ibVector1[1]-icVector1[1]) * (ibVector1[1]-icVector1[1])));
    Ica1 = (float)(sqrt((icVector1[0]-iaVector1[0]) * (icVector1[0]-iaVector1[0])
                        +(icVector1[1]-iaVector1[1]) * (icVector1[1]-iaVector1[1])));

    Ia2 = (float)(sqrt(iaVector2[0]*iaVector2[0] + iaVector2[1]*iaVector2[1]));
    Ib2 = (float)(sqrt(ibVector2[0]*ibVector2[0] + ibVector2[1]*ibVector2[1]));
    Ic2 = (float)(sqrt(icVector2[0]*icVector2[0] + icVector2[1]*icVector2[1]));

    Iab2 = (float)(sqrt((iaVector2[0]-ibVector2[0]) * (iaVector2[0]-ibVector2[0])
                        +(iaVector2[1]-ibVector2[1]) * (iaVector2[1]-ibVector2[1])));
    Ibc2 = (float)(sqrt((ibVector2[0]-icVector2[0]) * (ibVector2[0]-icVector2[0])
                        +(ibVector2[1]-icVector2[1]) * (ibVector2[1]-icVector2[1])));
    Ica2 = (float)(sqrt((icVector2[0]-iaVector2[0]) * (icVector2[0]-iaVector2[0])
                        +(icVector2[1]-iaVector2[1]) * (icVector2[1]-iaVector2[1])));

    detIaT = (float)(sqrt((iaVector1[0]-iaVector0[0]) * (iaVector1[0]-iaVector0[0])
                          +(iaVector1[1]-iaVector0[1]) * (iaVector1[1]-iaVector0[1])));

    detIbT = (float)(sqrt((ibVector1[0]-ibVector0[0]) * (ibVector1[0]-ibVector0[0])
                          +(ibVector1[1]-ibVector0[1]) * (ibVector1[1]-ibVector0[1])));

    detIcT = (float)(sqrt((icVector1[0]-icVector0[0]) * (icVector1[0]-icVector0[0])
                          +(icVector1[1]-icVector0[1]) * (icVector1[1]-icVector0[1])));

    detIa = (float)(sqrt((iaVector1[0]-iaVector2[0]) * (iaVector1[0]-iaVector2[0])
                         +(iaVector1[1]-iaVector2[1]) * (iaVector1[1]-iaVector2[1])));

    detIb = (float)(sqrt((ibVector1[0]-ibVector2[0]) * (ibVector1[0]-ibVector2[0])
                         +(ibVector1[1]-ibVector2[1]) * (ibVector1[1]-ibVector2[1])));

    detIc = (float)(sqrt((icVector1[0]-icVector2[0]) * (icVector1[0]-icVector2[0])
                         +(icVector1[1]-icVector2[1]) * (icVector1[1]-icVector2[1])));

    if(detIa > detIb)
        MAXdetI = detIa;
    else
        MAXdetI = detIb;
    if(detIc > MAXdetI)
        MAXdetI = detIc;

    detIabT = (float)(sqrt(((iaVector1[0]-iaVector0[0]) - (ibVector1[0]-ibVector0[0]))
                           *((iaVector1[0]-iaVector0[0]) - (ibVector1[0]-ibVector0[0]))
                           +((iaVector1[1]-iaVector0[1]) - (ibVector1[1]-ibVector0[1]))
                           *((iaVector1[1]-iaVector0[1]) - (ibVector1[1]-ibVector0[1]))));

    detIbcT = (float)(sqrt(((ibVector1[0]-ibVector0[0]) - (icVector1[0]-icVector0[0]))
                           *((ibVector1[0]-ibVector0[0]) - (icVector1[0]-icVector0[0]))
                           +((ibVector1[1]-ibVector0[1]) - (icVector1[1]-icVector0[1]))
                           *((ibVector1[1]-ibVector0[1]) - (icVector1[1]-icVector0[1]))));

    detIcaT = (float)(sqrt(((icVector1[0]-icVector0[0]) - (iaVector1[0]-iaVector0[0]))
                           *((icVector1[0]-icVector0[0]) - (iaVector1[0]-iaVector0[0]))
                           +((icVector1[1]-icVector0[1]) - (iaVector1[1]-iaVector0[1]))
                           *((icVector1[1]-icVector0[1]) - (iaVector1[1]-iaVector0[1]))));

    detIab = (float)(sqrt(((iaVector1[0]-iaVector2[0]) - (ibVector1[0]-ibVector2[0]))
                          *((iaVector1[0]-iaVector2[0]) - (ibVector1[0]-ibVector2[0]))
                          +((iaVector1[1]-iaVector2[1]) - (ibVector1[1]-ibVector2[1]))
                          *((iaVector1[1]-iaVector2[1]) - (ibVector1[1]-ibVector2[1]))));

    detIbc = (float)(sqrt(((ibVector1[0]-ibVector2[0]) - (icVector1[0]-icVector2[0]))
                          *((ibVector1[0]-ibVector2[0]) - (icVector1[0]-icVector2[0]))
                          +((ibVector1[1]-ibVector2[1]) - (icVector1[1]-icVector2[1]))
                          *((ibVector1[1]-ibVector2[1]) - (icVector1[1]-icVector2[1]))));

    detIca = (float)(sqrt(((icVector1[0]-icVector2[0]) - (iaVector1[0]-iaVector2[0]))
                          *((icVector1[0]-icVector2[0]) - (iaVector1[0]-iaVector2[0]))
                          +((icVector1[1]-icVector2[1]) - (iaVector1[1]-iaVector2[1]))
                          *((icVector1[1]-icVector2[1]) - (iaVector1[1]-iaVector2[1]))));

    I00 = (float)(sqrt((iaVector1[0]+ibVector1[0]+icVector1[0])*(iaVector1[0]+ibVector1[0]+icVector1[0])
                       +(iaVector1[1]+ibVector1[1]+icVector1[1])*(iaVector1[1]+ibVector1[1]+icVector1[1])));

    II0 = (float)(sqrt((iaVector2[0]+ibVector2[0]+icVector2[0])*(iaVector2[0]+ibVector2[0]+icVector2[0])
                       +(iaVector2[1]+ibVector2[1]+icVector2[1])*(iaVector2[1]+ibVector2[1]+icVector2[1])));

    if(detIbc > detIab)
    {
        maxDetff = detIbc;
        minDetff = detIab;
    }
    else
    {
        maxDetff = detIab;
        minDetff = detIbc;
    }

    if(detIca > maxDetff)
    {
        midDetff = maxDetff;
        maxDetff = detIca;
    }
    else if(detIca < minDetff)
    {
        midDetff = minDetff;
        minDetff = detIca;
    }
    else
        midDetff = detIca;

    //	qDebug("detIa = %g  detIb=%g  detIc=%g\n",detIa,detIb,detIc);
    //	qDebug("detIab = %g  detIbc=%g  detIca=%g\n",detIab,detIbc,detIca);
    //wpf 2021-5-16 单相接地时判据有些不合理，fPNFactor原本为0.5，改为0.2
//    const float fPNFactor = 0.5;
    const float fPNFactor = 0.2;

    //选相（突变量）
    if((a_nFaultType == FAULT_OVER) || (a_nFaultType == FAULT_NONE) || (a_nFaultType == FAULT_NOTDF))
    {
        if((5*detIab < detIca) && (5*detIab < detIbc))
        {
            if(detIc > 1.25*detIcT + fPNFactor*MAXdetI + IXX)
            {
                if(II0 > (1.25*I00 + IXX))
                {
                    faulttype = FAULT_CN;
                }
                else if(I00 > (1.25*II0 + IXX))
                {
                    faulttype = FAULT_OVER;
                }
                else
                {
                    faulttype = FAULT_NOTDF;
                }
            }
            else
            {
                faulttype = FAULT_NOTDF;
            }
        }
        else if((5*detIbc < detIab) && (5*detIbc < detIca))
        {
            if(detIa > 1.25*detIaT + fPNFactor*MAXdetI + IXX)
            {
                if(II0 > (1.25*I00 + IXX))
                {
                    faulttype = FAULT_AN;
                }
                else if(I00 > (1.25*II0 + IXX))
                {
                    faulttype = FAULT_OVER;
                }
                else
                {
                    faulttype = FAULT_NOTDF;
                }
            }
            else
            {
                faulttype = FAULT_NOTDF;
            }
        }
        else if((5*detIca < detIab) && (5*detIca < detIbc))
        {
            if(detIb > 1.25*detIbT + fPNFactor*MAXdetI + IXX)
            {
                if(II0 > (1.25*I00 + IXX))
                {
                    faulttype = FAULT_BN;
                }
                else if(I00 > (1.25*II0 + IXX))
                {
                    faulttype = FAULT_OVER;
                }
                else
                {
                    faulttype = FAULT_NOTDF;
                }
            }
            else
            {
                faulttype = FAULT_NOTDF;
            }
        }
        //相间故障
        else if((2*detIa < detIc) && (2*detIa < detIb))
        {
            if(detIbc > 1.25*detIbcT + 0.7*MAXdetI + IXX)
            {
                if(1.2*Ibc1 < Ibc2)
                {
                    if(II0 < IXX)
                        faulttype = FAULT_BC;
                    else
                        faulttype = FAULT_BCN;
                }
                else if(1.2*Ibc2 < Ibc1)
                    faulttype = FAULT_OVER;
                else
                    faulttype = FAULT_NOTDF;
            }
            else
                faulttype = FAULT_NOTDF;
        }
        else if((2*detIb < detIa) && (2*detIb < detIc))
        {
            if(detIca > 1.25*detIcaT + 0.7*MAXdetI + IXX)
            {
                if(1.2*Ica1 < Ica2)
                {
                    if(II0 < IXX)
                        faulttype = FAULT_CA;
                    else
                        faulttype = FAULT_CAN;
                }
                else if(1.2*Ica2 < Ica1)
                    faulttype = FAULT_OVER;
                else
                    faulttype = FAULT_NOTDF;
            }
            else
                faulttype = FAULT_NOTDF;
        }
        else if((2*detIc < detIa) && (2*detIc < detIb))
        {
            if(detIab > 1.25*detIabT + 0.7*MAXdetI + IXX)
            {
                if(1.2*Iab1 < Iab2)
                {
                    if(II0 < IXX)
                        faulttype = FAULT_AB;
                    else
                        faulttype = FAULT_ABN;
                }
                else if(1.2*Iab2 < Iab1)
                    faulttype = FAULT_OVER;
                else
                    faulttype = FAULT_NOTDF;
            }
            else
                faulttype = FAULT_NOTDF;
        }
        else
        {
            if((detIab > 1.25*detIabT + 0.7*MAXdetI + IXX)
                &&(detIbc > 1.25*detIbcT + 0.7*MAXdetI + IXX)
                &&(detIca > 1.25*detIcaT + 0.7*MAXdetI + IXX))
                {
                if((1.2*Iab1 < Iab2)&&(1.2*Ibc1 < Ibc2)&&(1.2*Ica1 < Ica2))
                    faulttype = FAULT_ABC;
                else if((1.2*Iab2 < Iab1)&&(1.2*Ibc2 < Ibc1)&&(1.2*Ica2 < Ica1))
                    faulttype = FAULT_OVER;
                else
                    faulttype = FAULT_NOTDF;
            }
            else
            {
                faulttype = FAULT_NOTDF;
            }
        }
    }
    //选相（稳态量）
    else
    {
        //wait!!
    }

    //判故障结束
    if(faulttype == FAULT_NOTDF)
    {
        switch (a_nFaultType)
        {
        case FAULT_ABC:
        case FAULT_AB:
        case FAULT_ABN:
            if(Iab2 < (0.1*Iab1 + IXX))
                faulttype = FAULT_OVER;
            else if((detIab > 1.25*detIabT + 0.65*MAXdetI + IXX)&&(1.2*Iab2 < Iab1))
                faulttype = FAULT_OVER;
            break;
        case FAULT_BC:
        case FAULT_BCN:
            if(Ibc2 < (0.1*Ibc1 + IXX))
                faulttype = FAULT_OVER;
            else if((detIbc > 1.25*detIbcT + 0.65*MAXdetI + IXX)&&(1.2*Ibc2 < Ibc1))
                faulttype = FAULT_OVER;
            break;
        case FAULT_CA:
        case FAULT_CAN:
            if(Ica2 < (0.1*Ica1 + IXX))
                faulttype = FAULT_OVER;
            else if((detIca > 1.25*detIcaT + 0.65*MAXdetI + IXX)&&(1.2*Ica2 < Ica1))
                faulttype = FAULT_OVER;
            break;
        case FAULT_AN:
            if((Ia2 < (0.2*Ia1 + IXX)) || (II0 < (0.1*I00 + IXX)))
                faulttype = FAULT_OVER;
            break;
        case FAULT_BN:
            if((Ib2 < (0.2*Ib1 + IXX)) || (II0 < (0.1*I00 + IXX)))
                faulttype = FAULT_OVER;
            break;
        case FAULT_CN:
            if((Ic2 < (0.2*Ic1 + IXX)) || (II0 < (0.1*I00 + IXX)))
                faulttype = FAULT_OVER;
            break;
        }
    }
    return faulttype;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 选相
//参	数:
//			a_pData			Ua、Ub、Ic数据(已经在计算位置)
//			a_nWavePoints	每周波点数目
//			a_nPoints		数据长度
//			a_nFaultType	上次计算的结果
//			a_nFaultPos		突变位置
//返 回	值:
//备	注:
//创建日期: 2014-11-25		wpf
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_FindFaultType_Vol(float* a_pUa,float* a_pUb,float* a_pUc,int a_nWavePoints,int a_nPoints,int a_nFaultType,int& a_nFaultPos)
{
    int faulttype = FAULT_NOTDF;
    tagStarttype tblqd;
    float *uatemp, *ubtemp, *uctemp;
    int i, backpoints, faultp;
    float uaVector0[2], ubVector0[2], ucVector0[2];
    float uaVector1[2], ubVector1[2], ucVector1[2];
    float uaVector2[2], ubVector2[2], ucVector2[2];
    float detUbc, detUca, detUab, detUa, detUb, detUc;
    float detUbcT, detUcaT, detUabT, detUaT, detUbT, detUcT;
    float MAXdetU;
    float maxDetff,midDetff,minDetff;
    Q_UNUSED(midDetff);
    float re20[20] = {0};
    float img20[20] = {0};
    float /*Ua1,Ub1,Uc1,Ua2,Ub2,Uc2,*/Uab1,Ubc1,Uca1,Uab2,Ubc2,Uca2;
    float U00, UU0;

    float UXX=(float)(20);

    int ndots = a_nWavePoints/20;

    tblqd.nStartFlag = 0;
    tblqd.nabcStartPoints = 0;
    tblqd.nabStartPoints = 0;
    tblqd.nbcStartPoints=0;
    tblqd.ncaStartPoints=0;

    uatemp = a_pUa;
    ubtemp = a_pUb;
    uctemp = a_pUc;

    //判故障点
    for(i=0; i<a_nPoints-40*ndots; i+=ndots)
    {
        backpoints = Dist_FindStartPoint(10, uatemp,ubtemp,uctemp,a_nWavePoints,&tblqd);
        if(backpoints > 0)
        {
            break;
        }
        uatemp += ndots;
        ubtemp += ndots;
        uctemp += ndots;
    }

    //判故障，工频变化量方法
    if(i>=a_nPoints - 40*ndots)
    {
        a_nFaultPos = a_nPoints-40*ndots;
        return FAULT_NONE;
    }

    faultp = (int)(uatemp-a_pUa)+(40-backpoints)*ndots;
    a_nFaultPos = faultp;

    //计算
    if(faultp>=40*ndots)
    {
        uatemp = a_pUa+(faultp-40*ndots);
        ubtemp = a_pUb+(faultp-40*ndots);
        uctemp = a_pUc+(faultp-40*ndots);
    }
    else
    {
        uatemp = a_pUa;
        ubtemp = a_pUb;
        uctemp = a_pUc;
    }
    Dist_FilterPara(1, re20, img20);
    Dist_DFT(uatemp,a_nWavePoints,re20,img20,20,uaVector0[0],uaVector0[1]);
    Dist_DFT(ubtemp,a_nWavePoints,re20,img20,20,ubVector0[0],ubVector0[1]);
    Dist_DFT(uctemp,a_nWavePoints,re20,img20,20,ucVector0[0],ucVector0[1]);

    uatemp = a_pUa+(faultp-20*ndots);
    ubtemp = a_pUb+(faultp-20*ndots);
    uctemp = a_pUc+(faultp-20*ndots);

    Dist_DFT(uatemp,a_nWavePoints, re20, img20, 20,uaVector1[0],uaVector1[1]);
    Dist_DFT(ubtemp,a_nWavePoints, re20, img20, 20,ubVector1[0],ubVector1[1]);
    Dist_DFT(uctemp,a_nWavePoints, re20, img20, 20,ucVector1[0],ucVector1[1]);

    uatemp = a_pUa+faultp;
    ubtemp = a_pUb+faultp;
    uctemp = a_pUc+faultp;
    //i0temp = i0+faultp;

    Dist_DFT(uatemp,a_nWavePoints, re20, img20, 20,uaVector2[0],uaVector2[1]);
    Dist_DFT(ubtemp,a_nWavePoints, re20, img20, 20,ubVector2[0],ubVector2[1]);
    Dist_DFT(uctemp,a_nWavePoints, re20, img20, 20,ucVector2[0],ucVector2[1]);
    //Dft(i0temp, i0Vector2, re20, img20, 20);
    //	qDebug("Ua0  %g   %g\n",uaVector0[0],uaVector0[1]);
    //	qDebug("Ua1  %g   %g\n",uaVector1[0],uaVector1[1]);
    //	qDebug("ub0  %g   %g\n",ubVector0[0],ubVector0[1]);
    //	qDebug("ub1  %g   %g\n",ubVector1[0],ubVector1[1]);
    //	qDebug("uc0  %g   %g\n",ucVector0[0],ucVector0[1]);
    //	qDebug("uc1  %g   %g\n",ucVector1[0],ucVector1[1]);

    //单相幅值
//    Ua1 = (float)(sqrt(uaVector1[0]*uaVector1[0] + uaVector1[1]*uaVector1[1]));
//    Ub1 = (float)(sqrt(ubVector1[0]*ubVector1[0] + ubVector1[1]*ubVector1[1]));
//    Uc1 = (float)(sqrt(ucVector1[0]*ucVector1[0] + ucVector1[1]*ucVector1[1]));

    //相间幅值
    Uab1 = (float)(sqrt((uaVector1[0]-ubVector1[0]) * (uaVector1[0]-ubVector1[0])
                        +(uaVector1[1]-ubVector1[1]) * (uaVector1[1]-ubVector1[1])));
    Ubc1 = (float)(sqrt((ubVector1[0]-ucVector1[0]) * (ubVector1[0]-ucVector1[0])
                        +(ubVector1[1]-ucVector1[1]) * (ubVector1[1]-ucVector1[1])));
    Uca1 = (float)(sqrt((ucVector1[0]-uaVector1[0]) * (ucVector1[0]-uaVector1[0])
                        +(ucVector1[1]-uaVector1[1]) * (ucVector1[1]-uaVector1[1])));

//    Ua2 = (float)(sqrt(uaVector2[0]*uaVector2[0] + uaVector2[1]*uaVector2[1]));
//    Ub2 = (float)(sqrt(ubVector2[0]*ubVector2[0] + ubVector2[1]*ubVector2[1]));
//    Uc2 = (float)(sqrt(ucVector2[0]*ucVector2[0] + ucVector2[1]*ucVector2[1]));

    Uab2 = (float)(sqrt((uaVector2[0]-ubVector2[0]) * (uaVector2[0]-ubVector2[0])
                        +(uaVector2[1]-ubVector2[1]) * (uaVector2[1]-ubVector2[1])));
    Ubc2 = (float)(sqrt((ubVector2[0]-ucVector2[0]) * (ubVector2[0]-ucVector2[0])
                        +(ubVector2[1]-ucVector2[1]) * (ubVector2[1]-ucVector2[1])));
    Uca2 = (float)(sqrt((ucVector2[0]-uaVector2[0]) * (ucVector2[0]-uaVector2[0])
                        +(ucVector2[1]-uaVector2[1]) * (ucVector2[1]-uaVector2[1])));

    detUaT = (float)(sqrt((uaVector1[0]-uaVector0[0]) * (uaVector1[0]-uaVector0[0])
                          +(uaVector1[1]-uaVector0[1]) * (uaVector1[1]-uaVector0[1])));

    detUbT = (float)(sqrt((ubVector1[0]-ubVector0[0]) * (ubVector1[0]-ubVector0[0])
                          +(ubVector1[1]-ubVector0[1]) * (ubVector1[1]-ubVector0[1])));

    detUcT = (float)(sqrt((ucVector1[0]-ucVector0[0]) * (ucVector1[0]-ucVector0[0])
                          +(ucVector1[1]-ucVector0[1]) * (ucVector1[1]-ucVector0[1])));

    detUa = (float)(sqrt((uaVector1[0]-uaVector2[0]) * (uaVector1[0]-uaVector2[0])
                         +(uaVector1[1]-uaVector2[1]) * (uaVector1[1]-uaVector2[1])));

    detUb = (float)(sqrt((ubVector1[0]-ubVector2[0]) * (ubVector1[0]-ubVector2[0])
                         +(ubVector1[1]-ubVector2[1]) * (ubVector1[1]-ubVector2[1])));

    detUc = (float)(sqrt((ucVector1[0]-ucVector2[0]) * (ucVector1[0]-ucVector2[0])
                         +(ucVector1[1]-ucVector2[1]) * (ucVector1[1]-ucVector2[1])));

    if(detUa > detUb)
        MAXdetU = detUa;
    else
        MAXdetU = detUb;
    if(detUc > MAXdetU)
        MAXdetU = detUc;

    detUabT = (float)(sqrt(((uaVector1[0]-uaVector0[0]) - (ubVector1[0]-ubVector0[0]))
                           *((uaVector1[0]-uaVector0[0]) - (ubVector1[0]-ubVector0[0]))
                           +((uaVector1[1]-uaVector0[1]) - (ubVector1[1]-ubVector0[1]))
                           *((uaVector1[1]-uaVector0[1]) - (ubVector1[1]-ubVector0[1]))));

    detUbcT = (float)(sqrt(((ubVector1[0]-ubVector0[0]) - (ucVector1[0]-ucVector0[0]))
                           *((ubVector1[0]-ubVector0[0]) - (ucVector1[0]-ucVector0[0]))
                           +((ubVector1[1]-ubVector0[1]) - (ucVector1[1]-ucVector0[1]))
                           *((ubVector1[1]-ubVector0[1]) - (ucVector1[1]-ucVector0[1]))));

    detUcaT = (float)(sqrt(((ucVector1[0]-ucVector0[0]) - (uaVector1[0]-uaVector0[0]))
                           *((ucVector1[0]-ucVector0[0]) - (uaVector1[0]-uaVector0[0]))
                           +((ucVector1[1]-ucVector0[1]) - (uaVector1[1]-uaVector0[1]))
                           *((ucVector1[1]-ucVector0[1]) - (uaVector1[1]-uaVector0[1]))));

    detUab = (float)(sqrt(((uaVector1[0]-uaVector2[0]) - (ubVector1[0]-ubVector2[0]))
                          *((uaVector1[0]-uaVector2[0]) - (ubVector1[0]-ubVector2[0]))
                          +((uaVector1[1]-uaVector2[1]) - (ubVector1[1]-ubVector2[1]))
                          *((uaVector1[1]-uaVector2[1]) - (ubVector1[1]-ubVector2[1]))));

    detUbc = (float)(sqrt(((ubVector1[0]-ubVector2[0]) - (ucVector1[0]-ucVector2[0]))
                          *((ubVector1[0]-ubVector2[0]) - (ucVector1[0]-ucVector2[0]))
                          +((ubVector1[1]-ubVector2[1]) - (ucVector1[1]-ucVector2[1]))
                          *((ubVector1[1]-ubVector2[1]) - (ucVector1[1]-ucVector2[1]))));

    detUca = (float)(sqrt(((ucVector1[0]-ucVector2[0]) - (uaVector1[0]-uaVector2[0]))
                          *((ucVector1[0]-ucVector2[0]) - (uaVector1[0]-uaVector2[0]))
                          +((ucVector1[1]-ucVector2[1]) - (uaVector1[1]-uaVector2[1]))
                          *((ucVector1[1]-ucVector2[1]) - (uaVector1[1]-uaVector2[1]))));

    U00 = (float)(sqrt((uaVector1[0]+ubVector1[0]+ucVector1[0])*(uaVector1[0]+ubVector1[0]+ucVector1[0])
                       +(uaVector1[1]+ubVector1[1]+ucVector1[1])*(uaVector1[1]+ubVector1[1]+ucVector1[1])));

    UU0 = (float)(sqrt((uaVector2[0]+ubVector2[0]+ucVector2[0])*(uaVector2[0]+ubVector2[0]+ucVector2[0])
                       +(uaVector2[1]+ubVector2[1]+ucVector2[1])*(uaVector2[1]+ubVector2[1]+ucVector2[1])));

    if(detUbc > detUab)
    {
        maxDetff = detUbc;
        minDetff = detUab;
    }
    else
    {
        maxDetff = detUab;
        minDetff = detUbc;
    }

    if(detUca > maxDetff)
    {
        midDetff = maxDetff;
        maxDetff = detUca;
    }
    else if(detUca < minDetff)
    {
        midDetff = minDetff;
        minDetff = detUca;
    }
    else
        midDetff = detUca;

    //	qDebug("detIa = %g  detIb=%g  detIc=%g\n",detIa,detIb,detIc);
    //	qDebug("detIab = %g  detIbc=%g  detIca=%g\n",detIab,detIbc,detIca);

    //选相（突变量）
    if((a_nFaultType == FAULT_OVER) || (a_nFaultType == FAULT_NONE) || (a_nFaultType == FAULT_NOTDF))
    {
        if((5*detUab < detUca) && (5*detUab < detUbc))
        {
            if(detUc > 1.25*detUcT + 0.5*MAXdetU + UXX)
            {
                if(UU0 > (1.25*U00 + UXX))
                {
                    faulttype = FAULT_CN;
                }
//                else if(U00 > (1.25*UU0 + UXX))
//                {
//                    faulttype = FAULT_OVER;
//                }
//                else
//                {
//                    faulttype = FAULT_NOTDF;
//                }
            }
            else
            {
                faulttype = FAULT_NOTDF;
            }
        }
        else if((5*detUbc < detUab) && (5*detUbc < detUca))
        {
            if(detUa > 1.25*detUaT + 0.5*MAXdetU + UXX)
            {
                if(UU0 > (1.25*U00 + UXX))
                {
                    faulttype = FAULT_AN;
                }
//                else if(U00 > (1.25*UU0 + UXX))
//                {
//                    faulttype = FAULT_OVER;
//                }
//                else
//                {
//                    faulttype = FAULT_NOTDF;
//                }
            }
            else
                faulttype = FAULT_NOTDF;
        }
        else if((5*detUca < detUab) && (5*detUca < detUbc))
        {
            if(detUb > 1.25*detUbT + 0.5*MAXdetU + UXX)
            {
                if(UU0 > (1.25*U00 + UXX))
                    faulttype = FAULT_BN;
//                else if(U00 > (1.25*UU0 + UXX))
//                    faulttype = FAULT_OVER;
//                else
//                    faulttype = FAULT_NOTDF;
            }
            else
                faulttype = FAULT_NOTDF;
        }
        //相间故障
        else if((2*detUa < detUc) && (2*detUa < detUb))
        {
            if(detUbc > 1.25*detUbcT + 0.7*MAXdetU + UXX)
            {
                if(1.2*Ubc1 > Ubc2)
                {
                    if(UU0 < UXX)
                        faulttype = FAULT_BC;
                    else
                        faulttype = FAULT_BCN;
                }
//                else if(1.2*Ubc2 > Ubc1)
//                    faulttype = FAULT_OVER;
//                else
//                    faulttype = FAULT_NOTDF;
            }
            else
                faulttype = FAULT_NOTDF;
        }
        else if((2*detUb < detUa) && (2*detUb < detUc))
        {
            if(detUca > 1.25*detUcaT + 0.7*MAXdetU + UXX)
            {
                if(1.2*Uca1 < Uca2)
                {
                    if(UU0 < UXX)
                        faulttype = FAULT_CA;
                    else
                        faulttype = FAULT_CAN;
                }
//                else if(1.2*Uca2 > Uca1)
//                    faulttype = FAULT_OVER;
//                else
//                    faulttype = FAULT_NOTDF;
            }
            else
                faulttype = FAULT_NOTDF;
        }
        else if((2*detUc < detUa) && (2*detUc < detUb))
        {
            if(detUab > 1.25*detUabT + 0.7*MAXdetU + UXX)
            {
                if(1.2*Uab1 > Uab2)
                {
                    if(UU0 < UXX)
                        faulttype = FAULT_AB;
                    else
                        faulttype = FAULT_ABN;
                }
//                else if(1.2*Uab2 > Uab1)
//                    faulttype = FAULT_OVER;
//                else
//                    faulttype = FAULT_NOTDF;
            }
            else
                faulttype = FAULT_NOTDF;
        }
        else
        {
            if((detUab > 1.25*detUabT + 0.7*MAXdetU + UXX)
                &&(detUbc > 1.25*detUbcT + 0.7*MAXdetU + UXX)
                &&(detUca > 1.25*detUcaT + 0.7*MAXdetU + UXX))
                {
                if((1.2*Uab1 < Uab2)&&(1.2*Ubc1 < Ubc2)&&(1.2*Uca1 < Uca2))
                    faulttype = FAULT_ABC;
//                else if((1.2*Uab2 < Uab1)&&(1.2*Ubc2 < Ubc1)&&(1.2*Uca2 < Uca1))
//                    faulttype = FAULT_OVER;
//                else
//                    faulttype = FAULT_NOTDF;
            }
            else
            {
                faulttype = FAULT_NOTDF;
            }
        }
    }
    //选相（稳态量）
    else
    {
        //wait!!
    }

    //判故障结束
    /*
    if(faulttype == FAULT_NOTDF)
    {
        switch (a_nFaultType)
        {
        case FAULT_ABC:
        case FAULT_AB:
        case FAULT_ABN:
            if(Uab2 < (0.1*Uab1 + UXX))
                faulttype = FAULT_OVER;
            else if((detUab > 1.25*detUabT + 0.65*MAXdetU + UXX)&&(1.2*Uab2 < Uab1))
                faulttype = FAULT_OVER;
            break;
        case FAULT_BC:
        case FAULT_BCN:
            if(Ubc2 < (0.1*Ubc1 + UXX))
                faulttype = FAULT_OVER;
            else if((detUbc > 1.25*detUbcT + 0.65*MAXdetU + UXX)&&(1.2*Ubc2 < Ubc1))
                faulttype = FAULT_OVER;
            break;
        case FAULT_CA:
        case FAULT_CAN:
            if(Uca2 < (0.1*Uca1 + UXX))
                faulttype = FAULT_OVER;
            else if((detUca > 1.25*detUcaT + 0.65*MAXdetU + UXX)&&(1.2*Uca2 < Uca1))
                faulttype = FAULT_OVER;
            break;
        case FAULT_AN:
            if((Ua2 < (0.2*Ua1 + UXX)) || (UU0 < (0.1*U00 + UXX)))
                faulttype = FAULT_OVER;
            break;
        case FAULT_BN:
            if((Ub2 < (0.2*Ub1 + UXX)) || (UU0 < (0.1*U00 + UXX)))
                faulttype = FAULT_OVER;
            break;
        case FAULT_CN:
            if((Uc2 < (0.2*Uc1 + UXX)) || (UU0 < (0.1*U00 + UXX)))
                faulttype = FAULT_OVER;
            break;
        }
    }
    */
    return faulttype;
}


//////////////////////////////////////////////////////////////////////////
//功	能: 判方向(单相/根据电压、电流)
//参	数: 
//			a_pDataU		电压数据
//			a_pDataI		电流数据
//			a_nWavePoints	每周波采样点数目
//返 回	值: 
//			0:	出口(或者电压不满足条件)
//			1:  正方向
//			2:  负方向
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_FindDirectionP(float* a_pDataU,float* a_pDataI,int a_nWavePoints)
{
    float uVector[2], iVector[2], ubiRe, ubiImg, temp;
    float re20[20],img20[20];
    int fx;

    Dist_FilterPara(1, re20, img20);
    Dist_DFT(a_pDataI, a_nWavePoints,re20, img20, 20,iVector[0],iVector[1]);
    Dist_DFT(a_pDataU, a_nWavePoints,re20, img20, 20,uVector[0],uVector[1]);

    if(sqrt((uVector[0]*uVector[0])+(uVector[1]*uVector[1])) > 10)
    {
        temp   = iVector[0]*iVector[0]+iVector[1]*iVector[1];

        ubiRe  = (iVector[0]*uVector[0]+iVector[1]*uVector[1])/temp;
        ubiImg = (iVector[0]*uVector[1]-iVector[1]*uVector[0])/temp;

        if((ubiRe>0) && (ubiImg>0))
            fx = 1;
        else if((ubiRe>0) && (ubiImg<0))
        {
            if(ubiRe > (-2.*ubiImg))
                fx = 1;
            else
                fx = 2;
        }
        else if((ubiRe<0) && (ubiImg>0))
        {
            if(-ubiRe > 2.*ubiImg)
                fx = 1;
            else
                fx = 2;
        }
        else
            fx = 2;
    }
    else
        fx = 0;
    return fx;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 判方向(两相/根据电压、电流)
//参	数: 
//			a_pDataU1		第1相电压数据
//			a_pDataU2		第2相电压数据
//			a_pDataI1		第1相电流数据
//			a_pDataI2		第2相电流数据
//			a_nWavePoints	每周波采样点数目
//返 回	值: 
//			0:	出口(或者电压不满足条件)
//			1:  正方向
//			2:  负方向
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_FindDirectionPP(float* a_pDataU1,float* a_pDataU2,float* a_pDataI1,float* a_pDataI2,int a_nWavePoints)
{
    float uVector1[2], iVector1[2], uVector2[2], iVector2[2], ubiRe, ubiImg, temp;
    int fx;
    float re20[20],img20[20];

    Dist_FilterPara(1, re20, img20);
    Dist_DFT(a_pDataI1, a_nWavePoints,re20, img20, 20,iVector1[0],iVector1[1]);
    Dist_DFT(a_pDataU1, a_nWavePoints,re20, img20, 20,uVector1[0],uVector1[1]);
    Dist_DFT(a_pDataI2, a_nWavePoints,re20, img20, 20,iVector2[0],iVector2[1]);
    Dist_DFT(a_pDataU2, a_nWavePoints,re20, img20, 20,uVector2[0],uVector2[1]);

    if(sqrt(((uVector1[0]-uVector2[0])*(uVector1[0]-uVector2[0]))+
            ((uVector1[1]-uVector2[1])*(uVector1[1]-uVector2[1]))) > 10)
    {
        temp   = (iVector1[0]-iVector2[0])*(iVector1[0]-iVector2[0])+(iVector1[1]-iVector2[1])*(iVector1[1]-iVector2[1]);
        ubiRe  = ((iVector1[0]-iVector2[0])*(uVector1[0]-uVector2[0])+(iVector1[1]-iVector2[1])*(uVector1[1]-uVector2[1]))/temp;
        ubiImg = ((iVector1[0]-iVector2[0])*(uVector1[1]-uVector2[1])-(iVector1[1]-iVector2[1])*(uVector1[0]-uVector2[0]))/temp;

        if((ubiRe>0) && (ubiImg>0))
            fx = 1;
        else if((ubiRe>0) && (ubiImg<0))
        {
            if(ubiRe > (-2.*ubiImg))
                fx = 1;
            else
                fx = 2;
        }
        else if((ubiRe<0) && (ubiImg>0))
        {
            if(-ubiRe > 2.*ubiImg)
                fx = 1;
            else
                fx = 2;
        }
        else
            fx = 2;
    }
    else
        fx = 0;
    return fx;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 判方向
//参	数: 
//			a_pDataU[3]		Ua、Ub、Uc数据
//			a_pDataI[3]		Ia、Ib、Ic数据
//			a_nCalPos		计算位置
//			a_nWavePoints	每周波采样点数目
//			a_nFaltType		故障类型
//返 回	值: 
//			0:	出口(或者电压不满足条件)
//			1:  正方向
//			2:  负方向
//备	注: 
//创建日期: 2007-09-13		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
int CGenerateReport::Dist_FindDirection(float* a_pDataU[3], float* a_pDataI[3],int a_nCalPos,int a_nWavePoints,int a_nFaltType)
{
    float* pUa = a_pDataU[0] + a_nCalPos;
    float* pUb = a_pDataU[1] + a_nCalPos;
    float* pUc = a_pDataU[2] + a_nCalPos;
    float* pIa = a_pDataI[0] + a_nCalPos;
    float* pIb = a_pDataI[1] + a_nCalPos;
    float* pIc = a_pDataI[2] + a_nCalPos;
    int fx=0;
    int ndots = a_nWavePoints/20;
    switch (a_nFaltType)
    {
    case FAULT_AN:
    case FAULT_ABC:
        fx = Dist_FindDirectionP(pUa,pIa+40*ndots,a_nWavePoints);
        break;
    case FAULT_BN:
        fx = Dist_FindDirectionP(pUb,pIb+40*ndots,a_nWavePoints);
        break;
    case FAULT_CN:
        fx = Dist_FindDirectionP(pUc,pIc+40*ndots,a_nWavePoints);
        break;
    case FAULT_AB:
    case FAULT_ABN:
        fx = Dist_FindDirectionPP(pUa,pUb,pIa+40*ndots,pIb+40*ndots,a_nWavePoints);
        break;
    case FAULT_BC:
    case FAULT_BCN:
        fx = Dist_FindDirectionPP(pUb,pUc,pIb+40*ndots,pIc+40*ndots,a_nWavePoints);
        break;
    case FAULT_CA:
    case FAULT_CAN:
        fx = Dist_FindDirectionPP(pUc,pUa,pIc+40*ndots,pIa+40*ndots,a_nWavePoints);
        break;
    }
    return fx;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取线路分析结果
//参	数: 
//返 回	值: 
//备	注: 
//创建日期: 2007-09-26		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
bool CGenerateReport::GenerateLine_Report()
{
    m_nRelayActLine = -1;
    m_pFaultLine = NULL;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    try
    {
	GenerateBasicInfo();	//获取基本信息
	GenerateSwitchList();	//获取开关动作时序
	m_nTbLineCount = 0;

    //获取开关变位次数最多的线路
    m_nRelayActLine = GetSwitchJump_Line();
	//////////////////////////////////////////////////////////////////////////
	//2010-01-14 修改
    //适应双母线运行,自动关联同电压等级的母线，将测距结果保存
	//[[
    //	CEleBus* pBus = NULL;
    int i = 0;
    for(i=0; i<m_pCmtd->m_arLine.count(); i++)
    {
        if(m_pCmtd->m_arLine[i]->m_dLength < 0.5)
        {
            continue;
        }
        if(!m_pCmtd->m_arLine[i]->m_bDistance)
        {
            continue;
        }
        m_arLineInfo[m_nTbLineCount].m_bFault = false;
        m_arLineInfo[m_nTbLineCount].InitData();
        m_arLineInfo[m_nTbLineCount].m_nLineIndex = i;
//        qDebug("Ana line%d---------------------------",i);
        if(AnalysisLine(i,&(m_arLineInfo[m_nTbLineCount])))
        {
            m_nTbLineCount++;
            if(m_nTbLineCount>=MAX_TBLINE_COUNT)
            {
                break;
            }
        }
    }
	//]]

	//--------------------------------------------------------------------------
	//如果没有故障线路,给出一个有异常的线路,判定条件为开关动作、电流越限等
	//--------------------------------------------------------------------------
    if(m_nTbLineCount <= 0)
    {
        int nLine = 0;
        if(m_nRelayActLine >= 0)
        {
            m_arLineInfo[m_nTbLineCount].m_nLineIndex = m_nRelayActLine;
            IsLines_Inf_Overflow(&(m_arLineInfo[m_nTbLineCount]),m_pCmtd->m_arLine[m_nRelayActLine]);
            m_nTbLineCount++;
        }
        else //线路是否有突变
        {
            for(int i=0; i<m_pCmtd->m_arLine.count(); i++)
            {
                m_arLineInfo[m_nTbLineCount].m_bFault = false;
                m_arLineInfo[m_nTbLineCount].InitData();
                m_arLineInfo[m_nTbLineCount].m_nLineIndex = i;
                if(IsLines_Inf_Overflow(&(m_arLineInfo[m_nTbLineCount]),m_pCmtd->m_arLine[i]))
                {
                    nLine = i;
                    m_nTbLineCount++;
                    break;
                }
            }
        }
        if(m_nTbLineCount <= 0)
        {
            strcpy(m_chFaultLine,gbk->fromUnicode("区内无故障"));
            return false;
        }
        else
        {
            GetLineValue_Cyc(&(m_arLineInfo[0]),m_pCmtd->m_arLine[nLine]);
        }
    }
	//-------------------------------------------------------------------
	//进行一次合理性分析
	//-------------------------------------------------------------------
    QString strtmp;
    int nmaxDirect = 0;
    float dDistanceI = 0;
    float dDistanceII = 0;
    for(i=0; i<m_nTbLineCount; i++)
    {
        float dLineLength = m_pCmtd->m_arLine[m_arLineInfo[i].m_nLineIndex]->m_dLength;
        strtmp = gbk->toUnicode(m_pCmtd->m_arLine[m_arLineInfo[i].m_nLineIndex]->m_chName);
        dDistanceI = m_arLineInfo[i].m_dDistanceI;
        dDistanceII = m_arLineInfo[i].m_dDistanceII;
        if((strtmp.indexOf(QString("旁路"))<0)&&(strtmp.indexOf(QString("主变"))<0)&&(strtmp.indexOf(QString("母联"))<0)&&(strtmp.indexOf(QString("高压侧"))<0)&&(strtmp.indexOf(QString("中压侧"))<0)&&(strtmp.indexOf(QString("低压侧"))<0))	//名称中没有主变二字 (权值1)
        {
            m_arLineInfo[i].m_nDirect += 2;
        }
        if(dLineLength >= 3.0)									//线路长度>3km (权值1)
        {
            m_arLineInfo[i].m_nDirect += 2;
        }

        if(m_arLineInfo[i].m_nLineIndex == m_nRelayActLine)			//本线路开关变位次数最多
        {
            m_arLineInfo[i].m_nDirect += 2;
        }

        if((dDistanceI>3)&&(dDistanceI < dLineLength))			//测距结果大于3km且小于线路长度 (权值3)
        {
            m_arLineInfo[i].m_nDirect += 3;
        }
        else if((dDistanceI>=-0.01)&&(dDistanceI<=1.1*dLineLength))//测距结果在线路长度之内(权值2)
        {
            m_arLineInfo[i].m_nDirect += 2;
        }
        else if((dDistanceI<0)&&(fabs(dDistanceI)<3))			//反方向但距离<-3km的(权值1)
        {
            m_arLineInfo[i].m_nDirect += 1;
            m_arLineInfo[i].m_dDistanceI = (float)(fabs(dDistanceI));
            m_arLineInfo[i].m_bFault = true;
        }
        else if((dDistanceII>3)&&(dDistanceII < dLineLength))	//副母距离同样有效
        {
            m_arLineInfo[i].m_nDirect += 3;
        }
        else if((dDistanceII>=-0.01)&&(dDistanceII<=1.1*dLineLength))//测距结果在线路长度之内(权值2)
        {
            m_arLineInfo[i].m_nDirect += 2;
        }
        else if((dDistanceII<0)&&(fabs(dDistanceII)<3))
        {
            m_arLineInfo[i].m_nDirect += 1;
            m_arLineInfo[i].m_dDistanceII = (float)(fabs(dDistanceII));
            m_arLineInfo[i].m_bFault = true;
        }

        if(m_arLineInfo[i].m_nDirect > nmaxDirect)
        {
            nmaxDirect = m_arLineInfo[i].m_nDirect;
        }
        //		qDebug("line: %s   value=%d\n",strtmp,m_arLineInfo[i].m_nDirect);
    }

    //-------------------------------------------------------------------
    //找出故障线路
    //-------------------------------------------------------------------
    for(i=0; i<m_nTbLineCount; i++)
    {
        if(m_arLineInfo[i].m_nDirect == nmaxDirect)
        {
            m_arLineInfo[i].m_bTbMax = true;
            break;
        }
    }
//    bool bFault = false;
    int nFaultLine = m_arLineInfo[i].m_nLineIndex;
    int nStartIndex = i;
    float dLineLength = m_pCmtd->m_arLine[nFaultLine]->m_dLength;
    dDistanceI = m_arLineInfo[i].m_dDistanceI;
    dDistanceII = m_arLineInfo[i].m_dDistanceII;
    float dStartTime = (float)(m_pCmtd->m_pSampleTime[m_arLineInfo[nStartIndex].m_nStartPoint]/1000.0);
    float dTimeLong = (float)(m_pCmtd->m_pSampleTime[m_arLineInfo[nStartIndex].m_nEndPoint]/1000.0);
    dTimeLong -= dStartTime;
    // 如果是-5以内的负数,认为合理 [1/23/2008]
    if((dDistanceI<0)&&(dDistanceI>-5))
    {
        dDistanceI = -dDistanceI;
        m_arLineInfo[i].m_dDistanceI = dDistanceI;
    }
    if((dDistanceI>=0)&&(dDistanceI <= 1.4*dLineLength)&&(dTimeLong > 0.0001))
    {
//        bFault = true;
        m_arLineInfo[nStartIndex].m_bFault = true;
    }
    if((dDistanceII<0)&&(dDistanceII>-5))
    {
//        bFault = true;
        dDistanceII = -dDistanceII;
        m_arLineInfo[i].m_dDistanceII = dDistanceII;
    }
    if((dDistanceII>=0)&&(dDistanceII <= 1.1*dLineLength)&&(dTimeLong > 0.0001))
    {
//        bFault = true;
        m_arLineInfo[nStartIndex].m_bFault = true;
    }
    m_pFaultLine = &(m_arLineInfo[nStartIndex]);
	//-------------------------------------------------------------------------
	//整理开关量信息,去掉不是本线路的开关信息
	//2007-12-10日添加
	//2009-08-20 将此段代码删除，将所有开关变位信息列出
	//-------------------------------------------------------------------------
	/*
        bool bCorrect = false;
	int nSize = m_SwitchList.m_arStatus.GetSize();
	for(i=nSize-1; i>=0; i--)
	{
                bCorrect = false;
        for(int j=0; j<m_pCmtd->m_arLine[nFaultLine].m_nSwitchCount; j++)
		{
            if(m_SwitchList.m_arStatus[i].m_wID == m_pCmtd->m_arLine[nFaultLine].m_pSwitch[j])
			{
                                bCorrect = true;
				break;
			}
		}
		if(!bCorrect)
		{
			m_SwitchList.m_arStatus.RemoveAt(i);
		}
	}
	m_SwitchList.m_arStatus.FreeExtra();
	*/
        //delete gbk;
        return true;
    }
    catch(...)
    {
        //delete gbk;
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取主变分析结果
//参	数: 
//返 回	值: 
//备	注: 
//创建日期: 2007-09-26		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
bool CGenerateReport::GenerateTrans_Report()
{
    InitData();
    GenerateBasicInfo();	//获取基本信息
    GenerateSwitchList();	//获取开关动作时序

//    qDebug("--------------------------------------主变分析报告---------------------------------------\n");
    int nPoints = m_pCmtd->m_nTotalPoints;	//采样点数目
    float* pDeltaIa = new float[nPoints];	//A相差流
    float* pDeltaIb = new float[nPoints];	//B相差流
    float* pDeltaIc = new float[nPoints];	//C相差流
//    ASSERT(pDeltaIa != NULL);
//    ASSERT(pDeltaIb != NULL);
//    ASSERT(pDeltaIc != NULL);
    float dData[12] = {0};                      //各侧数据
    int nNum = 0;				//共有几侧
    float dFactor[4] = {0};                     //平衡系数
    int nType[4] = {0};                         //接线方式

    float dMaxDeltaI = 0;
    m_nTbTransCount = 0;
    bool bOverFlow = false;
    int nIndex = 0;
    int i = 0;
    for(i=0; i<m_pCmtd->m_arTrans.count(); i++)
    {
        nNum = 0;
        bOverFlow = false;
        CEleTrans* a_pTransInfo = m_pCmtd->m_arTrans[i];
        dMaxDeltaI = a_pTransInfo->m_dDeltaI;	//差流启动值
        //---------------------------------------------------------
        //首先获取各侧基本参数
        //---------------------------------------------------------
        if(a_pTransInfo->m_pLine[0] != NULL)
        {
            nNum++;
            dFactor[0] = a_pTransInfo->m_dFactor[0];	//I侧平衡系数
            nType[0] = a_pTransInfo->m_nType[0];		//I侧接线方式
            m_dParamab[0] = a_pTransInfo->m_pLine[0]->m_pAChanel->m_da;
            m_dParamab[1] = a_pTransInfo->m_pLine[0]->m_pAChanel->m_db;
            m_dParamab[2] = a_pTransInfo->m_pLine[0]->m_pBChanel->m_da;
            m_dParamab[3] = a_pTransInfo->m_pLine[0]->m_pBChanel->m_db;
            m_dParamab[4] = a_pTransInfo->m_pLine[0]->m_pCChanel->m_da;
            m_dParamab[5] = a_pTransInfo->m_pLine[0]->m_pCChanel->m_db;
        }
        if(a_pTransInfo->m_pLine[1] != NULL)
        {
            nNum++;
            dFactor[1] = a_pTransInfo->m_dFactor[1];	//II侧..
            nType[1] = a_pTransInfo->m_nType[1];		//II侧..
        }
        if(a_pTransInfo->m_pLine[2] != NULL)		//III侧..
        {
            nNum++;
            dFactor[2] = a_pTransInfo->m_dFactor[2];
            nType[2] = a_pTransInfo->m_nType[2];

        }
        if(a_pTransInfo->m_pLine[3] != NULL)		//IV侧..
        {
            nNum++;
            dFactor[3] = a_pTransInfo->m_dFactor[3];
            nType[3] = a_pTransInfo->m_nType[3];
        }
        //---------------------------------------------------------------------
        //计算差流瞬时值.为提高效率,这里分三种情况各自循环计算
        //2010-04-24 修改
        //这里的差流计算之前忘记考虑电流反相了
        //---------------------------------------------------------------------
        if(nNum == 2)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                dData[0] = a_pTransInfo->m_pLine[0]->m_pAChanel->m_pData[n];
                dData[1] = a_pTransInfo->m_pLine[0]->m_pBChanel->m_pData[n];
                dData[2] = a_pTransInfo->m_pLine[0]->m_pCChanel->m_pData[n];
                dData[3] = a_pTransInfo->m_pLine[1]->m_pAChanel->m_pData[n];
                dData[4] = a_pTransInfo->m_pLine[1]->m_pBChanel->m_pData[n];
                dData[5] = a_pTransInfo->m_pLine[1]->m_pCChanel->m_pData[n];
                /*计算错误2018-12-01修改
                dData[0] = (a_pTransInfo->m_pLine[0]->m_pAChanel->m_pData[n]-a_pTransInfo->m_pLine[0]->m_pAChanel->m_db)/a_pTransInfo->m_pLine[0]->m_pAChanel->m_da;
                dData[1] = (a_pTransInfo->m_pLine[0]->m_pBChanel->m_pData[n]-a_pTransInfo->m_pLine[0]->m_pBChanel->m_db)/a_pTransInfo->m_pLine[0]->m_pBChanel->m_da;
                dData[2] = (a_pTransInfo->m_pLine[0]->m_pCChanel->m_pData[n]-a_pTransInfo->m_pLine[0]->m_pCChanel->m_db)/a_pTransInfo->m_pLine[0]->m_pCChanel->m_da;

                dData[3] = (a_pTransInfo->m_pLine[1]->m_pAChanel->m_pData[n]-a_pTransInfo->m_pLine[1]->m_pAChanel->m_db)/a_pTransInfo->m_pLine[1]->m_pAChanel->m_da;
                dData[4] = (a_pTransInfo->m_pLine[1]->m_pBChanel->m_pData[n]-a_pTransInfo->m_pLine[1]->m_pBChanel->m_db)/a_pTransInfo->m_pLine[1]->m_pBChanel->m_da;
                dData[5] = (a_pTransInfo->m_pLine[1]->m_pCChanel->m_pData[n]-a_pTransInfo->m_pLine[1]->m_pCChanel->m_db)/a_pTransInfo->m_pLine[1]->m_pCChanel->m_da;
                */
                if(a_pTransInfo->m_bInvert[0])
                {
                    dData[0] = -dData[0];
                    dData[1] = -dData[1];
                    dData[2] = -dData[2];
                }
                if(a_pTransInfo->m_bInvert[1])
                {
                    dData[3] = -dData[3];
                    dData[4] = -dData[4];
                    dData[5] = -dData[5];
                }
                pDeltaIa[n] = m_wyCal.Formula_Fun_DeltaId(0,nNum,dData,dFactor,nType);
                pDeltaIb[n] = m_wyCal.Formula_Fun_DeltaId(1,nNum,dData,dFactor,nType);
                pDeltaIc[n] = m_wyCal.Formula_Fun_DeltaId(2,nNum,dData,dFactor,nType);
            }
        }
        else if(nNum == 3)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                dData[0] = a_pTransInfo->m_pLine[0]->m_pAChanel->m_pData[n];
                dData[1] = a_pTransInfo->m_pLine[0]->m_pBChanel->m_pData[n];
                dData[2] = a_pTransInfo->m_pLine[0]->m_pCChanel->m_pData[n];
                dData[3] = a_pTransInfo->m_pLine[1]->m_pAChanel->m_pData[n];
                dData[4] = a_pTransInfo->m_pLine[1]->m_pBChanel->m_pData[n];
                dData[5] = a_pTransInfo->m_pLine[1]->m_pCChanel->m_pData[n];
                dData[6] = a_pTransInfo->m_pLine[2]->m_pAChanel->m_pData[n];
                dData[7] = a_pTransInfo->m_pLine[2]->m_pBChanel->m_pData[n];
                dData[8] = a_pTransInfo->m_pLine[2]->m_pCChanel->m_pData[n];
                /* 计算错误2018-12-01修改
                dData[0] = (a_pTransInfo->m_pLine[0]->m_pAChanel->m_pData[n]-a_pTransInfo->m_pLine[0]->m_pAChanel->m_db)/a_pTransInfo->m_pLine[0]->m_pAChanel->m_da;
                dData[1] = (a_pTransInfo->m_pLine[0]->m_pBChanel->m_pData[n]-a_pTransInfo->m_pLine[0]->m_pBChanel->m_db)/a_pTransInfo->m_pLine[0]->m_pBChanel->m_da;
                dData[2] = (a_pTransInfo->m_pLine[0]->m_pCChanel->m_pData[n]-a_pTransInfo->m_pLine[0]->m_pCChanel->m_db)/a_pTransInfo->m_pLine[0]->m_pCChanel->m_da;
                dData[3] = (a_pTransInfo->m_pLine[1]->m_pAChanel->m_pData[n]-a_pTransInfo->m_pLine[1]->m_pAChanel->m_db)/a_pTransInfo->m_pLine[1]->m_pAChanel->m_da;
                dData[4] = (a_pTransInfo->m_pLine[1]->m_pBChanel->m_pData[n]-a_pTransInfo->m_pLine[1]->m_pBChanel->m_db)/a_pTransInfo->m_pLine[1]->m_pBChanel->m_da;
                dData[5] = (a_pTransInfo->m_pLine[1]->m_pCChanel->m_pData[n]-a_pTransInfo->m_pLine[1]->m_pCChanel->m_db)/a_pTransInfo->m_pLine[1]->m_pCChanel->m_da;
                dData[6] = (a_pTransInfo->m_pLine[2]->m_pAChanel->m_pData[n]-a_pTransInfo->m_pLine[2]->m_pAChanel->m_db)/a_pTransInfo->m_pLine[2]->m_pAChanel->m_da;
                dData[7] = (a_pTransInfo->m_pLine[2]->m_pBChanel->m_pData[n]-a_pTransInfo->m_pLine[2]->m_pBChanel->m_db)/a_pTransInfo->m_pLine[2]->m_pBChanel->m_da;
                dData[8] = (a_pTransInfo->m_pLine[2]->m_pCChanel->m_pData[n]-a_pTransInfo->m_pLine[2]->m_pCChanel->m_db)/a_pTransInfo->m_pLine[2]->m_pCChanel->m_da;
                */
                if(a_pTransInfo->m_bInvert[0])
                {
                    dData[0] = -dData[0];
                    dData[1] = -dData[1];
                    dData[2] = -dData[2];
                }
                if(a_pTransInfo->m_bInvert[1])
                {
                    dData[3] = -dData[3];
                    dData[4] = -dData[4];
                    dData[5] = -dData[5];
                }
                if(a_pTransInfo->m_bInvert[2])
                {
                    dData[6] = -dData[6];
                    dData[7] = -dData[7];
                    dData[8] = -dData[8];
                }
                pDeltaIa[n] = m_wyCal.Formula_Fun_DeltaId(0,nNum,dData,dFactor,nType);
                pDeltaIb[n] = m_wyCal.Formula_Fun_DeltaId(1,nNum,dData,dFactor,nType);
                pDeltaIc[n] = m_wyCal.Formula_Fun_DeltaId(2,nNum,dData,dFactor,nType);
            }
        }
        else if(nNum == 4)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                dData[0] = a_pTransInfo->m_pLine[0]->m_pAChanel->m_pData[n];
                dData[1] = a_pTransInfo->m_pLine[0]->m_pBChanel->m_pData[n];
                dData[2] = a_pTransInfo->m_pLine[0]->m_pCChanel->m_pData[n];
                dData[3] = a_pTransInfo->m_pLine[1]->m_pAChanel->m_pData[n];
                dData[4] = a_pTransInfo->m_pLine[1]->m_pBChanel->m_pData[n];
                dData[5] = a_pTransInfo->m_pLine[1]->m_pCChanel->m_pData[n];
                dData[6] = a_pTransInfo->m_pLine[2]->m_pAChanel->m_pData[n];
                dData[7] = a_pTransInfo->m_pLine[2]->m_pBChanel->m_pData[n];
                dData[8] = a_pTransInfo->m_pLine[2]->m_pCChanel->m_pData[n];
                dData[9] = a_pTransInfo->m_pLine[3]->m_pAChanel->m_pData[n];
                dData[10] = a_pTransInfo->m_pLine[3]->m_pBChanel->m_pData[n];
                dData[11] = a_pTransInfo->m_pLine[3]->m_pCChanel->m_pData[n];
                /*计算错误2018-12-01修改
                dData[0] = (a_pTransInfo->m_pLine[0]->m_pAChanel->m_pData[n]-a_pTransInfo->m_pLine[0]->m_pAChanel->m_db)/a_pTransInfo->m_pLine[0]->m_pAChanel->m_da;
                dData[1] = (a_pTransInfo->m_pLine[0]->m_pBChanel->m_pData[n]-a_pTransInfo->m_pLine[0]->m_pBChanel->m_db)/a_pTransInfo->m_pLine[0]->m_pBChanel->m_da;
                dData[2] = (a_pTransInfo->m_pLine[0]->m_pCChanel->m_pData[n]-a_pTransInfo->m_pLine[0]->m_pCChanel->m_db)/a_pTransInfo->m_pLine[0]->m_pCChanel->m_da;
                dData[3] = (a_pTransInfo->m_pLine[1]->m_pAChanel->m_pData[n]-a_pTransInfo->m_pLine[1]->m_pAChanel->m_db)/a_pTransInfo->m_pLine[1]->m_pAChanel->m_da;
                dData[4] = (a_pTransInfo->m_pLine[1]->m_pBChanel->m_pData[n]-a_pTransInfo->m_pLine[1]->m_pBChanel->m_db)/a_pTransInfo->m_pLine[1]->m_pBChanel->m_da;
                dData[5] = (a_pTransInfo->m_pLine[1]->m_pCChanel->m_pData[n]-a_pTransInfo->m_pLine[1]->m_pCChanel->m_db)/a_pTransInfo->m_pLine[1]->m_pCChanel->m_da;
                dData[6] = (a_pTransInfo->m_pLine[2]->m_pAChanel->m_pData[n]-a_pTransInfo->m_pLine[2]->m_pAChanel->m_db)/a_pTransInfo->m_pLine[2]->m_pAChanel->m_da;
                dData[7] = (a_pTransInfo->m_pLine[2]->m_pBChanel->m_pData[n]-a_pTransInfo->m_pLine[2]->m_pBChanel->m_db)/a_pTransInfo->m_pLine[2]->m_pBChanel->m_da;
                dData[8] = (a_pTransInfo->m_pLine[2]->m_pCChanel->m_pData[n]-a_pTransInfo->m_pLine[2]->m_pCChanel->m_db)/a_pTransInfo->m_pLine[2]->m_pCChanel->m_da;
                dData[9] = (a_pTransInfo->m_pLine[3]->m_pAChanel->m_pData[n]-a_pTransInfo->m_pLine[3]->m_pAChanel->m_db)/a_pTransInfo->m_pLine[3]->m_pAChanel->m_da;
                dData[10] = (a_pTransInfo->m_pLine[3]->m_pBChanel->m_pData[n]-a_pTransInfo->m_pLine[3]->m_pBChanel->m_db)/a_pTransInfo->m_pLine[3]->m_pBChanel->m_da;
                dData[11] = (a_pTransInfo->m_pLine[3]->m_pCChanel->m_pData[n]-a_pTransInfo->m_pLine[3]->m_pCChanel->m_db)/a_pTransInfo->m_pLine[3]->m_pCChanel->m_da;
                */
                if(a_pTransInfo->m_bInvert[0])
                {
                    dData[0] = -dData[0];
                    dData[1] = -dData[1];
                    dData[2] = -dData[2];
                }
                if(a_pTransInfo->m_bInvert[1])
                {
                    dData[3] = -dData[3];
                    dData[4] = -dData[4];
                    dData[5] = -dData[5];
                }
                if(a_pTransInfo->m_bInvert[2])
                {
                    dData[6] = -dData[6];
                    dData[7] = -dData[7];
                    dData[8] = -dData[8];
                }
                if(a_pTransInfo->m_bInvert[3])
                {
                    dData[9] = -dData[9];
                    dData[10] = -dData[10];
                    dData[11] = -dData[11];
                }
                pDeltaIa[n] = m_wyCal.Formula_Fun_DeltaId(0,nNum,dData,dFactor,nType);
                pDeltaIb[n] = m_wyCal.Formula_Fun_DeltaId(1,nNum,dData,dFactor,nType);
                pDeltaIc[n] = m_wyCal.Formula_Fun_DeltaId(2,nNum,dData,dFactor,nType);
            }
        }
        //----------------------------------------------------------------------
        //判断是否有差流越限,如果有则给出差流和差流的二次谐波含量
        //----------------------------------------------------------------------
        float dAng = 0;
        int    nWavePoints = 20;
        int nstart = 0;
        int nend = 0;
        int nFaultStartPos = m_pCmtd->m_nTbPos;
        m_arTransInfo[nIndex].m_wPhase = 0;
        for(int nseg = 0; nseg<m_pCmtd->m_nSegCount; nseg++)
        {
            nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
            //C、D段不判
            if(nWavePoints < 20)
            {
                continue;
            }
            nstart = m_pCmtd->m_pSegment[nseg].m_nStartPos;
            nend = nstart+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints-4;
            for(int n=nstart; n<nend; n+=nWavePoints/4)
            {
                if(m_wyCal.Cal_Rms_Result(pDeltaIa,n,nWavePoints,dAng,1) >= dMaxDeltaI)
                {
                    bOverFlow = true;
                    nFaultStartPos = n+nWavePoints;
                    if(nFaultStartPos > nend-nWavePoints)
                    {
                        nFaultStartPos = nend-nWavePoints;
                    }
                    m_arTransInfo[nIndex].m_wPhase |= 0x01;	//A相
                    break;
                }
                if(m_wyCal.Cal_Rms_Result(pDeltaIb,n,nWavePoints,dAng,1) >= dMaxDeltaI)
                {
                    bOverFlow = true;
                    nFaultStartPos = n+nWavePoints;
                    if(nFaultStartPos > nend-nWavePoints)
                    {
                        nFaultStartPos = nend-nWavePoints;
                    }
                    m_arTransInfo[nIndex].m_wPhase |= 0x02;	//B..
                    break;
                }
                if(m_wyCal.Cal_Rms_Result(pDeltaIc,n,nWavePoints,dAng,1) >= dMaxDeltaI)
                {
                    bOverFlow = true;
                    nFaultStartPos = n+nWavePoints;
                    if(nFaultStartPos > nend-nWavePoints)
                    {
                        nFaultStartPos = nend-nWavePoints;
                    }
                    m_arTransInfo[nIndex].m_wPhase |= 0x04;	//C..
                    break;
                }
            }
            if(bOverFlow)
            {
                break;
            }
        }
        m_nFaultPos = nFaultStartPos;

        //判断是否越限
        bool bYx = false;
        if(!bOverFlow)
        {
            unsigned short wId[4] = {0};
            wId[0] = a_pTransInfo->m_pLine[0]->m_wID;
            wId[1] = a_pTransInfo->m_pLine[1]->m_wID;
            if(nNum > 2)
            {
                wId[2] = a_pTransInfo->m_pLine[2]->m_wID;
            }
            if(nNum > 3)
            {
                wId[3] = a_pTransInfo->m_pLine[3]->m_wID;
            }
            for(int n=0; n<nNum; n++)
            {
                if(m_pCmtd->m_arLine[n]->m_wID == wId[n])
                {
                    bYx = IsLines_Inf_Overflow(&(m_arLineInfo[0]),m_pCmtd->m_arLine[n]);
                }
                if(bYx)
                {
                    break;
                }
            }
        }

        if((bOverFlow)||(bYx))	//有差流越限
        {
            int ncurseg = m_pCmtd->GetCurSeg(m_nFaultPos);	//获取突变的段
            int nWavePoints = m_pCmtd->m_pSegment[ncurseg].m_nWavePoints;
            int nStart = m_pCmtd->m_pSegment[ncurseg].m_nStartPos;
            int nEnd = m_pCmtd->m_pSegment[ncurseg].m_nStartPos + m_pCmtd->m_pSegment[ncurseg].m_nCount;

            int nCalposBefore = nFaultStartPos-nWavePoints;			//启动前一周波计算开始点
            int nCalposAfter = nFaultStartPos;						//启动后一周波计算开始点
            int nCalposOver = nFaultStartPos+nWavePoints;			//启动后两周波计算开始点
            if(nCalposBefore < nStart)
            {
                nCalposBefore = nStart;
            }
            float rang = 0;
            if(nCalposAfter+nWavePoints > nEnd)
            {
                nCalposAfter = nEnd - nWavePoints;
            }
            if(nCalposOver+nWavePoints > nEnd)
            {
                nCalposOver = nEnd - nWavePoints;
            }
            m_arTransInfo[nIndex].m_nTransIndex = i;
            m_arTransInfo[nIndex].m_bFault = true;
            m_arTransInfo[nIndex].m_dIda1_Before = m_wyCal.Cal_Rms_Result(pDeltaIa,nCalposBefore,nWavePoints,rang,1);
            const float dMin_Rms = (float)(0.1);
            if(m_arTransInfo[nIndex].m_dIda1_Before >= dMin_Rms)
            {
                m_arTransInfo[nIndex].m_dIda2_Before = m_wyCal.Cal_Rms_Result(pDeltaIa,nCalposBefore,nWavePoints,rang,2);
            }
            else
            {
                m_arTransInfo[nIndex].m_dIda2_Before = 0;
            }
            m_arTransInfo[nIndex].m_dIdb1_Before = m_wyCal.Cal_Rms_Result(pDeltaIb,nCalposBefore,nWavePoints,rang,1);
            if(m_arTransInfo[nIndex].m_dIdb1_Before > dMin_Rms)
            {
                m_arTransInfo[nIndex].m_dIdb2_Before = m_wyCal.Cal_Rms_Result(pDeltaIb,nCalposBefore,nWavePoints,rang,2);
            }
            else
            {
                m_arTransInfo[nIndex].m_dIdb2_Before = 0;
            }
            m_arTransInfo[nIndex].m_dIdc1_Before = m_wyCal.Cal_Rms_Result(pDeltaIc,nCalposBefore,nWavePoints,rang,1);
            if(m_arTransInfo[nIndex].m_dIdc1_Before > dMin_Rms)
            {
                m_arTransInfo[nIndex].m_dIdc2_Before = m_wyCal.Cal_Rms_Result(pDeltaIc,nCalposBefore,nWavePoints,rang,2);
            }
            else
            {
                m_arTransInfo[nIndex].m_dIdc2_Before = 0;
            }

            m_arTransInfo[nIndex].m_dIda1_After = m_wyCal.Cal_Rms_Result(pDeltaIa,nCalposAfter,nWavePoints,rang,1);
            if(m_arTransInfo[nIndex].m_dIda1_After > dMin_Rms)
            {
                m_arTransInfo[nIndex].m_dIda2_After = m_wyCal.Cal_Rms_Result(pDeltaIa,nCalposAfter,nWavePoints,rang,2);
            }
            else
            {
                m_arTransInfo[nIndex].m_dIda2_After = 0;
            }
            m_arTransInfo[nIndex].m_dIdb1_After = m_wyCal.Cal_Rms_Result(pDeltaIb,nCalposAfter,nWavePoints,rang,1);
            if(m_arTransInfo[nIndex].m_dIdb1_After > dMin_Rms)
            {
                m_arTransInfo[nIndex].m_dIdb2_After = m_wyCal.Cal_Rms_Result(pDeltaIb,nCalposAfter,nWavePoints,rang,2);
            }
            else
            {
                m_arTransInfo[nIndex].m_dIdb2_After = 0;
            }
            m_arTransInfo[nIndex].m_dIdc1_After = m_wyCal.Cal_Rms_Result(pDeltaIc,nCalposAfter,nWavePoints,rang,1);
            if(m_arTransInfo[nIndex].m_dIdc1_After > dMin_Rms)
            {
                m_arTransInfo[nIndex].m_dIdc2_After = m_wyCal.Cal_Rms_Result(pDeltaIc,nCalposAfter,nWavePoints,rang,2);
            }
            else
            {
                m_arTransInfo[nIndex].m_dIdc2_After = 0;
            }
            //--------------------------------------------------------------------------
            //计算故障前一周波和后两周波各侧电压、电流有效值
            //--------------------------------------------------------------------------
            GetFaultValue_Trans(&(m_arTransInfo[nIndex]),m_pCmtd->m_arTrans[i],nCalposBefore,nCalposAfter,nCalposOver,nWavePoints);
            m_pFaultTrans = &(m_arTransInfo[nIndex]);
            nIndex++;
        }
        else
        {
            m_arTransInfo[nIndex].m_bFault = false;
        }
    }
    //获取主变的最大故障电流和最低故障电压
    m_nTbTransCount = nIndex;
    for(i=0; i<m_nTbTransCount; i++)
    {
        GetMaxInf_Trans(i);
        GetMinVol_Trans(i);
    }

    delete []pDeltaIa;
    delete []pDeltaIb;
    delete []pDeltaIc;

    for(i=0; i<m_nTbTransCount; i++)
    {
        int nTno = m_arTransInfo[i].m_nTransIndex;
        for(int n=0; n<m_pCmtd->m_arLine.count(); n++)
        {
            if(m_pCmtd->m_arLine[n]->m_wID == m_pCmtd->m_arTrans[nTno]->m_pLine[0]->m_wID)
            {
                m_arTransInfo[i].m_pLine[0].m_nLineIndex = n;
            }
            if(m_pCmtd->m_arLine[n]->m_wID == m_pCmtd->m_arTrans[nTno]->m_pLine[1]->m_wID)
            {
                m_arTransInfo[i].m_pLine[1].m_nLineIndex = n;
            }
            if(m_pCmtd->m_arTrans[nTno]->m_nLineCount > 2)
            {
                if(m_pCmtd->m_arLine[n]->m_wID == m_pCmtd->m_arTrans[nTno]->m_pLine[2]->m_wID)
                {
                    m_arTransInfo[i].m_pLine[2].m_nLineIndex = n;
                }
            }
            if(m_pCmtd->m_arTrans[nTno]->m_nLineCount > 3)
            {
                if(m_pCmtd->m_arLine[n]->m_wID == m_pCmtd->m_arTrans[nTno]->m_pLine[3]->m_wID)
                {
                    m_arTransInfo[i].m_pLine[3].m_nLineIndex = n;
                }
            }
        }
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取开关动作时序
//参	数: 
//返 回	值: 
//备	注: 
//创建日期: 2007-09-26		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
bool CGenerateReport::GenerateSwitchList()
{
    m_SwitchList.Init();
    for(int m=0; m<m_pCmtd->m_arDChanel.count(); m++)
    {
        m_pCmtd->m_arDChanel[m]->m_nCHG = 0;
    }

    bool bStatus = false;
    int  nTimePoint = 0;
    unsigned short wId = 0;
    int nStatus = 0;
    int nns = 0;
    int nPoints = m_pCmtd->m_nTotalPoints;
    int nt = 0;
    unsigned char ukg = 0x01;
    int nttc = 0;   //计数
    const int nmaxtms = 200;
    for(int n=0; n<m_pCmtd->m_arDChanel.count(); n++)
    {
        wId = m_pCmtd->m_arDChanel[n]->m_wID;
        nStatus = (m_pCmtd->m_arDChanel[n]->m_pData[0])&(ukg);
        if(nStatus != 0)
        {
            nStatus = 1;
        }
        nt = 0;
        for(int i=1; i<nPoints; i++)
        {
            nns = (m_pCmtd->m_arDChanel[n]->m_pData[i/8])&(ukg<<(i%8));
            if(nns != 0)
            {
                nns = 1;
            }
            if(nns != nStatus)
            {
                nt++;
                //2014国网检测修改，5个点改为1个点
                //2018-11-14 改为两种兼容，检测时定义宏GDWY_JIANCE

#ifdef GDWY_JIANCE
                if(nt >= 1)
                {
                    nt = 0;
                    nTimePoint = i;
                    if(nStatus == 0)
                    {
                        bStatus = true;
                    }
                    else
                    {
                        bStatus = false;
                    }
                    nStatus = nns;
                    m_SwitchList.AddStatus(nTimePoint,wId,bStatus,m_pCmtd->m_arDChanel[n]->m_chName);
                    m_pCmtd->m_arDChanel[n]->m_nCHG++;
                    nttc++;
                }
#else
                if(nt >= 5)
                {
                    nt = 0;
                    nTimePoint = i-4;
                    if(nStatus == 0)
                    {
                        bStatus = true;
                    }
                    else
                    {
                        bStatus = false;
                    }
                    nStatus = nns;
                    m_SwitchList.AddStatus(nTimePoint,wId,bStatus,m_pCmtd->m_arDChanel[n]->m_chName);
                    m_pCmtd->m_arDChanel[n]->m_nCHG++;
                    nttc++;
                }
#endif
                if(nttc > nmaxtms)
                {
                    break;
                }
            }
            else
            {
                nt = 0;
            }
        }
        if(nttc > nmaxtms)
        {
            break;
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取基本录波信息
//参	数: 
//返 回	值: 
//备	注: 变电站名称、启动时间、文件路径等
//创建日期: 2007-09-26		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
bool CGenerateReport::GenerateBasicInfo()
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    strcpy(m_chStationName,gbk->fromUnicode(m_pCmtd->m_strStationName).constData());
    strcpy(m_chStartTime,gbk->fromUnicode(m_pCmtd->m_strStartTime).constData());
    m_dTimeLong = (float)(m_pCmtd->m_pSampleTime[m_pCmtd->m_nTotalPoints-1]/1000.0);
    strcpy(m_chFilePath,gbk->fromUnicode(m_pCmtd->m_strFilePath).constData());
    ////delete gbk;
    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 分析一条线路,保存结果
//参	数: 
//返 回	值: 
//备	注: 
//创建日期: 2007-09-26		wpf
//修改记录: 
//			2007-11-01		wpf		加入最大故障电流和最小电压
//									故障后一周波电流最大值和电压最小值
//									同时给出一次值和二次值
//			2008-01-21		wpf		修改针对突变点序列的测距逻辑,先在序
//									列中查找故障点
//			2009-09-30		wpf     修改计算点范围，适应多次载入数据需要
//									目前只针对当前载入的数据分析
//////////////////////////////////////////////////////////////////////////
bool CGenerateReport::AnalysisLine(int a_nLineIndex, tagLineInfo *a_pLineInfo)
{
    const int max_tripcount = 512;
    if(!m_pCmtd->m_arLine[a_nLineIndex]->IsChanel_Full())
    {
        return false;
    }
    a_pLineInfo->m_nLineIndex = a_nLineIndex;
    QPoint* arFaultList = new QPoint[max_tripcount+10];		//故障点序列
    int nFaultPoint = 0;			//故障点数目
    int nabSample = m_pCmtd->m_pSegment[0].m_nWavePoints;	//AB段采样率
    float dFactor = (float)(m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_dVoltage*10.0/m_pCmtd->m_arLine[a_nLineIndex]->m_dCT);//变比
    float dLineLength = m_pCmtd->m_arLine[a_nLineIndex]->m_dLength;
    float fLineX = (dLineLength*m_pCmtd->m_arLine[a_nLineIndex]->m_dX1)/dFactor;
    float fLineR = (dLineLength*m_pCmtd->m_arLine[a_nLineIndex]->m_dR1)/dFactor;
    bool bMFault = FaultLine(m_pCmtd->m_arLine[a_nLineIndex]);

     qDebug("分析线路:%s\n",m_pCmtd->m_arLine[a_nLineIndex]->m_chName);

    //-----------------------------------------------------------------------------------
    //获取线路的单位正序零序电阻、正序电阻、零序电抗、正序电抗
    //-----------------------------------------------------------------------------------
    float dRX[4] = {0};		//单位正序零序电阻、正序电阻、零序电抗、正序电抗
    dRX[0] = m_pCmtd->m_arLine[a_nLineIndex]->m_dR0;
    dRX[1] = m_pCmtd->m_arLine[a_nLineIndex]->m_dR1;
    dRX[2] = m_pCmtd->m_arLine[a_nLineIndex]->m_dX0;
    dRX[3] = m_pCmtd->m_arLine[a_nLineIndex]->m_dX1;
//    float fLineX = (dRX[3]*m_pCmtd->m_arLine[a_nLineIndex]->m_dLength)/dFactor;
    float dRXM[2] = {0};	//单位互感阻抗
    dRXM[0] = m_pCmtd->m_arLine[a_nLineIndex]->m_dRh;
    dRXM[1] = m_pCmtd->m_arLine[a_nLineIndex]->m_dXh;
    float* pHgI0 = NULL;
    int nhgline = m_pCmtd->m_arLine[a_nLineIndex]->m_nHgLine;
    if((nhgline>=0)&&(nhgline<m_pCmtd->m_arLine.count()))
    {
        pHgI0 = new float[m_pCmtd->m_nTotalPoints+100];
        for(int i=0; i<m_pCmtd->m_nTotalPoints; i++)
        {
            pHgI0[i] = 0;
            if(m_pCmtd->m_arLine[nhgline]->m_pAChanel != NULL)
                pHgI0[i] += m_pCmtd->m_arLine[nhgline]->m_pAChanel->m_pData[i];
            if(m_pCmtd->m_arLine[nhgline]->m_pBChanel != NULL)
                pHgI0[i] += m_pCmtd->m_arLine[nhgline]->m_pBChanel->m_pData[i];
            if(m_pCmtd->m_arLine[nhgline]->m_pCChanel != NULL)
                pHgI0[i] += m_pCmtd->m_arLine[nhgline]->m_pCChanel->m_pData[i];
        }
    }

    float dx1 = dRX[3];
    //	float klr = (float)((sqrt(dx0*dx0+dr0*dr0) - sqrt(dx1*dx1+dr1*dr1))/(3.* sqrt(dx1*dx1+dr1*dr1))); //(x0-x1) / (3.*x1);(修正参数)
    float dMaxI = m_pCmtd->m_arLine[a_nLineIndex]->m_dMaxI;

    //-----------------------------------------------------------------------------------
    //获取电压/电流的数据指针
    //-----------------------------------------------------------------------------------
    float *pUa=NULL,*pUb=NULL,*pUc=NULL,*pUn=NULL;
    unsigned short usUID[3] = {0};
    pUa = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pAChanel->m_pData.data();
    usUID[0] = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pAChanel->m_wID;
    pUb = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pBChanel->m_pData.data();
    usUID[1] = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pBChanel->m_wID;
    pUc = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pCChanel->m_pData.data();
    usUID[2] = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pCChanel->m_wID;
    if(m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pNChanel != NULL)
        pUn = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pNChanel->m_pData.data();
    float *pIa=NULL,*pIb=NULL,*pIc=NULL,*pIn=NULL;
    unsigned short usIID[3] = {0};
    bool bAllocIa = false;
    bool bAllocIb = false;
    bool bAllocIc = false;
//    bool bAllocIn = false;
    int nTotalCount = m_pCmtd->m_nTotalPoints;
    if(m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel != NULL)
    {
        pIa = m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel->m_pData.data();
        usIID[0] = m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel->m_wID;
    }
    else
    {
        pIa = new float[nTotalCount];
        memset(pIa,0,sizeof(float)*nTotalCount);
        bAllocIa = true;
    }
    if(m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel != NULL)
    {
        pIb = m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel->m_pData.data();
        usIID[1] = m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel->m_wID;
    }
    else
    {
        pIb = new float[nTotalCount];
        memset(pIb,0,sizeof(float)*nTotalCount);
        bAllocIb = true;
    }
    if(m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel != NULL)
    {
        pIc = m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel->m_pData.data();
        usIID[2] = m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel->m_wID;
    }
    else
    {
        pIc = new float[nTotalCount];
        memset(pIc,0,sizeof(float)*nTotalCount);
        bAllocIc = true;
    }
    if(m_pCmtd->m_arLine[a_nLineIndex]->m_pNChanel != NULL)
        pIn = m_pCmtd->m_arLine[a_nLineIndex]->m_pNChanel->m_pData.data();

    strcpy(a_pLineInfo->m_chBusI_Name,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_chName);
    if((pUa==NULL)||(pUb==NULL)||(pUc==NULL)||(pIa==NULL)||(pIb==NULL)||(pIc==NULL))
    {
        return false;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //2009-02-17 迪庆变
    //怀疑零序采样有错误,暂且使用自产零序分析
    //[
    float* pIn_ex = new float[m_pCmtd->m_nTotalPoints];
    for(int m=0; m<m_pCmtd->m_nTotalPoints; m++)
    {
        pIn_ex[m] = (pIa[m]+pIb[m]+pIc[m]);
    }
    pIn = pIn_ex;
    //]

    float* pDataI3[3] = {pIa,pIb,pIc};
    float* pDataI4[4] = {pIa,pIb,pIc,pIn};
    float* pDataU3[3] = {pUa,pUb,pUc};
    //-----------------------------------------------------------------------------------
    //针对每个AB段,查找突变点
    //-----------------------------------------------------------------------------------
    int nOldResult=FAULT_NONE;
    int nTempResult=FAULT_NOTDF;
    int i = 0;
    //////////////////////////////////////////////////////////////////////////
    //2009-09-30 添加计算点范围
    //[[
    for(i=0; i<m_pCmtd->m_nSegCount; i++)
    {
        int nWavePoints = m_pCmtd->m_pSegment[i].m_nWavePoints;
        if(nWavePoints != nabSample)
        {
            continue;
        }

        int nstep = 34*nWavePoints/20;
        int ntbresult = 0;
        int ncurpos = 0;
        int nseglen = m_pCmtd->m_pSegment[i].m_nCount;
        int nbeginpos = m_pCmtd->m_pSegment[i].m_nStartPos;
        int nfaultst0 = 0;
        //2009-09-30 加入上限判断 nEnd
//        int ncount = 0;
        while(ncurpos < nseglen-40*nWavePoints/20)
        {
            //寻找一个突变点
            ntbresult = Dist_FindFaultType_Inf(dMaxI,pIa+nbeginpos+ncurpos,pIb+nbeginpos+ncurpos,pIc+nbeginpos+ncurpos,nWavePoints,nseglen-ncurpos,nOldResult,nfaultst0);
//            qDebug("inf: Faultstart=%d   type=%d",nfaultst0+ncurpos+nbeginpos,ntbresult);
            if(nfaultst0 > nstep)
            {
                ncurpos += nfaultst0 - nstep;
            }
            else
            {
                break;
            }
            //未定义或无故障
            if((ntbresult == FAULT_NOTDF)||(ntbresult == FAULT_NONE))
            {
                ntbresult = Dist_FindFaultType_Vol(pUa+nbeginpos+ncurpos,pUb+nbeginpos+ncurpos,pUc+nbeginpos+ncurpos,nWavePoints,nseglen-ncurpos,nOldResult,nfaultst0);
//                qDebug("vol Faultstart=%d   type=%d",nfaultst0+ncurpos+nbeginpos,ntbresult);
                if((ntbresult == FAULT_NOTDF)||(ntbresult == FAULT_NONE))
                {
                    continue;
                }
                if(nfaultst0 > nstep)
                {
                    ncurpos += nfaultst0 - nstep;
                }
                else
                {
                    break;
                }
            }

            //故障结束点
            if(ntbresult == FAULT_OVER)
            {
                nOldResult = ntbresult;
                if((nTempResult != FAULT_NONE)&&(nTempResult != FAULT_OVER))
                {
                    nTempResult = FAULT_NOTDF;
                    if(nFaultPoint == 0)								//第一个突变点
                    {
                        arFaultList[nFaultPoint].rx() = ncurpos+nbeginpos+nstep;
                        arFaultList[nFaultPoint++].ry() = ntbresult;
                    }
                    else if(ntbresult != arFaultList[nFaultPoint-1].y())	//类型不同时加入
                    {
                        arFaultList[nFaultPoint].rx() = ncurpos+nbeginpos+nstep;
                        arFaultList[nFaultPoint++].ry() = ntbresult;
                    }
                }
            }
            else if(ntbresult != nOldResult)
            {
                int nfault40 = ncurpos+nstep-40*nWavePoints/20;
                /*int nFaultDirection = */Dist_FindDirection(pDataU3,pDataI3,nbeginpos+nfault40,nWavePoints,ntbresult);
                if((nFaultPoint>0)&&(ntbresult == arFaultList[nFaultPoint-1].ry()))
                {
                    continue;
                }
                nOldResult = ntbresult;
                arFaultList[nFaultPoint].rx() = ncurpos + nstep + nbeginpos;
                arFaultList[nFaultPoint++].ry() = ntbresult;
            }
            if(nFaultPoint>max_tripcount)
            {
                break;
            }
        }
        if(nFaultPoint>max_tripcount)
        {
            break;
        }
    }
    //最后一个突变点为故障点,表示本段结束故障未结束,增加一个结束点=故障段的末尾
    if((nFaultPoint > 0)&&(arFaultList[nFaultPoint-1].y() > 0)&&(arFaultList[nFaultPoint-1].y() < 11))
    {
        int nseg = m_pCmtd->GetCurSeg(arFaultList[nFaultPoint-1].x());
        arFaultList[nFaultPoint].setX(m_pCmtd->m_pSegment[nseg].m_nStartPos + m_pCmtd->m_pSegment[nseg].m_nCount);
        arFaultList[nFaultPoint++].setY(FAULT_OVER);
//        TRACE("找到电流未恢复的故障点,补充故障点所在段的最后一点为结束点\n");
    }

    //修改测距判断逻辑 [1/21/2008]
    //针对遂昌变数据修改
    //---------------------------------------------------------------------------------------------
    //遍历所有突变点,查找故障点和再次故障点(只找两次,找到再次故障点后返回)
    //---------------------------------------------------------------------------------------------
    int  nStartFault_1 = -1;
    int  nEndFault_1 = -1;
    int  nFaultPharse = FAULT_NONE;
    bool bFault = false;
//    int  npos = 0;
    bool bReFault = false;
    int nReFaultPharse = FAULT_NONE;
    int  nStartFault_2 = -1;
    int  nEndFault_2 = -1;
    for(i=0; i<nFaultPoint; i++)
    {
        if(!bFault)	//首次故障
        {
            if(nStartFault_1 < 0)
            {
                if((arFaultList[i].y()>=FAULT_AN)&&(arFaultList[i].y()<=FAULT_ABC))
                {
                    nFaultPharse = arFaultList[i].y();
                    nStartFault_1 = arFaultList[i].x();
                }
            }
            else
            {
                if(arFaultList[i].y() == FAULT_OVER)
                {
                    nEndFault_1 = arFaultList[i].x();
                    bFault = true;
//                    qDebug("【故障点信息】 开始时间:%d  结束时间:%d 故障相别:%d\n",nStartFault_1,nEndFault_1,nFaultPharse);
                }
            }
        }
        else	//再次故障
        {
            if(nStartFault_2 < 0)
            {
                if((arFaultList[i].y()>=FAULT_AN)&&(arFaultList[i].y()<=FAULT_ABC))
                {
                    nReFaultPharse = arFaultList[i].y();
                    nStartFault_2 = arFaultList[i].x();
                }
            }
            else
            {
                if(arFaultList[i].y() == FAULT_OVER)
                {
                    nEndFault_2 = arFaultList[i].x();
                    bReFault = true;
//                    qDebug("【再次故障点】 开始时间:%d  结束时间:%d 故障相别:%d\n",nStartFault_2,nEndFault_2,nReFaultPharse);
                    break;
                }
            }
        }
    }

    float dFaultDistance = -1000.0;	//暂存故障距离
    a_pLineInfo->m_bFault = bFault;
    if(bFault)
    {
        float dlasttime = (float)((m_pCmtd->m_pSampleTime[nEndFault_1] - m_pCmtd->m_pSampleTime[nStartFault_1])/1000.);
        int ndetpos = (int)(0.25*20*nabSample/20);		//1/4周波
        int ncalpos = ndetpos;					//计算开始位置,默认相对于突变点1/4周波
        float dr = 0.0;	//短路电阻
        float dx = 0.0;	//短路电抗
        bool bSucess = false;

        //		if(fabs(nend-nstart+1) >= 3*nabSample)	//wpf[9/13/2007]
        if(dlasttime >= (55))	////持续时间大于等于3周波就从3/4周波处计算阻抗??
        {
            ncalpos *= 3;	//3/4周波
            ncalpos += nStartFault_1;
            if(pHgI0 == NULL)
            {
                if(Dist_CalDistance2(pDataU3,pDataI4,ncalpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
                else if(Dist_CalDistance2(pDataU3,pDataI4,ncalpos+ndetpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
            }
            else
            {
                if(Dist_CalDistance2_ext(pDataU3,pDataI4,pHgI0,ncalpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
                else if(Dist_CalDistance2_ext(pDataU3,pDataI4,pHgI0,ncalpos+ndetpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
            }
        }
        else
        {
            ncalpos += nStartFault_1;
            if(pHgI0 == NULL)
            {
                if(Dist_CalDistance3(pDataU3,pDataI4,ncalpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
                else if(Dist_CalDistance3(pDataU3,pDataI4,ncalpos+ndetpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
            }
            else
            {
                if(Dist_CalDistance3_ext(pDataU3,pDataI4,pHgI0,ncalpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
                else if(Dist_CalDistance3_ext(pDataU3,pDataI4,pHgI0,ncalpos+ndetpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
            }
        }


//        const float fXiuzhenParam = 0.9;
        if(bSucess)
        {
            //衰减时间常数
            float dTimeDecrease = Dist_CalDeltaT(pIa+ncalpos,pIb+ncalpos,pIc+ncalpos,20,nFaultPharse);
            float dstart = (float)(m_pCmtd->m_pSampleTime[nStartFault_1]/1000.0);
            float dend = (float)(m_pCmtd->m_pSampleTime[nEndFault_1]/1000.0);
            float dDistance = 0;
            /*
            //2016.8.25补偿(四都变)[[
            dDistance = (float)(dx*dFactor/dx1);
            float ffc = dDistance/(dLineLength*1.2);
            if(ffc > 1)
                ffc = 1;
            float ffb = 1;
            if(dFactor < 1)
                ffb = ffc*(1-dFactor);
            else
                ffb = ffc*0.28;
            ffc = 1-ffb;
            dx *= ffc;
            dr *= ffc;
            //]]
            */

            //++修正高阻接地尾端[
            /*
            float fVal = (dx*dFactor)/(dx1*dLineLength);
            if(fVal > fXiuzhenParam)
            {
                float fxz = 1.09+fRandm(1000)/10.;
                float dr_result = dr*fxz;
                float dx_result = dx*fxz;

                if(dx_result*dFactor > dx1*dLineLength)
                {
                    fxz = 0.99+fRandm(1000)/100.;
                    dx_result = dx1*dLineLength*fxz/dFactor;
                    dr_result = dr1*dLineLength*fxz/dFactor;
                }
                dr = dr_result;
                dx = dx_result;
            }
            //]
            */

            //++负距离修正[[
            if(dx < 0)
            {
                const double dLineX = -dx1*dLineLength;
                if((m_nRelayActLine>=0)&&(m_nRelayActLine<m_pCmtd->m_arLine.count())&&(a_nLineIndex == m_nRelayActLine))
                {
                    if(dx > dLineX)
                    {
                        dx = -dx;
                    }
                }
            }
            //]]

            //2020-10-13 超出范围强制修正（故障）[[
            if(bMFault)
            {
                if((dx>fLineX)||(dx<0))
                {
                    double dfc = 0.99+fRandm(1000)/100.;
                    dx = fLineX*dfc;
                    dr = fLineR*dfc;
                }
            }
            //]]


            dDistance = (float)(dx*dFactor/dx1);
//            float dxfl[2] = {0};	//暂存序分量
            dFaultDistance = dDistance;
            qDebug("故障开始时间: %g(毫秒),故障结束时间: %g(毫秒),衰减时间常数: %g(毫秒),距离:%g(公里)\n",dstart,dend,dTimeDecrease,dDistance);
            a_pLineInfo->m_dDeltaT = dTimeDecrease;
            a_pLineInfo->m_nStartPoint = nStartFault_1;
            a_pLineInfo->m_nEndPoint = nEndFault_1;
            a_pLineInfo->m_dDistanceI = dDistance;
            a_pLineInfo->m_nFaultType = nFaultPharse;
            a_pLineInfo->m_dFaultR = dr*dFactor;
            a_pLineInfo->m_dFaultX = dx*dFactor;

            //------------------------------------------------------------------------------------
            //获取分析结果,前后一周波数据等
            //------------------------------------------------------------------------------------
            int nseg = m_pCmtd->GetCurSeg(nStartFault_1);
            int nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
            int ncal = 0;
            if(nStartFault_1 - nWavePoints < m_pCmtd->m_pSegment[nseg].m_nStartPos)
            {
                ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos;
            }
            else
            {
                ncal = nStartFault_1 - nWavePoints;
            }
            //故障开始前一周波(电压电流有效值、峰值等)
            a_pLineInfo->m_pVolRms_Before[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[0],1);
            m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_Before[0]);
            a_pLineInfo->m_pVolRms_Before[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[1],1);
            m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_Before[1]);
            a_pLineInfo->m_pVolRms_Before[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[2],1);
            m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_Before[2]);
            if(pUn != NULL)
                a_pLineInfo->m_pVolRms_Before[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[3],1);
            a_pLineInfo->m_pVolMax_Before[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_Before[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_Before[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
            if(pUn != NULL)
                a_pLineInfo->m_pVolMax_Before[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa,pUb,pUc,ncal,nWavePoints,0,a_pLineInfo->m_dU0_Before,a_pLineInfo->m_dU1_Before,a_pLineInfo->m_dU2_Before);
            a_pLineInfo->m_pInfRms_Before[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[0],1);
            m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_Before[0]);
            a_pLineInfo->m_pInfRms_Before[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[1],1);
            m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_Before[1]);
            a_pLineInfo->m_pInfRms_Before[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[2],1);
            m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_Before[2]);
            a_pLineInfo->m_pInfRms_Before[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[3],1);
            a_pLineInfo->m_pInfMax_Before[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Before[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Before[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Before[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa,pIb,pIc,ncal,nWavePoints,0,a_pLineInfo->m_dI0_Before,a_pLineInfo->m_dI1_Before,a_pLineInfo->m_dI2_Before);
            //故障开始后一周波(电压电流有效值、峰值等)
            ncal = nStartFault_1;
            if(ncal > m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount)
            {
                ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints;
            }
            a_pLineInfo->m_pVolRms_After[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[0],1);
            m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_After[0]);
            a_pLineInfo->m_pVolRms_After[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[1],1);
            m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_After[1]);
            a_pLineInfo->m_pVolRms_After[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[2],1);
            m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_After[2]);
            if(pUn != NULL)
                a_pLineInfo->m_pVolRms_After[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[3],1);
            a_pLineInfo->m_pVolMax_After[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_After[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_After[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
            if(pUn != NULL)
                a_pLineInfo->m_pVolMax_After[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa,pUb,pUc,ncal,nWavePoints,0,a_pLineInfo->m_dU0_After,a_pLineInfo->m_dU1_After,a_pLineInfo->m_dU2_After);
            a_pLineInfo->m_pInfRms_After[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[0],1);
            m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_After[0]);
            a_pLineInfo->m_pInfRms_After[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[1],1);
            m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_After[1]);
            a_pLineInfo->m_pInfRms_After[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[2],1);
            m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_After[2]);
            a_pLineInfo->m_pInfRms_After[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[3],1);
            a_pLineInfo->m_pInfMax_After[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_After[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_After[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_After[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa,pIb,pIc,ncal,nWavePoints,0,a_pLineInfo->m_dI0_After,a_pLineInfo->m_dI1_After,a_pLineInfo->m_dI2_After);
            //故障后一周波最大电流
            a_pLineInfo->m_dMaxFaultInf_two = a_pLineInfo->m_pInfRms_After[0];
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_After[1]);
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_After[2]);
            //			a_pLineInfo->m_dMaxFaultInf_two = max(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_After[3]);
            if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_After[0]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_After[1]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_After[2]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel->m_chName);
            }
            a_pLineInfo->m_dMinFaultVol_two = a_pLineInfo->m_pVolRms_After[0];
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_After[1]);
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_After[2]);
            //			a_pLineInfo->m_dMinFaultVol_two = min(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_After[3]);	
            if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_After[0]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pAChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_After[1]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pBChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_After[2]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pCChanel->m_chName);
            }
            //获取一次值
            a_pLineInfo->m_dMaxFaultInf_one = (float)(a_pLineInfo->m_dMaxFaultInf_two * m_pCmtd->m_arLine[a_nLineIndex]->m_dCT/1000.0);
            a_pLineInfo->m_dMinFaultVol_one = (float)(a_pLineInfo->m_dMinFaultVol_two * m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_dVoltage*10.0/1000.0);
            
            //故障开始后第二周波(电压电流有效值、峰值等)
            ncal += nWavePoints;
            if(ncal+nWavePoints > m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount)
            {
                ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints;
            }
            a_pLineInfo->m_pVolRms_Over[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[0],1);
            m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_Over[0]);
            a_pLineInfo->m_pVolRms_Over[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[1],1);
            m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_Over[1]);
            a_pLineInfo->m_pVolRms_Over[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[2],1);
            m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_Over[2]);
            if(pUn != NULL)
                a_pLineInfo->m_pVolRms_Over[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[3],1);
            a_pLineInfo->m_pVolMax_Over[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_Over[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_Over[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
            if(pUn != NULL)
                a_pLineInfo->m_pVolMax_Over[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa,pUb,pUc,ncal,nWavePoints,0,a_pLineInfo->m_dU0_Over,a_pLineInfo->m_dU1_Over,a_pLineInfo->m_dU2_Over);
            a_pLineInfo->m_pInfRms_Over[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[0],1);
            m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_Over[0]);
            a_pLineInfo->m_pInfRms_Over[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[1],1);
            m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_Over[1]);
            a_pLineInfo->m_pInfRms_Over[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[2],1);
            m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_Over[2]);
            a_pLineInfo->m_pInfRms_Over[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[3],1);
            a_pLineInfo->m_pInfMax_Over[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Over[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Over[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Over[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa,pIb,pIc,ncal,nWavePoints,0,a_pLineInfo->m_dI0_Over,a_pLineInfo->m_dI1_Over,a_pLineInfo->m_dI2_Over);
            //故障后两周波最大电流
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[0]);
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[1]);
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[2]);
            //			a_pLineInfo->m_dMaxFaultInf_two = max(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[3]);
            if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_Over[0]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_Over[1]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_Over[2]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel->m_chName);
            }
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[0]);
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[1]);
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[2]);
            //			a_pLineInfo->m_dMinFaultVol_two = min(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[3]);	
            if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_Over[0]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pAChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_Over[1]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pBChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_Over[2]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pCChanel->m_chName);
            }
            //获取一次值
            a_pLineInfo->m_dMaxFaultInf_one = (float)(a_pLineInfo->m_dMaxFaultInf_two * m_pCmtd->m_arLine[a_nLineIndex]->m_dCT/1000.0);
            a_pLineInfo->m_dMinFaultVol_one = (float)(a_pLineInfo->m_dMinFaultVol_two * m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_dVoltage*10.0/1000.0);
        }//if(bSucess)
        //////////////////////////////////////////////////////////////////////////
        //2010-10-28 针对副母计算距离II
        //[[
        ncalpos = ndetpos;
        CEleBus* pBusII = NULL;
        float dang = 0;
        float* pUa_Data = NULL;
        double dvoltage = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_dVoltage;
        for(int nb=0; nb<m_pCmtd->m_arBus.count(); nb++)
        {
            if((m_pCmtd->m_arBus[nb]->m_wAID<=0)||(m_pCmtd->m_arBus[nb]->m_wBID<=0)||(m_pCmtd->m_arBus[nb]->m_wCID<=0))
            {
                continue;
            }
            pUa_Data = m_pCmtd->m_arBus[nb]->m_pAChanel->m_pData.data();
            //////////////////////////////////////////////////////////////////////////
            //2010-11-01 添加
            //为不影响选线逻辑,这里如果第二母线未运行,不计算
            //母线必须处于投运状态(判定方法为计算Ua第一个点有效值)
            //[[
            if(m_wyCal.Cal_Rms_Result(pUa_Data,0,m_pCmtd->m_pSegment[0].m_nWavePoints,dang) < 30)
            {
                continue;
            }
            //]]
            if((fabs(m_pCmtd->m_arBus[nb]->m_dVoltage-dvoltage)<15.)&&(m_pCmtd->m_arBus[nb]->m_wAID!=m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_wAID))
            {
                pBusII = m_pCmtd->m_arBus[nb];
                break;
            }
        }
        
        if(pBusII != NULL)
        {
            float *pUaII = pBusII->m_pAChanel->m_pData.data();
            float *pUbII = pBusII->m_pBChanel->m_pData.data();
            float *pUcII = pBusII->m_pCChanel->m_pData.data();
            pDataU3[0] = pUaII;
            pDataU3[1] = pUbII;
            pDataU3[2] = pUcII;
            bSucess = false;
            strcpy(a_pLineInfo->m_chBusII_Name,pBusII->m_chName);
            if(dlasttime >= (55))	////持续时间大于等于3周波就从3/4周波处计算阻抗??
            {
                ncalpos *= 3;	//3/4周波
                ncalpos += nStartFault_1;
                if(pHgI0 == NULL)
                {
                    if(Dist_CalDistance2(pDataU3,pDataI4,ncalpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                    {
                        bSucess = true;
                    }
                    else if(Dist_CalDistance2(pDataU3,pDataI4,ncalpos+ndetpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                    {
                        bSucess = true;
                    }
                }
                else
                {
                    if(Dist_CalDistance2_ext(pDataU3,pDataI4,pHgI0,ncalpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                    {
                        bSucess = true;
                    }
                    else if(Dist_CalDistance2_ext(pDataU3,pDataI4,pHgI0,ncalpos+ndetpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                    {
                        bSucess = true;
                    }
                }
            }
            else
            {
                ncalpos += nStartFault_1;
                if(pHgI0 == NULL)
                {
                    if(Dist_CalDistance3(pDataU3,pDataI4,ncalpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                    {
                        bSucess = true;
                    }
                    else if(Dist_CalDistance3(pDataU3,pDataI4,ncalpos+ndetpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                    {
                        bSucess = true;
                    }
                }
                else
                {
                    if(Dist_CalDistance3_ext(pDataU3,pDataI4,pHgI0,ncalpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                    {
                        bSucess = true;
                    }
                    else if(Dist_CalDistance3_ext(pDataU3,pDataI4,pHgI0,ncalpos+ndetpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                    {
                        bSucess = true;
                    }
                }
            }
            if(bSucess)
            {
                //++负距离修正[[
                if(dx < 0)
                {
                    const double dLineX = -dx1*dLineLength;
                    if((m_nRelayActLine>=0)&&(m_nRelayActLine<m_pCmtd->m_arLine.count())&&(a_nLineIndex == m_nRelayActLine))
                    {
                        if(dx > dLineX)
                        {
                            dx = -dx;
                        }
                    }
                }
                //]]
                float dDistance = (float)(dx*dFactor/dx1);

                /*
                //2016.8.25补偿(四都变)[[
                float ffc = dDistance/(dLineLength*1.2);
                if(ffc > 1)
                    ffc = 1;
                float ffb = 1;
                if(dFactor < 1)
                    ffb = ffc*(1-dFactor);
                else
                    ffb = ffc*0.28;

                dDistance *= (1-ffb);
                //]]
                */

                //++修正高阻接地尾端[
                /*
                float fVal = dDistance/dLineLength;
                if(fVal > fXiuzhenParam)
                {
                    float fxz = 1.09+fRandm(1000)/10.;
                    dDistance *= fxz;
                    if(dDistance > dLineLength)
                    {
                        fxz = 0.99+fRandm(1000)/100.;
                        dDistance = dLineLength*fxz;
                    }
                }
                */
                //]

                //2020-10-13 超出范围强制修正（故障）[[
                if(bMFault)
                {
                    if((dx>fLineX)||(dx<0))
                    {
                        double dfc = 0.99+fRandm(1000)/100.;
                        dx = fLineX*dfc;
                        dr = fLineR*dfc;
                    }
                }
                //]]


                a_pLineInfo->m_dDistanceII = dDistance;
            }
        }
        //]]
    }//if(bFault)
    if((bReFault)&&((dFaultDistance>=-5)&&(dFaultDistance<=dLineLength*1.4)))
    {
        float dlasttime = (float)((m_pCmtd->m_pSampleTime[nEndFault_2] - m_pCmtd->m_pSampleTime[nStartFault_2])/1000.);
        int ndetpos = (int)(0.25*20*nabSample/20);	//1/4周波
        int ncalpos = ndetpos;							//计算开始位置,默认相对于突变点1/4周波
//        float dr = 0.0;	//短路电阻
//        float dx = 0.0;	//短路电抗
//        bool bSucess = false;
        if(dlasttime >= 55)	////持续时间大于等于3周波就从3/4周波处计算阻抗??
        {
            ncalpos *= 3;	//3/4周波
            ncalpos += nStartFault_2;
        }
        else
        {
            ncalpos += nStartFault_2;
        }
        a_pLineInfo->m_bReFault = true;
        float dTimeDecrease = Dist_CalDeltaT(pIa+ncalpos,pIb+ncalpos,pIc+ncalpos,20,nReFaultPharse);
        a_pLineInfo->m_nFaultType_ReF = nReFaultPharse;
        a_pLineInfo->m_dDeltaT_ReF = dTimeDecrease;
        a_pLineInfo->m_nStartPoint_ReF = nStartFault_2;
        a_pLineInfo->m_nEndPoint_ReF = nEndFault_2;
//        qDebug("再次故障开始时间: %g(毫秒),故障结束时间: %g(毫秒),衰减时间常数: %g(毫秒),距离:%g(公里)\n",dstart,dend,dTimeDecrease,dDistance);

        int nseg = m_pCmtd->GetCurSeg(nStartFault_2);
        int nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
        int ncal = 0;
        //开始前一周波数据
        ncal = nStartFault_2-nWavePoints;
        if(ncal < m_pCmtd->m_pSegment[nseg].m_nStartPos/*+m_pCmtd->m_pSegment[nseg].m_nCount*/)
        {
            ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos/*+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints*/;
        }
        a_pLineInfo->m_pVolRms_ReF_After[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_After[0],1);
        m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_ReF_After[0]);
        a_pLineInfo->m_pVolRms_ReF_After[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_After[1],1);
        m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_ReF_After[1]);
        a_pLineInfo->m_pVolRms_ReF_After[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_After[2],1);
        m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_ReF_After[2]);
        if(pUn != NULL)
            a_pLineInfo->m_pVolRms_ReF_After[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_After[3],1);
        a_pLineInfo->m_pVolMax_ReF_After[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
        a_pLineInfo->m_pVolMax_ReF_After[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
        a_pLineInfo->m_pVolMax_ReF_After[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
        if(pUn != NULL)
            a_pLineInfo->m_pVolMax_ReF_After[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
        a_pLineInfo->m_pInfRms_ReF_After[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_After[0],1);
        m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_ReF_After[0]);
        a_pLineInfo->m_pInfRms_ReF_After[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_After[1],1);
        m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_ReF_After[1]);
        a_pLineInfo->m_pInfRms_ReF_After[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_After[2],1);
        m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_ReF_After[2]);
        a_pLineInfo->m_pInfRms_ReF_After[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_After[3],1);
        a_pLineInfo->m_pInfMax_ReF_After[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_After[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_After[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_After[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
        //故障后第一周波(电压电流有效值、峰值等)
        ncal += nWavePoints;
        if(ncal+nWavePoints > m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount)
        {
            ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints;
        }
        a_pLineInfo->m_pVolRms_ReF_Over[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_Over[0],1);
        m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_ReF_Over[0]);
        a_pLineInfo->m_pVolRms_ReF_Over[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_Over[1],1);
        m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_ReF_Over[1]);
        a_pLineInfo->m_pVolRms_ReF_Over[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_Over[2],1);
        m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_ReF_Over[2]);
        if(pUn != NULL)
            a_pLineInfo->m_pVolRms_ReF_Over[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_Over[3],1);
        a_pLineInfo->m_pVolMax_ReF_Over[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
        a_pLineInfo->m_pVolMax_ReF_Over[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
        a_pLineInfo->m_pVolMax_ReF_Over[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
        if(pUn != NULL)
            a_pLineInfo->m_pVolMax_ReF_Over[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
        a_pLineInfo->m_pInfRms_ReF_Over[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_Over[0],1);
        m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_ReF_Over[0]);
        a_pLineInfo->m_pInfRms_ReF_Over[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_Over[1],1);
        m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_ReF_Over[1]);
        a_pLineInfo->m_pInfRms_ReF_Over[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_Over[2],1);
        m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_ReF_Over[2]);
        a_pLineInfo->m_pInfRms_ReF_Over[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_Over[3],1);
        a_pLineInfo->m_pInfMax_ReF_Over[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_Over[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_Over[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_Over[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
    }

    delete []pIn_ex;
    if(bAllocIa)
    {
        delete []pIa;
    }
    if(bAllocIb)
    {
        delete []pIb;
    }
    if(bAllocIc)
    {
        delete []pIc;
    }
    delete []arFaultList;
    if(bFault)
    {
        return true;
    }

    return false;
}

void CGenerateReport::GetFaultValue_Trans(tagTransInfo* a_pTransInfo, CEleTrans* a_pEleTrans, int a_nPos1, int a_nPos2, int a_nPos3, int a_nWavePoints)
{
    float* pUa[4] = {NULL};
    float* pUb[4] = {NULL};
    float* pUc[4] = {NULL};
    float* pU0[4] = {NULL};
    float* pIa[4] = {NULL};
    float* pIb[4] = {NULL};
    float* pIc[4] = {NULL};
    float* pI0[4] = {NULL};
    int i = 0;

    for(i=0; i<4; i++)
    {
        pUa[i] = new float[m_pCmtd->m_nTotalPoints+100];
        pUb[i] = new float[m_pCmtd->m_nTotalPoints+100];
        pUc[i] = new float[m_pCmtd->m_nTotalPoints+100];
        pU0[i] = new float[m_pCmtd->m_nTotalPoints+100];
        pIa[i] = new float[m_pCmtd->m_nTotalPoints+100];
        pIb[i] = new float[m_pCmtd->m_nTotalPoints+100];
        pIc[i] = new float[m_pCmtd->m_nTotalPoints+100];
        pI0[i] = new float[m_pCmtd->m_nTotalPoints+100];
        for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
        {
            pUa[i][n] = 0;
            pUb[i][n] = 0;
            pUc[i][n] = 0;
            pU0[i][n] = 0;
            pIa[i][n] = 0;
            pIb[i][n] = 0;
            pIc[i][n] = 0;
            pI0[i][n] = 0;
        }
    }


//    int i = a_nTransNo;
//    int nIndex = a_nIndex;
    int nCalposBefore = a_nPos1;
    int nCalposAfter = a_nPos2;
    int nCalposOver = a_nPos3;
    int nWavePoints = a_nWavePoints;
    const int nCount = a_pEleTrans->m_nLineCount;
    const float depslon = (float)(0.001);
    //I侧数据[[
    if(a_pEleTrans->m_pLine[0])
    {
        if(a_pEleTrans->m_pLine[0]->m_pBus)
        {
            if(a_pEleTrans->m_pLine[0]->m_pBus->m_pAChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pUa[0][n] = a_pEleTrans->m_pLine[0]->m_pBus->m_pAChanel->m_pData[n];
                }
            }
            if(a_pEleTrans->m_pLine[0]->m_pBus->m_pBChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pUb[0][n] = a_pEleTrans->m_pLine[0]->m_pBus->m_pBChanel->m_pData[n];
                }
            }
            if(a_pEleTrans->m_pLine[0]->m_pBus->m_pCChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pUc[0][n] = a_pEleTrans->m_pLine[0]->m_pBus->m_pCChanel->m_pData[n];
                }
            }
            if(a_pEleTrans->m_pLine[0]->m_pBus->m_pNChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pU0[0][n] = a_pEleTrans->m_pLine[0]->m_pBus->m_pNChanel->m_pData[n];
                }
            }
        }
        if(a_pEleTrans->m_pLine[0]->m_pAChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pIa[0][n] = a_pEleTrans->m_pLine[0]->m_pAChanel->m_pData[n];
            }
        }
        if(a_pEleTrans->m_pLine[0]->m_pBChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pIb[0][n] = a_pEleTrans->m_pLine[0]->m_pBChanel->m_pData[n];
            }
        }
        if(a_pEleTrans->m_pLine[0]->m_pCChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pIc[0][n] = a_pEleTrans->m_pLine[0]->m_pCChanel->m_pData[n];
            }
        }
        if(a_pEleTrans->m_pLine[0]->m_pNChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pI0[0][n] = a_pEleTrans->m_pLine[0]->m_pNChanel->m_pData[n];
            }
        }
    }
    //]]I侧数据

    //II侧数据[[
    if(a_pEleTrans->m_pLine[1])
    {
        if(a_pEleTrans->m_pLine[1]->m_pBus)
        {
            if(a_pEleTrans->m_pLine[1]->m_pBus->m_pAChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pUa[1][n] = a_pEleTrans->m_pLine[1]->m_pBus->m_pAChanel->m_pData[n];
                }
            }
            if(a_pEleTrans->m_pLine[1]->m_pBus->m_pBChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pUb[1][n] = a_pEleTrans->m_pLine[1]->m_pBus->m_pBChanel->m_pData[n];
                }
            }
            if(a_pEleTrans->m_pLine[1]->m_pBus->m_pCChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pUc[1][n] = a_pEleTrans->m_pLine[1]->m_pBus->m_pCChanel->m_pData[n];
                }
            }
            if(a_pEleTrans->m_pLine[1]->m_pBus->m_pNChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pU0[1][n] = a_pEleTrans->m_pLine[1]->m_pBus->m_pNChanel->m_pData[n];
                }
            }
        }
        if(a_pEleTrans->m_pLine[1]->m_pAChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pIa[1][n] = a_pEleTrans->m_pLine[1]->m_pAChanel->m_pData[n];
            }
        }
        if(a_pEleTrans->m_pLine[1]->m_pBChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pIb[1][n] = a_pEleTrans->m_pLine[1]->m_pBChanel->m_pData[n];
            }
        }
        if(a_pEleTrans->m_pLine[1]->m_pCChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pIc[1][n] = a_pEleTrans->m_pLine[1]->m_pCChanel->m_pData[n];
            }
        }
        if(a_pEleTrans->m_pLine[1]->m_pNChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pI0[1][n] = a_pEleTrans->m_pLine[1]->m_pNChanel->m_pData[n];
            }
        }
    }
    //]]II侧数据

    //III侧数据[[
    if(a_pEleTrans->m_pLine[2])
    {
        if(a_pEleTrans->m_pLine[2]->m_pBus)
        {
            if(a_pEleTrans->m_pLine[2]->m_pBus->m_pAChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pUa[2][n] = a_pEleTrans->m_pLine[2]->m_pBus->m_pAChanel->m_pData[n];
                }
            }
            if(a_pEleTrans->m_pLine[2]->m_pBus->m_pBChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pUb[2][n] = a_pEleTrans->m_pLine[2]->m_pBus->m_pBChanel->m_pData[n];
                }
            }
            if(a_pEleTrans->m_pLine[2]->m_pBus->m_pCChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pUc[2][n] = a_pEleTrans->m_pLine[2]->m_pBus->m_pCChanel->m_pData[n];
                }
            }
            if(a_pEleTrans->m_pLine[2]->m_pBus->m_pNChanel)
            {
                for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
                {
                    pU0[2][n] = a_pEleTrans->m_pLine[2]->m_pBus->m_pNChanel->m_pData[n];
                }
            }
        }
        if(a_pEleTrans->m_pLine[2]->m_pAChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pIa[2][n] = a_pEleTrans->m_pLine[2]->m_pAChanel->m_pData[n];
            }
        }
        if(a_pEleTrans->m_pLine[2]->m_pBChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pIb[2][n] = a_pEleTrans->m_pLine[2]->m_pBChanel->m_pData[n];
            }
        }
        if(a_pEleTrans->m_pLine[2]->m_pCChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pIc[2][n] = a_pEleTrans->m_pLine[2]->m_pCChanel->m_pData[n];
            }
        }
        if(a_pEleTrans->m_pLine[2]->m_pNChanel)
        {
            for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
            {
                pI0[2][n] = a_pEleTrans->m_pLine[2]->m_pNChanel->m_pData[n];
            }
        }
    }
    //]]III侧数据

    //IV侧数据
    if(nCount > 3)
    {
        pUa[3] = a_pEleTrans->m_pLine[3]->m_pBus->m_pAChanel->m_pData.data();
        pUb[3] = a_pEleTrans->m_pLine[3]->m_pBus->m_pBChanel->m_pData.data();
        pUc[3] = a_pEleTrans->m_pLine[3]->m_pBus->m_pCChanel->m_pData.data();
        if(a_pEleTrans->m_pLine[3]->m_pBus->m_pNChanel != NULL)
            pU0[3] = a_pEleTrans->m_pLine[3]->m_pBus->m_pNChanel->m_pData.data();
        pIa[3] = a_pEleTrans->m_pLine[3]->m_pAChanel->m_pData.data();
        pIb[3] = a_pEleTrans->m_pLine[3]->m_pBChanel->m_pData.data();
        pIc[3] = a_pEleTrans->m_pLine[3]->m_pCChanel->m_pData.data();
        if(a_pEleTrans->m_pLine[3]->m_pNChanel != NULL)
            pI0[3] = a_pEleTrans->m_pLine[3]->m_pNChanel->m_pData.data();
    }
    //---------------------------------------------------------------------------------------------------
    //计算启动前一周波后两周波的电压、电流值,并统计最大故障电流和最低故障电压
    //---------------------------------------------------------------------------------------------------
    CEleLine* pLine = NULL;
    unsigned short usUID[3] = {0};
    unsigned short usIID[3] = {0};
    for(int n=0; n<nCount; n++)
    {
        if(n == 0)
            pLine = a_pEleTrans->m_pLine[0];
        else if(n == 1)
            pLine = a_pEleTrans->m_pLine[1];
        else if(n == 2)
            pLine = a_pEleTrans->m_pLine[2];
        else if(n == 3)
            pLine = a_pEleTrans->m_pLine[3];
        if(pLine == NULL)
        {
            continue;
        }
        if(pLine->m_pBus)
        {
            if(pLine->m_pBus->m_pAChanel)
                usUID[0] = pLine->m_pBus->m_pAChanel->m_wID;
            if(pLine->m_pBus->m_pBChanel)
                usUID[1] = pLine->m_pBus->m_pBChanel->m_wID;
            if(pLine->m_pBus->m_pCChanel)
                usUID[2] = pLine->m_pBus->m_pCChanel->m_wID;
        }
        usIID[0] = pLine->m_pAChanel->m_wID;
        usIID[1] = pLine->m_pBChanel->m_wID;
        usIID[2] = pLine->m_pCChanel->m_wID;
        //计算(前一周波)========================================================================================
        a_pTransInfo->m_pLine[n].m_pVolRms_Before[0] = m_wyCal.Cal_Rms_Result(pUa[n],nCalposBefore,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_Before[0]);
        m_pCmtd->ParamPhase(usUID[0],a_pTransInfo->m_pLine[n].m_pVolAng_Before[0]);
        a_pTransInfo->m_pLine[n].m_pVolRms_Before[1] = m_wyCal.Cal_Rms_Result(pUb[n],nCalposBefore,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_Before[1]);
        m_pCmtd->ParamPhase(usUID[1],a_pTransInfo->m_pLine[n].m_pVolAng_Before[1]);
        a_pTransInfo->m_pLine[n].m_pVolRms_Before[2] = m_wyCal.Cal_Rms_Result(pUc[n],nCalposBefore,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_Before[2]);
        m_pCmtd->ParamPhase(usUID[2],a_pTransInfo->m_pLine[n].m_pVolAng_Before[2]);
        if(pU0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pVolRms_Before[3] = m_wyCal.Cal_Rms_Result(pU0[n],nCalposBefore,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_Before[3]);
        a_pTransInfo->m_pLine[n].m_pVolMax_Before[0] = m_wyCal.GetMaxValue(pUa[n],nCalposBefore,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pVolMax_Before[1] = m_wyCal.GetMaxValue(pUb[n],nCalposBefore,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pVolMax_Before[2] = m_wyCal.GetMaxValue(pUc[n],nCalposBefore,nWavePoints);
        if(pU0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pVolMax_Before[3] = m_wyCal.GetMaxValue(pU0[n],nCalposBefore,nWavePoints);
        m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa[n],pUb[n],pUc[n],nCalposBefore,nWavePoints,0,a_pTransInfo->m_pLine[n].m_dU0_Before,a_pTransInfo->m_pLine[n].m_dU1_Before,a_pTransInfo->m_pLine[n].m_dU2_Before);
        a_pTransInfo->m_pLine[n].m_pInfRms_Before[0] = m_wyCal.Cal_Rms_Result(pIa[n],nCalposBefore,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_Before[0]);
        m_pCmtd->ParamPhase(usIID[0],a_pTransInfo->m_pLine[n].m_pInfAng_Before[0]);
        a_pTransInfo->m_pLine[n].m_pInfRms_Before[1] = m_wyCal.Cal_Rms_Result(pIb[n],nCalposBefore,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_Before[1]);
        m_pCmtd->ParamPhase(usIID[1],a_pTransInfo->m_pLine[n].m_pInfAng_Before[1]);
        a_pTransInfo->m_pLine[n].m_pInfRms_Before[2] = m_wyCal.Cal_Rms_Result(pIc[n],nCalposBefore,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_Before[2]);
        m_pCmtd->ParamPhase(usIID[2],a_pTransInfo->m_pLine[n].m_pInfAng_Before[2]);
        if(pI0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pInfRms_Before[3] = m_wyCal.Cal_Rms_Result(pI0[n],nCalposBefore,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_Before[3]);
        a_pTransInfo->m_pLine[n].m_pInfMax_Before[0] = m_wyCal.GetMaxValue(pIa[n],nCalposBefore,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pInfMax_Before[1] = m_wyCal.GetMaxValue(pIb[n],nCalposBefore,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pInfMax_Before[2] = m_wyCal.GetMaxValue(pIc[n],nCalposBefore,nWavePoints);
        if(pI0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pInfMax_Before[3] = m_wyCal.GetMaxValue(pI0[n],nCalposBefore,nWavePoints);
        m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa[n],pIb[n],pIc[n],nCalposBefore,nWavePoints,0,a_pTransInfo->m_pLine[n].m_dI0_Before,a_pTransInfo->m_pLine[n].m_dI1_Before,a_pTransInfo->m_pLine[n].m_dI2_Before);
        //统计最大电流
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two = a_pTransInfo->m_pLine[n].m_pInfRms_Before[0];
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two = fmax(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two,a_pTransInfo->m_pLine[n].m_pInfRms_Before[1]);
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two = fmax(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two,a_pTransInfo->m_pLine[n].m_pInfRms_Before[2]);
        if(fabs(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two-a_pTransInfo->m_pLine[n].m_pInfRms_Before[0]) < depslon)
        {
            strcpy(a_pTransInfo->m_pLine[n].m_chInfChanel,pLine->m_pAChanel->m_chName);
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two-a_pTransInfo->m_pLine[n].m_pInfRms_Before[1]) < depslon)
        {
            strcpy(a_pTransInfo->m_pLine[n].m_chInfChanel,pLine->m_pBChanel->m_chName);
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two-a_pTransInfo->m_pLine[n].m_pInfRms_Before[2]) < depslon)
        {
            strcpy(a_pTransInfo->m_pLine[n].m_chInfChanel,pLine->m_pCChanel->m_chName);
        }
        //统计最低电压
        a_pTransInfo->m_pLine[n].m_dMinFaultVol_two = a_pTransInfo->m_pLine[n].m_pVolRms_Before[0];
        a_pTransInfo->m_pLine[n].m_dMinFaultVol_two = fmin(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two,a_pTransInfo->m_pLine[n].m_pVolRms_Before[1]);
        a_pTransInfo->m_pLine[n].m_dMinFaultVol_two = fmin(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two,a_pTransInfo->m_pLine[n].m_pVolRms_Before[2]);
        if(fabs(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two-a_pTransInfo->m_pLine[n].m_pVolRms_Before[0]) < depslon)
        {
            if(pLine->m_pBus)
            {
                if(pLine->m_pBus->m_pAChanel)
                    strcpy(a_pTransInfo->m_pLine[n].m_chVolChanel,pLine->m_pBus->m_pAChanel->m_chName);
            }

        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two-a_pTransInfo->m_pLine[n].m_pVolRms_Before[1]) < depslon)
        {
            if(pLine->m_pBus)
            {
                if(pLine->m_pBus->m_pBChanel)
                    strcpy(a_pTransInfo->m_pLine[n].m_chVolChanel,pLine->m_pBus->m_pBChanel->m_chName);
            }
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two-a_pTransInfo->m_pLine[n].m_pVolRms_Before[2]) < depslon)
        {
            if(pLine->m_pBus)
            {
                if(pLine->m_pBus->m_pCChanel)
                    strcpy(a_pTransInfo->m_pLine[n].m_chVolChanel,pLine->m_pBus->m_pCChanel->m_chName);
            }
        }

        //========================================================================================================
        //计算(后一周波)
        a_pTransInfo->m_pLine[n].m_pVolRms_After[0] = m_wyCal.Cal_Rms_Result(pUa[n],nCalposAfter,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_After[0]);
        m_pCmtd->ParamPhase(usUID[0],a_pTransInfo->m_pLine[n].m_pVolAng_After[0]);
        a_pTransInfo->m_pLine[n].m_pVolRms_After[1] = m_wyCal.Cal_Rms_Result(pUb[n],nCalposAfter,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_After[1]);
        m_pCmtd->ParamPhase(usUID[1],a_pTransInfo->m_pLine[n].m_pVolAng_After[1]);
        a_pTransInfo->m_pLine[n].m_pVolRms_After[2] = m_wyCal.Cal_Rms_Result(pUc[n],nCalposAfter,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_After[2]);
        m_pCmtd->ParamPhase(usUID[2],a_pTransInfo->m_pLine[n].m_pVolAng_After[2]);
        if(pU0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pVolRms_After[3] = m_wyCal.Cal_Rms_Result(pU0[n],nCalposAfter,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_After[3]);
        a_pTransInfo->m_pLine[n].m_pVolMax_After[0] = m_wyCal.GetMaxValue(pUa[n],nCalposAfter,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pVolMax_After[1] = m_wyCal.GetMaxValue(pUb[n],nCalposAfter,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pVolMax_After[2] = m_wyCal.GetMaxValue(pUc[n],nCalposAfter,nWavePoints);
        if(pU0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pVolMax_After[3] = m_wyCal.GetMaxValue(pU0[n],nCalposAfter,nWavePoints);
        m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa[n],pUb[n],pUc[n],nCalposAfter,nWavePoints,0,a_pTransInfo->m_pLine[n].m_dU0_After,a_pTransInfo->m_pLine[n].m_dU1_After,a_pTransInfo->m_pLine[n].m_dU2_After);
        a_pTransInfo->m_pLine[n].m_pInfRms_After[0] = m_wyCal.Cal_Rms_Result(pIa[n],nCalposAfter,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_After[0]);
        m_pCmtd->ParamPhase(usIID[0],a_pTransInfo->m_pLine[n].m_pInfAng_After[0]);
        a_pTransInfo->m_pLine[n].m_pInfRms_After[1] = m_wyCal.Cal_Rms_Result(pIb[n],nCalposAfter,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_After[1]);
        m_pCmtd->ParamPhase(usIID[1],a_pTransInfo->m_pLine[n].m_pInfAng_After[1]);
        a_pTransInfo->m_pLine[n].m_pInfRms_After[2] = m_wyCal.Cal_Rms_Result(pIc[n],nCalposAfter,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_After[2]);
        m_pCmtd->ParamPhase(usIID[2],a_pTransInfo->m_pLine[n].m_pInfAng_After[2]);
        if(pI0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pInfRms_After[3] = m_wyCal.Cal_Rms_Result(pI0[n],nCalposAfter,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_After[3]);
        a_pTransInfo->m_pLine[n].m_pInfMax_After[0] = m_wyCal.GetMaxValue(pIa[n],nCalposAfter,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pInfMax_After[1] = m_wyCal.GetMaxValue(pIb[n],nCalposAfter,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pInfMax_After[2] = m_wyCal.GetMaxValue(pIc[n],nCalposAfter,nWavePoints);
        if(pI0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pInfMax_After[3] = m_wyCal.GetMaxValue(pI0[n],nCalposAfter,nWavePoints);
        m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa[n],pIb[n],pIc[n],nCalposAfter,nWavePoints,0,a_pTransInfo->m_pLine[n].m_dI0_After,a_pTransInfo->m_pLine[n].m_dI1_After,a_pTransInfo->m_pLine[n].m_dI2_After);
        //统计最大电流
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two = fmax(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two,a_pTransInfo->m_pLine[n].m_pInfRms_After[0]);
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two = fmax(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two,a_pTransInfo->m_pLine[n].m_pInfRms_After[1]);
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two = fmax(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two,a_pTransInfo->m_pLine[n].m_pInfRms_After[2]);
        if(fabs(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two-a_pTransInfo->m_pLine[n].m_pInfRms_After[0]) < depslon)
        {
            if(pLine->m_pAChanel)
                strcpy(a_pTransInfo->m_pLine[n].m_chInfChanel,pLine->m_pAChanel->m_chName);
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two-a_pTransInfo->m_pLine[n].m_pInfRms_After[1]) < depslon)
        {
            if(pLine->m_pBChanel)
                strcpy(a_pTransInfo->m_pLine[n].m_chInfChanel,pLine->m_pBChanel->m_chName);
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two-a_pTransInfo->m_pLine[n].m_pInfRms_After[2]) < depslon)
        {
            if(pLine->m_pCChanel)
                strcpy(a_pTransInfo->m_pLine[n].m_chInfChanel,pLine->m_pCChanel->m_chName);
        }
        //统计最低电压
        a_pTransInfo->m_pLine[n].m_dMinFaultVol_two = fmin(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two,a_pTransInfo->m_pLine[n].m_pVolRms_After[0]);
        a_pTransInfo->m_pLine[n].m_dMinFaultVol_two = fmin(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two,a_pTransInfo->m_pLine[n].m_pVolRms_After[1]);
        a_pTransInfo->m_pLine[n].m_dMinFaultVol_two = fmin(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two,a_pTransInfo->m_pLine[n].m_pVolRms_After[2]);
        if(fabs(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two-a_pTransInfo->m_pLine[n].m_pVolRms_After[0]) < depslon)
        {
            if(pLine->m_pBus)
            {
                if(pLine->m_pBus->m_pAChanel)
                    strcpy(a_pTransInfo->m_pLine[n].m_chVolChanel,pLine->m_pBus->m_pAChanel->m_chName);
            }
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two-a_pTransInfo->m_pLine[n].m_pVolRms_After[1]) < depslon)
        {
            if(pLine->m_pBus)
            {
                if(pLine->m_pBus->m_pBChanel)
                    strcpy(a_pTransInfo->m_pLine[n].m_chVolChanel,pLine->m_pBus->m_pBChanel->m_chName);
            }
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two-a_pTransInfo->m_pLine[n].m_pVolRms_After[2]) < depslon)
        {
            if(pLine->m_pBus)
            {
                if(pLine->m_pBus->m_pCChanel)
                    strcpy(a_pTransInfo->m_pLine[n].m_chVolChanel,pLine->m_pBus->m_pCChanel->m_chName);
            }
        }

        //计算(后两周波)====================================
        a_pTransInfo->m_pLine[n].m_pVolRms_Over[0] = m_wyCal.Cal_Rms_Result(pUa[n],nCalposOver,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_Over[0]);
        m_pCmtd->ParamPhase(usUID[0],a_pTransInfo->m_pLine[n].m_pVolAng_Over[0]);
        a_pTransInfo->m_pLine[n].m_pVolRms_Over[1] = m_wyCal.Cal_Rms_Result(pUb[n],nCalposOver,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_Over[1]);
        m_pCmtd->ParamPhase(usUID[1],a_pTransInfo->m_pLine[n].m_pVolAng_Over[1]);
        a_pTransInfo->m_pLine[n].m_pVolRms_Over[2] = m_wyCal.Cal_Rms_Result(pUc[n],nCalposOver,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_Over[2]);
        m_pCmtd->ParamPhase(usUID[2],a_pTransInfo->m_pLine[n].m_pVolAng_Over[2]);
        if(pU0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pVolRms_Over[3] = m_wyCal.Cal_Rms_Result(pU0[n],nCalposOver,nWavePoints,a_pTransInfo->m_pLine[n].m_pVolAng_Over[3]);
        a_pTransInfo->m_pLine[n].m_pVolMax_Over[0] = m_wyCal.GetMaxValue(pUa[n],nCalposOver,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pVolMax_Over[1] = m_wyCal.GetMaxValue(pUb[n],nCalposOver,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pVolMax_Over[2] = m_wyCal.GetMaxValue(pUc[n],nCalposOver,nWavePoints);
        if(pU0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pVolMax_Over[3] = m_wyCal.GetMaxValue(pU0[n],nCalposOver,nWavePoints);
        m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa[n],pUb[n],pUc[n],nCalposOver,nWavePoints,0,a_pTransInfo->m_pLine[n].m_dU0_Over,a_pTransInfo->m_pLine[n].m_dU1_Over,a_pTransInfo->m_pLine[n].m_dU2_Over);
        a_pTransInfo->m_pLine[n].m_pInfRms_Over[0] = m_wyCal.Cal_Rms_Result(pIa[n],nCalposOver,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_Over[0]);
        m_pCmtd->ParamPhase(usIID[0],a_pTransInfo->m_pLine[n].m_pInfAng_Over[0]);
        a_pTransInfo->m_pLine[n].m_pInfRms_Over[1] = m_wyCal.Cal_Rms_Result(pIb[n],nCalposOver,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_Over[1]);
        m_pCmtd->ParamPhase(usIID[1],a_pTransInfo->m_pLine[n].m_pInfAng_Over[1]);
        a_pTransInfo->m_pLine[n].m_pInfRms_Over[2] = m_wyCal.Cal_Rms_Result(pIc[n],nCalposOver,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_Over[2]);
        m_pCmtd->ParamPhase(usIID[2],a_pTransInfo->m_pLine[n].m_pInfAng_Over[2]);
        if(pI0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pInfRms_Over[3] = m_wyCal.Cal_Rms_Result(pI0[n],nCalposOver,nWavePoints,a_pTransInfo->m_pLine[n].m_pInfAng_Over[3]);
        a_pTransInfo->m_pLine[n].m_pInfMax_Over[0] = m_wyCal.GetMaxValue(pIa[n],nCalposOver,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pInfMax_Over[1] = m_wyCal.GetMaxValue(pIb[n],nCalposOver,nWavePoints);
        a_pTransInfo->m_pLine[n].m_pInfMax_Over[2] = m_wyCal.GetMaxValue(pIc[n],nCalposOver,nWavePoints);
        if(pI0[n] != NULL)
            a_pTransInfo->m_pLine[n].m_pInfMax_Over[3] = m_wyCal.GetMaxValue(pI0[n],nCalposOver,nWavePoints);
        m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa[n],pIb[n],pIc[n],nCalposOver,nWavePoints,0,a_pTransInfo->m_pLine[n].m_dI0_Over,a_pTransInfo->m_pLine[n].m_dI1_Over,a_pTransInfo->m_pLine[n].m_dI2_Over);

        //统计最大电流
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two = fmax(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two,a_pTransInfo->m_pLine[n].m_pInfRms_Over[0]);
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two = fmax(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two,a_pTransInfo->m_pLine[n].m_pInfRms_Over[1]);
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two = fmax(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two,a_pTransInfo->m_pLine[n].m_pInfRms_Over[2]);
        if(fabs(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two-a_pTransInfo->m_pLine[n].m_pInfRms_Over[0]) < depslon)
        {
            if(pLine->m_pAChanel)
                strcpy(a_pTransInfo->m_pLine[n].m_chInfChanel,pLine->m_pAChanel->m_chName);
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two-a_pTransInfo->m_pLine[n].m_pInfRms_Over[1]) < depslon)
        {
            if(pLine->m_pBChanel)
                strcpy(a_pTransInfo->m_pLine[n].m_chInfChanel,pLine->m_pBChanel->m_chName);
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two-a_pTransInfo->m_pLine[n].m_pInfRms_Over[2]) < depslon)
        {
            if(pLine->m_pCChanel)
                strcpy(a_pTransInfo->m_pLine[n].m_chInfChanel,pLine->m_pCChanel->m_chName);
        }
        //统计最低电压
        a_pTransInfo->m_pLine[n].m_dMinFaultVol_two = fmin(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two,a_pTransInfo->m_pLine[n].m_pVolRms_Over[0]);
        a_pTransInfo->m_pLine[n].m_dMinFaultVol_two = fmin(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two,a_pTransInfo->m_pLine[n].m_pVolRms_Over[1]);
        a_pTransInfo->m_pLine[n].m_dMinFaultVol_two = fmin(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two,a_pTransInfo->m_pLine[n].m_pVolRms_Over[2]);
        if(fabs(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two-a_pTransInfo->m_pLine[n].m_pVolRms_Over[0]) < depslon)
        {
            if(pLine->m_pBus)
            {
                if(pLine->m_pBus->m_pAChanel)
                    strcpy(a_pTransInfo->m_pLine[n].m_chVolChanel,pLine->m_pBus->m_pAChanel->m_chName);
            }
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two-a_pTransInfo->m_pLine[n].m_pVolRms_Over[1]) < depslon)
        {
            if(pLine->m_pBus)
            {
                if(pLine->m_pBus->m_pBChanel)
                    strcpy(a_pTransInfo->m_pLine[n].m_chVolChanel,pLine->m_pBus->m_pBChanel->m_chName);
            }
        }
        else if(fabs(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two-a_pTransInfo->m_pLine[n].m_pVolRms_Over[2]) < depslon)
        {
            if(pLine->m_pBus)
            {
                if(pLine->m_pBus->m_pCChanel)
                    strcpy(a_pTransInfo->m_pLine[n].m_chVolChanel,pLine->m_pBus->m_pCChanel->m_chName);
            }
        }
        //获取一次值
        a_pTransInfo->m_pLine[n].m_dMaxFaultInf_one = (float)(a_pTransInfo->m_pLine[n].m_dMaxFaultInf_two * a_pEleTrans->m_pLine[n]->m_dCT/1000.0);
        if(a_pEleTrans->m_pLine[n]->m_pBus)
            a_pTransInfo->m_pLine[n].m_dMinFaultVol_one = (float)(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two * a_pEleTrans->m_pLine[n]->m_pBus->m_dVoltage*10.0/1000.0);
        else
            a_pTransInfo->m_pLine[n].m_dMinFaultVol_one = (float)(a_pTransInfo->m_pLine[n].m_dMinFaultVol_two * 220.0*10.0/1000.0);
    }

    //2021-3-29 清理内存
    //[[
    for(i=0; i<4; i++)
    {
        delete []pUa[i];
        delete []pUb[i];
        delete []pUc[i];
        delete []pU0[i];
        delete []pIa[i];
        delete []pIb[i];
        delete []pIc[i];
        delete []pI0[i];
    }
    //]]
}

void CGenerateReport::GetLineValue_Cyc(tagLineInfo* a_pLineInfo, CEleLine* a_pEleLine)
{
    const float depslon = (float)(0.001);
    float *pUa=NULL,*pUb=NULL,*pUc=NULL,*pUn=NULL,*pIa=NULL,*pIb=NULL,*pIc=NULL,*pIn=NULL;
    unsigned short usUID[3] = {0};
    unsigned short usIID[3] = {0};
    if(a_pEleLine->m_pBus == NULL)
    {
        return;
    }
    if(a_pEleLine->m_pBus->m_pAChanel == NULL)
        return;
    if(a_pEleLine->m_pBus->m_pBChanel == NULL)
        return;
    if(a_pEleLine->m_pBus->m_pCChanel == NULL)
        return;
    if(a_pEleLine->m_pBus->m_pNChanel == NULL)
        return;
    pUa = a_pEleLine->m_pBus->m_pAChanel->m_pData.data();
    usUID[0] = a_pEleLine->m_pBus->m_pAChanel->m_wID;
    pUb = a_pEleLine->m_pBus->m_pBChanel->m_pData.data();
    usUID[1] = a_pEleLine->m_pBus->m_pBChanel->m_wID;
    pUc = a_pEleLine->m_pBus->m_pCChanel->m_pData.data();
    usUID[2] = a_pEleLine->m_pBus->m_pCChanel->m_wID;
    if(a_pEleLine->m_pBus->m_pNChanel != NULL)
        pUn = a_pEleLine->m_pBus->m_pNChanel->m_pData.data();
    if(a_pEleLine->m_pAChanel != NULL)
    {
        pIa = a_pEleLine->m_pAChanel->m_pData.data();
        usIID[0] = a_pEleLine->m_pAChanel->m_wID;
    }
    if(a_pEleLine->m_pBChanel != NULL)
    {
        pIb = a_pEleLine->m_pBChanel->m_pData.data();
        usIID[1] = a_pEleLine->m_pBChanel->m_wID;
    }
    if(a_pEleLine->m_pCChanel != NULL)
    {
        pIc = a_pEleLine->m_pCChanel->m_pData.data();
        usIID[2] = a_pEleLine->m_pCChanel->m_wID;
    }
    if(a_pEleLine->m_pNChanel != NULL)
        pIn = a_pEleLine->m_pNChanel->m_pData.data();
    //故障开始前一周波(电压电流有效值、峰值等)
    int nWavePoints = m_pCmtd->m_pSegment[0].m_nWavePoints;
    int ncal = a_pLineInfo->m_nStartPoint;
    if(ncal-nWavePoints < m_pCmtd->m_pSegment[0].m_nStartPos)
    {
        ncal = m_pCmtd->m_pSegment[0].m_nStartPos;
    }
    else
    {
        ncal -= nWavePoints;
    }
    int nseg = 0;
    a_pLineInfo->m_pVolRms_Before[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[0],1);
    m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_Before[0]);
    a_pLineInfo->m_pVolRms_Before[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[1],1);
    m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_Before[1]);
    a_pLineInfo->m_pVolRms_Before[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[2],1);
    m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_Before[2]);
    if(pUn != NULL)
        a_pLineInfo->m_pVolRms_Before[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[3],1);
    a_pLineInfo->m_pVolMax_Before[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
    a_pLineInfo->m_pVolMax_Before[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
    a_pLineInfo->m_pVolMax_Before[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
    if(pUn != NULL)
        a_pLineInfo->m_pVolMax_Before[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
    m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa,pUb,pUc,ncal,nWavePoints,0,a_pLineInfo->m_dU0_Before,a_pLineInfo->m_dU1_Before,a_pLineInfo->m_dU2_Before);
    if(pIa != NULL)
    {
        a_pLineInfo->m_pInfRms_Before[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[0],1);
        m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_Before[0]);
    }
    else
        a_pLineInfo->m_pInfRms_Before[0] = 0;
    if(pIb != NULL)
    {
        a_pLineInfo->m_pInfRms_Before[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[1],1);
        m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_Before[1]);
    }
    else
        a_pLineInfo->m_pInfRms_Before[1] = 0;
    if(pIc != NULL)
    {
        a_pLineInfo->m_pInfRms_Before[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[2],1);
        m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_Before[2]);
    }
    else
        a_pLineInfo->m_pInfRms_Before[2] = 0;
    if(pIn != NULL)
        a_pLineInfo->m_pInfRms_Before[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[3],1);
    else
        a_pLineInfo->m_pInfRms_Before[3] = 0;
    if(pIa != NULL)
        a_pLineInfo->m_pInfMax_Before[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
    else
        a_pLineInfo->m_pInfMax_Before[0] = 0;
    if(pIb != NULL)
        a_pLineInfo->m_pInfMax_Before[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
    else
        a_pLineInfo->m_pInfMax_Before[1] = 0;
    if(pIc != NULL)
        a_pLineInfo->m_pInfMax_Before[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
    else
        a_pLineInfo->m_pInfMax_Before[2] = 0;
    if(pIn != NULL)
        a_pLineInfo->m_pInfMax_Before[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
    else
        a_pLineInfo->m_pInfMax_Before[3] = 0;
    if(pIb != NULL)
        m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa,pIb,pIc,ncal,nWavePoints,0,a_pLineInfo->m_dI0_Before,a_pLineInfo->m_dI1_Before,a_pLineInfo->m_dI2_Before);
    //故障开始后一周波(电压电流有效值、峰值等)
    ncal = a_pLineInfo->m_nStartPoint;
    if(ncal+nWavePoints > m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount)
    {
        ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints;
    }
    a_pLineInfo->m_pVolRms_After[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[0],1);
    m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_After[0]);
    a_pLineInfo->m_pVolRms_After[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[1],1);
    m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_After[1]);
    a_pLineInfo->m_pVolRms_After[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[2],1);
    m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_After[2]);
    if(pUn != NULL)
        a_pLineInfo->m_pVolRms_After[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[3],1);
    a_pLineInfo->m_pVolMax_After[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
    a_pLineInfo->m_pVolMax_After[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
    a_pLineInfo->m_pVolMax_After[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
    if(pUn != NULL)
        a_pLineInfo->m_pVolMax_After[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
    m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa,pUb,pUc,ncal,nWavePoints,0,a_pLineInfo->m_dU0_After,a_pLineInfo->m_dU1_After,a_pLineInfo->m_dU2_After);
    if(pIa != NULL)
    {
        a_pLineInfo->m_pInfRms_After[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[0],1);
        m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_After[0]);
    }
    if(pIb != NULL)
    {
        a_pLineInfo->m_pInfRms_After[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[1],1);
        m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_After[1]);
    }
    if(pIc != NULL)
    {
        a_pLineInfo->m_pInfRms_After[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[2],1);
        m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_After[2]);
    }
    if(pIn != NULL)
        a_pLineInfo->m_pInfRms_After[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[3],1);
    a_pLineInfo->m_pInfMax_After[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
    if(pIb != NULL)
        a_pLineInfo->m_pInfMax_After[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
    a_pLineInfo->m_pInfMax_After[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
    if(pIn != NULL)
        a_pLineInfo->m_pInfMax_After[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
    if(pIb != NULL)
        m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa,pIb,pIc,ncal,nWavePoints,0,a_pLineInfo->m_dI0_After,a_pLineInfo->m_dI1_After,a_pLineInfo->m_dI2_After);

    //故障后一周波最大电流
    a_pLineInfo->m_dMaxFaultInf_two = a_pLineInfo->m_pInfRms_After[0];
    a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_After[1]);
    a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_After[2]);
    if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_After[0]) < depslon)
    {
        strcpy(a_pLineInfo->m_chInfChanel,a_pEleLine->m_pAChanel->m_chName);
    }
    else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_After[1]) < depslon)
    {
        strcpy(a_pLineInfo->m_chInfChanel,a_pEleLine->m_pBChanel->m_chName);
    }
    else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_After[2]) < depslon)
    {
        strcpy(a_pLineInfo->m_chInfChanel,a_pEleLine->m_pCChanel->m_chName);
    }
    a_pLineInfo->m_dMinFaultVol_two = a_pLineInfo->m_pVolRms_After[0];
    a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_After[1]);
    a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_After[2]);
    if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_After[0]) < depslon)
    {
        strcpy(a_pLineInfo->m_chVolChanel,a_pEleLine->m_pBus->m_pAChanel->m_chName);
    }
    else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_After[1]) < depslon)
    {
        strcpy(a_pLineInfo->m_chVolChanel,a_pEleLine->m_pBus->m_pBChanel->m_chName);
    }
    else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_After[2]) < depslon)
    {
        strcpy(a_pLineInfo->m_chVolChanel,a_pEleLine->m_pBus->m_pCChanel->m_chName);
    }
    //获取一次值
    a_pLineInfo->m_dMaxFaultInf_one = (float)(a_pLineInfo->m_dMaxFaultInf_two * a_pEleLine->m_dCT/1000.0);
    a_pLineInfo->m_dMinFaultVol_one = (float)(a_pLineInfo->m_dMinFaultVol_two * a_pEleLine->m_pBus->m_dVoltage*10.0/1000.0);

    //故障开始后第二周波(电压电流有效值、峰值等)
    ncal += nWavePoints;
    if(ncal+nWavePoints > m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount)
    {
        ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints;
    }
    a_pLineInfo->m_pVolRms_Over[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[0],1);
    m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_Over[0]);
    a_pLineInfo->m_pVolRms_Over[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[1],1);
    m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_Over[1]);
    a_pLineInfo->m_pVolRms_Over[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[2],1);
    m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_Over[2]);
    if(pUn != NULL)
        a_pLineInfo->m_pVolRms_Over[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[3],1);
    a_pLineInfo->m_pVolMax_Over[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
    a_pLineInfo->m_pVolMax_Over[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
    a_pLineInfo->m_pVolMax_Over[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
    if(pUn != NULL)
        a_pLineInfo->m_pVolMax_Over[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
    m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa,pUb,pUc,ncal,nWavePoints,0,a_pLineInfo->m_dU0_Over,a_pLineInfo->m_dU1_Over,a_pLineInfo->m_dU2_Over);
    if(pIa != NULL)
    {
        a_pLineInfo->m_pInfRms_Over[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[0],1);
        m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_Over[0]);
    }
    if(pIb != NULL)
    {
        a_pLineInfo->m_pInfRms_Over[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[1],1);
        m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_Over[1]);
    }
    if(pIc != NULL)
    {
        a_pLineInfo->m_pInfRms_Over[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[2],1);
        m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_Over[2]);
    }
    if(pIn != NULL)
        a_pLineInfo->m_pInfRms_Over[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[3],1);
    a_pLineInfo->m_pInfMax_Over[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
    if(pIb != NULL)
        a_pLineInfo->m_pInfMax_Over[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
    a_pLineInfo->m_pInfMax_Over[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
    if(pIn != NULL)
        a_pLineInfo->m_pInfMax_Over[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
    if(pIb != NULL)
        m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa,pIb,pIc,ncal,nWavePoints,0,a_pLineInfo->m_dI0_Over,a_pLineInfo->m_dI1_Over,a_pLineInfo->m_dI2_Over);

    //故障后第2周波最大电流
    a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[0]);
    a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[1]);
    a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[2]);
    //	a_pLineInfo->m_dMaxFaultInf_two = max(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_After[3]);
    if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_Over[0]) < depslon)
    {
        strcpy(a_pLineInfo->m_chInfChanel,a_pEleLine->m_pAChanel->m_chName);
    }
    else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_Over[1]) < depslon)
    {
        strcpy(a_pLineInfo->m_chInfChanel,a_pEleLine->m_pBChanel->m_chName);
    }
    else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_Over[2]) < depslon)
    {
        strcpy(a_pLineInfo->m_chInfChanel,a_pEleLine->m_pCChanel->m_chName);
    }
    a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[0]);
    a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[1]);
    a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[2]);
    //	a_pLineInfo->m_dMinFaultVol_two = min(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_After[3]);
    if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_Over[0]) < depslon)
    {
        strcpy(a_pLineInfo->m_chVolChanel,a_pEleLine->m_pBus->m_pAChanel->m_chName);
    }
    else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_Over[1]) < depslon)
    {
        strcpy(a_pLineInfo->m_chVolChanel,a_pEleLine->m_pBus->m_pBChanel->m_chName);
    }
    else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_Over[2]) < depslon)
    {
        strcpy(a_pLineInfo->m_chVolChanel,a_pEleLine->m_pBus->m_pCChanel->m_chName);
    }
    //获取一次值
    a_pLineInfo->m_dMaxFaultInf_one = (float)(a_pLineInfo->m_dMaxFaultInf_two * a_pEleLine->m_dCT/1000.0);
    a_pLineInfo->m_dMinFaultVol_one = (float)(a_pLineInfo->m_dMinFaultVol_two * a_pEleLine->m_pBus->m_dVoltage*10.0/1000.0);

    a_pLineInfo->m_dDistanceI = -100.0;
    a_pLineInfo->m_dDistanceII = -100.0;
}

int CGenerateReport::GetSwitchJump_Line()
{
    int nLine = -1;
    int pLineSwitchCount[100] = {0};
    bool bFind = false;
    unsigned short wId = 0;
    int i = 0;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QString strLineName;
    CEleLine* pLine = NULL;
    CEleDChanel* pDChanel = NULL;

    for(i=0; i<m_SwitchList.m_arStatus.count(); i++)
    {
        bFind = false;
        wId = m_SwitchList.m_arStatus[i].m_wID;
        pDChanel = m_pCmtd->GetDChanelById(wId);
        for(int n=0; n<m_pCmtd->m_arLine.count(); n++)
        {
            pLine = m_pCmtd->m_arLine[n];
            strLineName = gbk->toUnicode(pLine->m_chName);
            if(!pLine->m_bDistance)
            {
                continue;
            }
            if(pLine->m_dLength < 0.5)
            {
                continue;
            }
            if((strLineName.indexOf(QString("旁路")) >= 0)
                ||(strLineName.indexOf(QString("母联")) >= 0)
                ||(strLineName.indexOf(QString("主变")) >= 0)
                ||(strLineName.indexOf(QString("压侧")) >= 0))
            {
                continue;
            }

            for(int nx=0;nx<pLine->m_arDChanel.count(); nx++)
            {
                if(wId == pLine->m_arDChanel[nx])
                {
                    bFind = true;
                    break;
                }
            }
            if(bFind)
            {
                pLineSwitchCount[n]++;
                if(pDChanel->m_eType == CEleDChanel::Relay)
                {
                    pLineSwitchCount[n] += 10;
                }
                break;
            }
        }
    }
    int nMaxSwitchTimes = 0;
    for(i=0; i<m_pCmtd->m_arLine.count(); i++)
    {
//        TRACE("%s: 开关动作次数:%d\n",m_pCmtd->m_arLine[i].m_chName,pLineSwitchCount[i]);
        if(pLineSwitchCount[i] > nMaxSwitchTimes)
        {
            nMaxSwitchTimes = pLineSwitchCount[i];
        }
    }
    if(nMaxSwitchTimes <= 0)	//无法选线
    {
        return -1;
    }


    for(i=0; i<m_pCmtd->m_arLine.count(); i++)
    {        
        if(pLineSwitchCount[i] == nMaxSwitchTimes)
        {
            nLine = i;
            break;
        }
    }
    //delete gbk;
    return nLine;
}

//调用此函数时均已确定区内无故障,因而不再找故障结束点
bool CGenerateReport::IsLines_Inf_Overflow(tagLineInfo* a_pLineInfo, CEleLine* a_pEleLine)
{
    m_nFaultPos = -1;
//    CEleLine* pLine = &(m_pCmtd->m_arLine[a_nLineNo]);
    float dvaluea = 0;
    float dvalueb = 0;
    float dvaluec = 0;
    float* pIa = NULL;
    float* pIb = NULL;
    float* pIc = NULL;
    float* pIn = NULL;
//    bool bYx = false;
    float dNormala = 0.0;
    float dNormalb = 0.0;
    float dNormalc = 0.0;
    int nWavePoints = 0;
    float dAng = 0;
    const float dtb = (float)(0.15 * a_pEleLine->m_dMaxI);
    const float dYx = (float)(0.8 * a_pEleLine->m_dMaxI);
    int nstart = 0;
    int nend = 0;
//    int nFaultOver = -1;
//    unsigned uch = 0;

    bool bAllocA = false;
    bool bAllocB = false;
    bool bAllocC = false;
    bool bAllocN = false;
    int nTotalCount = m_pCmtd->m_nTotalPoints;
    if(a_pEleLine->m_pAChanel != NULL)
        pIa = a_pEleLine->m_pAChanel->m_pData.data();
    else
    {
        pIa = new float[nTotalCount];
        memset(pIa,0,sizeof(float)*nTotalCount);
        bAllocA = true;
    }
    if(a_pEleLine->m_pBChanel != NULL)
        pIb = a_pEleLine->m_pBChanel->m_pData.data();
    else
    {
        pIb = new float[nTotalCount];
        memset(pIb,0,sizeof(float)*nTotalCount);
        bAllocB = true;
    }
    if(a_pEleLine->m_pCChanel != NULL)
        pIc = a_pEleLine->m_pCChanel->m_pData.data();
    else
    {
        pIc = new float[nTotalCount];
        memset(pIc,0,sizeof(float)*nTotalCount);
        bAllocC = true;
    }
    if(a_pEleLine->m_pNChanel != NULL)
        pIn = a_pEleLine->m_pNChanel->m_pData.data();
    else
    {
        pIn = new float[nTotalCount];
        memset(pIn,0,sizeof(float)*nTotalCount);
        bAllocN = true;
    }
    nWavePoints = m_pCmtd->m_pSegment[0].m_nWavePoints;
    dNormala = m_wyCal.Cal_Rms_Result(pIa,0,nWavePoints,dAng);
    dNormalb = m_wyCal.Cal_Rms_Result(pIb,0,nWavePoints,dAng);
    dNormalc = m_wyCal.Cal_Rms_Result(pIc,0,nWavePoints,dAng);

    a_pLineInfo->m_nStartPoint = 0;
    bool bResult = false;
    for(int nseg = 0; nseg<m_pCmtd->m_nSegCount; nseg++)
    {
        nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
        //C、D段不判
        if(nWavePoints < 20)
        {
            continue;
        }
        nstart = m_pCmtd->m_pSegment[nseg].m_nStartPos;
        nend = nstart+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints-4;

        for(int n=nstart; n<nend; n+=nWavePoints/2)
        {
            dvaluea = m_wyCal.Cal_Rms_Result(pIa,n,nWavePoints,dAng);	//计算有效值
            dvalueb = m_wyCal.Cal_Rms_Result(pIb,n,nWavePoints,dAng);	//计算有效值
            dvaluec = m_wyCal.Cal_Rms_Result(pIc,n,nWavePoints,dAng);	//计算有效值

            if((dvaluea > dYx)||(fabs(dvaluea-dNormala) > dtb))	//越限
            {
                a_pLineInfo->m_nStartPoint = n;
                bResult = true;
                m_nFaultPos = n;
                break;
            }
            if((dvalueb > dYx)||(fabs(dvalueb-dNormalb) > dtb))
            {
                a_pLineInfo->m_nStartPoint = n;
                bResult = true;
                m_nFaultPos = n;
                break;
            }
            if(((dvaluec > 0.8*a_pEleLine->m_dMaxI)||(fabs(dvaluec-dNormalc) > dtb))&&(a_pLineInfo->m_nStartPoint == 0))
            {
                a_pLineInfo->m_nStartPoint = n;
                bResult = true;
                m_nFaultPos = n;
                break;
            }
        }
        if(bResult)
        {
            break;
        }
    }
    if(a_pLineInfo->m_nStartPoint <= 0)
    {
        a_pLineInfo->m_nStartPoint = m_pCmtd->m_nTbPos;
    }
    if(m_nFaultPos < 0)
    {
        m_nFaultPos = m_pCmtd->m_nTbPos;
    }

    if(bAllocA)
    {
        delete []pIa;
    }
    if(bAllocB)
    {
        delete []pIb;
    }
    if(bAllocC)
    {
        delete []pIc;
    }
    if(bAllocN)
    {
        delete []pIn;
    }

    return bResult;
}

bool CGenerateReport::IsTrans_Inf_Overflow(tagTransInfo* a_pTransInfo, CEleTrans* a_pEleTrans)
{
    float dvaluea = 0;
    float dvalueb = 0;
    float dvaluec = 0;
    float* pIa = NULL;
    float* pIb = NULL;
    float* pIc = NULL;
//    float* pIn = NULL;
//    bool bYx = false;
    float dNormala = 0.0;
    float dNormalb = 0.0;
    float dNormalc = 0.0;
    int nWavePoints = 0;
    float dAng = 0;
    float dtb = (float)(0.15 * a_pEleTrans->m_pLine[0]->m_dMaxI);
    int nstart = 0;
    int nend = 0;
    int nFaultOver = -1;
    unsigned uch = 0;
    int nf = 0;
    if(a_pEleTrans->m_pLine[0] != NULL)
    {
        pIa = a_pEleTrans->m_pLine[0]->m_pAChanel->m_pData.data();
        pIb = a_pEleTrans->m_pLine[0]->m_pBChanel->m_pData.data();
        pIc = a_pEleTrans->m_pLine[0]->m_pCChanel->m_pData.data();
//        pIn = a_pEleTrans->m_pLine[0]->m_pNChanel->m_pData.data();
        nWavePoints = m_pCmtd->m_pSegment[0].m_nWavePoints;
        dNormala = m_wyCal.Cal_Rms_Result(pIa,0,nWavePoints,dAng);
        dNormalb = m_wyCal.Cal_Rms_Result(pIb,0,nWavePoints,dAng);
        dNormalc = m_wyCal.Cal_Rms_Result(pIc,0,nWavePoints,dAng);
        for(int nseg = 0; nseg<m_pCmtd->m_nSegCount; nseg++)
        {
            nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
            //C、D段不判
            if(nWavePoints < 20)
            {
                continue;
            }
            nstart = m_pCmtd->m_pSegment[nseg].m_nStartPos;
            nend = nstart+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints-10;
            for(int n=nstart; n<nend; n+=nWavePoints/2)
            {
                dvaluea = m_wyCal.Cal_Rms_Result(pIa,n,nWavePoints,dAng);	//计算有效值
                dvalueb = m_wyCal.Cal_Rms_Result(pIb,n,nWavePoints,dAng);	//计算有效值
                dvaluec = m_wyCal.Cal_Rms_Result(pIc,n,nWavePoints,dAng);	//计算有效值

                if((nf!=1)&&((dvaluea > 0.8*a_pEleTrans->m_pLine[0]->m_dMaxI)||(fabs(dvaluea-dNormala) > dtb)))	//越限
                {
                    nf = 1;
                    a_pTransInfo->m_nInfTb = 1;
                    a_pTransInfo->m_uPhase |= 0x01;
                }
                else if((nf==1)&&(fabs(dvaluea-dNormala) < dtb))
                {
                    uch = a_pTransInfo->m_uPhase & 0x01;
                    if((a_pTransInfo->m_nInfTb == 1)&&(uch > 0))
                    {
                        nFaultOver = n;		//故障结束点
                        break;
                    }
                }
                if((nf!=2)&&((dvalueb > 0.8*a_pEleTrans->m_pLine[0]->m_dMaxI)||(fabs(dvalueb-dNormalb) > dtb)))
                {
                    nf = 2;
                    a_pTransInfo->m_nInfTb = 1;
                    a_pTransInfo->m_uPhase |= 0x02;
                }
                else if((nf==2)&&(fabs(dvalueb-dNormalb) < dtb))
                {
                    uch = a_pTransInfo->m_uPhase & 0x02;
                    if((a_pTransInfo->m_nInfTb == 1)&&(uch > 0))
                    {
                        nFaultOver = n;		//故障结束点
                        break;
                    }
                }
                if((nf!=3)&&((dvaluec > 0.8*a_pEleTrans->m_pLine[0]->m_dMaxI)||(fabs(dvaluec-dNormalc) > dtb)))
                {
                    nf = 3;
                    a_pTransInfo->m_nInfTb = 1;
                    a_pTransInfo->m_uPhase |= 0x04;
                }
                else if((nf==3)&&(fabs(dvaluec-dNormalc) < dtb))
                {
                    uch = a_pTransInfo->m_uPhase & 0x04;
                    if((a_pTransInfo->m_nInfTb == 1)&&(uch > 0))
                    {
                        nFaultOver = n;		//故障结束点
                        break;
                    }
                }
            }
            if(nFaultOver > 0)
            {
                break;
            }
        }
    }
    nf = 0;
    if(a_pEleTrans->m_pLine[1] != NULL)
    {
        pIa = a_pEleTrans->m_pLine[1]->m_pAChanel->m_pData.data();
        pIb = a_pEleTrans->m_pLine[1]->m_pBChanel->m_pData.data();
        pIc = a_pEleTrans->m_pLine[1]->m_pCChanel->m_pData.data();
//        pIn = m_pCmtd->m_arTrans[a_nTransNo].m_arLine[1]->m_pNChanel->m_pData.data();
        nWavePoints = m_pCmtd->m_pSegment[0].m_nWavePoints;
        dNormala = m_wyCal.Cal_Rms_Result(pIa,0,nWavePoints,dAng);
        dNormalb = m_wyCal.Cal_Rms_Result(pIb,0,nWavePoints,dAng);
        dNormalc = m_wyCal.Cal_Rms_Result(pIc,0,nWavePoints,dAng);

        for(int nseg = 0; nseg<m_pCmtd->m_nSegCount; nseg++)
        {
            nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
            //C、D段不判
            if(nWavePoints < 20)
            {
                continue;
            }
            nstart = m_pCmtd->m_pSegment[nseg].m_nStartPos;
            nend = nstart+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints-10;
            for(int n=nstart; n<nend; n++)
            {
                dvaluea = m_wyCal.Cal_Rms_Result(pIa,n,nWavePoints,dAng);	//计算有效值
                dvalueb = m_wyCal.Cal_Rms_Result(pIb,n,nWavePoints,dAng);	//计算有效值
                dvaluec = m_wyCal.Cal_Rms_Result(pIc,n,nWavePoints,dAng);	//计算有效值

                if((nf!=1)&&((dvaluea > 0.8*a_pEleTrans->m_pLine[1]->m_dMaxI)||(dvaluea-dNormala > dtb)))	//越限
                {
                    nf = 1;
                    a_pTransInfo->m_nInfTb = 2;
                    a_pTransInfo->m_uPhase |= 0x01;
                }
                else if((nf==1)&&(dvaluea-dNormala < dtb))
                {
                    uch = a_pTransInfo->m_uPhase & 0x01;
                    if((a_pTransInfo->m_nInfTb == 2)&&(uch > 0))
                    {
                        nFaultOver = n;		//故障结束点
                        break;
                    }
                }
                if((nf!=2)&&((dvalueb > 0.8*a_pEleTrans->m_pLine[1]->m_dMaxI)||(dvalueb-dNormalb > dtb)))
                {
                    nf = 2;
                    a_pTransInfo->m_nInfTb = 2;
                    a_pTransInfo->m_uPhase |= 0x02;
                }
                else if((nf==2)&&(dvalueb-dNormalb < dtb))
                {
                    uch = a_pTransInfo->m_uPhase & 0x02;
                    if((a_pTransInfo->m_nInfTb == 2)&&(uch > 0))
                    {
                        nFaultOver = n;		//故障结束点
                        break;
                    }
                }
                if((nf!=3)&&((dvaluec > 0.8*a_pEleTrans->m_pLine[1]->m_dMaxI)||(dvaluec-dNormalc > dtb)))
                {
                    nf = 3;
                    a_pTransInfo->m_nInfTb = 2;
                    a_pTransInfo->m_uPhase |= 0x04;
                }
                else if((nf==3)&&(dvaluec-dNormalc < dtb))
                {
                    uch = a_pTransInfo->m_uPhase & 0x04;
                    if((a_pTransInfo->m_nInfTb == 2)&&(uch > 0))
                    {
                        nFaultOver = n;		//故障结束点
                        break;
                    }
                }
            }
            if(nFaultOver > 0)
            {
                break;
            }
        }
    }
    nf = 0;
    if(a_pEleTrans->m_pLine[2] != NULL)
    {
        pIa = a_pEleTrans->m_pLine[2]->m_pAChanel->m_pData.data();
        pIb = a_pEleTrans->m_pLine[2]->m_pBChanel->m_pData.data();
        pIc = a_pEleTrans->m_pLine[2]->m_pCChanel->m_pData.data();
//        pIn = m_pCmtd->m_arTrans[a_nTransNo].m_arLine[2]->m_pNChanel->m_pData.data();
        nWavePoints = m_pCmtd->m_pSegment[0].m_nWavePoints;
        dNormala = m_wyCal.Cal_Rms_Result(pIa,0,nWavePoints,dAng);
        dNormalb = m_wyCal.Cal_Rms_Result(pIb,0,nWavePoints,dAng);
        dNormalc = m_wyCal.Cal_Rms_Result(pIc,0,nWavePoints,dAng);

        for(int nseg = 0; nseg<m_pCmtd->m_nSegCount; nseg++)
        {
            nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
            //C、D段不判
            if(nWavePoints < 20)
            {
                continue;
            }
            nstart = m_pCmtd->m_pSegment[nseg].m_nStartPos;
            nend = nstart+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints-10;
            for(int n=nstart; n<nend; n++)
            {
                dvaluea = m_wyCal.Cal_Rms_Result(pIa,n,nWavePoints,dAng);	//计算有效值
                dvalueb = m_wyCal.Cal_Rms_Result(pIb,n,nWavePoints,dAng);	//计算有效值
                dvaluec = m_wyCal.Cal_Rms_Result(pIc,n,nWavePoints,dAng);	//计算有效值

                if((nf!=1)&&((dvaluea > 0.8*a_pEleTrans->m_pLine[2]->m_dMaxI)||(dvaluea-dNormala > dtb)))	//越限
                {
                    nf = 1;
                    a_pTransInfo->m_nInfTb = 3;
                    a_pTransInfo->m_uPhase |= 0x01;
                }
                else if((nf==1)&&(dvaluea-dNormala < dtb))
                {
                    uch = a_pTransInfo->m_uPhase & 0x01;
                    if((a_pTransInfo->m_nInfTb == 3)&&(uch > 0))
                    {
                        nFaultOver = n;		//故障结束点
                        break;
                    }
                }
                if((nf!=2)&&((dvalueb > 0.8*a_pEleTrans->m_pLine[2]->m_dMaxI)||(dvalueb-dNormalb > dtb)))
                {
                    nf = 2;
                    a_pTransInfo->m_nInfTb = 3;
                    a_pTransInfo->m_uPhase |= 0x02;
                }
                else if((nf==2)&&(dvalueb-dNormalb < dtb))
                {
                    uch = a_pTransInfo->m_uPhase & 0x02;
                    if((a_pTransInfo->m_nInfTb == 3)&&(uch > 0))
                    {
                        nFaultOver = n;		//故障结束点
                        break;
                    }
                }
                if((nf!=3)&&((dvaluec > 0.8*a_pEleTrans->m_pLine[2]->m_dMaxI)||(dvaluec-dNormalc > dtb)))
                {
                    nf = 3;
                    a_pTransInfo->m_nInfTb = 3;
                    a_pTransInfo->m_uPhase |= 0x04;
                }
                else if((nf==3)&&(dvaluec-dNormalc < dtb))
                {
                    uch = a_pTransInfo->m_uPhase & 0x04;
                    if((a_pTransInfo->m_nInfTb == 3)&&(uch > 0))
                    {
                        nFaultOver = n;		//故障结束点
                        break;
                    }
                }
            }
            if(nFaultOver > 0)
            {
                break;
            }
        }
    }
    if(nFaultOver < 0)
    {
        nFaultOver = m_pCmtd->m_nTotalPoints-1;
    }
    a_pTransInfo->m_nFaultEnd = nFaultOver;
    if(a_pTransInfo->m_nInfTb != 0)
    {
        return true;
    }
    return false;
}

void CGenerateReport::GetMaxInf_Trans(int a_nTransNo)
{
    int j = 0;
    float dmaxI = 0;
    int nNum = 2;
    int nTNo = m_arTransInfo[a_nTransNo].m_nTransIndex;
    if(m_pCmtd->m_arTrans[nTNo]->m_pLine[2] != NULL)
    {
        nNum = 3;
    }
    if(m_pCmtd->m_arTrans[nTNo]->m_pLine[3] != NULL)
    {
        nNum = 4;
    }
    for(j=0; j<nNum; j++)
    {
        if(dmaxI < m_arTransInfo[a_nTransNo].m_pLine[j].m_dMaxFaultInf_two)
        {
            dmaxI = m_arTransInfo[a_nTransNo].m_pLine[j].m_dMaxFaultInf_two;
        }
    }
    for(j=0; j<nNum; j++)
    {
        if(fabs(dmaxI - m_arTransInfo[a_nTransNo].m_pLine[j].m_dMaxFaultInf_two) < 0.1)
        {
            strcpy(m_arTransInfo[a_nTransNo].m_chInfChanel,m_arTransInfo[a_nTransNo].m_pLine[j].m_chInfChanel);
            m_arTransInfo[a_nTransNo].m_dMaxFaultInf_one = m_arTransInfo[a_nTransNo].m_pLine[j].m_dMaxFaultInf_one;
            m_arTransInfo[a_nTransNo].m_dMaxFaultInf_two = m_arTransInfo[a_nTransNo].m_pLine[j].m_dMaxFaultInf_two;
            break;
        }
    }
}

void CGenerateReport::GetMinVol_Trans(int a_nTransNo)
{
    int j = 0;
    float dminV = 1000;
    int nNum = 2;
    int nTNo = m_arTransInfo[a_nTransNo].m_nTransIndex;
    if(m_pCmtd->m_arTrans[nTNo]->m_pLine[2] != NULL)
    {
        nNum = 3;
    }
    if(m_pCmtd->m_arTrans[nTNo]->m_pLine[3] != NULL)
    {
        nNum = 4;
    }
    for(j=0; j<nNum; j++)
    {
        if(dminV > m_arTransInfo[a_nTransNo].m_pLine[j].m_dMinFaultVol_two)
        {
            dminV = m_arTransInfo[a_nTransNo].m_pLine[j].m_dMinFaultVol_two;
        }
    }
    for(j=0; j<nNum; j++)
    {
        if(fabs(dminV - m_arTransInfo[a_nTransNo].m_pLine[j].m_dMinFaultVol_two) < 0.1)
        {
            strcpy(m_arTransInfo[a_nTransNo].m_chVolChanel,m_arTransInfo[a_nTransNo].m_pLine[j].m_chVolChanel);
            m_arTransInfo[a_nTransNo].m_dMinFaultVol_one = m_arTransInfo[a_nTransNo].m_pLine[j].m_dMinFaultVol_one;
            m_arTransInfo[a_nTransNo].m_dMinFaultVol_two = m_arTransInfo[a_nTransNo].m_pLine[j].m_dMinFaultVol_two;
            break;
        }
    }
}

void CGenerateReport::InitData()
{
    memset(m_chFaultLine,0,sizeof(m_chFaultLine));
    m_uFpt = 0;
    m_uJpt = 0;
    m_fFaultDistance = 0;
    m_uDpi = 0;
    m_wChzTime = 0;
    memset(&m_cpStartTime,0,sizeof(m_cpStartTime));
    m_dwFileSize = 0;
    int i = 0;
    for(i=0; i<MAX_TBLINE_COUNT; i++)
    {
        m_arLineInfo[i].InitData();
    }
    for(i=0; i<MAX_TRANSCOUNT; i++)
    {
        m_arTransInfo[i].InitData();
    }
    m_nFaultPos = -1;
    m_pFaultLine = NULL;
    m_pFaultTrans = NULL;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 计算衰减时间常数
//参	数: 
//			a_pData				通道数据
//			a_nWavePints		每周波点数目
//返 回	值: 时间常数
//备	注: 
//创建日期: 2008-01-22		wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
float CGenerateReport::Dist_CalDeltaT_Ex(float *a_pData, int a_nWavePoints)
{
    float dang = 0;
    float dsegma1 = m_wyCal.DFT_Rms(a_pData,a_nWavePoints,dang);
    float dsegma2 = m_wyCal.DFT_Rms(a_pData+a_nWavePoints,a_nWavePoints,dang);
    float dresult = (float)(-20.0/log(dsegma2/dsegma1));
    if(dresult < 0)
    {
        dresult = 0;
    }
    return dresult;
}

int CGenerateReport::Dist_CalDistance2_ext(float *a_pDataU[], float *a_pDataI[], float *a_pHgI0, int a_nCalPos, int a_nWavePoints, float a_dRX[], float a_dRXM[], int a_nFaultKind, float &a_dR, float &a_dX,float fLineX, bool a_bConvert)
{
    int tmp=0;

    float uaFilter[50],ubFilter[50],ucFilter[50];
    float iaFilter[50],ibFilter[50],icFilter[50],i0Filter[50];
    float uabFilter[50],ubcFilter[50],ucaFilter[50];
    float iabFilter[50],ibcFilter[50],icaFilter[50];

    float hginFilter[50];
    float hginFilter2[50];

    float uaFilter2[50],ubFilter2[50],ucFilter2[50];
    float iaFilter2[50],ibFilter2[50],icFilter2[50],i0Filter2[50];
    int i=0;
    int filterlen = 21;

    ///////////////////////////////////////////////////////////////////////////////////////
    //三相电压经过两次滤波
    //输入Ua,ub,uc,输出: uaFilter,ubFilter,ucFilter
    //[[
    Dist_WaveFilter(a_pDataU[0]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,uaFilter2);
    Dist_WaveFilter(a_pDataU[1]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,ubFilter2);
    Dist_WaveFilter(a_pDataU[2]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,ucFilter2);

    Dist_WaveFilter(uaFilter2,26,20,m_dParam,filterlen,uaFilter);
    Dist_WaveFilter(ubFilter2,26,20,m_dParam,filterlen,ubFilter);
    Dist_WaveFilter(ucFilter2,26,20,m_dParam,filterlen,ucFilter);
    //]]
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    //电流滤波
    //输入Ia,Ib,Ic,I0，输出: iaFilter,ibFilter,icFilter,i0Filter
    //[[
    Dist_WaveFilter(a_pDataI[0]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,iaFilter2);
    Dist_WaveFilter(a_pDataI[1]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,ibFilter2);
    Dist_WaveFilter(a_pDataI[2]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,icFilter2);
    Dist_WaveFilter(a_pDataI[3]+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,i0Filter2,a_bConvert);

    Dist_WaveFilter(iaFilter2,26,20,m_dParam,filterlen,iaFilter);
    Dist_WaveFilter(ibFilter2,26,20,m_dParam,filterlen,ibFilter);
    Dist_WaveFilter(icFilter2,26,20,m_dParam,filterlen,icFilter);
    Dist_WaveFilter(i0Filter2,26,20,m_dParam,filterlen,i0Filter);
    //]]

    //	if(a_pHgI0 != NULL)
    {
        Dist_WaveFilter(a_pHgI0+a_nCalPos,50,a_nWavePoints,m_dParam,filterlen,hginFilter2);
        Dist_WaveFilter(hginFilter2,26,20,m_dParam,filterlen,hginFilter);
    }

    //float icvalue = sqrt(0.5*(icFilter[0]*icFilter[0] + icFilter[5]*icFilter[5]));
    //float i0value = sqrt(0.5*(i0Filter[0]*i0Filter[0] + i0Filter[5]*i0Filter[5]));

    //////////////////////////////////////////////////////////////////////////
    //计算uab,ubc,uca,iab,ibc,ica
    //[[
    for(i=0;i<10;i++)
    {
        uabFilter[i] = uaFilter[i] - ubFilter[i];
        ubcFilter[i] = ubFilter[i] - ucFilter[i];
        ucaFilter[i] = ucFilter[i] - uaFilter[i];
        iabFilter[i] = iaFilter[i] - ibFilter[i];
        ibcFilter[i] = ibFilter[i] - icFilter[i];
        icaFilter[i] = icFilter[i] - iaFilter[i];
    }
    //]]

    //////////////////////////////////////////////////////////////////////////
    //调用测距函数计算阻抗
    //[[
    const float fRg = 10;                   //判断是否经过渡电阻接地 (2016-12-27加)
    const float fXe = fLineX*.75;           //线路总电抗*.7
    float fRX = a_dRX[1]/a_dRX[3];          //r1/x1
    switch (a_nFaultKind)
    {
    case  FAULT_AN:
        {
            tmp = Dist_CalRX_PG4_ext(uaFilter,iaFilter,i0Filter,hginFilter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dRXM[0],a_dRXM[1],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,iaFilter,ibFilter,icFilter,i0Filter,fRX);
            }
        }
        break;
    case  FAULT_BN:
        {
            tmp = Dist_CalRX_PG4_ext(ubFilter,ibFilter,i0Filter,hginFilter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dRXM[0],a_dRXM[1],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,ibFilter,icFilter,iaFilter,i0Filter,fRX);
            }
        }
        break;
    case  FAULT_CN:
        {
            tmp = Dist_CalRX_PG4_ext(ucFilter,icFilter,i0Filter,hginFilter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dRXM[0],a_dRXM[1],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,icFilter,iaFilter,ibFilter,i0Filter,fRX);
            }
        }
        break;
    case  FAULT_AB:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BC:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CA:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABN:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BCN:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CAN:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABC:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    }
    //]]

#ifndef GDWY_JIANCE
    if(a_dX < 0)
        a_dX = -a_dX;
#endif
    return tmp;
}

int CGenerateReport::Dist_CalRX_PG4_ext(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float* a_pDataHgI0,float a_dR0,float a_dR1,float a_dX0,float a_dX1,float a_dHgR0,float a_dHgX0,float& a_dR,float& a_dX)
{
    //基本公式：Ua=Ud+(Ia+k3I0)LZ1
    float u1,u2,i1,i2,d1,d2,det;
    float kr = (float)((a_dR0-a_dR1)/3./a_dR1);			//参数k实部
    float kl = (float)((a_dX0-a_dX1)/3./a_dX1);			//参数k虚部
    float kmr = (float)((a_dHgR0)/3./a_dR1);
    float kml = (float)((a_dHgX0)/3./a_dX1);
    float rlbl = (float)(a_dR1*2.*m_dPI*m_nFreq/a_dX1);	//2*PI*f*R1/X1

    //////////////////////////////////////////////////////////////////////////
    //这里是否是判断一个计算盲点?(根据有效值和下一点瞬时值判断)
    float ivalue = (float)(sqrt(a_pDataI[0]*a_pDataI[0] + a_pDataI[5]*a_pDataI[5]));	//有效值
    if(a_pDataI[1] > (0.9* ivalue))
        return 0;

    u1=a_pDataU[1];
    u2=a_pDataU[2];
    
    i1=a_pDataI0[1];
    i2=a_pDataI0[2];

    d1=(float)(rlbl*(a_pDataI[1]+kr*a_pDataI0[1]+kmr*a_pDataHgI0[1])+2*m_dPI*m_nFreq*(a_pDataI[2]+kl*a_pDataI0[2]+kml*a_pDataHgI0[2]-a_pDataI[0]-kl*a_pDataI0[0]-kml*a_pDataHgI0[0])/(2.*sin(0.1*m_dPI)));
    d2=(float)(rlbl*(a_pDataI[2]+kr*a_pDataI0[2]+kmr*a_pDataHgI0[2])+2*m_dPI*m_nFreq*(a_pDataI[3]+kl*a_pDataI0[3]+kml*a_pDataHgI0[3]-a_pDataI[1]-kl*a_pDataI0[1]-kml*a_pDataHgI0[1])/(2.*sin(0.1*m_dPI)));

    det=i2*d1-i1*d2;

    if(det)
    {
        a_dX=(float)((u1*i2-u2*i1)/det);
        a_dR=(float)((u2*d1-u1*d2)/det);

        a_dX=(float)(2.*m_dPI*m_nFreq*a_dX);
	
        return 1;
    }
    else
    {
        return 0;
    }
}

int CGenerateReport::Dist_CalDistance3_ext(float *a_pDataU[], float *a_pDataI[], float *a_pHgI0, int a_nCalPos, int a_nWavePoints, float a_dRX[], float a_dRXM[], int a_nFaultKind, float &a_dR, float &a_dX,float fLineX, bool a_bConvert)
{
    int tmp=0;

    float uaFilter[50] = {0};
    float ubFilter[50] = {0};
    float ucFilter[50] = {0};
    float iaFilter[50],ibFilter[50],icFilter[50],i0Filter[50];
    float uabFilter[50],ubcFilter[50],ucaFilter[50];
    float iabFilter[50],ibcFilter[50],icaFilter[50];
    int i=0;
    int filterlen = 21;

    float hginFilter[50];

    Dist_WaveFilter(a_pDataU[0]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,uaFilter);
    Dist_WaveFilter(a_pDataU[1]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,ubFilter);
    Dist_WaveFilter(a_pDataU[2]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,ucFilter);

    Dist_WaveFilter(a_pDataI[0]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,iaFilter);
    Dist_WaveFilter(a_pDataI[1]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,ibFilter);
    Dist_WaveFilter(a_pDataI[2]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,icFilter);
    Dist_WaveFilter(a_pDataI[3]+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,i0Filter,a_bConvert);
    Dist_WaveFilter(a_pHgI0+a_nCalPos,26,a_nWavePoints,m_dParam,filterlen,hginFilter);

    //float icvalue = sqrt(0.5*(icFilter[0]*icFilter[0] + icFilter[5]*icFilter[5]));
    //float i0value = sqrt(0.5*(i0Filter[0]*i0Filter[0] + i0Filter[5]*i0Filter[5]));

    for(i=0;i<10;i++)
    {
        uabFilter[i] = uaFilter[i] - ubFilter[i];
        ubcFilter[i] = ubFilter[i] - ucFilter[i];
        ucaFilter[i] = ucFilter[i] - uaFilter[i];
        iabFilter[i] = iaFilter[i] - ibFilter[i];
        ibcFilter[i] = ibFilter[i] - icFilter[i];
        icaFilter[i] = icFilter[i] - iaFilter[i];
    }

    //2016-12-27
    const float fRg = 10;                   //判断是否经过渡电阻接地 (2016-12-27加)
    const float fXe = fLineX*.75;    //线路总电抗*.7
    float fRX = a_dRX[1]/a_dRX[3];          //r1/x1

    switch (a_nFaultKind)
    {
    case  FAULT_AN:
        {
            tmp = Dist_CalRX_PG4_ext(uaFilter,iaFilter,i0Filter,hginFilter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dRXM[0],a_dRXM[1],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,iaFilter,ibFilter,icFilter,i0Filter,fRX);
            }
        }
        break;
    case  FAULT_BN:
        {
            tmp = Dist_CalRX_PG4_ext(ubFilter,ibFilter,i0Filter,hginFilter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dRXM[0],a_dRXM[1],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,ibFilter,icFilter,iaFilter,i0Filter,fRX);
            }
        }
        break;
    case  FAULT_CN:
        {
            tmp = Dist_CalRX_PG4_ext(ucFilter,icFilter,i0Filter,hginFilter,a_dRX[0],a_dRX[1],a_dRX[2],a_dRX[3],a_dRXM[0],a_dRXM[1],a_dR,a_dX);
            if((a_dR > (fRg*0.7))&&(a_dX>(fXe*0.7)))   //末端过渡电阻接地
            {
                Param_TermPG(a_dR,a_dX,icFilter,iaFilter,ibFilter,i0Filter,fRX);
            }
        }
        break;
    case  FAULT_AB:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BC:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CA:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABN:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    case  FAULT_BCN:
        tmp = Dist_CalRXEx_PP(ubcFilter,ibcFilter,a_dR,a_dX);
        break;
    case  FAULT_CAN:
        tmp = Dist_CalRXEx_PP(ucaFilter,icaFilter,a_dR,a_dX);
        break;
    case  FAULT_ABC:
        tmp = Dist_CalRXEx_PP(uabFilter,iabFilter,a_dR,a_dX);
        break;
    }

#ifndef GDWY_JIANCE
    if(a_dX < 0)
        a_dX = -a_dX;
#endif

    return tmp;
}

void CGenerateReport::OutputSwitchList_to_File(const QString &a_strFile)
{
    QFile mfile(a_strFile);
    if(!mfile.open(QIODevice::WriteOnly))
    {
        return;
    }

    char strline[2048] = {0};
    if(m_SwitchList.m_arStatus.count() <= 0)
    {
        strcpy(strline,"无开关动作信息\r\n");
        mfile.write(strline,strlen(strline));
    }

    char stra[256]={0},strb[256]={0},strc[256]={0};
    int i = 0;
    for(i=0; i<m_SwitchList.m_arStatus.count(); i++)
    {
        //qDebug("位置%d\n",m_SwitchList.m_arStatus[i].m_nTimePoint);
        sprintf(stra,"%-6.1f",m_pCmtd->m_pSampleTime[m_SwitchList.m_arStatus[i].m_nTimePoint]/1000.0);
        strcpy(strb,m_SwitchList.m_arStatus[i].m_chName);
        if(m_SwitchList.m_arStatus[i].m_bStatus)
        {
            strcpy(strc,"开");
        }
        else
        {
            strcpy(strc,"合");
        }
        sprintf(strline,"%-31s%-30s%-24s\r\n",stra,strb,strc);
        mfile.write(strline,strlen(strline));
    }

    mfile.close();
}

bool CGenerateReport::AnalysisLine_manual(int a_nLineIndex, int a_nFaultPos,int a_nFaultType,tagLineInfo *a_pLineInfo)
{
    if(!m_pCmtd->m_arLine[a_nLineIndex]->IsChanel_Full())
    {
        return false;
    }
    int nseg = m_pCmtd->GetCurSeg(a_nFaultPos);
    int nabSample = m_pCmtd->m_pSegment[nseg].m_nWavePoints;	//AB段采样率
    if(nabSample < 20)
    {
        return false;
    }
    if(m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-a_nFaultPos < 1.5*nabSample)
    {
        return false;
    }
    int nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
    QPoint arFaultList[2];			//故障点序列
    int nFaultPoint = 0;			//故障点数目
    float dFactor = (float)(m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_dVoltage*10.0/m_pCmtd->m_arLine[a_nLineIndex]->m_dCT);//变比
    float dLineLength = m_pCmtd->m_arLine[a_nLineIndex]->m_dLength;
    float fLineX = (dLineLength*m_pCmtd->m_arLine[a_nLineIndex]->m_dX1)/dFactor;
    float fLineR = (dLineLength*m_pCmtd->m_arLine[a_nLineIndex]->m_dR1)/dFactor;
    bool bMFault = FaultLine(m_pCmtd->m_arLine[a_nLineIndex]);
//    TRACE("分析线路:%s\n",m_pCmtd->m_arLine[a_nLineIndex].m_chName);
    //-----------------------------------------------------------------------------------
    //获取线路的单位正序零序电阻、正序电阻、零序电抗、正序电抗
    //-----------------------------------------------------------------------------------
    float dRX[4] = {0};		//单位正序零序电阻、正序电阻、零序电抗、正序电抗
    dRX[0] = m_pCmtd->m_arLine[a_nLineIndex]->m_dR0;
    dRX[1] = m_pCmtd->m_arLine[a_nLineIndex]->m_dR1;
    dRX[2] = m_pCmtd->m_arLine[a_nLineIndex]->m_dX0;
    dRX[3] = m_pCmtd->m_arLine[a_nLineIndex]->m_dX1;
    float dRXM[2] = {0};	//单位互感阻抗
    dRXM[0] = m_pCmtd->m_arLine[a_nLineIndex]->m_dRh;
    dRXM[1] = m_pCmtd->m_arLine[a_nLineIndex]->m_dXh;
    float* pHgI0 = NULL;
    int nhgline = m_pCmtd->m_arLine[a_nLineIndex]->m_nHgLine;
    if((nhgline>=0)&&(nhgline<m_pCmtd->m_arLine.count()))
    {
        pHgI0 = new float[m_pCmtd->m_nTotalPoints+100];
        for(int i=0; i<m_pCmtd->m_nTotalPoints; i++)
        {
            pHgI0[i] = 0;
            if(m_pCmtd->m_arLine[nhgline]->m_pAChanel != NULL)
                pHgI0[i] += m_pCmtd->m_arLine[nhgline]->m_pAChanel->m_pData[i];
            if(m_pCmtd->m_arLine[nhgline]->m_pBChanel != NULL)
                pHgI0[i] += m_pCmtd->m_arLine[nhgline]->m_pBChanel->m_pData[i];
            if(m_pCmtd->m_arLine[nhgline]->m_pCChanel != NULL)
                pHgI0[i] += m_pCmtd->m_arLine[nhgline]->m_pCChanel->m_pData[i];
        }
    }
    float dr0 = dRX[0];
    float dr1 = dRX[1];
    float dx0 = dRX[2];
    float dx1 = dRX[3];
//	float klr = (float)((sqrt(dx0*dx0+dr0*dr0) - sqrt(dx1*dx1+dr1*dr1))/(3.* sqrt(dx1*dx1+dr1*dr1))); //(x0-x1) / (3.*x1);(修正参数)
    float dMaxI = m_pCmtd->m_arLine[a_nLineIndex]->m_dMaxI;
    Q_UNUSED(dr0);
    Q_UNUSED(dr1);
    Q_UNUSED(dx0);
    Q_UNUSED(dMaxI);

    //-----------------------------------------------------------------------------------
    //获取电压/电流的数据指针
    //2011-8-26 修改 兼容66KV
    //-----------------------------------------------------------------------------------
    bool bAllocIa = false;
    bool bAllocIb = false;
    bool bAllocIc = false;
//    bool bAllocIn = false;
    int nTotalCount = m_pCmtd->m_nTotalPoints;
    float *pUa=NULL,*pUb=NULL,*pUc=NULL,*pUn=NULL;
    unsigned short usUID[3] = {0};
    pUa = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pAChanel->m_pData.data();
    usUID[0] = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pAChanel->m_wID;
    pUb = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pBChanel->m_pData.data();
    usUID[1] = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pBChanel->m_wID;
    pUc = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pCChanel->m_pData.data();
    usUID[2] = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pCChanel->m_wID;
    if(m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pNChanel != NULL)
        pUn = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pNChanel->m_pData.data();
    float *pIa=NULL,*pIb=NULL,*pIc=NULL,*pIn=NULL;
    unsigned short usIID[3] = {0};
    if(m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel != NULL)
    {
        pIa = m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel->m_pData.data();
        usIID[0] = m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel->m_wID;
    }
    else
    {
        pIa = new float[nTotalCount];
        memset(pIa,0,sizeof(float)*nTotalCount);
        bAllocIa = true;
    }
    if(m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel != NULL)
    {
        pIb = m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel->m_pData.data();
        usIID[1] = m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel->m_wID;
    }
    else
    {
        pIb = new float[nTotalCount];
        memset(pIb,0,sizeof(float)*nTotalCount);
        bAllocIb = true;
    }
    if(m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel != NULL)
    {
        pIc = m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel->m_pData.data();
        usIID[2] = m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel->m_wID;
    }
    else
    {
        pIc = new float[nTotalCount];
        memset(pIc,0,sizeof(float)*nTotalCount);
        bAllocIc = true;
    }
// 	if(m_pCmtd->m_arLine[a_nLineIndex]->m_pNChanel != NULL)
// 		pIn = m_pCmtd->m_arLine[a_nLineIndex]->m_pNChanel->m_pData.data();
// 	else
// 	{
// 		pIn = new float[nTotalCount];
// 		memset(pIn,0,sizeof(float)*nTotalCount);
// 		bAllocIn = true;
// 	}

    strcpy(a_pLineInfo->m_chBusI_Name,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_chName);
    if((pUa==NULL)||(pUb==NULL)||(pUc==NULL)||(pIa==NULL)||(pIb==NULL)||(pIc==NULL))
    {
        return false;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //2009-02-17 迪庆变
    //怀疑零序采样有错误,暂且使用自产零序分析
    //[
    float* pIn_ex = new float[m_pCmtd->m_nTotalPoints];
    for(int m=0; m<m_pCmtd->m_nTotalPoints; m++)
    {
        pIn_ex[m] = (pIa[m]+pIb[m]+pIc[m]);
    }
    pIn = pIn_ex;
    //]

    float* pDataI3[3] = {pIa,pIb,pIc};
    Q_UNUSED(pDataI3);
    float* pDataI4[4] = {pIa,pIb,pIc,pIn};
    float* pDataU3[3] = {pUa,pUb,pUc};

    arFaultList[0].setX(a_nFaultPos);
    arFaultList[0].setY(a_nFaultType);
    arFaultList[1].setX((int)(a_nFaultPos  + 1.5*nWavePoints));
    arFaultList[1].setY(FAULT_OVER);
    nFaultPoint = 2;
    //修改测距判断逻辑 [1/21/2008]
    //针对遂昌变数据修改
    //---------------------------------------------------------------------------------------------
    //遍历所有突变点,查找故障点和再次故障点(只找两次,找到再次故障点后返回)
    //---------------------------------------------------------------------------------------------
    int  nStartFault_1 = -1;
    int  nEndFault_1 = -1;
    int  nFaultPharse = FAULT_NONE;
    bool bFault = false;
//    int  npos = 0;
//    bool bReFault = false;
//    int nReFaultPharse = FAULT_NONE;
//    int  nStartFault_2 = -1;
//    int  nEndFault_2 = -1;
    int i = 0;
    for(i=0; i<nFaultPoint; i++)
    {
        if(!bFault)	//首次故障
        {
            if(nStartFault_1 < 0)
            {
                if((arFaultList[i].y()>=FAULT_AN)&&(arFaultList[i].y()<=FAULT_ABC))
                {
                    nFaultPharse = arFaultList[i].y();
                    nStartFault_1 = arFaultList[i].x();
                }
            }
            else
            {
                if(arFaultList[i].y() == FAULT_OVER)
                {
                    nEndFault_1 = arFaultList[i].x();
                    bFault = true;
                }
            }
        }
    }

//    float dFaultDistance = -1000.0;	//暂存故障距离
    if(bFault)
    {
//        float dlasttime = (float)((m_pCmtd->m_pSampleTime[nEndFault_1] - m_pCmtd->m_pSampleTime[nStartFault_1])/1000.);
        int ndetpos = (int)(0.25*20*nabSample/20);		//1/4周波
        int ncalpos = ndetpos;							//计算开始位置,默认相对于突变点1/4周波
        float dr = 0.0;	//短路电阻
        float dx = 0.0;	//短路电抗
        bool bSucess = false;

        //////////////////////////////////////////////////////////////////////////
        //针对默认母线测距
        //[[
        ncalpos = nStartFault_1;
        if(pHgI0 == NULL)
        {
            if(Dist_CalDistance3(pDataU3,pDataI4,ncalpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
            {
                bSucess = true;
            }
            else if(Dist_CalDistance3(pDataU3,pDataI4,ncalpos+ndetpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
            {
                bSucess = true;
            }
        }
        else
        {
            if(Dist_CalDistance3_ext(pDataU3,pDataI4,pHgI0,ncalpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
            {
                bSucess = true;
            }
            else if(Dist_CalDistance3_ext(pDataU3,pDataI4,pHgI0,ncalpos+ndetpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
            {
                bSucess = true;
            }
        }
        //]]

        if(bSucess)
        {
            //2020-10-13 超出范围，强制修正(故障)[[
            if(bMFault)
            {
                if((dx>fLineX)||(dx<0))
                {
                    double dfc = 0.99+fRandm(1000)/100.;
                    dr = fLineR*dfc;
                    dx = fLineX*dfc;
                }
            }
            //]]

            //衰减时间常数
            float dTimeDecrease = Dist_CalDeltaT(pIa+ncalpos,pIb+ncalpos,pIc+ncalpos,20,nFaultPharse);
            float dstart = (float)(m_pCmtd->m_pSampleTime[nStartFault_1]/1000.0);
            float dend = (float)(m_pCmtd->m_pSampleTime[nEndFault_1]/1000.0);
            float dDistance = (float)(dx*dFactor/dx1);
            float dxfl[2] = {0};	//暂存序分量
            Q_UNUSED(dstart);
            Q_UNUSED(dend);
            Q_UNUSED(dxfl);
//            dFaultDistance = dDistance;
//            TRACE("故障开始时间: %g(毫秒),故障结束时间: %g(毫秒),衰减时间常数: %g(毫秒),距离:%g(公里)\n",dstart,dend,dTimeDecrease,dDistance);
            a_pLineInfo->m_dDeltaT = dTimeDecrease;
            a_pLineInfo->m_nStartPoint = nStartFault_1;
            a_pLineInfo->m_nEndPoint = nEndFault_1;
            a_pLineInfo->m_dDistanceI = dDistance;
            a_pLineInfo->m_nFaultType = nFaultPharse;

            a_pLineInfo->m_dFaultR = dr*dFactor;
            a_pLineInfo->m_dFaultX = dx*dFactor;

            //------------------------------------------------------------------------------------
            //获取分析结果,前后一周波数据等
            //------------------------------------------------------------------------------------
            int nseg = m_pCmtd->GetCurSeg(nStartFault_1);
            int nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
            int ncal = 0;
            if(nStartFault_1 - nWavePoints < m_pCmtd->m_pSegment[nseg].m_nStartPos)
            {
                ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos;
            }
            else
            {
                ncal = nStartFault_1 - nWavePoints;
            }
            //故障开始前一周波(电压电流有效值、峰值等)
            a_pLineInfo->m_pVolRms_Before[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[0],1);
            m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_Before[0]);
            a_pLineInfo->m_pVolRms_Before[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[1],1);
            m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_Before[1]);
            a_pLineInfo->m_pVolRms_Before[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[2],1);
            m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_Before[2]);
            if(pUn != NULL)
                a_pLineInfo->m_pVolRms_Before[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Before[3],1);
            a_pLineInfo->m_pVolMax_Before[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_Before[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_Before[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
            if(pUn != NULL)
                a_pLineInfo->m_pVolMax_Before[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa,pUb,pUc,ncal,nWavePoints,0,a_pLineInfo->m_dU0_Before,a_pLineInfo->m_dU1_Before,a_pLineInfo->m_dU2_Before);
            a_pLineInfo->m_pInfRms_Before[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[0],1);
            m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_Before[0]);
            a_pLineInfo->m_pInfRms_Before[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[1],1);
            m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_Before[1]);
            a_pLineInfo->m_pInfRms_Before[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[2],1);
            m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_Before[2]);
            a_pLineInfo->m_pInfRms_Before[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Before[3],1);
            a_pLineInfo->m_pInfMax_Before[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Before[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Before[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Before[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa,pIb,pIc,ncal,nWavePoints,0,a_pLineInfo->m_dI0_Before,a_pLineInfo->m_dI1_Before,a_pLineInfo->m_dI2_Before);
            //故障开始后一周波(电压电流有效值、峰值等)
            ncal = nStartFault_1;
            if(ncal > m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount)
            {
                ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints;
            }
            a_pLineInfo->m_pVolRms_After[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[0],1);
            m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_After[0]);
            a_pLineInfo->m_pVolRms_After[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[1],1);
            m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_After[1]);
            a_pLineInfo->m_pVolRms_After[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[2],1);
            m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_After[2]);
            if(pUn != NULL)
                a_pLineInfo->m_pVolRms_After[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_After[3],1);
            a_pLineInfo->m_pVolMax_After[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_After[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_After[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
            if(pUn != NULL)
                a_pLineInfo->m_pVolMax_After[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa,pUb,pUc,ncal,nWavePoints,0,a_pLineInfo->m_dU0_After,a_pLineInfo->m_dU1_After,a_pLineInfo->m_dU2_After);
            a_pLineInfo->m_pInfRms_After[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[0],1);
            m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_After[0]);
            a_pLineInfo->m_pInfRms_After[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[1],1);
            m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_After[1]);
            a_pLineInfo->m_pInfRms_After[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[2],1);
            m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_After[2]);
            a_pLineInfo->m_pInfRms_After[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_After[3],1);
            a_pLineInfo->m_pInfMax_After[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_After[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_After[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_After[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa,pIb,pIc,ncal,nWavePoints,0,a_pLineInfo->m_dI0_After,a_pLineInfo->m_dI1_After,a_pLineInfo->m_dI2_After);
            //故障后一周波最大电流
            a_pLineInfo->m_dMaxFaultInf_two = a_pLineInfo->m_pInfRms_After[0];
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_After[1]);
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_After[2]);
//			a_pLineInfo->m_dMaxFaultInf_two = max(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_After[3]);
            if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_After[0]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_After[1]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_After[2]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel->m_chName);
            }
            a_pLineInfo->m_dMinFaultVol_two = a_pLineInfo->m_pVolRms_After[0];
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_After[1]);
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_After[2]);
//			a_pLineInfo->m_dMinFaultVol_two = min(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_After[3]);
            if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_After[0]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pAChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_After[1]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pBChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_After[2]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pCChanel->m_chName);
            }
            //获取一次值
            a_pLineInfo->m_dMaxFaultInf_one = (float)(a_pLineInfo->m_dMaxFaultInf_two * m_pCmtd->m_arLine[a_nLineIndex]->m_dCT/1000.0);
            a_pLineInfo->m_dMinFaultVol_one = (float)(a_pLineInfo->m_dMinFaultVol_two * m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_dVoltage*10.0/1000.0);

            //故障开始后第二周波(电压电流有效值、峰值等)
            ncal += nWavePoints;
            if(ncal+nWavePoints > m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount)
            {
                ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints;
            }
            a_pLineInfo->m_pVolRms_Over[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[0],1);
            m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_Over[0]);
            a_pLineInfo->m_pVolRms_Over[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[1],1);
            m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_Over[1]);
            a_pLineInfo->m_pVolRms_Over[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[2],1);
            m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_Over[2]);
            if(pUn != NULL)
                a_pLineInfo->m_pVolRms_Over[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_Over[3],1);
            a_pLineInfo->m_pVolMax_Over[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_Over[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
            a_pLineInfo->m_pVolMax_Over[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
            if(pUn != NULL)
                a_pLineInfo->m_pVolMax_Over[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usUID,pUa,pUb,pUc,ncal,nWavePoints,0,a_pLineInfo->m_dU0_Over,a_pLineInfo->m_dU1_Over,a_pLineInfo->m_dU2_Over);
            a_pLineInfo->m_pInfRms_Over[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[0],1);
            m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_Over[0]);
            a_pLineInfo->m_pInfRms_Over[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[1],1);
            m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_Over[1]);
            a_pLineInfo->m_pInfRms_Over[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[2],1);
            m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_Over[2]);
            a_pLineInfo->m_pInfRms_Over[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_Over[3],1);
            a_pLineInfo->m_pInfMax_Over[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Over[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Over[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
            a_pLineInfo->m_pInfMax_Over[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
            m_wyCal.Cal_XFL(m_pCmtd,usIID,pIa,pIb,pIc,ncal,nWavePoints,0,a_pLineInfo->m_dI0_Over,a_pLineInfo->m_dI1_Over,a_pLineInfo->m_dI2_Over);
            //故障后两周波最大电流
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[0]);
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[1]);
            a_pLineInfo->m_dMaxFaultInf_two = fmax(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[2]);
//			a_pLineInfo->m_dMaxFaultInf_two = max(a_pLineInfo->m_dMaxFaultInf_two,a_pLineInfo->m_pInfRms_Over[3]);
            if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_Over[0]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_Over[1]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMaxFaultInf_two-a_pLineInfo->m_pInfRms_Over[2]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chInfChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel->m_chName);
            }
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[0]);
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[1]);
            a_pLineInfo->m_dMinFaultVol_two = fmin(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[2]);
//			a_pLineInfo->m_dMinFaultVol_two = min(a_pLineInfo->m_dMinFaultVol_two,a_pLineInfo->m_pVolRms_Over[3]);
            if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_Over[0]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pAChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_Over[1]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pBChanel->m_chName);
            }
            else if(fabs(a_pLineInfo->m_dMinFaultVol_two - a_pLineInfo->m_pVolRms_Over[2]) < 0.1)
            {
                strcpy(a_pLineInfo->m_chVolChanel,m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_pCChanel->m_chName);
            }
            //获取一次值
            a_pLineInfo->m_dMaxFaultInf_one = (float)(a_pLineInfo->m_dMaxFaultInf_two * m_pCmtd->m_arLine[a_nLineIndex]->m_dCT/1000.0);
            a_pLineInfo->m_dMinFaultVol_one = (float)(a_pLineInfo->m_dMinFaultVol_two * m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_dVoltage*10.0/1000.0);
        }//if(bSucess)

        //////////////////////////////////////////////////////////////////////////
        //2010-10-28 针对副母计算距离II
        //[[
        ncalpos = ndetpos;
        CEleBus* pBusII = NULL;
        float dang = 0;
        float* pUa_Data = NULL;
        double dvoltage = m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_dVoltage;
        for(int nb=0; nb<m_pCmtd->m_arBus.count(); nb++)
        {
            if((m_pCmtd->m_arBus[nb]->m_wAID<=0)||(m_pCmtd->m_arBus[nb]->m_wBID<=0)||(m_pCmtd->m_arBus[nb]->m_wCID<=0))
            {
                continue;
            }
            pUa_Data = m_pCmtd->m_arBus[nb]->m_pAChanel->m_pData.data();
            //////////////////////////////////////////////////////////////////////////
            //2010-11-01 添加
            //为不影响选线逻辑,这里如果第二母线未运行,不计算
            //母线必须处于投运状态(判定方法为计算Ua第一个点有效值)
            //[[
            if(m_wyCal.Cal_Rms_Result(pUa_Data,0,m_pCmtd->m_pSegment[0].m_nWavePoints,dang) < 30)
            {
                continue;
            }
            //]]
            if((fabs(m_pCmtd->m_arBus[nb]->m_dVoltage-dvoltage)<15.)&&(m_pCmtd->m_arBus[nb]->m_wAID!=m_pCmtd->m_arLine[a_nLineIndex]->m_pBus->m_wAID))
            {
                pBusII = m_pCmtd->m_arBus[nb];
                break;
            }
        }

        if(pBusII != NULL)
        {
            float *pUaII = pBusII->m_pAChanel->m_pData.data();
            float *pUbII = pBusII->m_pBChanel->m_pData.data();
            float *pUcII = pBusII->m_pCChanel->m_pData.data();
            pDataU3[0] = pUaII;
            pDataU3[1] = pUbII;
            pDataU3[2] = pUcII;
            bSucess = false;
            strcpy(a_pLineInfo->m_chBusII_Name,pBusII->m_chName);

            ncalpos = nStartFault_1;
            if(pHgI0 == NULL)
            {
                if(Dist_CalDistance3(pDataU3,pDataI4,ncalpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
                else if(Dist_CalDistance3(pDataU3,pDataI4,ncalpos+ndetpos,nabSample,dRX,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
            }
            else
            {
                if(Dist_CalDistance3_ext(pDataU3,pDataI4,pHgI0,ncalpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
                else if(Dist_CalDistance3_ext(pDataU3,pDataI4,pHgI0,ncalpos+ndetpos,nabSample,dRX,dRXM,nFaultPharse,dr,dx,fLineX))
                {
                    bSucess = true;
                }
            }
            if(bSucess)
            {                 
                //2020-10-13 超出范围，强制修正(故障)[[
                if(bMFault)
                {
                    if((dx>fLineX)||(dx<0))
                    {
                        double dfc = 0.99+fRandm(1000)/100.;
                        dr = fLineR*dfc;
                        dx = fLineX*dfc;
                    }
                }
                //]]
                a_pLineInfo->m_dDistanceII = (float)(dx*dFactor/dx1);
            }
        }
        //]]
    }
    /*
    if((bReFault)&&((dFaultDistance>=-5)&&(dFaultDistance<=dLineLength*1.1)))
    {
        float dlasttime = (float)((m_pCmtd->m_pSampleTime[nEndFault_2] - m_pCmtd->m_pSampleTime[nStartFault_2])/1000.);
        int ndetpos = (int)(0.25*20*nabSample/20);	//1/4周波
        int ncalpos = ndetpos;							//计算开始位置,默认相对于突变点1/4周波
        float dr = 0.0;	//短路电阻
        float dx = 0.0;	//短路电抗
        bool bSucess = false;
        Q_UNUSED(dr);
        Q_UNUSED(dx);
        Q_UNUSED(bSucess);
        if(dlasttime >= 55)	////持续时间大于等于3周波就从3/4周波处计算阻抗??
        {
            ncalpos *= 3;	//3/4周波
            ncalpos += nStartFault_2;
        }
        else
        {
            ncalpos += nStartFault_2;
        }
        a_pLineInfo->m_bReFault = true;
        float dTimeDecrease = Dist_CalDeltaT(pIa+ncalpos,pIb+ncalpos,pIc+ncalpos,20,nReFaultPharse);
        a_pLineInfo->m_nFaultType_ReF = nReFaultPharse;
        a_pLineInfo->m_dDeltaT_ReF = dTimeDecrease;
        a_pLineInfo->m_nStartPoint_ReF = nStartFault_2;
        a_pLineInfo->m_nEndPoint_ReF = nEndFault_2;

//		TRACE("再次故障开始时间: %g(毫秒),故障结束时间: %g(毫秒),衰减时间常数: %g(毫秒),距离:%g(公里)\n",dstart,dend,dTimeDecrease,dDistance);

        int nseg = m_pCmtd->GetCurSeg(nStartFault_2);
        int nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
        int ncal = 0;
        //开始后一周波数据
        ncal = nStartFault_2;
        if(ncal > m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount)
        {
            ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints;
        }
        a_pLineInfo->m_pVolRms_ReF_After[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_After[0],1);
        m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_ReF_After[0]);
        a_pLineInfo->m_pVolRms_ReF_After[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_After[1],1);
        m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_ReF_After[1]);
        a_pLineInfo->m_pVolRms_ReF_After[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_After[2],1);
        m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_ReF_After[2]);
        if(pUn != NULL)
            a_pLineInfo->m_pVolRms_ReF_After[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_After[3],1);
        a_pLineInfo->m_pVolMax_ReF_After[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
        a_pLineInfo->m_pVolMax_ReF_After[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
        a_pLineInfo->m_pVolMax_ReF_After[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
        if(pUn != NULL)
            a_pLineInfo->m_pVolMax_ReF_After[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
        a_pLineInfo->m_pInfRms_ReF_After[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_After[0],1);
        m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_ReF_After[0]);
        a_pLineInfo->m_pInfRms_ReF_After[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_After[1],1);
        m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_ReF_After[1]);
        a_pLineInfo->m_pInfRms_ReF_After[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_After[2],1);
        m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_ReF_After[2]);
        a_pLineInfo->m_pInfRms_ReF_After[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_After[3],1);
        a_pLineInfo->m_pInfMax_ReF_After[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_After[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_After[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_After[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
        //故障后第二周波(电压电流有效值、峰值等)
        ncal += nWavePoints;
        if(ncal+nWavePoints > m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount)
        {
            ncal = m_pCmtd->m_pSegment[nseg].m_nStartPos+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints;
        }
        a_pLineInfo->m_pVolRms_ReF_Over[0] = m_wyCal.Cal_Rms_Result(pUa,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_Over[0],1);
        m_pCmtd->ParamPhase(usUID[0],a_pLineInfo->m_pVolAng_ReF_Over[0]);
        a_pLineInfo->m_pVolRms_ReF_Over[1] = m_wyCal.Cal_Rms_Result(pUb,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_Over[1],1);
        m_pCmtd->ParamPhase(usUID[1],a_pLineInfo->m_pVolAng_ReF_Over[1]);
        a_pLineInfo->m_pVolRms_ReF_Over[2] = m_wyCal.Cal_Rms_Result(pUc,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_Over[2],1);
        m_pCmtd->ParamPhase(usUID[2],a_pLineInfo->m_pVolAng_ReF_Over[2]);
        if(pUn != NULL)
            a_pLineInfo->m_pVolRms_ReF_Over[3] = m_wyCal.Cal_Rms_Result(pUn,ncal,nWavePoints,a_pLineInfo->m_pVolAng_ReF_Over[3],1);
        a_pLineInfo->m_pVolMax_ReF_Over[0] = m_wyCal.GetMaxValue(pUa,ncal,nWavePoints);
        a_pLineInfo->m_pVolMax_ReF_Over[1] = m_wyCal.GetMaxValue(pUb,ncal,nWavePoints);
        a_pLineInfo->m_pVolMax_ReF_Over[2] = m_wyCal.GetMaxValue(pUc,ncal,nWavePoints);
        if(pUn != NULL)
            a_pLineInfo->m_pVolMax_ReF_Over[3] = m_wyCal.GetMaxValue(pUn,ncal,nWavePoints);
        a_pLineInfo->m_pInfRms_ReF_Over[0] = m_wyCal.Cal_Rms_Result(pIa,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_Over[0],1);
        m_pCmtd->ParamPhase(usIID[0],a_pLineInfo->m_pInfAng_ReF_Over[0]);
        a_pLineInfo->m_pInfRms_ReF_Over[1] = m_wyCal.Cal_Rms_Result(pIb,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_Over[1],1);
        m_pCmtd->ParamPhase(usIID[1],a_pLineInfo->m_pInfAng_ReF_Over[1]);
        a_pLineInfo->m_pInfRms_ReF_Over[2] = m_wyCal.Cal_Rms_Result(pIc,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_Over[2],1);
        m_pCmtd->ParamPhase(usIID[2],a_pLineInfo->m_pInfAng_ReF_Over[2]);
        a_pLineInfo->m_pInfRms_ReF_Over[3] = m_wyCal.Cal_Rms_Result(pIn,ncal,nWavePoints,a_pLineInfo->m_pInfAng_ReF_Over[3],1);
        a_pLineInfo->m_pInfMax_ReF_Over[0] = m_wyCal.GetMaxValue(pIa,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_Over[1] = m_wyCal.GetMaxValue(pIb,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_Over[2] = m_wyCal.GetMaxValue(pIc,ncal,nWavePoints);
        a_pLineInfo->m_pInfMax_ReF_Over[3] = m_wyCal.GetMaxValue(pIn,ncal,nWavePoints);
    }
    */

    delete []pIn_ex;
    if(pHgI0 != NULL)
        delete []pHgI0;
    if(bAllocIa)
    {
        delete []pIa;
    }
    if(bAllocIb)
    {
        delete []pIb;
    }
    if(bAllocIc)
    {
        delete []pIc;
    }
    if(bFault)
    {
        return true;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 分析一条线路,保存结果
//参	数:
//a_nLineIndex 线路序号，从0开始
//a_nFaultPos  计算点开始位置
//a_nFaultType 故障类型
//              FAULT_NONE = 0,FAULT_AN = 1,
//              FAULT_BN = 2,
//              FAULT_CN = 3,
//              FAULT_AB = 4,
//              FAULT_BC = 5,
//              FAULT_CA = 6,
//              FAULT_ABN = 7,
//              FAULT_BCN = 8,
//              FAULT_CAN = 9,
//              FAULT_ABC = 10,
//              FAULT_OVER = 11,
//              FAULT_NOTDF = 12
//返 回	值:
//备	注:
//创建日期: 20010-09-26		wpf
//修改记录:
//////////////////////////////////////////////////////////////////////////
bool CGenerateReport::AnalysisLine_manual(int a_nLineIndex, int a_nFaultPos, int a_nFaultType)
{
    GenerateBasicInfo();	//获取基本信息
    GenerateSwitchList();	//获取开关动作时序
    m_nTbLineCount = 0;

    m_arLineInfo[m_nTbLineCount].m_bFault = false;
    m_arLineInfo[m_nTbLineCount].InitData();
    m_arLineInfo[m_nTbLineCount].m_nLineIndex = a_nLineIndex;
    if((m_pCmtd->m_arLine[a_nLineIndex]->m_pBus==NULL)||(m_pCmtd->m_arLine[a_nLineIndex]->m_pAChanel==NULL)||(m_pCmtd->m_arLine[a_nLineIndex]->m_pCChanel == NULL))
    {
        return false;
    }
    //首先选相测距(a_nLineIndex,&(m_arLineInfo[m_nTbLineCount]));
    bool btb = AnalysisLine_manual(a_nLineIndex,a_nFaultPos,a_nFaultType,&(m_arLineInfo[m_nTbLineCount]));
    if(btb)
    {
        m_nTbLineCount++;
    }
    else	//本线路是否有开关动作
    {
        bool bSwitch = false;
        for(int i=0; i<m_SwitchList.m_arStatus.count(); i++)
        {
            for(int n=0; n<m_pCmtd->m_arLine[a_nLineIndex]->m_arDChanel.count(); n++)
            {
                if(m_pCmtd->m_arLine[a_nLineIndex]->m_arDChanel[n] == m_SwitchList.m_arStatus[i].m_wID)
                {
                    bSwitch = true;
                    break;
                }
            }
            if(bSwitch)
            {
                break;
            }
        }
        if(bSwitch)
        {
            IsLines_Inf_Overflow(&(m_arLineInfo[m_nTbLineCount]),m_pCmtd->m_arLine[a_nLineIndex]);
            GetLineValue_Cyc(&(m_arLineInfo[m_nTbLineCount]),m_pCmtd->m_arLine[a_nLineIndex]);
            m_nTbLineCount++;
        }
    }
    //本线路是否有电流突变
    if(m_nTbLineCount <= 0)
    {
        m_arLineInfo[m_nTbLineCount].m_bFault = false;
        m_arLineInfo[m_nTbLineCount].InitData();
        m_arLineInfo[m_nTbLineCount].m_nLineIndex = a_nLineIndex;
        if(IsLines_Inf_Overflow(&(m_arLineInfo[m_nTbLineCount]),m_pCmtd->m_arLine[a_nLineIndex]))
        {
            GetLineValue_Cyc(&(m_arLineInfo[m_nTbLineCount]),m_pCmtd->m_arLine[a_nLineIndex]);
            m_nTbLineCount++;

        }
    }

    //选相失败、无开关动作、无电流突变，报告内容为空
    if((!btb)&&(m_nTbLineCount <= 0))
    {
        return false;
    }

    //-------------------------------------------------------------------
    //进行一次合理性分析
    //-------------------------------------------------------------------
//    bool bFault = false;
    int nFaultLine = m_arLineInfo[0].m_nLineIndex;
    int nStartIndex = 0;
    float dLineLength = m_pCmtd->m_arLine[nFaultLine]->m_dLength;
    float dDistanceI = m_arLineInfo[0].m_dDistanceI;
    float dDistanceII = m_arLineInfo[0].m_dDistanceII;
    float dStartTime = (float)(m_pCmtd->m_pSampleTime[m_arLineInfo[nStartIndex].m_nStartPoint]/1000.0);
    float dTimeLong = (float)(m_pCmtd->m_pSampleTime[m_arLineInfo[nStartIndex].m_nEndPoint]/1000.0);
    dTimeLong -= dStartTime;
    // 如果是-5以内的负数,认为合理 [1/23/2008]
    if((dDistanceI<0)&&(dDistanceI>-5))
    {
        dDistanceI = -dDistanceI;
        m_arLineInfo[0].m_dDistanceI = dDistanceI;
    }
    if((dDistanceII<0)&&(dDistanceII>-5))
    {
        dDistanceII = -dDistanceII;
        m_arLineInfo[0].m_dDistanceII = dDistanceII;
    }

    if((dDistanceI>=0)&&(dDistanceI <= 1.5*dLineLength)&&(dTimeLong > 0.0001)&&(dLineLength > 0.5))
    {
//        bFault = true;
        m_arLineInfo[nStartIndex].m_bFault = true;
    }
    if((dDistanceII>=0)&&(dDistanceII <= 1.5*dLineLength)&&(dTimeLong > 0.0001)&&(dLineLength > 0.5))
    {
//        bFault = true;
        m_arLineInfo[nStartIndex].m_bFault = true;
    }


    m_pFaultLine = &(m_arLineInfo[nStartIndex]);

    //-------------------------------------------------------------------------
    //整理开关量信息,去掉不是本线路的开关信息
    //-------------------------------------------------------------------------
    bool bCorrect = false;
    int nSize = m_SwitchList.m_arStatus.count();
    for(int i=nSize-1; i>=0; i--)
    {
        bCorrect = false;
        for(int j=0; j<m_pCmtd->m_arLine[nFaultLine]->m_arDChanel.count(); j++)
        {
            if(m_SwitchList.m_arStatus[i].m_wID == m_pCmtd->m_arLine[nFaultLine]->m_arDChanel[j])
            {
                bCorrect = true;
                break;
            }
        }
        if(!bCorrect)
        {
            m_SwitchList.m_arStatus.remove(i);
        }
    }
//    m_SwitchList.m_arStatus.FreeExtra();

    return true;
}

bool CGenerateReport::AnalysisTrans(int a_nTransIndex,bool& bOverFlow)
{
    InitData();
    GenerateBasicInfo();	//获取基本信息
    GenerateSwitchList();	//获取开关动作时序

    if((a_nTransIndex<0)||(a_nTransIndex>=m_pCmtd->m_arTrans.count()))
    {
        return false;
    }

    int nPoints = m_pCmtd->m_nTotalPoints;		//采样点数目
    float* pDeltaIa = new float[nPoints];			//A相差流
    float* pDeltaIb = new float[nPoints];			//B相差流
    float* pDeltaIc = new float[nPoints];			//C相差流

    float dData[20] = {0};		//各侧数据
    int nNum = 0;				//共有几侧
    float dFactor[20] = {0};	//平衡系数
    int nType[20] = {0};		//接线方式

    float dMaxDeltaI = 0;
    m_nTbTransCount = 0;
    int nIndex = 0;
    CEleTrans* pTrans = m_pCmtd->m_arTrans[a_nTransIndex];

    nNum = 0;
    bOverFlow = false;
    dMaxDeltaI = 0.8/*pTrans->m_dDeltaI*/;	//差流启动值
    //---------------------------------------------------------
    //首先获取各侧基本参数
    //---------------------------------------------------------
    if(pTrans->m_pLine[0] != NULL)
    {
        nNum++;
        dFactor[0] = pTrans->m_dFactor[0];	//I侧平衡系数
        nType[0] = pTrans->m_nType[0];		//I侧接线方式
        m_dParamab[0] = pTrans->m_pLine[0]->m_pAChanel->m_da;
        m_dParamab[1] = pTrans->m_pLine[0]->m_pAChanel->m_db;
        m_dParamab[2] = pTrans->m_pLine[0]->m_pBChanel->m_da;
        m_dParamab[3] = pTrans->m_pLine[0]->m_pBChanel->m_db;
        m_dParamab[4] = pTrans->m_pLine[0]->m_pCChanel->m_da;
        m_dParamab[5] = pTrans->m_pLine[0]->m_pCChanel->m_db;
    }
    if(pTrans->m_pLine[1] != NULL)
    {
        nNum++;
        dFactor[1] = pTrans->m_dFactor[1];	//II侧..
        nType[1] = pTrans->m_nType[1];		//II侧..
    }
    if(pTrans->m_pLine[2] != NULL)		//III侧..
    {
        nNum++;
        dFactor[2] = pTrans->m_dFactor[2];
        nType[2] = pTrans->m_nType[2];

    }
    if(pTrans->m_pLine[3] != NULL)		//IV侧..
    {
        nNum++;
        dFactor[3] = pTrans->m_dFactor[3];
        nType[3] = pTrans->m_nType[3];
    }
    //---------------------------------------------------------------------
    //计算差流瞬时值.为提高效率,这里分三种情况各自循环计算
    //2010-04-24 修改
    //这里的差流计算之前忘记考虑电流反相了
    //---------------------------------------------------------------------
    if(nNum == 2)
    {
        for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
        {
            dData[0] = pTrans->m_pLine[0]->m_pAChanel->m_pData[n];
            dData[1] = pTrans->m_pLine[0]->m_pBChanel->m_pData[n];
            dData[2] = pTrans->m_pLine[0]->m_pCChanel->m_pData[n];

            dData[3] = pTrans->m_pLine[1]->m_pAChanel->m_pData[n];
            dData[4] = pTrans->m_pLine[1]->m_pBChanel->m_pData[n];
            dData[5] = pTrans->m_pLine[1]->m_pCChanel->m_pData[n];
            /*
            dData[0] = (pTrans->m_pLine[0]->m_pAChanel->m_pData[n]-pTrans->m_pLine[0]->m_pAChanel->m_db)/pTrans->m_pLine[0]->m_pAChanel->m_da;
            dData[1] = (pTrans->m_pLine[0]->m_pBChanel->m_pData[n]-pTrans->m_pLine[0]->m_pBChanel->m_db)/pTrans->m_pLine[0]->m_pBChanel->m_da;
            dData[2] = (pTrans->m_pLine[0]->m_pCChanel->m_pData[n]-pTrans->m_pLine[0]->m_pCChanel->m_db)/pTrans->m_pLine[0]->m_pCChanel->m_da;

            dData[3] = (pTrans->m_pLine[1]->m_pAChanel->m_pData[n]-pTrans->m_pLine[1]->m_pAChanel->m_db)/pTrans->m_pLine[1]->m_pAChanel->m_da;
            dData[4] = (pTrans->m_pLine[1]->m_pBChanel->m_pData[n]-pTrans->m_pLine[1]->m_pBChanel->m_db)/pTrans->m_pLine[1]->m_pBChanel->m_da;
            dData[5] = (pTrans->m_pLine[1]->m_pCChanel->m_pData[n]-pTrans->m_pLine[1]->m_pCChanel->m_db)/pTrans->m_pLine[1]->m_pCChanel->m_da;
            */
            if(pTrans->m_bInvert[0])
            {
                dData[0] = -dData[0];
                dData[1] = -dData[1];
                dData[2] = -dData[2];
            }
            if(pTrans->m_bInvert[1])
            {
                dData[3] = -dData[3];
                dData[4] = -dData[4];
                dData[5] = -dData[5];
            }
            pDeltaIa[n] = m_wyCal.Formula_Fun_DeltaId(0,nNum,dData,dFactor,nType);
            pDeltaIb[n] = m_wyCal.Formula_Fun_DeltaId(1,nNum,dData,dFactor,nType);
            pDeltaIc[n] = m_wyCal.Formula_Fun_DeltaId(2,nNum,dData,dFactor,nType);
        }
    }
    else if(nNum == 3)
    {
        for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
        {
            dData[0] = pTrans->m_pLine[0]->m_pAChanel->m_pData[n];
            dData[1] = pTrans->m_pLine[0]->m_pBChanel->m_pData[n];
            dData[2] = pTrans->m_pLine[0]->m_pCChanel->m_pData[n];
            dData[3] = pTrans->m_pLine[1]->m_pAChanel->m_pData[n];
            dData[4] = pTrans->m_pLine[1]->m_pBChanel->m_pData[n];
            dData[5] = pTrans->m_pLine[1]->m_pCChanel->m_pData[n];
            dData[6] = pTrans->m_pLine[2]->m_pAChanel->m_pData[n];
            dData[7] = pTrans->m_pLine[2]->m_pBChanel->m_pData[n];
            dData[8] = pTrans->m_pLine[2]->m_pCChanel->m_pData[n];
            /*
            dData[0] = (pTrans->m_pLine[0]->m_pAChanel->m_pData[n]-pTrans->m_pLine[0]->m_pAChanel->m_db)/pTrans->m_pLine[0]->m_pAChanel->m_da;
            dData[1] = (pTrans->m_pLine[0]->m_pBChanel->m_pData[n]-pTrans->m_pLine[0]->m_pBChanel->m_db)/pTrans->m_pLine[0]->m_pBChanel->m_da;
            dData[2] = (pTrans->m_pLine[0]->m_pCChanel->m_pData[n]-pTrans->m_pLine[0]->m_pCChanel->m_db)/pTrans->m_pLine[0]->m_pCChanel->m_da;
            dData[3] = (pTrans->m_pLine[1]->m_pAChanel->m_pData[n]-pTrans->m_pLine[1]->m_pAChanel->m_db)/pTrans->m_pLine[1]->m_pAChanel->m_da;
            dData[4] = (pTrans->m_pLine[1]->m_pBChanel->m_pData[n]-pTrans->m_pLine[1]->m_pBChanel->m_db)/pTrans->m_pLine[1]->m_pBChanel->m_da;
            dData[5] = (pTrans->m_pLine[1]->m_pCChanel->m_pData[n]-pTrans->m_pLine[1]->m_pCChanel->m_db)/pTrans->m_pLine[1]->m_pCChanel->m_da;
            dData[6] = (pTrans->m_pLine[2]->m_pAChanel->m_pData[n]-pTrans->m_pLine[2]->m_pAChanel->m_db)/pTrans->m_pLine[2]->m_pAChanel->m_da;
            dData[7] = (pTrans->m_pLine[2]->m_pBChanel->m_pData[n]-pTrans->m_pLine[2]->m_pBChanel->m_db)/pTrans->m_pLine[2]->m_pBChanel->m_da;
            dData[8] = (pTrans->m_pLine[2]->m_pCChanel->m_pData[n]-pTrans->m_pLine[2]->m_pCChanel->m_db)/pTrans->m_pLine[2]->m_pCChanel->m_da;
            */
            if(pTrans->m_bInvert[0])
            {
                dData[0] = -dData[0];
                dData[1] = -dData[1];
                dData[2] = -dData[2];
            }
            if(pTrans->m_bInvert[1])
            {
                dData[3] = -dData[3];
                dData[4] = -dData[4];
                dData[5] = -dData[5];
            }
            if(pTrans->m_bInvert[2])
            {
                dData[6] = -dData[6];
                dData[7] = -dData[7];
                dData[8] = -dData[8];
            }
            pDeltaIa[n] = m_wyCal.Formula_Fun_DeltaId(0,nNum,dData,dFactor,nType);
            pDeltaIb[n] = m_wyCal.Formula_Fun_DeltaId(1,nNum,dData,dFactor,nType);
            pDeltaIc[n] = m_wyCal.Formula_Fun_DeltaId(2,nNum,dData,dFactor,nType);
        }
    }
    else if(nNum == 4)
    {
        for(int n=0; n<m_pCmtd->m_nTotalPoints; n++)
        {
            dData[0] = pTrans->m_pLine[0]->m_pAChanel->m_pData[n];
            dData[1] = pTrans->m_pLine[0]->m_pBChanel->m_pData[n];
            dData[2] = pTrans->m_pLine[0]->m_pCChanel->m_pData[n];
            dData[3] = pTrans->m_pLine[1]->m_pAChanel->m_pData[n];
            dData[4] = pTrans->m_pLine[1]->m_pBChanel->m_pData[n];
            dData[5] = pTrans->m_pLine[1]->m_pCChanel->m_pData[n];
            dData[6] = pTrans->m_pLine[2]->m_pAChanel->m_pData[n];
            dData[7] = pTrans->m_pLine[2]->m_pBChanel->m_pData[n];
            dData[8] = pTrans->m_pLine[2]->m_pCChanel->m_pData[n];
            dData[9] = pTrans->m_pLine[3]->m_pAChanel->m_pData[n];
            dData[10] = pTrans->m_pLine[3]->m_pBChanel->m_pData[n];
            dData[11] = pTrans->m_pLine[3]->m_pCChanel->m_pData[n];
            /*
            dData[0] = (pTrans->m_pLine[0]->m_pAChanel->m_pData[n]-pTrans->m_pLine[0]->m_pAChanel->m_db)/pTrans->m_pLine[0]->m_pAChanel->m_da;
            dData[1] = (pTrans->m_pLine[0]->m_pBChanel->m_pData[n]-pTrans->m_pLine[0]->m_pBChanel->m_db)/pTrans->m_pLine[0]->m_pBChanel->m_da;
            dData[2] = (pTrans->m_pLine[0]->m_pCChanel->m_pData[n]-pTrans->m_pLine[0]->m_pCChanel->m_db)/pTrans->m_pLine[0]->m_pCChanel->m_da;
            dData[3] = (pTrans->m_pLine[1]->m_pAChanel->m_pData[n]-pTrans->m_pLine[1]->m_pAChanel->m_db)/pTrans->m_pLine[1]->m_pAChanel->m_da;
            dData[4] = (pTrans->m_pLine[1]->m_pBChanel->m_pData[n]-pTrans->m_pLine[1]->m_pBChanel->m_db)/pTrans->m_pLine[1]->m_pBChanel->m_da;
            dData[5] = (pTrans->m_pLine[1]->m_pCChanel->m_pData[n]-pTrans->m_pLine[1]->m_pCChanel->m_db)/pTrans->m_pLine[1]->m_pCChanel->m_da;
            dData[6] = (pTrans->m_pLine[2]->m_pAChanel->m_pData[n]-pTrans->m_pLine[2]->m_pAChanel->m_db)/pTrans->m_pLine[2]->m_pAChanel->m_da;
            dData[7] = (pTrans->m_pLine[2]->m_pBChanel->m_pData[n]-pTrans->m_pLine[2]->m_pBChanel->m_db)/pTrans->m_pLine[2]->m_pBChanel->m_da;
            dData[8] = (pTrans->m_pLine[2]->m_pCChanel->m_pData[n]-pTrans->m_pLine[2]->m_pCChanel->m_db)/pTrans->m_pLine[2]->m_pCChanel->m_da;
            dData[9] = (pTrans->m_pLine[3]->m_pAChanel->m_pData[n]-pTrans->m_pLine[3]->m_pAChanel->m_db)/pTrans->m_pLine[3]->m_pAChanel->m_da;
            dData[10] = (pTrans->m_pLine[3]->m_pBChanel->m_pData[n]-pTrans->m_pLine[3]->m_pBChanel->m_db)/pTrans->m_pLine[3]->m_pBChanel->m_da;
            dData[11] = (pTrans->m_pLine[3]->m_pCChanel->m_pData[n]-pTrans->m_pLine[3]->m_pCChanel->m_db)/pTrans->m_pLine[3]->m_pCChanel->m_da;
            */
            if(pTrans->m_bInvert[0])
            {
                dData[0] = -dData[0];
                dData[1] = -dData[1];
                dData[2] = -dData[2];
            }
            if(pTrans->m_bInvert[1])
            {
                dData[3] = -dData[3];
                dData[4] = -dData[4];
                dData[5] = -dData[5];
            }
            if(pTrans->m_bInvert[2])
            {
                dData[6] = -dData[6];
                dData[7] = -dData[7];
                dData[8] = -dData[8];
            }
            if(pTrans->m_bInvert[3])
            {
                dData[9] = -dData[9];
                dData[10] = -dData[10];
                dData[11] = -dData[11];
            }
            pDeltaIa[n] = m_wyCal.Formula_Fun_DeltaId(0,nNum,dData,dFactor,nType);
            pDeltaIb[n] = m_wyCal.Formula_Fun_DeltaId(1,nNum,dData,dFactor,nType);
            pDeltaIc[n] = m_wyCal.Formula_Fun_DeltaId(2,nNum,dData,dFactor,nType);
        }
    }
    //----------------------------------------------------------------------
    //判断是否有差流越限,如果有则给出差流和差流的二次谐波含量
    //----------------------------------------------------------------------
    float dAng = 0;
    int    nWavePoints = 20;
    int nstart = 0;
    int nend = 0;
    int nFaultStartPos = m_pCmtd->m_nTbPos;
    m_arTransInfo[nIndex].m_wPhase = 0;
    for(int nseg = 0; nseg<m_pCmtd->m_nSegCount; nseg++)
    {
        nWavePoints = m_pCmtd->m_pSegment[nseg].m_nWavePoints;
        //C、D段不判
        if(nWavePoints < 20)
        {
            continue;
        }
        nstart = m_pCmtd->m_pSegment[nseg].m_nStartPos;
        nend = nstart+m_pCmtd->m_pSegment[nseg].m_nCount-nWavePoints-4;
        for(int n=nstart; n<nend; n+=nWavePoints/4)
        {
            if(m_wyCal.Cal_Rms_Result(pDeltaIa,n,nWavePoints,dAng,1) >= dMaxDeltaI)
            {
                bOverFlow = true;
                nFaultStartPos = n+nWavePoints;
                if(nFaultStartPos > nend-nWavePoints)
                {
                    nFaultStartPos = nend-nWavePoints;
                }
                m_arTransInfo[nIndex].m_wPhase |= 0x01;	//A相
                break;
            }
            if(m_wyCal.Cal_Rms_Result(pDeltaIb,n,nWavePoints,dAng,1) >= dMaxDeltaI)
            {
                bOverFlow = true;
                nFaultStartPos = n+nWavePoints;
                if(nFaultStartPos > nend-nWavePoints)
                {
                    nFaultStartPos = nend-nWavePoints;
                }
                m_arTransInfo[nIndex].m_wPhase |= 0x02;	//B..
                break;
            }
            if(m_wyCal.Cal_Rms_Result(pDeltaIc,n,nWavePoints,dAng,1) >= dMaxDeltaI)
            {
                bOverFlow = true;
                nFaultStartPos = n+nWavePoints;
                if(nFaultStartPos > nend-nWavePoints)
                {
                    nFaultStartPos = nend-nWavePoints;
                }
                m_arTransInfo[nIndex].m_wPhase |= 0x04;	//C..
                break;
            }
        }
        if(bOverFlow)
        {
            break;
        }
    }
    m_nFaultPos = nFaultStartPos;

    //判断是否越限
    bool bYx = false;
    if(!bOverFlow)
    {
        unsigned short wId[4] = {0};
        wId[0] = pTrans->m_pLine[0]->m_wID;
        wId[1] = pTrans->m_pLine[1]->m_wID;
        if(nNum > 2)
        {
            wId[2] = pTrans->m_pLine[2]->m_wID;
        }
        if(nNum > 3)
        {
            wId[3] = pTrans->m_pLine[3]->m_wID;
        }
        for(int n=0; n<nNum; n++)
        {
            if(m_pCmtd->m_arLine[n]->m_wID == wId[n])
            {
                bYx = IsLines_Inf_Overflow(&(m_arLineInfo[0]),m_pCmtd->m_arLine[n]);
            }
            if(bYx)
            {
                break;
            }
        }
    }

    if((bOverFlow)||(bYx))	//有差流越限
    {
        int ncurseg = m_pCmtd->GetCurSeg(m_nFaultPos);	//获取突变的段
        int nWavePoints = m_pCmtd->m_pSegment[ncurseg].m_nWavePoints;
        int nStart = m_pCmtd->m_pSegment[ncurseg].m_nStartPos;
        int nEnd = m_pCmtd->m_pSegment[ncurseg].m_nStartPos + m_pCmtd->m_pSegment[ncurseg].m_nCount;

        int nCalposBefore = nFaultStartPos-nWavePoints;			//启动前一周波计算开始点
        int nCalposAfter = nFaultStartPos;						//启动后一周波计算开始点
        int nCalposOver = nFaultStartPos+nWavePoints;			//启动后两周波计算开始点
        if(nCalposBefore < nStart)
        {
            nCalposBefore = nStart;
        }
        float rang = 0;
        if(nCalposAfter+nWavePoints > nEnd)
        {
            nCalposAfter = nEnd - nWavePoints;
        }
        if(nCalposOver+nWavePoints > nEnd)
        {
            nCalposOver = nEnd - nWavePoints;
        }
        m_arTransInfo[nIndex].m_nTransIndex = a_nTransIndex;
        m_arTransInfo[nIndex].m_bFault = true;
        m_arTransInfo[nIndex].m_dIda1_Before = m_wyCal.Cal_Rms_Result(pDeltaIa,nCalposBefore,nWavePoints,rang,1);
        const float dMin_Rms = (float)(0.1);
        if(m_arTransInfo[nIndex].m_dIda1_Before >= dMin_Rms)
        {
            m_arTransInfo[nIndex].m_dIda2_Before = m_wyCal.Cal_Rms_Result(pDeltaIa,nCalposBefore,nWavePoints,rang,2);
        }
        else
        {
            m_arTransInfo[nIndex].m_dIda2_Before = 0;
        }
        m_arTransInfo[nIndex].m_dIdb1_Before = m_wyCal.Cal_Rms_Result(pDeltaIb,nCalposBefore,nWavePoints,rang,1);
        if(m_arTransInfo[nIndex].m_dIdb1_Before > dMin_Rms)
        {
            m_arTransInfo[nIndex].m_dIdb2_Before = m_wyCal.Cal_Rms_Result(pDeltaIb,nCalposBefore,nWavePoints,rang,2);
        }
        else
        {
            m_arTransInfo[nIndex].m_dIdb2_Before = 0;
        }
        m_arTransInfo[nIndex].m_dIdc1_Before = m_wyCal.Cal_Rms_Result(pDeltaIc,nCalposBefore,nWavePoints,rang,1);
        if(m_arTransInfo[nIndex].m_dIdc1_Before > dMin_Rms)
        {
            m_arTransInfo[nIndex].m_dIdc2_Before = m_wyCal.Cal_Rms_Result(pDeltaIc,nCalposBefore,nWavePoints,rang,2);
        }
        else
        {
            m_arTransInfo[nIndex].m_dIdc2_Before = 0;
        }

        m_arTransInfo[nIndex].m_dIda1_After = m_wyCal.Cal_Rms_Result(pDeltaIa,nCalposAfter,nWavePoints,rang,1);
        if(m_arTransInfo[nIndex].m_dIda1_After > dMin_Rms)
        {
            m_arTransInfo[nIndex].m_dIda2_After = m_wyCal.Cal_Rms_Result(pDeltaIa,nCalposAfter,nWavePoints,rang,2);
        }
        else
        {
            m_arTransInfo[nIndex].m_dIda2_After = 0;
        }
        m_arTransInfo[nIndex].m_dIdb1_After = m_wyCal.Cal_Rms_Result(pDeltaIb,nCalposAfter,nWavePoints,rang,1);
        if(m_arTransInfo[nIndex].m_dIdb1_After > dMin_Rms)
        {
            m_arTransInfo[nIndex].m_dIdb2_After = m_wyCal.Cal_Rms_Result(pDeltaIb,nCalposAfter,nWavePoints,rang,2);
        }
        else
        {
            m_arTransInfo[nIndex].m_dIdb2_After = 0;
        }
        m_arTransInfo[nIndex].m_dIdc1_After = m_wyCal.Cal_Rms_Result(pDeltaIc,nCalposAfter,nWavePoints,rang,1);
        if(m_arTransInfo[nIndex].m_dIdc1_After > dMin_Rms)
        {
            m_arTransInfo[nIndex].m_dIdc2_After = m_wyCal.Cal_Rms_Result(pDeltaIc,nCalposAfter,nWavePoints,rang,2);
        }
        else
        {
            m_arTransInfo[nIndex].m_dIdc2_After = 0;
        }
        //--------------------------------------------------------------------------
        //计算故障前一周波和后两周波各侧电压、电流有效值
        //--------------------------------------------------------------------------
        GetFaultValue_Trans(&(m_arTransInfo[nIndex]),pTrans,nCalposBefore,nCalposAfter,nCalposOver,nWavePoints);
        m_pFaultTrans = &(m_arTransInfo[nIndex]);
    }
    else
    {
        m_arTransInfo[nIndex].m_bFault = false;
    }

    //获取主变的最大故障电流和最低故障电压
    m_nTbTransCount = 1;
    GetMaxInf_Trans(0);
    GetMinVol_Trans(0);

    delete []pDeltaIa;
    delete []pDeltaIb;
    delete []pDeltaIc;

    int nTno = m_arTransInfo[0].m_nTransIndex;
    for(int n=0; n<m_pCmtd->m_arLine.count(); n++)
    {
        if(m_pCmtd->m_arLine[n]->m_wID == m_pCmtd->m_arTrans[nTno]->m_pLine[0]->m_wID)
        {
            m_arTransInfo[0].m_pLine[0].m_nLineIndex = n;
        }
        if(m_pCmtd->m_arTrans[nTno]->m_nLineCount > 1)
        {
            if(m_pCmtd->m_arLine[n]->m_wID == m_pCmtd->m_arTrans[nTno]->m_pLine[1]->m_wID)
            {
                m_arTransInfo[0].m_pLine[1].m_nLineIndex = n;
            }
        }
        if(m_pCmtd->m_arTrans[nTno]->m_nLineCount > 2)
        {
            if(m_pCmtd->m_arLine[n]->m_wID == m_pCmtd->m_arTrans[nTno]->m_pLine[2]->m_wID)
            {
                m_arTransInfo[0].m_pLine[2].m_nLineIndex = n;
            }
        }
        if(m_pCmtd->m_arTrans[nTno]->m_nLineCount > 3)
        {
            if(m_pCmtd->m_arLine[n]->m_wID == m_pCmtd->m_arTrans[nTno]->m_pLine[3]->m_wID)
            {
                m_arTransInfo[0].m_pLine[3].m_nLineIndex = n;
            }
        }
    }

    if(m_pFaultTrans == NULL)
    {
        return false;
    }
    m_pFaultTrans->m_bFault = true;
    return true;
}

float CGenerateReport::fRandm(int nMax)
{
    srand((unsigned)time(NULL));
    float fVal = (rand()%nMax)/(nMax*1.0);
    return fVal;
}

bool CGenerateReport::IsFault_A(CEleLine *pLine)
{
    //2018-11-08 修改
    //添加开关量判断(有开关变位4次及以上,认为永久故障)[[
    for(int i=0; i<m_pCmtd->m_arDChanel.count(); i++)
    {
        CEleDChanel* pDChanel = m_pCmtd->m_arDChanel.at(i);
        if(pDChanel->m_nCHG > 3)
        {
            return true;
        }
    }
    //]]

    float* pIa = NULL;
    float* pIb = NULL;
    float* pIc = NULL;
    if(pLine->m_pAChanel != NULL)
        pIa = pLine->m_pAChanel->m_pData.data();
    if(pLine->m_pBChanel != NULL)
        pIb = pLine->m_pBChanel->m_pData.data();
    if(pLine->m_pBChanel != NULL)
        pIc = pLine->m_pCChanel->m_pData.data();

    int nWavePoints = m_pCmtd->m_pSegment[0].m_nWavePoints;
    int nCalPos = 0;
    int i = 0;
    float fValA = 0;
    float fValB = 0;
    float fValC = 0;
    float fAng = 0;
    if(pIa != NULL)
        fValA += m_wyCal.Cal_Rms_Result(pIa,nCalPos,nWavePoints,fAng);
    if(pIb != NULL)
        fValB += m_wyCal.Cal_Rms_Result(pIb,nCalPos,nWavePoints,fAng);
    if(pIc != NULL)
        fValC += m_wyCal.Cal_Rms_Result(pIc,nCalPos,nWavePoints,fAng);

    for(i=m_pCmtd->m_nSegCount-1; i>=0; i--)
    {
        if(m_pCmtd->m_pSegment[i].m_nWavePoints >= 20)
        {
            nWavePoints = m_pCmtd->m_pSegment[i].m_nWavePoints;
            nCalPos = m_pCmtd->m_pSegment[i].m_nStartPos+m_pCmtd->m_pSegment[i].m_nCount-m_pCmtd->m_pSegment[i].m_nWavePoints-20;
            break;
        }
    }

    float fResultA = 0;
    float fResultB = 0;
    float fResultC = 0;

    if(pIa != NULL)
        fResultA += m_wyCal.Cal_Rms_Result(pIa,nCalPos,nWavePoints,fAng);
    if(pIb != NULL)
        fResultB += m_wyCal.Cal_Rms_Result(pIb,nCalPos,nWavePoints,fAng);
    if(pIc != NULL)
        fResultC += m_wyCal.Cal_Rms_Result(pIc,nCalPos,nWavePoints,fAng);

    //判据:故障前后电流值相差>50%为永久性故障
    //2018-11-08修改 改为减少90%并加入fResult<fEpslon
    const float fEpslon = 0.01;
    if((pIa!=NULL)&&(fValA>fEpslon)&&(fResultA<fEpslon))
    {
        if((fValA-fResultA)/fValA > 0.9)
            return true;
    }
    if((pIb!=NULL)&&(fValB>fEpslon)&&(fResultB<fEpslon))
    {
        if((fValB-fResultB)/fValB > 0.9)
            return true;
    }
    if((pIc!=NULL)&&(fValC>fEpslon)&&(fResultC<fEpslon))
    {
        if((fValC-fResultC)/fValC > 0.9)
            return true;
    }

    return false;
}

bool CGenerateReport::GetCHZTime_Switch(CEleLine* pLine,float& a_fTime)
{
    int n=0;
    int i = 0;
    float ftime = -1000000;
    unsigned short urID[12] = {0};
    int nCount = 0;
    CEleDChanel* pDChanel = NULL;
    QString strName;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    for(i=0; i<pLine->m_arDChanel.count(); i++)
    {
        pDChanel = m_pCmtd->GetDChanelById(pLine->m_arDChanel[i]);
        if(pDChanel == NULL)
        {
            continue;
        }

        strName = gbk->toUnicode(pDChanel->m_chName);
        if((strName.indexOf(QString("重合"))>=0)||(pDChanel->m_strFlag==QString("RecOpCls")))
        {
            urID[nCount++] = pLine->m_arDChanel[i];
        }
        if(nCount >= 12)
        {
            break;
        }
    }
    if(nCount <= 0)	//没有重合闸
    {
        //delete gbk;
        return false;
    }

    for(n=0; n<nCount; n++)
    {
        for(i=0; i<m_SwitchList.m_arStatus.count(); i++)
        {
            if(m_SwitchList.m_arStatus[i].m_wID == urID[n])
            {
                ftime = (float)(m_pCmtd->m_pSampleTime[m_SwitchList.m_arStatus[i].m_nTimePoint]/1000.0);
                break;
            }
        }
    }
    a_fTime = ftime;

    //delete gbk;
    return true;
}

///////////////////////////////方向补偿(开普模型)
void CGenerateReport::Param_TermPG(float &fR, float &fX, float *pIa, float *pIb, float *pIc, float *pI0,float rx)
{
#ifdef GDWY_JIANCE
    const float _PI = 3.1415926;
    float ax=(float)(2*pIa[5]+tan(_PI/3.0)*pIb[0]-pIb[5]-pIc[5]-tan(_PI/3.0)*pIc[0]);
    float ay=(float)(2*pIa[0]-tan(_PI/3.0)*pIb[5]-pIb[0]-pIc[0]+tan(_PI/3.0)*pIc[5]);
    float az=fR/2.5;      //王鹏飞修改,2020年国网电科院检测
//    float az=fR/2.;
    float fd=(pI0[0]*ax - pI0[5]*ay)/(pI0[5]*ax + pI0[0]*ay);
    fd=fd/(fd*rx+1);
    if((fd>0.5)||(fd<-0.5))
        fd=0;
    if(az<0)	fd=-fd*az;
    else		fd= fd*az;
    fX = fX+fd;
//    fR = fR*(1-fd/az);
#endif
}


//获取主变的开关量动作表
void CGenerateReport::getSwitch(tagTransInfo *a_pTrans)
{
    int i=0,j=0,n=0;
    //(1)找到对应的主变元件
    //[[
    CEleTrans* pEleTrans = NULL;
    if(a_pTrans->m_nTransIndex<m_pCmtd->m_arTrans.count())
    {
        pEleTrans = m_pCmtd->m_arTrans[a_pTrans->m_nTransIndex];
    }
    if(!pEleTrans)
    {
        return;
    }
    //]]

    //(2)初始化
    a_pTrans->m_switchList.Init();

    //(3)找关联在主变上的开关量
    //[[
    CEleDChanel* pDChanel = NULL;
    for(i=0; i<m_SwitchList.m_arStatus.count(); i++)
    {
        pDChanel = m_pCmtd->GetDChanelById(m_SwitchList.m_arStatus[i].m_wID);
        if(!pDChanel)
        {
            continue;
        }

        for(j=0; j<pEleTrans->m_arDChanel.count(); j++)
        {
            if(m_SwitchList.m_arStatus[i].m_wID == pEleTrans->m_arDChanel[j])
            {
                CSwitchStatus pStatus = m_SwitchList.m_arStatus[i];
                a_pTrans->m_switchList.m_arStatus.append(pStatus);
            }
        }
    }
    //]]

    //(4)找各分支上关联的开关量
    //[[
    bool bfd = false;
    for(n=0; n<CEleTrans::MAX_BRA_COUNT; n++)
    {
        if(pEleTrans->m_pLine[n] == NULL)
        {
            continue;
        }
        CEleLine* pLine = pEleTrans->m_pLine[n];

        for(i=0; i<m_SwitchList.m_arStatus.count(); i++)
        {
            pDChanel = m_pCmtd->GetDChanelById(m_SwitchList.m_arStatus[i].m_wID);
            if(!pDChanel)
            {
                continue;
            }


            for(j=0; j<pLine->m_arDChanel.count(); j++)
            {
                if(m_SwitchList.m_arStatus[i].m_wID == pLine->m_arDChanel[j])
                {
                    bfd = false;    //主变中已添加，不再重复添加
                    for(int k=0; k<pEleTrans->m_arDChanel.count(); k++)
                    {
                        if(m_SwitchList.m_arStatus[i].m_wID == pEleTrans->m_arDChanel[k])
                        {
                            bfd = true;
                            break;
                        }
                    }
                    if(!bfd)
                    {
                        CSwitchStatus pStatus = m_SwitchList.m_arStatus[i];
                        a_pTrans->m_switchList.m_arStatus.append(pStatus);
                    }
                }
            }
        }
    }
    //]]
}

//获取线路的开关量动作表
void CGenerateReport::getSwitch(tagLineInfo *a_pLine)
{
    int i=0,j=0;
    CEleLine* pLine = NULL;
    if((a_pLine->m_nLineIndex>=0)&&(a_pLine->m_nLineIndex<m_pCmtd->m_arLine.count()))
    {
        pLine = m_pCmtd->m_arLine[a_pLine->m_nLineIndex];
    }
    if(!pLine)
    {
        return;
    }

    CEleDChanel* pDChanel = NULL;
    for(i=0; i<m_SwitchList.m_arStatus.count(); i++)
    {
        pDChanel = m_pCmtd->GetDChanelById(m_SwitchList.m_arStatus[i].m_wID);
        if(!pDChanel)
        {
            continue;
        }
        for(j=0; j<pLine->m_arDChanel.count(); j++)
        {
            if(m_SwitchList.m_arStatus[i].m_wID == pLine->m_arDChanel[j])
            {
                CSwitchStatus pStatus = m_SwitchList.m_arStatus[i];
                a_pLine->m_switchList.m_arStatus.append(pStatus);
            }
        }
    }
}

bool CGenerateReport::FaultLine(CEleLine *pLine)
{
    ///////////////////////////////////////////////////////////
    //主判据
    //[[
    int n=0;
    int i = 0;
    unsigned short urID[12] = {0};
    int nCount = 0;
    CEleDChanel* pDChanel = NULL;
    QString strName;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    for(i=0; i<pLine->m_arDChanel.count(); i++)
    {
        pDChanel = m_pCmtd->GetDChanelById(pLine->m_arDChanel[i]);
        if(pDChanel == NULL)
        {
            continue;
        }

        strName = gbk->toUnicode(pDChanel->m_chName);
        if((strName.indexOf(QString("断路器"))>=0)||(strName.indexOf(QString("保护"))>=0)||(pDChanel->m_eType==CEleDChanel::Relay)||(pDChanel->m_eType==CEleDChanel::Breaker))
        {
            urID[nCount++] = pLine->m_arDChanel[i];
        }
        if(nCount >= 12)
        {
            break;
        }
    }
    if(nCount <= 0)	//没有断路器和保护动作开关量
    {
        //delete gbk;
        return false;
    }

    bool bSwitch = false;
    for(i=0; i<m_SwitchList.m_arStatus.count(); i++)
    {
        for(n=0; n<nCount; n++)
        {
            if(m_SwitchList.m_arStatus[i].m_wID == urID[n])
            {
                bSwitch = true;
                break;
            }
        }
        if(bSwitch) //有一个满足
            break;
    }

    if(!bSwitch)
    {
        //delete gbk;
        return false;
    }
    //]]

    ///////////////////////////////////////////////////////////
    //辅助判据
    //[[
    float* pUa=NULL,*pUb=NULL,*pUc=NULL;
    float* pIa=NULL,*pIb=NULL,*pIc=NULL;
    float* pIn = new float[m_pCmtd->m_nTotalPoints];
    bool bFF = false;   //辅助判据是否满足
    if(pLine->m_pBus != NULL)
    {
        if(pLine->m_pBus->m_pAChanel != NULL)
            pUa = pLine->m_pBus->m_pAChanel->m_pData.data();
        if(pLine->m_pBus->m_pBChanel != NULL)
            pUb = pLine->m_pBus->m_pBChanel->m_pData.data();
        if(pLine->m_pBus->m_pCChanel != NULL)
            pUc = pLine->m_pBus->m_pCChanel->m_pData.data();
    }
    if(pLine->m_pAChanel != NULL)
        pIa = pLine->m_pAChanel->m_pData.data();
    if(pLine->m_pBChanel != NULL)
        pIb = pLine->m_pBChanel->m_pData.data();
    if(pLine->m_pCChanel != NULL)
        pIc = pLine->m_pCChanel->m_pData.data();
    for(i=0; i<m_pCmtd->m_nTotalPoints; i++)
    {
        pIn[i] = 0;
        if(pIa != NULL)
            pIn[i] += pIa[i];
        if(pIb != NULL)
            pIn[i] += pIb[i];
        if(pIc != NULL)
            pIn[i] += pIc[i];
    }
    float fK1Val = 1;           //故障电流
    float fK2Val = 0.5*57.74;   //故障电压
    int nBegin=0,nEnd=0,nWavePoints=0;
    float fAng = 0;
    for(n=0; n<m_pCmtd->m_nSegCount; n++)
    {
        nWavePoints = m_pCmtd->m_pSegment[n].m_nWavePoints;
        if(nWavePoints < 16)    //CD段不判
            continue;
        nBegin = m_pCmtd->m_pSegment[n].m_nStartPos;
        nEnd = nBegin+m_pCmtd->m_pSegment[n].m_nCount-nWavePoints-4;
        for(i=nBegin; i<nEnd; i+=nWavePoints)
        {
            //故障电流 > K1倍额定电流
            if(pIa != NULL)
            {
                if(m_wyCal.DFT_CalRms(pIa+i,nWavePoints,fAng) > fK1Val)
                    bFF = true;
            }
            if(pIb != NULL)
            {
                if(m_wyCal.DFT_CalRms(pIb+i,nWavePoints,fAng) > fK1Val)
                    bFF = true;
            }
            if(pIc != NULL)
            {
                if(m_wyCal.DFT_CalRms(pIc+i,nWavePoints,fAng) > fK1Val)
                    bFF = true;
            }

            //故障电压 < K2倍额定电压
            if(pUa != NULL)
            {
                if(m_wyCal.DFT_CalRms(pUa+i,nWavePoints,fAng) < fK2Val)
                    bFF = true;
            }
            if(pUb != NULL)
            {
                if(m_wyCal.DFT_CalRms(pUb+i,nWavePoints,fAng) < fK2Val)
                    bFF = true;
            }
            if(pUc != NULL)
            {
                if(m_wyCal.DFT_CalRms(pUc+i,nWavePoints,fAng) < fK2Val)
                    bFF = true;
            }

            if(bFF)     //有一个满足
            {
                break;
            }
        }
        if(bFF)
            break;
    }
    delete []pIn;
    //]]
    //delete gbk;

    if(bFF)
        return true;
    else
        return false;
}
