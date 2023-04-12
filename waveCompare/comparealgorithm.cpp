#include "comparealgorithm.h"
#include <QDebug>
#include <cmath>
#include <QFile>
#include <QTextStream>

using namespace::std;

CompareAlgorithm::CompareAlgorithm(QObject *parent) : QObject(parent)
{
    
}

CompareAlgorithm::CompareAlgorithm(const QList<QVector<float> >  &sampleList, const QList<QVector<float> > &effectiveList):
   chValueStatus(false)
{
    sampleBefore1zhou = sampleList.at(0);
    sampleAfter1zhou = sampleList.at(1);
    
    sampleBefore1zhou2 = sampleList.at(2);
    sampleAfter1zhou2 = sampleList.at(3);

    effectBefore1zhou = effectiveList.at(0);
    effectAfter1zhou = effectiveList.at(1);

    effectBefore1zhou2 = effectiveList.at(2);
    effectAfter1zhou2 = effectiveList.at(3);

    effectTotal1zhou2 = effectBefore1zhou2;
    effectTotal1zhou2.append(effectAfter1zhou2);
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

void CompareAlgorithm::calEffectInsertZero(int& multiVar)
{
    for(int i= t_wavePoints1; i< effectBefore1zhou.size(); i++)
    {
        effectZeroBefore1.append(effectBefore1zhou[i]);
        for(int i = 0; i<multiVar/t_wavePoints1-1; i++){
            effectZeroBefore1.append(0.0);
        }
    }

    for(int i=0; i< effectAfter1zhou.size() - t_wavePoints1; i++){
        effectZeroAfter1.append(effectAfter1zhou[i]);
        for(int i=0; i<multiVar/t_wavePoints1-1; i++){
            effectZeroAfter1.append(0.0);
        }
    }
}

void CompareAlgorithm::calEffectInsert2Zero(int& varAlign, int& multiVar)
{
    float deltaFactor = varAlign/(multiVar/t_wavePoints2);
    int deltaFactor_int = static_cast<int>(deltaFactor);
    for(int i= t_wavePoints2 + deltaFactor_int; i< effectBefore1zhou2.size() + deltaFactor_int; i++)
    {
        effectZeroBefore2.append(effectTotal1zhou2[i]);
        for(int i = 0; i<multiVar/t_wavePoints2-1; i++){
            effectZeroBefore2.append(0.0);
        }
    }

    for(int i = effectBefore1zhou2.size() + deltaFactor_int; i<effectTotal1zhou2.size() - t_wavePoints2 + deltaFactor_int; i++)
    {
        effectZeroAfter2.append(effectTotal1zhou2[i]);
        for(int i = 0; i<multiVar/t_wavePoints2-1; i++){
             effectZeroAfter2.append(0.0);
        }
    }
}

QList<QVector<float>> CompareAlgorithm::getChopBeforeZhou() const
{
    QList<QVector<float>> chopBeforeZhouList;
    chopBeforeZhouList.append(sampleBefore1zhou);
    chopBeforeZhouList.append(sampleBefore1zhou2);
    return chopBeforeZhouList;
}

QList<QVector<float>> CompareAlgorithm::getChopAfterZhou() const
{
    QList<QVector<float>> chopAfterZhouList;
    chopAfterZhouList.append(sampleAfter1zhou);
    chopAfterZhouList.append(sampleAfter1zhou2);
    return chopAfterZhouList;
}

QList<QVector<float>> CompareAlgorithm::getInsertCompareVector() const
{
    //先插入突变点之前的采样值
    QVector<float> insertCompareVector1 = insertCompareBefore1;
    QVector<float> insertCompareVector2 = insertCompareBefore2;

    //再插入突变点之后的采样值
    insertCompareVector1.append(insertCompareAfter1);
    insertCompareVector2.append(insertCompareAfter2);

    QList<QVector<float>> insertValueList;
    insertValueList.append(insertCompareVector1);
    insertValueList.append(insertCompareVector2);
    return insertValueList;
}

int CompareAlgorithm::calAlignPosition(int& multivar)
{
    int ssStart1 = t_surgeTime1.section(',', 1, 1).section(':', 2, 2).section('.', 0, 0).toInt();
    int mesStart1 = t_surgeTime1.section(',', 1, 1).section(':', 2, 2).section('.', 1, 1).toInt();

    int ssStart2 = t_surgeTime2.section(',', 1, 1).section(':', 2, 2).section('.', 0, 0).toInt();
    int mesStart2 = t_surgeTime2.section(',', 1, 1).section(':', 2, 2).section('.', 1, 1).toInt();

    int varAlign = 0;
    int ssRet = ssStart1 - ssStart2;
    int mesRet = mesStart1 - mesStart2;

    if(ssRet || mesRet){
        //只用突变前一个周波， 突变后一个周波
        QVector<float> chopBefore1zhou_half;
        QVector<float> chopBefore1zhou2_half;

        QVector<float> chopAfter1zhou_half;
        QVector<float> chopAfter1zhou2_half;

//************往前算***********
//        for(int i=2*t_wavePoints1 - 1; i<sampleBefore1zhou.size(); i++){
//            chopBefore1zhou_half.append(sampleBefore1zhou.at(i));
//        }

//        for(int i=2*t_wavePoints2 - 1; i<sampleBefore1zhou2.size(); i++){
//            chopBefore1zhou2_half.append(sampleBefore1zhou2.at(i));
//        }

//************往后算***********
        for(int i=t_wavePoints1 - 1; i<sampleBefore1zhou.size(); i++){
            chopBefore1zhou_half.append(sampleBefore1zhou.at(i));
        }

        for(int i=t_wavePoints2 - 1; i<sampleBefore1zhou2.size(); i++){
            chopBefore1zhou2_half.append(sampleBefore1zhou2.at(i));
        }

        for(int i=0; i<t_wavePoints1; i++){
            chopAfter1zhou_half.append(sampleAfter1zhou.at(i));
        }

        for(int i=0; i<t_wavePoints2; i++){
            chopAfter1zhou2_half.append(sampleAfter1zhou2.at(i));
        }

        //A段是否启动
        bool zeroAFloat = false;
        bool zeroAFloat2 = false;

        //B段是否启动
        bool zeroBFloat = false;
        bool zeroBFloat2 = false;

        double sumAFloat = 0.0;
        double sumAFloat2 = 0.0;
        double sumBFloat = 0.0;
        double sumBFloat2 = 0.0;

        double aveAFloat = 0.0;
        double aveAFloat2 = 0.0;
        double aveBFloat = 0.0;
        double aveBFloat2 = 0.0;

        //A段丢失突变点附近十个点;
        for(int i=0; i<sampleBefore1zhou.size()-10; i++){
            sumAFloat += static_cast<double>(fabs(sampleBefore1zhou.at(i)));
        }
        aveAFloat = sumAFloat/(sampleBefore1zhou.size()-10);
        if(fabs(aveAFloat) > 0.2)
        {
            zeroAFloat = true;
        }else
        {
            zeroAFloat = false;
        }

        for(int i=0; i<sampleBefore1zhou2.size()-10; i++){
            sumAFloat2 += static_cast<double>(fabs(sampleBefore1zhou2.at(i)));
        }
        aveAFloat2 = sumAFloat2/(sampleBefore1zhou2.size()-10);
        if(fabs(aveAFloat2) > 0.2)
        {
            zeroAFloat2 = true;
        }else
        {
            zeroAFloat2 = false;
        }

        foreach(float var, sampleAfter1zhou){
            sumBFloat += static_cast<double>(fabs(var));
        }
        aveBFloat = sumBFloat/sampleAfter1zhou.size();
        if(fabs(aveBFloat) > 0.2)
        {
            zeroBFloat = true;
        }else
        {
            zeroBFloat = false;
        }

        foreach(float var, sampleAfter1zhou2){
            sumBFloat2 += static_cast<double>(fabs(var));
        }
        aveBFloat2 = sumBFloat2/sampleAfter1zhou2.size();
        if(fabs(aveBFloat2) > 0.2)
        {
            zeroBFloat2 = true;
        }else
        {
            zeroBFloat2 = false;
        }

        if(zeroAFloat && zeroAFloat2){
            //被对齐序列
            QList<float> beforePeakList = this->calVectorPeak(chopBefore1zhou_half);
            QList<float> before2PeakList = this->calVectorPeak(chopBefore1zhou2_half);

            auto beforePeakMin = std::min_element(std::begin(beforePeakList), std::end(beforePeakList));
            auto before2PeakMin = std::min_element(std::begin(before2PeakList), std::end(before2PeakList));

            int beforeAlign = 0;
            int beforeSameSeq = 0;
            int beforeTrue = 0;

            //一个周波
            for(int i=0; i<chopBefore1zhou_half.size(); i++){
                if(fabs(static_cast<double>(chopBefore1zhou_half.at(i) - *beforePeakMin)) < 0.0000001)
                {
                    beforeAlign = i;
                    break;
                }
            }

            for(int j = 1; j<chopBefore1zhou_half.size() - beforeAlign; j++){
                if(fabs(static_cast<double>(chopBefore1zhou_half.at(beforeAlign + j) - *beforePeakMin)) < 0.0000001)
                {
                    beforeSameSeq = j;
                    break;
                }
            }
            beforeTrue = beforeAlign +  beforeSameSeq/2;

            int before2Align = 0;
            int before2SameSeq = 0;
            int before2True = 0;
            //一个周波
            for(int i=0; i<chopBefore1zhou2_half.size(); i++){
                if(fabs(static_cast<double>(chopBefore1zhou2_half.at(i) - *before2PeakMin)) < 0.0000001)
                {
                    before2Align = i;
                    break;
                }
            }

            for(int j = 1; j<chopBefore1zhou2_half.size() - before2Align; j++){
                if(fabs(static_cast<double>(chopBefore1zhou2_half.at(before2Align + j) - *before2PeakMin)) < 0.0000001)
                {
                    before2SameSeq = j;
                    break;
                }
            }
            before2True = before2Align + before2SameSeq/2;

            varAlign = beforeTrue*(multivar/t_wavePoints1) - before2True*(multivar/t_wavePoints2);
            chValueStatus = true;
            return varAlign;
        }else if(!zeroAFloat && !zeroAFloat2
                 && zeroBFloat && zeroBFloat2)
        {
            //被对齐序列
            QList<float> afterPeakList = this->calVectorPeak(chopAfter1zhou_half);
            QList<float> after2PeakList = this->calVectorPeak(chopAfter1zhou2_half);

            auto afterPeakMin = std::min_element(std::begin(afterPeakList), std::end(afterPeakList));
            auto after2PeakMin = std::min_element(std::begin(after2PeakList), std::end(after2PeakList));

            int afterAlign = 0;
            int afterSameSeq = 0;
            int afterTrue = 0;

            //一个周波
            for(int i=0; i<chopAfter1zhou_half.size(); i++){
                if(fabs(static_cast<double>(chopAfter1zhou_half.at(i) - *afterPeakMin)) < 0.0000001)
                {
                    afterAlign = i;
                    break;
                }
            }

            for(int j=1; j<chopAfter1zhou_half.size() - afterAlign; j++){
                if(fabs(static_cast<double>(chopAfter1zhou_half.at(afterAlign + j) - *afterPeakMin)) < 0.0000001)
                {
                    afterSameSeq = j;
                    break;
                }
            }
            afterTrue = afterAlign +  afterSameSeq/2;

            int after2Align = 0;
            int after2SameSeq = 0;
            int after2True = 0;
            //一个周波
            for(int i=0; i<chopAfter1zhou2_half.size(); i++){
                if(fabs(static_cast<double>(chopAfter1zhou2_half.at(i) - *after2PeakMin)) < 0.0000001)
                {
                    after2Align = i;
                    break;
                }
            }

            for(int j = 1; j<chopAfter1zhou2_half.size() - after2Align; j++){
                if(fabs(static_cast<double>(chopAfter1zhou2_half.at(after2Align + j) - *after2PeakMin)) < 0.0000001)
                {
                    after2SameSeq = j;
                    break;
                }
            }
            after2True = after2Align + after2SameSeq/2;

            varAlign = afterTrue*(multivar/t_wavePoints1) - after2True*(multivar/t_wavePoints2);
            chValueStatus = true;
            return varAlign;
        }else if(!zeroAFloat && !zeroAFloat2 && !zeroBFloat && !zeroBFloat2){
            chValueStatus = false;
            qDebug() << "该通道无采样数据";
        }else{
            qDebug() << "比对通道一个有值，一个没有值，异常退出";
            exit(0);
        }
    }

    //如果突变点时刻一致
    else if(!ssRet && !mesRet){
        //只用突变前一个周波， 突变后一个周波
        QVector<float> chopBefore1zhou_half;
        QVector<float> chopBefore1zhou2_half;

        QVector<float> chopAfter1zhou_half;
        QVector<float> chopAfter1zhou2_half;

//************往前算***********
//        for(int i=2*t_wavePoints1 - 1; i<sampleBefore1zhou.size(); i++){
//            chopBefore1zhou_half.append(sampleBefore1zhou.at(i));
//        }

//        for(int i=2*t_wavePoints2 - 1; i<sampleBefore1zhou2.size(); i++){
//            chopBefore1zhou2_half.append(sampleBefore1zhou2.at(i));
//        }

//************往后算***********
        for(int i=t_wavePoints1 - 1; i<sampleBefore1zhou.size(); i++){
            chopBefore1zhou_half.append(sampleBefore1zhou.at(i));
        }

        for(int i=t_wavePoints2 - 1; i<sampleBefore1zhou2.size(); i++){
            chopBefore1zhou2_half.append(sampleBefore1zhou2.at(i));
        }

        for(int i=0; i<t_wavePoints1; i++){
            chopAfter1zhou_half.append(sampleAfter1zhou.at(i));
        }

        for(int i=0; i<t_wavePoints2; i++){
            chopAfter1zhou2_half.append(sampleAfter1zhou2.at(i));
        }

        //A段是否启动
        bool zeroAFloat = false;
        bool zeroAFloat2 = false;

        //B段是否启动
        bool zeroBFloat = false;
        bool zeroBFloat2 = false;

        double sumAFloat = 0.0;
        double sumAFloat2 = 0.0;
        double sumBFloat = 0.0;
        double sumBFloat2 = 0.0;

        double aveAFloat = 0.0;
        double aveAFloat2 = 0.0;
        double aveBFloat = 0.0;
        double aveBFloat2 = 0.0;

        //A段去掉突变点附近十个点;
        for(int i=0; i<sampleBefore1zhou.size()-10; i++){
            sumAFloat += static_cast<double>(fabs(sampleBefore1zhou.at(i)));
        }
        aveAFloat = sumAFloat/(sampleBefore1zhou.size()-10);
        if(fabs(aveAFloat) > 0.2)
        {
            zeroAFloat = true;
        }else
        {
            zeroAFloat = false;
        }

        for(int i=0; i<sampleBefore1zhou2.size()-10; i++){
            sumAFloat2 += static_cast<double>(fabs(sampleBefore1zhou2.at(i)));
        }
        aveAFloat2 = sumAFloat2/(sampleBefore1zhou2.size()-10);
        if(fabs(aveAFloat2) > 0.2)
        {
            zeroAFloat2 = true;
        }else
        {
            zeroAFloat2 = false;
        }

        foreach(float var, sampleAfter1zhou){
            sumBFloat += static_cast<double>(fabs(var));
        }
        aveBFloat = sumBFloat/sampleAfter1zhou.size();
        if(fabs(aveBFloat) > 0.2)
        {
            zeroBFloat = true;
        }else
        {
            zeroBFloat = false;
        }

        foreach(float var, sampleAfter1zhou2){
            sumBFloat2 += static_cast<double>(fabs(var));
        }
        aveBFloat2 = sumBFloat2/sampleAfter1zhou2.size();
        if(fabs(aveBFloat2) > 0.2)
        {
            zeroBFloat2 = true;
        }else
        {
            zeroBFloat2 = false;
        }

        if(!zeroAFloat && !zeroAFloat2 && !zeroBFloat && !zeroBFloat2){
            chValueStatus = false;
        }else if(zeroAFloat && zeroAFloat2)
        {
            chValueStatus = true;
        }else if(!zeroAFloat && !zeroAFloat2 && zeroBFloat && zeroBFloat2){
            chValueStatus = true;
        }else{
            qDebug() << "比对通道一个有值，一个没有值，异常退出";
            exit(0);
        }
        varAlign = 0;
        return varAlign;
    }
    return varAlign;
}

void CompareAlgorithm::calBeforeCompareData(int& varAlign, int& multiVar, QString& itemType)
{
    int deltaFactor = varAlign/(multiVar/t_wavePoints2);
    int valueFactor = ceil(effectBefore1zhou2.size()/effectBefore1zhou.size());
    int valueFactorVar = -1;
    for(int i=0; i < effectBefore1zhou.size(); i++)
    {
            t_pointSeqList1.append(t_startPos1 + i);
            insertCompareBefore1.append(effectBefore1zhou.at(i));
        if(0 == effectBefore1zhou2.size()%effectBefore1zhou.size()){
            t_pointSeqList2.append(t_startPos2 + deltaFactor + valueFactor*i);
            insertCompareBefore2.append(effectBefore1zhou2.at(i*valueFactor));
            if(QString::compare(itemType, "C")){
                if(effectBefore1zhou.at(i) < 0.1 && effectBefore1zhou2.at(i*valueFactor) < 0.1){
                    beforeCompareData.append(0);
                    double comparisionRel = 0;
                    relativeError.append(comparisionRel);
                    if(fabs(comparisionRel) < 0.050)
                    {
                        pointConclusion.append(normal);
                    }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                        pointConclusion.append(innormal);
                    }else if(fabs(comparisionRel) >= 0.100){
                        pointConclusion.append(critical);
                    }
                }else if(effectBefore1zhou.at(i) ==0 && effectBefore1zhou2.at(i*valueFactor) == 0){
                    beforeCompareData.append(0);
                    double comparisionRel = 0;
                    relativeError.append(comparisionRel);
                    if(fabs(comparisionRel) < 0.050)
                    {
                        pointConclusion.append(normal);
                    }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                        pointConclusion.append(innormal);
                    }else if(fabs(comparisionRel) >= 0.100){
                        pointConclusion.append(critical);
                    }
                }else if(effectBefore1zhou.at(i) > 0.1 && effectBefore1zhou2.at(i*valueFactor) < 0.001){
                    beforeCompareData.append(0.1);
                    //报异常
                    double comparisionRel = 0.06;
                    relativeError.append(comparisionRel);
                    if(fabs(comparisionRel) < 0.050)
                    {
                        pointConclusion.append(normal);
                    }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                        pointConclusion.append(innormal);
                    }else if(fabs(comparisionRel) >= 0.100){
                        pointConclusion.append(critical);
                    }
                }else{
                    beforeCompareData.append(static_cast<double>(effectBefore1zhou.at(i) - effectBefore1zhou2.at(i*valueFactor)));
                    double comparisionRel = static_cast<double>(effectBefore1zhou.at(i) - effectBefore1zhou2.at(i*valueFactor))/static_cast<double>(effectBefore1zhou2.at(i*valueFactor));
                    relativeError.append(comparisionRel);

                    if(fabs(comparisionRel) < 0.050)
                    {
                        pointConclusion.append(normal);
                    }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                        pointConclusion.append(innormal);
                    }else if(fabs(comparisionRel) >= 0.100){
                        pointConclusion.append(critical);
                    }
                }
            }else if(QString::compare(itemType, "V")){
                if(effectBefore1zhou.at(i) < 0.5 && effectBefore1zhou2.at(i*valueFactor) < 0.5){
                    beforeCompareData.append(0);
                    double comparisionRel = 0;
                    relativeError.append(comparisionRel);
                    if(fabs(comparisionRel) < 0.050)
                    {
                        pointConclusion.append(normal);
                    }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                        pointConclusion.append(innormal);
                    }else if(fabs(comparisionRel) >= 0.100){
                        pointConclusion.append(critical);
                    }
                }else if(effectBefore1zhou.at(i) ==0 && effectBefore1zhou2.at(i*valueFactor)  ==1){
                    beforeCompareData.append(0);
                    double comparisionRel = 0;
                    relativeError.append(comparisionRel);
                    if(fabs(comparisionRel) < 0.050)
                    {
                        pointConclusion.append(normal);
                    }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                        pointConclusion.append(innormal);
                    }else if(fabs(comparisionRel) >= 0.100){
                        pointConclusion.append(critical);
                    }
                }else if(effectBefore1zhou.at(i) > 0.5 && effectBefore1zhou2.at(i*valueFactor) < 0.001){
                    beforeCompareData.append(0.1);
                    //报异常
                    double comparisionRel = 0.06;
                    relativeError.append(comparisionRel);
                    if(fabs(comparisionRel) < 0.050)
                    {
                        pointConclusion.append(normal);
                    }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                        pointConclusion.append(innormal);
                    }else if(fabs(comparisionRel) >= 0.100){
                        pointConclusion.append(critical);
                    }
                }else{
                    beforeCompareData.append(static_cast<double>(effectBefore1zhou.at(i) - effectBefore1zhou2.at(i*valueFactor)));
                    double comparisionRel = static_cast<double>(effectBefore1zhou.at(i) - effectBefore1zhou2.at(i*valueFactor))/static_cast<double>(effectBefore1zhou2.at(i*valueFactor));
                    relativeError.append(comparisionRel);

                    if(fabs(comparisionRel) < 0.050)
                    {
                        pointConclusion.append(normal);
                    }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                        pointConclusion.append(innormal);
                    }else if(fabs(comparisionRel) >= 0.100){
                        pointConclusion.append(critical);
                    }
                }
            }
            //不能整除
        }else if(effectBefore1zhou2.size()%effectBefore1zhou.size()!=0)
        {
            //采样频率为1.2K
            if(i%3 == 0|| i%3 ==1){
                valueFactorVar += valueFactor;
                t_pointSeqList2.append(t_startPos2 + deltaFactor + valueFactorVar);
                insertCompareBefore2.append(effectBefore1zhou2.at(valueFactorVar));
            }

            if(i%3 == 2){
                valueFactorVar += valueFactor + 1;
                t_pointSeqList2.append(t_startPos2 + deltaFactor + valueFactorVar);
                insertCompareBefore2.append(effectBefore1zhou2.at(valueFactorVar));
            }

            if(QString::compare(itemType, "C")){
            if(effectBefore1zhou.at(i) < 0.1 && effectBefore1zhou2.at(valueFactorVar) < 0.1){
                beforeCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
            else if(effectBefore1zhou.at(i) == 0 && effectBefore1zhou2.at(valueFactorVar) ==0){
                beforeCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else if(effectBefore1zhou.at(i) >0.1 && effectBefore1zhou2.at(valueFactorVar) == 0)
            {
                beforeCompareData.append(0.1);
                double comparisionRel = 0.06;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
            else{
                beforeCompareData.append(static_cast<double>(effectBefore1zhou.at(i) - effectBefore1zhou2.at(valueFactorVar)));
                double comparisionRel = static_cast<double>((effectBefore1zhou.at(i) - effectBefore1zhou2.at(valueFactorVar)))/static_cast<double>(effectBefore1zhou2.at(valueFactorVar));
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
            }else if(QString::compare(itemType, "V")){
            if(effectBefore1zhou.at(i) < 0.5 && effectBefore1zhou2.at(valueFactorVar) < 0.5){
                beforeCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
            else if(effectBefore1zhou.at(i) == 0 && effectBefore1zhou2.at(valueFactorVar) ==0){
                beforeCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else if(effectBefore1zhou.at(i) >0.5 && effectBefore1zhou2.at(valueFactorVar) == 0)
            {
                beforeCompareData.append(0.1);
                double comparisionRel = 0.06;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
            else{
                beforeCompareData.append(static_cast<double>(effectBefore1zhou.at(i) - effectBefore1zhou2.at(valueFactorVar)));
                double comparisionRel = static_cast<double>((effectBefore1zhou.at(i) - effectBefore1zhou2.at(valueFactorVar)))/static_cast<double>(effectBefore1zhou2.at(valueFactorVar));
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
            }
        }
     }
}

void CompareAlgorithm::calAfterCompareData(int& multiVar, QString& itemType)
{
    int valueFactor = effectAfter1zhou2.size()/effectAfter1zhou.size();

    int afterStartPos = t_pointSeqList1.last() + 1;
    int afterStartPos2 = 0.0;
    afterStartPos2 = t_pointSeqList2.last() + valueFactor;
    int valueFactorVar = -1;
    for(int i=0; i < effectAfter1zhou.size(); i++)
    {
        t_pointSeqList1.append(afterStartPos + i);
        //保护采样点
        insertCompareAfter1.append(effectAfter1zhou.at(i));
        if(0 == effectAfter1zhou2.size()%effectAfter1zhou.size()){
            t_pointSeqList2.append(afterStartPos2 + (valueFactor*i));
            insertCompareAfter2.append(effectAfter1zhou2.at(i*valueFactor));
            if(QString::compare(itemType, "C")){
            //采集采样点
            if(effectAfter1zhou.at(i) < 0.1 && effectAfter1zhou2.at(i*valueFactor) < 0.1){
                afterCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else if(effectAfter1zhou.at(i) == 0 && effectAfter1zhou2.at(i*valueFactor) == 0){
                afterCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }

            }else if(effectAfter1zhou.at(i) >0.1 && effectAfter1zhou2.at(i*valueFactor) == 0)
            {
                afterCompareData.append(0.1);
                double comparisionRel = 0.06;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else {
                afterCompareData.append(static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactor*i)));
                double comparisionRel = static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactor*i))/static_cast<double>(effectAfter1zhou2.at(valueFactor*i));
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
            }else if(QString::compare(itemType, "V")){
            if(effectAfter1zhou.at(i) < 0.5 && effectAfter1zhou2.at(i*valueFactor) < 0.5){
                afterCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else if(effectAfter1zhou.at(i) == 0 && effectAfter1zhou2.at(i*valueFactor) == 0){
                afterCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }

            }else if(effectAfter1zhou.at(i) >0.5 && effectAfter1zhou2.at(i*valueFactor) == 0)
            {
                afterCompareData.append(0.1);
                double comparisionRel = 0.06;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else {
                afterCompareData.append(static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactor*i)));
                double comparisionRel = static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactor*i))/static_cast<double>(effectAfter1zhou2.at(valueFactor*i));
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
        }
        }else if(effectAfter1zhou2.size()%effectAfter1zhou.size()!=0){
            if(i%3 == 0 || i%3 == 1){
                valueFactorVar += valueFactor;
                t_pointSeqList2.append(afterStartPos2 + valueFactorVar);
                insertCompareAfter2.append(effectAfter1zhou2.at(valueFactorVar));
            }else if(i%3 == 2){
                valueFactorVar += valueFactor + 1;
                t_pointSeqList2.append(afterStartPos2 + valueFactorVar);
                insertCompareAfter2.append(effectAfter1zhou2.at(valueFactorVar));
            }
            if(QString::compare(itemType, "C")){
            if(effectAfter1zhou.at(i) < 0.1 && effectAfter1zhou2.at(valueFactorVar) < 0.1){
                afterCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else if(effectAfter1zhou.at(i) == 0 && effectAfter1zhou2.at(valueFactorVar)== 0){
                afterCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else if(effectAfter1zhou.at(i) > 0.1 && effectAfter1zhou2.at(valueFactorVar) ==0)
            {
                //直接报异常
                afterCompareData.append(0.01);
                double comparisionRel = 0.06;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else{
                afterCompareData.append(static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactorVar)));
                double comparisionRel = static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactorVar))/static_cast<double>(effectAfter1zhou2.at(valueFactorVar));
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
            }else if(QString::compare(itemType, "V")){
            if(effectAfter1zhou.at(i) < 0.5 && effectAfter1zhou2.at(valueFactorVar) < 0.1){
                afterCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else if(effectAfter1zhou.at(i) == 0 && effectAfter1zhou2.at(valueFactorVar)== 0){
                afterCompareData.append(0);
                double comparisionRel = 0;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else{
                afterCompareData.append(static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactorVar)));
                double comparisionRel = static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactorVar))/static_cast<double>(effectAfter1zhou2.at(valueFactorVar));
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
            }
            }else if(effectAfter1zhou.at(i) > 0.1 && effectAfter1zhou2.at(valueFactorVar) ==0)
            {
                //直接报异常
                afterCompareData.append(0.01);
                double comparisionRel = 0.06;
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }else{
                afterCompareData.append(static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactorVar)));
                double comparisionRel = static_cast<double>(effectAfter1zhou.at(i) - effectAfter1zhou2.at(valueFactorVar))/static_cast<double>(effectAfter1zhou2.at(valueFactorVar));
                relativeError.append(comparisionRel);
                if(fabs(comparisionRel) < 0.050)
                {
                    pointConclusion.append(normal);
                }else if(fabs(comparisionRel) >=0.050 && fabs(comparisionRel) < 0.100){
                    pointConclusion.append(innormal);
                }else if(fabs(comparisionRel) >= 0.100){
                    pointConclusion.append(critical);
                }
            }
    }
}

