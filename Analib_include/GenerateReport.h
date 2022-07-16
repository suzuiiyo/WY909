//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : AnaResult.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 故障分析接口
//  备    注 : 
//				输入：输入录波文件
//				AnasysLine: 分析指定线路
//				AutoAnasys: 自动选线
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-09-13		创建初始版本
//
//
//
//////////////////////////////////////////////////////////////////////////

#if !defined(FRCANA_GENERATEREPORT_H_)
#define FRCANA_GENERATEREPORT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmtdFile.h"
#include "SwitchStatusList.h"
#include "WyCal.h"

#define MAX_TBLINE_COUNT 48	//有突变的电流数目
#define MAX_ACHANELCOUNT 24 //本视图中最多模拟量通道数目

class tagLineInfo
{
public:
    tagLineInfo()
    {
        InitData();
    }
    ~tagLineInfo()
    {
    }
    void InitData()
    {
        m_bFault = false;
        m_bTbMax = false;
        m_nDirect = 0;
        m_nLineIndex = 0;
        m_nStartPoint = 0;
        m_nEndPoint = 0;
        m_dDistanceI = -10000.0;
        m_dDistanceII = -10000.0;
        memset(m_chBusI_Name,0,sizeof(m_chBusI_Name));
        memset(m_chBusII_Name,0,sizeof(m_chBusII_Name));
        m_dDeltaT = 0.0;
        m_nFaultType = 0;
        memset(m_pVolRms_Before,0,sizeof(m_pVolRms_Before));
        memset(m_pVolAng_Before,0,sizeof(m_pVolAng_Before));
        memset(m_pVolMax_Before,0,sizeof(m_pVolMax_Before));
        memset(m_pVolRms_After,0,sizeof(m_pVolRms_After));
        memset(m_pVolAng_After,0,sizeof(m_pVolAng_After));
        memset(m_pVolMax_After,0,sizeof(m_pVolMax_After));
        memset(m_pVolRms_Over,0,sizeof(m_pVolRms_Over));
        memset(m_pVolAng_Over,0,sizeof(m_pVolAng_Over));
        memset(m_pVolMax_Over,0,sizeof(m_pVolMax_Over));
        memset(m_pInfRms_Before,0,sizeof(m_pInfRms_Before));
        memset(m_pInfAng_Before,0,sizeof(m_pInfAng_Before));
        memset(m_pInfMax_Before,0,sizeof(m_pInfMax_Before));
        memset(m_pInfRms_After,0,sizeof(m_pInfRms_After));
        memset(m_pInfAng_After,0,sizeof(m_pInfAng_After));
        memset(m_pInfMax_After,0,sizeof(m_pInfMax_After));
        memset(m_pInfRms_Over,0,sizeof(m_pInfRms_Over));
        memset(m_pInfAng_Over,0,sizeof(m_pInfAng_Over));
        memset(m_pInfMax_Over,0,sizeof(m_pInfMax_Over));
        m_bReFault = false;
        m_nFaultType_ReF = 0;
        m_nStartPoint_ReF = 0;
        m_nEndPoint_ReF = 0;
        m_dDeltaT_ReF = 0.0;

        memset(m_dU0_Before,0,sizeof(m_dU0_Before));
        memset(m_dU1_Before,0,sizeof(m_dU1_Before));
        memset(m_dU2_Before,0,sizeof(m_dU2_Before));
        memset(m_dI0_Before,0,sizeof(m_dI0_Before));
        memset(m_dI1_Before,0,sizeof(m_dI1_Before));
        memset(m_dI2_Before,0,sizeof(m_dI2_Before));
        memset(m_dU0_After,0,sizeof(m_dU0_After));
        memset(m_dU1_After,0,sizeof(m_dU1_After));
        memset(m_dU2_After,0,sizeof(m_dU2_After));
        memset(m_dI0_After,0,sizeof(m_dI0_After));
        memset(m_dI1_After,0,sizeof(m_dI1_After));
        memset(m_dI2_After,0,sizeof(m_dI2_After));
        memset(m_dU0_Over,0,sizeof(m_dU0_Over));
        memset(m_dU1_Over,0,sizeof(m_dU1_Over));
        memset(m_dU2_Over,0,sizeof(m_dU2_Over));
        memset(m_dI0_Over,0,sizeof(m_dI0_Over));
        memset(m_dI1_Over,0,sizeof(m_dI1_Over));
        memset(m_dI2_Over,0,sizeof(m_dI2_Over));
        memset(m_pVolRms_ReF_After,0,sizeof(m_pVolRms_ReF_After));
        memset(m_pVolAng_ReF_After,0,sizeof(m_pVolAng_ReF_After));
        memset(m_pVolMax_ReF_After,0,sizeof(m_pVolMax_ReF_After));
        memset(m_pVolRms_ReF_Over,0,sizeof(m_pVolRms_ReF_Over));
        memset(m_pVolAng_ReF_Over,0,sizeof(m_pVolAng_ReF_Over));
        memset(m_pVolMax_ReF_Over,0,sizeof(m_pVolMax_ReF_Over));
        memset(m_pInfRms_ReF_After,0,sizeof(m_pVolRms_ReF_After));
        memset(m_pInfAng_ReF_After,0,sizeof(m_pVolAng_ReF_After));
        memset(m_pInfMax_ReF_After,0,sizeof(m_pVolMax_ReF_After));
        memset(m_pInfRms_ReF_Over,0,sizeof(m_pVolRms_ReF_Over));
        memset(m_pInfAng_ReF_Over,0,sizeof(m_pVolAng_ReF_Over));
        memset(m_pInfMax_ReF_Over,0,sizeof(m_pVolMax_ReF_Over));

        m_dMaxFaultInf_one = -1;
        m_dMinFaultVol_one = -1;
        //			m_dMaxFaultInf_two = -1;
        //			m_dMinFaultVol_two = -1;
        m_uRelayPhase = 0;
        m_dRelayActTime = -1000;
        m_dBreakerJumpTime = -1000;
        m_dReCloseTime = -1000;
        m_dBreakerShutTime = -1000;
        m_dRelayActAgainTime = -1000;
        m_dBreakerJumpAgainTime = -1000;
        m_dRelayActTime2 = -1000;
        m_dRelayActTime3 = -1000;
        m_bRecloseSucess = false;
        m_bHaveReclose = false;
        m_uPhase = 0;
        m_dFaultR = 0;
        m_dFaultX = 0;

        m_dMaxFaultInf_two = 0;
        m_dMinFaultVol_two = 0;
        memset(m_chInfChanel,0,sizeof(m_chInfChanel));
        memset(m_chVolChanel,0,sizeof(m_chVolChanel));

        m_uFpt = 0;
        m_uJpt = 0;
        m_uDpi = 0;
        m_wChzTime = 0;
        m_switchList.Init();
    }
public:
    bool m_bFault;			//是否为故障线路
    int m_nDirect;			//是否是故障线路的权值
    int m_nLineIndex;		//线路编号
    int m_nStartPoint;		//故障开始点序号
    int m_nEndPoint;		//故障结束点序号
    float m_dDistanceI;		//距离(母线1距离)
    float m_dDistanceII;		//距离(母线2距离)
    char m_chBusI_Name[256];	//母线I名称
    char m_chBusII_Name[256];	//母线II名称
    float m_dDeltaT;		//衰减时间常数
    int    m_nFaultType;		//故障类型
    float m_pVolRms_Before[4];	//故障前一周波电压有效值
    float m_pVolAng_Before[4];	//故障前一周波电压角度
    float m_pVolMax_Before[4];	//故障前一周波电压峰值
    float m_pVolRms_After[4];	//故障后一周波电压有效值
    float m_pVolAng_After[4];	//故障后一周波电压角度
    float m_pVolMax_After[4];	//故障后一周波电压峰值
    float m_pVolRms_Over[4];	//故障切除后第一周波电压有效值
    float m_pVolAng_Over[4];	//故障切除后第一周波电压角度
    float m_pVolMax_Over[4];	//故障切除后第一周波电压峰值
    float m_pInfRms_Before[4];	//故障前一周波电流有效值
    float m_pInfAng_Before[4];	//故障前一周波电流角度
    float m_pInfMax_Before[4];	//故障前一周波电流峰值
    float m_pInfRms_After[4];	//故障后一周波电流有效值
    float m_pInfAng_After[4];	//故障后一周波电流角度
    float m_pInfMax_After[4];	//故障后一周波电流峰值
    float m_pInfRms_Over[4];	//故障切除后第一周波电流有效值
    float m_pInfAng_Over[4];	//故障切除后第一周波电流角度
    float m_pInfMax_Over[4];	//故障切除后第一周波电流峰值

