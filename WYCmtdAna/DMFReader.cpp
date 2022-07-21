#include "DMFReader.h"
#include <QFile>
#include <QFileInfo>
#include "CnCodec.h"
#include "Markup.h"

CDMFReader::CDMFReader()
{  
    m_pCmtdFile = NULL;
    m_pDMF = NULL;
}

CDMFReader::CDMFReader(CCmtdFile* pCmtdFile)
{
    m_pCmtdFile = pCmtdFile;
    m_pDMF = NULL;
}

CDMFReader::~CDMFReader()
{
    if(m_pDMF)
    {
        delete m_pDMF;
    }
    m_pDMF = NULL;
}

bool CDMFReader::readFile(const QString& strPath)
{
    if(m_pDMF)
    {
        delete m_pDMF;
        m_pDMF = NULL;
    }

    m_pDMF = new CMarkup;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");

    if(!m_pDMF->Load(MCD_CSTR_FILENAME(strPath.toStdString())))
    {
        if(!m_pDMF->Load(MCD_CSTR_FILENAME(std::string(gbk->fromUnicode(strPath)))))
        {
            ////delete gbk;
            return false;
        }
    }
    if(!m_pDMF->FindElem(L"scl:ComtradeModel"))
    {
        if(!m_pDMF->FindElem(L"ComtradeModel"))
        {
            ////delete gbk;
            return false;
        }
    }
    m_pCmtdFile->m_strStationName = QString::fromStdWString(m_pDMF->GetAttrib(L"station_name"));
    m_pCmtdFile->m_strVersion = QString::fromStdWString(m_pDMF->GetAttrib(L"version"));
    m_pCmtdFile->m_strReference = QString::fromStdWString(m_pDMF->GetAttrib(L"reference"));
    m_pCmtdFile->m_strRecDevName = QString::fromStdWString(m_pDMF->GetAttrib(L"rec_dev_name"));
    m_pCmtdFile->m_strRecRef = QString::fromStdWString(m_pDMF->GetAttrib(L"rec_ref"));

    m_pDMF->IntoElem();
    if(readComtradeModel())
    {
        m_pDMF->OutOfElem();
        ////delete gbk;
        return true;
    }

    ////delete gbk;
    return false;
}