bool CompareAlgorithm::getChValueStatus()
{
    return chValueStatus;
}

QList<QVector<double>> CompareAlgorithm::getCompareDataList() const
{
    QList<QVector<double>> compareDataList;
    compareDataList.append(beforeCompareData);
    compareDataList.append(afterCompareData);

    return compareDataList;
}

QList<QList<int>> CompareAlgorithm::getPointSeqList() const
{
    QList<QList<int>> pointSeqList;
    pointSeqList.append(t_pointSeqList1);
    pointSeqList.append(t_pointSeqList2);
    return pointSeqList;
}

QList<int> CompareAlgorithm::getFirstPos()
{
    QList<int> firstPosList;
    firstPosList.append(t_pointSeqList1.at(0));
    firstPosList.append(t_pointSeqList2.at(0));

    return firstPosList;
}

double CompareAlgorithm::getCompareConclusion()
{
     QVector<double> chopResultVector;
     //每隔半个周波取一个有效值
     for(int i=0; i<relativeError.size(); i+=relativeError.size()/9)
     {
          chopResultVector.append(static_cast<double>(relativeError.at(i)));
     }

     bool criStatus = false;
     bool innStatus = false;
     for(int i=0; i<chopResultVector.size() - 2; i++){
        if(fabs(chopResultVector.at(i)) > 0.10
           &&
           fabs(chopResultVector.at(i + 1)) > 0.10
           &&
           fabs(chopResultVector.at(i + 2)) > 0.10)
        {
           t_compareConclusion = (chopResultVector.at(i) + chopResultVector.at(i+1) + chopResultVector.at(i+2))/3;
           criStatus = true;
        }
        else if(fabs(chopResultVector.at(i)) > 0.05
                &&  fabs(chopResultVector.at(i + 1)) > 0.05
                &&  fabs(chopResultVector.at(i + 2)) > 0.05
                ){
            t_compareConclusion = (chopResultVector.at(i) + chopResultVector.at(i+1) + chopResultVector.at(i+2))/3;
            innStatus = true;
        }else
        {
            t_compareConclusion = 0.0;
        }
     }
     if(criStatus){
         t_result = critical;
     }else if(innStatus && !criStatus)
     {
         t_result = innormal;
     }else if(!criStatus && !innStatus)
     {
         t_result = normal;
     }
     return t_compareConclusion;
}

