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
    void calEffectInsertZero(int&);
    //采样序列2
    void calEffectInsert2Zero(int&, int&);

    //获取突变前周波采样序列
    QList<QVector<float>> getChopBeforeZhou() const;
    //获取突变后周波采样序列
    QList<QVector<float>> getChopAfterZhou() const;

    //计算两序列的挑点值序列
    QList<QVector<float>> getInsertCompareVector() const;

    //计算对齐位置
    int calAlignPosition(int&);
    //计算突变前比对值
    void calBeforeCompareData(int&, int&, QString&);
    //计算突变后比对值
    void calAfterCompareData(int&, QString&);

    //通道是否有采样数据
    bool getChValueStatus();
    //获取通道类型
    QString getChType();

    //获得比对值序列
    QList<QVector<double>> getCompareDataList() const;
    //获得比对点序号序列
    QList<QList<int>> getPointSeqList() const;
    //获得比对段第一个点的序号
    QList<int> getFirstPos();

    //获得比对结论
    double getCompareConclusion();
    int getCompareResult();
    
    void setSurgeTime(const QString&, const QString&);
    void setWavePoint(const int&, const int&);
    void setStartPoint(const int&, const int&);
    
    QVector<double> getRelativeError();

    QVector<double> getAbsoluteError();

    QList<int> getPointConclusion();

    //计算相关系数
    double calRelevence(const QVector<float>&, const QVector<float>&, int length);
    //计算本通道数据相关系数
    double getRelevence();

private:
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

    //插入零值后的有效值序列
    QVector<float> effectZeroBefore1;
    QVector<float> effectZeroBefore2;

    QVector<float> effectZeroAfter1;
    QVector<float> effectZeroAfter2;

    //比对点序列A
    QList<int> t_pointSeqList1;
    QList<int> t_pointSeqList2;
    
    //挑点进行比对, 挑出较长序列中进行比对的点的值
    QVector<float> insertCompareBefore1;
    QVector<float> insertCompareBefore2;

    QVector<float> insertCompareAfter1;
    QVector<float> insertCompareAfter2;

    //比对结果序列(百分比)
    QVector<double> beforeCompareData;
    QVector<double> afterCompareData;

    //记录通道是否有采样值
    bool chValueStatus;

    //相对误差
    QVector<double> relativeError;
    //绝对误差
    QVector<double> absoluteError;
    //点结论
    QList<int> pointConclusion;
    
    //比对结论
    double t_compareConclusion;
    int t_result;
};

#endif // COMPAREALGORITHM_H
