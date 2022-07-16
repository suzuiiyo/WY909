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
    
    QMap<int, int> getCountMap1();
    QMap<int, int> getCountMap2();

    //获得总录波时长
    double getTotalTime();
    //获得最左点时刻
    QList<QDateTime> getLeftTimeList();

    //获得采样值
    QMap<QVector<float>, QVector<float>> getSampleValueMap1(const int);
    //获得通道名称
    QStringList getChanelNameList1();
    //获得周波系数，包括采样点个数和突变时刻
    QMap<QDateTime, int> getChopFactor1();
    //获得本周波第一个采样点的序号
    int getStartPos1();

    QMap<QVector<float>, QVector<float>> getSampleValueMap2(const int);
    QStringList getChanelNameList2();
    QMap<QDateTime, int> getChopFactor2();
    int getStartPos2();

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
    QList<int> getSwitchStatusList1(const int);
    //获得通道名称
    QStringList getSwChanelNameList1();

    QList<int> getSwitchStatusList2(const int);
    QStringList getSwChanelNameList2();

    //获得开关量通道索引序列
    QVector<int> getDchIdVector1();
    QVector<int> getDchIdVector2();
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
    
    QMap<QDateTime, int> chopFactor1;
    QMap<QDateTime, int> chopFactor2;
};

#endif // CALPARAMETER_H