int CompareAlgorithm::getCompareResult()
{
    return t_result;
}

void CompareAlgorithm::setSurgeTime(const QString& time1, const QString& time2)
{
    t_surgeTime1 = time1;
    t_surgeTime2 = time2;
}

void CompareAlgorithm::setWavePoint(const int& num1, const int& num2)
{
    t_wavePoints1 = num1;
    t_wavePoints2 = num2;
}

void CompareAlgorithm::setStartPoint(const int& num1, const int& num2)
{
    t_startPos1 = num1;
    t_startPos2 = num2;
}

QVector<double> CompareAlgorithm::getRelativeError()
{
    return relativeError;
}

QVector<double> CompareAlgorithm::getAbsoluteError()
{
    absoluteError = beforeCompareData;
    absoluteError.append(afterCompareData);
    return absoluteError;
}

QList<int> CompareAlgorithm::getPointConclusion()
{
    return pointConclusion;
}

double CompareAlgorithm::calRelevence(const QVector<float>& standVec, const QVector<float>& taskVec, int length)
{
    double sumStand = 0.0;
    double sumTask = 0.0;
    double aveStand = 0.0;
    double aveTask = 0.0;

    //求和
    sumStand = std::accumulate(standVec.begin(), standVec.end(), 0.0);
    sumTask = std::accumulate(taskVec.begin(), taskVec.end(), 0.0);

    //求平均值
    aveStand = sumStand/double(length);
    aveTask = sumTask/double(length);

    //计算相关系数
    double R1 = 0.0;
    double R2 = 0.0;
    double R3 = 0.0;
    for(int i = 0; i< length; i++)
    {
        R1 += (static_cast<double>(standVec.at(i)) - aveStand)*(static_cast<double>(taskVec.at(i)) - aveTask);
        R2 += pow((static_cast<double>(standVec.at(i)) - aveStand), 2);
        R3 += pow((static_cast<double>(taskVec.at(i)) - aveTask), 2);
    }

    return (R1/sqrt(R2*R3));
}