    float m_dU0_Before[2];		//零序电压
    float m_dU1_Before[2];		//正序电压
    float m_dU2_Before[2];		//负序电压
    float m_dI0_Before[2];		//零序电流
    float m_dI1_Before[2];		//正序电流
    float m_dI2_Before[2];		//负序电流
    float m_dU0_After[2];		//零序电压
    float m_dU1_After[2];		//正序电压
    float m_dU2_After[2];		//负序电压
    float m_dI0_After[2];		//零序电流
    float m_dI1_After[2];		//正序电流
    float m_dI2_After[2];		//负序电流
    float m_dU0_Over[2];		//零序电压
    float m_dU1_Over[2];		//正序电压
    float m_dU2_Over[2];		//负序电压
    float m_dI0_Over[2];		//零序电流
    float m_dI1_Over[2];		//正序电流
    float m_dI2_Over[2];		//负序电流

    bool m_bReFault;		//再次故障
    int m_nFaultType_ReF;		//再次故障类型
    int m_nStartPoint_ReF;		//故障开始时间(点序号)
    int m_nEndPoint_ReF;		//故障结束时间(点序号)
    float m_dDeltaT_ReF;		//衰减时间常数
    float m_pVolRms_ReF_After[4];	//故障后一周波电压有效值
    float m_pVolAng_ReF_After[4];	//故障后一周波电压角度
    float m_pVolMax_ReF_After[4];	//故障后一周波电压峰值
    float m_pVolRms_ReF_Over[4];	//故障切除后第一周波电压有效值
    float m_pVolAng_ReF_Over[4];	//故障切除后第一周波电压角度
    float m_pVolMax_ReF_Over[4];	//故障切除后第一周波电压峰值
    float m_pInfRms_ReF_After[4];	//故障后一周波电流有效值
    float m_pInfAng_ReF_After[4];	//故障后一周波电流角度
    float m_pInfMax_ReF_After[4];	//故障后一周波电流峰值
    float m_pInfRms_ReF_Over[4];	//故障切除后第一周波电流有效值
    float m_pInfAng_ReF_Over[4];	//故障切除后第一周波电流角度
    float m_pInfMax_ReF_Over[4];	//故障切除后第一周波电流峰值

