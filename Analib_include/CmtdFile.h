//////////////////////////////////////////////////////////////////////////
//	Copyright (c)2007 武汉国电武仪
//	All rights reserved.
//	
//	文 件 名 : CmtdFile.h
//	文件类型 : h
//	版	  本 : ver 1.0
//	编    制 : wpf
//	描    述 : 读COMTRADE文件类定义;
//  备    注 : 
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-06-12		创建初始版本
//ver 1.1       2008-05-04      兼容中元华电ext文件
//
//
//////////////////////////////////////////////////////////////////////////

#if !defined(WYANALYZE_COMTDFILE_H_)
#define WYANALYZE_COMTDFILE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmtdSegment.h"
#include "EleAChanel.h"
#include "EleDChanel.h"
#include "EleBus.h"
#include "EleTrans.h"
#include "EleDC.h"
#include "EleLine.h"
#include "EleRemark.h"
#include "EleGenerator.h"
#include "EleExciter.h"
#include <QVector>
#include <QString>
#include <QTime>
#include "readthread.h"

#define MAX_TRANSCOUNT 16

//////////////////////////////////////////////////////////////////////////
//类中用到的数据单元
#pragma  pack(push)
#pragma pack(1)
//二进制文件存储单元
typedef struct _DATFILE_UNIT
{
    int m_nSampIndex;
    int m_nSampTime;
    short m_nSampData[4096];
}tagDatUnit;
//定值存储单元
/*
typedef struct _TAG_SetUnit
{
	BYTE m_uKind;
	BYTE m_uIndex;
        unsigned short m_wAttr;
	int  m_nValueA;
	short m_nValueB;
	char m_chName[22];
}tagSetUnit;

typedef struct _TAG_LineUnit
{
	int m_nIndex;	//编号
	int m_nAChanel; //A相通道号
}tagLineUnit;
*/
typedef struct
{
    char chFault;               //=0,无故障 =1,有故障但故障性质为S =2,有故障但故障性质为F
    unsigned char chTrans;      //=0,线路录波 =1,主变录波器
    char chFaultLine;           // 故障线路序号,从0开始的编号
    char chFaultKind;           //=0    故障类型1 AN; 2 BN; 3 CN; 4 AB; 5 BC; 6 CA; 7 ABN;8 BCN;9 CAN;10 ABC
    float fDistance;            //故障距离
    float fFaultR;              //电阻
    float fFaultX;              //电抗
    long  lTimes;               //UTC时间
    char	chBak[12];       	//备用
}ext_INFO_FAULT;

typedef struct
{
    unsigned int  	leap_ltime;      	//时间
    unsigned int  	leap_command;    	//命令字
    char   			chBak[24];       	//备用
}ext_INFO_LEAPTIME;

typedef struct
{
    unsigned char   dt_year;        //年,减去1900后的值
    unsigned char   dt_month;       //月
    unsigned char   dt_day;         //日
    unsigned char   dt_hour;        //时
    unsigned char   dt_minute;      //分
    unsigned char   dt_second;      //秒
    unsigned short  dt_msec;        //毫秒
    unsigned char   chTrigType;     //启动原因
    unsigned char   chChnType;      //元件类型
    unsigned short  chChnNo;        //元件序号
    float           fTrigValue;     //启动值
    float           fSetValue;      //整定值
    char            chTrigDesc[108];//启动元件描述
}ext_INFO_TRIG;

#pragma pack(pop)

class CCmtdFile
{
public:
    CCmtdFile();
    virtual ~CCmtdFile();
public:
    //////////////////////////////////////////////////////////////////////////
    //接口定义
    bool ReadComtradeFile(const QString& a_strCfgFilePath);	//读Comtrade文件
    bool ReadFile_GetFaultInfo(const QString& a_strCfgFilePath);	//读Comtrade文件

