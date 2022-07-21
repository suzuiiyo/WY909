#include "readthread.h"
#include "CmtdFile.h"
#include <QFile>
#include <math.h>

ReadThread::ReadThread(QObject *parent) :
    QThread(parent)
{
    m_pFileInfo = NULL;
    m_bExit = false;
}

void ReadThread::run()
{    
    m_bExit = false;
    if(m_pFileInfo == NULL)
    {
        return;
    }
    if(m_pFileInfo->m_bBinaryFile)
    {
        Read_BinaryFile();
    }
    else
    {
        Read_AsciiFile();
    }
}

void ReadThread::setFileInfo(CCmtdFile* pFileInfo)
{
    m_pFileInfo = pFileInfo;
}

void ReadThread::setExitFlag()
{
    m_bExit = true;
}

void ReadThread::Read_AsciiFile()
{
    CCmtdFile* pFile = m_pFileInfo;
    //---------------------------------------------------------
    //用内存映射方法读文件
    //---------------------------------------------------------
    QFile datfile(pFile->m_strDatFilePath);
    if(!datfile.open(QIODevice::ReadOnly))
    {
        return;
    }
    char* strline = new char[10240];
    const int nlsize = 10240;
    char* p = NULL;
    char* p1 = NULL;
    char* p2 = NULL;
    unsigned char ukg = 0x01;
    int _tp = 0;
    int n = 0;
    int npercent = 0;
    int i = 0;
    emit SIG_ReadData_Begin();
    for(i=0; i<pFile->m_nTotalPoints; i++)
    {
        if(datfile.readLine(strline,nlsize) <= 0)
        {
            pFile->m_nTotalPoints = i;
            break;
        }
        p = strchr(strline,',');
        p += 1;
        pFile->m_pSampleTime[i] = atol(p);
        pFile->m_pSampleTime[i] *= pFile->m_fTimemult*1.;
        //2018-03-01兼容60Hz
        pFile->m_pSampleTime[i] /= pFile->m_fParam60HZ;
        p1 = strchr(strline,',');
        for(n=0; n<pFile->m_nACount; n++)
        {
            p2=strchr(p1+1,',');
            if(sscanf(p2+1,"%d",&_tp)!=1)//m_pCfg[k].Data[j])!=1)
            {
                datfile.close();
                return;
            }

            pFile->m_arAChanel[n]->m_pData[i] = _tp*pFile->m_arAChanel[n]->m_da + pFile->m_arAChanel[n]->m_db;
            //wpf 2018-08-10添加(COMRADE P10)
            //wpf 2019-03-09 兼容老文件
            //[[
            if((pFile->m_strCfgFilePath.indexOf("DGL")>=0)||(pFile->m_strCfgFilePath.indexOf("dgl")>=0)
                    ||(pFile->m_strCfgFilePath.indexOf("WGL")>=0)||(pFile->m_strCfgFilePath.indexOf("wgl")>=0))
            {}
            else
            {
                if(pFile->m_arAChanel[n]->m_ePS == CEleAChanel::ps_P)
                    pFile->m_arAChanel[n]->m_pData[i] *= pFile->m_arAChanel[n]->m_fSecondary/pFile->m_arAChanel[n]->m_fPrimary;
            }
            //]]

            if(pFile->m_arAChanel[n]->m_dMaxAbs < fabs(pFile->m_arAChanel[n]->m_pData[i]))
            {
                pFile->m_arAChanel[n]->m_dMaxAbs = (float)(fabs(pFile->m_arAChanel[n]->m_pData[i]));
            }
            p1=p2;
        }
        for(n=0;n<pFile->m_nDCount; n++)
        {
            if(i%8 == 0)
            {
                pFile->m_arDChanel[n]->m_pData[i/8] = 0;
            }
            p2=strchr(p1+1,',');
            if(sscanf(p2+1,"%d",&_tp)!=1)//m_pCfg[n].Data[i])!=1)
            {
                datfile.close();
                return;
            }
            if(_tp == 1)
            {
                pFile->m_arDChanel[n]->m_pData[i/8] |= (ukg<<(i%8));
            }
            p1=p2;
        }
        if(i*100/pFile->m_nTotalPoints != npercent)
        {
            npercent = i*100/pFile->m_nTotalPoints;
            emit SIG_ReadData_Percent(npercent);
        }
    }
    
    datfile.close();
    pFile->m_pSampleTime.resize(pFile->m_nTotalPoints);
    //////////////////////////////////////////////////////////////////////////
    //重新计算结束点确定cfg文件的形式
    if(pFile->m_pSegment[pFile->m_nSegCount-1].m_nCount > pFile->m_nTotalPoints-2)
    {
        for(i=pFile->m_nSegCount-1; i>0; i--)
        {
            pFile->m_pSegment[i].m_nCount -= pFile->m_pSegment[i-1].m_nCount;
        }
    }

    delete []strline;
    
    pFile->m_bHaveOpenFile = true;
    pFile->FreshMaxABS();
    pFile->m_bHaveLoad = true;
    pFile->GenerateUnit();
    pFile->GenerateOtherInfo();
    pFile->GenerateLineInfo();
    pFile->m_bLoadFinished = true;

    emit SIG_ReadData_Finished();
}