bool CDMFReader::saveFile(const QString &strPath)
{
    if(m_pDMF)
    {
        delete m_pDMF;
        m_pDMF = NULL;
    }

    m_pDMF = new CMarkup;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    m_pDMF->SetDoc(L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    m_pDMF->AddElem(L"scl:ComtradeModel");
    m_pDMF->SetAttrib(L"station_name",m_pCmtdFile->m_strStationName.toStdWString());
    m_pDMF->SetAttrib(L"version",m_pCmtdFile->m_strVersion.toStdWString());
    m_pDMF->SetAttrib(L"reference",m_pCmtdFile->m_strReference.toStdWString());
    m_pDMF->SetAttrib(L"rec_dev_name",m_pCmtdFile->m_strRecDevName.toStdWString());
    m_pDMF->SetAttrib(L"rec_ref",m_pCmtdFile->m_strRecRef.toStdWString());
    m_pDMF->SetAttrib(L"xsi:schemaLocation",L"http://www.iec.ch/61850/2003/SCLcomtrade_mdl_v1.1.xsd");
    m_pDMF->SetAttrib(L"xmlns:scl",L"http://www.iec.ch/61850/2003/SCL");
    m_pDMF->SetAttrib(L"xmlns:xsi",L"http://www.w3.org/2001/XMLSchema-instance");

    m_pDMF->IntoElem();
    writeAChanel();
    writeDChanel();
    writeBus();
    writeLine();
    writeTrans();
    writeGenerator();
    writeExciter();

    bool bresult = m_pDMF->Save(MCD_CSTR_FILENAME(gbk->fromUnicode(strPath).constData()));
    if(!bresult)
    {
        bresult = m_pDMF->Save(MCD_CSTR_FILENAME(strPath.toStdString()));
    }
    ////delete gbk;

    return bresult;
}

bool CDMFReader::readComtradeModel()
{
    m_pDMF->SavePos(L"ComtradeModel");
    readAChanel();
    m_pDMF->RestorePos(L"ComtradeModel");
    readDChanel();
    m_pDMF->RestorePos(L"ComtradeModel");
    readBus();
    m_pDMF->RestorePos(L"ComtradeModel");
    readLine();
    m_pDMF->RestorePos(L"ComtradeModel");
    readTrans();
    m_pDMF->RestorePos(L"ComtradeModel");
    readGenerator();
    m_pDMF->RestorePos(L"ComtradeModel");
    readExciter();
    return true;
}

bool CDMFReader::readAChanel()
{
    QString strVal;
    CEleAChanel* pAChanel = NULL;
    while(m_pDMF->FindElem(L"scl:AnalogChannel"))
    {
        pAChanel = m_pCmtdFile->GetAChanelById(QString::fromStdWString(m_pDMF->GetAttrib(L"idx_cfg")).toUInt());
        if(!pAChanel)
            continue;
        pAChanel->m_wIdxOrg = QString::fromStdWString(m_pDMF->GetAttrib(L"idx_org")).toUInt();
        pAChanel->m_wIdxRel = QString::fromStdWString(m_pDMF->GetAttrib(L"idx_rlt")).toUInt();
        strVal = QString::fromStdWString(m_pDMF->GetAttrib(L"type"));
        if(strVal == QString("A"))
            pAChanel->m_eType = CEleAChanel::type_A;
        else if(strVal == QString("D"))
            pAChanel->m_eType = CEleAChanel::type_D;
        else
            pAChanel->m_eType = CEleAChanel::type_O;

        strVal = QString::fromStdWString(m_pDMF->GetAttrib(L"flag"));
        if(strVal == QString("ACV"))
            pAChanel->m_eFlag = CEleAChanel::flag_ACV;
        else if(strVal == QString("ACC"))
            pAChanel->m_eFlag = CEleAChanel::flag_ACC;
        else if(strVal == QString("HF"))
            pAChanel->m_eFlag = CEleAChanel::flag_HF;
        else if(strVal == QString("FQ"))
            pAChanel->m_eFlag = CEleAChanel::flag_FQ;
        else if(strVal == QString("AG"))
            pAChanel->m_eFlag = CEleAChanel::flag_AG;
        else if(strVal == QString("AMP"))
            pAChanel->m_eFlag = CEleAChanel::flag_AMP;
        else if(strVal == QString("PW"))
            pAChanel->m_eFlag = CEleAChanel::flag_PW;
        else if(strVal == QString("ZX"))
            pAChanel->m_eFlag = CEleAChanel::flag_ZX;
        else if(strVal == QString("CONST"))
            pAChanel->m_eFlag = CEleAChanel::flag_CONST;

        pAChanel->m_fPMin = QString::fromStdWString(m_pDMF->GetAttrib(L"p_min")).toFloat();
        pAChanel->m_fPMax = QString::fromStdWString(m_pDMF->GetAttrib(L"p_max")).toFloat();
        pAChanel->m_fSMin = QString::fromStdWString(m_pDMF->GetAttrib(L"s_min")).toFloat();
        pAChanel->m_fSMax = QString::fromStdWString(m_pDMF->GetAttrib(L"s_max")).toFloat();
        pAChanel->m_fFreq = QString::fromStdWString(m_pDMF->GetAttrib(L"freq")).toFloat();
        pAChanel->m_fAU = QString::fromStdWString(m_pDMF->GetAttrib(L"au")).toFloat();
        pAChanel->m_fBU = QString::fromStdWString(m_pDMF->GetAttrib(L"bu")).toFloat();
        strVal = QString::fromStdWString(m_pDMF->GetAttrib(L"sIUnit"));
        if(strVal == QString("A"))
            pAChanel->m_eSiUnit = CEleAChanel::unit_A;
        else if(strVal == QString("V"))
            pAChanel->m_eSiUnit = CEleAChanel::unit_V;
        else if(strVal == QString("Hz"))
            pAChanel->m_eSiUnit = CEleAChanel::unit_Hz;
        else if(strVal == QString("Ω"))
            pAChanel->m_eSiUnit = CEleAChanel::unit_O;
        else if(strVal == QString("W"))
            pAChanel->m_eSiUnit = CEleAChanel::unit_W;
        else if(strVal == QString("Var"))
            pAChanel->m_eSiUnit = CEleAChanel::unit_Var;

        strVal = QString::fromStdWString(m_pDMF->GetAttrib(L"multiplier"));
        if(strVal == QString("m"))
            pAChanel->m_eMultiplier = CEleAChanel::multi_m;
        else if(strVal == QString("k"))
            pAChanel->m_eMultiplier = CEleAChanel::multi_k;
        else if(strVal == QString("M"))
            pAChanel->m_eMultiplier = CEleAChanel::multi_M;

        pAChanel->m_fPrimary = QString::fromStdWString(m_pDMF->GetAttrib(L"primary")).toFloat();
        pAChanel->m_fSecondary = QString::fromStdWString(m_pDMF->GetAttrib(L"secondary")).toFloat();
        strVal = QString::fromStdWString(m_pDMF->GetAttrib(L"ps"));
        if(strVal.toLower() == QString("p"))
            pAChanel->m_ePS = CEleAChanel::ps_P;
        else if(strVal.toLower() == QString("s"))
            pAChanel->m_ePS = CEleAChanel::ps_S;
        pAChanel->m_strSrcRef = QString::fromStdWString(m_pDMF->GetAttrib(L"srcRef"));
    }

    //2016.12.6增加直流通道
    //[[
    //CWYGbkCodec* gbk = new CWYGbkCodec;
    for(int i=0; i<m_pCmtdFile->m_arAChanel.count(); i++)
    {
        CEleAChanel* pCH = m_pCmtdFile->m_arAChanel.at(i);
        if(pCH->m_eType == CEleAChanel::type_D)
        {
            CEleDC* pDC = new CEleDC;
            strcpy(pDC->m_chName,pCH->m_chName);
            pDC->m_pChanel = pCH;
            strcpy(pDC->m_chUnit1,pCH->m_chUnit1);
            strcpy(pDC->m_chUnit2,pCH->m_chUnit2);
            pDC->m_wChanelID = pCH->m_wID;
            pDC->m_bExternDC = true;
            pDC->m_dMin_One = pCH->m_fPMin;
            pDC->m_dMax_One = pCH->m_fPMax;
            pDC->m_dMin_Two = pCH->m_fSMin;
            pDC->m_dMax_Two = pCH->m_fSMax;
            m_pCmtdFile->m_arDC.append(pDC);
        }
    }
    //delete gbk;
    //]]

    return true;
}

bool CDMFReader::readDChanel()
{
    QString strVal;
    CEleDChanel* pDChanel = NULL;
    while(m_pDMF->FindElem(L"scl:StatusChannel"))
    {
        pDChanel = m_pCmtdFile->GetDChanelById(QString::fromStdWString(m_pDMF->GetAttrib(L"idx_cfg")).toUInt());
        if(!pDChanel)
            continue;
        pDChanel->m_wIdxOrg = QString::fromStdWString(m_pDMF->GetAttrib(L"idx_org")).toUInt();
        strVal =  QString::fromStdWString(m_pDMF->GetAttrib(L"type"));
        if(strVal == QString("Relay"))
            pDChanel->m_eType = CEleDChanel::Relay;
        else if(strVal == QString("Breaker"))
            pDChanel->m_eType = CEleDChanel::Breaker;
        else if(strVal == QString("Switch"))
            pDChanel->m_eType = CEleDChanel::Switch;
        else if(strVal == QString("Warning"))
            pDChanel->m_eType = CEleDChanel::Warning;
        else if(strVal == QString("Other"))
            pDChanel->m_eType = CEleDChanel::Other;

        pDChanel->m_strFlag = QString::fromStdWString(m_pDMF->GetAttrib(L"flag"));
        strVal =  QString::fromStdWString(m_pDMF->GetAttrib(L"contact"));
        if(strVal == QString("NormallyOpen"))
            pDChanel->m_eContact = CEleDChanel::NormallyOpen;
        else if(strVal == QString("NormallyClosed"))
            pDChanel->m_eContact = CEleDChanel::NormallyClosed;

        pDChanel->m_strSrcRef =  QString::fromStdWString(m_pDMF->GetAttrib(L"srcRef"));
    }
    return true;
}

bool CDMFReader::readBus()
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QString strval;
    while(m_pDMF->FindElem(L"scl:Bus"))
    {
        CEleBus* pBus = new CEleBus();
        m_pCmtdFile->m_arBus.append(pBus);
        pBus->m_wID = QString::fromStdWString(m_pDMF->GetAttrib(L"idx")).toUInt();
        pBus->m_wSysID = pBus->m_wID;
        strcpy(pBus->m_chName,gbk->fromUnicode(QString::fromStdWString(m_pDMF->GetAttrib(L"bus_name"))));
        pBus->m_strSrcRef = QString::fromStdWString(m_pDMF->GetAttrib(L"srcRef"));
        pBus->m_fVrtg = QString::fromStdWString(m_pDMF->GetAttrib(L"VRtg")).toFloat();
        pBus->m_dVoltage = pBus->m_fVrtg;
        pBus->m_fVrtgSnd = QString::fromStdWString(m_pDMF->GetAttrib(L"VRtgSnd")).toFloat();
        strval = QString::fromStdWString(m_pDMF->GetAttrib(L"VRtgSnd_Pos")).toLower();
        if(strval == QString("bus"))
            pBus->m_eTvPos = CEleBus::e_tv_bus;
        else if(strval == QString("line"))
            pBus->m_eTvPos = CEleBus::e_tv_line;
        m_pDMF->SavePos(L"Bus_Pos");

//        m_pDMF->IntoElem();
        if(m_pDMF->FindChildElem(L"scl:ACVChn"))
        {
            pBus->m_wAID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ua_idx")).toUInt();
            pBus->m_pAChanel = m_pCmtdFile->GetAChanelById(pBus->m_wAID);
            pBus->m_wBID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ub_idx")).toUInt();
            pBus->m_pBChanel = m_pCmtdFile->GetAChanelById(pBus->m_wBID);
            pBus->m_wCID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"uc_idx")).toUInt();
            pBus->m_pCChanel = m_pCmtdFile->GetAChanelById(pBus->m_wCID);
            pBus->m_wNID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"un_idx")).toUInt();
            pBus->m_pNChanel = m_pCmtdFile->GetAChanelById(pBus->m_wNID);
            pBus->m_wLID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ul_idx")).toUInt();
            pBus->m_pLChanel = m_pCmtdFile->GetAChanelById(pBus->m_wLID);
        }
        m_pDMF->RestorePos(L"Bus_Pos");
        while(m_pDMF->FindChildElem(L"scl:AnaChn"))
        {
            pBus->m_arAChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }
        m_pDMF->RestorePos(L"Bus_Pos");
        while(m_pDMF->FindChildElem(L"scl:StaChn"))
        {
            pBus->m_arDChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }
//        m_pDMF->OutOfElem();
    }

    //delete gbk;
    return true;
}

