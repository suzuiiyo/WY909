﻿#include "comparealgorithm.h"
#include <QDebug>
#include <cmath>

CompareAlgorithm::CompareAlgorithm(QObject *parent) : QObject(parent)
{
    
}

CompareAlgorithm::CompareAlgorithm(const QList<QVector<float> >  &sampleList, const QList<QVector<float> > &effectiveList):
    transFlag(false)
    ,multipleRate(0)
{
    sampleBefore1zhou = sampleList.at(0);
    sampleAfter1zhou = sampleList.at(1);
    
    sampleBefore1zhou2 = sampleList.at(2);
    sampleAfter1zhou2 = sampleList.at(3);

    effectBefore1zhou = effectiveList.at(0);
    effectAfter1zhou = effectiveList.at(1);

    effectBefore1zhou2 = effectiveList.at(2);
    effectAfter1zhou2 = effectiveList.at(3);
}

CompareAlgorithm::~CompareAlgorithm()
{
}

int CompareAlgorithm::calMultipleRate(int m, int n)
{
    if(n > m){
        int temp;
        temp = n;
        n = m;
        m = temp;
    }

    int k = 0;
    for(int i=m; i>0; i++){
        if(i%m == 0 && i%n == 0){
            k = i;
            break;
        }
    }
    return k;
}

QList<float> CompareAlgorithm::calVectorPeak(QVector<float> var)
{
    QList<float> peakList;
    for(int i=2; i<var.size()-3; i++){
        if(var.at(i-2) >= var.at(i-1) && var.at(i-1) >= var.at(i) && var.at(i) <= var.at(i+1) && var.at(i + 1) <= var.at(i+2))
        {
            peakList.append(var.at(i));
        }
    }
    return peakList;
}

QVector<float> CompareAlgorithm::calSample1Value(QVector<float> varSample1, int varAlign)
{
    QVector<float> sample1;

    if(varAlign!=0){
        if(transFlag == false){
            for(int i= 0; i< varSample1.size(); i++)
            {
                sample1.append(varSample1[i]);
                for(int i = 0; i<multipleRate/t_wavePoints1-1; i++){
                    sample1.append(0.0);
                }
            }
        }else
        {
            for(int i= abs(varAlign)/(multipleRate/t_wavePoints1); i< varSample1.size(); i++)
            {
                sample1.append(varSample1[i]);
                for(int i=0; i<multipleRate/t_wavePoints1-1; i++){
                    sample1.append(0);
                }
            }
        }
    }else{
        for(int i=0; i<varSample1.size(); i++)
        {
            sample1.append(varSample1[i]);
        }
    }
    return sample1;
}

QVector<float> CompareAlgorithm::calSample2Value(QVector<float> varSample2, int varAlign)
{
    QVector<float> sample2;

    if(varAlign!=0){
        if(transFlag){
            for(int i= abs(varAlign)/(multipleRate/t_wavePoints2); i< varSample2.size(); i++)
            {
                sample2.append(varSample2[i]);
                for(int i = 0; i<multipleRate/t_wavePoints2-1; i++){
                    sample2.append(0.0);
                }
            }
        }else {
            for(int i= 0; i< varSample2.size(); i++)
            {
                sample2.append(varSample2[i]);
                for(int i = 0; i<multipleRate/t_wavePoints2-1; i++){
                    sample2.append(0.0);
                }
            }
        }
    }else
    {
        for(int i= 0; i< varSample2.size(); i++)
        {
            sample2.append(varSample2[i]);
        }
    }
    return sample2;
}

QMap<QVector<float>, QVector<float> > CompareAlgorithm::getChopBeforeZhou() const
{
    QMap<QVector<float>, QVector<float>> chopBeforeZhouMap;
    chopBeforeZhouMap.insert(sampleBefore1zhou, sampleBefore1zhou2);
    return chopBeforeZhouMap;
}

QMap<QVector<float>, QVector<float> > CompareAlgorithm::getChopAfterZhou() const
{
    QMap<QVector<float>, QVector<float>> chopAfterZhouMap;
    chopAfterZhouMap.insert(sampleAfter1zhou, sampleAfter1zhou2);
    return chopAfterZhouMap;
}

