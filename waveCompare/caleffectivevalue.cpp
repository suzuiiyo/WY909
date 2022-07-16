#include <caleffectivevalue.h>
#include <qmath.h>
#include <algorithm>
#include <QDebug>

CalEffectiveValue::CalEffectiveValue(const QList<QVector<float>>& varList, int varPoint1, int varPoint2):
        wyCal(new CWyCal())
      , t_wavePoint1(varPoint1)
      , t_wavePoint2(varPoint2)
      , chopBefore1zhou(varList.at(0))
      , chopAfter1zhou(varList.at(1))
      , chopBefore1zhou2(varList.at(2))
      , chopAfter1zhou2(varList.at(3))
{
}

CalEffectiveValue::~CalEffectiveValue()
{
    if(wyCal!=nullptr){
        delete wyCal;
    }
}

QVector<float> CalEffectiveValue::calEffValueBefore(QVector<float> varList, int pointNum)
{
    QVector<float> uEffVector;
    QVector<float> uCalVector;
    //计算前一个周波的有效值就要取两个周波的采样值
    float* p_data = new float[2*pointNum];
    for(int i=0; i<2*pointNum; i++){
       uCalVector.append(varList.at(i));
    }

    //将值放到p_data里
    if(!uCalVector.empty()){
        memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof(float));
    }

    //每一个点的采样值,往后推一个周波
    for(int i=0; i<pointNum + 1; i++){
       float fp = 0;
       float rms = wyCal->DFT_Rms(p_data+i, pointNum, fp);

       if(rms < 0.01){
           uEffVector.append(0.0);
       }else{
           uEffVector.append(rms);
       }
    }

    return uEffVector;
}

QVector<float> CalEffectiveValue::calEffValueAfter(QVector<float> varList, int pointNum)
{
    QVector<float> uEffVector;
    QVector<float> uCalVector;
    //计算后五个周波的有效值就要取后六个周波的采样值
    float* p_data = new float[6*pointNum];
    for(int i=pointNum; i<7*pointNum; i++){
       uCalVector.append(varList.at(i));
    }

    //将值放到p_data里
    if(!uCalVector.empty()){
       memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof(float));
    }

    //每一个点的有效值,往后推一个周波
    for(int i=0; i<5*pointNum + 1; i++){
        float fp =0;
        float rms = wyCal->DFT_Rms(p_data+i, pointNum, fp);

        if(rms<0.01){
            uEffVector.append(0.0);
        }else{
            uEffVector.append(rms);
        }
    }

    return uEffVector;
}

QList<QVector<float>> CalEffectiveValue::getEffectiveValueList()
{
    QList<QVector<float>> effectiveValueList;
    QVector<float> chopTotal1zhou = chopBefore1zhou;
    QVector<float> chopTotal1zhou2 = chopBefore1zhou2;
    chopTotal1zhou.append(chopAfter1zhou);
    chopTotal1zhou2.append(chopAfter1zhou2);

    QVector<float> chopBeforeEffect1zhou = calEffValueBefore(chopTotal1zhou, t_wavePoint1);
    QVector<float> chopBeforeEffect1zhou2 = calEffValueBefore(chopTotal1zhou2, t_wavePoint2);
    QVector<float> chopAfterEffect1zhou = calEffValueAfter(chopTotal1zhou, t_wavePoint1);
    QVector<float> chopAfterEffect1zhou2 = calEffValueAfter(chopTotal1zhou2, t_wavePoint2);

    effectiveValueList << chopBeforeEffect1zhou
                       << chopAfterEffect1zhou
                       << chopBeforeEffect1zhou2
                       << chopAfterEffect1zhou2;

    return effectiveValueList;
}
