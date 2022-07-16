#ifndef ACKRECORD_H
#define ACKRECORD_H
#include <QString>
#include <QList>
class AckRecord
{
public:
    enum
    {
        ZanTaiTongYuanBiDui,    //0
        JianShiYuJing,          //1
        YiErCiBuDuiYing,        //2
        BaoHuDongZuoZhenDuan,   //3
        HuiLuLianLuYiChang,     //4
        HuiLuDuanKouYiChang,    //5
        MmsConnection,          //6
        SteadyTaskTM,           //7
        SteadyTaskTS,           //8
        CRC,                    //9
        TimeSyn                 //10
    };
public:
    AckRecord();
    ~AckRecord();
public:
    bool ackRecord(int type);
    bool ackRecord(int type, QList<int> &lst);
private:
    QString m_connectionName;
};
#endif // ACKRECORD_H