bool CDMFReader::readLine()
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QString strval;
    while(m_pDMF->FindElem(L"scl:Line"))
    {
        CEleLine* pLine = new CEleLine();
        m_pCmtdFile->m_arLine.append(pLine);
        pLine->m_wID = QString::fromStdWString(m_pDMF->GetAttrib(L"idx")).toUInt();
        strcpy(pLine->m_chName,gbk->fromUnicode(QString::fromStdWString(m_pDMF->GetAttrib(L"line_name"))));
        pLine->m_wBusId = QString::fromStdWString(m_pDMF->GetAttrib(L"bus_ID")).toUInt();
        pLine->m_pBus = m_pCmtdFile->GetBusById(pLine->m_wBusId);
//        pLine->m_nHgLine = QString::fromStdWString(m_pDMF->GetAttrib(L"other_ID")).toUInt()-1;
        pLine->m_strSrcRef = QString::fromStdWString(m_pDMF->GetAttrib(L"srcRef"));
        pLine->m_dVoltage = QString::fromStdWString(m_pDMF->GetAttrib(L"VRtg")).toFloat();
        pLine->m_fArtg = QString::fromStdWString(m_pDMF->GetAttrib(L"ARtg")).toFloat();
        pLine->m_dMaxI = QString::fromStdWString(m_pDMF->GetAttrib(L"ARtgSnd")).toFloat();
        pLine->m_dLength = QString::fromStdWString(m_pDMF->GetAttrib(L"LinLen")).toFloat();
        if(pLine->m_dLength < 0.5)
            pLine->m_bDistance = false;
        else
            pLine->m_bDistance = true;
        pLine->m_nBranNum = QString::fromStdWString(m_pDMF->GetAttrib(L"bran_num")).toInt();
        pLine->m_dCT = pLine->m_fArtg/pLine->m_dMaxI;

        m_pDMF->SavePos(L"Line_Pos");
        if(m_pDMF->FindChildElem(L"scl:RX"))
        {
            pLine->m_dR1 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"r1")).toFloat();
            pLine->m_dX1 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"x1")).toFloat();
            pLine->m_dR0 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"r0")).toFloat();
            pLine->m_dX0 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"x0")).toFloat();
        }
        m_pDMF->RestorePos(L"Line_Pos");
        if(m_pDMF->FindChildElem(L"scl:CG"))
        {
            pLine->m_fC1 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"c1")).toFloat();
            pLine->m_fC0 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"c0")).toFloat();
            pLine->m_fG1 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"g1")).toFloat();
            pLine->m_fG0 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"g0")).toFloat();
        }
        m_pDMF->RestorePos(L"Line_Pos");
        if(m_pDMF->FindChildElem(L"scl:MR"))
        {
            pLine->m_nHgLine = QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx")).toUInt()-1;
            pLine->m_dRh= QString::fromStdWString(m_pDMF->GetChildAttrib(L"mr0")).toFloat();
            pLine->m_dXh = QString::fromStdWString(m_pDMF->GetChildAttrib(L"mx0")).toFloat();
        }
        m_pDMF->RestorePos(L"Line_Pos");
        while(m_pDMF->FindChildElem(L"scl:ACC_Bran"))
        {
            if(pLine->m_wAID <= 0)
            {
                pLine->m_wAID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ia_idx")).toUInt();
                pLine->m_wBID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ib_idx")).toUInt();
                pLine->m_wCID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ic_idx")).toUInt();
                pLine->m_wNID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"in_idx")).toUInt();

                strval = QString::fromStdWString(m_pDMF->GetChildAttrib(L"dir"));;
                if(strval == QString("POS"))
                    pLine->m_eDir1 = CEleLine::dir_POS;
                else if(strval == QString("NEG"))
                    pLine->m_eDir1 = CEleLine::dir_NEG;
                else
                    pLine->m_eDir1 = CEleLine::dir_UNC;
            }
            else
            {
                pLine->m_wAID2 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ia_idx")).toUInt();
                pLine->m_wBID2 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ib_idx")).toUInt();
                pLine->m_wCID2 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ic_idx")).toUInt();
                pLine->m_wNID2 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"in_idx")).toUInt();
                strval = QString::fromStdWString(m_pDMF->GetChildAttrib(L"dir"));;
                if(strval == QString("POS"))
                    pLine->m_eDir2 = CEleLine::dir_POS;
                else if(strval == QString("NEG"))
                    pLine->m_eDir2 = CEleLine::dir_NEG;
                else
                    pLine->m_eDir2 = CEleLine::dir_UNC;
            }
        }

        m_pDMF->RestorePos(L"Line_Pos");
        if(pLine->m_nBranNum == 1)
        {
            pLine->m_pAChanel = m_pCmtdFile->GetAChanelById(pLine->m_wAID);
            pLine->m_pBChanel = m_pCmtdFile->GetAChanelById(pLine->m_wBID);
            pLine->m_pCChanel = m_pCmtdFile->GetAChanelById(pLine->m_wCID);
            pLine->m_pNChanel = m_pCmtdFile->GetAChanelById(pLine->m_wNID);
        }

        m_pDMF->RestorePos(L"Line_Pos");
        if(m_pDMF->FindChildElem(L"scl:PX"))
        {
            pLine->m_fPx1 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"px")).toFloat();
            pLine->m_fPx0 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"px0")).toFloat();
        }

        m_pDMF->RestorePos(L"Line_Pos");
        while(m_pDMF->FindChildElem(L"scl:AnaChn"))
        {
            pLine->m_arAChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }
        m_pDMF->RestorePos(L"Line_Pos");
        while(m_pDMF->FindChildElem(L"scl:StaChn"))
        {
            pLine->m_arDChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }
    }

    //delete gbk;
    return true;
}

bool CDMFReader::readTrans()
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QString strVal;
    while(m_pDMF->FindElem(L"scl:Transformer"))
    {
        CEleTrans* pTrans = new CEleTrans();
        m_pCmtdFile->m_arTrans.append(pTrans);
        pTrans->m_wID = QString::fromStdWString(m_pDMF->GetAttrib(L"idx")).toUInt();
        strcpy(pTrans->m_chName,gbk->fromUnicode(QString::fromStdWString(m_pDMF->GetAttrib(L"trm_name"))));
        pTrans->m_strSrcRef = QString::fromStdWString(m_pDMF->GetAttrib(L"srcRef"));
        pTrans->m_fPwrRtg = QString::fromStdWString(m_pDMF->GetAttrib(L"pwrRtg")).toFloat();
        m_pDMF->SavePos(L"Trans_Pos");
        while(m_pDMF->FindChildElem(L"scl:TransformerWinding"))
        {            
            readWinding(pTrans);
        }
        m_pDMF->RestorePos(L"Trans_Pos");
        while(m_pDMF->FindChildElem(L"scl:AnaChn"))
        {
            pTrans->m_arAChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }
        m_pDMF->RestorePos(L"Trans_Pos");
        while(m_pDMF->FindChildElem(L"scl:StaChn"))
        {
            pTrans->m_arDChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }
    }

    //delete gbk;
    return true;
}