QMap<QVector<float>, QVector<float> > CompareAlgorithm::getInsertCompareVector() const
{
    //先插入突变点之前的采样值
    QVector<float> insertCompareVector1 = insertCompareBefore1;
    QVector<float> insertCompareVector2 = insertCompareBefore2;

    //再插入突变点之后的采样值
    insertCompareVector1.append(insertCompareAfter1);
    insertCompareVector2.append(insertCompareAfter2);

    QMap<QVector<float>, QVector<float>> insertValueMap;
    insertValueMap.insert(insertCompareVector1, insertCompareVector2);
    return insertValueMap;
}

int CompareAlgorithm::calAlignPosition()
{
    uint stime = t_surgeTime1.toMSecsSinceEpoch();
    uint etime = t_surgeTime2.toMSecsSinceEpoch();
    int varAlign = 0;
    multipleRate = calMultipleRate(t_wavePoints1, t_wavePoints2);

    int tRet = stime - etime;

    if(tRet){
        //被对齐序列
        QList<float> beforePeakList = this->calVectorPeak(sampleBefore1zhou);
        QList<float> before2PeakList = this->calVectorPeak(sampleBefore1zhou2);

        auto beforePeakMin = std::min_element(std::begin(beforePeakList), std::end(beforePeakList));
        auto before2PeakMin = std::min_element(std::begin(before2PeakList), std::end(before2PeakList));

        int beforeAlign = 0;
        for(int i=0; i<sampleBefore1zhou.size(); i++){
            if(sampleBefore1zhou.at(i) == *beforePeakMin)
               beforeAlign = i;
        }

        int before2Align = 0;
        for(int i=0; i<sampleBefore1zhou2.size(); i++){
            if(sampleBefore1zhou2.at(i) == *before2PeakMin)
               before2Align = i;
        }

        varAlign = beforeAlign*(multipleRate/t_wavePoints1) - before2Align*(multipleRate/t_wavePoints2);
        if(abs(varAlign) > sampleBefore1zhou.size()*(multipleRate/t_wavePoints1)/2 || abs(varAlign) < multipleRate/t_wavePoints1){
            QVector<float> sampleAfter1zhou_half;
            QVector<float> sampleAfter1zhou2_half;

            for(int i=0; i<t_wavePoints1; i++){
                sampleAfter1zhou_half.append(sampleAfter1zhou.at(i));
            }

            for(int i=0; i<t_wavePoints2; i++){
                sampleAfter1zhou2_half.append(sampleAfter1zhou2.at(i));
            }

            //被对齐序列
            QList<float> afterPeakList = this->calVectorPeak(sampleAfter1zhou_half);
            QList<float> afterPeak2List = this->calVectorPeak(sampleAfter1zhou2_half);

            auto afterPeakMin = std::min_element(std::begin(afterPeakList), std::end(afterPeakList));
            auto after2PeakMin = std::min_element(std::begin(afterPeak2List), std::end(afterPeak2List));

            int afterAlign = 0;
            for(int i=0; i<t_wavePoints1; i++){
                if(sampleAfter1zhou_half.at(i) == *afterPeakMin)
                   afterAlign = i;
            }

            int after2Align = 0;
            for(int i=0; i<t_wavePoints2; i++){
                if(sampleAfter1zhou2_half.at(i) == *after2PeakMin)
                   after2Align = i;
            }

            varAlign = afterAlign*(multipleRate/t_wavePoints1) - after2Align*(multipleRate/t_wavePoints2);
        }

        if(varAlign < 0){
            transFlag = true;
        }else {
            transFlag = false;
        }

        return varAlign;
    }

    //如果突变点时刻一致
    else if(!tRet){
        varAlign = 0;
        return varAlign;
    }
    return varAlign;
}