    bool ReadCfgFile();                                     //读cfg文件
    bool ReadBinaryDatFile();                               //读二进制dat文件
    bool ReadAsciiDatFile();                                //读ASCII码dat文件
    bool ReadDMFFile(const QString& strDMF);
    bool ReadLneFile();                                     //读lne文件
    bool GetAttatch();
    bool ReadPrvFile();                                     //读prv文件
    bool ReadHdrFile();                                     //读hdr文件
    bool ReadRmkFile();                                     //读标签文件
    bool ReadExtFile();                                     //
    bool ReadDCExtend();
    void GeneratePTCT();                                    //初始PT变比
    bool FileLoadFinished();                                //文件载入是否完成(用于二进制Dat文件)
    int GetCalPos(int a_nDataWindowType, int a_nCurPos, int &a_nWavePoints); //获取计算位置
    int GetCurSeg(int a_nCurPos);                           //获取指定位置所在采样段
    double GetChanelParam(int n);
    bool IsNull();                                          //是否已经有打开的文件
    bool HaveEleItem();
    void ParamPhase(unsigned short usID,float& fPhase);
    bool IsUpperCase();
    void RemoveBus(int nInd);
    void RemoveLine(int nInd);
    void RemoveTrans(int nInd);
    void RemoveDC(int nInd);
    void RemoveGenerator(int nInd);
    void RemoveExciter(int nInd);
    void removeEleItem();
    bool AutoDef();
    bool SaveToDmf(const QString &strPath);
    bool ReadEleParam(const QString &strCfgPath);
    CEleBus* GetBus(CEleTrans* pTrans,CEleTransWiding* pWiding);
    CEleLine* GetLine(CEleTrans* pTrans,CEleTransWiding* pWiding,uint wAID,uint wBID,uint wCID);
    bool readStartTime();
    bool writeDCExtend();
public:
    QString GetLeftStr(QString& a_strLine, char a_ch=',');	//获取第一个子串
    void FreeMemory();                                      //清内存
    CEleAChanel* GetAChanelById(unsigned short a_wId);		//根据通道号获取通道指针
    CEleDChanel* GetDChanelById(unsigned short a_wId);
    CEleBus* GetBusById(unsigned short a_wId);
    QString Hdr_GetRightString(QString& a_strLine);         //读hdr文件辅助函数(获取右子串)
    int Hdr_GetInfoKind(const QString& a_strLine);          //读hdr文件信息类型
    int Hdr_GetEndPos(QString& a_strLine);                  //获取hdr文件结束位置
    int QtoB(const QString& a_strQ);                               //全角转半角
    float GetTds_CTPT(unsigned short a_wChanelID,unsigned short a_wType);//获取通道的CTPT
    float GetChanels_PTCT(CEleAChanel* pChanel);
    QDateTime GetTimeFromString(const QString& a_strTime,float& a_dMiniSecond);//从cfg文件时间描述串中获取时间
    unsigned short DMF_GetChanelIDX(unsigned short usChnID, int *pAChanel,int nACount);
    QString DMF_GetTranswGDesc(int nType);                      //接线方式描述
public:
    bool SaveFileAs(int a_nStartPos,int a_nEndPos,const QString& a_strFilePath);
    bool SaveFileAs(int* pAChanel,int a_nACount,int* pDChanel,int a_nDCount,const QString& a_strFilePath);
    bool SaveLineFile(CEleLine* a_pLine, const QString& a_strFilePath,bool a_bAct=false,bool a_bUpperCase=false);
    bool SaveTransFile(CEleTrans* a_pTrans, const QString& a_strFilePath,bool a_bAct=false,bool a_bUpperCase=false);

    void GenerateUnit();                //修正单位
    void GenerateOtherInfo();
    void GenerateLineInfo();            //处理和电流
    void Generate_ZL_Abs();
    void FreshMaxABS();
                                       //
    bool UnPackgeFile(const QString& a_strWy2FilePath);
    float GetChanels_Min_Rms(unsigned short a_wChanelID);
    bool WriteInfoToFile();
    char* GetErrorInfo();
    void WriteRmkFile();
    bool IsDigital();
    QString ParamTimes(double nTime,int nDigit=6);
    QString SGParamTimes(int nTime);
private:
    bool IsFileExist(const QString& strFilePath);
    void GenerateTransInfo();
    struct tm* LeapTime(uint ltime);
    void GetFilePath(const QString& strCfgPath);
    void GetChanelsPhase(CEleAChanel* pAChanel);
    void GetFaultInfo();
public:
    //////////////////////////////////////////////////////////////////////////
    //成员变量定义
    CCmtdSegment* m_pSegment;                   //采样段
    int m_nSegCount;                            //采样段数目
    QVector<CEleBus*> m_arBus;                  //母线
    QVector<CEleLine*> m_arLine;                //线路
    QVector<CEleDC*> m_arDC;                    //直流
    QVector<CEleTrans*> m_arTrans;              //主变
    QVector<CEleExciter*> m_arExciter;          //励磁机
    QVector<CEleGenerator*> m_arGenerator;      //发电机

