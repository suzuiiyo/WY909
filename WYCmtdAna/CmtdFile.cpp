 //////////////////////////////////////////////////////////////////////////
//Copyright (c)2007 武汉国电武仪
//All rights reserved.
//
//文 件 名 : CmtdFile.cpp
//文件类型 : cpp
//版本 : ver 1.0
//编    制 : wpf
//描    述 : 读COMTRADE文件类实现;
//备    注 : 1> 可读取WGL3000文件和WGL9000文件
//          2> 支持cfg文件关于采样段描述的两种方式
//          3> 支持二进制dat文件
//
//--------------------------------------------------------
//版本历史:
//--------------------------------------------------------
//ver 1.0		2007-06-12		创建初始版本
//
//
//
//////////////////////////////////////////////////////////////////////////

#include "CmtdFile.h"
#include <memory.h>
#include <math.h>
#include "readthread.h"
#include <QThread>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QMutex>
#include <QWaitCondition>
#include <QSettings>
#include <QDir>
#include "CnCodec.h"
#include <QCoreApplication>
#include "EleBus.h"
#include "DMFReader.h"
#include <time.h>
#include "Markup.h"
#include "EleDChanel.h"
#include "stdint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCmtdFile::CCmtdFile()
{
    m_bWgl9000 = true;
    m_bHaveLoad = false;
    m_bLoadFinished = false;
    m_pSegment = NULL;
    m_arRemark.clear();
    m_bBinaryFile = false;
    m_dMaxUAbs = 0;
    m_dMaxIAbs = 0;
    m_dMaxZAbs = 0;
    m_nACount = 0;
    m_nDCount = 0;
    m_nChanelCount = 0;
    m_nFrate = 50;
    m_nSegCount = 0;
    m_nTotalPoints = 0;

    m_pSampleTime.clear();
    m_pSegment = NULL;
    m_bHaveOpenFile = false;
    m_strFilePath = "";
    m_dTimeSpan = 0;
    m_nTbPos = 0;
    m_bTransRec = false;
    m_bExternFile = false;
    m_wCmtdYear = 1991;
    memset(m_chErrorInfo,0,sizeof(m_chErrorInfo));
    m_bLRC = false;
//    memset(m_chTemp,0,sizeof(m_chTemp));
    
    m_dMaxZAbs_ZL_OTHER = 0;
    m_dMaxZAbs_ZL_30V_GP = 0;
    m_dMaxZAbs_ZL_5V_VOL = 0;
    m_dMaxZAbs_ZL_300V_VOL = 0;
    m_dMaxZAbs_ZL_2000V_VOL = 0;
    m_dMaxZAbs_ZL_ZL_200MV_VOL = 0;
    m_dMaxZAbs_ZL_ZL_4TO20MA_INF = 0;
    m_dMaxZAbs_ZL_JL_57V_VOL = 0;
    m_dMaxZAbs_ZL_JL_100V_VOL = 0;
    m_dMaxZAbs_ZL_JL_5A_INF = 0;
    m_dMaxZAbs_ZL_JL_1A_INF = 0;
    m_dMaxZAbs_ZL_ZP_100V_VOL = 0;
    m_dMaxZAbs_ZL_ZP_400V_VOL = 0;
    m_dMaxZAbs_ZL_ZP_5A_INF = 0;
    m_dMaxZAbs_ZL_ZL_PINLV = 0;
    
    m_pThread = new ReadThread;

    m_strWorkPath = QCoreApplication::applicationDirPath();
    m_strWorkPath += QString("/sys_config.ini");
    QSettings qset(m_strWorkPath,QSettings::IniFormat);
    m_bShowVal = qset.value("Device/dshw",0).toBool();
    m_bZeroH = qset.value("Device/dsts",0).toBool();
    m_strDevCode = qset.value("Device/devno",QString("2016001")).toString();
    if(m_bShowVal)
    {
        m_strDes0 = QString("0");
        m_strDes1 = QString("1");
    }
    else if(m_bZeroH)
    {
        m_strDes0 = QString("合");
        m_strDes1 = QString("开");
    }
    else
    {
        m_strDes0 = QString("开");
        m_strDes1 = QString("合");
    }
    m_bUpperCase = true;
    m_nleap_command = 0;
    m_nleap_ltime = 0;

    m_strReference = QString("1");
    m_strVersion = QString("1.0");
    m_chTrigInfo = NULL;
    m_nTrigCount = 0;
    m_fTimemult = 1;
    m_nFaultLine = 0;
    m_nFaultPhase = 0;
    m_fParam60HZ = 1;
}

CCmtdFile::~CCmtdFile()
{
    FreeMemory();
    m_pThread->deleteLater();
}

