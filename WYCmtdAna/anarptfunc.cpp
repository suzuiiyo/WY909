//AnaRptFunc.cpp

#include "Dll_Include.h"
#include "CmtdFile.h"
#include "GenerateReport.h"

extern BOOL IsAnaReport(const char* a_strFilePath);

GDWY_FUNC BOOL DLLReport_AnalyzeReport_Line(const char* a_strFilePath,char* a_chErrorInfo)
{
	try
	{
	if(!IsAnaReport(a_strFilePath))
	{
		sprintf(a_chErrorInfo,"文件过大");
		return FALSE;
	}
	memset(&m_gFaultInfo,0,sizeof(tagFaultInfo));
	CCmtdFile  m_FileInfo;
	if(!m_FileInfo.ReadComtradeFile(a_strFilePath))
	{
		sprintf(a_chErrorInfo,"读文件失败,失败信息:%s",m_FileInfo.GetErrorInfo());
		return FALSE;
	}
	CGenerateReport m_wyRpt;
	CString strFilePath = a_strFilePath;
	if(m_FileInfo.m_nTransCount <= 0)	//线路录波
	{
		m_wyRpt.InitData();
		m_wyRpt.m_pFileInfo = &m_FileInfo;
		m_wyRpt.GenerateLine_Report_GD();
		
		if(m_wyRpt.m_pFaultInfo != NULL)
		{
			if(m_wyRpt.m_pFaultInfo->m_bFault)
			m_gFaultInfo.chFault = 1;
			if((m_wyRpt.m_pFaultInfo->m_nFaultType>=1)&&(m_wyRpt.m_pFaultInfo->m_nFaultType<=10))
			{
				m_gFaultInfo.chFaultKind = m_wyRpt.m_pFaultInfo->m_nFaultType;
			}
			else
			{
				m_gFaultInfo.chFaultKind = 0;
			}
			m_gFaultInfo.chFaultLine = m_wyRpt.m_pFaultInfo->m_nLineIndex;
			m_gFaultInfo.fDistance = (float)(m_wyRpt.m_pFaultInfo->m_dDistance);
			m_gFaultInfo.fFaultR = (float)(m_wyRpt.m_pFaultInfo->m_dFaultR);
			m_gFaultInfo.fFaultX = (float)(m_wyRpt.m_pFaultInfo->m_dFaultX);
		}
		m_gFaultInfo.lTimes = m_wyRpt.m_dwFaultTime;
		if(m_FileInfo.m_nTransCount > 0)
			m_gFaultInfo.chTrans = 1;
		

		
		int npos = strFilePath.ReverseFind('.');
		if(npos > 0)
		{
			strFilePath = strFilePath.Left(npos);
		}
		strFilePath += ".hdr";
		if(!m_wyRpt.OutputLineReportToFile_SX(strFilePath))
		{
			strcpy(a_chErrorInfo,m_wyRpt.GetErrorInfo());
		}
	}
	else
	{
		m_wyRpt.InitData();
		m_wyRpt.m_pFileInfo = &m_FileInfo;
		m_wyRpt.GenerateTrans_Report_ZJ();
		/*
		int npos = strFilePath.ReverseFind('.');
		if(npos > 0)
		{
			strFilePath = strFilePath.Left(npos);
		}
		strFilePath += ".hdr";
		m_wyRpt.OutputTransReportToFile_ZJ(strFilePath);
		*/
	}
	return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

GDWY_FUNC void DLLReport_GetFaultInfo(void* pFaultInfo)
{
	memcpy(pFaultInfo,&m_gFaultInfo,sizeof(tagFaultInfo));
}

GDWY_DLL_ANA_FUNC char* DLLReport_GetErrorInfo()
{
	return m_chErrorInfo;
}

BOOL IsAnaReport(const char* a_strFilePath)
{
	CString strPath = a_strFilePath;
	int npos = strPath.ReverseFind('.');
	if(npos > 0)
	{
		strPath = strPath.Left(npos);
		strPath += ".dat";
	}
	CFileStatus ftu;
	CFile::GetStatus(strPath,ftu);
	const int MAX_FILESIZE = 60*1024*1024;
	if(ftu.m_size > MAX_FILESIZE)
	{
		return FALSE;
	}
	return TRUE;
}