void CompareAlgorithm::calBeforeCompareData(int alignBeforeDelta)
{
    QVector<float> effectBefore1 = calSample1Value(effectBefore1zhou, alignBeforeDelta);
    QVector<float> effectBefore2 = calSample2Value(effectBefore1zhou2, alignBeforeDelta);
    insertCompareBefore1 = effectBefore1zhou;

    int compareValue = multipleRate/t_wavePoints1;
    int compareValue2 = multipleRate/t_wavePoints2;
    //挑点系数
    int valueFactor = compareValue/compareValue2;
    int totalComparePoints = 0;

//    if(transFlag == true){
//        totalComparePoints = sampleBefore1.size() + alignBeforeDelta;
//    }else{
//        totalComparePoints = sampleBefore1.size();
//    }

//    for(int i=0; i < totalComparePoints / compareValue; i++)
//    {
//       t_pointSeqList1.append(t_startPos1 + i);
//       if(i == 0){
//           int comparision1 = (sampleBefore1.at(0) - sampleBefore2.at(0))/sampleBefore2.at(0);
//           beforeCompareData.append(comparision1);
//           t_pointSeqList2.append(t_startPos2 + i);

//           //获取参与比对序列的挑点序列
//           insertCompareBefore2.append(sampleBefore2.at(0));
//       }
//       else
//       {
//           float comparision1;
//           float comparision2;

//           for(int j=0; j<valueFactor; j++){
//               if(sampleBefore2.at(compareValue*i - j)!=0){
//                   comparision1 = (sampleBefore1.at(compareValue*i) - sampleBefore2.at(compareValue*i - j))/sampleBefore2.at(compareValue*i-j);
//               }

//               if(sampleBefore2.at(compareValue*i + j)!=0){

//                   comparision2 = (sampleBefore1.at(compareValue*i) - sampleBefore2.at(compareValue*i + j))/sampleBefore2.at(compareValue*i + j);
//               }
//           }

//           if(fabs(comparision1) > fabs(comparision2)){
//               beforeCompareData.append(comparision2);
//               t_pointSeqList2.append(t_startPos2 + valueFactor*i + 1);

//               //根据comparision和sampleBefore1计算sampleBefore2
//               insertCompareBefore2.append(insertCompareBefore1.at(i)/(comparision2 + 1));
//           }
//           else
//           {
//               beforeCompareData.append(comparision1);
//               t_pointSeqList2.append(t_startPos2 + valueFactor*i);

//               insertCompareBefore2.append(insertCompareBefore1.at(i)/(comparision1 + 1));
//           }
//       }
//    }
    if(transFlag){
        totalComparePoints = effectBefore1.size() + alignBeforeDelta;
    }else{
        totalComparePoints = effectBefore1.size();
    }

    for(int i=0; i<totalComparePoints / compareValue; i++){
        t_pointSeqList1.append(t_startPos1 + i);
        if(i == 0){
            float comparision = effectBefore1.at(0) - effectBefore2.at(0);
            float comparisionRel;
            if(effectBefore1.at(0) == 0 && effectBefore2.at(0) == 0){
                comparisionRel = 0.0;
            }else if(comparision > 0.01 && effectBefore2.at(0) == 0){
                comparisionRel = 1.0;
            }else{
                comparisionRel = (effectBefore1.at(0) - effectBefore2.at(0))/effectBefore2.at(0);
            }

            beforeCompareData.append(comparision);
            t_pointSeqList2.append(t_startPos2 + i);
            insertCompareBefore2.append(effectBefore2.at(0));
            relativeError.append(comparisionRel);

            if(comparisionRel < 0.050)
            {
               pointConclusion.append(normal);
            }else if(comparisionRel >=0.050 && comparisionRel < 0.100){
               pointConclusion.append(innormal);
            }else if(comparisionRel >= 0.100){
               pointConclusion.append(critical);
            }
        }
        else
        {
            float comparision;
            float comparisionRel;

            for(int j=0; j<valueFactor; j++){
                if(effectBefore2.at(compareValue*i - j) !=0
                    &&
                   effectBefore2.size() > (compareValue*i + j)
                    &&
                   effectBefore2.at(compareValue*i + j)!=0){
                   float average = (effectBefore2.at(compareValue*i - j) + effectBefore2.at(compareValue*i + j))/2;
                   comparision = effectBefore1.at(compareValue*i) - average;
                   if(effectBefore1.at(compareValue*i) == 0 && average == 0){
                    comparisionRel = 0.0;
                   }else if(comparision > 0.01 && average == 0)
                   {
                       comparisionRel = 1.0;
                   }else{
                       comparisionRel = (effectBefore1.at(compareValue*i) - average)/average;
                   }
                }else if(effectBefore2.at(compareValue*i - j)!=0
                         &&
                         effectBefore2.size() < (compareValue*i + j)
                         ){
                   float average = (effectBefore2.at(compareValue*i - j) + effectBefore2.last())/2;
                   comparision = effectBefore1.at(compareValue*i) - average;
                   if(effectBefore1.at(compareValue*i) == 0 && average == 0){
                       comparisionRel = 0.0;
                   }else if(comparision > 0.01 && average == 0)
                   {
                       comparisionRel = 1.0;
                   }else{
                       comparisionRel = (effectBefore1.at(compareValue*i) - average)/average;
                   }
                }
            }

            beforeCompareData.append(comparision);
            t_pointSeqList2.append(t_startPos2 + valueFactor*i + 1);
            insertCompareBefore2.append(effectBefore1.at(compareValue*i) - comparision);
            relativeError.append(comparisionRel);

            if(comparisionRel < 0.050)
            {
               pointConclusion.append(normal);
            }else if(comparisionRel >=0.050 && comparisionRel < 0.100){
               pointConclusion.append(innormal);
            }else if(comparisionRel >= 0.100){
               pointConclusion.append(critical);
            }

            for(int i=0; i<insertCompareBefore2.size(); i++){
                if(insertCompareBefore2.at(i) < 0.01){
                    insertCompareBefore2.replace(i, 0.0);
                }
            }
        }
    }
}