bool CDMFReader::readGenerator()
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QString strVal;
    while(m_pDMF->FindElem(L"scl:Generator"))
    {
        CEleGenerator* pGenerator = new CEleGenerator();
        m_pCmtdFile->m_arGenerator.append(pGenerator);

        pGenerator->m_wID = QString::fromStdWString(m_pDMF->GetAttrib(L"idx")).toUInt();
        strcpy(pGenerator->m_chName,gbk->fromUnicode(QString::fromStdWString(m_pDMF->GetAttrib(L"gen_name"))));
        pGenerator->m_strSrcRef = QString::fromStdWString(m_pDMF->GetAttrib(L"srcRef"));
        pGenerator->m_wTrmSID = QString::fromStdWString(m_pDMF->GetAttrib(L"trm_SID")).toUInt();
        strVal = QString::fromStdWString(m_pDMF->GetAttrib(L"type"));
        if(strVal == QString("STEAM_TURBINE"))
            pGenerator->m_eType = CEleGenerator::STEAM_TURBINE;
        else/* if(strVal == QString("WATER_TURBINE"))*/
            pGenerator->m_eType = CEleGenerator::WATER_TURBINE;
        pGenerator->m_fFreq = QString::fromStdWString(m_pDMF->GetAttrib(L"freq")).toFloat();
        pGenerator->m_fCapacity = QString::fromStdWString(m_pDMF->GetAttrib(L"capacity")).toFloat();
        pGenerator->m_fFactor = QString::fromStdWString(m_pDMF->GetAttrib(L"factor")).toFloat();
        pGenerator->m_fVRtg = QString::fromStdWString(m_pDMF->GetAttrib(L"VRtg")).toFloat();
        pGenerator->m_fRotorI = QString::fromStdWString(m_pDMF->GetAttrib(L"rotor_I")).toFloat();
        pGenerator->m_fRotorV2 = QString::fromStdWString(m_pDMF->GetAttrib(L"rotor_V2")).toFloat();
        pGenerator->m_nNeutGroupNum = QString::fromStdWString(m_pDMF->GetAttrib(L"neut_group_num")).toUInt();
        pGenerator->m_nExciterMode = QString::fromStdWString(m_pDMF->GetAttrib(L"exciter_Mode")).toInt();
        pGenerator->m_nIgtDir = QString::fromStdWString(m_pDMF->GetAttrib(L"igt_Dir")).toInt();

        m_pDMF->SavePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:Ufe"))
        {
            pGenerator->m_fUfe = QString::fromStdWString(m_pDMF->GetChildAttrib(L"Ufe")).toFloat();
        }
        m_pDMF->RestorePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:X"))
        {
            pGenerator->m_fXd = QString::fromStdWString(m_pDMF->GetChildAttrib(L"xd")).toFloat();
            pGenerator->m_fXq = QString::fromStdWString(m_pDMF->GetChildAttrib(L"xq")).toFloat();
            pGenerator->m_fXd1= QString::fromStdWString(m_pDMF->GetChildAttrib(L"xd1")).toFloat();
            pGenerator->m_fXs = QString::fromStdWString(m_pDMF->GetChildAttrib(L"xs")).toFloat();
        }
        m_pDMF->RestorePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:ACCChn"))
        {
            pGenerator->m_wIAID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ia_idx")).toUInt();
            pGenerator->m_wIBID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ib_idx")).toUInt();
            pGenerator->m_wICID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ic_idx")).toUInt();
            strVal = QString::fromStdWString(m_pDMF->GetChildAttrib(L"dir"));
            if(strVal == QString("POS"))
                pGenerator->m_eDirA = CEleGenerator::dir_POS;
            else if(strVal == QString("NEG"))
                pGenerator->m_eDirA = CEleGenerator::dir_NEG;
            else
                pGenerator->m_eDirA = CEleGenerator::dir_UNC;
        }
        m_pDMF->RestorePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:ACCZChn"))
        {
            pGenerator->m_wZAID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ia_idx")).toUInt();
            pGenerator->m_wZBID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ib_idx")).toUInt();
            pGenerator->m_wZCID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ic_idx")).toUInt();
            strVal = QString::fromStdWString(m_pDMF->GetChildAttrib(L"dir"));
            if(strVal == QString("POS"))
                pGenerator->m_eDirZ = CEleGenerator::dir_POS;
            else if(strVal == QString("NEG"))
                pGenerator->m_eDirZ = CEleGenerator::dir_NEG;
            else
                pGenerator->m_eDirZ = CEleGenerator::dir_UNC;
        }

        m_pDMF->RestorePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:ACVChn"))
        {
            pGenerator->m_wUAID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ua_idx")).toUInt();
            pGenerator->m_wUBID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ub_idx")).toUInt();
            pGenerator->m_wUCID = QString::fromStdWString(m_pDMF->GetChildAttrib(L"uc_idx")).toUInt();
        }

        m_pDMF->RestorePos(L"Generator_Pos");
        while(m_pDMF->FindChildElem(L"scl:NeutGroup"))
        {
            pGenerator->m_arNeutBranNum.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"bran_num")).toUInt());
            pGenerator->m_arNeutIa.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"ia_idx")).toUInt());
            pGenerator->m_arNeutIb.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"ib_idx")).toUInt());
            pGenerator->m_arNeutIc.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"ic_idx")).toUInt());
            strVal = QString::fromStdWString(m_pDMF->GetChildAttrib(L"dir"));
            if(strVal == QString("POS"))
                pGenerator->m_arDir.append(CEleGenerator::dir_POS);
            else if(strVal == QString("NEG"))
                pGenerator->m_arDir.append(CEleGenerator::dir_NEG);
            else/* if(strVal == QString("UNC"))*/
                pGenerator->m_arDir.append(CEleGenerator::dir_UNC);
        }

        m_pDMF->RestorePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:Ufe_Chns"))
        {
            pGenerator->m_wUfe = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ufe_idx")).toUInt();
            pGenerator->m_wPosUfe = QString::fromStdWString(m_pDMF->GetChildAttrib(L"posufe_idx")).toUInt();
            pGenerator->m_wNegUfe = QString::fromStdWString(m_pDMF->GetChildAttrib(L"negufe_idx")).toUInt();
        }

        m_pDMF->RestorePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:Ife_Chn"))
        {
            pGenerator->m_wIfe = QString::fromStdWString(m_pDMF->GetChildAttrib(L"Ife")).toUInt();
        }

        m_pDMF->RestorePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:ACV_Z0"))
        {
            pGenerator->m_wACV_Z0 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"z0_idx")).toUInt();
        }

        m_pDMF->RestorePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:ACV_ZZ0"))
        {
            pGenerator->m_wACV_ZZ0 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"zz0_idx")).toUInt();
        }

        m_pDMF->RestorePos(L"Generator_Pos");
        if(m_pDMF->FindChildElem(L"scl:ACC_Id0"))
        {
            pGenerator->m_wACC_Id0 = QString::fromStdWString(m_pDMF->GetChildAttrib(L"id0_idx")).toUInt();
        }

        m_pDMF->RestorePos(L"Generator_Pos");
        while(m_pDMF->FindChildElem(L"scl:AnaChn"))
        {
            pGenerator->m_arAChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }

        m_pDMF->RestorePos(L"Generator_Pos");
        while(m_pDMF->FindChildElem(L"scl:StaChn"))
        {
            pGenerator->m_arDChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }
    }
    return true;
}

bool CDMFReader::readExciter()
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QString strVal;
    while(m_pDMF->FindElem(L"scl:Generator"))
    {
        CEleExciter* pExciter = new CEleExciter();
        m_pCmtdFile->m_arExciter.append(pExciter);

        pExciter->m_wIdx = QString::fromStdWString(m_pDMF->GetAttrib(L"idx")).toUInt();
        strcpy(pExciter->m_chName,gbk->fromUnicode(QString::fromStdWString(m_pDMF->GetAttrib(L"exc_name"))));
        pExciter->m_strSrcRef = QString::fromStdWString(m_pDMF->GetAttrib(L"srcRef"));
        pExciter->m_wGenSID = QString::fromStdWString(m_pDMF->GetAttrib(L"gen_SID")).toUInt();
        strVal = QString::fromStdWString(m_pDMF->GetAttrib(L"type"));
        if(strVal == QString("PRIMARY"))
            pExciter->m_eType = CEleExciter::PRIMARY;
        else/* if(strVal == QString("SLAVE"))*/
            pExciter->m_eType = CEleExciter::SLAVE;
        pExciter->m_fFreq = QString::fromStdWString(m_pDMF->GetAttrib(L"freq")).toFloat();
        pExciter->m_fVRtg = QString::fromStdWString(m_pDMF->GetAttrib(L"VRtg")).toFloat();

        m_pDMF->SavePos(L"Exciter_Pos");
        if(m_pDMF->FindChildElem(L"ACVChn"))
        {
            pExciter->m_wUaIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ua_idx")).toUInt();
            pExciter->m_wUbIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ub_idx")).toUInt();
            pExciter->m_wUcIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"uc_idx")).toUInt();
        }

        m_pDMF->RestorePos(L"Exciter_Pos");
        if(m_pDMF->FindChildElem(L"scl:ACCChn"))
        {
            pExciter->m_wIaIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ia_idx")).toUInt();
            pExciter->m_wIbIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ib_idx")).toUInt();
            pExciter->m_wIcIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ic_idx")).toUInt();
            strVal = QString::fromStdWString(m_pDMF->GetChildAttrib(L"dir"));
            if(strVal == QString("POS"))
                pExciter->m_eDirI = CEleExciter::dir_POS;
            else if(strVal == QString("NEG"))
                pExciter->m_eDirI = CEleExciter::dir_NEG;
            else
                pExciter->m_eDirI = CEleExciter::dir_UNC;
        }

        m_pDMF->RestorePos(L"Exciter_Pos");
        if(m_pDMF->FindChildElem(L"scl:ACCZChn"))
        {
            pExciter->m_wZIaIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ia_idx")).toUInt();
            pExciter->m_wZIbIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ib_idx")).toUInt();
            pExciter->m_wZIcIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ic_idx")).toUInt();
            strVal = QString::fromStdWString(m_pDMF->GetChildAttrib(L"dir"));
            if(strVal == QString("POS"))
                pExciter->m_eDirZ = CEleExciter::dir_POS;
            else if(strVal == QString("NEG"))
                pExciter->m_eDirZ = CEleExciter::dir_NEG;
            else
                pExciter->m_eDirZ = CEleExciter::dir_UNC;
        }

        m_pDMF->RestorePos(L"Exciter_Pos");
        while(m_pDMF->FindChildElem(L"scl:AnaChn"))
        {
            pExciter->m_arAChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }

        m_pDMF->RestorePos(L"Exciter_Pos");
        while(m_pDMF->FindChildElem(L"scl:StaChn"))
        {
            pExciter->m_arDChanel.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"idx_cfg")).toUInt());
        }
    }
    return true;
}

