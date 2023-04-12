#ifndef LOADCOMTRADE_H
#define LOADCOMTRADE_H
#include "CmtdFile.h"
#include <QMap>
#include "WyCal.h"
#include "GenerateReport.h"
#include <QTextCodec>
#include <cmath>

#define m_dsqt2 sqrt(2)
#define g_dPI 3.1415926

class LoadComtrade : public QObject
{
    Q_OBJECT
public:
    explicit LoadComtrade(QObject *parent=nullptr);
    ~LoadComtrade();

    enum{
        continuous,
        uncontinuous
    };

    bool init(const QString&);
    //获得保护指定通道采样值
    QList<QVector<float>> getSampleValue(const int&, const int&);
    //获得采集指定通道采样值
    QList<QVector<float>> getRecordSampleValue(const int&, const int&, const int&);
    //获得dataRef2开关量通道状态
    int getSwitchStatus(const int&);
    //获得开关量变位状态
    QMap<QString, QList<int>> getSwitchDelayMap(const int&, const int&);
    //获得通道名称
    QStringList getChName();
    //获得开关量通道名称
    QStringList getSwitchName();
    //是否成功读取comtrade文件
    bool Func_LoadCmtdFile(CCmtdFile*, const QString&);
    //获取采样点数
    int getWavePoints();
    //获得突变点时刻
    QString getSurgeTime();
    //获取模拟量通道总数和开关量通道总数
    QList<int> getChTotal();
    //获得起始点序号
    int getStartPos(const int, const int);
    //计算录波时长
    double getTotalTime();
    //获得最左时刻
    QDateTime getLeftTime();
    //获得开关量通道id
    QVector<int> getDchIdVector();
    //获得缺少的开关量数量
    int getlackChNum();

    //修正nTbpos,  兼容模拟量通道先于nTbpos时刻动作
    int getSurgeNum(const int&);

    QVector<float> modifyWholeChop(const int&);
    //计算有效值
    float DFT_CalHarm(float *, int, int, int, int nStep = 1);

    //获取通道号和通道类型映射
    QStringList getChseqItemTypeList();

private:
    CCmtdFile* p_cmtdFile;
    QTextCodec* utf8;
    int wavePoints;
    //启动零时刻序列号
    int nTbPos;
    //通道号和通道类型映射
    QStringList chseqItemTypeList;
    //不连续的开关量通道号数量
    int lackChNum;

    //是否继保设备
    bool jibaoFile;

    //最左时刻   和启动零时刻
    QString strStartTime;
    QString strLeftTime;
    int totalPoints;

    //存储开关量通道id
    QVector<int> dchIdVector;

//    bool readOver;

public slots:
    //    void readThFinished();
};

#endif // LOADCOMTRADE_H