void ReadThread::Read_BinaryFile()
{
    CCmtdFile* pFile = m_pFileInfo;
    QFile mfile(pFile->m_strDatFilePath);
    if(!mfile.open(QIODevice::ReadOnly))
    {
        return;
    }

    //////////////////////////////////////////////////////////////////////////
    //根据通道数目计算数据单元长度
    int anasize = 0;
    int digsize = 0;
    anasize = pFile->m_nACount*2;
    digsize = pFile->m_nDCount/8;
    if(pFile->m_nDCount%8 != 0)
    {
        digsize += 1;
    }
    if(digsize%2 != 0)
    {
        digsize += 1;
    }
    int blocksize = 8 + anasize + digsize;
    int nBSIZE = 20*1024*blocksize;
    int nTotalPoints = pFile->m_nDatSize/blocksize;
    pFile->m_pSampleTime.resize(nTotalPoints+10);

    int i = 0;
    for(i=0; i<pFile->m_nACount; i++)
    {
        pFile->m_arAChanel[i]->m_pData.resize(nTotalPoints+1000);
    }
    for(i=0; i<pFile->m_nDCount; i++)
    {
        pFile->m_arDChanel[i]->m_pData.resize(nTotalPoints/8+1000);
    }

    char* chBuf = new char[nBSIZE];
    int ncount = pFile->m_nDatSize/nBSIZE;
    if(pFile->m_nDatSize%nBSIZE != 0)
    {
        ncount += 1;
    }

    tagDatUnit* datau = new tagDatUnit;
    int nread = 0;
    int np = 0;
    int n = 0;
    int cn = 0;
    pFile->m_nTotalPoints = 0;
    int npercent = 0;
    const   unsigned char ukg = 0x01;
    unsigned char ud = 0;
    emit SIG_ReadData_Begin();
    for(i=0; i<ncount; i++)
    {
        nread = fmin(nBSIZE,pFile->m_nDatSize-i*nBSIZE);
        mfile.read(chBuf,nread);
        for(np=0; np<nread/blocksize; np++)
        {
            if(m_bExit)
            {
                break;
            }
            memset(datau,0,sizeof(tagDatUnit));
            memcpy(datau,chBuf+np*blocksize,blocksize);
            pFile->m_pSampleTime[n] = datau->m_nSampTime*pFile->m_fTimemult*1.;
            //2018-03-01兼容60Hz
            pFile->m_pSampleTime[n] /= pFile->m_fParam60HZ;
            for(cn=0; cn<pFile->m_nACount; cn++)
            {
                pFile->m_arAChanel[cn]->m_pData[n] = pFile->m_arAChanel[cn]->m_da * datau->m_nSampData[cn] + pFile->m_arAChanel[cn]->m_db;
                //wpf 2018-08-10添加(COMRADE P10)
                //[[
                if(pFile->m_arAChanel[cn]->m_ePS == CEleAChanel::ps_P)
                    pFile->m_arAChanel[cn]->m_pData[n] *= pFile->m_arAChanel[cn]->m_fSecondary/pFile->m_arAChanel[cn]->m_fPrimary;
                //]]

                if(fabs(pFile->m_arAChanel[cn]->m_dMaxAbs) < fabs(pFile->m_arAChanel[cn]->m_pData[n]))
                    pFile->m_arAChanel[cn]->m_dMaxAbs = (float)(fabs(pFile->m_arAChanel[cn]->m_pData[n]));
            }

            for(cn=0; cn<digsize/2; cn++)
            {
                for(int dn=0; dn<16; dn++)
                {
                    int nchno = cn*16 + dn;
                    if(nchno >= pFile->m_nDCount)
                    {
                        break;
                    }
                    if(n%8 == 0)
                    {
                        pFile->m_arDChanel[nchno]->m_pData[n/8] = 0;
                    }
                    ud = (datau->m_nSampData[cn+pFile->m_nACount]>>dn)&ukg;
                    pFile->m_arDChanel[nchno]->m_pData[n/8] |= (ud<<(n%8));
                }
            }
            n++;
            if(n*100/nTotalPoints != npercent)
            {
                npercent = n*100/nTotalPoints;
                emit SIG_ReadData_Percent(npercent);
            }
        }
        if(m_bExit)
        {
            break;
        }
        pFile->m_nTotalPoints = n;
    }

    //////////////////////////////////////////////////////////////////////////
    //这里刷新显示一次
    pFile->FreshMaxABS();
    pFile->m_bHaveOpenFile = true;
    if(!pFile->m_bHaveLoad)
    {
        pFile->m_bHaveLoad = true;
        pFile->GenerateUnit();
        pFile->GenerateOtherInfo();
    }
    pFile->GenerateLineInfo();

    mfile.close();
    delete []chBuf;
    delete datau;
    m_bExit = false;

    pFile->m_bLoadFinished = true;
    //给出结束信号
    emit SIG_ReadData_Finished();
}
