////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:
// Copyright 2016 gdwy
// Created : 2016/5/10 by Jerry
// History :
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ELEGENERATOR_H
#define ELEGENERATOR_H
#include <QString>
#include "VarDef.h"
#include <QVector>

class CEleGenerator
{
public:
    CEleGenerator();
    virtual ~CEleGenerator();
public:
    enum e_type
    {
        STEAM_TURBINE = 1,  //汽轮机
        WATER_TURBINE = 2   //水轮机
    };
    enum e_dir
    {
        dir_POS = 1,
        dir_NEG = 2,
        dir_UNC = 3
    };
    uint m_wID;
    char m_chName[MAX_CHANELNAME_LENGTH];
    QString m_strSrcRef;
    uint m_wTrmSID;
    e_type m_eType;
    float m_fFreq;          //额定频率
    float m_fCapacity;      //额定容量
    float m_fFactor;        //功率因数
    float m_fVRtg;
    float m_fRotorI;
    float m_fRotorV2;
    uint m_nNeutGroupNum;
    int m_nExciterMode;     //0=励磁变；1=励磁机；2=励磁变+励磁机
    int m_nIgtDir;          //0=流出发电机；1=流入发电机。
    float m_fUfe;
    float m_fXd,m_fXq,m_fXd1,m_fXs; //xd=纵轴同步电抗；xq=交轴同步电抗；xd1=暂态纵轴同步电抗；xs=系统联系电抗.
    uint m_wIAID,m_wIBID,m_wICID;   //机端电流
    e_dir m_eDirA;
    uint m_wZAID,m_wZBID,m_wZCID;    //中性点电流
    e_dir m_eDirZ;
    uint m_wUAID,m_wUBID,m_wUCID;   //机端电压
    QVector<uint> m_arNeutBranNum;  //中性点分支组
    QVector<uint> m_arNeutIa;
    QVector<uint> m_arNeutIb;
    QVector<uint> m_arNeutIc;
    QVector<e_dir> m_arDir;

    uint m_wUfe;                    //励磁电压
    uint m_wPosUfe;                 //正对地励磁电压
    uint m_wNegUfe;                 //负对地励磁电压
    uint m_wIfe;                    //励磁电流
    uint m_wACV_Z0;                 //中性点零序电压通道
    uint m_wACV_ZZ0;                //纵向零序电压通道
    uint m_wACC_Id0;                //零序横差电流通道
    QVector<uint> m_arAChanel;
    QVector<uint> m_arDChanel;
};

#endif // ELEGENERATOR_H

