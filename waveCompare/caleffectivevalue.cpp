#include <caleffectivevalue.h>
#include <qmath.h>
#include <algorithm>
#include <QDebug>

CalEffectiveValue::CalEffectiveValue(const QList<QVector<float>>& varList, int& varPoint1, int& varPoint2, int& surgeNum1, int& surgeNum2, int&firstPos):
        wyCal(new CWyCal())
      , t_wavePoint1(varPoint1)
      , t_wavePoint2(varPoint2)
      , t_surgeNum1(surgeNum1)
      , t_surgeNum2(surgeNum2)
      , t_firPos2(firstPos)
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

QVector<float> CalEffectiveValue::calRecordEffValueBefore(QVector<float>varList, int&pointNum, int&surgeNum, int&recordFirPos)
{
    QVector<float> uEffVector;
    QVector<float> uCalVector;

//    std::reverse(varList.begin(), varList.end());
//    //计算前两个周波的有效值就要取三个周波的采样值
//    float* p_data = new float[3*pointNum];
//    for(int i=6*pointNum; i<varList.size(); i++){
//       uCalVector.append(varList.at(i));
//    }

//    //将值放到p_data里
//    if(!uCalVector.empty()){
//        memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof(float));
//    }

//    //每一个点的采样值,往后推一个周波
//    for(int i=0; i<2*pointNum; i++){
////        float a_Ang  = wyCal->Cal_Ang(p_data +i, 0, pointNum);
////        float rms = wyCal->DFT_Rms(p_data+i, pointNum, a_Ang);
////        float trms = wyCal->Cal_True_Rms(p_data +i, 0, pointNum);
////        float rms = wyCal->DFT_Rms(p_data+i, pointNum, fp);
//        float trms = calTrueRms(p_data + i, 0, pointNum);

//        uEffVector.append(trms);
//    }
//    std::reverse(uEffVector.begin(), uEffVector.end());
//    delete[] p_data;

//***************往后算有效值***************
//突变点位置大于两个周波
//A段取到的值是否大于两个周波
    int aSegNum = surgeNum - recordFirPos;
    if(aSegNum >= 2*pointNum){
        //前2 后7
        //计算前两个周波的有效值就要取三个周波的采样值， 本身一个，偏移量一个周波
        float* p_data = new float[3*pointNum];
        for(int i=0; i<3*pointNum; i++){
            uCalVector.append(varList.at(i));
        }

        //将值放到p_data里
        if(!uCalVector.empty()){
            memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof (float));
        }

        //每一个点的采样值，往后推一个周波
        for(int i=0; i<2*pointNum; i++){
//        float a_Ang = wyCal->Cal_Ang(p_data+i, 0, pointNum);
//        float rms = wyCal->Cal_Rms_Result_Ex(p_data+i, 0, pointNum, a_Ang);

            float trms = calTrueRms(p_data+i, 0, pointNum);

            uEffVector.append(trms);
        }
        delete[] p_data;
    }else if(aSegNum < 2*pointNum){
        //前2 后7
        //计算前两个周波的有效值就要取三个周波的采样值， 本身一个，偏移量一个周波
        //不足两个周波
        float* p_data = new float[2*aSegNum];
        for(int i=0; i<2*aSegNum; i++){
            uCalVector.append(varList.at(i));
        }

        //将值放到p_data里
        if(!uCalVector.empty()){
            memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof (float));
        }

        //每一个点的采样值，往后推一个周波
        for(int i=0; i<aSegNum; i++){
//        float a_Ang = wyCal->Cal_Ang(p_data+i, 0, pointNum);
//        float rms = wyCal->Cal_Rms_Result_Ex(p_data+i, 0, pointNum, a_Ang);

            float trms = calTrueRms(p_data+i, 0, pointNum);

            uEffVector.append(trms);
        }
        delete[] p_data;
    }
    return uEffVector;
}