void CompareAlgorithm::calAfterCompareData(int alignAfterDelta)
{
    QVector<float> effectAfter1 = calSample1Value(effectAfter1zhou, alignAfterDelta);
    QVector<float> effectAfter2 = calSample2Value(effectAfter1zhou2, alignAfterDelta);

    insertCompareAfter1 = effectAfter1zhou;

    int compareValue = multipleRate/t_wavePoints1;
    int compareValue2 = multipleRate/t_wavePoints2;
    int valueFactor = compareValue/compareValue2;
    int totalComparePoints = 0;

    int afterStartPos = 0;
    int afterStartPos2 = 0;
//    if(transFlag == true){
//        totalComparePoints = sampleAfter1.size() + alignAfterDelta;
//    }else
//    {
//        totalComparePoints = sampleAfter1.size();
//    }

//    if(!t_pointSeqList1.isEmpty())
//    {
//        afterStartPos = t_pointSeqList1.last() + 1;
//    }

//    if(!t_pointSeqList2.isEmpty())
//    {
//        afterStartPos2 = t_pointSeqList2.last() + valueFactor;
//    }

//    for(int i=0; i < totalComparePoints/compareValue; i++)
//    {
//        t_pointSeqList1.append(afterStartPos + i);

//        if(i == 0){
//            int comparision = (sampleAfter1.at(0) - sampleAfter2.at(0))/sampleAfter2.at(0);
//            afterCompareData.append(comparision);
//            t_pointSeqList2.append(afterStartPos2 + i);

//            //获取参与比对序列的挑点序列
//            insertCompareAfter2.append(sampleAfter2.at(0));
//        }
//        else
//        {
//            float comparision1;
//            float comparision2;

//            for(int j =0 ; j< valueFactor; j++){
//                if(sampleAfter2.at(compareValue*i - j)!=0){
//                    comparision1 = (sampleAfter1.at(compareValue*i) - sampleAfter2.at(compareValue*i - j))/sampleAfter2.at(compareValue*i - j);
//                }
//                if(sampleAfter2.at(compareValue*i + j)!=0){
//                    comparision2 = (sampleAfter1.at(compareValue*i) - sampleAfter2.at(compareValue*i + j))/sampleAfter2.at(compareValue*i + j);
//                }
//            }

//            if(abs(comparision1) > abs(comparision2)){
//                afterCompareData.append(comparision2);
//                t_pointSeqList2.append(afterStartPos2 + valueFactor*i + 1);

//                insertCompareAfter2.append(insertCompareAfter1.at(i)/(comparision2 + 1));
//            }
//            else
//            {
//                afterCompareData.append(comparision1);
//                t_pointSeqList2.append(afterStartPos2 + valueFactor*i);

//                insertCompareAfter2.append(insertCompareAfter1.at(i)/(comparision1 + 1));
//            }
//        }
//    }
    if(transFlag){
        totalComparePoints = effectAfter1.size() + alignAfterDelta;
    }else
    {
        totalComparePoints = effectAfter1.size();
    }

    if(!t_pointSeqList1.isEmpty())
    {
        afterStartPos = t_pointSeqList1.last() + 1;
    }

    if(!t_pointSeqList2.isEmpty())
    {
        afterStartPos2 = t_pointSeqList2.last() + 1;
    }

                    QVector<float> floatIndo;
                    QVector<float> averageList;
                    QVector<float> floatResult;
                    QVector<float> averageBefore;
                    QVector<float> averageAfter;
    for(int i=0; i<totalComparePoints/compareValue; i++)
    {
        t_pointSeqList1.append(afterStartPos + i);

        if(i == 0){
            float comparision = effectAfter1.at(0) - effectAfter2.at(0);
            float comparisionRel;
            if(effectAfter1.at(0) == 0 && effectAfter2.at(0) == 0){
                comparisionRel = 0.0;
            }else if(comparision > 0.01 && effectAfter2.at(0) == 0){
                comparisionRel = 1.0;
            }else{
                comparisionRel = (effectAfter1.at(0) - effectAfter2.at(0))/effectAfter2.at(0);
            }
            afterCompareData.append(comparision);
            t_pointSeqList2.append(afterStartPos2 + i);
            insertCompareAfter2.append(effectAfter2.at(0));
            relativeError.append(comparisionRel);

            if(comparisionRel < 0.050)
            {
               pointConclusion.append(normal);
            }else if(comparisionRel >=0.050 && comparisionRel < 0.100){
               pointConclusion.append(innormal);
            }else if(comparisionRel >= 0.100){
               pointConclusion.append(critical);
            }
        }
        else
        {
            float comparision;
            float comparisionRel;

            for(int j =0 ; j< valueFactor; j++){
                if(effectAfter2.at(compareValue*i - j)!=0
                     &&
                   effectAfter2.size() > (compareValue*i + j)
                     &&
                   effectAfter2.at(compareValue*i + j)!=0){
                    float average = (effectAfter2.at(compareValue*i - j) + effectAfter2.at(compareValue*i + j))/2;
                    comparision = effectAfter1.at(compareValue*i) - average;

                    if(effectAfter1.at(compareValue*i) == 0 && average == 0){
                        comparisionRel = 0.0;
                    }else if(comparision > 0.01 && average == 0){
                        comparisionRel = 1.0;
                    }else{
                        comparisionRel = (effectAfter1.at(compareValue*i) - average)/average;
                        floatIndo.append(effectAfter1.at(compareValue*i));
                        averageList.append(average);
                        floatResult.append(comparisionRel);
                    }

                    averageBefore.append(effectAfter2.at(compareValue*i - j));
                    averageAfter.append(effectAfter2.at(compareValue*i + j));
                }else if(effectAfter2.at(compareValue*i - j)!=0
                         &&
                         effectAfter2.size() < (compareValue*i + j)){
                    float average = (effectAfter2.at(compareValue*i - j) + effectAfter2.last())/2;
                    comparision = effectAfter1.at(compareValue*i) - average;
                    if(effectAfter1.at(compareValue*i) == 0 && average == 0){
                        comparisionRel = 0.0;
                    }else if(comparision > 0.01 && average == 0){
                        comparisionRel = 1.0;
                    }else{
                        comparisionRel = (effectAfter1.at(compareValue*i) - average)/average;
                    }
                }
            }

            afterCompareData.append(comparision);
            t_pointSeqList2.append(afterStartPos2 + valueFactor*i + 1);
            insertCompareAfter2.append(effectAfter1.at(compareValue*i) - comparision);
            relativeError.append(comparisionRel);

            if(comparisionRel < 0.050)
            {
                pointConclusion.append(normal);
            }else if(comparisionRel >=0.050 && comparisionRel < 0.100){
                pointConclusion.append(innormal);
            }else if(comparisionRel >= 0.100){
                pointConclusion.append(critical);
            }

            for(int i=0; i<insertCompareAfter2.size(); i++){
                if(insertCompareAfter2.at(i) < 0.01){
                    insertCompareAfter2.replace(i, 0.0);
                }
            }
        }
    }

                    qDebug() << effectAfter1 << "a1a1a1a1a1a1a1a1a1";
                    qDebug() << effectAfter2 << "a2a2a2a2a2a2a2a2a2";
                    qDebug() << effectAfter1.size() << "kkakakakaka";
                    qDebug() << effectAfter2.size() << "manamamanama";
//                    qDebug() << floatIndo << "aaaaaaaaaaaaaa";
//                    qDebug() << floatIndo.size() << "11111111";
//                    qDebug() << averageAfter << "AfterAfterAfter";
//                    qDebug() << averageBefore << "BeforeBeforeBefore";
//                    qDebug() << averageList << "bbbbbbbbbbb";
//                    qDebug() << averageList.size() << "2222222222";
//                    qDebug() << floatResult << "ccccccccccc";
//                    qDebug() << floatResult.size() << "33333333333";
}