    QVector<CEleAChanel*> m_arAChanel;          //
    QVector<CEleDChanel*> m_arDChanel;          //
    int m_nChanelCount;                         //通道数目
    QString m_strCfgFilePath;                   //cfg文件路径
    QString m_strDatFilePath;                   //dat文件路径
    QString m_strLneFilePath;                   //lne文件路径
    QString m_strDMFFilePath;                   //DMF文件路径
    QString m_strRmkFilePath;                   //Rmk文件路径
    QString m_strSetFilePath;                   //定值文件路径
    QString m_strHdrFilePath;                   //hdr文件路径
    QString m_strPrvFilePath;                   //Prv文件路径
    QString m_strExtFilePath;                   //Ext文件路径
    volatile bool m_bBinaryFile;                //是否为二进制文件
    QVector<double> m_pSampleTime;                 //采样时间序列
    volatile int  m_nTotalPoints;               //采样点个数
    QString m_strStartTime;                     //录波判启动的时间
    QString m_strLeftTime;                      //最左侧时刻
    QString m_strStationName;                   //站名称
    int m_nFrate;                               //频率
    volatile float m_dMaxUAbs;                  //电压最大绝对值
    volatile float m_dMaxIAbs;                  //电流最大绝对值
    volatile float m_dMaxZAbs;                  //直流最大绝对值
    volatile float m_dMaxZAbs_ZL_OTHER;
    volatile float m_dMaxZAbs_ZL_30V_GP;
    volatile float m_dMaxZAbs_ZL_5V_VOL;
    volatile float m_dMaxZAbs_ZL_300V_VOL;
    volatile float m_dMaxZAbs_ZL_2000V_VOL;
    volatile float m_dMaxZAbs_ZL_ZL_200MV_VOL;
    volatile float m_dMaxZAbs_ZL_ZL_4TO20MA_INF;
    volatile float m_dMaxZAbs_ZL_JL_57V_VOL;
    volatile float m_dMaxZAbs_ZL_JL_100V_VOL;
    volatile float m_dMaxZAbs_ZL_JL_5A_INF;
    volatile float m_dMaxZAbs_ZL_JL_1A_INF;
    volatile float m_dMaxZAbs_ZL_ZP_100V_VOL;
    volatile float m_dMaxZAbs_ZL_ZP_400V_VOL;
    volatile float m_dMaxZAbs_ZL_ZP_5A_INF;
    volatile float m_dMaxZAbs_ZL_ZL_PINLV;

    volatile bool   m_bHaveOpenFile;			//已经有打开的文件
    QString m_strFilePath;                      //原始路径
    float m_dTimeSpan;                          //突变时间 - 启动时间
    int    m_nTbPos;                            //突变点序号
    bool   m_bTransRec;                         //是否为主变录波器

    QDateTime  m_tmStart;                       //录波启动时刻
    unsigned int   m_wFaultMiniSec;             //启动时刻的毫秒

    QVector<CEleRemark*> m_arRemark;             //标签
    bool  m_bExternFile;                        //是否有配置文件
    float m_dMaxRed;                            //差流越限值

    int m_nRecId;                               //装置ID
    unsigned short m_wCmtdYear;                 //Comtrade文件的修改时间(版本号,91或者99)

    char m_chErrorInfo[MAX_PATH];               //错误信息
    QString m_strAttach;                        //lne文件最后一行
    volatile int m_nDatSize;                    //dat文件大小

    bool m_bLRC;                                //是否为长录波文件
    QDateTime m_tmLeft;                         //最左时刻
    unsigned short  m_wLeftMiniSec;             //毫秒数
//    char m_chTemp[512];                         //临时缓冲
    QString m_strTmp;                           //临时串

    volatile bool m_bHaveLoad;                  //
    volatile bool m_bLoadFinished;              //文件载入是否完成

    bool m_bWgl9000;                            //9000数据
    ReadThread* m_pThread;                      //数据读取线程
    bool m_bDigital;                            //是否为数字化录波器的录波文件(采样率4K)
    QString m_strRecName;                       //录波器名称
    QString m_strTimeFinalpart;                 //启动时间字符串的最后一部分
    QString m_strTimeFinalpartL;                //开始时间字符串最后一部分

    //////////////////////////////////////////////////////////////////////////
    //2011-06-16添加
    //开关量显示问题
    //[[
    bool m_bShowVal;                            //是否显示为开合
    bool m_bZeroH;                              //0合1开
    QString m_strDes0;                          //0显示的值
    QString m_strDes1;                          //1显示的值
    QString m_strWorkPath;                      //工作路径
    //]]

    bool m_bUpperCase;
    short m_usPhaseParam[260];                  //角度补偿值
    //闰秒处理
    unsigned int m_nleap_command;
    unsigned int m_nleap_ltime;

//    QString m_strStationName;
    QString m_strVersion;
    QString m_strReference;
    QString m_strRecDevName;
    QString m_strRecRef;
public:
    int m_nACount;                              //模拟量数目
    int m_nDCount;                              //开关量数目
    char *m_chTrigInfo;                         //启动原因
    int m_nTrigCount;

    QString m_strFaultLine;
    float m_fDistance;
    QString m_strFaultPhase;
    QString m_strDevCode;

    float m_fTimemult;

    //2017-12-11添加
    int m_nFaultLine;                           //初步判断的故障线路
    int m_nFaultPhase;                          //初步判断的故障相别(A=0,B=1,C=2)

    //2018-03-01添加(兼容60Hz)
    float m_fParam60HZ;                           //频率/50.
};

#endif // !defined(WYANALYZE_COMTDFILE_H_)
