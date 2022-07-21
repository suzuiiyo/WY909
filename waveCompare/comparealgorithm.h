#ifndef COMPAREALGORITHM_H
#define COMPAREALGORITHM_H
#include <QDateTime>
#include <QObject>
#include <QVector>
#include <QMap>

class CompareAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit CompareAlgorithm(QObject *parent = nullptr);
    explicit CompareAlgorithm(const QList<QVector<float>>&, const QList<QVector<float>>&);
    ~CompareAlgorithm();

    enum pointConc{
        normal,
        innormal,
        critical
    };

    //计算两设备采样频率最小公倍数
    int calMultipleRate(int, int);
    
    //在指定范围内计算采样序列峰值
    QList<float> calVectorPeak(QVector<float>);
    
    //插入0值使得比对序列采样点数一致
    //采样序列1
    QVector<float> calSample1Value(QVector<float>, int);
    //采样序列2
    QVector<float> calSample2Value(QVector<float>, int);
    
    //获取突变前周波采样序列
    QMap<QVector<float>, QVector<float>> getChopBeforeZhou() const;
    //获取突变后周波采样序列
    QMap<QVector<float>, QVector<float>> getChopAfterZhou() const;

    //计算两序列的挑点值序列
    QMap<QVector<float>, QVector<float>> getInsertCompareVector() const;

    //计算对齐位置
    int calAlignPosition();
    //计算突变前比对值
    void calBeforeCompareData(int);
    //计算突变后比对值
    void calAfterCompareData(int);
    
    //获得比对值序列
    QMap<QVector<float>, QVector<float>> getCompareDataMap() const;
    //获得比对点序号序列
    QMap<QList<int>, QList<int>> getPointSeqMap() const;

    //获得比对结论
    float getCompareConclusion();
    
    void setSurgeTime(const QString&, const QString&);
    void setWavePoint(const int&, const int&);
    void setStartPoint(const int&, const int&);
    
    QVector<float> getRelativeError();

    QVector<float> getAbsoluteError();

    QList<int> getPointConclusion();

private:
    //保护和录波启动时间前后判别
    bool transFlag;
    
    //采样点最小公倍数
    int multipleRate;
    
    //突变点时刻
    QString t_surgeTime1;
    QString t_surgeTime2;
    
    //每周波采样点
    int t_wavePoints1;
    int t_wavePoints2;
    
    //起始点序号
    int t_startPos1;
    int t_startPos2;
    
    //基准比对序列突变前采样值序列
    QVector<float> sampleBefore1zhou;
    //基准比对序列突变后采样值序列
    QVector<float> sampleAfter1zhou;
    //参与比对序列突变前采样值序列
    QVector<float> sampleBefore1zhou2;
    //参与比对序列突变后采样值序列
    QVector<float> sampleAfter1zhou2;

    //基准比对序列突变前有效值序列
    QVector<float> effectBefore1zhou;
    //基准比对序列突变后有效值序列
    QVector<float> effectAfter1zhou;
    //参与比对序列突变前有效值序列
    QVector<float> effectBefore1zhou2;
    //参与比对序列突变后采样序列
    QVector<float> effectAfter1zhou2;
    //总序列
    QVector<float> effectTotal1zhou2;

    
    //比对点序列
    QList<int> t_pointSeqList1;
    QList<int> t_pointSeqList2;
    
    //挑点进行比对, 挑出较长序列中进行比对的点的值
    QVector<float> insertCompareBefore1;
    QVector<float> insertCompareBefore2;

    QVector<float> insertCompareAfter1;
    QVector<float> insertCompareAfter2;

    //比对结果序列(百分比)
    QVector<float> beforeCompareData;
    QVector<float> afterCompareData;

    //相对误差
    QVector<float> relativeError;
    //绝对误差
    QVector<float> absoluteError;
    //点结论
    QList<int> pointConclusion;
    
    //比对结论
    float t_compareConclusion;
};

#endif // COMPAREALGORITHM_H
