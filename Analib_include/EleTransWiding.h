////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:
// Copyright 2016 gdwy
// Created : 2016/5/10 by Jerry
// History :
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CELETRANSWIDING_H
#define CELETRANSWIDING_H
#include <QString>
#include <QVector>

class CEleTransWiding
{
public:
    CEleTransWiding();
    virtual ~CEleTransWiding();
public:
    enum e_dir
    {
        dir_POS = 1,
        dir_NEG = 2,
        dir_UNC = 3
    };
    enum e_location
    {
        High = 1,
        Medium = 2,
        Low = 3,
        Common = 4
    };
    enum e_WGA
    {
        wG_Y = 1,
        wG_YN = 2,
        wG_D = 3
    };
    e_location m_eLocation;
    QString m_strSrcRef;
    float m_fVRtg;                      //一次额定电压(kV)
    float m_fARtg;                      //一次额定电流(A)
    int m_nBranNum;                     //卷电流分支数

    uint m_wUaIdx,m_wUbIdx,m_wUcIdx;    //电压通道号
    QVector<uint> m_arIaIdx;            //电流通道号
    QVector<uint> m_arIbIdx;
    QVector<uint> m_arIcIdx;
    QVector<int> m_arDir;

    uint m_wZgapIdx;                     //中性点直接接地电流的通道号
    uint m_wZsgapIdx;                    //中性点经间隙接地电流的通道号
    e_WGA m_eWGA;                        //Y、Yn、D
    int m_nWGB;                          //0~12
};

#endif // CELETRANSWIDING_H