QVector<float> CalEffectiveValue::calEffValueBefore(QVector<float>varList, int&pointNum, int&surgeNum)
{
    QVector<float> uEffVector;
    QVector<float> uCalVector;

//    std::reverse(varList.begin(), varList.end());
//    //计算前两个周波的有效值就要取三个周波的采样值
//    float* p_data = new float[3*pointNum];
//    for(int i=6*pointNum; i<varList.size(); i++){
//       uCalVector.append(varList.at(i));
//    }

//    //将值放到p_data里
//    if(!uCalVector.empty()){
//        memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof(float));
//    }

//    //每一个点的采样值,往后推一个周波
//    for(int i=0; i<2*pointNum; i++){
////        float a_Ang  = wyCal->Cal_Ang(p_data +i, 0, pointNum);
////        float rms = wyCal->DFT_Rms(p_data+i, pointNum, a_Ang);
////        float trms = wyCal->Cal_True_Rms(p_data +i, 0, pointNum);
////        float rms = wyCal->DFT_Rms(p_data+i, pointNum, fp);
//        float trms = calTrueRms(p_data + i, 0, pointNum);

//        uEffVector.append(trms);
//    }
//    std::reverse(uEffVector.begin(), uEffVector.end());
//    delete[] p_data;

//***************往后算有效值***************
//突变点位置大于两个周波
    if(surgeNum >= 2*pointNum){
        //前2 后7
        //计算前两个周波的有效值就要取三个周波的采样值， 本身一个，偏移量一个周波
        float* p_data = new float[3*pointNum];
        for(int i=0; i<3*pointNum; i++){
            uCalVector.append(varList.at(i));
        }

        //将值放到p_data里
        if(!uCalVector.empty()){
            memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof (float));
        }

        //每一个点的采样值，往后推一个周波
        for(int i=0; i<2*pointNum; i++){
//        float a_Ang = wyCal->Cal_Ang(p_data+i, 0, pointNum);
//        float rms = wyCal->Cal_Rms_Result_Ex(p_data+i, 0, pointNum, a_Ang);

            float trms = calTrueRms(p_data+i, 0, pointNum);

            uEffVector.append(trms);
        }
        delete[] p_data;
    }else if(surgeNum < 2*pointNum){
        //前2 后7
        //不足取2倍surgeNum
        float* p_data = new float[2*surgeNum];
        for(int i=0; i<2*surgeNum; i++){
            uCalVector.append(varList.at(i));
        }

        //将值放到p_data里
        if(!uCalVector.empty()){
            memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof (float));
        }

        //每一个点的采样值，往后推一个周波
        for(int i=0; i<surgeNum; i++){
//        float a_Ang = wyCal->Cal_Ang(p_data+i, 0, pointNum);
//        float rms = wyCal->Cal_Rms_Result_Ex(p_data+i, 0, pointNum, a_Ang);

            float trms = calTrueRms(p_data+i, 0, pointNum);

            uEffVector.append(trms);
        }
        delete[] p_data;
    }
    return uEffVector;
}

QVector<float> CalEffectiveValue::calEffValueAfter(QVector<float> varList, int& pointNum)
{
    QVector<float> uEffVector;
    QVector<float> uCalVector;

//    std::reverse(varList.begin(), varList.end());
//    //计算后六个周波的有效值就要取后七个周波的采样值
//    float* p_data = new float[7*pointNum];
//    for(int i=0; i<7*pointNum; i++){
//       uCalVector.append(varList.at(i));
//    }

//    //将值放到p_data里
//    if(!uCalVector.empty()){
//       memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof(float));
//    }

//    //每一个点的有效值,往后推一个周波
//    for(int i=0; i<6*pointNum; i++){
////        float a_Ang  = wyCal->Cal_Ang(p_data +i, 0, pointNum);
////        float rms = wyCal->DFT_Rms(p_data+i, pointNum, a_Ang);
////        float trms = wyCal->Cal_True_Rms(p_data + i, 0, pointNum);
//        float trms = calTrueRms(p_data + i, 0, pointNum);

//        uEffVector.append(trms);
//    }
//    std::reverse(uEffVector.begin(), uEffVector.end());
//    delete[] p_data;

//******************往后算有效值********************
//前2  后7
//计算后六个周波的有效值就要取七个周波的采样值
    float* p_data = new float[7*pointNum];
    for(int i=2*pointNum; i<varList.size(); i++){
        uCalVector.append(varList.at(i));
    }

    //将值放到p_data里
    if(!uCalVector.empty()){
        memcpy(p_data, &uCalVector[0], uCalVector.size()*sizeof (float));
    }

    //每一个点的有效值，往后推一个周波,  正序
    for(int i=0; i<6*pointNum; i++){
//        float a_Ang = wyCal->Cal_Ang(p_data+i, 0, pointNum);
//        float rms = wyCal->Cal_Rms_Result_Ex(p_data+i, 0, pointNum, a_Ang);
        float trms = calTrueRms(p_data+i, 0, pointNum);

        uEffVector.append(trms);
    }
    delete[] p_data;

    return uEffVector;
}

//计算真有效值
float CalEffectiveValue::calTrueRms(float *a_pData, int startPos, int &pointNum)
{
    float drms = 0.0;
    float sum = 0.0;
    for(int i=0; i<pointNum; i++){
        sum += static_cast<float>(fabs(a_pData[startPos+i]*a_pData[startPos+i]));
    }
    sum /= pointNum;
    drms = static_cast<float>(sqrt(sum));

    return drms;
}

QList<QVector<float>> CalEffectiveValue::getEffectiveValueList()
{
    QList<QVector<float>> effectiveValueList;
    QVector<float> chopTotal1zhou = chopBefore1zhou;
    QVector<float> chopTotal1zhou2 = chopBefore1zhou2;
    chopTotal1zhou.append(chopAfter1zhou);
    chopTotal1zhou2.append(chopAfter1zhou2);

    //告知A段取值是否满2个周波
    QVector<float> chopBeforeEffect1zhou = calEffValueBefore(chopTotal1zhou, t_wavePoint1, t_surgeNum1);
    QVector<float> chopBeforeEffect1zhou2 = calRecordEffValueBefore(chopTotal1zhou2, t_wavePoint2, t_surgeNum2, t_firPos2);
    QVector<float> chopAfterEffect1zhou = calEffValueAfter(chopTotal1zhou, t_wavePoint1);
    QVector<float> chopAfterEffect1zhou2 = calEffValueAfter(chopTotal1zhou2, t_wavePoint2);

    effectiveValueList << chopBeforeEffect1zhou
                       << chopAfterEffect1zhou
                       << chopBeforeEffect1zhou2
                       << chopAfterEffect1zhou2;

    return effectiveValueList;
}