bool CDMFReader::readWinding(CEleTrans *pTrans)
{
    QString strVal;
    CEleTransWiding* pWiding = new CEleTransWiding();
    pTrans->m_arWiding.append(pWiding);
    strVal = QString::fromStdWString(m_pDMF->GetChildAttrib(L"location"));
    if(strVal == QString("High"))
        pWiding->m_eLocation = CEleTransWiding::High;
    else if(strVal == QString("Medium"))
        pWiding->m_eLocation = CEleTransWiding::Medium;
    else if(strVal == QString("Low"))
        pWiding->m_eLocation = CEleTransWiding::Low;
    else
        pWiding->m_eLocation = CEleTransWiding::Common;
    pWiding->m_strSrcRef = QString::fromStdWString(m_pDMF->GetChildAttrib(L"srcRef"));
    pWiding->m_fVRtg = QString::fromStdWString(m_pDMF->GetChildAttrib(L"VRtg")).toFloat();
    pWiding->m_fARtg = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ARtg")).toFloat();
    strVal = QString::fromStdWString(m_pDMF->GetChildAttrib(L"wG"));
    if(strVal.indexOf(QString("yn")) >= 0)
    {
        pWiding->m_eWGA= CEleTransWiding::wG_YN;
        strVal.remove(0,2);
        pWiding->m_nWGB = strVal.toInt();
    }
    else if(strVal.indexOf(QString("y")) >= 0)
    {
        pWiding->m_eWGA = CEleTransWiding::wG_Y;
        strVal.remove(0,1);
        pWiding->m_nWGB = strVal.toInt();
    }
    else if(strVal.indexOf(QString("d")) >= 0)
    {
        pWiding->m_eWGA = CEleTransWiding::wG_D;
        strVal.remove(0,1);
        pWiding->m_nWGB = strVal.toInt();
    }
    m_pDMF->IntoElem();
    m_pDMF->SavePos(L"TransWiding_Pos");
    if(m_pDMF->FindChildElem(L"scl:ACVChn"))
    {
        pWiding->m_wUaIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ua_idx")).toUInt();
        pWiding->m_wUbIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"ub_idx")).toUInt();
        pWiding->m_wUcIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"uc_idx")).toUInt();
    }
    m_pDMF->RestorePos(L"TransWiding_Pos");
    while(m_pDMF->FindChildElem(L"scl:ACC_Bran"))
    {
        pWiding->m_arIaIdx.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"ia_idx")).toUInt());
        pWiding->m_arIbIdx.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"ib_idx")).toUInt());
        pWiding->m_arIcIdx.append(QString::fromStdWString(m_pDMF->GetChildAttrib(L"ic_idx")).toUInt());
        strVal = QString::fromStdWString(m_pDMF->GetChildAttrib(L"dir"));
        if(strVal == QString("POS"))
            pWiding->m_arDir.append(CEleTransWiding::dir_POS);
        else if(strVal == QString("NEG"))
            pWiding->m_arDir.append(CEleTransWiding::dir_NEG);
        else/* if(strVal == QString("UNC"))*/
            pWiding->m_arDir.append(CEleTransWiding::dir_UNC);
    }
    if(m_pDMF->FindChildElem(L"scl:Igap"))
    {
        pWiding->m_wZgapIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"zgap_idx")).toUInt();
        pWiding->m_wZsgapIdx = QString::fromStdWString(m_pDMF->GetChildAttrib(L"zsgap_idx")).toUInt();
    }
    m_pDMF->OutOfElem();
    return true;
}

