////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: AnaFunc.cpp
// Copyright 2015 gdwy
// Created : 2015/4/20 by Jerry
// History :
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <QCoreApplication>
#include <QElapsedTimer>
#include <QFile>
#include "CnCodec.h"
#include "WYCmtdAna_HB_include.h"
#include "HBCmtdFile.h"
#include "HBAnaReport.h"
#include <QFileInfo>

QString g_strErrorInfo;
extern bool IsAnaReport(const QString& a_strFilePath,bool buppercase);

tagFaultListHB::tagFaultListHB()
{
    m_arFaultInfo = new tagFaultInfoHB[DLL_MAX_FAULT_INFO_HB];
    for(int i=0; i<DLL_MAX_FAULT_INFO_HB; i++)
        memset(&(m_arFaultInfo[i]),0,sizeof(tagFaultInfoHB));
    m_nFaultount = 0;
}

tagFaultListHB::~tagFaultListHB()
{
    delete []m_arFaultInfo;
}

// void DebugPrint(LPCTSTR fmt,...)
// {
// #ifndef _DEBUG
// 	if(fmt == NULL)	return;
// 	QString str;
// 	va_list marker;
// 	va_start( marker, fmt );
// 	str.FormatV( fmt, marker );
// 	va_end( marker );
// 	OutputDebugString(str);
// #endif
// }

void WriteList(const QString& strPath,const QString& strAttach,const QString& strName)
{
    QString strline;
    QString strtmp = strAttach;
    int npos = strtmp.lastIndexOf(QChar(','));
    if(npos > 0)
    {
        strtmp = strtmp.right(strtmp.length()-npos-1);
    }
//    const int nMaxLen = 2*1024*1024;
    int nFan = /*(nIndex+1)*(0x10000)+*/strtmp.toInt()%(0xffff);
    QFile qf(strPath+QString("s_list.txt"));
    if(!qf.open(QIODevice::Append))
    {
        return;
    }
    CWYGbkCodec* gbk = new CWYGbkCodec();
    qf.write(gbk->fromUnicode(QString("%1%2,%3\n").arg(strPath).arg(strName).arg(nFan)));
    qf.close();
    delete gbk;
}

bool DLL_AnalyzeReport_HB(const QString& a_strFilePath,tagFaultListHB* pFaultList,const QString& strStation,const QString& strRec,bool bUppercase/*=false*/)
{
    try
    {
    if(!IsAnaReport(a_strFilePath,bUppercase))
    {
//        sprintf(g_chErrorInfo,"文件过大");
        return false;
    }
//    tagFaultInfoHB* pFaultInfo = (tagFaultInfoHB*)(a_pFaultInfo);
    CHBCmtdFile* pCmtd = new CHBCmtdFile();
//	DebugPrint("[nw]开始读文件");
    if(!pCmtd->HBReadCmtdFile(a_strFilePath))
    {
        delete pCmtd;
//        sprintf(g_chErrorInfo,"读文件失败,失败信息:%s",pCmtd->GetErrorInfo());
        return false;
    }

    CHBAnaReport* pAna = new CHBAnaReport();
    pAna->m_pFileInfo = pCmtd;
    int nFaultInd = 0;
    pAna->GenerateBasicInfo();
    pAna->GenerateSwitchList();

    if(!pAna->GenerateLine_Report_HB(bUppercase))
    {
        delete pCmtd;
        delete pAna;
        return false;
    }
    pFaultList->m_arFaultInfo[nFaultInd].uTrans = 0;


    if(pAna->m_pFaultLine != NULL)
    {
        if(pAna->m_pFaultLine->m_bFault)
            pFaultList->m_arFaultInfo[nFaultInd].chFault = 1;
        else
            pFaultList->m_arFaultInfo[nFaultInd].chFault = 0;
        pFaultList->m_arFaultInfo[nFaultInd].chFaultKind = 0;
        if((pAna->m_pFaultLine->m_nFaultType>=1)&&(pAna->m_pFaultLine->m_nFaultType<=10))
            pFaultList->m_arFaultInfo[nFaultInd].chFaultKind = pAna->m_pFaultLine->m_nFaultType;
        pFaultList->m_arFaultInfo[nFaultInd].chFaultLine = pAna->m_pFaultLine->m_nLineIndex;
        pFaultList->m_arFaultInfo[nFaultInd].nFaultInd = pAna->m_pFaultLine->m_nLineIndex;
        pFaultList->m_arFaultInfo[nFaultInd].fFaultR = (float)(pAna->m_pFaultLine->m_dFaultR);
        pFaultList->m_arFaultInfo[nFaultInd].fFaultX = (float)(pAna->m_pFaultLine->m_dFaultX);

        CEleLine* pLine = &(pCmtd->m_pLine[pAna->m_pFaultLine->m_nLineIndex]);
        strcpy(pFaultList->m_arFaultInfo[nFaultInd].chLineName,pLine->m_chName);
        pFaultList->m_arFaultInfo[nFaultInd].uFpt = pAna->m_pFaultLine->m_uFpt;
        pFaultList->m_arFaultInfo[nFaultInd].uJpt = pAna->m_pFaultLine->m_uJpt;
        pFaultList->m_arFaultInfo[nFaultInd].fFaultDistance = pAna->m_pFaultLine->m_dDistanceI;
        pFaultList->m_arFaultInfo[nFaultInd].uDpi = pAna->m_pFaultLine->m_uDpi;
        pFaultList->m_arFaultInfo[nFaultInd].wChzTime = pAna->m_pFaultLine->m_wChzTime;
    }
    else
    {
        pFaultList->m_arFaultInfo[nFaultInd].chFault = 0;
    }

    QString strhdr = a_strFilePath;
    int npos = strhdr.lastIndexOf(QChar('.'));
    if(npos >= 0)
        strhdr = strhdr.left(npos);
    if(bUppercase)
        strhdr += QString(".HDR");
    else
        strhdr += QString(".hdr");

    pAna->OutputLineReportToFile_HB(pAna->m_pFaultLine,strhdr,strStation,strRec);
    delete pCmtd;
    delete pAna;
    pFaultList->m_nFaultount = 1;
    return true;
    }
    catch(...)
    {
        return false;
    }
}

const QString& DLL_GetErrorInfo_HB()
{
    return g_strErrorInfo;
}

bool IsAnaReport(const QString& a_strFilePath,bool bUppercase)
{
    QString strPath = a_strFilePath;
    int npos = strPath.lastIndexOf('.');
    if(npos > 0)
    {
        strPath = strPath.left(npos);
        if(bUppercase)
            strPath += ".DAT";
        else
            strPath += ".dat";
    }
    QFileInfo finfo(strPath);
    const int MAX_FILESIZE = 60*1024*1024;
    if( finfo.size() > MAX_FILESIZE)
    {
        return false;
    }
    return true;
}