void CCmtdFile::GetFilePath(const QString &strCfgPath)
{
    m_bUpperCase = false;
    if(strCfgPath.indexOf(".CFG") > 0)
    {
        m_bUpperCase = true;
    }
    QFileInfo finfo(strCfgPath);
    QString strPath = finfo.absolutePath()+QString("/%1").arg(finfo.completeBaseName());
    m_strFilePath = strPath;
    if(m_bUpperCase)
    {
        m_strCfgFilePath = strPath + QString(".CFG");
        m_strDatFilePath = strPath + QString(".DAT");
        m_strLneFilePath = strPath + QString(".LNE");
        m_strDMFFilePath = strPath + QString(".DMF");
        m_strRmkFilePath = strPath + QString(".RMK");
        m_strHdrFilePath = strPath + QString(".HDR");
        m_strPrvFilePath = strPath + QString(".PRV");
        m_strExtFilePath = strPath + QString(".EXT");
    }
    else
    {
        m_strCfgFilePath = strPath + QString(".cfg");
        m_strDatFilePath = strPath + QString(".dat");
        m_strLneFilePath = strPath + QString(".lne");
        m_strDMFFilePath = strPath + QString(".dmf");
        m_strRmkFilePath = strPath + QString(".rmk");
        m_strHdrFilePath = strPath + QString(".hdr");
        m_strPrvFilePath = strPath + QString(".prv");
        m_strExtFilePath = strPath + QString(".ext");
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 读COMTRADE文件(本类的入口)
//参	数: a_strCfgFilePath cfg文件路径
//返 回	值:
//备	注:
//创建日期: 2007-06-12  wpf
//修改记录: 2007-11-27  wpf  加入C、D段值的处理(实时值为实部和虚部形式)
//		   2007-11-28  wpf	 加入零时刻的修正
//          2008-05-04	wpf	 加入对wy2文件和ext文件的支持
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::ReadComtradeFile(const QString& a_strCfgFilePath)
{
    m_bLoadFinished = false;
    m_bDigital = false;
    m_fParam60HZ = 1;

    m_nleap_command = 0;
    m_nleap_ltime = 0;
    memset(m_usPhaseParam,0,sizeof(m_usPhaseParam));
    GetFilePath(a_strCfgFilePath);

    try
    {
        //如果是wy2文件,先解包[[
        m_strTmp = a_strCfgFilePath;
        if(!QFile::exists(m_strTmp))
        {
            sprintf(m_chErrorInfo,"error 0001: file not exist![%s]",m_strTmp.toLocal8Bit().constData());
            return false;
        }
        //m_strTmp.toLower();
        if(m_strTmp.indexOf(".wy2") >= 0)
        {
            if(!UnPackgeFile(m_strTmp))
            {
                strcpy(m_chErrorInfo,"error 0002: wy2 file depackge failed!");
                return false;
            }
        }
        //]]
        m_strAttach = "";
        FreeMemory();
        
        m_bHaveOpenFile = false;
        m_bTransRec = false;
        m_bExternFile = false;


        if(!QFile::exists(m_strCfgFilePath))
        {
            strcpy(m_chErrorInfo,"error 0003: cfg file not exist!");
            return false;
        }
        if(!QFile::exists(m_strDatFilePath))
        {
            strcpy(m_chErrorInfo,"error 0004: dat file not exist!");
            return false;
        }
        
        if(!ReadCfgFile())
        {
            FreeMemory();
 //           strcpy(m_chErrorInfo,"error 0005: read cfg file error!");
            return false;
        }

        int npos = 0;
        for(int i=0; i<m_nSegCount; i++)
        {
            m_pSegment[i].m_nStartPos = npos;
            npos += m_pSegment[i].m_nCount;
        }

        /*
        if(QFile::exists(m_strLneFilePath))         //lne文件
        {
            if(!ReadLneFile())
            {
//                m_bExternFile = true;
            }
        }
        else if(QFile::exists(m_strDMFFilePath))    //DMF文件
        {
            if(!ReadDMFFile(m_strDMFFilePath))
            {
                //                m_bExternFile = true;
            }
            GetAttatch();
        }
        */
        if(QFile::exists(m_strDMFFilePath))    //DMF文件
        {
            if(!ReadDMFFile(m_strDMFFilePath))
            {
                //                m_bExternFile = true;
            }
            GetAttatch();
        }
        else if(QFile::exists(m_strLneFilePath))         //lne文件
        {
            if(!ReadLneFile())
            {
//                m_bExternFile = true;
            }
        }

        else if(!ReadHdrFile())                     //hdr文件
        {
//            m_bExternFile = true;	//为其他公司的文件
        }

        if(QFile::exists(m_strExtFilePath))
        {
            ReadExtFile();
        }

        if(m_arLine.count() <= 0)
        {
            m_bExternFile = true;
        }
        
        if(m_bBinaryFile)
        {
            if(!ReadBinaryDatFile())
            {
                FreeMemory();
                return false;
            }
        }
        else
        {
            if(!ReadAsciiDatFile())
            {
                FreeMemory();
                return false;
            }
//            m_bLoadFinished = true;
        }

        ReadPrvFile();
        ReadRmkFile();
//        GeneratePTCT();

        GenerateTransInfo();
        ReadDCExtend();
        for(int i=0; i<m_arLine.count(); i++)
        {
            m_arLine[i]->m_nSwitchCount = m_arLine[i]->m_arDChanel.count();
        }
        return true;
    }
    catch(...)
    {
        strcpy(m_chErrorInfo,"error 006: exception.");
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 读Cfg文件
//参	数:	
//返 回	值:
//备	注:
//创建日期: 2007-06-12  wpf
//修改记录: 
//	2007-06-03  wpf  把每周波采样不到1点的改为1点
//	2007-11-28  wpf	 二进制文件时,不初始化内存
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::ReadCfgFile()
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");

    QFile cfgfile(m_strCfgFilePath);

    if(!cfgfile.open(QIODevice::ReadOnly))
    {
        sprintf(m_chErrorInfo,"error 0007: Open cfg file failed. FilePath = %s",m_strCfgFilePath.toLatin1().constData());
        ////delete gbk;
        return false;
    }
    if(cfgfile.size() < 20)
    {
        cfgfile.close();
        strcpy(m_chErrorInfo,"error 0008: cfg file is empty.(<20bytes)");
        ////delete gbk;
        return false;
    }
    char chline[2048] = {0};
    const int size = 2048;
    cfgfile.readLine(chline,size);
    QString strline = gbk->toUnicode(chline);
    QString strt;
    const QString strsplit = QString(",");
    QStringList arstr = strline.split(strsplit);
    if(arstr.count() < 2)
    {
        strcpy(m_chErrorInfo,"error 0009: cfg file is error(line 1).");
        ////delete gbk;
        return false;
    }
    //line 1: StationName,RecId,Year
    m_strStationName = arstr.at(0);
    m_nRecId = arstr.at(1).toInt();
    if(arstr.count() == 3)
    {
        m_wCmtdYear = arstr.at(2).toInt();
    }
    //line2: CHNCount,ACount,DCount
    cfgfile.readLine(chline,size);
    strline = gbk->toUnicode(chline);
    arstr = strline.split(strsplit);
    if(arstr.count() != 3)
    {
        strcpy(m_chErrorInfo,"error 0009: cfg file is error(line 2).");
        cfgfile.close();
        ////delete gbk;
        return false;
    }
    m_nChanelCount = arstr.at(0).toInt();
    strt = arstr.at(1).toUpper();
    strt.replace("A","");
    m_nACount = strt.toInt();
    strt = arstr.at(2).toUpper();
    strt.replace("D","");
    m_nDCount = strt.toInt();

    if((m_nACount<=0)&&(m_nDCount<=0))
    {
        strcpy(m_chErrorInfo,"error 0010: cfg file is error(chanelcount=0).");
        cfgfile.close();
        ////delete gbk;
        return false;
    }

    //line 3~m_nACount:ID,Name,Phase,Unit1,Unit2,a,b,
    QString strCHName;
    QString strtmp;

    for(int i=0; i<m_nACount; i++)
    {
        CEleAChanel* pAChanel = new CEleAChanel;
        m_arAChanel.append(pAChanel);
        cfgfile.readLine(chline,size);
        strline = gbk->toUnicode(chline);
        arstr = strline.split(strsplit);
        if(arstr.count() < 10)
        {
            sprintf(m_chErrorInfo,"error 0009: cfg file is error(line %d).",2+i);
            cfgfile.close();
            ////delete gbk;
            return false;
        }
        pAChanel->m_strph = arstr.at(2);
        pAChanel->m_strccbm = arstr.at(3);
        pAChanel->m_struu = arstr.at(4);
        pAChanel->m_nmin = arstr.at(8).toInt();
        pAChanel->m_nmax = arstr.at(9).toInt();
        GetChanelsPhase(pAChanel);

        if(arstr.count() > 12)
        {
            pAChanel->m_fPrimary = arstr.at(10).toFloat();
            pAChanel->m_fSecondary = arstr.at(11).toFloat();

            if(arstr.at(12).toLower().indexOf(QString("s")) >= 0)
                pAChanel->m_ePS = CEleAChanel::ps_S;
            else
                pAChanel->m_ePS = CEleAChanel::ps_P;
        }

        pAChanel->m_wID = arstr.at(0).toInt();
        strcpy(pAChanel->m_chName,gbk->fromUnicode(arstr.at(1)));
        strCHName = arstr.at(1);
        //相别为空,根据名称判定相别
        strtmp = arstr.at(2);
        if(strtmp.isEmpty())
        {
            strCHName = strCHName.toLower();
            if(strCHName.indexOf("a")>=0)
            {
                strtmp = "a";
            }
            else if(strCHName.indexOf("b")>=0)
            {
                strtmp = "b";
            }
            else if(strCHName.indexOf("c")>=0)
            {
                strtmp = "c";
            }
            else if((strCHName.indexOf("n")>=0)||(strCHName.indexOf("0")>=0))
            {
                strtmp = "n";
            }
        }
        strtmp = strtmp.toLower();
        pAChanel->m_wType = 0;
        if(strtmp == "a")
        {
            pAChanel->m_crColor = Qt::yellow;
            pAChanel->m_wType = 1;	//=0  a
        }
        else if(strtmp == "b")
        {
            pAChanel->m_crColor = Qt::green;
            pAChanel->m_wType = 2;	//=1  b
        }
        else if(strtmp == "c")
        {
            pAChanel->m_crColor = Qt::red;
            pAChanel->m_wType = 3;	//=2  c
        }
        else if((strtmp == "n")||(strtmp == "0"))
        {
            pAChanel->m_crColor = Qt::white;
            pAChanel->m_wType = 4;	//=2  n
        }
        else//直流通道
        {
            pAChanel->m_crColor = Qt::white;
            pAChanel->m_wType = 5;	//=2  n
        }

        QString strTT;
        strTT = arstr.at(3);
        if(pAChanel->m_wType != 5)
        {
            strtmp = strTT.toUpper();
            strtmp.replace("K","k");
            strcpy(pAChanel->m_chUnit1,gbk->fromUnicode(strtmp));
            strTT = arstr.at(4);
            strtmp = strTT.toUpper();
            strtmp.replace("K","");
            strcpy(pAChanel->m_chUnit2,gbk->fromUnicode(strtmp));
        }
        else
        {
            strcpy(pAChanel->m_chUnit1,gbk->fromUnicode(strTT));
            strtmp = arstr.at(4);
            strcpy(pAChanel->m_chUnit2,gbk->fromUnicode(strtmp));
        }
        if((strtmp == "V")&&(pAChanel->m_wType>0)&&(pAChanel->m_wType<5))
        {
            pAChanel->m_wType = 1;
        }
        else if((strtmp == "A")&&(pAChanel->m_wType>0)&&(pAChanel->m_wType<5))
        {
            pAChanel->m_wType = 2;
        }
        else
        {
            pAChanel->m_wType = 3;
        }

        pAChanel->m_da = arstr.at(5).toFloat();
        pAChanel->m_db = arstr.at(6).toFloat();
        pAChanel->m_dSkew = arstr.at(7).toFloat();
        if(arstr.count() > 12)
            pAChanel->m_dPT = arstr.at(10).toFloat()/arstr.at(11).toFloat();

        pAChanel->m_dCT = pAChanel->m_dPT;
//        qDebug("%d CT=%.3f",i,pAChanel->m_dCT);
        pAChanel->m_dMaxAbs = 0;
    }

    //line 3+m_nACount~3+m_nACount+m_nDCount
    for(int i=0; i<m_nDCount; i++)
    {
        CEleDChanel* pDChanel = new CEleDChanel;
        m_arDChanel.append(pDChanel);
        if(cfgfile.readLine(chline,size) <= 0)
        {
            sprintf(m_chErrorInfo,"error 0009: cfg file is error(line %d).",2+m_nACount+i);
            cfgfile.close();
            ////delete gbk;
            return false;
        }
        strline = gbk->toUnicode(chline);
        arstr = strline.split(strsplit);
        if(arstr.count() < 3)
        {
            sprintf(m_chErrorInfo,"error 0009: cfg file is error(line %d).",2+m_nACount+i);
            cfgfile.close();
            ////delete gbk;
            return false;
        }

        pDChanel->m_wID = arstr.at(0).toInt();
        strcpy(pDChanel->m_chName,gbk->fromUnicode(arstr.at(1)));
        pDChanel->m_crColor = Qt::white;
    }

    //seg info
    cfgfile.readLine(chline,size);
//    m_nFrate = atoi(chline);
    m_nFrate = 50;
    //兼容60Hz [2018-03-01]
    m_fParam60HZ = atof(chline)/50.;
    cfgfile.readLine(chline,size);
    m_nSegCount = atoi(chline);
    // 兼容COMTRADE1997 [2/19/2008]
//    if(m_wCmtdYear == 1997)
//    {
//        m_nSegCount += 1;
//    }
    //]]
    if(m_nSegCount <= 0)
    {
        m_nSegCount += 1;
    }
    m_pSegment = new CCmtdSegment[m_nSegCount];
    int ntotalcount = 0;
    for(int i=0; i<m_nSegCount; i++)
    {
        cfgfile.readLine(chline,size);
        strline = gbk->toUnicode(chline);
        arstr = strline.split(strsplit);

        m_pSegment[i].m_nSecCount = atoi(arstr.at(0).toLocal8Bit().constData());
        m_pSegment[i].m_nWavePoints = m_pSegment[i].m_nSecCount/m_nFrate;
        m_pSegment[i].m_nCount = atoi(arstr.at(1).toLocal8Bit().constData());
        ntotalcount += m_pSegment[i].m_nCount;
        //2007-03-01 每周波不到一点的包罗线段,改为1
        //[[
        if(m_pSegment[i].m_nWavePoints <= 0)
            m_pSegment[i].m_nWavePoints = 1;
        //]]
    }
    m_nTotalPoints = ntotalcount;

    //读开始时间和启动录波时间
    cfgfile.readLine(chline,size);
    m_strLeftTime = gbk->toUnicode(chline);
    cfgfile.readLine(chline,size);
    m_strStartTime = gbk->toUnicode(chline);
    //加工这个时刻

    //dat文件格式ASCII或者BINARY
    cfgfile.readLine(chline,size);
    strtmp = gbk->toUnicode(chline);
    strtmp = strtmp.toUpper();
    if(strtmp.indexOf("ASCII")>=0)
        m_bBinaryFile = false;
    else
        m_bBinaryFile = true;
    //时标倍率因子Timemult
    cfgfile.readLine(chline,size);
    if(strlen(chline)>1)
        m_fTimemult = atof(chline);

    cfgfile.close();

    //---------------------------------------------------------------------
    //初始化内存
    //---------------------------------------------------------------------
    // 如果是二进制文件,不初始化内存 [11/28/2007]
    if(!m_bBinaryFile)
    {
        m_pSampleTime.resize(ntotalcount+10);
        for(int i=0; i<m_nACount; i++)
            m_arAChanel[i]->m_pData.resize(ntotalcount+10);
        for(int i=0; i<m_nDCount; i++)
            m_arDChanel[i]->m_pData.resize(ntotalcount/8+10);
    }

    //---------------------------------------------------------------------
    //获取两个时间的差值
    //---------------------------------------------------------------------
    m_wFaultMiniSec = 0;
    float dminiseconds = 0.0;
    float dminisecondf = 0.0;
    QDateTime tms = GetTimeFromString(m_strLeftTime,dminiseconds);
    QDateTime tmf = GetTimeFromString(m_strStartTime,dminisecondf);
    m_strTimeFinalpart = m_strStartTime;
    int npos = m_strTimeFinalpart.lastIndexOf('.');
    if(npos > 0)
    {
        m_strTimeFinalpart = m_strTimeFinalpart.right(m_strTimeFinalpart.length()-npos-1);
    }
    int nspec = tms.secsTo(tmf);
    m_dTimeSpan = (float)(fabs(nspec*1.0) * 1000.0 + dminisecondf-dminiseconds);	//两个时间的差值
    m_tmStart = tmf;
    if(dminisecondf < 1)
    {
        m_wFaultMiniSec = (unsigned int)(dminisecondf * 1000.0);
    }
    else
    {
        m_wFaultMiniSec = (unsigned int)(dminisecondf/* + 0.500001*/);
    }
    m_tmLeft = tms;
    if(dminiseconds < 1)
    {
        m_wLeftMiniSec = (unsigned short)(dminiseconds*1000.0);
    }
    else
    {
        m_wLeftMiniSec = (unsigned short)(dminiseconds/*+0.500001*/);
    }
    if(m_wLeftMiniSec > 1001)
    {
        m_wLeftMiniSec /= 1000;
    }

    strtmp = m_strStartTime;
    npos = strtmp.indexOf(',');
    if(npos >= 0)
    {
        strtmp.sprintf("%d-%d-%d ",tmf.date().year(),tmf.date().month(),tmf.date().day());
        m_strStartTime = m_strStartTime.right(m_strStartTime.length() - npos - 1);
        strtmp += m_strStartTime;
        m_strStartTime = strtmp;
    }
    ////delete gbk;
    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 从源串中读取并剪切第一个子串,各子串以a_ch字符隔开
//参	数:	a_strLine 源串;a_ch 分隔字符
//返 回	值:	子串
//备	注:
//创建日期: 2007-06-12  wpf
//修改记录: 
//			2007-06-17	wpf		最后一个单元时就=源串
//////////////////////////////////////////////////////////////////////////
QString CCmtdFile::GetLeftStr(QString &a_strLine, char a_ch)
{
    QString strtmp = "";
    int npos = a_strLine.indexOf(a_ch);
    if(npos>=0)
    {
        strtmp = a_strLine.left(npos);
        strtmp = strtmp.trimmed();
        a_strLine = a_strLine.right(a_strLine.length() - npos - 1);
    }
    else
    {
        strtmp = a_strLine;
    }
    return strtmp;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 读ASCII码Dat文件,根据采样点数目确定cfg文件中的采样段描述
//			是分段描述还是连续描述;统计各通道最大值,计算缩放因子
//参	数:	
//返 回	值:	成功返回true;否则返回false
//备	注:
//创建日期: 2007-06-12  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::ReadAsciiDatFile()
{
    unsigned int nsize = 0;
    QFileInfo finfo(m_strDatFilePath);
    nsize = finfo.size();
    if(nsize < 200)
    {
        sprintf(m_chErrorInfo,"dat文件内容不全,读文件失败! ");
        return false;
    }
    
    m_nDatSize = nsize;
    m_pThread->setFileInfo(this);
    m_pThread->start();          
    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 读二进制Dat文件,根据采样点数目确定cfg文件中的采样段描述
//			是分段描述还是连续描述;统计各通道最大值,计算缩放因子
//参	数:	
//返 回	值:	
//备	注:
//创建日期: 2007-06-12  wpf
//修改记录: 
//说	明: 一个数据单元 = 4字节点序号+4字节时间+模拟通道数*2+[开关通道数/8],
//			开关量16个通道一个单元,如17个开关通道,需要4字节存储
//
//			2009-09-29 修改
//			数据过大时添加一个数据窗
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::ReadBinaryDatFile()
{
    //////////////////////////////////////////////////////////////////////////
    //根据通道数目计算数据单元长度
    int anasize = 0;
    int digsize = 0;
    anasize = m_nACount*2;
    digsize = m_nDCount/8;
    if(m_nDCount%8 != 0)
    {
        digsize += 1;
    }
    if(digsize%2 != 0)
    {
        digsize += 1;
    }
    
    int blocksize = 8 + anasize + digsize;
    
    m_bHaveLoad = false;
    
    //////////////////////////////////////////////////////////////////////////
    //文件大小<200字节的,认为文件残缺,不打开
    QFileInfo finfo(m_strDatFilePath);
    int nsize = finfo.size();
    if(nsize < 200)
    {
        sprintf(m_chErrorInfo,"dat文件内容不全,读文件失败! ");
        qDebug("dat文件内容不全,读文件失败!");
        return false;
    }
    m_nDatSize = nsize;
    
    //////////////////////////////////////////////////////////////////////////
    //统计采样段
    int nTotalPoints = m_nDatSize/blocksize;
    int i = 0;
    if(m_pSegment[m_nSegCount-1].m_nCount > nTotalPoints-2)  //是累加的
    {
        for(i=m_nSegCount-1; i>0; i--)
        {
            m_pSegment[i].m_nCount -= m_pSegment[i-1].m_nCount;
        }
    }
    m_pThread->setFileInfo(this);
    m_pThread->start();
    
    return true;
}

void CCmtdFile::removeEleItem()
{
    qDeleteAll(m_arBus);
    qDeleteAll(m_arLine);
    qDeleteAll(m_arTrans);
    qDeleteAll(m_arDC);
    qDeleteAll(m_arExciter);
    qDeleteAll(m_arGenerator);
    m_arBus.clear();
    m_arLine.clear();
    m_arDC.clear();
    m_arTrans.clear();
    m_arGenerator.clear();
    m_arExciter.clear();
}

//////////////////////////////////////////////////////////////////////////
//功	能: 读Lne文件
//参	数:	
//返 回	值:	有错误返回false,否则返回true
//备	注:
//创建日期: 2007-06-12  wpf
//修改记录: 
//2007-06-13	wpf		加入从lne文件中读取主变信息的代码
//2007-06-19    wpf		加入判断,如果没有III侧和IV侧,置NULL
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::ReadLneFile()
{
    removeEleItem();
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QFile lnefile(m_strLneFilePath);
    if(!lnefile.open(QIODevice::ReadOnly))
    {
        sprintf(m_chErrorInfo,"error 0011: Lne file open failed. (file path=%s)",m_strLneFilePath.toLocal8Bit().constData());
        return false;
    }

    //变量定义[[
    QString strtmp;
    QString strline;
    char* chline = new char[4096];
    const int size = 4096;
    const QString strsplit = QString(",");
    QStringList arstr;
    int i = 0;
    int nBus = 0;
    QString strt;
    int nzlcount = 0;
    int ntdnum = 0;
    int nLineIndex = 0;
    //]]

    //line 1
    lnefile.readLine(chline,size);
    strline = gbk->toUnicode(chline);
    if(!strline.contains(QString("COMTRADE_HDR")))
    {
        sprintf(m_chErrorInfo,"error 0012: Lnefile error. (line 1)");
        lnefile.close();
        delete []chline;
        return false;
    }
    removeEleItem();
    int npos = strline.indexOf(QString("Ver"));
    if(npos > 0)
        strtmp = strline.right(strline.length() - npos - 3);
    float dlnever = strtmp.toFloat();

    //line 2
    lnefile.readLine(chline,size);
    strline = gbk->toUnicode(chline);
    arstr = strline.split(strsplit);
    if(arstr.count() < 3)
    {
        strcpy(m_chErrorInfo,"error 0012: Lnefile error. (line 2)");
        lnefile.close();
        delete []chline;
        return false;
    }
    int nBusCount=0,nLineCount=0,nDCCount=0,nTransCount=0;
    nBusCount = arstr.at(0).toInt();
    nLineCount = arstr.at(1).toInt();
    nDCCount = arstr.at(2).toInt();
    if(dlnever > 1.0)
    {
       nTransCount = arstr.at(3).toInt();
    }
    for(i=0; i<nBusCount; i++)
    {
        CEleBus* pBus = new CEleBus();
        m_arBus.append(pBus);
    }
    for(i=0; i<nLineCount; i++)
    {
        CEleLine* pLine = new CEleLine();
        m_arLine.append(pLine);
    }
    for(i=0; i<nDCCount; i++)
    {
        CEleDC* pDC = new CEleDC();
        m_arDC.append(pDC);
    }
    for(i=0; i<nTransCount; i++)
    {
        CEleTrans* pTrans = new CEleTrans();
        m_arTrans.append(pTrans);
    }

    //读母线信息
    //line 3~3+m_nBusCount
    //[[
    for(i=0; i<nBusCount; i++)
    {
        if(lnefile.readLine(chline,size) <= 0)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",3+i);
            lnefile.close();
            delete []chline;
            return false;
        }
        strline = gbk->toUnicode(chline);
        arstr = strline.split(strsplit);
        if(arstr.count() < 7)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",3+i);
            lnefile.close();
            delete []chline;
            return false;
        }

        m_arBus[i]->m_wID = i+1;
        strcpy(m_arBus[i]->m_chName,gbk->fromUnicode(arstr.at(1)));
        m_arBus[i]->m_wAID = arstr.at(2).toInt();
        m_arBus[i]->m_wBID = arstr.at(3).toInt();
        m_arBus[i]->m_wCID = arstr.at(4).toInt();
        m_arBus[i]->m_wNID = arstr.at(5).toInt();
        m_arBus[i]->m_dVoltage = arstr.at(6).toFloat();

        int nphase = 0;
        for(int j=0; j<m_nACount; j++)
        {
            if(m_arAChanel[j]->m_wID == m_arBus[i]->m_wAID)
            {
                m_arBus[i]->m_pAChanel = m_arAChanel[j];
                nphase++;
            }
            if(m_arAChanel[j]->m_wID == m_arBus[i]->m_wBID)
            {
                m_arBus[i]->m_pBChanel = m_arAChanel[j];
                nphase++;
            }
            if(m_arAChanel[j]->m_wID == m_arBus[i]->m_wCID)
            {
                m_arBus[i]->m_pCChanel = m_arAChanel[j];
                nphase++;
            }
            if(m_arAChanel[j]->m_wID == m_arBus[i]->m_wNID)
            {
                m_arBus[i]->m_pNChanel = m_arAChanel[j];
                nphase++;
            }
            if(nphase >= 4)
            {
                break;
            }
        }
    }
    //]]

    //读线路信息
    //line 3+m_nBusCount~3+m_nBusCount+m_arLine.count()
    //[[
    for(i=0; i<nLineCount; i++)
    {
        if(lnefile.readLine(chline,size) <= 0)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",3+nBusCount+i);
            lnefile.close();
            delete []chline;
            return false;
        }
        strline = gbk->toUnicode(chline);
        arstr = strline.split(strsplit);
        if(arstr.count() < 21)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",3+nBusCount+i);
            lnefile.close();
            delete []chline;
            return false;
        }
        m_arLine[i]->m_wID = i+1;
        strcpy(m_arLine[i]->m_chName,gbk->fromUnicode(arstr.at(1)));
        m_arLine[i]->m_wAID = arstr.at(2).toInt();
        m_arLine[i]->m_wBID = arstr.at(3).toInt();
        m_arLine[i]->m_wCID = arstr.at(4).toInt();
        m_arLine[i]->m_wNID = arstr.at(5).toInt();
        nBus = arstr.at(6).toInt();
        //arstr.at(7); 线路/主变
        if(arstr.at(8).toInt() == 0)
        {
            m_arLine[i]->m_bDistance = false;
        }
        else
        {
            m_arLine[i]->m_bDistance = true;
        }
        m_arLine[i]->m_dR1 = arstr.at(9).toFloat();
        m_arLine[i]->m_dX1 = arstr.at(10).toFloat();
        m_arLine[i]->m_dR0 = arstr.at(11).toFloat();
        m_arLine[i]->m_dX0 = arstr.at(12).toFloat();
        m_arLine[i]->m_nHgLine = arstr.at(13).toInt()-1;
        m_arLine[i]->m_dRh = arstr.at(14).toFloat();
        m_arLine[i]->m_dXh = arstr.at(15).toFloat();
        m_arLine[i]->m_dMaxI = arstr.at(16).toFloat();
        m_arLine[i]->m_dCT = arstr.at(17).toFloat();
        m_arLine[i]->m_dLength = arstr.at(18).toFloat();
        m_arLine[i]->m_sGp1 = arstr.at(19).toInt();
        m_arLine[i]->m_sGp2 = arstr.at(20).toInt();

        //查找各通道和所接母线
        int nphase = 0;
        for(int j=0; j<m_nACount; j++)
        {
            if(m_arAChanel[j]->m_wID == m_arLine[i]->m_wAID)
            {
                m_arLine[i]->m_pAChanel = m_arAChanel[j];
                nphase++;
            }
            if(m_arAChanel[j]->m_wID == m_arLine[i]->m_wBID)
            {
                m_arLine[i]->m_pBChanel = m_arAChanel[j];
                nphase++;
            }
            if(m_arAChanel[j]->m_wID == m_arLine[i]->m_wCID)
            {
                m_arLine[i]->m_pCChanel = m_arAChanel[j];
                nphase++;
            }
            if(m_arAChanel[j]->m_wID == m_arLine[i]->m_wNID)
            {
                m_arLine[i]->m_pNChanel = m_arAChanel[j];
                nphase++;
            }
            if(nphase >= 4)
            {
                break;
            }
        }
        nBus -= 1;
        m_arLine[i]->m_wBusId = nBus+1;
        if((nBus>=0)&&(nBus<nBusCount))
        {
            m_arLine[i]->m_pBus = m_arBus[nBus];
            m_arLine[i]->m_dVoltage = m_arBus[nBus]->m_dVoltage;
        }
        else if(nBusCount > 0)
        {
            m_arLine[i]->m_pBus = m_arBus[0];
            m_arLine[i]->m_dVoltage = m_arBus[0]->m_dVoltage;
        }
    }
    //]]

    //读直流信息
    //line 3+m_nBusCount+m_arLine.count() ~ 3+m_nBusCount+m_arLine.count()+m_arDC.count()
    //[[
    for(i=0; i<nDCCount; i++)
    {
        if(lnefile.readLine(chline,size) <= 0)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",3+nBusCount+nLineCount+i);
            lnefile.close();
            delete []chline;
            return false;
        }
        strcpy(m_arDC[i]->m_chKind,"\0");
        strline = gbk->toUnicode(chline);
        arstr = strline.split(strsplit);
        if(arstr.count() < 6)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",3+nBusCount+nLineCount+i);
            lnefile.close();
            delete []chline;
            return false;
        }

        strcpy(m_arDC[i]->m_chName,gbk->fromUnicode(arstr.at(1)));	//名称
        ntdnum = arstr.at(2).toInt();                                  //通道号
        m_arDC[i]->m_pChanel = GetAChanelById(ntdnum);
        if(m_arDC[i]->m_pChanel == NULL)
        {
            continue;
        }
        m_arDC[i]->m_wChanelID = m_arDC[i]->m_pChanel->m_wID;
        strcpy(m_arDC[i]->m_chKind,gbk->fromUnicode(arstr.at(3)));    //类型
        strt = arstr.at(3);
        if(strt.indexOf(QString("直流5V")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::ZL_5V_VOL;
        else if(strt.indexOf(QString("直流30V")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::ZL_30V_GP;
        else if(strt.indexOf(QString("直流300V")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::ZL_300V_VOL;
        else if(strt.indexOf(QString("直流2000V")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::ZL_2000V_VOL;
        else if(strt.indexOf(QString("直流200mV")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::ZL_200MV_VOL;
        else if(strt.indexOf(QString("直流4-20mA")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::ZL_4TO20MA_INF;
        else if(strt.indexOf(QString("交流57.74V")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::JL_57V_VOL;
        else if(strt.indexOf(QString("交流100V")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::JL_100V_VOL;
        else if(strt.indexOf(QString("交流5A")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::JL_5A_INF;
        else if(strt.indexOf(QString("交流1A")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::JL_1A_INF;
        else if(strt.indexOf(QString("中频100V")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::ZP_100V_VOL;
        else if(strt.indexOf(QString("中频400V")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::ZP_400V_VOL;
        else if(strt.indexOf(QString("中频5A")) >= 0)
            m_arDC[i]->m_nKind = CEleDC::ZP_5A_INF;
        else
            m_arDC[i]->m_nKind = CEleDC::ZL_OTHER;

        //////////////////////////////////////////////////////////////////////////
        //适应刻度做的修改
        //2010-04-12
        //[[
        m_arDC[i]->m_pChanel->m_wType = m_arDC[i]->m_nKind;
        //]]

        strcpy(m_arDC[i]->m_chUnit1,gbk->fromUnicode(arstr.at(4)));
        m_arDC[i]->m_dFactor = arstr.at(5).toFloat();
        m_arDC[i]->m_dFactor /= 1000;
        nzlcount++;
    }

    //]]

    //读主变信息
    //line 3+m_nBusCount+m_arLine.count()+m_arDC.count()+1 ~ 3+m_nBusCount+m_arLine.count()+nDCCount+1+m_nTransCount
    //[[
    if(nTransCount > 0)
    {
        m_bTransRec = true;
    }
    if(dlnever < 1.001)
    {
        nTransCount = 0;
    }

    for(i=0; i<nTransCount; i++)
    {
        if(lnefile.readLine(chline,size) <= 0)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",3+nBusCount+nLineCount+nDCCount+i);
            lnefile.close();
            delete []chline;
            return false;
        }
        strline = gbk->toUnicode(chline);
        arstr = strline.split(strsplit);
        if(arstr.count() < 21)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",3+nBusCount+nLineCount+nDCCount+i);
            lnefile.close();
            delete []chline;
            return false;
        }
        m_arTrans[i]->m_nLineCount = 1;
        strcpy(m_arTrans[i]->m_chName,gbk->fromUnicode(arstr.at(1)));
        nLineIndex = arstr.at(2).toInt()-1;
        m_arTrans[i]->m_wBraID[0] = nLineIndex+1;
        if((nLineIndex >= 0)&&(nLineIndex<nLineCount))
        {
            m_arTrans[i]->m_pLine[0] = m_arLine[nLineIndex];					//I侧电流编号,基于1
            m_arTrans[i]->m_nType[0] = arstr.at(3).toInt();                     //I侧接线方式
            m_arTrans[i]->m_dFactor[0] = arstr.at(4).toFloat();                 //I侧平衡系数
            m_arTrans[i]->m_dMaxI[0] = m_arTrans[i]->m_pLine[0]->m_dMaxI;		//I侧额定电流
            m_arTrans[i]->m_bInvert[0] = arstr.at(5).toInt();                   //I侧是否反向
        }
        else
        {
            m_arTrans[i]->m_pLine[0] = NULL;
        }

        nLineIndex = arstr.at(6).toInt()-1;
        m_arTrans[i]->m_wBraID[1] = nLineIndex+1;
        if((nLineIndex >= 0)&&(nLineIndex<nLineCount))
        {
            m_arTrans[i]->m_pLine[1] = m_arLine[nLineIndex];                 //II侧电流编号,基于1
            m_arTrans[i]->m_nType[1] = arstr.at(7).toInt();                    //II侧接线方式
            m_arTrans[i]->m_dFactor[1] = arstr.at(8).toFloat();                //II侧平衡系数
            m_arTrans[i]->m_dMaxI[1] = m_arTrans[i]->m_pLine[1]->m_dMaxI;          //II侧额定电流
            m_arTrans[i]->m_bInvert[1] = arstr.at(9).toInt();                  //II侧是否反向
            m_arTrans[i]->m_nLineCount = 2;
        }
        else
        {
            m_arTrans[i]->m_pLine[1] = NULL;
        }

        nLineIndex = arstr.at(10).toInt()-1;
        m_arTrans[i]->m_wBraID[2] = nLineIndex+1;
        if((nLineIndex >= 0)&&(nLineIndex<nLineCount))
        {
            m_arTrans[i]->m_pLine[2] = m_arLine[nLineIndex];                //III侧电流编号,基于1
            m_arTrans[i]->m_nType[2] = arstr.at(11).toInt();                  //III侧接线方式
            m_arTrans[i]->m_dFactor[2] = arstr.at(12).toFloat();              //III侧平衡系数
            m_arTrans[i]->m_dMaxI[2] = m_arTrans[i]->m_pLine[2]->m_dMaxI;        //III侧额定电流
            m_arTrans[i]->m_bInvert[2] = arstr.at(13).toInt();                //III侧是否反向
            m_arTrans[i]->m_nLineCount = 3;
        }
        else
        {
            m_arTrans[i]->m_pLine[2] = NULL;
        }

        nLineIndex = arstr.at(14).toInt()-1;
        m_arTrans[i]->m_wBraID[3] = nLineIndex+1;
        if((nLineIndex >= 0)&&(nLineIndex<nLineCount))
        {
            m_arTrans[i]->m_pLine[3] = m_arLine[nLineIndex];             //IV侧电流编号,基于1
            m_arTrans[i]->m_nType[3] = arstr.at(15).toInt();               //IV侧接线方式
            m_arTrans[i]->m_dFactor[3] = arstr.at(16).toFloat();           //IV侧平衡系数
            m_arTrans[i]->m_dMaxI[3] = m_arTrans[i]->m_pLine[3]->m_dMaxI;	//IV侧额定电流
            m_arTrans[i]->m_bInvert[3] = arstr.at(17).toInt();             //IV侧是否反向
            m_arTrans[i]->m_nLineCount = 4;
        }
        else
        {
            m_arTrans[i]->m_pLine[3] = NULL;
        }

        m_arTrans[i]->m_dIcd = arstr.at(18).toFloat();                    //最小动作电流
        m_arTrans[i]->m_dIsd = arstr.at(19).toFloat();                    //速断电流
        m_arTrans[i]->m_nKind = arstr.at(20).toInt();                     //算法类型(0:南瑞;1:四方)
    }
    //]]

    //读开关量信息
    //[[
    int nline = 3+nBusCount+nLineCount+nDCCount+nTransCount;
    if(nLineCount > 0)
    {
        if(lnefile.readLine(chline,size) <= 0)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",nline);
            lnefile.close();
            delete []chline;
            return false;
        }
        strline = gbk->toUnicode(chline);
        arstr = strline.split(strsplit);
        if(arstr.count() < nLineCount)
        {
            sprintf(m_chErrorInfo,"error 0014: Lnefile error. (line %d)",nline);
            lnefile.close();
            delete []chline;
            return false;
        }
        for(i=0; i<nLineCount; i++)
        {
            m_arLine[i]->m_nSwitchCount = arstr.at(i).toInt();
        }
    }
    QString strn;
    int nkind = 0;
    int nNum = 0;
    for(i=0; i<nLineCount; i++)
    {
        if(lnefile.readLine(chline,size) <= 0)
        {
            sprintf(m_chErrorInfo,"error 0013: Lnefile not completely. (line %d)",nline+1+i);
            lnefile.close();
            delete []chline;
            return false;
        }
        strline = gbk->toUnicode(chline);
        arstr = strline.split(strsplit);
//        qDebug("%d",arstr.count());
        if(arstr.count() < m_arLine[i]->m_nSwitchCount+1)
        {
            sprintf(m_chErrorInfo,"error 0014: Lnefile error. (line %d)",nline+1+i);
            lnefile.close();
            delete []chline;
            return false;
        }

        for(int j=0; j<m_arLine[i]->m_nSwitchCount; j++)
        {
            strt = arstr.at(j+1);
            strn = GetLeftStr(strt,':');
            nNum = strn.toInt();
            if((nNum<=0)||(nNum>m_nDCount))
            {
                continue;
            }
            m_arLine[i]->m_arDChanel.append(nNum);
            nkind = strt.toInt();
            switch(nkind)
            {
            case 0:
            {
                m_arDChanel[nNum-1]->m_eType = CEleDChanel::Other;
                m_arDChanel[nNum-1]->m_strFlag = QString("general");
            }
                break;
            case 21:
            {
                m_arDChanel[nNum-1]->m_eType = CEleDChanel::Relay;
                m_arDChanel[nNum-1]->m_strFlag = QString("TrPhsA");
            }
                break;
            case 22:
            {
                m_arDChanel[nNum-1]->m_eType = CEleDChanel::Relay;
                m_arDChanel[nNum-1]->m_strFlag = QString("TrPhsB");
            }
                break;
            case 23:
            {
                m_arDChanel[nNum-1]->m_eType = CEleDChanel::Relay;
                m_arDChanel[nNum-1]->m_strFlag = QString("TrPhsC");
            }
                break;
            case 24:
            {
                m_arDChanel[nNum-1]->m_eType = CEleDChanel::Relay;
                m_arDChanel[nNum-1]->m_strFlag = QString("OpTP");
            }
                break;
            case 25:
            case 26:
            {
                m_arDChanel[nNum-1]->m_eType = CEleDChanel::Relay;
                m_arDChanel[nNum-1]->m_strFlag = QString("RecOpCls");
            }
                break;
            default:
                break;
            }
        }
    }
    //]]

    //attatch
    while(lnefile.readLine(chline,size) > 0)
    {
        strline = gbk->toUnicode(chline);
        if(strline.indexOf(QString("[attach]")) >= 0)
        {
            m_strAttach = strline;
            break;
        }
    }
    lnefile.close();

    delete []chline;
    ////delete gbk;
    return true;
}

bool CCmtdFile::GetAttatch()
{
    QFile lnefile(m_strLneFilePath);
    if(!lnefile.open(QIODevice::ReadOnly))
    {
        sprintf(m_chErrorInfo,"error 0011: Lne file open failed. (file path=%s)",m_strLneFilePath.toLocal8Bit().constData());
        return false;
    }

    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    //attatch
    char* chline = new char[4096];
    const int size = 4096;
    QString strline;
    while(lnefile.readLine(chline,size) > 0)
    {
        strline = gbk->toUnicode(chline);
        if(strline.indexOf(QString("[attach]")) >= 0)
        {
            m_strAttach = strline;
            break;
        }
    }
    lnefile.close();

    delete []chline;
    ////delete gbk;
    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 释放内存
//参	数:	
//返 回	值:	
//备	注: 释放内存(打开新文件时调用此函数)
//创建日期: 2007-06-12  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
void CCmtdFile::FreeMemory()
{
    try
    {
        qDeleteAll(m_arAChanel);
        qDeleteAll(m_arDChanel);

        if(m_pSegment != NULL)
        {
            delete []m_pSegment;
            m_pSegment = NULL;
        }

        if(m_chTrigInfo != NULL)
        {
            delete []m_chTrigInfo;
            m_chTrigInfo = NULL;
            m_nTrigCount = 0;
        }

        qDeleteAll(m_arRemark);
        m_arRemark.clear();
        m_pSampleTime.clear();

        removeEleItem();

        m_arAChanel.clear();
        m_arDChanel.clear();
        m_pSegment = NULL;
        m_bHaveOpenFile = false;
        m_bHaveLoad = false;
        m_bWgl9000 = true;
    }
    catch(...)
    {
        return;
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 判断是否有已经打开的文件
//参	数:	
//返 回	值:	
//备	注:
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::IsNull()
{
    return !m_bHaveOpenFile;
}

bool CCmtdFile::HaveEleItem()
{
    if(m_arBus.count()+m_arLine.count()+m_arTrans.count()+m_arGenerator.count()+m_arExciter.count() > 0)
        return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 读Hdr文件
//参	数:	失败返回false(文件不存在或者格式有误)
//返 回	值:	
//备	注:
//创建日期: 2007-06-12  wpf
//修改记录: 
//			2007-10-08	wpf		1> 母线、线路、直流数目从cfg文件中获取
//								   这里不再统计.
//								2> 加入数目越限判断
//			2008-05-16  wpf        hdr文件读两遍,第一次读出母线、线路和
//								   直流数目,第二遍读出电气量信息.
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::ReadHdrFile()
{
    QFile hdrfile(m_strHdrFilePath);
    if(!hdrfile.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    
    char strline[2048] = {0};
    const int size = sizeof(strline);
    bool bRead = hdrfile.readLine(strline,size);     //第一行信息
    
    // 兼容其他厂家的HDR文件 [2/19/2008]
    // 如果不是WGL3000的HDR文件,直接返回false
    QString strtmp = strline;
    strtmp = strtmp.toUpper();
    if((strtmp.indexOf(gbk->fromUnicode("录波器类型"))<0)&&(strtmp.indexOf("DGL200")<0))
    {
        hdrfile.close();
        ////delete gbk;
        return false;
    }
    //]
    
    //////////////////////////////////////////////////////////////////////////
    //首先读出母线、线路、直流数目[[[

    removeEleItem();
    //读第一行[[
    strtmp = strtmp.trimmed();
    while((strtmp.length()<=0)&&(bRead))
    {
        bRead = hdrfile.readLine(strline,size);
        strtmp = strline;
    }
    //]]
    //  int nFileEndPos = Hdr_GetEndPos(strtmp);
    int nFileCurPos = hdrfile.pos();
    QString strl = gbk->toUnicode(strline);
    const QString strsplit = QString(",");
    QStringList arstr = strl.split(strsplit);

    int nInfoLinePos = arstr.at(9).toInt();		//信息列位置
    int nInfoKind = 0;					//信息类别(第七列的值)
    QString strItem;
    int cx;
    CEleBus* pBus = NULL;
    CEleDC* pDC = NULL;
    CEleLine* pLine = NULL;
    int nDCChanel = 0;
    QString strn;

    bRead = hdrfile.readLine(strline,size);
    while((bRead)&&(nFileCurPos<nInfoLinePos))
    {		
        strtmp = gbk->toUnicode(strline);
        strtmp = strtmp.trimmed();
        nInfoKind = Hdr_GetInfoKind(strtmp);        
        bRead = hdrfile.readLine(strline,size);
        strtmp = gbk->toUnicode(strline);
        strItem = Hdr_GetRightString(strtmp);
        if((nInfoKind>=100)&&(nInfoKind<2000))		// 只取名称和电压等级 [10/8/2007]
        {
            cx = nInfoKind%100;			
            if(cx == 0)
            {
                pBus = new CEleBus();
                strcpy(pBus->m_chName,gbk->fromUnicode(strItem));
                m_arBus.append(pBus);
            }
            else if(cx == 1)		//Ua
            {
                if(pBus)
                {
                    pBus->m_wAID = QtoB(strItem);
                    pBus->m_pAChanel = GetAChanelById(pBus->m_wAID);
                }
            }
            else if(cx == 2)		//Ub
            {
                if(pBus)
                {
                    pBus->m_wBID = QtoB(strItem);
                    pBus->m_pBChanel = GetAChanelById(pBus->m_wBID);
                }
            }
            else if(cx == 3)		//Uc
            {
                if(pBus)
                {
                    pBus->m_wCID = QtoB(strItem);
                    pBus->m_pCChanel = GetAChanelById(pBus->m_wCID);
                }
            }
            else if(cx == 4)		//3U0
            {
                if(pBus)
                {
                    pBus->m_wNID = QtoB(strItem);
                    pBus->m_pNChanel = GetAChanelById(pBus->m_wNID);
                }
            }
            else if(cx == 5)		//电压等级
            {
                if(pBus != NULL)
                {
                    pBus->m_dVoltage = (float)QtoB(strItem);
                }
            }
        }
        else if(nInfoKind>=200000)  //直流
        {	
            cx = nInfoKind%10;		
            if(cx == 0)             //名称
            {
                pDC = new CEleDC();
                nDCChanel = nInfoKind%1000/10;
                strcpy(pDC->m_chName,gbk->fromUnicode(strItem));
                pDC->m_pChanel = GetAChanelById(nDCChanel);
                m_arDC.append(pDC);
            }
            else if(cx == 1)        //类型
            {
                if(pDC)
                {
                    pDC->m_dMaxValue = (float)(atoi(strItem.toLocal8Bit()));
                }
            }
            else if(cx == 2)       //一次侧单位
            {
                if(pDC != NULL)
                {
                    strcpy(pDC->m_chUnit1,gbk->fromUnicode(strItem));
                    if(pDC->m_pChanel != NULL)
                    {
                        strcpy(pDC->m_pChanel->m_chUnit1,pDC->m_chUnit1);
                    }
                }
            }
            else if(cx == 3)      //变换系数
            {
                if(pDC)
                {
                    pDC->m_dFactor = (float)(atof(strItem.toLocal8Bit().constData()));
                }
            }
            else if(cx == 4)      //二次侧单位
            {
                if(pDC != NULL)
                {
                    strcpy(pDC->m_chUnit2,gbk->fromUnicode(strItem));
                    if(pDC->m_pChanel != NULL)
                    {
                        strcpy(pDC->m_pChanel->m_chUnit2,pDC->m_chUnit2);
                    }
                }
            }
        }
        else if((nInfoKind>=2000)&&(nInfoKind<200000))
        {
            cx = nInfoKind%2000;
            if(cx == 0)
            {
                pLine = new CEleLine;
                strcpy(pLine->m_chName,gbk->fromUnicode(strItem));
                m_arLine.append(pLine);
            }
            else if(pLine != NULL)
            {
                if(cx == 5)				//Ia
                {
                    if(pLine)
                    {
                        pLine->m_wAID = QtoB(strItem);
                        pLine->m_pAChanel = GetAChanelById(pLine->m_wAID);
                    }
                }
                else if(cx == 6)		//Ib
                {
                    if(pLine)
                    {
                        pLine->m_wBID = QtoB(strItem);
                        pLine->m_pBChanel = GetAChanelById(pLine->m_wBID);
                    }
                }
                else if(cx == 7)		//Ic
                {
                    if(pLine)
                    {
                        pLine->m_wCID = QtoB(strItem);
                        pLine->m_pCChanel = GetAChanelById(pLine->m_wCID);
                    }
                }
                else if(cx == 8)		//3I0
                {
                    if(pLine)
                    {
                        pLine->m_wNID = QtoB(strItem);
                        pLine->m_pNChanel = GetAChanelById(pLine->m_wNID);
                    }
                }
                else if(cx == 30)		//母线序号
                {
                    int ntmp = strItem.toInt();
                    pLine->m_pBus = NULL;
                    if((ntmp>0)&&(ntmp<=m_arBus.count()))
                    {
                        if(pLine)
                        {
                            pLine->m_pBus = m_arBus[ntmp-1];
                            pLine->m_wBusId = ntmp;
                        }
                    }
                }
                else if(cx == 11)	//R1
                {
                    if(pLine)
                        pLine->m_dR1 = (float)atof(strItem.toLatin1().constData());
                }
                else if(cx == 12)	//X1
                {
                    if(pLine)
                        pLine->m_dX1 = (float)atof(strItem.toLatin1().constData());
                }
                else if(cx == 13)	//R0
                {
                    if(pLine)
                        pLine->m_dR0 = (float)atof(strItem.toLatin1().constData());
                }
                else if(cx == 14)	//X0
                {
                    if(pLine)
                        pLine->m_dX0 = (float)atof(strItem.toLatin1().constData());
                }
                else if(cx == 18)	//CT
                {
                    if(pLine)
                        pLine->m_dCT = (float)(atof(strItem.toLatin1().constData()));
                }
                else if(cx == 19)	//高频1
                {
                    if(pLine)
                        pLine->m_sGp1 = QtoB(strItem)-1;
                }
                else if(cx == 20)	//高频2
                {
                    if(pLine)
                        pLine->m_sGp2 = QtoB(strItem)-1;
                }
                else if(cx == 21)                           //互感线路名称
                {
                    if(pLine)
                    {
                        for(int i=0; i<m_arLine.count(); i++)
                        {
                            strn = gbk->toUnicode(m_arLine[i]->m_chName);
                            if(strItem == strn)	//忽感线路
                            {
                                pLine->m_nHgLine = i;
                                break;
                            }
                        }
                    }
                }
                else if(cx == 22)                           //互感电阻
                {
                    if(pLine)
                        pLine->m_dRh = (float)(atof(strItem.toLatin1().constData()));
                }
                else if(cx == 23)                           //互感电抗
                {
                    if(pLine)
                        pLine->m_dXh = (float)(atof(strItem.toLatin1().constData()));
                }
                else if(cx == 24)							//额定电流
                {
                    if(pLine)
                        pLine->m_dMaxI = (float)atof(strItem.toLatin1().constData());
                }
                else if(cx == 25)							//A跳
                {
                    if(pLine)
                    {
                        pLine->m_arDChanel.append(QtoB(strItem));
                    }
                }
                else if(cx == 26)							//B跳
                {
                    if(pLine)
                        pLine->m_arDChanel.append(QtoB(strItem));
                }
                else if(cx == 27)							//C跳
                {
                    if(pLine)
                        pLine->m_arDChanel.append(QtoB(strItem));
                }
                else if(cx == 28)							//三跳
                {
                    if(pLine)
                        pLine->m_arDChanel.append(QtoB(strItem));
                }
                else if(cx == 29)							//重合闸
                {
                    if(pLine)
                        pLine->m_arDChanel.append(QtoB(strItem));
                }
                else if(cx == 31)							//线路长度
                {
                    if(pLine)
                        pLine->m_dLength = (float)atof(strItem.toLatin1().constData());
                }
                else if(cx>50)								//开关量
                {
                    if(pLine)
                        pLine->m_arDChanel.append(QtoB(strItem));
                }
            }
        }				
        bRead = hdrfile.readLine(strline,size);         //正文内容了
        nFileCurPos = hdrfile.pos();
    }
    //]]]
    hdrfile.close();
    ////delete gbk;
    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取hdr结束位置
//参	数:	a_strLine: hdr文件第一行
//返 回	值:	hdr文件结束位置
//备	注: hdr文件第一行的第7列
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
int CCmtdFile::Hdr_GetEndPos(QString &a_strLine)
{
    int dnum = 0;
    while(dnum<=6)
    {
        int npos = a_strLine.indexOf(',');
        if(npos>=0)
        {
            a_strLine = a_strLine.right(a_strLine.length() - npos - 1);
            dnum++;
        }
    }
    int npos = a_strLine.indexOf(',');
    a_strLine = a_strLine.left(npos);
    int res = atoi(a_strLine.toLatin1().constData());
    return res;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取数据类型
//参	数:	a_strLine: hdr文件的一行
//返 回	值:	类型
//备	注: 第7列的值
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
int CCmtdFile::Hdr_GetInfoKind(const QString &a_strLine)
{
    int res = -1;
    QString strx = a_strLine;
    int pos = strx.lastIndexOf(',');
    strx = strx.left(pos);
    pos = strx.lastIndexOf(',');
    strx = strx.right(strx.length() - pos - 1);
    res = atoi(strx.toLatin1().constData());
    return res;
}
//////////////////////////////////////////////////////////////////////////
//功	能: 获取最右边子串的
//参	数:	a_strLine: 源串
//返 回	值:	最右边的子串
//备	注: 
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
QString CCmtdFile::Hdr_GetRightString(QString &a_strLine)
{
    QString strx = "";
    a_strLine = a_strLine.trimmed();
    if(a_strLine.length()<=0)
        return strx;	
    int npos = a_strLine.lastIndexOf(',');
    strx = a_strLine.right(a_strLine.length() - npos - 1);
    strx.replace("\r\n","");
    return strx;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 通过通道号获取通道
//参	数:	a_wId:通道号
//返 回	值:	通道指针
//备	注: 
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
CEleAChanel* CCmtdFile::GetAChanelById(unsigned short a_wId)
{
    for(int i=0; i<m_arAChanel.count(); i++)
    {
        if(m_arAChanel[i]->m_wID == a_wId)
        {
            return m_arAChanel[i];
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 通过通道号获取通道
//参	数:	a_wId:通道号
//返 回	值:	通道指针
//备	注: 
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
CEleDChanel* CCmtdFile::GetDChanelById(unsigned short a_wId)
{
    for(int i=0; i<m_arDChanel.count(); i++)
    {
        if(m_arDChanel[i]->m_wID == a_wId)
        {
            return m_arDChanel[i];
        }
    }
    return NULL;
}

CEleBus* CCmtdFile::GetBusById(unsigned short a_wId)
{
    for(int i=0; i<m_arBus.count(); i++)
    {
        CEleBus* pBus = m_arBus.at(i);
        if(pBus->m_wID == a_wId)
        {
            return pBus;
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 全角数字转半角数字
//参	数:	a_strQ:全角数字(不能超过10位数)
//返 回	值:	转换结果
//备	注: 
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
int CCmtdFile::QtoB(const QString& a_strQ)
{
    int i = 0;
    int a[11] = {0};
    int nresult = 0;
    QString  strQ = a_strQ.trimmed();
    strQ.replace("\r\n","");
    QString strc = "";
    int nlen = strQ.length();
    int cpos = 0;
    for(i=0; i<nlen; i++)
    {
        strc = strQ.mid(i,1);
        if(strc == QString("０"))
            a[cpos++] = 0;
        else if(strc == QString("１"))
            a[cpos++] = 1;
        else if(strc == QString("２"))
            a[cpos++] = 2;
        else if(strc == QString("３"))
            a[cpos++] = 3;
        else if(strc == QString("４"))
            a[cpos++] = 4;
        else if(strc == QString("５"))
            a[cpos++] = 5;
        else if(strc == QString("６"))
            a[cpos++] = 6;
        else if(strc == QString("７"))
            a[cpos++] = 7;
        else if(strc == QString("８"))
            a[cpos++] = 8;
        else if(strc == QString("９"))
            a[cpos++] = 9;
        if(cpos >= 10)
            break;
    }

    for(int x=0; x<cpos; x++)
    {
        nresult *= 10;
        nresult += a[x];
    }

    return nresult;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取采样点所在采样段
//参	数:	a_nCurPos:当前点序号
//返 回	值:	采样段序号
//备	注: 
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
int CCmtdFile::GetCurSeg(int a_nCurPos)
{
    for(int i=m_nSegCount-1; i>=0; i--)
    {
        if(a_nCurPos > m_pSegment[i].m_nStartPos)
        {
            return i;
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取采样点的计算开始位置
//参	数:	a_nDataWindowType  数据窗类型
//			a_nCurPos		   当前位置
//			a_nWavePoints	   每周波采样点数目
//返 回	值:	修正后的计算位置
//备	注: 当前位置数据窗不够的做补偿
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
int CCmtdFile::GetCalPos(int a_nDataWindowType, int a_nCurPos, int &a_nWavePoints)
{
    int curseg = GetCurSeg(a_nCurPos);
    a_nWavePoints = m_pSegment[curseg].m_nWavePoints;
    int ncalpos = a_nCurPos;	//开始计算的位置
    int nend = m_pSegment[curseg].m_nStartPos+m_pSegment[curseg].m_nCount;
    //	a_nCurPos += 4;
    if(a_nDataWindowType == WGL_DATAWINDOW_WAVEBEFORE)
    {
        if(a_nCurPos < m_pSegment[curseg].m_nStartPos+a_nWavePoints+4)
        {
            ncalpos = m_pSegment[curseg].m_nStartPos+a_nWavePoints+4;
        }
        else
        {
            ncalpos = a_nCurPos-a_nWavePoints-4;
        }
    }
    else if(a_nDataWindowType == WGL_DATAWINDOW_WAVEMIDLE)
    {
        if(a_nCurPos < m_pSegment[curseg].m_nStartPos+a_nWavePoints/2+4)
        {
            ncalpos = m_pSegment[curseg].m_nStartPos+a_nWavePoints/2+4;
        }
        else if((nend - a_nCurPos) < a_nWavePoints/2+4)
        {
            ncalpos = nend - a_nWavePoints/2-4;
        }
        else
        {
            ncalpos = a_nCurPos-a_nWavePoints/2-4;
        }
    }
    else
    {
        if((nend-a_nCurPos) < a_nWavePoints+10)
        {
            ncalpos = nend - a_nWavePoints-10;
        }
        else 
        {
            ncalpos = a_nCurPos;
        }
    }
    return ncalpos;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取通道的CT/PT变比
//参	数:	a_wChanelID		通道号
//			a_wType			通道类型
//返 回	值:	CT/PT变比
//备	注: 当前位置数据窗不够的做补偿
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
float CCmtdFile::GetTds_CTPT(unsigned short a_wChanelID, unsigned short a_wType)
{
    float dtrs = 1.0;
    bool bfind = false;
    if(a_wType == 1)
    {
        for(int i=0; i<m_arBus.count(); i++)
        {
            bfind = false;
            if((m_arBus[i]->m_pAChanel != NULL)&&(m_arBus[i]->m_pAChanel->m_wID == a_wChanelID))
            {
                bfind = true;
            }
            if((m_arBus[i]->m_pBChanel != NULL)&&(m_arBus[i]->m_pBChanel->m_wID == a_wChanelID))
            {
                bfind = true;
            }
            if((m_arBus[i]->m_pCChanel != NULL)&&(m_arBus[i]->m_pCChanel->m_wID == a_wChanelID))
            {
                bfind = true;
            }
            if((m_arBus[i]->m_pNChanel != NULL)&&(m_arBus[i]->m_pNChanel->m_wID == a_wChanelID))
            {
                bfind = true;
            }
            if(bfind)
            {
                dtrs = (float)(m_arBus[i]->m_dVoltage*10.0/1000.0);
                return dtrs;
            }
        }
    }
    else if(a_wType == 2)
    {
        for(int i=0; i<m_arLine.count(); i++)
        {
            bfind = false;
            if((m_arLine[i]->m_pAChanel != NULL)&&(m_arLine[i]->m_pAChanel->m_wID == a_wChanelID))
            {
                bfind = true;
            }
            if((m_arLine[i]->m_pBChanel != NULL)&&(m_arLine[i]->m_pBChanel->m_wID == a_wChanelID))
            {
                bfind = true;
            }
            if((m_arLine[i]->m_pCChanel != NULL)&&(m_arLine[i]->m_pCChanel->m_wID == a_wChanelID))
            {
                bfind = true;
            }
            if((m_arLine[i]->m_pNChanel != NULL)&&(m_arLine[i]->m_pNChanel->m_wID == a_wChanelID))
            {
                bfind = true;
            }
            if(bfind)
            {
                dtrs = (float)(m_arLine[i]->m_dCT/1000.0);
                return dtrs;
            }
        }
    }
    else
    {
        for(int i=0; i<m_arDC.count(); i++)
        {
            if(m_arDC[i]->m_pChanel == NULL)
            {
                continue;
            }
            if(m_arDC[i]->m_pChanel->m_wID == a_wChanelID)
            {
                dtrs = m_arDC[i]->m_dFactor;
                return dtrs;
            }
        }
    }
    return dtrs;
}

float CCmtdFile::GetChanels_PTCT(CEleAChanel *pChanel)
{
    const float fEpslon = 0.0001;
    float dtrs = 1.0;
    if(pChanel->m_wType == 1)   //电压通道
    {
        if(pChanel->m_fSecondary > fEpslon)
            dtrs = (float)(pChanel->m_fPrimary/pChanel->m_fSecondary/1000.);
    }
    else if(pChanel->m_wType == 2)  //电流
    {
        if(pChanel->m_fSecondary > fEpslon)
            dtrs = (float)(pChanel->m_fPrimary/pChanel->m_fSecondary/1000.);
        else    //2021-5-29添加（DMF文件primary secondart没写值）
        {
            CEleLine* pLine = NULL;
            for(int i=0; i<m_arLine.count(); i++)
            {
                pLine = m_arLine.at(i);
                if((pLine->m_pAChanel == pChanel)||(pLine->m_pBChanel == pChanel)||(pLine->m_pCChanel == pChanel)||(pLine->m_pNChanel == pChanel))
                {
                    dtrs = pLine->m_dCT/1000.;
                    break;
                }
            }
        }
    }
    else
    {
        if(pChanel->m_fSecondary > fEpslon)
            dtrs = (float)(pChanel->m_fPrimary/pChanel->m_fSecondary/1000.);
//        for(int i=0; i<m_arDC.count(); i++)
//        {
//            if(m_arDC[i]->m_pChanel == NULL)
//            {
//                continue;
//            }
//            if(m_arDC[i]->m_pChanel->m_wID == pChanel->m_wID)
//            {
//                dtrs = m_arDC[i]->m_dFactor;
//                return dtrs;
//            }
//        }
//        if(pChanel->m_fSecondary > fEpslon)
//            dtrs = (float)(pChanel->m_fPrimary/pChanel->m_fSecondary/1000.);
    }
    return dtrs;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 从cfg文件的时间串中获取时间
//参	数:	a_strTime		时间串
//			a_dMiniSecond	返回毫秒数
//返 回	值:	时间
//备	注: 
//创建日期: 2007-06-12  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
QDateTime CCmtdFile::GetTimeFromString(const QString &a_strTime, float& a_dMiniSecond)
{
    QString strtime = a_strTime;
    int year=2000,month=1,date=1,hour=0,minute=0,second=0;
    a_dMiniSecond = 0;
    if(m_wCmtdYear >= 1997)
    {
        sscanf(strtime.toLatin1().constData(),"%d/%d/%d,%d:%d:%d",&date,&month,&year,&hour,&minute,&second);
    }
    else
    {
        sscanf(strtime.toLatin1().constData(),"%d/%d/%d,%d:%d:%d",&month,&date,&year,&hour,&minute,&second);
    }
    
    if(year < 200)
    {
        if(year > 80)
        {
            year += 1900;
        }
        else
        {
            year += 2000;
        }
    }
    QString strmini = a_strTime;
    int npos = strmini.lastIndexOf('.');
    if(npos > 0)
    {
        strtime = strmini.right(strmini.length() - npos - 1);
        a_dMiniSecond = (float)(atoi(strtime.toLatin1().constData()));
    }
    
    //---------------------------------------------------------------------
    //兼容一种时间格式,保证不出错
    //[[
    int ntmp = 0;
    if(month>12)
    {
        ntmp = month;
        month = date;
        date = ntmp;
    }
    //]]

    QDate dt(year,month,date);
    QTime tt(hour,minute,second);
    QDateTime mtm(dt,tt);
    a_dMiniSecond /= 1000.0;
    return mtm;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 从Rmk文件中读取标签信息
//参	数:	
//返 回	值:	
//备	注: 每次编辑标签之后调用此函数重新读取
//创建日期: 2007-09-24  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::ReadRmkFile()
{
    m_arRemark.clear();
    //	char chContent[MAX_PATH] = {0};
    QSettings qset(m_strRmkFilePath,QSettings::IniFormat);
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    qset.setIniCodec(gbk);
    int ncount = qset.value("Remark/number",0).toInt();
    if(ncount <= 0)
    {
        ////delete gbk;
        return false;
    }
    
    QString strSection;

    QString strContent;
    for(int i=0; i<ncount; i++)
    {
        CEleRemark* pRmk = new CEleRemark();
        strSection.sprintf("Rem%d",i+1);
        pRmk->m_wChanelId = qset.value(strSection+"/TDNum",1).toInt();
        pRmk->m_nPos = qset.value(strSection+"/Pos",0).toInt();
        pRmk->m_nCX = qset.value(strSection+"/x",0).toInt();
        pRmk->m_nCY = qset.value(strSection+"/y",0).toInt();
        pRmk->m_bAChanel = qset.value(strSection+"/AChanel",1).toInt();
        memset(pRmk->m_chContent,0,sizeof(pRmk->m_chContent));
        strContent = qset.value(strSection+"/Text","Un Define").toString();
        strcpy(pRmk->m_chContent,gbk->fromUnicode(strContent));
        m_arRemark.append(pRmk);
    }
    ////delete gbk;
    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 把标签信息写入rmk文件
//参	数:	
//返 回	值:	
//备	注: 每次编辑标签之后调用此函数写入
//创建日期: 2007-09-24  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
void CCmtdFile::WriteRmkFile()
{
    /*
    QFile::remove(m_strRmkFilePath);
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    char chContent[MAX_PATH] = {0};
    int nsize = m_arRemark.count();
    sprintf(chContent,"%d",nsize);
    QSettings qset(m_strRmkFilePath,QSettings::IniFormat);
    qset.setIniCodec("GBK");
    qset.setValue("Remark/number",chContent);
    QString strSection;
    int i = 0;
    QString strtest;
    for(i=0; i<nsize; i++)
    {
        CEleRemark* pRmk = m_arRemark[i];
        strSection.sprintf("Rem%d",i+1);
        memset(chContent,0,sizeof(chContent));
        sprintf(chContent,"%d",pRmk->m_wChanelId);
        qset.setValue(strSection+"/TDNum",chContent);
        memset(chContent,0,sizeof(chContent));
        sprintf(chContent,"%d",pRmk->m_bAChanel);
        qset.setValue(strSection+"/AChanel",chContent);
        memset(chContent,0,sizeof(chContent));
        sprintf(chContent,"%d",pRmk->m_nPos);
        qset.setValue(strSection+"/pos",chContent);
        memset(chContent,0,sizeof(chContent));
        sprintf(chContent,"%d",pRmk->m_nCX);
        qset.setValue(strSection+"/x",chContent);
        memset(chContent,0,sizeof(chContent));
        sprintf(chContent,"%d",pRmk->m_nCY);
        qset.setValue(strSection+"/y",chContent);
        strtest = gbk->toUnicode(pRmk->m_chContent);
        qset.setValue(strSection+"/Text",strtest);
    }
    ////delete gbk;
    */
}

//////////////////////////////////////////////////////////////////////////
//功	能: 返回错误信息
//参	数:	
//返 回	值:	
//备	注: 
//创建日期: 2007-11-01  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
char* CCmtdFile::GetErrorInfo()
{
    return m_chErrorInfo;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 写入线路/主变参数
//参	数:	
//返 回	值:	
//备	注: 如果是hdr文件/INI文件,直接创建一个lne文件,不再修改hdr文件
//创建日期: 2007-11-01  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::WriteInfoToFile()
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
//    QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
    bool bExternDC = false;
    char strline[2048] = {0};
    strcpy(strline,gbk->fromUnicode(QString("国电武仪COMTRADE_HDR文件Ver2.0")));
    m_strLneFilePath = m_strLneFilePath.toUpper();
    m_strLneFilePath.replace(".HDR",".LNE");
    //////////////////////////////////////////////////////////////////////////
    //创建文件,写文件标头和母线数目、线路数目、直流数目和主变数目
    QFile lnefile(m_strLneFilePath);
    if(!lnefile.open(QIODevice::WriteOnly))
    {
        strcpy(m_chErrorInfo,"打开lne文件错误,请检查文件是否被其他程序打开");
        return false;
    }
    strcat(strline,"\r\n");
    lnefile.write(strline,strlen(strline));
    sprintf(strline,"%d,%d,%d,%d\r\n",m_arBus.count(),m_arLine.count(),m_arDC.count(),m_arTrans.count());
    lnefile.write(strline,strlen(strline));
    
    //////////////////////////////////////////////////////////////////////////
    //写母线信息	序号,名称,A、B、C、N通道号,电压等级
    unsigned short wAId=0,wBId=0,wCId=0,wNId=0;
    int i = 0;
    for(i=0; i<m_arBus.count(); i++)
    {
        wAId = m_arBus[i]->m_pAChanel->m_wID;
        wBId = m_arBus[i]->m_pBChanel->m_wID;
        wCId = m_arBus[i]->m_pCChanel->m_wID;
        wNId = m_arBus[i]->m_pNChanel->m_wID;
        //		m_arBus[i]->m_wID = i+1;
        sprintf(strline,"%d,%s,%d,%d,%d,%d,%g\r\n",i+1,m_arBus[i]->m_chName,wAId,wBId,wCId,wNId,m_arBus[i]->m_dVoltage);
        lnefile.write(strline,strlen(strline));
    }
    //////////////////////////////////////////////////////////////////////////
    //写线路信息	
    //序号,名称,A、B、C、N通道号,连接母线,线路/主变,是否测距,r1,x1,r0,x0,忽感线路序号,hr,hx,额定电流,CT变比,线路长度,高频1,高频2
    for(i=0; i<m_arLine.count(); i++)
    {
        if(m_arLine[i]->m_pAChanel != NULL)
        {
            wAId = m_arLine[i]->m_pAChanel->m_wID;
        }
        else
        {
            wAId = 0;
        }
        if(m_arLine[i]->m_pBChanel != NULL)
        {
            wBId = m_arLine[i]->m_pBChanel->m_wID;
        }
        else
        {
            wBId = 0;
        }
        if(m_arLine[i]->m_pCChanel != NULL)
        {
            wCId = m_arLine[i]->m_pCChanel->m_wID;
        }
        else
        {
            wCId = 0;
        }
        if(m_arLine[i]->m_pNChanel != NULL)
        {
            wNId = m_arLine[i]->m_pNChanel->m_wID;
        }
        else
        {
            wNId = 0;
        }
//        if(m_arTrans.count() > 0)
//        {
//            sprintf(strline,"%d,%s,%d,%d,%d,%d,%d,%s,0,%g,%g,%g,%g,%d,%g,%g,%g,%g,%g,%d,%d\r\n",i+1,m_arLine[i]->m_chName,wAId,wBId,wCId,wNId,m_arLine[i]->m_pBus->m_wID,gbk->fromUnicode("主变").constData(),m_arLine[i]->m_dR1,m_arLine[i]->m_dX1,m_arLine[i]->m_dR0,m_arLine[i]->m_dX0,m_arLine[i]->m_nHgLine+1,m_arLine[i]->m_dRh,m_arLine[i]->m_dXh,m_arLine[i]->m_dMaxI,m_arLine[i]->m_dCT,m_arLine[i]->m_dLength,m_arLine[i]->m_sGp1,m_arLine[i]->m_sGp2);
//        }
//        else
//        {
            sprintf(strline,"%d,%s,%d,%d,%d,%d,%d,%s,1,%g,%g,%g,%g,%d,%g,%g,%g,%g,%g,%d,%d\r\n",i+1,m_arLine[i]->m_chName,wAId,wBId,wCId,wNId,m_arLine[i]->m_pBus->m_wID,gbk->fromUnicode("线路").constData(),m_arLine[i]->m_dR1,m_arLine[i]->m_dX1,m_arLine[i]->m_dR0,m_arLine[i]->m_dX0,m_arLine[i]->m_nHgLine+1,m_arLine[i]->m_dRh,m_arLine[i]->m_dXh,m_arLine[i]->m_dMaxI,m_arLine[i]->m_dCT,m_arLine[i]->m_dLength,m_arLine[i]->m_sGp1,m_arLine[i]->m_sGp2);
//        }
        lnefile.write(strline,strlen(strline));
    }
    //-------------------------------------------------------------------------------------
    //写直流信息	格式: 编号,名称,通道号
    //-------------------------------------------------------------------------------------
    for(i=0; i<m_arDC.count(); i++)
    {
        if((m_arDC[i]->m_bExternDC)&&(!bExternDC))
        {
            bExternDC = true;
        }
        if(m_arDC[i]->m_pChanel != NULL)
        {
            sprintf(strline,"%d,%s,%d,%s,%s,%g\r\n",i+1,m_arDC[i]->m_chName,m_arDC[i]->m_pChanel->m_wID,m_arDC[i]->m_chKind,m_arDC[i]->m_chUnit1,m_arDC[i]->m_dFactor);
        }
        else
        {
            sprintf(strline,"%d,%s,%d,%s,%s,%g\r\n",i+1,m_arDC[i]->m_chName,0,m_arDC[i]->m_chKind,m_arDC[i]->m_chUnit1,m_arDC[i]->m_dFactor);
        }
        lnefile.write(strline,strlen(strline));
    }
    //-------------------------------------------------------------------------------------------------------
    //写主变信息	格式: 编号,名称,I侧电流ID,I侧接线方式,I侧平衡系数,I侧是否反向,II侧...,III侧...,IV侧...,
    //				动作电流,速断电流,制动电流计算方法
    //-------------------------------------------------------------------------------------------------------
    char strI[256]={0},strII[256]={0},strIII[256]={0},strIV[256]={0};
    for(i=0; i<m_arTrans.count(); i++)
    {
        sprintf(strI,"%d,%d,%g,%d",m_arTrans[i]->m_pLine[0]->m_wID,m_arTrans[i]->m_nType[0],m_arTrans[i]->m_dFactor[0],m_arTrans[i]->m_bInvert[0]);
        sprintf(strII,"%d,%d,%g,%d",m_arTrans[i]->m_pLine[1]->m_wID,m_arTrans[i]->m_nType[1],m_arTrans[i]->m_dFactor[1],m_arTrans[i]->m_bInvert[1]);
        if(m_arTrans[i]->m_pLine[2] != NULL)
        {
            sprintf(strIII,"%d,%d,%g,%d",m_arTrans[i]->m_pLine[2]->m_wID,m_arTrans[i]->m_nType[2],m_arTrans[i]->m_dFactor[2],m_arTrans[i]->m_bInvert[2]);
        }
        else
        {
            strcpy(strIII,"0,1,1.0,0");
        }
        if(m_arTrans[i]->m_pLine[3] != NULL)
        {
            sprintf(strIV,"%d,%d,%g,%d",m_arTrans[i]->m_pLine[3]->m_wID,m_arTrans[i]->m_nType[3],m_arTrans[i]->m_dFactor[3],m_arTrans[i]->m_bInvert[3]);
        }
        else
        {
            strcpy(strIV,"0,1,1.0,0");
        }
        sprintf(strline,"%d,%s,%s,%s,%s,%s,%g,%g,%d\r\n",i+1,m_arTrans[i]->m_chName,strI,strII,strIII,strIV,m_arTrans[i]->m_dIcd,m_arTrans[i]->m_dIsd,m_arTrans[i]->m_nKind);
        lnefile.write(strline,strlen(strline));
    }
    //-------------------------------------------------------------------------------------
    //写开关量信息
    //-------------------------------------------------------------------------------------
    char strTmp[256] = {0};
    memset(strline,0,sizeof(strline));
    for(i=0; i<m_arLine.count(); i++)
    {	
        sprintf(strTmp,"%d",m_arLine[i]->m_nSwitchCount);
        if(i < m_arLine.count()-1)
        {
            strcat(strTmp,",");
        }
        strcat(strline,strTmp);
    }
    strcat(strline,"\r\n");
    lnefile.write(strline,strlen(strline));
    int nId = 1;
    for(i=0; i<m_arLine.count(); i++)
    {
        sprintf(strline,"%d,",i+1);
        for(int j=0; j<m_arLine[i]->m_arDChanel.count(); j++)
        {
            nId = m_arLine[i]->m_arDChanel[j];
            if(m_arDChanel[nId-1]->m_strFlag == QString("TrPhsA"))
                sprintf(strTmp,"%d:21",nId);
            else if(m_arDChanel[nId-1]->m_strFlag == QString("TrPhsB"))
                sprintf(strTmp,"%d:22",nId);
            else if(m_arDChanel[nId-1]->m_strFlag == QString("TrPhsC"))
                sprintf(strTmp,"%d:23",nId);
            else if(m_arDChanel[nId-1]->m_strFlag == QString("OpTP"))
                sprintf(strTmp,"%d:24",nId);
            else if(m_arDChanel[nId-1]->m_strFlag == QString("RecOpCls"))
                sprintf(strTmp,"%d:25",nId);
            else
                sprintf(strTmp,"%d:0",nId);
            if(j <m_arLine[i]->m_nSwitchCount-1)
            {
                strcat(strTmp,",");
            }
            strcat(strline,strTmp);
        }
        strcat(strline,"\r\n");
        lnefile.write(strline,strlen(strline));
    }
    //-------------------------------------------------------------------------------------
    //写[attach]行,对于WGL9000录波器,直接写入备份的行;WGL3000录波器需构建该行
    //-------------------------------------------------------------------------------------
    if(m_strAttach.length() > 0)	//已经有attach行
    {
        strcpy(strline,m_strAttach.toLatin1().constData());
        strcat(strline,"\r\n");
        lnefile.write(strline,strlen(strline));
    }
    else							//
    {
        strcpy(strline,"[attach]");
        sprintf(strTmp,"%d/%d/%d,%d:%d:%d.%.6d,0,",m_tmStart.date().month(),m_tmStart.date().day(),m_tmStart.date().year()-2000,m_tmStart.time().hour(),m_tmStart.time().minute(),m_tmStart.time().second(),m_wFaultMiniSec);
        strcat(strline,strTmp);
        sprintf(strTmp,"%d,0",m_nDatSize);
        strcat(strline,strTmp);
        m_strAttach = strline;
        strcat(strline,"\r\n");
        lnefile.write(strline,strlen(strline));
    }
    
    lnefile.close();
    
    if(!bExternDC)					//扩展直流量
    {
        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    //写入扩展DC文件DC_Extend.txt.
    //格式：通道号,二次侧最小值,二次侧最大值,一次侧最小值,一次侧最大值
    //例如：61,4,20,0,300
    QFileInfo finfo(m_strCfgFilePath);
    QString strDCExFile = finfo.absolutePath()+QString("/DC_Extend.txt");
    lnefile.setFileName(strDCExFile);
    if(!lnefile.open(QIODevice::WriteOnly))
    {
        strcpy(m_chErrorInfo,"创建DC_Extend.txt文件错误,请检查是否正打开文件");
        return false;
    }
    for(i=0; i<m_arDC.count(); i++)
    {
        if(m_arDC[i]->m_bExternDC)
        {
            if(m_arDC[i]->m_pChanel != NULL)
            {
                sprintf(strline,"%d,%g,%g,%g,%g\r\n",m_arDC[i]->m_pChanel->m_wID,m_arDC[i]->m_dMin_Two,m_arDC[i]->m_dMax_Two,m_arDC[i]->m_dMin_One,m_arDC[i]->m_dMax_One);
            }
            else
            {
                sprintf(strline,"%d,%g,%g,%g,%g\r\n",0,m_arDC[i]->m_dMin_Two,m_arDC[i]->m_dMax_Two,m_arDC[i]->m_dMin_One,m_arDC[i]->m_dMax_One);
            }
            lnefile.write(strline,strlen(strline));
        }
    }
    lnefile.close();
    
    return true;
}

bool CCmtdFile::writeDCExtend()
{
    int i = 0;
    bool bExternDC = false;
    char strline[2048] = {0};
    for(i=0; i<m_arDC.count(); i++)
    {
        if((m_arDC[i]->m_bExternDC)&&(!bExternDC))
        {
            bExternDC = true;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    //写入扩展DC文件DC_Extend.txt.
    //格式：通道号,二次侧最小值,二次侧最大值,一次侧最小值,一次侧最大值
    //例如：61,4,20,0,300
    QFileInfo finfo(m_strCfgFilePath);
    QString strDCExFile = finfo.absolutePath()+QString("/DC_Extend.txt");
    QFile dcefile(strDCExFile);
    if(!dcefile.open(QIODevice::WriteOnly))
    {
        strcpy(m_chErrorInfo,"创建DC_Extend.txt文件错误,请检查是否正打开文件");
        return false;
    }

    for(i=0; i<m_arDC.count(); i++)
    {
        if(m_arDC[i]->m_bExternDC)
        {
            if(m_arDC[i]->m_pChanel != NULL)
            {
                sprintf(strline,"%d,%g,%g,%g,%g\r\n",m_arDC[i]->m_pChanel->m_wID,m_arDC[i]->m_dMin_Two,m_arDC[i]->m_dMax_Two,m_arDC[i]->m_dMin_One,m_arDC[i]->m_dMax_One);
            }
            else
            {
                sprintf(strline,"%d,%g,%g,%g,%g\r\n",0,m_arDC[i]->m_dMin_Two,m_arDC[i]->m_dMax_Two,m_arDC[i]->m_dMin_One,m_arDC[i]->m_dMax_One);
            }
            dcefile.write(strline,strlen(strline));
        }
    }
    dcefile.close();

    return true;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 获取通道的最小有效值(计算谐波时使用)
//参	数:	
//返 回	值:	
//备	注: 如果有效值小于该值,不计算谐波
//创建日期: 2007-11-15  wpf
//修改记录: 
//			
//////////////////////////////////////////////////////////////////////////
float CCmtdFile::GetChanels_Min_Rms(unsigned short a_wChanelID)
{
    float dvalue = (float)(0.2);
    CEleAChanel* pChanel = NULL;
    int i = 0;
    for(i=0; i<m_arAChanel.count(); i++)
    {
        if(m_arAChanel[i]->m_wID == a_wChanelID)
        {
            pChanel = m_arAChanel[i];
            break;
        }
    }
    if(pChanel == NULL)
    {
        return dvalue;
    }
    if(pChanel->m_wType == 1)	//电压
    {
        dvalue = 1.0;
    }
    else if(pChanel->m_wType == 2)	//电流
    {
        int nLine = -1;
        for(i=0; i<m_arLine.count(); i++)
        {
            if((m_arLine[i]->m_pAChanel!=NULL)&&(m_arLine[i]->m_pAChanel->m_wID == a_wChanelID))
            {
                nLine = i;
                break;
            }
            if((m_arLine[i]->m_pBChanel!=NULL)&&(m_arLine[i]->m_pBChanel->m_wID == a_wChanelID))
            {
                nLine = i;
                break;
            }
            if((m_arLine[i]->m_pCChanel!=NULL)&&(m_arLine[i]->m_pCChanel->m_wID == a_wChanelID))
            {
                nLine = i;
                break;
            }
            if((m_arLine[i]->m_pNChanel!=NULL)&&(m_arLine[i]->m_pNChanel->m_wID == a_wChanelID))
            {
                nLine = i;
                break;
            }
        }
        if(nLine >= 0)
        {
            dvalue = (float)(m_arLine[nLine]->m_dMaxI * 0.01);
        }
        else
        {
            dvalue = (float)(0.2);
        }
    }
    else
    {
        dvalue = 1;
    }
    return dvalue;
}

//////////////////////////////////////////////////////////////////////////
//功	能: 解开wy2文件包
//参	数:	
//返 回	值:	有错误返回false,否则返回true
//备	注:
//创建日期: 2008-05-04  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::UnPackgeFile(const QString &a_strWy2FilePath)
{
    try
    {
        QFileInfo finfo(a_strWy2FilePath);
        unsigned int dwFileSize = finfo.size();
        if(dwFileSize < 200)
        {
            strcpy(m_chErrorInfo,"解压wy2文件失败,文件不完整");
            return false;
        }
        QFile wyFile(a_strWy2FilePath);
        //打开文件并获取数据指针[[
        if(!wyFile.open(QIODevice::ReadOnly))
        {
            strcpy(m_chErrorInfo,"解压wy2文件失败,打开文件失败");
            return false;
        }
        char* chData = (char*)(wyFile.map(0,dwFileSize));
        wyFile.close();
        //]]
        
        //////////////////////////////////////////////////////////////////////////
        //读数据、写文件[[
        unsigned int dwFileLen = 0;
        QString strPath = a_strWy2FilePath;
        int npos = strPath.lastIndexOf('.');
        if(npos > 0)
        {
            strPath = strPath.left(npos);
        }
        
        QString strt = strPath+".";
        QFile mfile;
        int ncount = (unsigned char)(chData[0]);
        int nflen = 0;
        int i = 0;
        for(i=0; i<ncount; i++)
        {
            strPath = strt;
            strPath += chData[i*7+1];
            strPath += chData[i*7+2];
            strPath += chData[i*7+3];
            mfile.setFileName(strPath);
            memcpy(&dwFileLen,chData+i*7+4,4);
            if(mfile.open(QIODevice::WriteOnly))
            {
                mfile.write(chData+ncount*7+1+nflen,dwFileLen);
                mfile.close();
            }
            nflen += dwFileLen;
        }
        wyFile.unmap((uchar*)(chData));
        QFile::remove(a_strWy2FilePath);
        strcpy(m_chErrorInfo,"解压wy2文件完成");
        return true;
    }
    catch(...)
    {
        strcpy(m_chErrorInfo,"解压wy2文件失败,操作异常");
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////
//功	能: 保存指定时间范围的点到指定的文件
//参	数:	
//返 回	值:	有错误返回false,否则返回true
//备	注:
//创建日期: 2008-05-12  wpf
//修改记录: 
//////////////////////////////////////////////////////////////////////////
bool CCmtdFile::SaveFileAs(int a_nStartPos, int a_nEndPos, const QString& a_strFilePath)
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    //---------------------------------------------------
    //确认有效性
    //---------------------------------------------------
    if(a_nStartPos < 0)
    {
        sprintf(m_chErrorInfo,"保存文件错误,开始点序号(%d)小于0",a_nStartPos);
        ////delete gbk;
        return false;
    }
    if(a_nEndPos > m_nTotalPoints)
    {
        sprintf(m_chErrorInfo,"保存文件错误,结束点序号(%d)大于本文件总的采样点数(%d)",a_nEndPos,m_nTotalPoints);
        ////delete gbk;
        return false;
    }
    if(a_nEndPos == a_nStartPos)
    {
        sprintf(m_chErrorInfo,"保存文件错误,开始点序号%d等于结束点序号%d",a_nStartPos,a_nEndPos);
        ////delete gbk;
        return false;
    }
    if(a_nEndPos < a_nStartPos)		//如果开始点序号大于结束点序号,对换开始点和结束点
    {
        int nTemp = a_nEndPos;
        a_nEndPos = a_nStartPos;
        a_nStartPos = nTemp;
    }
    
    //---------------------------------------------------
    //获取所选范围内采样段数目
    //---------------------------------------------------
    int nSegCount = 0;
    int nStartSeg = -1;
    int nEndSeg = -1;
    int i = 0;
    for(i=0; i<m_nSegCount; i++)
    {
        if(nStartSeg < 0)
        {
            if((a_nStartPos > m_pSegment[i].m_nStartPos)&&(a_nStartPos <= m_pSegment[i].m_nStartPos+m_pSegment[i].m_nCount))	//开始点落在本段范围内
            {
                nStartSeg = i;
            }
        }
        if(nEndSeg < 0)
        {
            if((a_nEndPos > m_pSegment[i].m_nStartPos)&&(a_nEndPos <= m_pSegment[i].m_nStartPos+m_pSegment[i].m_nCount))	//开始点落在本段范围内
            {
                nEndSeg = i;
            }
        }
        else
        {
            break;
        }
    }
    nSegCount = nEndSeg - nStartSeg + 1;
    //---------------------------------------------------
    //保存cfg文件中的采样段信息
    //---------------------------------------------------
    //获取cfg文件路径[[
    m_strTmp = a_strFilePath;
    char strline[2048] = {0};
    const int size = sizeof(strline);
    
    int nPos = m_strTmp.lastIndexOf('.');
    if(nPos > 0)
    {
        m_strTmp = m_strTmp.left(nPos);
    }
    m_strTmp += ".cfg";
    //]]
    
    //保存cfg文件到目标路径并打开访问[[
    QFile cfgFile(m_strTmp);
    if(!cfgFile.open(QIODevice::WriteOnly))
    {
        strcpy(m_chErrorInfo,"访问目标cfg文件失败");
        return false;
    }
    QFile sFile(m_strCfgFilePath);
    if(!sFile.open(QIODevice::ReadOnly))
    {
        strcpy(m_chErrorInfo,"访问源cfg文件失败");
        cfgFile.close();
        return false;
    }
    for(i=0; i<m_nACount+m_nDCount+3; i++)			//一直读到采样率字段
    {
        sFile.readLine(strline,size);
//        strcat(strline,"\r\n");
        cfgFile.write(strline,strlen(strline));
    }
    //]]
    
    //修改采样信息[[
    sFile.readLine(strline,size);					//采样段数目
    int nTmp = atoi(strline);
    for(i=0; i<nTmp; i++)							//读出源文件的全部采样段(不再需要)
    {
        sFile.readLine(strline,size);
    }
    sprintf(strline,"%d\r\n",nSegCount);
    cfgFile.write(strline,strlen(strline));			//写入新的采样段数目
    int nEndPoints = 0;
    //写采样段信息(格式为"采样率,结束点")
    
    for(i=0;i<nSegCount; i++)
    {
        if(i == 0)
        {
            //2009-09-17 添加 min            
            nEndPoints = fmin(m_pSegment[i+nStartSeg].m_nCount,a_nEndPos)-a_nStartPos;
        }
        else if(i == nSegCount-1)
        {
            nEndPoints = a_nEndPos - a_nStartPos + 1;	
        }
        else
        {
            nEndPoints += m_pSegment[i+nStartSeg].m_nCount;
        }
        sprintf(strline,"%d,%d\r\n",m_pSegment[i+nStartSeg].m_nWavePoints*50,nEndPoints);
        cfgFile.write(strline,strlen(strline));
    }
    int nTotalPoints = nEndPoints+1;
    //]]
    
    sFile.readLine(strline,size);	//采样开始时间
    sFile.readLine(strline,size);	//突变时间
    unsigned int dwMiniSeconds = m_wLeftMiniSec + m_pSampleTime[a_nStartPos]/1000;
    QDateTime tmLeft = m_tmLeft;
    tmLeft = tmLeft.addSecs(dwMiniSeconds/1000);
    dwMiniSeconds %= 1000;
    sprintf(strline,"%.2d/%.2d/%d,%d:%d:%d.%d\r\n",tmLeft.date().day(),tmLeft.date().month(),tmLeft.date().year(),tmLeft.time().hour(),tmLeft.time().minute(),tmLeft.time().second(),dwMiniSeconds);
    cfgFile.write(strline,strlen(strline));
    cfgFile.write(strline,strlen(strline));
    
    sFile.readLine(strline,size);		//文件格式(ASCII或者BINARY)
    strcpy(strline,"BINARY\r\n");
    cfgFile.write(strline,strlen(strline));
    if(sFile.readLine(strline,size))	//版本号
    {
        cfgFile.write(strline,strlen(strline));
    }
    cfgFile.close();
    sFile.close();
    
    //-------------------------------------------------------
    //处理DAT文件
    //-------------------------------------------------------
    m_strTmp.replace(".cfg",".dat");
    QFile datFile(m_strTmp);
    if(!datFile.open(QIODevice::WriteOnly))
    {
        sprintf(m_chErrorInfo,"创建目标dat文件错误");
        return false;
    }
    tagDatUnit dUnit;
    memset(&dUnit,0,sizeof(tagDatUnit));
    
    const int nZeroTime = m_pSampleTime[a_nStartPos];
    nPos = 0;
    unsigned short wValue = 0;
    int nUnitSize = m_nACount+m_nDCount/16;
    if(m_nDCount%16 != 0)
    {
        nUnitSize += 1;
    }
    nUnitSize *= 2;
    nUnitSize += 8;
    unsigned char ukg = 0x01;
    int cn = 0;
    for(i=0; i<nTotalPoints; i++)
    {
        memset(&dUnit,0,sizeof(tagDatUnit));
        dUnit.m_nSampIndex = i+1;
        dUnit.m_nSampTime = m_pSampleTime[i+a_nStartPos]-nZeroTime;
        nPos = 0;
        for(cn=0; cn<m_arAChanel.count(); cn++)
        {
            dUnit.m_nSampData[nPos] = (short)((m_arAChanel[cn]->m_pData[i+a_nStartPos]-m_arAChanel[cn]->m_db)/m_arAChanel[cn]->m_da);
            nPos++;
        }
        
        for(cn=0; cn<m_nDCount; cn++)
        {
            if(((m_arDChanel[cn]->m_pData[(i+a_nStartPos)/8])&(ukg<<((i+a_nStartPos)%8))) != 0)
            {
                wValue = (unsigned short)(pow(2,cn%16));
                dUnit.m_nSampData[nPos+cn/16] |= wValue;
            }
        }
        datFile.write((char*)(&dUnit),nUnitSize);
    }
    datFile.close();
    
    //拷贝另一个扩展文件到目标文件夹//
    if(IsFileExist(m_strDMFFilePath))
    {
        m_strTmp.replace(".dat",".dmf");
        m_strTmp.replace(".DAT",".DMF");
        QFile::copy(m_strDMFFilePath,m_strTmp);
    }
    else if(IsFileExist(m_strLneFilePath))
    {
        m_strTmp.replace(".dat",".lne");
        m_strTmp.replace(".DAT",".LNE");
        QFile::copy(m_strLneFilePath,m_strTmp);
    }
    else if(IsFileExist(m_strHdrFilePath))
    {
        m_strTmp.replace(".dat",".hdr");
        m_strTmp.replace(".DAT",".HDR");
        QFile::copy(m_strHdrFilePath,m_strTmp);
    }
    //]]
    return true;
}

void CCmtdFile::FreshMaxABS()
{
    //////////////////////////////////////////////////////////////////////////
    //统计各种类型通道的最大最小值
    int i = 0;
    m_dMaxUAbs = 0;
    m_dMaxIAbs = 0;
    m_dMaxZAbs = 0;
    for(i=0; i<m_arAChanel.count(); i++)
    {
        //电压通道
        if(m_arAChanel[i]->m_wType == 1)
        {		
            if(m_dMaxUAbs < m_arAChanel[i]->m_dMaxAbs)
                m_dMaxUAbs = m_arAChanel[i]->m_dMaxAbs;
        }
        else if(m_arAChanel[i]->m_wType == 2)	//电流通道
        {
            if(m_dMaxIAbs < m_arAChanel[i]->m_dMaxAbs)
                m_dMaxIAbs = m_arAChanel[i]->m_dMaxAbs;
        }	
        else								//直流通道
        {
            if(m_dMaxZAbs < m_arAChanel[i]->m_dMaxAbs)
                m_dMaxZAbs = m_arAChanel[i]->m_dMaxAbs;
        }
    }
    
    if(m_dMaxUAbs < g_dMaxUAbs_Min)
    {
        m_dMaxUAbs = g_dMaxUAbs_Min;
    }
    if(m_dMaxIAbs < g_dMaxIAbs_Min)
    {
        m_dMaxIAbs = g_dMaxIAbs_Min;
    }
    if(m_dMaxIAbs*1.5 < m_dMaxUAbs)
    {
        m_dMaxIAbs *= 1.5;
    }
    
    if(m_dMaxZAbs < g_dMaxZAbs_Min)
    {
        m_dMaxZAbs = g_dMaxZAbs_Min;
    }
    m_dMaxZAbs *= 1.5;
    
    Generate_ZL_Abs();
}

void CCmtdFile::Generate_ZL_Abs()
{
    for(int i=0; i<m_arDC.count(); i++)
    {
        if(m_arDC[i]->m_pChanel == NULL)
        {
            continue;
        }
        if(m_arDC[i]->m_wType == CEleDC::ZL_OTHER)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_OTHER)
            {
                m_dMaxZAbs_ZL_OTHER = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZL_30V_GP)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_30V_GP)
            {
                m_dMaxZAbs_ZL_30V_GP = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZL_5V_VOL)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_5V_VOL)
            {
                m_dMaxZAbs_ZL_5V_VOL = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZL_300V_VOL)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_300V_VOL)
            {
                m_dMaxZAbs_ZL_300V_VOL = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZL_2000V_VOL)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_2000V_VOL)
            {
                m_dMaxZAbs_ZL_2000V_VOL = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZL_200MV_VOL)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_ZL_200MV_VOL)
            {
                m_dMaxZAbs_ZL_ZL_200MV_VOL = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZL_4TO20MA_INF)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_ZL_4TO20MA_INF)
            {
                m_dMaxZAbs_ZL_ZL_4TO20MA_INF = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::JL_57V_VOL)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_JL_57V_VOL)
            {
                m_dMaxZAbs_ZL_JL_57V_VOL = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::JL_100V_VOL)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_JL_100V_VOL)
            {
                m_dMaxZAbs_ZL_JL_100V_VOL = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::JL_5A_INF)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_JL_5A_INF)
            {
                m_dMaxZAbs_ZL_JL_5A_INF = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::JL_1A_INF)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_JL_1A_INF)
            {
                m_dMaxZAbs_ZL_JL_1A_INF = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZP_100V_VOL)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_ZP_100V_VOL)
            {
                m_dMaxZAbs_ZL_ZP_100V_VOL = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZP_400V_VOL)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_ZP_400V_VOL)
            {
                m_dMaxZAbs_ZL_ZP_400V_VOL = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZP_5A_INF)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_ZP_5A_INF)
            {
                m_dMaxZAbs_ZL_ZP_5A_INF = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
        else if(m_arDC[i]->m_wType == CEleDC::ZL_PINLV)
        {
            if(m_arDC[i]->m_pChanel->m_dMaxAbs > m_dMaxZAbs_ZL_ZL_PINLV)
            {
                m_dMaxZAbs_ZL_ZL_PINLV = m_arDC[i]->m_pChanel->m_dMaxAbs;
            }
        }
    }
    
    //对通道合理值进行校验
    if(m_dMaxZAbs_ZL_OTHER < 20)
    {
        m_dMaxZAbs_ZL_OTHER = 20;
    }
    if(m_dMaxZAbs_ZL_30V_GP < 30)
    {
        m_dMaxZAbs_ZL_30V_GP = 30;
    }
    if(m_dMaxZAbs_ZL_5V_VOL < 5)
    {
        m_dMaxZAbs_ZL_5V_VOL = 5;
    }
    if(m_dMaxZAbs_ZL_300V_VOL < 50)
    {
        m_dMaxZAbs_ZL_300V_VOL = 50;
    }
    if(m_dMaxZAbs_ZL_2000V_VOL < 50)
    {
        m_dMaxZAbs_ZL_2000V_VOL = 50;
    }
    if(m_dMaxZAbs_ZL_ZL_200MV_VOL < 50)
    {
        m_dMaxZAbs_ZL_ZL_200MV_VOL = 50;
    }
    if(m_dMaxZAbs_ZL_ZL_4TO20MA_INF < 20)
    {
        m_dMaxZAbs_ZL_ZL_4TO20MA_INF = 20;
    }
    if(m_dMaxZAbs_ZL_JL_57V_VOL < 50)
    {
        m_dMaxZAbs_ZL_JL_57V_VOL = 50;
    }
    if(m_dMaxZAbs_ZL_JL_100V_VOL < 50)
    {
        m_dMaxZAbs_ZL_JL_100V_VOL = 50;
    }
    if(m_dMaxZAbs_ZL_JL_5A_INF < 5)
    {
        m_dMaxZAbs_ZL_JL_5A_INF = 5;
    }
    if(m_dMaxZAbs_ZL_JL_1A_INF < 2)
    {
        m_dMaxZAbs_ZL_JL_1A_INF = 2;
    }
    if(m_dMaxZAbs_ZL_ZP_100V_VOL < 50)
    {
        m_dMaxZAbs_ZL_ZP_100V_VOL = 50;
    }
    if(m_dMaxZAbs_ZL_ZP_400V_VOL < 50)
    {
        m_dMaxZAbs_ZL_ZP_400V_VOL = 50;
    }
    if(m_dMaxZAbs_ZL_ZP_5A_INF < 5)
    {
        m_dMaxZAbs_ZL_ZP_5A_INF = 5;
    }
    if(m_dMaxZAbs_ZL_ZL_PINLV < 5)
    {
        m_dMaxZAbs_ZL_ZL_PINLV = 5;
    }
    
    m_dMaxZAbs_ZL_OTHER *= (float)(1.2);
    m_dMaxZAbs_ZL_30V_GP *= (float)(1.2);
    m_dMaxZAbs_ZL_5V_VOL *= (float)(1.2);
    m_dMaxZAbs_ZL_300V_VOL *= (float)(1.2);
    m_dMaxZAbs_ZL_2000V_VOL *= (float)(1.2);
    m_dMaxZAbs_ZL_ZL_200MV_VOL *= (float)(1.2);
    m_dMaxZAbs_ZL_ZL_4TO20MA_INF *= (float)(1.2);
    m_dMaxZAbs_ZL_JL_57V_VOL *= (float)(1.2);
    m_dMaxZAbs_ZL_JL_100V_VOL *= (float)(1.2);
    m_dMaxZAbs_ZL_JL_5A_INF *= (float)(1.2);
    m_dMaxZAbs_ZL_JL_1A_INF *= (float)(1.2);
    m_dMaxZAbs_ZL_ZP_100V_VOL *= (float)(1.2);
    m_dMaxZAbs_ZL_ZP_400V_VOL *= (float)(1.2);
    m_dMaxZAbs_ZL_ZP_5A_INF *= (float)(1.2);
    m_dMaxZAbs_ZL_ZL_PINLV *= (float)(1.2);
    
}

bool CCmtdFile::IsFileExist(const QString& strFilePath)
{
    QFileInfo finfo(strFilePath);
    return finfo.exists();
}

void CCmtdFile::GenerateUnit()
{
    int i = 0;
    //整理一次侧单位
    for(i=0; i<m_nACount; i++)
    {
        //冀北电科院,暂时屏蔽 2019-12-25
        //[[
        if((m_arAChanel[i]->m_wType == 1)||(m_arAChanel[i]->m_wType == 2))
        {
            strcpy(m_arAChanel[i]->m_chUnit1,"k");
            strcat(m_arAChanel[i]->m_chUnit1,m_arAChanel[i]->m_chUnit2);
        }

        //2019-12-25
        //如果有DMF文件,从DMF文件中读取单位
        if(m_arAChanel[i]->m_eSiUnit != CEleAChanel::unit_unknown)
        {
            if(m_arAChanel[i]->m_eSiUnit == CEleAChanel::unit_A)
                strcpy(m_arAChanel[i]->m_chUnit2,"A");
            else if(m_arAChanel[i]->m_eSiUnit == CEleAChanel::unit_V)
                strcpy(m_arAChanel[i]->m_chUnit2,"V");
            else if(m_arAChanel[i]->m_eSiUnit == CEleAChanel::unit_Hz)
                strcpy(m_arAChanel[i]->m_chUnit2,"Hz");
            else if(m_arAChanel[i]->m_eSiUnit == CEleAChanel::unit_O)
                strcpy(m_arAChanel[i]->m_chUnit2,"Ω");
            else if(m_arAChanel[i]->m_eSiUnit == CEleAChanel::unit_W)
                strcpy(m_arAChanel[i]->m_chUnit2,"W");
            else if(m_arAChanel[i]->m_eSiUnit == CEleAChanel::unit_Var)
                strcpy(m_arAChanel[i]->m_chUnit2,"Var");

            if(m_arAChanel[i]->m_eMultiplier == CEleAChanel::multi_k)
                strcpy(m_arAChanel[i]->m_chUnit1,"k");
            else if(m_arAChanel[i]->m_eMultiplier == CEleAChanel::multi_m)
                strcpy(m_arAChanel[i]->m_chUnit1,"m");
            else if(m_arAChanel[i]->m_eMultiplier == CEleAChanel::multi_M)
                strcpy(m_arAChanel[i]->m_chUnit1,"M");
            else
            {
                if((m_arAChanel[i]->m_eSiUnit == CEleAChanel::unit_A)||(m_arAChanel[i]->m_eSiUnit == CEleAChanel::unit_V))
                    strcpy(m_arAChanel[i]->m_chUnit1,"k");
                else
                    strcpy(m_arAChanel[i]->m_chUnit1,"");
            }
            strcat(m_arAChanel[i]->m_chUnit1,m_arAChanel[i]->m_chUnit2);
        }
        //]]
    }
}

void CCmtdFile::GenerateOtherInfo()
{    
    int i = 0;
    //整理一次侧单位
    float dTime0 = (float)(m_pSampleTime[0]/1000.0);
    m_nTbPos = -1;
    if(m_dTimeSpan < 0.00000001)	//两个时刻相同(WGL9000)
    {
        int nsec = (int)((m_wLeftMiniSec + fabs(m_pSampleTime[0]/1000.0))/1000.0);
        m_dTimeSpan = (float)(fabs(m_pSampleTime[0]/1000.0));
        m_wFaultMiniSec = (m_wLeftMiniSec + (int)(fabs(m_pSampleTime[0]/1000.0)))%1000;
        m_tmStart = m_tmLeft.addSecs(nsec);
        m_strStartTime.sprintf("%d-%d-%d %d:%d:%d.%.3d",m_tmStart.date().year(),m_tmStart.date().month(),m_tmStart.date().day(),m_tmStart.time().hour(),m_tmStart.time().minute(),m_tmStart.time().second(),m_wFaultMiniSec);
        for(i=0; i<m_nTotalPoints; i++)
        {
            if(m_pSampleTime[i] >= 0)
            {
                m_nTbPos = i;
                break;
            }
        }
    }
    else if(dTime0 > (-1.0))	//WGL3000,第一个点时标总为0
    {
        for(i=0; i<m_nTotalPoints; i++)
        {
            m_pSampleTime[i] -= (int)(m_dTimeSpan*1000.0);
            if((m_pSampleTime[i] >= 0)&&(m_nTbPos < 0))
            {
                m_nTbPos = i;
            }
        }
    }
    else						//WGL9000+
    {
        //////////////////////////////////////////////////////////////////////////
        //确定0时刻位置,(点序号)
        for(i=0; i<m_nTotalPoints; i++)
        {
            if(m_pSampleTime[i] >= 0)
            {
                m_nTbPos = i;
                break;
            }
        }
    }
    if(m_nTbPos < 0)
    {
        m_nTbPos = 0;
    }
    
    //////////////////////////////////////////////////////////////////////////
    //重新确定零时刻字符串
    m_strLeftTime.sprintf("%d-%d-%d %d:%d:%d.%.3d",m_tmLeft.date().year(),m_tmLeft.date().month(),m_tmLeft.date().day(),m_tmLeft.time().hour(),m_tmLeft.time().minute(),m_tmLeft.time().second(),m_wLeftMiniSec);
    m_bLRC = true;
    for(i=0; i<m_nSegCount-1; i++)
    {
        if(m_pSegment[i].m_nWavePoints != m_pSegment[i+1].m_nWavePoints)
        {
            m_bLRC = false;
            break;
        }
    }
    //----------------------------------------------------------------------------------
    //根据读到的采样点数目,确认是累加的还是分离的
    //----------------------------------------------------------------------------------
    if(fabs((float)(m_nTotalPoints-m_pSegment[m_nSegCount-1].m_nCount)) < 10)	//是累加的
    {
        for(i=m_nSegCount-1; i>0; i--)
        {
            m_pSegment[i].m_nCount -= m_pSegment[i-1].m_nCount;
        }
    }
    
    //----------------------------------------------------------------------------------
    //合并采样率相同的采样段
    //2009-04-17
    //----------------------------------------------------------------------------------
    if(m_nSegCount > 1)
    {
        int nsegcount = 0;
        CCmtdSegment* pseg = new CCmtdSegment[m_nSegCount];
        pseg[nsegcount] = m_pSegment[0];
        for(int nseg=1; nseg<m_nSegCount; nseg++)
        {			
            if(m_pSegment[nseg].m_nSecCount != pseg[nsegcount].m_nSecCount)
            {
                nsegcount++;
                pseg[nsegcount] = m_pSegment[nseg];
                //2010-10-30 添加
                pseg[nsegcount].m_nStartPos = pseg[nsegcount-1].m_nStartPos+pseg[nsegcount-1].m_nCount;
            }
            else
            {
                pseg[nsegcount].m_nCount += m_pSegment[nseg].m_nCount;
            }
        }
        nsegcount++;
        for(int nseg=0; nseg<nsegcount; nseg++)
        {
            m_pSegment[nseg] = pseg[nseg];
        }
        m_nSegCount = nsegcount;
        delete []pseg;
    }
    
    //////////////////////////////////////////////////////////////////////////
    //兼容1997(采样率都为0)的格式 [2/19/2008]
    //根据采样点之间的时间间隔计算每周波采样点数目
    if(m_wCmtdYear == 1997)
    {
        int nstart = 0;
        int ntimes = 0;
        for(int i=0; i<m_nSegCount; i++)
        {
            nstart = m_pSegment[i].m_nStartPos+1;
            ntimes = (int)((m_pSampleTime[nstart+1]-m_pSampleTime[nstart])/1000.0);
            m_pSegment[i].m_nWavePoints = (int)(20.0/ntimes);
        }
    }
    //]
     
    //////////////////////////////////////////////////////////////////////////
    //读扩展直流配置文件
    QString strtmp = m_strCfgFilePath;
    QFileInfo finfo(strtmp);
    char strline[2048] = {0};
    strtmp = finfo.absolutePath()+QString("/DC_Extend.txt");
    QFile cfgfile(strtmp);
    if(cfgfile.open(QIODevice::ReadOnly))
    {
        unsigned short wId = 0;
        char chseg[] = ",\r\n";
        int n = cfgfile.readLine(strline,sizeof(strline));
        while(n > 0)
        {
            char* token = strtok(strline,chseg);
            wId =  atoi(token);
            for(int i=0; i<m_arDC.count(); i++)
            {
                if(m_arDC[i]->m_pChanel == NULL)
                {
                    continue;
                }
                if(m_arDC[i]->m_pChanel->m_wID == wId)
                {
                    m_arDC[i]->m_bExternDC = true;
                    token = strtok(NULL,chseg);
                    m_arDC[i]->m_dMin_Two = (float)(atof(token));
                    token = strtok(NULL,chseg);
                    m_arDC[i]->m_dMax_Two = (float)(atof(token));
                    token = strtok(NULL,chseg);
                    m_arDC[i]->m_dMin_One = (float)(atof(token));
                    token = strtok(NULL,chseg);
                    m_arDC[i]->m_dMax_One = (float)(atof(token));
                    break;
                }
            }
            n = cfgfile.readLine(strline,sizeof(strline));
        }
        cfgfile.close();
    }
    
    Generate_ZL_Abs();

    for(int i=0; i<m_arLine.count(); i++)
    {
        if(m_arLine[i]->m_dCT < 1)
        {
            if(m_arLine[i]->m_pAChanel != NULL)
                m_arLine[i]->m_dCT = m_arLine[i]->m_pAChanel->m_dCT;
        }
//        qDebug("line%d = %.3f",i,m_arLine[i]->m_dCT);
    }

    const float fEpslon = 0.0001;
    for(int i=0; i<m_arLine.count(); i++)
    {
        if(m_arLine[i]->m_dR0 < fEpslon)
            m_arLine[i]->m_dR0 = fEpslon;
        if(m_arLine[i]->m_dR1 < fEpslon)
            m_arLine[i]->m_dR1 = fEpslon;
        if(m_arLine[i]->m_dX0 < fEpslon)
            m_arLine[i]->m_dX0 = fEpslon;
        if(m_arLine[i]->m_dX1 < fEpslon)
            m_arLine[i]->m_dX1 = fEpslon;
    }
}

void CCmtdFile::GenerateLineInfo()
{
    int i=0;
    int n = 0;
    //生成和电流
    for(i=0; i<m_arLine.count(); i++)
    {
        CEleLine* pLine = m_arLine[i];
        if(pLine->m_nBranNum != 2)
        {
            continue;
        }
        CEleAChanel* pIa = new CEleAChanel();
        CEleAChanel* pIb = new CEleAChanel();
        CEleAChanel* pIc = new CEleAChanel();
        CEleAChanel* pIn = new CEleAChanel();

        strcpy(pIa->m_chName,pLine->m_chName);
        strcpy(pIb->m_chName,pLine->m_chName);
        strcpy(pIc->m_chName,pLine->m_chName);
        strcpy(pIn->m_chName,pLine->m_chName);
        strcat(pIa->m_chName,"Ia");
        strcat(pIb->m_chName,"Ib");
        strcat(pIc->m_chName,"Ic");
        strcat(pIn->m_chName,"3I0");
        strcpy(pIa->m_chUnit2,"A");
        strcpy(pIb->m_chUnit2,"A");
        strcpy(pIc->m_chUnit2,"A");
        strcpy(pIn->m_chUnit2,"A");
        strcpy(pIa->m_chUnit1,"kA");
        strcpy(pIb->m_chUnit1,"kA");
        strcpy(pIc->m_chUnit1,"kA");
        strcpy(pIn->m_chUnit1,"kA");
        pIa->m_wType = 2;
        pIb->m_wType = 2;
        pIc->m_wType = 2;
        pIn->m_wType = 2;

        CEleAChanel* pA1 = GetAChanelById(pLine->m_wAID);
        CEleAChanel* pA2 = GetAChanelById(pLine->m_wAID2);
        CEleAChanel* pB1 = GetAChanelById(pLine->m_wBID);
        CEleAChanel* pB2 = GetAChanelById(pLine->m_wBID2);
        CEleAChanel* pC1 = GetAChanelById(pLine->m_wCID);
        CEleAChanel* pC2 = GetAChanelById(pLine->m_wCID2);
        CEleAChanel* pN1 = GetAChanelById(pLine->m_wNID);
        CEleAChanel* pN2 = GetAChanelById(pLine->m_wNID2);

        float fIa=0,fIb=0,fIc=0,fIn=0;
        for(n=0; n<m_nTotalPoints; n++)
        {
            fIa=fIb=fIc=fIn = 0;
            if(pLine->m_eDir1 == CEleLine::dir_NEG)
            {
                if(pA1)
                    fIa -= pA1->m_pData[n];
                if(pB1)
                    fIb -= pB1->m_pData[n];
                if(pC1)
                    fIc -= pC1->m_pData[n];
                if(pN1)
                    fIn -= pN1->m_pData[n];
            }
            else
            {
                if(pA1)
                    fIa += pA1->m_pData[n];
                if(pB1)
                    fIb += pB1->m_pData[n];
                if(pC1)
                    fIc += pC1->m_pData[n];
                if(pN1)
                    fIn += pN1->m_pData[n];
            }

            if(pLine->m_eDir2 == CEleLine::dir_NEG) //反方向
            {
                if(pA2)
                    fIa -= pA2->m_pData[n];
                if(pB2)
                    fIb -= pB2->m_pData[n];
                if(pC2)
                    fIc -= pC2->m_pData[n];
                if(pN2)
                    fIn -= pN2->m_pData[n];
            }
            else        //正方向
            {
                if(pA2)
                    fIa += pA2->m_pData[n];
                if(pB2)
                    fIb += pB2->m_pData[n];
                if(pC2)
                    fIc += pC2->m_pData[n];
                if(pN2)
                    fIn += pN2->m_pData[n];
            }
            if(fabs(fIa) > pIa->m_dMaxAbs)
                pIa->m_dMaxAbs = fIa;
            if(fabs(fIb) > pIb->m_dMaxAbs)
                pIb->m_dMaxAbs = fIb;
            if(fabs(fIc) > pIc->m_dMaxAbs)
                pIc->m_dMaxAbs = fIc;
            pIa->m_pData.append(fIa);
            pIb->m_pData.append(fIb);
            pIc->m_pData.append(fIc);
            if((pN1!=NULL)&&(pN2!=NULL))    //两个分支的零序都存在
                pIn->m_pData.append(fIn);
            else
                pIn->m_pData.append(fIa+fIb+fIc);
        }
        pLine->m_pAChanel = pIa;
        pLine->m_pBChanel = pIb;
        pLine->m_pCChanel = pIc;
        pLine->m_pNChanel = pIn;
        pIa->m_crColor = Qt::yellow;
        pIb->m_crColor = Qt::green;
        pIc->m_crColor = Qt::red;
        pIn->m_crColor = Qt::white;

        pIa->m_wID = m_arAChanel.count()+1;
        m_arAChanel.append(pIa);
        pIb->m_wID = m_arAChanel.count()+1;
        m_arAChanel.append(pIb);
        pIc->m_wID = m_arAChanel.count()+1;
        m_arAChanel.append(pIc);
        pIn->m_wID = m_arAChanel.count()+1;
        m_arAChanel.append(pIn);
    }

    GetFaultInfo();
}

bool CCmtdFile::FileLoadFinished()
{
    if(m_bLoadFinished)
    {
        return true;
    }
    return false;
}

bool CCmtdFile::SaveFileAs(int *a_pAChanel,int a_nACount, int *a_pDChanel,int a_nDCount, const QString& a_strFilePath)
{
    if(a_nACount+a_nDCount <= 0)
    {
        strcpy(m_chErrorInfo,"通道总数为0,保存失败");
        return false;
    }

    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    m_strTmp = a_strFilePath;
    int np = m_strTmp.lastIndexOf('.');
    if(np > 0)
    {
        m_strTmp = m_strTmp.left(np);
    }

    //////////////////////////////////////////////////////////////////////////
    //cfg文件
    //[[
    QFile srcFile(m_strCfgFilePath);
    if(!srcFile.open(QIODevice::ReadOnly))
    {
        sprintf(m_chErrorInfo,"打开源cfg文件失败. 文件路径: %s",gbk->fromUnicode(m_strCfgFilePath).constData());
        ////delete gbk;
        return false;
    }

    QString strPP;
    if(m_bUpperCase)
        strPP = m_strTmp+QString(".cfg");
    else
        strPP = m_strTmp+QString(".cfg");
    QFile cfgfile(strPP);
    if(!cfgfile.open(QFile::WriteOnly))
    {
        sprintf(m_chErrorInfo,"创建cfg文件失败.文件路径: %s",gbk->fromUnicode(m_strTmp+".cfg").constData());
        ////delete gbk;
        return false;
    }

    QString strline,strsrc;
    int nChN = 0;
    char chline[4096] = {0};
    const int size = 4096;
    sprintf(chline,"%s,%d,1999\r\n",gbk->fromUnicode(m_strStationName).constData(),m_nRecId);
    cfgfile.write(chline);
    sprintf(chline,"%d,%dA,%dD\r\n",a_nACount+a_nDCount,a_nACount,a_nDCount);
    cfgfile.write(chline);

    srcFile.readLine(chline,size);
    srcFile.readLine(chline,size);
    int nIndex = 0;
    int i=0,j=0;
    QStringList arChanel;
    QMap<int,QString> mapChanel;
    for(i=0; i<m_nACount; i++)
    {
        srcFile.readLine(chline,size);
        strsrc = gbk->toUnicode(chline);
        np = strsrc.indexOf(',');
        if(np < 0)
        {
            continue;
        }
        nChN = strsrc.left(np).toInt();
        strsrc = strsrc.right(strsrc.length()-np-1);

        for(j=0; j<a_nACount; j++)
        {
            if(a_pAChanel[j] == nChN)
            {
                strsrc.remove(QChar('\r'));
                strsrc.remove(QChar('\n'));
                sprintf(chline,",%s\r\n",gbk->fromUnicode(strsrc).constData());
//                cfgfile.write(chline);
                mapChanel.insert(nChN,gbk->toUnicode(chline));
                nIndex++;

                break;
            }
        }
    }

    for(int i=0; i<nIndex; i++)
    {
        cfgfile.write(gbk->fromUnicode(QString("%1%2").arg(i+1).arg(mapChanel.value(a_pAChanel[i]))));
    }
    mapChanel.clear();
    nIndex = 0;
    for(i=0; i<m_nDCount; i++)
    {
        srcFile.readLine(chline,size);
        strsrc = gbk->toUnicode(chline);
        np = strsrc.indexOf(',');
        if(np < 0)
        {
            continue;
        }
        nChN = strsrc.left(np).toInt();
        strsrc = strsrc.right(strsrc.length()-np-1);
        for(j=0; j<a_nDCount; j++)
        {
            if(a_pDChanel[j] == nChN)
            {
                strsrc.remove(QChar('\r'));
                strsrc.remove(QChar('\n'));
                sprintf(chline,",%s\r\n",gbk->fromUnicode(strsrc).constData());
//                cfgfile.write(chline);
                mapChanel.insert(nChN,gbk->toUnicode(chline));
                nIndex++;
                break;
            }
        }
    }
    for(i=0; i<nIndex; i++)
    {
        cfgfile.write(gbk->fromUnicode(QString("%1%2").arg(i+1).arg(mapChanel.value(a_pDChanel[i]))));
    }
    mapChanel.clear();

    //频率
    srcFile.readLine(chline,size);
    strsrc = gbk->toUnicode(chline);
    strsrc.remove(QChar('\r'));
    strsrc.remove(QChar('\n'));
    cfgfile.write(gbk->fromUnicode(strsrc+QString("\r\n")).constData());
    //采样段
    srcFile.readLine(chline,size);
    strsrc = gbk->toUnicode(chline);
    strsrc.remove(QChar('\r'));
    strsrc.remove(QChar('\n'));
    int nseg = strsrc.toInt();
    cfgfile.write(gbk->fromUnicode(strsrc+"\r\n").constData());
    //写各采样段和两行时间
    for(i=0; i<nseg+2; i++)
    {
        srcFile.readLine(chline,size);
        strsrc = gbk->toUnicode(chline);
        strsrc.remove(QChar('\r'));
        strsrc.remove(QChar('\n'));
//        qDebug("%s",strsrc.toLocal8Bit().constData());
        cfgfile.write(gbk->fromUnicode(strsrc+"\r\n"));
    }
    //DAT文件格式(固定为BINARY)
    strcpy(chline,"BINARY\r\n");
    cfgfile.write(chline);
    strcpy(chline,"1.0\r\n");
    cfgfile.write(chline);

    srcFile.close();
    cfgfile.close();
    //]]

    //////////////////////////////////////////////////////////////////////////
    //dat文件
    //[[
    tagDatUnit dUnit;
    memset(&dUnit,0,sizeof(tagDatUnit));
    int nanasize = a_nACount*2;
    int ndigsize = a_nDCount/8;
    if(a_nDCount%8 != 0)
    {
        ndigsize += 1;
    }
    if(ndigsize%2 != 0)
    {
        ndigsize += 1;
    }
    int nblocksize = 8 + nanasize + ndigsize;
    int cn = 0;
    int nPos = 0;
    unsigned short wValue = 0;
    QString strDP;
    if(m_bUpperCase)
        strDP = m_strTmp+".dat";
    else
        strDP = m_strTmp+".dat";
    QFile datfile(strDP);
    if(!datfile.open(QIODevice::WriteOnly))
    {
        sprintf(m_chErrorInfo,"Create dat file error. File path:%s",gbk->fromUnicode(m_strTmp+".dat"+".dat").constData());
        return false;
    }
    char* buf = new char[nblocksize*m_nTotalPoints];
//    CEleAChanel* pAChanel = NULL;
    unsigned char ukg = 0x01;
    for(i=0; i<m_nTotalPoints; i++)
    {
        memset(&dUnit,0,sizeof(tagDatUnit));
        dUnit.m_nSampIndex = i+1;
        dUnit.m_nSampTime = m_pSampleTime[i];
        nPos = 0;
        for(cn=0; cn<a_nACount; cn++)
        {
            if((a_pAChanel[cn]>0)&&(a_pAChanel[cn]<=m_nACount))
            {
                dUnit.m_nSampData[nPos] = (int)((m_arAChanel[a_pAChanel[cn]-1]->m_pData[i]-m_arAChanel[a_pAChanel[cn]-1]->m_db)/m_arAChanel[a_pAChanel[cn]-1]->m_da+.5);
            }
            else
            {
                dUnit.m_nSampData[nPos] = 0;
            }
            nPos++;
        }
        for(cn=0; cn<a_nDCount; cn++)
        {
            if((a_pDChanel[cn]>0)&&(a_pDChanel[cn]<=m_nDCount))
            {
                if(((m_arDChanel[a_pDChanel[cn]-1]->m_pData[i/8])&(ukg<<(i%8))) != 0)
                {
                    wValue = ushort(pow(2,cn%16));
                    dUnit.m_nSampData[nPos+cn/16] |= wValue;
                }
            }
        }
        memcpy(buf+nblocksize*i,&dUnit,nblocksize);
    }
    datfile.write(buf,nblocksize*m_nTotalPoints);
    datfile.close();
    //]]
    delete []buf;
    ////delete gbk;

    return true;
}

bool CCmtdFile::SaveLineFile(CEleLine* a_pLine, const QString& a_strFilePath,bool a_bAct/*=false*/,bool a_bUpperCase/*=false*/)
{
    int pAChanel[128] = {0};
    int pDChanel[512] = {0};
    int nAChanel = 0;
    int nDChanel = 0;
    int i = 0;
    int nBus=1,nLine=1,nSingle=0;
    CEleLine* pLine1 = a_pLine;
    CEleBus* pBus1 = pLine1->m_pBus;

    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    if(pBus1 != NULL)
    {
        nBus = 1;
        if(pBus1->m_pAChanel != NULL)
            pAChanel[nAChanel++] = pBus1->m_pAChanel->m_wID;
        if(pBus1->m_pBChanel != NULL)
            pAChanel[nAChanel++] = pBus1->m_pBChanel->m_wID;
        if(pBus1->m_pCChanel != NULL)
            pAChanel[nAChanel++] = pBus1->m_pCChanel->m_wID;
        if(pBus1->m_pNChanel != NULL)
            pAChanel[nAChanel++] = pBus1->m_pNChanel->m_wID;
        if((pBus1->m_wLID>0)&&(pBus1->m_wLID<=(uint)m_nACount))
            pAChanel[nAChanel++] = pBus1->m_wLID;
        for(i=0; i<pBus1->m_arAChanel.count(); i++)
        {
           if((pBus1->m_arAChanel[i] > 0)&&(pBus1->m_arAChanel[i] <= (uint)m_nACount))
           {
               pAChanel[nAChanel++] = pBus1->m_arAChanel[i];
           }
        }
        for(i=0; i<pBus1->m_arDChanel.count(); i++)
        {
            if((pBus1->m_arDChanel[i] > 0)&&(pBus1->m_arDChanel[i] <= (uint)m_nDCount))
            {
                pDChanel[nDChanel++] = pBus1->m_arDChanel[i];
            }
        }
    }

    if((pLine1->m_wAID>0)&&(pLine1->m_wAID<=m_nACount))
        pAChanel[nAChanel++] = pLine1->m_wAID;
    if((pLine1->m_wBID>0)&&(pLine1->m_wBID<=m_nACount))
        pAChanel[nAChanel++] = pLine1->m_wBID;
    if((pLine1->m_wCID>0)&&(pLine1->m_wCID<=m_nACount))
        pAChanel[nAChanel++] = pLine1->m_wCID;
    if((pLine1->m_wNID>0)&&(pLine1->m_wNID<=m_nACount))
        pAChanel[nAChanel++] = pLine1->m_wNID;
    for(i=0; i<pLine1->m_arAChanel.count(); i++)
    {
        if((pLine1->m_arAChanel[i] > 0)&&(pLine1->m_arAChanel[i] <= (uint)m_nACount))
        {
            pAChanel[nAChanel++] = pLine1->m_arAChanel[i];
        }
    }
    for(i=0; i<pLine1->m_arDChanel.count(); i++)
    {
        if((pLine1->m_arDChanel[i] > 0)&&(pLine1->m_arDChanel[i] <= (uint)m_nDCount))
        {
            pDChanel[nDChanel++] = pLine1->m_arDChanel[i];
        }
    }

    if(pLine1->m_nBranNum == 2)
    {
        if((pLine1->m_wAID2>0)&&(pLine1->m_wAID2<=m_nACount))
            pAChanel[nAChanel++] = pLine1->m_wAID2;
        if((pLine1->m_wBID2>0)&&(pLine1->m_wBID2<=m_nACount))
            pAChanel[nAChanel++] = pLine1->m_wBID2;
        if((pLine1->m_wCID2>0)&&(pLine1->m_wCID2<=m_nACount))
            pAChanel[nAChanel++] = pLine1->m_wCID2;
        if((pLine1->m_wNID2>0)&&(pLine1->m_wNID2<=m_nACount))
            pAChanel[nAChanel++] = pLine1->m_wNID2;
    }

    if(a_bAct)
    {
        nDChanel = 0;
        for(int i=0; i<m_nDCount; i++)
        {
            if(m_arDChanel[i]->m_bAct)
            {
                pDChanel[nDChanel] = m_arDChanel[i]->m_wID;
                nDChanel++;
            }
        }
    }

    if(!SaveFileAs(pAChanel,nAChanel,pDChanel,nDChanel,a_strFilePath))
    {
        return false;
    }

    //////////////////////////////////////////////////////////////////////////
    //创建lne文件
    //[[
    m_strTmp = a_strFilePath;
    int np = m_strTmp.lastIndexOf('.');
    if(np > 0)
        m_strTmp = m_strTmp.left(np);
    QString strCP;
    if(a_bUpperCase)
        strCP = m_strTmp+QString(".LNE");
    else
        strCP = m_strTmp+QString(".lne");
    QFile lnefile(strCP);
    if(!lnefile.open(QIODevice::WriteOnly))
    {
        return true;
    }

    QString strline = QString("国电武仪COMTRADE_HDR文件Ver2.0\n");
    lnefile.write(gbk->fromUnicode(strline));
    strline = QString("%1,%2,%3,0\n").arg(nBus).arg(nLine).arg(nSingle);
    lnefile.write(gbk->fromUnicode(strline));

    int nA=0,nB=0,nC=0,nN=0;
    int nGp1=0,nGp2=0;
    if(nBus > 0)
    {
        for(int j=0; j<nAChanel; j++)
        {
            if(pAChanel[j] == a_pLine->m_pBus->m_wAID)
                nA = j+1;
            else if(pAChanel[j] == a_pLine->m_pBus->m_wBID)
                nB = j+1;
            else if(pAChanel[j] == a_pLine->m_pBus->m_wCID)
                nC = j+1;
            else if(pAChanel[j] == a_pLine->m_pBus->m_wNID)
                nN = j+1;
        }
        strline = QString("1,%1,%2,%3,%4,%5,%6\n").arg(gbk->toUnicode(a_pLine->m_pBus->m_chName)).arg(nA).arg(nB).arg(nC).arg(nN).arg(a_pLine->m_pBus->m_dVoltage);
        lnefile.write(gbk->fromUnicode(strline));
    }
    //序号,名称,Ia,Ib,Ic,3I0,母线,线路/主变,是否测距,R1,X1,R0,X0,互感线路,忽感电阻,互感电抗,CT,长度,高频1,高频2
    for(int j=0; j<nAChanel; j++)
    {
        if(pAChanel[j] == a_pLine->m_wAID)
            nA = j+1;
        else if(pAChanel[j] == a_pLine->m_wBID)
            nB = j+1;
        else if(pAChanel[j] == a_pLine->m_wCID)
            nC = j+1;
        else if(pAChanel[j] == a_pLine->m_wNID)
            nN = j+1;
        else if(pAChanel[j] == a_pLine->m_sGp1)
            nGp1 = j+1;
        else if(pAChanel[j] == a_pLine->m_sGp2)
            nGp2 = j+1;
    }
    strline = QString("1,%1,%2,%3,%4,%5,%6,线路,1,%7,%8,%9,%10,0,0.000,0.000,%11,%12,%13,%14,%15\n")
            .arg(gbk->toUnicode(a_pLine->m_chName))
            .arg(nA).arg(nB).arg(nC).arg(nN)
            .arg(nBus)
            .arg(a_pLine->m_dR1,0,'f',4,QChar('0')).arg(a_pLine->m_dX1,0,'f',4,QChar('0'))
            .arg(a_pLine->m_dR0,0,'f',4,QChar('0')).arg(a_pLine->m_dX0,0,'f',4,QChar('0'))
            .arg(a_pLine->m_dMaxI,0,'f',4,QChar('0')).arg(a_pLine->m_dCT,0,'f',4,QChar('0'))
            .arg(a_pLine->m_dLength,0,'f',4,QChar('0'))
            .arg(nGp1).arg(nGp2);
    lnefile.write(gbk->fromUnicode(strline));

    strline = QString("%1\n").arg(nDChanel);
    lnefile.write(gbk->fromUnicode(strline));
    strline = QString("1");
    QString strr;
    CEleDChanel* pDCH = NULL;
    for(int i=0; i<nDChanel; i++)
    {
        pDCH = GetDChanelById(pDChanel[i]);
        if(pDCH != NULL)
        {
            if(pDCH->m_strFlag == QString("TrPhsA"))
                strr = QString(",%1:21").arg(i+1);
            else if(pDCH->m_strFlag == QString("TrPhsB"))
                strr = QString(",%1:22").arg(i+1);
            else if(pDCH->m_strFlag == QString("TrPhsC"))
                strr = QString(",%1:23").arg(i+1);
            else if(pDCH->m_strFlag == QString("OpTP"))
                strr = QString(",%1:24").arg(i+1);
            else if(pDCH->m_strFlag == QString("RecOpCls"))
                strr = QString(",%1:25").arg(i+1);
            else
                strr = QString(",%1:0").arg(i+1);
        }
        else
        {
            strr = QString(",%1:0").arg(i+1);
        }
        strline += strr;
    }
    strline += QString("\n");
    lnefile.write(gbk->fromUnicode(strline).constData());
    lnefile.write(gbk->fromUnicode(m_strAttach+QString("\n")).constData());

    lnefile.close();
    //]]

    //////////////////////////////////////////////////////////////////////////////////
    //创建DMF文件
    //[[
    m_strTmp = a_strFilePath;
    np = m_strTmp.lastIndexOf('.');
    if(np > 0)
        m_strTmp = m_strTmp.left(np);
    QString strMP;
    if(a_bUpperCase)
        strMP = m_strTmp+QString(".DMF");
    else
        strMP = m_strTmp+QString(".dmf");
    QFile dmffile(strMP);
    dmffile.remove();
    if(!dmffile.open(QIODevice::WriteOnly))
    {
        return false;
    }

    strline = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
    dmffile.write(strline.toUtf8());
    strline = QString("<scl:ComtradeModel station_name=\"%1\" version=\"%2\" reference=\"%3\" rec_dev_name=\"%4\"  rec_ref=\"%5\" xsi:schemaLocation=\"http://www.iec.ch/61850/2003/SCLcomtrade_mdl_v1.1.xsd\" xmlns:scl=\"http://www.iec.ch/61850/2003/SCL\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\r\n")
            .arg(m_strStationName).arg(m_strVersion).arg(m_strReference).arg(m_strRecDevName).arg(m_strRecRef);
    dmffile.write(strline.toUtf8());

    for(int i=0; i<nAChanel; i++)
    {
        strline = QString("<scl:AnalogChannel idx_cfg=\"%1\" idx_org=\"%2\" ").arg(i+1).arg(pAChanel[i]);
        CEleAChanel* pChanel = GetAChanelById(pAChanel[i]);
        if(pChanel != NULL)
        {
            if(pChanel->m_eType == CEleAChanel::type_A)
                strline += QString("type=\"A\" ");
            else if(pChanel->m_eType == CEleAChanel::type_D)
                strline += QString("type=\"D\" ");
            else if(pChanel->m_eType == CEleAChanel::type_O)
                strline += QString("type=\"O\" ");
            else
                strline += QString("type=\"A\" ");

            if(pChanel->m_eFlag == CEleAChanel::flag_ACV)
                strline += QString("flag=\"ACV\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_ACC)
                strline += QString("flag=\"ACC\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_HF)
                strline += QString("flag=\"HF\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_FQ)
                strline += QString("flag=\"FQ\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_AG)
                strline += QString("flag=\"AG\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_AMP)
                strline += QString("flag=\"AMP\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_PW)
                strline += QString("flag=\"PW\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_ZX)
                strline += QString("flag=\"ZX\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_CONST)
                strline += QString("flag=\"CONST\" ");

            strline += QString("freq=\"%1\" au=\"%2\" bu=\"%3\" ")
                    .arg(pChanel->m_fFreq,0,'f',1,QChar('0')).arg(pChanel->m_fAU,0,'f',6,QChar('0')).arg(pChanel->m_fBU,0,'f',6,QChar('0'));
            if(pChanel->m_eSiUnit == CEleAChanel::unit_A)
                strline += QString("sIUnit=\"A\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_V)
                strline += QString("sIUnit=\"V\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_Hz)
                strline += QString("sIUnit=\"Hz\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_O)
                strline += QString("sIUnit=\"Ω\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_W)
                strline += QString("sIUnit=\"W\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_Var)
                strline += QString("sIUnit=\"Var\" ");
            else
                strline += QString("sIUnit=\"\" ");

            if(pChanel->m_eMultiplier == CEleAChanel::multi_k)
                strline += QString("multiplier=\"k\" ");
            else if(pChanel->m_eMultiplier == CEleAChanel::multi_m)
                strline += QString("multiplier=\"m\" ");
            else if(pChanel->m_eMultiplier == CEleAChanel::multi_M)
                strline += QString("multiplier=\"M\" ");
            else
                strline += QString("multiplier=\"\" ");

            strline += QString("primary=\"%1\" secondary=\"%2\" ")
                    .arg(pChanel->m_fPrimary,0,'f',6,QChar('0'))
                    .arg(pChanel->m_fSecondary,0,'f',6,QChar('0'));

            if(pChanel->m_ePS == CEleAChanel::ps_P)
                strline += QString("ps=\"P\"/>\r\n");
            else if(pChanel->m_ePS == CEleAChanel::ps_S)
                strline += QString("ps=\"S\"/>\r\n");
            else
                strline += QString("ps=\"S\"/>\r\n");
        }
        else
            strline += QString("type=\"A\" flag=\"ACV\" freq=\"50.0\" au=\"1.000000\" bu=\"0.000000\" sIUnit=\"V\" multiplier=\"\" primary=\"2500.000\" secondary=\"1.000\" ps=\"S\"/>\r\n");
        dmffile.write(strline.toUtf8());
    }

    //DChanel
    for(int i=0; i<nDChanel; i++)
    {
        strline = QString("<scl:StatusChannel idx_cfg=\"%1\" idx_org=\"%2\" ").arg(i+1).arg(i+1);
        CEleDChanel* pChanel = GetDChanelById(pDChanel[i]);
        if(pChanel != NULL)
        {
            if(pChanel->m_eType == CEleDChanel::Relay)
                strline += QString("type=\"Relay\" ");
            else if(pChanel->m_eType == CEleDChanel::Breaker)
                strline += QString("type=\"Breaker\" ");
            else if(pChanel->m_eType == CEleDChanel::Switch)
                strline += QString("type=\"Switch\" ");
            else if(pChanel->m_eType == CEleDChanel::Warning)
                strline += QString("type=\"Warning\" ");
            else if(pChanel->m_eType == CEleDChanel::Other)
                strline += QString("type=\"Other\" ");
            strline += QString("flag=\"%1\" ").arg(pChanel->m_strFlag);
            if(pChanel->m_eContact == CEleDChanel::NormallyOpen)
                strline += QString("contact=\"NormallyOpen\" ");
            else if(pChanel->m_eContact == CEleDChanel::NormallyClosed)
                strline += QString("contact=\"NormallyClosed\" ");
            else
                strline += QString("contact=\"NormallyOpen\" ");
            strline += QString("srcRef=\"%1\"/>\r\n").arg(pChanel->m_strSrcRef);
        }
        else
            strline += QString("type=\"Other\" flag=\"general\" contact=\"NormallyOpen\" srcRef=\"\"/>\r\n");
        dmffile.write(strline.toUtf8());
    }

    unsigned short usA=0,usB=0,usC=0,usN=0,usL=0;
    //Bus
    if(pBus1 != NULL)
    {
        if(pBus1->m_eTvPos == CEleBus::e_tv_bus)
            strline = QString("<scl:Bus idx=\"1\" bus_name=\"%1\" srcRef=\"%2\" VRtg=\"%3\" VRtgSnd=\"100.0\" VRtgSnd_Pos=\"BUS\">\r\n").arg(gbk->toUnicode(a_pLine->m_pBus->m_chName)).arg(pBus1->m_strSrcRef).arg(a_pLine->m_pBus->m_dVoltage);
        else if(pBus1->m_eTvPos == CEleBus::e_tv_line)
            strline = QString("<scl:Bus idx=\"1\" bus_name=\"%1\" srcRef=\"%2\" VRtg=\"%3\" VRtgSnd=\"100.0\" VRtgSnd_Pos=\"LINE\">\r\n").arg(gbk->toUnicode(a_pLine->m_pBus->m_chName)).arg(pBus1->m_strSrcRef).arg(a_pLine->m_pBus->m_dVoltage);
        else
            strline = QString("<scl:Bus idx=\"1\" bus_name=\"%1\" srcRef=\"%2\" VRtg=\"%3\" VRtgSnd=\"100.0\" VRtgSnd_Pos=\"BUS\">\r\n").arg(gbk->toUnicode(a_pLine->m_pBus->m_chName)).arg(pBus1->m_strSrcRef).arg(a_pLine->m_pBus->m_dVoltage);
        dmffile.write(strline.toUtf8());

        usA = DMF_GetChanelIDX(pBus1->m_wAID,pAChanel,nAChanel);
        usB = DMF_GetChanelIDX(pBus1->m_wBID,pAChanel,nAChanel);
        usC = DMF_GetChanelIDX(pBus1->m_wCID,pAChanel,nAChanel);
        usN = DMF_GetChanelIDX(pBus1->m_wNID,pAChanel,nAChanel);
        usL = DMF_GetChanelIDX(pBus1->m_wLID,pAChanel,nAChanel);
        strline = QString("<scl:ACVChn ua_idx=\"%1\" ub_idx=\"%2\" uc_idx=\"%3\" un_idx=\"%4\" ul_idx=\"%5\"/>\r\n").arg(usA).arg(usB).arg(usC).arg(usN).arg(usL);
        dmffile.write(strline.toUtf8());
        for(i=0; i<pBus1->m_arAChanel.count(); i++)
        {
            usA = DMF_GetChanelIDX(pBus1->m_arAChanel[i],pAChanel,nAChanel);
            strline = QString("<scl:AnaChn idx_cfg=\"%1\"/>\r\n").arg(usA);
            dmffile.write(strline.toUtf8());
        }
        for(i=0; i<pBus1->m_arDChanel.count(); i++)
        {
            usA = DMF_GetChanelIDX(pBus1->m_arDChanel[i],pDChanel,nDChanel);
            strline = QString("<scl:StaChn idx_cfg=\"%1\"/>\r\n").arg(usA);
            dmffile.write(strline.toUtf8());
        }

        dmffile.write(QString("</scl:Bus>\r\n").toUtf8());
    }

    //line
    strline = QString("<scl:Line idx=\"1\" line_name=\"%1\" bus_ID=\"1\" srcRef=\"%2\" VRtg=\"%3\" ARtg=\"%4\" ArtgSnd=\"%5\" LinLen=\"%6\" bran_num=\"%7\">\r\n")
            .arg(gbk->toUnicode(a_pLine->m_chName))
            .arg(pLine1->m_strSrcRef)
            .arg(pLine1->m_dVoltage,0,'f',6,QChar('0'))
            .arg(pLine1->m_dMaxI*pLine1->m_dCT,0,'f',6,QChar('0'))
            .arg(pLine1->m_dMaxI,0,'f',6,QChar('0'))
            .arg(pLine1->m_dLength,0,'f',6,QChar('0'))
            .arg(pLine1->m_nBranNum);
    dmffile.write(strline.toUtf8());
    strline = QString("<scl:RX r1=\"%1\" x1=\"%2\" r0=\"%3\" x0=\"%4\"/>\r\n")
            .arg(pLine1->m_dR1,0,'f',6,QChar('0'))
            .arg(pLine1->m_dX1,0,'f',6,QChar('0'))
            .arg(pLine1->m_dR0,0,'f',6,QChar('0'))
            .arg(pLine1->m_dX0,0,'f',6,QChar('0'));
    dmffile.write(strline.toUtf8());

    strline = QString("<scl:CG c1=\"%1\" c0=\"%2\"/>\r\n")
            .arg(pLine1->m_fC1,0,'f',6,QChar('0'))
            .arg(pLine1->m_fC0,0,'f',6,QChar('0'));
    dmffile.write(strline.toUtf8());

    strline = QString("<scl:PX px=\"%1\" px0=\"%2\"/>\r\n")
            .arg(pLine1->m_fPx1,0,'f',6,QChar('0'))
            .arg(pLine1->m_fPx0,0,'f',6,QChar('0'));
    dmffile.write(strline.toUtf8());

    usA = DMF_GetChanelIDX(pLine1->m_wAID,pAChanel,nAChanel);
    usB = DMF_GetChanelIDX(pLine1->m_wBID,pAChanel,nAChanel);
    usC = DMF_GetChanelIDX(pLine1->m_wCID,pAChanel,nAChanel);
    usN = DMF_GetChanelIDX(pLine1->m_wNID,pAChanel,nAChanel);
    strline = QString("<scl:ACC_Bran bran_idx=\"1\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" in_idx=\"%4\" ").arg(usA).arg(usB).arg(usC).arg(usN);
    if(pLine1->m_eDir1 == CEleLine::dir_POS)
        strline += QString("dir=\"POS\"/>\r\n");
    else if(pLine1->m_eDir1 == CEleLine::dir_NEG)
        strline += QString("dir=\"NEG\"/>\r\n");
    else if(pLine1->m_eDir1 == CEleLine::dir_UNC)
        strline += QString("dir=\"UNC\"/>\r\n");
    else
        strline += QString("dir=\"UNC\"/>\r\n");
    dmffile.write(strline.toUtf8());

    if(pLine1->m_nBranNum == 2)
    {
        usA = DMF_GetChanelIDX(pLine1->m_wAID2,pAChanel,nAChanel);
        usB = DMF_GetChanelIDX(pLine1->m_wBID2,pAChanel,nAChanel);
        usC = DMF_GetChanelIDX(pLine1->m_wCID2,pAChanel,nAChanel);
        usN = DMF_GetChanelIDX(pLine1->m_wNID2,pAChanel,nAChanel);
        strline = QString("<scl:ACC_Bran bran_idx=\"2\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" in_idx=\"%4\" ").arg(usA).arg(usB).arg(usC).arg(usN);
        if(pLine1->m_eDir2 == CEleLine::dir_POS)
            strline += QString("dir=\"POS\"/>\r\n");
        else if(pLine1->m_eDir2 == CEleLine::dir_NEG)
            strline += QString("dir=\"NEG\"/>\r\n");
        else if(pLine1->m_eDir2 == CEleLine::dir_UNC)
            strline += QString("dir=\"UNC\"/>\r\n");
        else
            strline += QString("dir=\"UNC\"/>\r\n");
        dmffile.write(strline.toUtf8());
    }

    for(i=0; i<pLine1->m_arAChanel.count(); i++)
    {
        usA = DMF_GetChanelIDX(pLine1->m_arAChanel[i],pAChanel,nAChanel);
        strline = QString("<scl:AnaChn idx_cfg=\"%1\"/>\r\n").arg(usA);
        dmffile.write(strline.toUtf8());
    }
    for(i=0; i<pLine1->m_arDChanel.count(); i++)
    {
        usA = DMF_GetChanelIDX(pLine1->m_arDChanel[i],pDChanel,nDChanel);
        strline = QString("<scl:StaChn idx_cfg=\"%1\"/>\r\n").arg(usA);
        dmffile.write(strline.toUtf8());
    }

    dmffile.write(QString("</scl:Line>\r\n").toUtf8());

    dmffile.write(QString("</scl:ComtradeModel>\r\n").toUtf8());
    dmffile.close();

    ////delete gbk;
    return true;
}

bool CCmtdFile::SaveTransFile(CEleTrans* a_pTrans,const QString& a_strFilePath,bool a_bAct/*=false*/,bool a_bUpperCase/*=false*/)
{
    int pAChanel[128] = {0};
    int pDChanel[512] = {0};
    int pSingle[96] = {0};
    int nAChanel = 0;
    int nDChanel = 0;
    int nBus=0,nLine=0,nSingle=0;
    CEleBus* pBus[64] = {NULL};
    CEleLine* pLine[64] = {NULL};
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QString strr;
    int i = 0,j = 0;
    bool bexist = false;
    if(a_pTrans->m_pLine[0] != NULL)
    {
        if(a_pTrans->m_pLine[0]->m_pBus != NULL)
            pBus[nBus++] = a_pTrans->m_pLine[0]->m_pBus;
        pLine[nLine++] = a_pTrans->m_pLine[0];
    }
    if(a_pTrans->m_pLine[1] != NULL)
    {
        if(a_pTrans->m_pLine[1]->m_pBus != NULL)
        {
            bexist = false;
            for(i=0; i<nBus; i++)
            {
                if(a_pTrans->m_pLine[1]->m_pBus == pBus[i])
                {
                    bexist = true;
                    break;
                }
            }
            if(!bexist)
                pBus[nBus++] = a_pTrans->m_pLine[1]->m_pBus;
        }
        pLine[nLine++] = a_pTrans->m_pLine[1];
    }
    if(a_pTrans->m_pLine[2] != NULL)
    {
        if(a_pTrans->m_pLine[2]->m_pBus != NULL)
        {
            bexist = false;
            for(i=0; i<nBus; i++)
            {
                if(a_pTrans->m_pLine[2]->m_pBus == pBus[i])
                {
                    bexist = true;
                    break;
                }
            }
            if(!bexist)
                pBus[nBus++] = a_pTrans->m_pLine[2]->m_pBus;
        }
        pLine[nLine++] = a_pTrans->m_pLine[2];
    }
    if(a_pTrans->m_pLine[3] != NULL)
    {
        if(a_pTrans->m_pLine[3]->m_pBus != NULL)
        {
            bexist = false;
            for(i=0; i<nBus; i++)
            {
                if(a_pTrans->m_pLine[3]->m_pBus == pBus[i])
                {
                    bexist = true;
                    break;
                }
            }
            if(!bexist)
                pBus[nBus++] = a_pTrans->m_pLine[3]->m_pBus;
        }
        pLine[nLine++] = a_pTrans->m_pLine[3];
    }

    for(i=0; i<nBus; i++)
    {
        if(pBus[i]->m_pAChanel != NULL)
            pAChanel[nAChanel++] = pBus[i]->m_wAID;
        if(pBus[i]->m_pBChanel != NULL)
            pAChanel[nAChanel++] = pBus[i]->m_wBID;
        if(pBus[i]->m_pCChanel != NULL)
            pAChanel[nAChanel++] = pBus[i]->m_wCID;
        if(pBus[i]->m_pNChanel != NULL)
            pAChanel[nAChanel++] = pBus[i]->m_wNID;
    }
    for(i=0; i<nLine; i++)
    {
        if(pLine[i]->m_pAChanel != NULL)
            pAChanel[nAChanel++] = pLine[i]->m_wAID;
        if(pLine[i]->m_pBChanel != NULL)
            pAChanel[nAChanel++] = pLine[i]->m_wBID;
        if(pLine[i]->m_pCChanel != NULL)
            pAChanel[nAChanel++] = pLine[i]->m_wCID;
        if(pLine[i]->m_pNChanel != NULL)
            pAChanel[nAChanel++] = pLine[i]->m_wNID;
        if(pLine[i]->m_sGp1 > 0)
        {
            pAChanel[nAChanel++] = pLine[i]->m_sGp1;
            pSingle[nSingle++] = pLine[i]->m_sGp1;
        }
        if(pLine[i]->m_sGp2 > 0)
        {
            pAChanel[nAChanel++] = pLine[i]->m_sGp2;
            pSingle[nSingle++] = pLine[i]->m_sGp2;
        }
        /*
        if(!a_bAct)
        {
            for(j=0; j<pLine[i]->m_arDChanel.count(); j++)
            {
                pDChanel[nDChanel++] = a_pTrans->m_arDChanel[j];
            }
        }
        */
    }
    for(i=0; i<a_pTrans->m_arAChanel.count(); i++)
    {
        pAChanel[nAChanel++] = a_pTrans->m_arAChanel[i];
    }
    for(i=0; i<a_pTrans->m_arDChanel.count(); i++)
    {
        pDChanel[nDChanel++] = a_pTrans->m_arDChanel[i];
    }

    if(a_bAct)
    {
        nDChanel = 0;
        for(i=0; i<m_nDCount; i++)
        {
            if(m_arDChanel[i]->m_bAct)
            {
                pDChanel[nDChanel] = m_arDChanel[i]->m_wID;
                nDChanel++;
            }
        }
    }

    if(!SaveFileAs(pAChanel,nAChanel,pDChanel,nDChanel,a_strFilePath))
    {
        return false;
    }

    //////////////////////////////////////////////////////////////////////////
    //创建lne文件
    //[[
    m_strTmp = a_strFilePath;
    int np = m_strTmp.lastIndexOf('.');
    if(np > 0)
        m_strTmp = m_strTmp.left(np);
    QString strLP;
    if(a_bUpperCase)
        strLP = m_strTmp+QString(".LNE");
    else
        strLP = m_strTmp+QString(".lne");
    QFile lnefile(strLP);
    if(!lnefile.open(QIODevice::WriteOnly))
    {
        return true;
    }
    //]]

    QString strline;
    strline = QString("国电武仪COMTRADE_HDR文件Ver2.0\n");
    lnefile.write(gbk->fromUnicode(strline));
    strline = QString("%1,%2,%3,1\n").arg(nBus).arg(nLine).arg(nSingle);
    lnefile.write(gbk->fromUnicode(strline));

    int nA=0,nB=0,nC=0,nN=0;
    for(i=0; i<nBus; i++)
    {
        nA=0,nB=0,nC=0,nN=0;
        for(j=0; j<nAChanel; j++)
        {
            if(pAChanel[j] == pBus[i]->m_wAID)
                nA = j+1;
            else if(pAChanel[j] == pBus[i]->m_wBID)
                nB = j+1;
            else if(pAChanel[j] == pBus[i]->m_wCID)
                nC = j+1;
            else if(pAChanel[j] == pBus[i]->m_wNID)
                nN = j+1;
        }
        strline = QString("%1,%2,%3,%4,%5,%6,%7\n").arg(i+1).arg(gbk->toUnicode(pBus[i]->m_chName)).arg(nA).arg(nB).arg(nC).arg(nN)
                .arg(pBus[i]->m_dVoltage,0,'f',2,QChar('0'));
        lnefile.write(gbk->fromUnicode(strline));
    }

    int nGp1=0,nGp2=0;
    for(i=0; i<nLine; i++)
    {
        nA=nB=nC=nN=0;
        nGp1=nGp2=0;
        for(j=0; j<nAChanel; j++)
        {
            if(pAChanel[j] == pLine[i]->m_wAID)
                nA = j+1;
            else if(pAChanel[j] == pLine[i]->m_wBID)
                nB = j+1;
            else if(pAChanel[j] == pLine[i]->m_wCID)
                nC = j+1;
            else if(pAChanel[j] == pLine[i]->m_wNID)
                nN = j+1;
            else if(pAChanel[j] == pLine[i]->m_sGp1)
                nGp1 = j+1;
            else if(pAChanel[j] == pLine[i]->m_sGp2)
                nGp2 = j+1;
        }

        int nbbid = 0;
        for(int n=0; n<nBus; n++)
        {
            if(pLine[i]->m_pBus == pBus[n])
                nbbid = n+1;
        }

        strline = QString("%1,%2,%3,%4,%5,%6,%7,主变,0,%8,%9,%10,%11,0,0.000,0.000,%12,%13,%14,%15,%16\n").arg(i+1)
                .arg(gbk->toUnicode(pLine[i]->m_chName)).arg(nA).arg(nB).arg(nC).arg(nN).arg(nbbid).arg(pLine[i]->m_dR1,0,'f',4,QChar('0')).arg(pLine[i]->m_dX1,0,'f',4,QChar('0')).arg(pLine[i]->m_dR0,0,'f',4,QChar('0'))
                .arg(pLine[i]->m_dX0,0,'f',4,QChar('0')).arg(pLine[i]->m_dMaxI,0,'f',4,QChar('0')).arg(pLine[i]->m_dCT,0,'f',4,QChar('0')).arg(pLine[i]->m_dLength,0,'f',4,QChar('0')).arg(nGp1).arg(nGp2);
        lnefile.write(gbk->fromUnicode(strline));
    }

    int nInd = 0;
    for(i=0; i<nSingle; i++)
    {
        for(j=0; j<m_arDC.count(); j++)
        {
            if(m_arDC[j]->m_pChanel == NULL)
                continue;
            if(m_arDC[j]->m_pChanel->m_wID == pSingle[i])
            {
                for(int n=0; n<nAChanel; n++)
                {
                    if(pAChanel[n] == pSingle[i])
                        nInd = n+1;
                }
                strline = QString("1,%1,%2,%3,%4,%5\n").arg(gbk->toUnicode(m_arDC[i]->m_chName)).arg(nInd).arg(gbk->toUnicode(m_arDC[i]->m_chKind)).arg(gbk->toUnicode(m_arDC[i]->m_chUnit1)).arg(m_arDC[i]->m_dFactor,0,'f',4,QChar('0'));
                lnefile.write(gbk->fromUnicode(strline));
                break;
            }
        }
    }

    strline = QString("1,%1").arg(gbk->toUnicode(a_pTrans->m_chName));
    strr = QString(",0,1,1,0");
    if(a_pTrans->m_pLine[0] != NULL)
    {
        for(i=0; i<nLine; i++)
        {
            if(a_pTrans->m_pLine[0] == pLine[i])
            {
                nInd = i+1;
                break;
            }
        }
        strr = QString(",%1,%2,%3,%4").arg(nInd).arg(a_pTrans->m_nType[0]).arg(a_pTrans->m_dFactor[0],0,'f',4,QChar('0')).arg(a_pTrans->m_bInvert[0]);
    }
    strline += strr;
    strr = ",0,1,1,0";
    if(a_pTrans->m_pLine[1] != NULL)
    {
        for(i=0; i<nLine; i++)
        {
            if(a_pTrans->m_pLine[1] == pLine[i])
                nInd = i+1;
        }
        strr = QString(",%1,%2,%3,%4").arg(nInd).arg(a_pTrans->m_nType[1]).arg(a_pTrans->m_dFactor[1],0,'f',4,QChar('0')).arg(a_pTrans->m_bInvert[1]);
    }
    strline += strr;

    strr = ",0,1,1,0";
    if(a_pTrans->m_pLine[2] != NULL)
    {
        for(i=0; i<nLine; i++)
        {
            if(a_pTrans->m_pLine[2] == pLine[i])
            {
                nInd = i+1;
                break;
            }
        }
        strr = QString(",%1,%2,%3,%4").arg(nInd).arg(a_pTrans->m_nType[2]).arg(a_pTrans->m_dFactor[2],0,'f',4,QChar('0')).arg(a_pTrans->m_bInvert[2]);
    }
    strline += strr;

    strr = ",0,1,1,0";
    if(a_pTrans->m_pLine[3] != NULL)
    {
        for(i=0; i<nLine; i++)
        {
            if(a_pTrans->m_pLine[3] == pLine[i])
            {
                nInd = i+1;
                break;
            }
        }
        strr = QString(",%1,%2,%3,%4").arg(nInd).arg(a_pTrans->m_nType[3]).arg(a_pTrans->m_dFactor[3],0,'f',4,QChar('0')).arg(a_pTrans->m_bInvert[3]);
    }
    strline += strr;
    strline += QString(",%1,%2,%3").arg(a_pTrans->m_dIcd,0,'f',4,QChar('0')).arg(a_pTrans->m_dIsd,0,'f',4,QChar('0')).arg(a_pTrans->m_nKind);
    strline += "\n";
    lnefile.write(gbk->fromUnicode(strline));

    strline = QString("%1").arg(nDChanel);
    for(i=1; i<nLine; i++)
    {
        strline += QString(",0");
    }
    strline += "\n";
    lnefile.write(gbk->fromUnicode(strline));
    strline = "1";
//	CString strr;
    CEleDChanel* pDCH = NULL;
//    int nId = 0;
    for(i=0; i<nDChanel; i++)
    {
        pDCH = GetDChanelById(pDChanel[i]);
        // 		for(int j=0; j<nDChanel; j++)
        // 		{
        // 			if(a_pLine->m_pSwitch[i] == pDChanel[j])
        // 			{
        // 				nId = j+1;
        // 				break;
        // 			}
        //		}
        if(pDCH != NULL)
        {
//            strr = QString(",%1:0").arg(i+1).arg(pDCH->m_wKind);
            if(pDCH->m_strFlag == QString("TrPhsA"))
                strr = QString(",%d:21").arg(i+1);
            else if(pDCH->m_strFlag == QString("TrPhsB"))
                strr = QString(",%d:22").arg(i+1);
            else if(pDCH->m_strFlag == QString("TrPhsC"))
                strr = QString(",%d:23").arg(i+1);
            else if(pDCH->m_strFlag == QString("OpTP"))
                strr = QString(",%d:24").arg(i+1);
            else if(pDCH->m_strFlag == QString("RecOpCls"))
                strr = QString(",%d:25").arg(i+1);
            else
                strr = QString(",%1:0").arg(i+1);
        }
        else
        {
            strr = QString(",%1:0").arg(i+1);
        }
        strline += strr;
    }
    strline += "\n";
    lnefile.write(gbk->fromUnicode(strline));
    for(i=1; i<nLine; i++)
    {
        strline = QString("%1,\n").arg(i+1);
        lnefile.write(gbk->fromUnicode(strline));
    }
    lnefile.write(gbk->fromUnicode(m_strAttach));

    lnefile.close();
    //]]

    //////////////////////////////////////////////////////////////////////////////////
    //DMF文件
    //[[
    m_strTmp = a_strFilePath;
    np = m_strTmp.lastIndexOf('.');
    if(np > 0)
        m_strTmp = m_strTmp.left(np);
    QString strMP;
    if(a_bUpperCase)
        strMP = m_strTmp+QString(".DMF");
    else
        strMP = m_strTmp+QString(".dmf");
    QFile dmffile(strMP);
    dmffile.remove();
    if(!dmffile.open(QIODevice::WriteOnly))
    {
        return false;
    }

    strline = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
    dmffile.write(strline.toUtf8());
    strline = QString("<scl:ComtradeModel station_name=\"%1\" version=\"%2\" reference=\"%3\" rec_dev_name=\"%4\"  rec_ref=\"%5\" xsi:schemaLocation=\"http://www.iec.ch/61850/2003/SCLcomtrade_mdl_v1.1.xsd\" xmlns:scl=\"http://www.iec.ch/61850/2003/SCL\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\r\n")
            .arg(m_strStationName).arg(m_strVersion).arg(m_strReference).arg(m_strRecDevName).arg(m_strRecRef);
    dmffile.write(strline.toUtf8());

    for(int i=0; i<nAChanel; i++)
    {
        strline = QString("<scl:AnalogChannel idx_cfg=\"%1\" idx_org=\"%2\" ").arg(i+1).arg(pAChanel[i]);
        CEleAChanel* pChanel = GetAChanelById(pAChanel[i]);
        if(pChanel != NULL)
        {
            if(pChanel->m_eType == CEleAChanel::type_A)
                strline += QString("type=\"A\" ");
            else if(pChanel->m_eType == CEleAChanel::type_D)
                strline += QString("type=\"D\" ");
            else if(pChanel->m_eType == CEleAChanel::type_O)
                strline += QString("type=\"O\" ");
            else
                strline += QString("type=\"A\" ");

            if(pChanel->m_eFlag == CEleAChanel::flag_ACV)
                strline += QString("flag=\"ACV\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_ACC)
                strline += QString("flag=\"ACC\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_HF)
                strline += QString("flag=\"HF\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_FQ)
                strline += QString("flag=\"FQ\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_AG)
                strline += QString("flag=\"AG\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_AMP)
                strline += QString("flag=\"AMP\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_PW)
                strline += QString("flag=\"PW\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_ZX)
                strline += QString("flag=\"ZX\" ");
            else if(pChanel->m_eFlag == CEleAChanel::flag_CONST)
                strline += QString("flag=\"CONST\" ");

            strline += QString("freq=\"%1\" au=\"%2\" bu=\"%3\" ")
                    .arg(pChanel->m_fFreq,0,'f',1,QChar('0')).arg(pChanel->m_fAU,0,'f',6,QChar('0')).arg(pChanel->m_fBU,0,'f',6,QChar('0'));
            if(pChanel->m_eSiUnit == CEleAChanel::unit_A)
                strline += QString("sIUnit=\"A\" multiplier=\"\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_V)
                strline += QString("sIUnit=\"V\" multiplier=\"\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_Hz)
                strline += QString("sIUnit=\"Hz\" multiplier=\"\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_O)
                strline += QString("sIUnit=\"Ω\" multiplier=\"\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_W)
                strline += QString("sIUnit=\"W\" multiplier=\"\" ");
            else if(pChanel->m_eSiUnit == CEleAChanel::unit_Var)
                strline += QString("sIUnit=\"Var\" multiplier=\"\" ");
            else
                strline += QString("sIUnit=\"\" multiplier=\"\" ");

            strline += QString("primary=\"%1\" secondary=\"%2\" ")
                    .arg(pChanel->m_fPrimary,0,'f',6,QChar('0'))
                    .arg(pChanel->m_fSecondary,0,'f',6,QChar('0'));

            if(pChanel->m_ePS == CEleAChanel::ps_P)
                strline += QString("ps=\"P\"/>\r\n");
            else if(pChanel->m_ePS == CEleAChanel::ps_S)
                strline += QString("ps=\"S\"/>\r\n");
            else
                strline += QString("ps=\"S\"/>\r\n");
        }
        else
            strline += QString("type=\"A\" flag=\"ACV\" freq=\"50.0\" au=\"1.000000\" bu=\"0.000000\" sIUnit=\"V\" multiplier=\"\" primary=\"2500.000\" secondary=\"1.000\" ps=\"S\"/>\r\n");
        dmffile.write(strline.toUtf8());
    }

    //DChanel
    for(int i=0; i<nDChanel; i++)
    {
        strline = QString("<scl:StatusChannel idx_cfg=\"%1\" idx_org=\"%2\" ").arg(i+1).arg(i+1);
        CEleDChanel* pChanel = GetDChanelById(pDChanel[i]);
        if(pChanel != NULL)
        {
            if(pChanel->m_eType == CEleDChanel::Relay)
                strline += QString("type=\"Relay\" ");
            else if(pChanel->m_eType == CEleDChanel::Breaker)
                strline += QString("type=\"Breaker\" ");
            else if(pChanel->m_eType == CEleDChanel::Switch)
                strline += QString("type=\"Switch\" ");
            else if(pChanel->m_eType == CEleDChanel::Warning)
                strline += QString("type=\"Warning\" ");
            else if(pChanel->m_eType == CEleDChanel::Other)
                strline += QString("type=\"Other\" ");
            strline += QString("flag=\"%1\" ").arg(pChanel->m_strFlag);
            if(pChanel->m_eContact == CEleDChanel::NormallyOpen)
                strline += QString("contact=\"NormallyOpen\" ");
            else if(pChanel->m_eContact == CEleDChanel::NormallyClosed)
                strline += QString("contact=\"NormallyClosed\" ");
            else
                strline += QString("contact=\"NormallyOpen\" ");
            strline += QString("srcRef=\"%1\"/>\r\n").arg(pChanel->m_strSrcRef);
        }
        else
            strline += QString("type=\"Other\" flag=\"general\" contact=\"NormallyOpen\" srcRef=\"\"/>\r\n");
        dmffile.write(strline.toUtf8());
    }

    //变压器
    unsigned short usA=0,usB=0,usC=0;
    strline = QString("<scl:Transformer idx=\"1\" trm_name=\"%1\" srcRef=\"%2\" pwrRtg=\"%3\">\r\n")
            .arg(gbk->toUnicode(a_pTrans->m_chName))
            .arg(a_pTrans->m_strSrcRef)
            .arg(a_pTrans->m_fPwrRtg,0,'f',3,QChar('0'));
    dmffile.write(strline.toUtf8());
    if(a_pTrans->m_pLine[0] != NULL)
    {
        strline = QString("<scl:TransformerWinding location=\"High\" VRtg=\"%1\" ARtg=\"%2\" bran_num=\"1\" wG=\"%3\">\r\n")
                .arg(a_pTrans->m_pLine[0]->m_dVoltage)
                .arg(a_pTrans->m_pLine[0]->m_dMaxI*a_pTrans->m_pLine[0]->m_dCT)
                .arg(DMF_GetTranswGDesc(a_pTrans->m_nType[0]));
        dmffile.write(strline.toUtf8());
        if(a_pTrans->m_pLine[0]->m_pBus != NULL)
        {
            usA = DMF_GetChanelIDX(a_pTrans->m_pLine[0]->m_pBus->m_wAID,pAChanel,nAChanel);
            usB = DMF_GetChanelIDX(a_pTrans->m_pLine[0]->m_pBus->m_wBID,pAChanel,nAChanel);
            usC = DMF_GetChanelIDX(a_pTrans->m_pLine[0]->m_pBus->m_wCID,pAChanel,nAChanel);
            dmffile.write(QString("<scl:ACVChn ua_idx=\"%1\" ub_idx=\"%2\" uc_idx=\"%3\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());
        }
        usA = DMF_GetChanelIDX(a_pTrans->m_pLine[0]->m_wAID,pAChanel,nAChanel);
        usB = DMF_GetChanelIDX(a_pTrans->m_pLine[0]->m_wBID,pAChanel,nAChanel);
        usC = DMF_GetChanelIDX(a_pTrans->m_pLine[0]->m_wCID,pAChanel,nAChanel);
        if(a_pTrans->m_bInvert[0])
            dmffile.write(QString("<scl:ACC_Bran bran_idx=\"1\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" dir=\"POS\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());
        else
            dmffile.write(QString("<scl:ACC_Bran bran_idx=\"1\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" dir=\"NEG\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());

        dmffile.write(QString("</scl:TransformerWinding>\r\n").toUtf8());
    }

    if(a_pTrans->m_pLine[1] != NULL)
    {
        strline = QString("<scl:TransformerWinding location=\"Medium\" VRtg=\"%1\" ARtg=\"%2\" bran_num=\"1\" wG=\"%3\">\r\n")
                .arg(a_pTrans->m_pLine[1]->m_dVoltage)
                .arg(a_pTrans->m_pLine[1]->m_dMaxI*a_pTrans->m_pLine[1]->m_dCT)
                .arg(DMF_GetTranswGDesc(a_pTrans->m_nType[1]));
        dmffile.write(strline.toUtf8());
        if(a_pTrans->m_pLine[1]->m_pBus != NULL)
        {
            usA = DMF_GetChanelIDX(a_pTrans->m_pLine[1]->m_pBus->m_wAID,pAChanel,nAChanel);
            usB = DMF_GetChanelIDX(a_pTrans->m_pLine[1]->m_pBus->m_wBID,pAChanel,nAChanel);
            usC = DMF_GetChanelIDX(a_pTrans->m_pLine[1]->m_pBus->m_wCID,pAChanel,nAChanel);
            dmffile.write(QString("<scl:ACVChn ua_idx=\"%1\" ub_idx=\"%2\" uc_idx=\"%3\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());
        }
        usA = DMF_GetChanelIDX(a_pTrans->m_pLine[1]->m_wAID,pAChanel,nAChanel);
        usB = DMF_GetChanelIDX(a_pTrans->m_pLine[1]->m_wBID,pAChanel,nAChanel);
        usC = DMF_GetChanelIDX(a_pTrans->m_pLine[1]->m_wCID,pAChanel,nAChanel);
        if(a_pTrans->m_bInvert[1])
            dmffile.write(QString("<scl:ACC_Bran bran_idx=\"1\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" dir=\"POS\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());
        else
            dmffile.write(QString("<scl:ACC_Bran bran_idx=\"1\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" dir=\"NEG\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());

        dmffile.write(QString("</scl:TransformerWinding>\r\n").toUtf8());
    }

    if(a_pTrans->m_pLine[2] != NULL)
    {
        if(a_pTrans->m_pLine[3] != NULL)
        {
            strline = QString("<scl:TransformerWinding location=\"Low\" VRtg=\"%1\" ARtg=\"%2\" bran_num=\"2\" wG=\"%3\">\r\n")
                    .arg(a_pTrans->m_pLine[2]->m_dVoltage)
                    .arg(a_pTrans->m_pLine[2]->m_dMaxI*a_pTrans->m_pLine[2]->m_dCT)
                    .arg(DMF_GetTranswGDesc(a_pTrans->m_nType[2]));
        }
        else
        {
            strline = QString("<scl:TransformerWinding location=\"Low\" VRtg=\"%1\" ARtg=\"%2\" bran_num=\"1\" wG=\"%3\">\r\n")
                    .arg(a_pTrans->m_pLine[2]->m_dVoltage)
                    .arg(a_pTrans->m_pLine[2]->m_dMaxI*a_pTrans->m_pLine[2]->m_dCT)
                    .arg(DMF_GetTranswGDesc(a_pTrans->m_nType[2]));
        }
        dmffile.write(strline.toUtf8());

        if(a_pTrans->m_pLine[2]->m_pBus != NULL)
        {
            usA = DMF_GetChanelIDX(a_pTrans->m_pLine[2]->m_pBus->m_wAID,pAChanel,nAChanel);
            usB = DMF_GetChanelIDX(a_pTrans->m_pLine[2]->m_pBus->m_wBID,pAChanel,nAChanel);
            usC = DMF_GetChanelIDX(a_pTrans->m_pLine[2]->m_pBus->m_wCID,pAChanel,nAChanel);
            dmffile.write(QString("<scl:ACVChn ua_idx=\"%1\" ub_idx=\"%2\" uc_idx=\"%3\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());
        }
        usA = DMF_GetChanelIDX(a_pTrans->m_pLine[2]->m_wAID,pAChanel,nAChanel);
        usB = DMF_GetChanelIDX(a_pTrans->m_pLine[2]->m_wBID,pAChanel,nAChanel);
        usC = DMF_GetChanelIDX(a_pTrans->m_pLine[2]->m_wCID,pAChanel,nAChanel);
        if(a_pTrans->m_bInvert[2])
            dmffile.write(QString("<scl:ACC_Bran bran_idx=\"1\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" dir=\"POS\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());
        else
            dmffile.write(QString("<scl:ACC_Bran bran_idx=\"1\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" dir=\"NEG\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());

        if(a_pTrans->m_pLine[3] != NULL)
        {
            usA = DMF_GetChanelIDX(a_pTrans->m_pLine[3]->m_wAID,pAChanel,nAChanel);
            usB = DMF_GetChanelIDX(a_pTrans->m_pLine[3]->m_wBID,pAChanel,nAChanel);
            usC = DMF_GetChanelIDX(a_pTrans->m_pLine[3]->m_wCID,pAChanel,nAChanel);
            if(a_pTrans->m_bInvert[3])
                dmffile.write(QString("<scl:ACC_Bran bran_idx=\"2\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" dir=\"POS\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());
            else
                dmffile.write(QString("<scl:ACC_Bran bran_idx=\"2\" ia_idx=\"%1\" ib_idx=\"%2\" ic_idx=\"%3\" dir=\"NEG\"/>\r\n").arg(usA).arg(usB).arg(usC).toUtf8());
        }
        dmffile.write(QString("</scl:TransformerWinding>\r\n").toUtf8());
    }

    for(int i=0; i<a_pTrans->m_arAChanel.count(); i++)
    {
        usA = DMF_GetChanelIDX(a_pTrans->m_arAChanel[i],pAChanel,nAChanel);
        dmffile.write(QString("<scl:AnaChn idx_cfg=\"%1\" />\r\n").arg(usA).toUtf8());
    }
    for(int i=0; i<a_pTrans->m_arDChanel.count(); i++)
    {
        usA = DMF_GetChanelIDX(a_pTrans->m_arDChanel[i],pDChanel,nDChanel);
        dmffile.write(QString("<scl:StaChn idx_cfg=\"%1\" />\r\n").arg(usA).toUtf8());
    }

    dmffile.write(QString("<scl:Igap zsgap_idx=\"0\" zgap_idx=\"0\" />\r\n").toUtf8());
    dmffile.write(QString("</scl:Transformer>\r\n").toUtf8());
    dmffile.write(QString("</scl:ComtradeModel>\r\n").toUtf8());

    //]]
    dmffile.close();
    ////delete gbk;
    return true;
}

QString CCmtdFile::ParamTimes(double nTime,int nDigit/*=6*/)
{
    QDateTime tmf = m_tmStart;
    int64_t ntl = m_strTimeFinalpart.toInt()+(int64_t)nTime;
// 	CTime tmf = m_tmLeft;
// 	int ntl = atoi(m_strTimeFinalpartL)+nTime;
    if(ntl < 0)
    {
        tmf = tmf.addSecs(-(ntl/1000000+1));
        ntl += (ntl/1000000+1)*1000000;
    }
    else
    {
        tmf = tmf.addSecs(ntl/1000000);	//秒的部分
        ntl %= 1000000;
    }

    if((m_nleap_command !=0)&&(m_nleap_ltime != 0))
    {
        uint ltm = tmf.toTime_t();
        struct tm* ptm = LeapTime(ltm);
        QString strf = QString("%1-%2-%3 %4:%5:%6.%7").arg(ptm->tm_year+1900)
                .arg(ptm->tm_mon+1,4,10,QChar('0'))
                .arg(ptm->tm_mday,4,10,QChar('0'))
                .arg(ptm->tm_hour,2,10,QChar('0'))
                .arg(ptm->tm_min,2,10,QChar('0'))
                .arg(ptm->tm_sec,2,10,QChar('0'))
                .arg(ntl,nDigit,10,QChar('0'));
        return strf;
    }
    else
    {
        QString strf = tmf.toString(QString("yyyy-MM-dd hh:mm:ss"));
        strf += QString(".%1").arg(ntl,nDigit,10,QChar('0'));
        return strf;
    }
}

QString CCmtdFile::SGParamTimes(int nTime)
{
    QDateTime tmf = m_tmStart;
    int ntl = m_strTimeFinalpart.toInt()+nTime;
// 	CTime tmf = m_tmLeft;
// 	int ntl = atoi(m_strTimeFinalpartL)+nTime;
    if(ntl < 0)
    {
        tmf = tmf.addSecs(-(ntl/1000000+1));
        ntl += (ntl/1000000+1)*1000000;
    }
    else
    {
        tmf = tmf.addSecs(ntl/1000000);	//秒的部分
        ntl %= 1000000;
    }

    if((m_nleap_command !=0)&&(m_nleap_ltime != 0))
    {
        uint ltm = tmf.toTime_t();
        struct tm* ptm = LeapTime(ltm);
        QString strf = QString("%1-%2-%3 %4:%5:%6:%7").arg(ptm->tm_year+1900)
                .arg(ptm->tm_mon+1,4,10,QChar('0'))
                .arg(ptm->tm_mday,4,10,QChar('0'))
                .arg(ptm->tm_hour,2,10,QChar('0'))
                .arg(ptm->tm_min,2,10,QChar('0'))
                .arg(ptm->tm_sec,2,10,QChar('0'))
                .arg(ntl/1000,3,10,QChar('0'));
        return strf;
    }
    else
    {
        QString strf = tmf.toString(QString("yyyy-MM-dd hh:mm:ss"));
        strf += QString(":%1").arg(ntl/1000,3,10,QChar('0'));
        return strf;
    }
}

struct tm* CCmtdFile::LeapTime(uint ltime)
{
    tm * tmleap,*stutime;

    stutime=NULL;
    uint nleapltime = m_nleap_ltime;
    tmleap=localtime((long*)&nleapltime);
    if(tmleap!=NULL)
    {	tmleap->tm_sec=0;	//从闰秒前一整分计算 修正
        nleapltime=mktime(tmleap);

        if(m_nleap_command==0x80)	//正润秒
        {
            nleapltime+=60;

            if(ltime==nleapltime)
            {	ltime--;
                stutime=localtime((long*)&ltime);
                if(stutime!=NULL)
                    stutime->tm_sec=60;
            }
            else if(ltime>nleapltime)
            {	ltime--;
                stutime=localtime((long*)&ltime);
            }
            else
            {	stutime=localtime((long*)&ltime);
            }
        }
        else if(m_nleap_command==0x88)	//负润秒
        {	nleapltime+=59;
            if(ltime>=nleapltime)
            {	ltime++;
            }
            stutime=localtime((long*)&ltime);
        }
        else
        {
            stutime=localtime((long*)&ltime);
        }
    }
    else
    {
        stutime=localtime((long*)&ltime);
    }

    return stutime;
}

void CCmtdFile::GeneratePTCT()
{
    int i = 0;
    for(i=0; i<m_arBus.count(); i++)
    {
        CEleBus* pBus = m_arBus[i];
        if(pBus->m_pAChanel != NULL)
            pBus->m_pAChanel->m_dPT = pBus->m_dVoltage;
        if(pBus->m_pBChanel != NULL)
            pBus->m_pBChanel->m_dPT = pBus->m_dVoltage;
        if(pBus->m_pCChanel != NULL)
            pBus->m_pCChanel->m_dPT = pBus->m_dVoltage;
        if(pBus->m_pNChanel != NULL)
            pBus->m_pNChanel->m_dPT = pBus->m_dVoltage;
    }
    for(i=0; i<m_arLine.count(); i++)
    {
        CEleLine* pLine = m_arLine[i];
        if(pLine->m_pAChanel != NULL)
            pLine->m_pAChanel->m_dCT = pLine->m_dCT;
        if(pLine->m_pBChanel != NULL)
            pLine->m_pBChanel->m_dCT = pLine->m_dCT;
        if(pLine->m_pCChanel != NULL)
            pLine->m_pCChanel->m_dCT = pLine->m_dCT;
        if(pLine->m_pNChanel != NULL)
            pLine->m_pNChanel->m_dCT = pLine->m_dCT;
    }
}

unsigned short CCmtdFile::DMF_GetChanelIDX(unsigned short usChnID, int *pAChanel,int nACount)
{
    unsigned short usIdx = 0;
    for(int i=0; i<nACount; i++)
    {
        if(usChnID == pAChanel[i])
        {
            usIdx = i+1;
            break;
        }
    }
    return usIdx;
}

QString CCmtdFile::DMF_GetTranswGDesc(int nType)
{
    if(nType == 1)
        return QString("y0");
    else if(nType == 2)
        return QString("D11");
    else if(nType == 3)
        return QString("D1");
    else
        return QString("yn0");
}

CEleBus* CCmtdFile::GetBus(CEleTrans* pTrans,CEleTransWiding* pWiding)
{
    uint wAID = pWiding->m_wUaIdx;
    uint wBID = pWiding->m_wUbIdx;
    uint wCID = pWiding->m_wUcIdx;
    int i = 0;
    if((wAID<=0)||(wBID<=0)||(wCID<=0))
    {
        return NULL;
    }
    if((wAID>(uint)m_nACount)||(wBID>(uint)m_nACount)||(wCID>(uint)m_nACount))
    {
        return NULL;
    }

    for(i=0; i<m_arBus.count(); i++)
    {
        CEleBus* pBus = m_arBus.at(i);
        if(pBus->m_wAID != wAID)
            continue;
        if(pBus->m_wBID != wBID)
            continue;
        if(pBus->m_wCID != wCID)
            continue;
        return pBus;
    }

    //没找到，根据ID创建
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    CEleBus* pBus = new CEleBus();
    strcpy(pBus->m_chName,pTrans->m_chName);
    if(pWiding->m_eLocation == CEleTransWiding::High)
        strcat(pBus->m_chName,gbk->fromUnicode(QString("高压侧电压")));
    else if(pWiding->m_eLocation == CEleTransWiding::Medium)
        strcat(pBus->m_chName,gbk->fromUnicode(QString("中压侧电压")));
    else if(pWiding->m_eLocation == CEleTransWiding::Low)
        strcat(pBus->m_chName,gbk->fromUnicode(QString("低压侧电压")));

    pBus->m_wAID = wAID;
    pBus->m_wBID = wBID;
    pBus->m_wCID = wCID;
    pBus->m_fVrtg = pWiding->m_fVRtg;

    pBus->m_pAChanel = GetAChanelById(wAID);
    pBus->m_pBChanel = GetAChanelById(wBID);
    pBus->m_pCChanel = GetAChanelById(wCID);
    pBus->m_wID = m_arBus.count()+1;
    m_arBus.append(pBus);
    ////delete gbk;

    return pBus;
}

CEleLine* CCmtdFile::GetLine(CEleTrans* pTrans,CEleTransWiding* pWiding,uint wAID, uint wBID, uint wCID)
{
    int i = 0;
    if((wAID<=0)||(wBID<=0)||(wCID<=0))
    {
        return NULL;
    }
    if((wAID>(uint)m_nACount)||(wBID>(uint)m_nACount)||(wCID>(uint)m_nACount))
    {
        return NULL;
    }

    for(i=0; i<m_arLine.count(); i++)
    {
        if(m_arLine[i]->m_wAID != wAID)
            continue;
        if(m_arLine[i]->m_wBID != wBID)
            continue;
        if(m_arLine[i]->m_wCID != wCID)
            continue;
        return m_arLine.at(i);
    }

    //没找到，根据ID创建
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    CEleLine* pLine = new CEleLine();
    strcpy(pLine->m_chName,pTrans->m_chName);
    if(pWiding->m_eLocation == CEleTransWiding::High)
        strcat(pLine->m_chName,gbk->fromUnicode(QString("高压侧电流")));
    else if(pWiding->m_eLocation == CEleTransWiding::Medium)
        strcat(pLine->m_chName,gbk->fromUnicode(QString("中压侧电流")));
    else if(pWiding->m_eLocation == CEleTransWiding::Low)
        strcat(pLine->m_chName,gbk->fromUnicode(QString("低压侧电流")));

    pLine->m_pBus = GetBus(pTrans,pWiding);
    if(pLine->m_pBus != NULL)
    {
        pLine->m_wBusId = pLine->m_pBus->m_wID;
    }

    pLine->m_wID = m_arLine.count()+1;
    pLine->m_wAID = wAID;
    pLine->m_wBID = wBID;
    pLine->m_wCID = wCID;
    pLine->m_dVoltage = pWiding->m_fVRtg;
    pLine->m_fArtg = pWiding->m_fARtg;
    pLine->m_dCT = pLine->m_fArtg;

    pLine->m_pAChanel = GetAChanelById(wAID);
    pLine->m_pBChanel = GetAChanelById(wBID);
    pLine->m_pCChanel = GetAChanelById(wCID);
    m_arLine.append(pLine);
    ////delete gbk;

    return pLine;
}

void CCmtdFile::GenerateTransInfo()
{
    int i = 0;
    int j = 0;
    int n = 0;
    for(i=0; i<m_arTrans.count(); i++)
    {
        for(j=0; j<CEleTrans::MAX_BRA_COUNT; j++)
        {
            if(m_arTrans[i]->m_pLine[j] != NULL)
            {
                for(n=0; n<m_arLine.count(); n++)
                {
                    if(m_arTrans[i]->m_pLine[j] == m_arLine[n])
                    {
                        m_arTrans[i]->m_wBraID[j] = n+1;
                        break;
                    }
                }
            }
        }
    }

    //2018-11-15修改，支持4分支(可在高中低任一侧分支)
    //[[
    CEleTrans* pTrans = NULL;
    CEleTransWiding* pWiding = NULL;
    float fFactorHigh = 220;
    for(i=0; i<m_arTrans.count(); i++)
    {
        pTrans = m_arTrans.at(i);
        pTrans->m_nLineCount = 0;
        int nLnd = 0;
        for(j=0; j<pTrans->m_arWiding.count(); j++)
        {
            pWiding = pTrans->m_arWiding.at(j);
            if(pWiding->m_arIaIdx.count() <= 0)
            {
                continue;
            }
            for(n=0; n<pWiding->m_arIaIdx.count(); n++)
            {
                pTrans->m_pLine[nLnd] = GetLine(pTrans,pWiding,pWiding->m_arIaIdx[n],pWiding->m_arIbIdx[n],pWiding->m_arIcIdx[n]);
                if(pTrans->m_pLine[nLnd] != NULL)
                {
                    if((pWiding->m_eWGA == CEleTransWiding::wG_Y)||(pWiding->m_eWGA == CEleTransWiding::wG_YN))
                        pTrans->m_nType[nLnd] = 1;
                    else if(pWiding->m_eWGA == CEleTransWiding::wG_D)
                    {
                        if(pWiding->m_nWGB == 11)
                            pTrans->m_nType[nLnd] = 2;
                        else if(pWiding->m_nWGB == 1)
                            pTrans->m_nType[nLnd] = 3;
                    }

                    //高压侧第一分支，计算高压侧系数
                    if(pWiding->m_eLocation == CEleTransWiding::High)
                    {
                        if(n == 0)
                        {
                            fFactorHigh = pWiding->m_fVRtg*pTrans->m_pLine[nLnd]->m_dCT;
                        }
                    }

                    pTrans->m_dFactor[nLnd] = (pWiding->m_fVRtg*pTrans->m_pLine[nLnd]->m_dCT)/fFactorHigh;
                    if(pWiding->m_arDir[n] == CEleTransWiding::dir_NEG)
                        pTrans->m_bInvert[nLnd] = 1;
                    else
                        pTrans->m_bInvert[nLnd] = 0;

                    nLnd++;
                    if(nLnd > 3)
                    {
                        break;
                    }
                }
            }
        }
        pTrans->m_nLineCount = nLnd;
    }
    //]]

    /*
    //过渡期解决办法(完全依赖DMF文件时删除此段代码)
    //[[
    CEleTrans* pTrans = NULL;
    CEleTransWiding* pWiding = NULL;
    float fFactorHigh = 220;
    for(i=0; i<m_arTrans.count(); i++)
    {
        pTrans = m_arTrans.at(i);
        pTrans->m_nLineCount = pTrans->m_arWiding.count();
        for(j=0; j<pTrans->m_arWiding.count(); j++)
        {
            pWiding = pTrans->m_arWiding.at(j);
            if(pWiding->m_arIaIdx.count() > 0)
            {
                if(pWiding->m_eLocation == CEleTransWiding::High)
                {
                    pTrans->m_pLine[0] = GetLine(pTrans,pWiding,pWiding->m_arIaIdx[0],pWiding->m_arIbIdx[0],pWiding->m_arIcIdx[0]);
                    if(pTrans->m_pLine[0] != NULL)
                    {
                        if((pWiding->m_eWGA == CEleTransWiding::wG_Y)||(pWiding->m_eWGA == CEleTransWiding::wG_YN))
                            pTrans->m_nType[0] = 1;
                        else if(pWiding->m_eWGA == CEleTransWiding::wG_D)
                        {
                            if(pWiding->m_nWGB == 11)
                                pTrans->m_nType[0] = 2;
                            else if(pWiding->m_nWGB == 1)
                                pTrans->m_nType[0] = 3;
                        }
                        pTrans->m_dFactor[0] = 1;
                        fFactorHigh = pWiding->m_fVRtg*pTrans->m_pLine[0]->m_dCT;
                        if(pWiding->m_arDir[0] == CEleTransWiding::dir_NEG)
                            pTrans->m_bInvert[0] = 1;
                        else
                            pTrans->m_bInvert[0] = 0;

                    }
                    else
                    {
                        fFactorHigh = pWiding->m_fVRtg*pWiding->m_fARtg;
                    }
                }
                else if(pWiding->m_eLocation == CEleTransWiding::Medium)
                {
                    pTrans->m_pLine[1] = GetLine(pTrans,pWiding,pWiding->m_arIaIdx[0],pWiding->m_arIbIdx[0],pWiding->m_arIcIdx[0]);
                    if(pTrans->m_pLine[1] != NULL)
                    {
                        if((pWiding->m_eWGA == CEleTransWiding::wG_Y)||(pWiding->m_eWGA == CEleTransWiding::wG_YN))
                            pTrans->m_nType[1] = 1;
                        else if(pWiding->m_eWGA == CEleTransWiding::wG_D)
                        {
                            if(pWiding->m_nWGB == 11)
                                pTrans->m_nType[1] = 2;
                            else if(pWiding->m_nWGB == 1)
                                pTrans->m_nType[1] = 3;
                        }
                        pTrans->m_dFactor[1] = (pWiding->m_fVRtg*pTrans->m_pLine[1]->m_dCT)/fFactorHigh;
                        if(pWiding->m_arDir[0] == CEleTransWiding::dir_NEG)
                            pTrans->m_bInvert[1] = 1;
                        else
                            pTrans->m_bInvert[1] = 0;
                    }
                    else
                    {
                        pTrans->m_dFactor[1] = (pWiding->m_fVRtg*pWiding->m_fARtg)/fFactorHigh;
                    }
                }
                else if(pWiding->m_eLocation == CEleTransWiding::Low)
                {
                    int nLND = 2;
                    if(pTrans->m_pLine[1] == NULL)
                    {
                        nLND = 1;
                    }

                    pTrans->m_pLine[nLND] = GetLine(pTrans,pWiding,pWiding->m_arIaIdx[0],pWiding->m_arIbIdx[0],pWiding->m_arIcIdx[0]);
                    if(pTrans->m_pLine[nLND] != NULL)
                    {
                        if((pWiding->m_eWGA == CEleTransWiding::wG_Y)||(pWiding->m_eWGA == CEleTransWiding::wG_YN))
                            pTrans->m_nType[nLND] = 1;
                        else if(pWiding->m_eWGA == CEleTransWiding::wG_D)
                        {
                            if(pWiding->m_nWGB == 11)
                                pTrans->m_nType[nLND] = 2;
                            else if(pWiding->m_nWGB == 1)
                                pTrans->m_nType[nLND] = 3;
                        }
                        pTrans->m_dFactor[nLND] = (pWiding->m_fVRtg*pTrans->m_pLine[nLND]->m_dCT)/fFactorHigh;
                        if(pWiding->m_arDir[0] == CEleTransWiding::dir_NEG)
                            pTrans->m_bInvert[nLND] = 1;
                        else
                            pTrans->m_bInvert[nLND] = 0;
                    }
                    else
                    {
                        pTrans->m_dFactor[nLND] = (pWiding->m_fVRtg*pWiding->m_fARtg)/fFactorHigh;
                    }
                }
            }
        }
    }
    //]]
    */
}

bool CCmtdFile::IsUpperCase()
{
    if(m_bUpperCase)
        return true;
    return false;
}

bool CCmtdFile::ReadPrvFile()
{
    QFile prvFile(m_strPrvFilePath);
    if(!prvFile.open(QIODevice::ReadOnly))
    {
        return false;
    }
    char *chfile = new char[2048];
    memset(chfile,0,2048);
    int size = prvFile.size();
    if(prvFile.read(chfile,size) != size)
    {
        qDebug("prv file size error!");
    }
    prvFile.close();

    const int szprv = 384;
    int ndd = 0;
    memcpy(&ndd,chfile,4);
    if(ndd == 1)  //有效
    {
        memcpy((char*)(m_usPhaseParam),chfile+4,szprv);
    }
    memcpy((char*)(&m_nleap_ltime),chfile+4+szprv,4);
    memcpy((char*)(&m_nleap_command),chfile+4+szprv+4,4);

    return true;
}

double CCmtdFile::GetChanelParam(int n)
{
    if(n>256)
        return 0;
    double fParam = m_usPhaseParam[n]*2*3.1415926/20000;
    return fParam;
}

void CCmtdFile::ParamPhase(unsigned short usID, float &fPhase)
{
    double dval = GetChanelParam(usID-1);
    fPhase += dval;
}

void CCmtdFile::RemoveBus(int nInd)
{
    int i = 0;
    if((nInd<0)||(nInd>=m_arBus.count()))
    {
        return;
    }
    CEleBus* pBus = m_arBus.at(nInd);
    for(i=nInd+1; i<m_arBus.count(); i++)
    {
        m_arBus[i]->m_wID -= 1;
    }
    for(i=0; i<m_arLine.count(); i++)
    {
        if(m_arLine[i]->m_wBusId == nInd+1)
            m_arLine[i]->m_wBusId = 0;
        else if(m_arLine[i]->m_wBusId > nInd+1)
            m_arLine[i]->m_wBusId -= 1;
    }
    m_arBus.remove(nInd);
    delete pBus;
}

void CCmtdFile::RemoveLine(int nInd)
{
    int i = 0;
    if((nInd<0)||(nInd>=m_arLine.count()))
    {
        return;
    }
    for(i=nInd+1; i<m_arLine.count(); i++)
    {
        m_arLine[i]->m_wID -= 1;
    }
    CEleLine* pLine = m_arLine.at(nInd);
    m_arLine.remove(nInd);
    delete pLine;

    for(i=0; i<m_arTrans.count(); i++)
    {
        for(int j=0; j<CEleTrans::MAX_BRA_COUNT; j++)
        {
            if(m_arTrans[i]->m_wBraID[j] == nInd+1)
                m_arTrans[i]->m_wBraID[j] = 0;
            else if(m_arTrans[i]->m_wBraID[j] > nInd+1)
                m_arTrans[i]->m_wBraID[j] -= 1;
        }
    }
}

void CCmtdFile::RemoveTrans(int nInd)
{
    if((nInd<0)||(nInd>=m_arTrans.count()))
    {
        return;
    }
    CEleTrans* pTrans = m_arTrans.at(nInd);
    m_arTrans.remove(nInd);
    delete pTrans;
}

void CCmtdFile::RemoveDC(int nInd)
{
    if((nInd<0)||(nInd>=m_arDC.count()))
    {
        return;
    }
    CEleDC* pDC = m_arDC.at(nInd);
    m_arDC.remove(nInd);
    delete pDC;
}

void CCmtdFile::RemoveGenerator(int nInd)
{
    if((nInd<0)||(nInd>=m_arGenerator.count()))
    {
        return;
    }
    CEleGenerator* pGenerator = m_arGenerator.at(nInd);
    m_arGenerator.remove(nInd);
    delete pGenerator;
}

void CCmtdFile::RemoveExciter(int nInd)
{
    if((nInd<0)||(nInd>=m_arExciter.count()))
    {
        return;
    }
    CEleExciter* pItem = m_arExciter.at(nInd);
    m_arExciter.remove(nInd);
    delete pItem;
}

bool CCmtdFile::ReadDMFFile(const QString& strDMF)
{
    CDMFReader* pdmf = new CDMFReader(this);
    if(!pdmf->readFile(strDMF))
    {
        delete pdmf;
        return false;
    }
    delete pdmf;
    return true;
}

bool CCmtdFile::AutoDef()
{
    removeEleItem();
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    //自动查找电压
    //[[
    QString strBus;
    int i=0,j=0;
    QString strName;
    unsigned short wAID=0,wBID=0,wCID=0,wNID=0;
    for(i=0; i<m_arAChanel.count(); i++)
    {
        if(m_arAChanel[i]->m_wType != 1)
        {
            continue;
        }
        wAID=0;wBID=0;wCID=0;wNID=0;
        strName = gbk->toUnicode(m_arAChanel[i]->m_chName);
        if(strName.indexOf(QString("Ua")) >= 0)
        {
            strBus = strName;
            strBus = strBus.replace(QString("Ua"),QString(""));
            wAID = i+1;
        }
        else
        {
            continue;
        }

        for(j=0; j<m_nACount; j++)
        {
            if(j == i)
            {
                continue;
            }
            if(m_arAChanel[j]->m_wType != 1)
            {
                continue;
            }
            strName = gbk->toUnicode(m_arAChanel[j]->m_chName);
            if(strName == strBus+QString("Ub"))
            {
                wBID = j+1;
            }
            else if(strName == strBus+QString("Uc"))
            {
                wCID = j+1;
            }
            else if(strName == strBus+QString("3U0"))
            {
                wNID = j+1;
            }
        }

        if((wAID>0)&&(wBID>0)&&(wCID>0))
        {
            CEleBus* pBus = new CEleBus();
            strcpy(pBus->m_chName,gbk->fromUnicode(strBus));
            pBus->m_wAID = wAID;
            pBus->m_wBID = wBID;
            pBus->m_wCID = wCID;
            pBus->m_wNID = wNID;

            if(strBus.indexOf(QString("1000")) >= 0)
                pBus->m_dVoltage = 1000;
            else if(strBus.indexOf(QString("750")) >= 0)
                pBus->m_dVoltage = 750;
            else if(strBus.indexOf(QString("500")) >= 0)
                pBus->m_dVoltage = 500;
            else if(strBus.indexOf(QString("330")) >= 0)
                pBus->m_dVoltage = 330;
            else if(strBus.indexOf(QString("220")) >= 0)
                pBus->m_dVoltage = 220;
            else if(strBus.indexOf(QString("110")) >= 0)
                pBus->m_dVoltage = 110;
            else if(strBus.indexOf(QString("66")) >= 0)
                pBus->m_dVoltage = 66;
            else if(strBus.indexOf(QString("35")) >= 0)
                pBus->m_dVoltage = 35;
            else if(strBus.indexOf(QString("10")) >= 0)
                pBus->m_dVoltage = 10;
            else
                pBus->m_dVoltage = 220;
            m_arBus.append(pBus);
        }
    }
    //]]

    //自动查找电流
    //[[
    QString strLine;
    for(i=0; i<m_nACount; i++)
    {
        if(m_arAChanel[i]->m_wType != 2)
            continue;
        wAID=0;wBID=0;wCID=0;wNID=0;
        strName = gbk->toUnicode(m_arAChanel[i]->m_chName);
        if(strName.indexOf(QString("Ia")) >= 0)
        {
            strLine = strName;
            strLine = strLine.replace(QString("Ia"),QString(""));
            wAID = i+1;
        }
        else
        {
            continue;
        }

        for(j=0; j<m_nACount; j++)
        {
            if(j == i)
            {
                continue;
            }
            if(m_arAChanel[j]->m_wType != 2)
            {
                continue;
            }

            strName = gbk->toUnicode(m_arAChanel[j]->m_chName);
            if(strName == strLine+QString("Ib"))
            {
                wBID = j+1;
            }
            else if(strName == strLine+QString("Ic"))
            {
                wCID = j+1;
            }

            if(strName == strLine+QString("3I0"))
            {
                wNID = j+1;
            }
        }

        if((wAID>0)&&(wCID>0))
        {
            CEleLine* pLine = new CEleLine();
            strcpy(pLine->m_chName,gbk->fromUnicode(strLine));
            pLine->m_wAID = wAID;
            pLine->m_wBID = wBID;
            pLine->m_wCID = wCID;
            pLine->m_wNID = wNID;

            if(m_arBus.count() > 0)
            {
                pLine->m_wBusId = 1;
                pLine->m_pBus = m_arBus.at(0);
            }
            else
            {
                pLine->m_pBus = NULL;
            }
            m_arLine.append(pLine);
        }
    }
    //]]

    if((m_arBus.count()<=0)&&(m_arLine.count()<=0))
    {
        return false;
    }
    return true;
}

bool CCmtdFile::SaveToDmf(const QString &strPath)
{
    CDMFReader* pDMF = new CDMFReader(this);
    if(pDMF->saveFile(strPath))
    {
        delete pDMF;
        //////////////////////////////////////////////////////////////////////////
        //写入扩展DC文件DC_Extend.txt.
        //格式：通道号,二次侧最小值,二次侧最大值,一次侧最小值,一次侧最大值
        //例如：61,4,20,0,300
        QFileInfo finfo(strPath);
        QString strDCExFile = finfo.absolutePath()+QString("/DC_Extend.txt");
        QFile ecetd(strDCExFile);
        if(!ecetd.open(QIODevice::WriteOnly))
        {
            return false;
        }
        char* strline = new char[2048];
        for(int i=0; i<m_arDC.count(); i++)
        {
            if(m_arDC[i]->m_bExternDC)
            {
                if(m_arDC[i]->m_pChanel != NULL)
                {
                    sprintf(strline,"%d,%g,%g,%g,%g\r\n",m_arDC[i]->m_pChanel->m_wID,m_arDC[i]->m_dMin_Two,m_arDC[i]->m_dMax_Two,m_arDC[i]->m_dMin_One,m_arDC[i]->m_dMax_One);
                }
                else
                {
                    sprintf(strline,"%d,%g,%g,%g,%g\r\n",0,m_arDC[i]->m_dMin_Two,m_arDC[i]->m_dMax_Two,m_arDC[i]->m_dMin_One,m_arDC[i]->m_dMax_One);
                }
                ecetd.write(strline,strlen(strline));
            }
        }
        ecetd.close();
        delete []strline;
        return true;
    }
    delete pDMF;
    return false;
}

bool CCmtdFile::ReadEleParam(const QString &strCfgPath)
{
    GetFilePath(strCfgPath);
    if(!ReadCfgFile())
    {
        return false;
    }
    if(!ReadDMFFile(m_strDMFFilePath))
    {
        if(!ReadLneFile())
        {
            if(!ReadHdrFile())
                return false;
        }
    }
    GenerateTransInfo();
    ReadDCExtend();


    return true;
}

void CCmtdFile::GetChanelsPhase(CEleAChanel *pAChanel)
{
    if((pAChanel->m_strph.toUpper() == QString("A"))&&(pAChanel->m_struu.toUpper() == QString("V")))
        pAChanel->m_ePhase = CEleAChanel::phs_Ua;
    if((pAChanel->m_strph.toUpper() == QString("B"))&&(pAChanel->m_struu.toUpper() == QString("V")))
        pAChanel->m_ePhase = CEleAChanel::phs_Ub;
    if((pAChanel->m_strph.toUpper() == QString("C"))&&(pAChanel->m_struu.toUpper() == QString("V")))
        pAChanel->m_ePhase = CEleAChanel::phs_Uc;
    if((pAChanel->m_strph.toUpper() == QString("N"))&&(pAChanel->m_struu.toUpper() == QString("V")))
        pAChanel->m_ePhase = CEleAChanel::phs_3U0;
    if((pAChanel->m_strph.toUpper() == QString("A"))&&(pAChanel->m_struu.toUpper() == QString("A")))
        pAChanel->m_ePhase = CEleAChanel::phs_Ia;
    if((pAChanel->m_strph.toUpper() == QString("B"))&&(pAChanel->m_struu.toUpper() == QString("A")))
        pAChanel->m_ePhase = CEleAChanel::phs_Ib;
    if((pAChanel->m_strph.toUpper() == QString("C"))&&(pAChanel->m_struu.toUpper() == QString("A")))
        pAChanel->m_ePhase = CEleAChanel::phs_Ic;
    if((pAChanel->m_strph.toUpper() == QString("N"))&&(pAChanel->m_struu.toUpper() == QString("A")))
        pAChanel->m_ePhase = CEleAChanel::phs_3I0;
}

bool CCmtdFile::ReadDCExtend()
{
    QFileInfo finfo(m_strCfgFilePath);
    QString strDCExFile = finfo.absolutePath()+QString("/DC_Extend.txt");
    QFile dcefile(strDCExFile);
    if(!dcefile.open(QIODevice::ReadOnly))
    {
        return false;
    }
    //变量定义[[
    QString strline;
    char* chline = new char[4096];
    const int size = 4096;
    const QString strsplit = QString(",");
    QStringList arstr;
    int id = 0;

    while(dcefile.readLine(chline,size) > 0)
    {
        arstr.clear();
        strline = QString::fromUtf8(chline);
        arstr = strline.split(strsplit);
        if(arstr.size() < 5)
        {
            continue;
        }
        id = arstr.at(0).toInt();   //通道号
        for(int i=0; i<m_arDC.count(); i++)
        {
            if(m_arDC[i]->m_pChanel != NULL)
            {
                if(m_arDC[i]->m_pChanel->m_wID == id)
                {
                    m_arDC[i]->m_bExternDC = true;
                    m_arDC[i]->m_dMin_Two = arstr.at(1).toFloat();
                    m_arDC[i]->m_dMax_Two = arstr.at(2).toFloat();
                    m_arDC[i]->m_dMin_One = arstr.at(3).toFloat();
                    m_arDC[i]->m_dMax_One = arstr.at(4).toFloat();

                    m_arDC[i]->m_pChanel->m_fSMin = m_arDC[i]->m_dMin_Two;
                    m_arDC[i]->m_pChanel->m_fSMax = m_arDC[i]->m_dMax_Two;
                    m_arDC[i]->m_pChanel->m_fPMin = m_arDC[i]->m_dMin_One;
                    m_arDC[i]->m_pChanel->m_fPMax = m_arDC[i]->m_dMax_One;
                    break;
                }
            }
        }
    }

    delete []chline;
    dcefile.close();

    return true;
}

bool CCmtdFile::ReadExtFile()
{
    QFile extfile(m_strExtFilePath);
    if(!extfile.open(QFile::ReadOnly))
    {
        return false;
    }

    const unsigned int type_fault = 0xFFFF0151;
    const unsigned int type_leaptime = 0xFFFF0351;
    const unsigned int type_trig = 0xFFFF0251;

    unsigned int utype = 0;
    unsigned short ucount = 0;
    unsigned short ulen = 0;
    int npos = 0;
    int nsize = extfile.size();
    ext_INFO_LEAPTIME tagLeapTime;
    const int szLeap = sizeof(ext_INFO_LEAPTIME);
    while(npos < nsize)
    {
        //类型、数目、长度[[
        if(extfile.read((char*)(&utype),4) != 4)
        {
            break;
        }
        npos += 4;
        if(npos > nsize)
        {
            break;
        }
        if(extfile.read((char*)(&ucount),2) != 2)
        {
            break;
        }
        npos += 2;
        if(npos > nsize)
        {
            break;
        }

        if(extfile.read((char*)(&ulen),2) != 2)
        {
            break;
        }
        npos += 2;
        if(npos > nsize)
        {
            break;
        }
        //]]类型、数目、长度

        //条目内容[[
        //(1) faultinfo[
        if(utype == type_fault)
        {
            extfile.seek(npos+ulen*ucount);
            npos += ulen*ucount;
            if(npos >= nsize)
            {
                break;
            }
        }//]
        else if(utype == type_leaptime)  //(2) leaptime[
        {
            memset(&tagLeapTime,0,szLeap);
            if(extfile.read((char*)(&tagLeapTime),szLeap) != szLeap)
            {
                break;
            }
            m_nleap_ltime = tagLeapTime.leap_ltime;
            m_nleap_command = tagLeapTime.leap_command;

            npos += szLeap;
            if(npos >= nsize)
            {
                break;
            }
        }//]
        else if(utype == type_trig)      //(3) trig[
        {
            if(ulen*ucount > 0)
            {
                m_chTrigInfo = new char[ulen*ucount];
                extfile.read(m_chTrigInfo,ulen*ucount);
                m_nTrigCount = ucount;
            }

            npos += ulen*ucount;
            if(npos >= nsize)
            {
                break;
            }
        }//]
        else    //未知信息[
        {
            extfile.seek(npos+ulen*ucount);
            npos += ulen*ucount;
            if(npos >= nsize)
            {
                break;
            }
        }//]

        //]]条目内容
    }

    extfile.close();
    return true;
}

bool CCmtdFile::readStartTime()
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QFile cfgfile(m_strCfgFilePath);
    if(!cfgfile.open(QIODevice::ReadOnly))
    {
        sprintf(m_chErrorInfo,"error 0007: Open cfg file failed. FilePath = %s",m_strCfgFilePath.toLatin1().constData());
        ////delete gbk;
        return false;
    }
    if(cfgfile.size() < 20)
    {
        cfgfile.close();
        strcpy(m_chErrorInfo,"error 0008: cfg file is empty.(<20bytes)");
        ////delete gbk;
        return false;
    }
    char chline[2048] = {0};
    const int size = 2048;
    cfgfile.readLine(chline,size);
    QString strline = gbk->toUnicode(chline);
    QString strt;
    const QString strsplit = QString(",");
    QStringList arstr = strline.split(strsplit);
    if(arstr.count() < 2)
    {
        strcpy(m_chErrorInfo,"error 0009: cfg file is error(line 1).");
        ////delete gbk;
        return false;
    }
    //line 1: StationName,RecId,Year
    m_strStationName = arstr.at(0);
    m_nRecId = arstr.at(1).toInt();
    if(arstr.count() == 3)
    {
        m_wCmtdYear = arstr.at(2).toInt();
    }
    //line2: CHNCount,ACount,DCount
    cfgfile.readLine(chline,size);
    strline = gbk->toUnicode(chline);
    arstr = strline.split(strsplit);
    if(arstr.count() != 3)
    {
        strcpy(m_chErrorInfo,"error 0009: cfg file is error(line 2).");
        cfgfile.close();
        ////delete gbk;
        return false;
    }
    m_nChanelCount = arstr.at(0).toInt();
    strt = arstr.at(1).toUpper();
    strt.replace("A","");
    m_nACount = strt.toInt();
    strt = arstr.at(2).toUpper();
    strt.replace("D","");
    m_nDCount = strt.toInt();

    if((m_nACount<=0)&&(m_nDCount<=0))
    {
        strcpy(m_chErrorInfo,"error 0010: cfg file is error(chanelcount=0).");
        cfgfile.close();
        ////delete gbk;
        return false;
    }

    for(int i=0; i<m_nACount+m_nDCount; i++)
    {
        cfgfile.readLine(chline,size);
    }

    //seg info
    cfgfile.readLine(chline,size);
    m_nFrate = atoi(chline);
    cfgfile.readLine(chline,size);
    m_nSegCount = atoi(chline);
    // 兼容COMTRADE1997 [2/19/2008]
    if(m_wCmtdYear == 1997)
    {
        m_nSegCount += 1;
    }
    //]]
    if(m_nSegCount <= 0)
    {
        m_nSegCount += 1;
    }

    for(int i=0; i<m_nSegCount; i++)
    {
        cfgfile.readLine(chline,size);
    }

    //读开始时间和启动录波时间
    cfgfile.readLine(chline,size);
    m_strLeftTime = gbk->toUnicode(chline);
    cfgfile.readLine(chline,size);
    m_strStartTime = gbk->toUnicode(chline);
    //加工这个时刻
    cfgfile.close();

    //---------------------------------------------------------------------
    //获取两个时间的差值
    //---------------------------------------------------------------------
    m_wFaultMiniSec = 0;
    float dminiseconds = 0.0;
    float dminisecondf = 0.0;
    QDateTime tms = GetTimeFromString(m_strLeftTime,dminiseconds);
    QDateTime tmf = GetTimeFromString(m_strStartTime,dminisecondf);
    m_strTimeFinalpart = m_strStartTime;
    int npos = m_strTimeFinalpart.lastIndexOf('.');
    if(npos > 0)
    {
        m_strTimeFinalpart = m_strTimeFinalpart.right(m_strTimeFinalpart.length()-npos-1);
    }
    int nspec = tms.secsTo(tmf);
    m_dTimeSpan = (float)(fabs(nspec*1.0) * 1000.0 + dminisecondf-dminiseconds);	//两个时间的差值
    m_tmStart = tmf;
    if(dminisecondf < 1)
    {
        m_wFaultMiniSec = (unsigned int)(dminisecondf * 1000.0);
    }
    else
    {
        m_wFaultMiniSec = (unsigned int)(dminisecondf/* + 0.500001*/);
    }
    m_tmLeft = tms;
    if(dminiseconds < 1)
    {
        m_wLeftMiniSec = (unsigned short)(dminiseconds*1000.0);
    }
    else
    {
        m_wLeftMiniSec = (unsigned short)(dminiseconds/*+0.500001*/);
    }
    if(m_wLeftMiniSec > 1001)
    {
        m_wLeftMiniSec /= 1000;
    }

    ////delete gbk;
    return true;
}

bool CCmtdFile::ReadFile_GetFaultInfo(const QString &a_strCfgFilePath)
{
    GetFilePath(a_strCfgFilePath);
    readStartTime();
    CMarkup* pHdr = new CMarkup();
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    if(!pHdr->Load(MCD_CSTR_FILENAME(m_strHdrFilePath.toStdString())))
    {
        if(!pHdr->Load(MCD_CSTR_FILENAME(gbk->fromUnicode(m_strHdrFilePath).constData())))
        {
            ////delete gbk;
            delete pHdr;
            return false;
        }
    }
    if(!pHdr->FindElem(L"FaultReport"))
    {
        ////delete gbk;
        delete pHdr;
        return false;
    }
    pHdr->IntoElem();

    m_strFaultLine.clear();
    m_strFaultPhase.clear();
    m_fDistance = -1000;
    QString strName,strVal;
    while(pHdr->FindElem(L"FaultInfo"))
    {
        if(pHdr->FindChildElem(L"name"))
            strName = QString::fromStdWString(pHdr->GetChildData());
        if(pHdr->FindChildElem(L"value"))
            strVal = QString::fromStdWString(pHdr->GetChildData());

        if(strName == QString("故障设备名称"))
        {
            m_strFaultLine = strVal;
        }
        else if(strName == QString("故障相别"))
        {
            m_strFaultPhase = strVal;
        }
        else if(strName == QString("故障测距结果"))
        {
            if(strVal.isEmpty())
                m_fDistance = -1000;
            else
                m_fDistance = strVal.toFloat();
        }
    }

    ////delete gbk;
    delete pHdr;
    return true;
}

void CCmtdFile::GetFaultInfo()
{
    float fMaxI = 0;
    int i = 0;
    int n = 0;
    const float fEpslon = 0.2;
    const float fMinFaultI = 0.2;
    if(m_arLine.count() <= 0)
    {
        return;
    }
    //(1) 统计最大电流[[
    for(i=0; i<m_arLine.count(); i++)
    {
        CEleLine* pLine = m_arLine.at(i);
//        if((pLine->m_dLength<fEpslon)||(!pLine->m_bDistance))
//        {
//            continue;
//        }
        for(n=0; n<pLine->m_nSwitchCount; n++)
        {
            CEleDChanel* pDChanel = GetDChanelById(pLine->m_arDChanel[n]);
            if(pDChanel)
                pDChanel->m_sLineNum = i;
        }
        if(pLine->m_pAChanel != NULL)
        {
            if(pLine->m_pAChanel->m_dMaxAbs > fMaxI)
                fMaxI = pLine->m_pAChanel->m_dMaxAbs;
        }
        if(pLine->m_pBChanel != NULL)
        {
            if(pLine->m_pBChanel->m_dMaxAbs > fMaxI)
                fMaxI = pLine->m_pBChanel->m_dMaxAbs;
        }
        if(pLine->m_pCChanel != NULL)
        {
            if(pLine->m_pCChanel->m_dMaxAbs > fMaxI)
                fMaxI = pLine->m_pCChanel->m_dMaxAbs;
        }
    }
    if(fMaxI < fMinFaultI)  //认为无故障
    {
        //(3)查找开关量变位次数[[
        int nbts = m_nTotalPoints/8;
        for(i=0; i<m_nDCount; i++)
        {
            CEleDChanel* pDChanel = m_arDChanel.at(i);
            if(pDChanel->m_sLineNum < 0)    //未关联线路的直接跳过
            {
                continue;
            }
            for(n=1; n<nbts; n++)
            {
                if(pDChanel->m_pData[n] != pDChanel->m_pData[n-1])
                {
                    pDChanel->m_nSWTimes++;
                }
            }
        }
        //]]

        //(4)统计最可能的故障线路(结合开关再次查找)
        int nsw = 0;
        for(i=0; i<m_arLine.count(); i++)
        {
            CEleLine* pLine = m_arLine.at(i);
    //        if(pLine->m_nFaultVal <= 0)
    //        {
    //            continue;
    //        }
            nsw = 0;
            for(n=0; n<pLine->m_nSwitchCount; n++)
            {
                CEleDChanel* pDChanel = GetDChanelById(pLine->m_arDChanel[n]);
                if(pDChanel)
                {
                    nsw += pDChanel->m_nSWTimes;
                }
            }
            if(nsw > 0)
            {
                m_nFaultLine = i;
                return;
            }
        }
        return;
    }
    //]]

    //(2) 查找线路和相别(找两遍，第一遍跳过不需要测距的)[[
    bool bfind = false;
    for(i=0; i<m_arLine.count(); i++)
    {
        CEleLine* pLine = m_arLine.at(i);
        if((pLine->m_dLength<fEpslon)||(!pLine->m_bDistance))
        {
            continue;
        }
        if(pLine->m_pAChanel != NULL)
        {
            if(fabs(pLine->m_pAChanel->m_dMaxAbs-fMaxI) < fEpslon)
            {
                bfind = true;
                m_nFaultLine = i;
                pLine->m_nFaultVal = 2;
                m_nFaultPhase = 0;
            }
        }
        if(pLine->m_pBChanel != NULL)
        {
            if(fabs(pLine->m_pBChanel->m_dMaxAbs-fMaxI) < fEpslon)
            {
                bfind = true;
                m_nFaultLine = i;
                pLine->m_nFaultVal = 2;
                m_nFaultPhase = 1;
            }
        }
        if(pLine->m_pCChanel != NULL)
        {
            if(fabs(pLine->m_pCChanel->m_dMaxAbs-fMaxI) < fEpslon)
            {
                bfind = true;
                m_nFaultLine = i;
                pLine->m_nFaultVal = 2;
                m_nFaultPhase = 2;
            }
        }
    }
    //第二遍全找（主变录波）
    if(!bfind)
    {
        for(i=0; i<m_arLine.count(); i++)
        {
            CEleLine* pLine = m_arLine.at(i);
//            if((pLine->m_dLength<fEpslon)||(!pLine->m_bDistance))
//            {
//                continue;
//            }
            if(pLine->m_pAChanel != NULL)
            {
                if(fabs(pLine->m_pAChanel->m_dMaxAbs-fMaxI) < fEpslon)
                {
                    bfind = true;
                    m_nFaultLine = i;
                    pLine->m_nFaultVal = 2;
                    m_nFaultPhase = 0;
                }
            }
            if(pLine->m_pBChanel != NULL)
            {
                if(fabs(pLine->m_pBChanel->m_dMaxAbs-fMaxI) < fEpslon)
                {
                    bfind = true;
                    m_nFaultLine = i;
                    pLine->m_nFaultVal = 2;
                    m_nFaultPhase = 1;
                }
            }
            if(pLine->m_pCChanel != NULL)
            {
                if(fabs(pLine->m_pCChanel->m_dMaxAbs-fMaxI) < fEpslon)
                {
                    bfind = true;
                    m_nFaultLine = i;
                    pLine->m_nFaultVal = 2;
                    m_nFaultPhase = 2;
                }
            }
        }
    }
    //]]

    //(3)查找开关量变位次数[[
    int nbts = m_nTotalPoints/8;
    for(i=0; i<m_nDCount; i++)
    {
        CEleDChanel* pDChanel = m_arDChanel.at(i);
        if(pDChanel->m_sLineNum < 0)    //未关联线路的直接跳过
        {
            continue;
        }
        for(n=1; n<nbts; n++)
        {
            if(pDChanel->m_pData[n] != pDChanel->m_pData[n-1])
            {
                pDChanel->m_nSWTimes++;
            }
        }
    }
    //]]

    //(4)统计最可能的故障线路(结合开关再次查找)
    int nsw = 0;
    for(i=0; i<m_arLine.count(); i++)
    {
        CEleLine* pLine = m_arLine.at(i);
//        if(pLine->m_nFaultVal <= 0)
//        {
//            continue;
//        }
        nsw = 0;
        for(n=0; n<pLine->m_nSwitchCount; n++)
        {
            CEleDChanel* pDChanel = GetDChanelById(pLine->m_arDChanel[n]);
            if(pDChanel)
            {
                nsw += pDChanel->m_nSWTimes;
            }
        }
        if(nsw > 2)
        {
            m_nFaultLine = i;
            return;
        }
    }

    //(5)主变故障(开关量>=1即可)
    for(i=0; i<m_arLine.count(); i++)
    {
        CEleLine* pLine = m_arLine.at(i);
//        if(pLine->m_nFaultVal <= 0)
//        {
//            continue;
//        }
        nsw = 0;
        for(n=0; n<pLine->m_nSwitchCount; n++)
        {
            CEleDChanel* pDChanel = GetDChanelById(pLine->m_arDChanel[n]);
            if(pDChanel)
            {
                nsw += pDChanel->m_nSWTimes;
            }
        }
        if(nsw > 0)
        {
            m_nFaultLine = i;
            return;
        }
    }
}