bool CDMFReader::writeAChanel()
{
    int i = 0;
    for(i=0; i<m_pCmtdFile->m_nACount; i++)
    {
        CEleAChanel* pChanel = m_pCmtdFile->m_arAChanel[i];
        m_pDMF->AddElem(L"scl:AnalogChannel");
        m_pDMF->SetAttrib(L"idx_cfg",pChanel->m_wID);
        m_pDMF->SetAttrib(L"idx_org",pChanel->m_wIdxOrg);
        if(pChanel->m_eType == CEleAChanel::type_A)
            m_pDMF->SetAttrib(L"type",L"A");
        else if(pChanel->m_eType == CEleAChanel::type_D)
            m_pDMF->SetAttrib(L"type",L"D");
        else
            m_pDMF->SetAttrib(L"type",L"O");
        if(pChanel->m_eFlag == CEleAChanel::flag_ACV)
            m_pDMF->SetAttrib(L"flag",L"ACV");
        else if(pChanel->m_eFlag == CEleAChanel::flag_ACC)
            m_pDMF->SetAttrib(L"flag",L"ACC");
        else if(pChanel->m_eFlag == CEleAChanel::flag_HF)
            m_pDMF->SetAttrib(L"flag",L"HF");
        else if(pChanel->m_eFlag == CEleAChanel::flag_FQ)
            m_pDMF->SetAttrib(L"flag",L"FQ");
        else if(pChanel->m_eFlag == CEleAChanel::flag_AG)
            m_pDMF->SetAttrib(L"flag",L"AG");
        else if(pChanel->m_eFlag == CEleAChanel::flag_AMP)
            m_pDMF->SetAttrib(L"flag",L"AMP");
        else if(pChanel->m_eFlag == CEleAChanel::flag_PW)
            m_pDMF->SetAttrib(L"flag",L"PW");
        else if(pChanel->m_eFlag == CEleAChanel::flag_ZX)
            m_pDMF->SetAttrib(L"flag",L"ZX");
        else if(pChanel->m_eFlag == CEleAChanel::flag_CONST)
            m_pDMF->SetAttrib(L"flag",L"CONST");
        m_pDMF->SetAttrib(L"p_min",QString("%1").arg(pChanel->m_fPMin,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"p_max",QString("%1").arg(pChanel->m_fPMax,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"s_min",QString("%1").arg(pChanel->m_fSMin,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"s_max",QString("%1").arg(pChanel->m_fSMax,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"freq",QString("%1").arg(pChanel->m_fFreq,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"au",QString("%1").arg(pChanel->m_fAU,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"bu",QString("%1").arg(pChanel->m_fBU,0,'f',6,QChar('0')).toStdWString());
        if(pChanel->m_eSiUnit == CEleAChanel::unit_A)
            m_pDMF->SetAttrib(L"sIUnit",QString("A").toStdWString());
        else if(pChanel->m_eSiUnit == CEleAChanel::unit_V)
            m_pDMF->SetAttrib(L"sIUnit",QString("V").toStdWString());
        else if(pChanel->m_eSiUnit == CEleAChanel::unit_Hz)
            m_pDMF->SetAttrib(L"sIUnit",QString("Hz").toStdWString());
        else if(pChanel->m_eSiUnit == CEleAChanel::unit_O)
            m_pDMF->SetAttrib(L"sIUnit",QString("Ω").toStdWString());
        else if(pChanel->m_eSiUnit == CEleAChanel::unit_W)
            m_pDMF->SetAttrib(L"sIUnit",QString("W").toStdWString());
        else if(pChanel->m_eSiUnit == CEleAChanel::unit_Var)
            m_pDMF->SetAttrib(L"sIUnit",QString("Var").toStdWString());
        else
            m_pDMF->SetAttrib(L"sIUnit",QString("").toStdWString());
        if(pChanel->m_eMultiplier == CEleAChanel::multi_m)
            m_pDMF->SetAttrib(L"multiplier",QString("m").toStdWString());
        else if(pChanel->m_eMultiplier == CEleAChanel::multi_k)
            m_pDMF->SetAttrib(L"multiplier",QString("k").toStdWString());
        else if(pChanel->m_eMultiplier == CEleAChanel::multi_M)
            m_pDMF->SetAttrib(L"multiplier",QString("M").toStdWString());
        else
            m_pDMF->SetAttrib(L"multiplier",QString("").toStdWString());

        m_pDMF->SetAttrib(L"primary",QString("%1").arg(pChanel->m_fPrimary,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"secondary",QString("%1").arg(pChanel->m_fSecondary,0,'f',6,QChar('0')).toStdWString());

        if(pChanel->m_ePS == CEleAChanel::ps_P)
            m_pDMF->SetAttrib(L"ps",QString("P").toStdWString());
        else
            m_pDMF->SetAttrib(L"ps",QString("S").toStdWString());
    }
    return true;
}

bool CDMFReader::writeDChanel()
{
    int i = 0;
    for(i=0; i<m_pCmtdFile->m_nDCount; i++)
    {
        CEleDChanel* pChanel = m_pCmtdFile->m_arDChanel[i];
        m_pDMF->AddElem(L"scl:StatusChannel");
        m_pDMF->SetAttrib(L"idx_cfg",pChanel->m_wID);
        m_pDMF->SetAttrib(L"idx_org",pChanel->m_wIdxOrg);
        if(pChanel->m_eType == CEleDChanel::Relay)
            m_pDMF->SetAttrib(L"type",QString("Relay").toStdWString());
        else if(pChanel->m_eType == CEleDChanel::Breaker)
            m_pDMF->SetAttrib(L"type",QString("Breaker").toStdWString());
        else if(pChanel->m_eType == CEleDChanel::Switch)
            m_pDMF->SetAttrib(L"type",QString("Switch").toStdWString());
        else if(pChanel->m_eType == CEleDChanel::Warning)
            m_pDMF->SetAttrib(L"type",QString("Warning").toStdWString());
        else/* if(pChanel->m_eType == CEleDChanel::Other)*/
            m_pDMF->SetAttrib(L"type",QString("Other").toStdWString());

        m_pDMF->SetAttrib(L"flag",pChanel->m_strFlag.toStdWString());
        if(pChanel->m_eContact == CEleDChanel::NormallyOpen)
            m_pDMF->SetAttrib(L"contact",QString("NormallyOpen").toStdWString());
        else
            m_pDMF->SetAttrib(L"contact",QString("NormallyClosed").toStdWString());
        m_pDMF->SetAttrib(L"srcRef",pChanel->m_strSrcRef.toStdWString());
    }
    return true;
}

bool CDMFReader::writeBus()
{
    int i = 0;
    int j = 0;
    CEleBus* pBus = NULL;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    for(i=0; i<m_pCmtdFile->m_arBus.count(); i++)
    {
        pBus = m_pCmtdFile->m_arBus.at(i);
        m_pDMF->AddElem(L"scl:Bus");
        m_pDMF->SetAttrib(L"idx",pBus->m_wID);
        m_pDMF->SetAttrib(L"bus_name",gbk->toUnicode(pBus->m_chName).toStdWString());
        m_pDMF->SetAttrib(L"srcRef",pBus->m_strSrcRef.toStdWString());

        m_pDMF->SetAttrib(L"VRtg",QString("%1").arg(pBus->m_fVrtg,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"VRtgSnd",QString("%1").arg(pBus->m_fVrtgSnd,0,'f',6,QChar('0')).toStdWString());
        if(pBus->m_eTvPos == CEleBus::e_tv_bus)
            m_pDMF->SetAttrib(L"VRtgSnd_Pos",QString("BUS").toStdWString());
        else if(pBus->m_eTvPos == CEleBus::e_tv_line)
            m_pDMF->SetAttrib(L"VRtgSnd_Pos",QString("LINE").toStdWString());
        else
            m_pDMF->SetAttrib(L"VRtgSnd_Pos",QString("BUS").toStdWString());

        m_pDMF->AddChildElem(L"scl:ACVChn");
        m_pDMF->SetChildAttrib(L"ua_idx",pBus->m_wAID);
        m_pDMF->SetChildAttrib(L"ub_idx",pBus->m_wBID);
        m_pDMF->SetChildAttrib(L"uc_idx",pBus->m_wCID);
        m_pDMF->SetChildAttrib(L"un_idx",pBus->m_wNID);
        m_pDMF->SetChildAttrib(L"ul_idx",pBus->m_wLID);

        for(j=0; j<pBus->m_arAChanel.count(); j++)
        {
            m_pDMF->AddChildElem(L"scl:AnaChn");
            m_pDMF->SetChildAttrib(L"idx_cfg",pBus->m_arAChanel[j]);
        }

        for(j=0; j<pBus->m_arDChanel.count(); j++)
        {
            m_pDMF->AddChildElem(L"scl:StaChn");
            m_pDMF->SetChildAttrib(L"idx_cfg",pBus->m_arDChanel[j]);
        }
    }
    //delete gbk;
    return true;
}

bool CDMFReader::writeLine()
{
    int i = 0;
    int j = 0;
    CEleLine* pLine = NULL;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    for(i=0; i<m_pCmtdFile->m_arLine.count(); i++)
    {
        pLine = m_pCmtdFile->m_arLine.at(i);
        m_pDMF->AddElem(L"scl:Line");
        m_pDMF->SetAttrib(L"idx",pLine->m_wID);
        m_pDMF->SetAttrib(L"line_name",gbk->toUnicode(pLine->m_chName).toStdWString());
        m_pDMF->SetAttrib(L"bus_ID",pLine->m_wBusId);
        m_pDMF->SetAttrib(L"other_ID",pLine->m_nHgLine);
        m_pDMF->SetAttrib(L"srcRef",pLine->m_strSrcRef.toStdWString());
        m_pDMF->SetAttrib(L"VRtg",QString("%1").arg(pLine->m_dVoltage,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"ARtg",QString("%1").arg(pLine->m_fArtg,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"ARtgSnd",QString("%1").arg(pLine->m_dMaxI,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"LinLen",QString("%1").arg(pLine->m_dLength,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"bran_num",pLine->m_nBranNum);

        m_pDMF->AddChildElem(L"scl:RX");
        m_pDMF->SetChildAttrib(L"r1",QString("%1").arg(pLine->m_dR1,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetChildAttrib(L"x1",QString("%1").arg(pLine->m_dX1,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetChildAttrib(L"r0",QString("%1").arg(pLine->m_dR0,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetChildAttrib(L"x0",QString("%1").arg(pLine->m_dX0,0,'f',6,QChar('0')).toStdWString());

        m_pDMF->AddChildElem(L"scl:CG");
        m_pDMF->SetChildAttrib(L"c1",QString("%1").arg(pLine->m_fC1,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetChildAttrib(L"c0",QString("%1").arg(pLine->m_fC0,0,'f',6,QChar('0')).toStdWString());

        m_pDMF->AddChildElem(L"scl:MR");
        m_pDMF->SetChildAttrib(L"idx",pLine->m_nHgLine);
        m_pDMF->SetChildAttrib(L"mr0",QString("%1").arg(pLine->m_dRh,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetChildAttrib(L"mx0",QString("%1").arg(pLine->m_dXh,0,'f',6,QChar('0')).toStdWString());

        m_pDMF->AddChildElem(L"scl:PX");
        m_pDMF->SetChildAttrib(L"px",QString("%1").arg(pLine->m_fPx1,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetChildAttrib(L"px0",QString("%1").arg(pLine->m_fPx0,0,'f',6,QChar('0')).toStdWString());

        m_pDMF->AddChildElem(L"scl:ACC_Bran");
        m_pDMF->SetChildAttrib(L"bran_idx",L"1");
        m_pDMF->SetChildAttrib(L"ia_idx",pLine->m_wAID);
        m_pDMF->SetChildAttrib(L"ib_idx",pLine->m_wBID);
        m_pDMF->SetChildAttrib(L"ic_idx",pLine->m_wCID);
        m_pDMF->SetChildAttrib(L"in_idx",pLine->m_wNID);
        if(pLine->m_eDir1 == CEleLine::dir_POS)
            m_pDMF->SetChildAttrib(L"dir",L"POS");
        else if(pLine->m_eDir1 == CEleLine::dir_NEG)
            m_pDMF->SetChildAttrib(L"dir",L"NEG");
        else if(pLine->m_eDir1 == CEleLine::dir_UNC)
            m_pDMF->SetChildAttrib(L"dir",L"UNC");
        else
            m_pDMF->SetChildAttrib(L"dir",L"UNC");

        if(pLine->m_nBranNum == 2)
        {
            m_pDMF->AddChildElem(L"scl:ACC_Bran");
            m_pDMF->SetChildAttrib(L"bran_idx",L"2");
            m_pDMF->SetChildAttrib(L"ia_idx",pLine->m_wAID2);
            m_pDMF->SetChildAttrib(L"ib_idx",pLine->m_wBID2);
            m_pDMF->SetChildAttrib(L"ic_idx",pLine->m_wCID2);
            m_pDMF->SetChildAttrib(L"in_idx",pLine->m_wNID2);
            if(pLine->m_eDir2 == CEleLine::dir_POS)
                m_pDMF->SetChildAttrib(L"dir",L"POS");
            else if(pLine->m_eDir2 == CEleLine::dir_NEG)
                m_pDMF->SetChildAttrib(L"dir",L"NEG");
            else if(pLine->m_eDir2 == CEleLine::dir_UNC)
                m_pDMF->SetChildAttrib(L"dir",L"UNC");
            else
                m_pDMF->SetChildAttrib(L"dir",L"UNC");
        }

        for(j=0; j<pLine->m_arAChanel.count(); j++)
        {
            m_pDMF->AddChildElem(L"scl:AnaChn");
            m_pDMF->SetChildAttrib(L"idx_cfg",pLine->m_arAChanel[j]);
        }

        for(j=0; j<pLine->m_arDChanel.count(); j++)
        {
            m_pDMF->AddChildElem(L"scl:StaChn");
            m_pDMF->SetChildAttrib(L"idx_cfg",pLine->m_arDChanel[j]);
        }
    }
    //delete gbk;
    return true;
}

bool CDMFReader::writeTrans()
{
    int i = 0;
    int j = 0;
    int n = 0;
    CEleTrans* pTrans = NULL;
    CEleTransWiding* pWiding = NULL;
    QString strVal;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    for(i=0; i<m_pCmtdFile->m_arTrans.count(); i++)
    {
        pTrans = m_pCmtdFile->m_arTrans.at(i);
        m_pDMF->AddElem(L"scl:Transformer");
        m_pDMF->SetAttrib(L"idx",pTrans->m_wID);
        m_pDMF->SetAttrib(L"trm_name",gbk->toUnicode(pTrans->m_chName).toStdWString());
        m_pDMF->SetAttrib(L"srcRef",pTrans->m_strSrcRef.toStdWString());
        m_pDMF->SetAttrib(L"pwrRtg",QString("%1").arg(pTrans->m_fPwrRtg,0,'f',6,QChar('0')).toStdWString());

        for(j=0; j<pTrans->m_arWiding.count(); j++)
        {
            pWiding = pTrans->m_arWiding.at(j);
            m_pDMF->AddChildElem(L"scl:TransformerWinding");
            m_pDMF->IntoElem();
            if(pWiding->m_eLocation == CEleTransWiding::High)
                m_pDMF->SetAttrib(L"location",L"High");
            else if(pWiding->m_eLocation == CEleTransWiding::Medium)
                m_pDMF->SetAttrib(L"location",L"Medium");
            else if(pWiding->m_eLocation == CEleTransWiding::Low)
                m_pDMF->SetAttrib(L"location",L"Low");
            else if(pWiding->m_eLocation == CEleTransWiding::Common)
                m_pDMF->SetAttrib(L"location",L"Common");
            else
                m_pDMF->SetAttrib(L"location",L"Common");

            m_pDMF->SetAttrib(L"srcRef",pWiding->m_strSrcRef.toStdWString());
            m_pDMF->SetAttrib(L"VRtg",QString("%1").arg(pWiding->m_fVRtg,0,'f',6,QChar('0')).toStdWString());
            m_pDMF->SetAttrib(L"ARtg",QString("%1").arg(pWiding->m_fARtg,0,'f',6,QChar('0')).toStdWString());
            m_pDMF->SetAttrib(L"bran_num",pWiding->m_nBranNum);
            if(pWiding->m_eWGA == CEleTransWiding::wG_Y)
                strVal = QString("y");
            else if(pWiding->m_eWGA == CEleTransWiding::wG_YN)
                strVal = QString("yn");
            else if(pWiding->m_eWGA == CEleTransWiding::wG_D)
                strVal = QString("d");
            else
                strVal = QString("y");
            strVal += QString("%1").arg(pWiding->m_nWGB);
            m_pDMF->SetAttrib(L"wG",strVal.toStdWString());

            m_pDMF->AddChildElem(L"scl:ACVChn");
            m_pDMF->SetChildAttrib(L"ua_idx",pWiding->m_wUaIdx);
            m_pDMF->SetChildAttrib(L"ub_idx",pWiding->m_wUbIdx);
            m_pDMF->SetChildAttrib(L"uc_idx",pWiding->m_wUcIdx);

            for(n=0; n<pWiding->m_arIaIdx.count(); n++)
            {
                m_pDMF->AddChildElem(L"scl:ACC_Bran");
                m_pDMF->SetChildAttrib(L"bran_idx",n+1);
                m_pDMF->SetChildAttrib(L"ia_idx",pWiding->m_arIaIdx.at(n));
                m_pDMF->SetChildAttrib(L"ib_idx",pWiding->m_arIbIdx.at(n));
                m_pDMF->SetChildAttrib(L"ic_idx",pWiding->m_arIcIdx.at(n));
                if(pWiding->m_arDir[n] == CEleTransWiding::dir_POS)
                    m_pDMF->SetChildAttrib(L"dir",L"POS");
                else if(pWiding->m_arDir[n] == CEleTransWiding::dir_NEG)
                    m_pDMF->SetChildAttrib(L"dir",L"NEG");
                else if(pWiding->m_arDir[n] == CEleTransWiding::dir_UNC)
                    m_pDMF->SetChildAttrib(L"dir",L"UNC");
                else
                    m_pDMF->SetChildAttrib(L"dir",L"UNC");
            }
            m_pDMF->AddChildElem(L"scl:Igap");
            m_pDMF->SetChildAttrib(L"zgap_idx",pWiding->m_wZgapIdx);
            m_pDMF->SetChildAttrib(L"zsgap_idx",pWiding->m_wZsgapIdx);

            m_pDMF->OutOfElem();
        }
        for(j=0; j<pTrans->m_arAChanel.count(); j++)
        {
            m_pDMF->AddChildElem(L"scl:AnaChn");
            m_pDMF->SetChildAttrib(L"idx_cfg",pTrans->m_arAChanel[j]);
        }

        for(j=0; j<pTrans->m_arDChanel.count(); j++)
        {
            m_pDMF->AddChildElem(L"scl:StaChn");
            m_pDMF->SetChildAttrib(L"idx_cfg",pTrans->m_arDChanel[j]);
        }
    }

    //delete gbk;
    return true;
}

bool CDMFReader::writeGenerator()
{
    int i = 0;
    int j = 0;
    CEleGenerator* pGenerator = NULL;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    for(i=0; i<m_pCmtdFile->m_arGenerator.count(); i++)
    {
        pGenerator = m_pCmtdFile->m_arGenerator.at(i);
        m_pDMF->AddElem(L"scl:Generator");
        m_pDMF->SetAttrib(L"idx",pGenerator->m_wID);
        m_pDMF->SetAttrib(L"gen_name",gbk->toUnicode(pGenerator->m_chName).toStdWString());
        m_pDMF->SetAttrib(L"srcRef",pGenerator->m_strSrcRef.toStdWString());
        m_pDMF->SetAttrib(L"trm_SID",pGenerator->m_wTrmSID);
        if(pGenerator->m_eType == CEleGenerator::STEAM_TURBINE)
            m_pDMF->SetAttrib(L"type",L"STEAM_TURBINE");
        else if(pGenerator->m_eType == CEleGenerator::WATER_TURBINE)
            m_pDMF->SetAttrib(L"type",L"WATER_TURBINE");
        else
            m_pDMF->SetAttrib(L"type",L"STEAM_TURBINE");
        m_pDMF->SetAttrib(L"freq",QString("%1").arg(pGenerator->m_fFreq,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"capacity",QString("%1").arg(pGenerator->m_fCapacity,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"factor",QString("%1").arg(pGenerator->m_fFactor,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"VRtg",QString("%1").arg(pGenerator->m_fVRtg,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"rotor_I",QString("%1").arg(pGenerator->m_fRotorI,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"rotor_V2",QString("%1").arg(pGenerator->m_fRotorV2,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"neut_group_num",pGenerator->m_nNeutGroupNum);
        m_pDMF->SetAttrib(L"exciter_Mode",pGenerator->m_nExciterMode);
        m_pDMF->SetAttrib(L"igt_Dir",pGenerator->m_nIgtDir);

        m_pDMF->AddChildElem(L"scl:Ufe");
        m_pDMF->SetChildAttrib(L"Ufe",QString("%1").arg(pGenerator->m_fUfe,0,'f',6,QChar('0')).toStdWString());

        m_pDMF->AddChildElem(L"scl:X");
        m_pDMF->SetChildAttrib(L"xd",QString("%1").arg(pGenerator->m_fXd,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetChildAttrib(L"xq",QString("%1").arg(pGenerator->m_fXq,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetChildAttrib(L"xd1",QString("%1").arg(pGenerator->m_fXd1,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetChildAttrib(L"xs",QString("%1").arg(pGenerator->m_fXs,0,'f',6,QChar('0')).toStdWString());

        m_pDMF->AddChildElem(L"scl:ACCChn");
        m_pDMF->SetChildAttrib(L"ia_idx",pGenerator->m_wIAID);
        m_pDMF->SetChildAttrib(L"ib_idx",pGenerator->m_wIBID);
        m_pDMF->SetChildAttrib(L"ic_idx",pGenerator->m_wICID);
        if(pGenerator->m_eDirA == CEleGenerator::dir_POS)
            m_pDMF->SetChildAttrib(L"dir",L"POS");
        else if(pGenerator->m_eDirA == CEleGenerator::dir_NEG)
            m_pDMF->SetChildAttrib(L"dir",L"NEG");
        else/* if(pGenerator->m_eDirA == CEleGenerator::dir_UNC)*/
            m_pDMF->SetChildAttrib(L"dir",L"UNC");

        m_pDMF->AddChildElem(L"scl:ACCZChn");
        m_pDMF->SetChildAttrib(L"ia_idx",pGenerator->m_wZAID);
        m_pDMF->SetChildAttrib(L"ib_idx",pGenerator->m_wZBID);
        m_pDMF->SetChildAttrib(L"ic_idx",pGenerator->m_wZCID);
        if(pGenerator->m_eDirZ == CEleGenerator::dir_POS)
            m_pDMF->SetChildAttrib(L"dir",L"POS");
        else if(pGenerator->m_eDirZ == CEleGenerator::dir_NEG)
            m_pDMF->SetChildAttrib(L"dir",L"NEG");
        else/* if(pGenerator->m_eDirZ == CEleGenerator::dir_UNC)*/
            m_pDMF->SetChildAttrib(L"dir",L"UNC");

        m_pDMF->AddChildElem(L"scl:ACVChn");
        m_pDMF->SetChildAttrib(L"ua_idx",pGenerator->m_wUAID);
        m_pDMF->SetChildAttrib(L"ub_idx",pGenerator->m_wUBID);
        m_pDMF->SetChildAttrib(L"uc_idx",pGenerator->m_wUCID);

        for(j=0; j<pGenerator->m_arNeutIa.count(); j++)
        {
            m_pDMF->AddChildElem(L"scl:NeutGroup");
            m_pDMF->SetChildAttrib(L"group_idx",j+1);
            m_pDMF->SetChildAttrib(L"bran_num",pGenerator->m_arNeutBranNum[j]);
            m_pDMF->SetChildAttrib(L"ia_idx",pGenerator->m_arNeutIa[j]);
            m_pDMF->SetChildAttrib(L"ib_idx",pGenerator->m_arNeutIb[j]);
            m_pDMF->SetChildAttrib(L"ic_idx",pGenerator->m_arNeutIc[j]);
            if(pGenerator->m_arDir[j] == CEleGenerator::dir_POS)
                m_pDMF->SetChildAttrib(L"dir",L"POS");
            else if(pGenerator->m_arDir[j] == CEleGenerator::dir_NEG)
                m_pDMF->SetChildAttrib(L"dir",L"NEG");
            else/* if(pGenerator->m_arDir[j] == CEleGenerator::dir_UNC)*/
                m_pDMF->SetChildAttrib(L"dir",L"UNC");

            m_pDMF->AddChildElem(L"scl:Ufe_Chns");
            m_pDMF->SetChildAttrib(L"ufe_idx",pGenerator->m_wUfe);
            m_pDMF->SetChildAttrib(L"posufe_idx",pGenerator->m_wPosUfe);
            m_pDMF->SetChildAttrib(L"negufe_idx",pGenerator->m_wNegUfe);

            m_pDMF->AddChildElem(L"scl:Ife_Chn");
            m_pDMF->SetChildAttrib(L"Ife",pGenerator->m_wIfe);

            m_pDMF->AddChildElem(L"scl:ACV_Z0");
            m_pDMF->SetChildAttrib(L"z0_idx",pGenerator->m_wACV_Z0);

            m_pDMF->AddChildElem(L"scl:ACV_ZZ0");
            m_pDMF->SetChildAttrib(L"zz0_idx",pGenerator->m_wACV_ZZ0);

            m_pDMF->AddChildElem(L"scl:ACC_Id0");
            m_pDMF->SetChildAttrib(L"id0_idx",pGenerator->m_wACC_Id0);

            for(j=0; j<pGenerator->m_arAChanel.count(); j++)
            {
                m_pDMF->AddChildElem(L"scl:AnaChn");
                m_pDMF->SetChildAttrib(L"idx_cfg",pGenerator->m_arAChanel[j]);
            }

            for(j=0; j<pGenerator->m_arDChanel.count(); j++)
            {
                m_pDMF->AddChildElem(L"scl:StaChn");
                m_pDMF->SetChildAttrib(L"idx_cfg",pGenerator->m_arDChanel[j]);
            }
        }
    }
    //delete gbk;
    return true;
}

bool CDMFReader::writeExciter()
{
    int i = 0;
    int j = 0;
    CEleExciter* pExciter = NULL;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    for(i=0; i<m_pCmtdFile->m_arExciter.count(); i++)
    {
        pExciter = m_pCmtdFile->m_arExciter.at(i);
        m_pDMF->AddElem(L"scl:Exciter");
        m_pDMF->SetAttrib(L"idx",pExciter->m_wIdx);
        m_pDMF->SetAttrib(L"exc_name",gbk->toUnicode(pExciter->m_chName).toStdWString());
        m_pDMF->SetAttrib(L"srcRef",pExciter->m_strSrcRef.toStdWString());
        m_pDMF->SetAttrib(L"gen_SID",pExciter->m_wGenSID);
        if(pExciter->m_eType == CEleExciter::PRIMARY)
            m_pDMF->SetAttrib(L"type",L"PRIMARY");
        else if(pExciter->m_eType == CEleExciter::PRIMARY)
            m_pDMF->SetAttrib(L"type",L"SLAVE");
        else
            m_pDMF->SetAttrib(L"type",L"PRIMARY");
        m_pDMF->SetAttrib(L"freq",QString("%1").arg(pExciter->m_fFreq,0,'f',6,QChar('0')).toStdWString());
        m_pDMF->SetAttrib(L"VRtg",QString("%1").arg(pExciter->m_fVRtg,0,'f',6,QChar('0')).toStdWString());

        m_pDMF->AddChildElem(L"scl:ACVChn");
        m_pDMF->SetChildAttrib(L"ua_idx",pExciter->m_wUaIdx);
        m_pDMF->SetChildAttrib(L"ub_idx",pExciter->m_wUbIdx);
        m_pDMF->SetChildAttrib(L"uc_idx",pExciter->m_wUcIdx);

        m_pDMF->AddChildElem(L"scl:ACCChn");
        m_pDMF->SetChildAttrib(L"ia_idx",pExciter->m_wIaIdx);
        m_pDMF->SetChildAttrib(L"ib_idx",pExciter->m_wIbIdx);
        m_pDMF->SetChildAttrib(L"ic_idx",pExciter->m_wIcIdx);
        if(pExciter->m_eDirI == CEleExciter::dir_POS)
            m_pDMF->SetChildAttrib(L"dir",L"POS");
        else if(pExciter->m_eDirI == CEleExciter::dir_NEG)
            m_pDMF->SetChildAttrib(L"dir",L"NEG");
        else/* if(pExciter->m_eDirI == CEleExciter::dir_UNC)*/
            m_pDMF->SetChildAttrib(L"dir",L"UNC");

        m_pDMF->AddChildElem(L"scl:ACCZChn");
        m_pDMF->SetChildAttrib(L"ia_idx",pExciter->m_wZIaIdx);
        m_pDMF->SetChildAttrib(L"ib_idx",pExciter->m_wZIbIdx);
        m_pDMF->SetChildAttrib(L"ic_idx",pExciter->m_wZIcIdx);
        if(pExciter->m_eDirZ == CEleExciter::dir_POS)
            m_pDMF->SetChildAttrib(L"dir",L"POS");
        else if(pExciter->m_eDirZ == CEleExciter::dir_NEG)
            m_pDMF->SetChildAttrib(L"dir",L"NEG");
        else/* if(pExciter->m_eDirZ == CEleExciter::dir_UNC)*/
            m_pDMF->SetChildAttrib(L"dir",L"UNC");

        for(j=0; j<pExciter->m_arAChanel.count(); j++)
        {
            m_pDMF->AddChildElem(L"scl:AnaChn");
            m_pDMF->SetChildAttrib(L"idx_cfg",pExciter->m_arAChanel[j]);
        }

        for(j=0; j<pExciter->m_arDChanel.count(); j++)
        {
            m_pDMF->AddChildElem(L"scl:StaChn");
            m_pDMF->SetChildAttrib(L"idx_cfg",pExciter->m_arDChanel[j]);
        }
    }

    //delete gbk;
    return true;
}