    //浙江简报添加
    float m_dMaxFaultInf_one;	//最大故障电流(一次侧)
    char   m_chInfChanel[256];	//最大电流的相别
    float m_dMinFaultVol_one;	//最低故障电压(一次侧)
    char   m_chVolChanel[256];	//最低电压相别
    float m_dMaxFaultInf_two;	//最大故障电流(二次侧)
    float m_dMinFaultVol_two;	//最低故障电压(二次侧)
    unsigned char m_uRelayPhase;	//保护装置跳闸相别
    float m_dRelayActTime;		//保护动作时刻
    float m_dBreakerJumpTime;	//断路器分时刻
    float m_dReCloseTime;		//重合闸动作时刻
    float m_dBreakerShutTime;	//断路器合时刻
    float m_dRelayActAgainTime;	//保护再次动作时刻
    float m_dBreakerJumpAgainTime;	//断路器再次分时刻
    float m_dRelayActTime2;			//第二套保护动作时刻
    float m_dRelayActTime3;			//非电量保护动作时刻
    bool  m_bRecloseSucess;		//重合闸是否成功
    bool  m_bHaveReclose;		//是否有重合闸
    unsigned char m_uPhase;		//突变/越限的相别

    bool m_bTbMax;			//本线路是否为突变线路
    float m_dFaultR;		//故障电阻
    float m_dFaultX;		//故障电抗
    unsigned char m_uFpt;							//故障相别
    unsigned char m_uJpt;							//跳闸相别
    unsigned char m_uDpi;							//是否有重合闸
    unsigned short m_wChzTime;					    //重合闸时间

