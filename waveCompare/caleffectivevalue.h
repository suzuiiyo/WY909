#ifndef CALEFFECTIVEVALUE_H
#define CALEFFECTIVEVALUE_H

#include <QMap>
#include <QVector>
#include <WyCal.h>

class CalEffectiveValue
{
public:
    CalEffectiveValue(const QList<QVector<float>> &, int&, int&, int&, int&, int&);
    ~CalEffectiveValue();

    //取保护A段有效值
    QVector<float> calEffValueBefore(QVector<float>, int&, int&);
    //取采集A段有效值
    QVector<float> calRecordEffValueBefore(QVector<float>, int&, int&, int&);

    QVector<float> calEffValueAfter(QVector<float>, int&);

    float calTrueRms(float *, int, int&);

    QList<QVector<float>> getEffectiveValueList();

private:
    CWyCal* wyCal;
    QString sampleType;
    int t_wavePoint1;
    int t_wavePoint2;
    //保护A段取值
    int t_surgeNum1;
    //采集A段取值
    int t_surgeNum2;

    //采集通道取的第一个点序号
    int t_firPos2;
    //基准比对序列突变前有效值序列
    QVector<float> chopBefore1zhou;
    //基准比对序列突变后有效值序列
    QVector<float> chopAfter1zhou;
    //参与比对序列突变前有效值序列
    QVector<float> chopBefore1zhou2;
    //参与比对序列突变后有效值序列
    QVector<float> chopAfter1zhou2;
};

#endif // CALEFFECTIVEVALUE_H
