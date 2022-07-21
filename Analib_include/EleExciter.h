////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: EleExciter
// Copyright 2016 gdwy
// Created : 2016/5/23 by
// History :
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ELEEXCITER_H
#define ELEEXCITER_H
#include <QString>
#include "VarDef.h"
#include <QVector>

class CEleExciter
{
public:
    CEleExciter();
    virtual ~CEleExciter();
public:
    enum e_type
    {
        PRIMARY = 1,    //主励磁机
        SLAVE = 2       //副励磁机
    };
    enum e_dir
    {
        dir_POS = 1,        //正方向
        dir_NEG = 2,        //反方向
        dir_UNC = 3         //不清楚方向
    };
    uint m_wIdx;
    char m_chName[MAX_CHANELNAME_LENGTH];
    QString m_strSrcRef;
    uint m_wGenSID;

    e_type m_eType;
    float m_fFreq;
    float m_fVRtg;
    uint m_wUaIdx,m_wUbIdx,m_wUcIdx;    //机端电压
    uint m_wIaIdx,m_wIbIdx,m_wIcIdx;    //机端电流
    e_dir m_eDirI;
    uint m_wZIaIdx,m_wZIbIdx,m_wZIcIdx; //中性点电流
    e_dir m_eDirZ;
    QVector<uint> m_arAChanel;
    QVector<uint> m_arDChanel;
};

#endif // ELEEXCITER_H