QMap<QVector<float>, QVector<float> > CompareAlgorithm::getCompareDataMap() const
{
    QMap<QVector<float>, QVector<float>> compareDataMap;
    compareDataMap.insert(beforeCompareData, afterCompareData);

    return compareDataMap;
}

QMap<QList<int>, QList<int> > CompareAlgorithm::getPointSeqMap() const
{
    QMap<QList<int>, QList<int>> pointSeqMap;
    pointSeqMap.insert(t_pointSeqList1, t_pointSeqList2);
    return pointSeqMap;
}

float CompareAlgorithm::getCompareConclusion()
{
     //连续3个点的有效值超出5%
//     for(int i=0; i<relativeError.size() - 2; i++){
//         if(relativeError.at(i) > 0.05
//                 &&
//            relativeError.at(i + 1) > 0.05
//                 &&
//            relativeError.at(i + 2) > 0.05){
//            t_compareConclusion = (relativeError.at(i) + relativeError.at(i + 1) + relativeError.at(i + 2))/3;
//         }else if(relativeError.at(i) > 0.1
//                 &&
//            relativeError.at(i + 1) > 0.1
//                 &&
//            relativeError.at(i + 2) > 0.1){
//            t_compareConclusion = (relativeError.at(i) + relativeError.at(i + 1) + relativeError.at(i + 2))/3;
//         }
//     }
     float sum = 0;
     for(int i=0; i<relativeError.size(); i++){
         sum += relativeError.at(i);
     }
     t_compareConclusion = sum/relativeError.size();

     //计算比较值序列的平均值作为比对结论
//     t_compareConclusion = fabs((sumAfter + sumBefore)/(afterCompareData.size() + beforeCompareData.size())/((sumEffectBefore1 + sumEffectAfter1)/(effectBefore1zhou.size() + effectAfter1zhou.size())));
     qDebug() << t_compareConclusion << "wanlawanlawanlawanla";
     return t_compareConclusion;
}

void CompareAlgorithm::setSurgetTime(QDateTime time1, QDateTime time2)
{
    t_surgeTime1 = time1;
    t_surgeTime2 = time2;
}

void CompareAlgorithm::setWavePoint(int num1, int num2)
{
    t_wavePoints1 = num1;
    t_wavePoints2 = num2;
}

void CompareAlgorithm::setStartPoint(int num1, int num2)
{
    t_startPos1 = num1;
    t_startPos2 = num2;
}

QVector<float> CompareAlgorithm::getRelativeError()
{
    return relativeError;
}

QVector<float> CompareAlgorithm::getAbsoluteError()
{
    absoluteError = beforeCompareData;
    absoluteError.append(afterCompareData);
    return absoluteError;
}

QList<int> CompareAlgorithm::getPointConclusion()
{
    return pointConclusion;
}
