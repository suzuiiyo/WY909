#ifndef CALEFFECTIVEVALUE_H
#define CALEFFECTIVEVALUE_H

#include <QMap>
#include <QVector>
#include <WyCal.h>

class CalEffectiveValue
{
public:
    CalEffectiveValue(const QList<QVector<float>> &, int, int);
    ~CalEffectiveValue();

    QVector<float> calEffValueBefore(QVector<float>, int);

    QVector<float> calEffValueAfter(QVector<float>, int);

    QList<QVector<float>> getEffectiveValueList();

private:
    CWyCal* wyCal;
    QString sampleType;
    int t_wavePoint1;
    int t_wavePoint2;
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