    CSwitchStatusList m_switchList;
};
class tagTransInfo
{
public:
    tagTransInfo()
    {
        InitData();
    }
    ~tagTransInfo()
    {
    }
    void InitData()
    {
        m_pLine[0].InitData();
        m_pLine[1].InitData();
        m_pLine[2].InitData();
        m_pLine[3].InitData();
        m_nTransIndex = 0;
        m_dIda1_Before = 0;
        m_dIdb1_Before = 0;
        m_dIdc1_Before = 0;
        m_dIda2_Before = 0;
        m_dIdb2_Before = 0;
        m_dIdc2_Before = 0;
        m_dIda1_After = 0;
        m_dIdb1_After = 0;
        m_dIdc1_After = 0;
        m_dIda2_After = 0;
        m_dIdb2_After = 0;
        m_dIdc2_After = 0;
        m_wPhase = 0;
        m_bFault = false;
        m_dMaxFaultInf_I = 0;
        m_dMaxFaultInf_II = 0;
        m_dMaxFaultInf_III = 0;
        m_dMaxFaultInf_IV = 0;
        m_dMinFaultVol_I = 0;
        m_dMinFaultVol_II = 0;
        m_dMinFaultVol_III = 0;
        m_dMinFaultVol_IV = 0;
        m_dMaxFaultInf_two = 0;
        m_dMinFaultVol_one = 10000;
        m_dRelayActTime = -1000.0;
        m_dRelayActTime2 = -1000.0;
        m_dRelayActTime3 = -1000.0;
        m_dBreakerJumpTime_I = -1000.0;
        m_dBreakerJumpTime_II = -1000.0;
        m_dBreakerJumpTime_III = -1000.0;
        m_dBreakerJumpTime_IV = -1000.0;
        m_nInfTb = 0;
        m_uPhase = 0;
        m_nFaultEnd = -1;
        m_nFaultStart = -1;
        memset(m_chInfChanel,0,sizeof(m_chInfChanel));
        memset(m_chVolChanel,0,sizeof(m_chVolChanel));
        m_bFFlag = false;
        m_uFpt = 0;
        m_uJpt = 0;
        m_uDpi = 0;
        m_wChzTime = 0;
        m_switchList.Init();
    }
public:
    unsigned short m_nTransIndex;	//主变序号
    unsigned short m_wPhase;		//越限的相(A、B、C)
    tagLineInfo m_pLine[4];			//四侧电流
    bool m_bFault;
    bool m_bFFlag;
    //启动前一周差流有效值
    float m_dIda1_Before;			//A相差流
    float m_dIdb1_Before;			//B相差流
    float m_dIdc1_Before;			//C相差流
    float m_dIda2_Before;			//A相差流二次谐波
    float m_dIdb2_Before;			//B相差流二次谐波
    float m_dIdc2_Before;			//C相差流二次谐波
    //启动后一周差流有效值
    float m_dIda1_After;			//A相差流
    float m_dIdb1_After;			//B相差流
    float m_dIdc1_After;			//C相差流
    float m_dIda2_After;			//A相差流二次谐波
    float m_dIdb2_After;			//B相差流二次谐波
    float m_dIdc2_After;			//C相差流二次谐波

    //浙江添加
    float m_dMaxFaultInf_I;         //高压侧最大故障电流
    float m_dMaxFaultInf_II;		//中压侧...
    float m_dMaxFaultInf_III;		//
    float m_dMaxFaultInf_IV;		//
    float m_dMinFaultVol_I;
    float m_dMinFaultVol_II;
    float m_dMinFaultVol_III;
    float m_dMinFaultVol_IV;
    float m_dMaxFaultInf_one;		//最大故障相电流
    float m_dMaxFaultInf_two;		//
    float m_dMinFaultVol_one;		//最低故障相电压
    float m_dMinFaultVol_two;
    float m_dRelayActTime;			//保护动作时刻
    float m_dRelayActTime2;			//第二套保护动作时间
    float m_dRelayActTime3;
    float m_dBreakerJumpTime_I;     //短路器分时刻
    float m_dBreakerJumpTime_II;
    float m_dBreakerJumpTime_III;
    float m_dBreakerJumpTime_IV;

    unsigned char	m_nInfTb;		//相电流突变
    unsigned char   m_uPhase;		//越限的相
    int m_nFaultEnd;
    int m_nFaultStart;
    char   m_chInfChanel[MAX_PATH];	//
    char   m_chVolChanel[MAX_PATH];	//