double CompareAlgorithm::getRelevence()
{
   //计算相关系数
   QVector<float> standEffectVector;
//   QVector<float> standEffectVector = insertCompareBefore1;
//   standEffectVector.append(insertCompareAfter1);

   QVector<float> taskEffectVector;
//   QVector<float> taskEffectVector = insertCompareBefore2;
//   taskEffectVector.append(insertCompareAfter2);

   for(int i=0; i<insertCompareBefore1.size(); i++)
   {
       if(static_cast<double>(insertCompareBefore1.at(i)) < 0.1){
           standEffectVector.append(0);
       }else{
           standEffectVector.append(insertCompareBefore1.at(i));
       }
   }

   for(int i=0; i<insertCompareBefore2.size(); i++)
   {
       if(static_cast<double>(insertCompareBefore2.at(i)) < 0.1){
           taskEffectVector.append(0);
       }else{
           taskEffectVector.append(insertCompareBefore2.at(i));
       }
   }

   for(int i=0; i<insertCompareAfter1.size(); i++)
   {
       if(static_cast<double>(insertCompareAfter1.at(i)) < 0.1){
           standEffectVector.append(0);
       }else{
           standEffectVector.append(insertCompareAfter1.at(i));
       }
   }

   for(int i=0; i<insertCompareAfter2.size(); i++)
   {
       if(static_cast<double>(insertCompareAfter2.at(i)) < 0.1){
           taskEffectVector.append(0);
       }else{
           taskEffectVector.append(insertCompareAfter2.at(i));
       }
   }

//   qDebug() << standEffectVector << "11111111111111111111111111111";
//   qDebug() << taskEffectVector << "22222222222222222222222222222";
//   qDebug() << standEffectVector.size() << "                " << taskEffectVector.size() << "QQQQQQQQQQQQQQQQ";

   int length = standEffectVector.size();
   return calRelevence(standEffectVector, taskEffectVector, length);
}

