#ifndef LOADCOMTRADE_H
#define LOADCOMTRADE_H
#include "CmtdFile.h"
#include <QMap>
#include "WyCal.h"
#include "GenerateReport.h"
#include <QTextCodec>

class LoadComtrade : public QObject
{
    Q_OBJECT
public:
    explicit LoadComtrade(QObject *parent=0);
    ~LoadComtrade();

    enum{
        continuous,
        uncontinuous
    };

    bool init(const QString&);
    //获得指定通道采样值
    QMap<QVector<float>, QVector<float>> getSampleValue(int);
    //获得dataRef2开关量通道状态
    int getSwitchStatus(const int&);
    //获得开关量变位状态
    QList<int> getSwitchDelay(const int&);
    //获得通道名称
    QStringList getChName();
    //获得开关量通道名称
    QStringList getSwitchName();
    //是否成功读取comtrade文件
    bool Func_LoadCmtdFile(CCmtdFile*, const QString&);
    //获取采样点数和突变点时刻
    QMap<QDateTime, int> getWavePoints();
    //获取模拟量通道总数和开关量通道总数
    QMap<int, int> getChTotal();
    //获得起始点序号
    int getStartPos(const int&);
    //计算录波时长
    double getTotalTime();
    //获得最左时刻
    QDateTime getLeftTime();
    //获得开关量通道id
    QVector<int> getDchIdVector();

private:
    CCmtdFile* p_cmtdFile;
    QTextCodec* utf8;
    int wavePoints;
    int nTbPos;

    //是否继保设备
    bool jibaoFile;

    //最左时刻   和突变零时刻
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