    unsigned char m_uFpt;							//故障相别
    unsigned char m_uJpt;							//跳闸相别
    unsigned char m_uDpi;							//是否有重合闸
    unsigned short m_wChzTime;					    //重合闸时间

    CSwitchStatusList m_switchList;
};

class CGenerateReport
{
public:
    CGenerateReport();
    virtual ~CGenerateReport();
public:
    struct CP56DateTime
    {
        unsigned short wMiniSeconds;	//毫秒
        unsigned char uMinutes:6;	//分钟
        unsigned char uRes1:1;		//备用
        unsigned char uIV:1;		//=0有效;=1无效
        unsigned char uHours:5;		//小时
        unsigned char uRes2:2;		//备用
        unsigned char uSu:1;		//=0标准时间;=1夏季时间
        unsigned char uDay:5;		//日
        unsigned char uWeek:3;		//星期
        unsigned char uMonth:4;		//月
        unsigned char uRes3:4;		//备用
        unsigned char uYears:7;		//年
        unsigned char uRes4:1;		//备用
    };

    class tagStarttype
    {
    public:
        tagStarttype(){}
        ~tagStarttype(){}
        int nStartFlag;			//是否有启动的标志
        int nabcStartPoints;    //abc启动
        int nabStartPoints;		//ab相突变点数
        int nbcStartPoints;		//bc相突变点数
        int ncaStartPoints;		//ca相突变点数
    };

    class tagChanelInfo
    {
    public:
        tagChanelInfo()
        {
            InitData();
        }
        ~tagChanelInfo()
        {
        }
        void InitData()
        {
            memset(m_chName,0,sizeof(m_chName));
            m_dRmsBefore = 0;
            m_dPharseBefore = 0;
            m_dMaxBefore = 0;
            m_dRmsAfter = 0;
            m_dPharseAfter = 0;
            m_dMaxAfter = 0;
            m_dRmsOver = 0;
            m_dPharseOver = 0;
            m_dMaxOver = 0;
        }
        char   m_chName[120];
        float  m_dRmsBefore;		//故障前1周波有效值
        float  m_dPharseBefore;		//故障前1周波相位
        float  m_dMaxBefore;		//故障前1周波峰值
        float  m_dRmsAfter;		//故障后1周波有效值
        float  m_dPharseAfter;		//故障后1周波相位
        float  m_dMaxAfter;		//故障后1周波峰值
        float  m_dRmsOver;		//故障后2周波有效值
        float  m_dPharseOver;		//故障后2周波相位
        float  m_dMaxOver;		//故障后2周波峰值
    };

protected:
    //----------------------------------------------------------------------------------------------------------------
    //测距用函数
    //----------------------------------------------------------------------------------------------------------------
    float Dist_CalAvg(float* a_pData,int a_nPoints);//计算平均值
    float Dist_CalAvgEx(float* a_pData,int a_nPoints);//计算平均值(去掉第一个点,去掉最大/最小值)
    float Dist_CalSum(float* a_pData);//求和
    float Dist_CalSum(float* a_pDataI,float* a_pDataII);//求和
    void Dist_FilterPara(int a_nHarm,float* a_pParamRe,float* a_pParamIm,int a_nWavePoints=20);//匹配滤波器
    void Dist_DFT(float* a_pData,int a_nWavePoints,float* a_pParamRe,float* a_pParamIm,int a_nPoints,float& a_dRe,float& a_dIm);//DFT
    void Dist_WaveFilter(float* a_pData,int a_nPoints,int a_nWavePoints,float* a_pParam,int a_nCount,float* a_pResult,bool a_bConvert = false);//滤波
    float Dist_CalAmp(float* a_pData,int a_nWavePoints);//基于正弦量计算幅值
    float Dist_CalFreq(float* a_pData,int a_nWavePoints);//计算频率
    float Dist_CalDeltaT_Result(float* a_pData,int a_nWavePoints);//计算衰减时间常数
    float Dist_CalDeltaT_Ex(float* a_pData,int a_nWavePoints);
    float Dist_CalDeltaT(float* a_pIa,float* a_pIb,float* a_pIc,int a_nWavePoints,int a_nFaultType);//计算衰减时间常数
    int	 Dist_FindStartPoint(float a_dMaxI,float* a_pIa,float* a_pIb,float* a_pIc,int a_nWavePoints,tagStarttype* a_pStarttype);//获取突变点
    void Dist_CalRX_PP(float* a_pDataU,float* a_pDataI,float& a_dR,float& a_dX);//计算阻抗(相间)CalXRFiFi1
    int  Dist_CalRXEx_PP(float* a_pDataU,float* a_pDataI,float& a_dR,float& a_dX);//计算阻抗(相间)CalXRFiFi
    int  Dist_CalRX_PG1(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float a_dFactor,float& a_dR,float& a_dX);//计算阻抗(相地)CalXRFi
    void Dist_CalRX_PG2(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float a_dFactor,float& a_dR,float& a_dX);//计算阻抗(相地)CalXRFi1
    int  Dist_CalRX_PG3(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float a_dR0,float a_dR1,float a_dX0,float a_dX1,float& a_dR,float& a_dX);//计算阻抗(相地)CalXRFi2
    int  Dist_CalRX_PG4(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float a_dR0,float a_dR1,float a_dX0,float a_dX1,float& a_dR,float& a_dX);//计算阻抗(相地)CalXRFi3
    int  Dist_CalDistance1(float* a_pDataU[3],float* a_pDataI[4],int a_nCalPos,int a_nWavePoints,float a_dFactor,int a_nFaultKind,float& a_dR,float& a_dX);//测距
public:
    int  Dist_CalDistance2(float* a_pDataU[3],float* a_pDataI[4],int a_nCalPos,int a_nWavePoints,float a_dRX[4],int a_nFaultKind,float& a_dR,float& a_dX,float fLineX,bool a_bConvert = false);//测距
    int  Dist_CalDistance3(float* a_pDataU[3],float* a_pDataI[4],int a_nCalPos,int a_nWavePoints,float a_dRX[4],int a_nFaultKind,float& a_dR,float& a_dX,float fLineX,bool a_bConvert = false);//测距
protected:
    int Dist_CalDistance3_ext(float* a_pDataU[3],float* a_pDataI[4],float* a_pHgI0,int a_nCalPos,int a_nWavePoints,float a_dRX[4],float a_dMRX[2],int a_nFaultKind,float& a_dR,float& a_dX,float fLineX,bool a_bConvert = false);
    int Dist_CalDistance2_ext(float* a_pDataU[3],float* a_pDataI[4],float* a_pHgI0,int a_nCalPos,int a_nWavePoints,float a_dRX[4],float a_dMRX[2],int a_nFaultKind,float& a_dR,float& a_dX,float fLineX,bool a_bConvert = false);
    int Dist_CalRX_PG4_ext(float* a_pDataU,float* a_pDataI,float* a_pDataI0,float* a_pDataHgI0,float a_dR0,float a_dR1,float a_dX0,float a_dX1,float a_dHgR0,float a_dHgX0,float& a_dR,float& a_dX);//计算阻抗(相地)CalXRFi3

