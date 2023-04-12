#ifndef CALPARAMETER_H
#define CALPARAMETER_H
#include <QMap>
#include <QMultiMap>
#include "loadcomtrade.h"
#include "chanelparadao.h"
#include "QList"

class CalParameter : public QObject
{
    Q_OBJECT
public:
    explicit CalParameter(QString, QString);
    ~CalParameter();

    //初始化
    bool getCalInit();
    bool getComtradeInit();
    //获得通道号
    QStringList getChanelRef1List();
    QStringList getChanelRef2List();
    //获得通道相关参数
    QStringList getIedNameList();
    QStringList getBayNameList();
    QStringList getItemNameList();
    QStringList getItemTypeList();
    QStringList getPhaseList();
    QStringList getSetTypeList();
    //获得通道的相关描述
    QStringList getchDescribeList();
    
    QList<int> getCountList1();
    QList<int> getCountList2();

    //获得总录波时长
    double getTotalTime();
    //获得最左点时刻
    QList<QDateTime> getLeftTimeList();

    //获得采样值
    QList<QVector<float>> getSampleValueList1(const int&);
    //获得通道名称
    QStringList getChanelNameList1();
    //获得周波系数，采样点个数和突变时刻
    int getWavePoint1();
    QString getSurgeTime1();
    //获得本周波第一个采样点的序号
    int getStartPos1(const int&);

    QList<QVector<float>> getSampleValueList2(const int&, const int&);
    QStringList getChanelNameList2();
    int getWavePoint2();
    QString getSurgeTime2();
    int getStartPos2(const int&);

    //修正启动零时刻nTbPos;
    int modifyNtbpos(const int&, const int&);

    //获得dataRef2开关量通道的值
    int getDchanelValue(const int);

    //开关量
    //获得通道号
    QStringList getSwChanelRef1List();
    //获得通道相关参数
    QStringList getSwIedNameList();
    QStringList getSwBayNameList();
    QStringList getSwItemNameList();
    QStringList getSwItemTypeList();
    QStringList getSwPhaseList();
    QStringList getSwSetTypeList();
    //获得通道的相关描述
    QStringList getSwchDescribeList();

    //获得开关量状态
    QMap<QString, QList<int>> getSwitchStatusMap1(const int&, const int&);
    //获得通道名称
    QStringList getSwChanelNameList1();

    QMap<QString, QList<int>> getSwitchStatusMap2(const int&, const int&);
    QStringList getSwChanelNameList2();

    //获得开关量通道索引序列
    QVector<int> getDchIdVector1();
    QVector<int> getDchIdVector2();

    //获得开关量缺少的序号总数
    QList<int> getSwLackNumList();

    //获得第一个文件的通道号和通道类型映射
    QStringList getChseqTypeList();

    //获得保护突变点
    int getSurgeNum(int);
    //获得录波突变点
    int getSurgeNum2(int);

    //判断模拟量和开关量配制表是否为空
    bool getChanelDataListStatus();
    bool getSwChanelDataListStatus();

    //获取采集本通道第一个点的位置
    int getRecordFirPos(int, int);

private:
    LoadComtrade* openComtrade;
    LoadComtrade* openComtrade2;
    ChanelParaDAO* chanelPara;

    //模拟量通道参数
    QList<QStringList> chanelDataList;
    //开关量通道参数
    QList<QStringList> swChanelDataList;

    QString strPath1;
    QString strPath2;
    
    int wavePoints1;
    int wavePoints2;

    QString tmSurge1;
    QString tmSurge2;

};

#endif // CALPARAMETER_H