    int  Dist_FindFaultType_Vol(float* a_pUa,float* a_pUb,float* a_pUc,int a_nWavePoints,int a_nPoints,int a_nFaultType,int& a_nFaultPos);
    int  Dist_FindFaultType_Inf(float a_dMaxI,float* a_pIa,float* a_pIb,float* a_pIc,int a_nWavePoints,int a_nPoints,int a_nFaultType,int& a_nFaultPos);//故障选相
    int  Dist_FindDirectionP(float* a_pDataU,float* a_pDataI,int a_nWavePoints = 20);//判方向(单相)//JudgeFXFI
    int  Dist_FindDirectionPP(float* a_pDataU1,float* a_pDataU2,float* a_pDataI1,float* a_pDataI2,int a_nWavePoints = 20);//判方向(相间)//JudgeFXFIFI
    int  Dist_FindDirection(float* a_pDataU[3], float* a_pDataI[3],int a_nCalPos,int a_nWavePoints,int a_nFaltType);//判方向//FaultDir
    void GetMaxInf_Trans(int a_nTransNo);
    void GetMinVol_Trans(int a_nTransNo);
    void Param_TermPG(float& fR,float& fX,float* pIa,float* pIb,float* pIc,float* pI0,float rx);
public:
    void OutputSwitchList_to_File(const QString& a_strFile);
    bool AnalysisLine(int a_nLineIndex);
    bool AnalysisLine(int a_nLineIndex,tagLineInfo* a_pLineInfo);
    bool AnalysisLine_manual(int a_nLineIndex,int a_nFaultPos,int a_nFaultType,tagLineInfo* a_pLineInfo);
    bool AnalysisLine_manual(int a_nLineIndex,int a_nFaultPos,int a_nFaultType);
    bool AnalysisTrans(int a_nTransIndex,bool& bOverFlow);

    bool GenerateBasicInfo();
    bool GenerateSwitchList();
    bool GenerateTrans_Report();
    bool GenerateLine_Report();
    bool IsFault_A(CEleLine* pLine);                //是否为永久性故障
    bool GetCHZTime_Switch(CEleLine* pLine,float& a_fTime);

    void InitData();
    bool IsLines_Inf_Overflow(tagLineInfo* a_pLineInfo, CEleLine* a_pEleLine);
    bool IsTrans_Inf_Overflow(tagTransInfo* a_pTransInfo, CEleTrans* a_pEleTrans);
    int GetSwitchJump_Line();
    void GetLineValue_Cyc(tagLineInfo* a_pLineInfo, CEleLine* a_pEleLine);
    void GetFaultValue_Trans(tagTransInfo* a_pTransInfo, CEleTrans* a_pEleTrans,int a_nPos1,int a_nPos2,int a_nPos3,int a_nWavePoints);

    void getSwitch(tagTransInfo* a_pTrans);
    void getSwitch(tagLineInfo* a_pLine);
protected:
    float fRandm(int nMax);
    bool FaultLine(CEleLine *pLine);
public:
    CCmtdFile* m_pCmtd;
    CWyCal m_wyCal;
    //////////////////////////////////////////////////////////////////////////
    //测距用变量
    float m_dParam[21];	//变换参数
    int    m_nFreq;			//频率
    enum
    {
        FAULT_NONE = 0,
        FAULT_AN = 1,
        FAULT_BN = 2,
        FAULT_CN = 3,
        FAULT_AB = 4,
        FAULT_BC = 5,
        FAULT_CA = 6,
        FAULT_ABN = 7,
        FAULT_BCN = 8,
        FAULT_CAN = 9,
        FAULT_ABC = 10,
        FAULT_OVER = 11,
        FAULT_NOTDF = 12
    };
    float m_dPI;	//PI

    //----------------------------------------------------------------------------
    //测距分析公用部分
    //----------------------------------------------------------------------------
    CSwitchStatusList m_SwitchList;					//开关变位时序
    char m_chStationName[MAX_PATH];					//变电站名称
    char m_chStartTime[MAX_PATH];					//启动时刻
    float m_dTimeLong;								//录波持续时间
    char m_chStartInfo[MAX_PATH];					//启动原因
    char m_chFilePath[MAX_PATH];					//文件路径

    //----------------------------------------------------------------------------
    //保存分析结果
    //----------------------------------------------------------------------------
    tagLineInfo* m_arLineInfo;
    int m_nTbLineCount;
    tagTransInfo* m_arTransInfo;
    int m_nTbTransCount;
    tagChanelInfo* m_arChanelInfo;
    int m_nChanelCount;
    int m_nFaultPos;

    //----------------------------------------------------------------------------
    //浙江简报添加
    //----------------------------------------------------------------------------
    char m_chFaultLine[40];							//故障线路
    unsigned char m_uFpt;							//故障相别
    unsigned char m_uJpt;							//跳闸相别
    float m_fFaultDistance;							//故障测距结果
    unsigned char m_uDpi;							//是否有重合闸
    unsigned short m_wChzTime;								//重合闸时间
    CP56DateTime m_cpStartTime;						//启动时间
    unsigned int m_dwFileSize;								//文件大小

    QString m_strFaultType[13];						//故障类型描述
    char m_chRecName[MAX_PATH];						//装置名称


    float m_dParamab[6];							//高压侧各相a，b
    char m_chErrorInfo[512];

    //----------------------------------------------------------------------------
    //2009-04-17 添加故障信息指针,便于保存故障线路信息
    //----------------------------------------------------------------------------
    tagLineInfo* m_pFaultLine;
    tagTransInfo* m_pFaultTrans;

    int m_nRelayActLine;
};

#endif // !defined(FRCANA_GENERATEREPORT_H_)
