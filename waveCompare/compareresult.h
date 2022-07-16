#ifndef COMPARERESULT_H
#define COMPARERESULT_H
#include <QVector>
#include <QList>
#include <QMap>
#include <QDateTime>
#include "calparameter.h"
#include "comparealgorithm.h"
#include "caleffectivevalue.h"
#include <QDebug>

//namespace  skg {
//    typedef std::uint64_t hash_t;
//    constexpr hash_t prime = 0x100000001B3ull;
//    constexpr hash_t basis = 0xCBF29CE48222325ull;

//    constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
//    {
//        return *str ? hash_compile_time(str+1, (*str ^last_value)* prime) : last_value;
//    }

//    constexpr unsigned long long operator "" _hash(char const* p, size_t)
//    {
//        return hash_compile_time(p);
//    }

    //计算bayName, itemType, setType, phase对应的dataRef
//QMap<QStringList, QStringList> calBayNameCorrMap(const QString&, const QString&, QMap<QString, QStringList>&, QStringList&, QStringList&, QList<int>&);
//QMap<QStringList, QStringList> calBayNameCorrMap(const QString&, const QString&, QMap<QString, QStringList>&, QStringList&, QStringList&);

//QMap<QStringList, QStringList> generaBayNameCorrMap(QMap<QString, QStringList>::const_iterator &, QMap<QString, QStringList>::const_iterator &);
//}

class CompareResult : public QObject
{
    Q_OBJECT
public:
    CompareResult(const QString&, const QString&);
    ~CompareResult();

    enum coc_Sta
    {
        normal = 0,
        innormal = 1,
        critical = 2
    };

    //获取iedname
    QStringList getIedName() const;

    //获取settype
    QStringList getSetType() const;

    //按itemType筛选,sysconfig的一行
    //获取比对ＤataRef, 按setType,  phase别为键筛选
    QMap<QStringList, QStringList> calBayNameCompareRef1Ref2(const QString &, const QString &);
    QMap<QStringList, QStringList> calBayNameCompareRef1(const QString &, const QString &);

    QMap<QStringList, QStringList> calBayNameCompareSwitch(const QString &, const QString &);

    QMap<QStringList, QStringList> getChanelNameMap() const;
        
    QMap<QStringList, QList<int>> getKeyMap() const;

    //模拟量
    QMap<QStringList, QStringList> calBayNameCorrMap(const QString&, const QString&, QMap<QString, QStringList>&, QStringList&, QStringList&, QList<int>&);
    QMap<QStringList, QStringList> calBayNameCorrMap(const QString&, const QString&, QMap<QString, QStringList>&, QStringList&, QStringList&);

    static QMap<QStringList, QStringList> generaBayNameCorrMap(QMap<QString, QStringList>::const_iterator &, QMap<QString, QStringList>::const_iterator &);

    //开关量
    QMap<QStringList, QStringList> calSwitchBayNameCorrMap(const QString&, const QString&, QMap<QString, QStringList>&, QStringList&, QStringList&);
    static QMap<QStringList, QStringList> generaSwitchBayNameCorrMap(QMap<QString, QStringList>::const_iterator &, QMap<QString, QStringList>::const_iterator &);

    //获取比对值序列集
    QList<QMap<QVector<float>, QVector<float>>> getCompareDatalistMapList() const;

    //获取比对点序号序列集
    QList<QMap<QList<int>, QList<int>>> getPointSeqlistMapList() const;
    //获取比对结论
    QList<float> getCompareConclusionList() const;
    //获取比对挑值序列集
    QList<QMap<QVector<float>, QVector<float>>> getInsertCompareDataMapList() const;
    //获取突变点时刻
    QList<QDateTime> getSurgeTimeList() const;

    bool parse2WaveParameterRef2(const QString &, const QString &);
    //获取波形比对关键参数
    bool parse2WaveParameter(const QString &, const QString &);
    //判断dataref2开关量状态
    QStringList respDataRef2(QStringList&);

    //获取开关量比对关键参数
    bool parseSwitchParameter(const QString&, const QString &);
    //获取开关量比对结论

    QStringList getChDescribeList() const;

    QStringList getFinalResultList() const;
    
    QDateTime getReportTime() const;

    QStringList getWordList();

    double getTotalTime();

    double getResetTime1();
    double getResetTime2();

    QList<QVector<float>> getRelativeErrorVectorList() const;

    QList<QVector<float>> getAbsoluteErrorVectorList() const;

    QList<QList<int>> getPointConclusionVectorList() const;

private:
    CalParameter* keyPara;
    CalEffectiveValue* effVal;

    //iEDname
    QStringList iedNameList;

    //Bayname
    QStringList bayNameList;

    //ItemName
    QStringList itemNameList;

    //相别
    QStringList phaseList;

    //item类型
    QStringList itemTypeList;

    //setType
    QStringList setTypeList;

    //通道描述
    QStringList chDescribeList;

    //比对通道号
    //dataRef1
    QStringList chSeqList1;
    //dataRef2
    QStringList chSeqList2;

    //通道名称
    QList<QString> chNameList1;
    QList<QString> chNameList2;

    //开关量
    QStringList swChseqList1;
    QStringList swIedNameList;
    QStringList swBayNameList;
    QStringList swItemNameList;
    QStringList swPhaseList;
    QStringList swItemTypeList;
    QStringList swSetTypeList;
    QStringList swChdescribeList;

    QList<QString> swChNameList1;
    QList<QString> swChNameList2;

    //开关量比对结论



    //突变点时刻
    QDateTime surgeTime1;
    QDateTime surgeTime2;

    //最左点时刻
    QDateTime leftTime1;
    QDateTime leftTime2;

    //录波总时长
    double totalTime;

    //每周波采样点
    int wavePoints1;
    int wavePoints2;

    //起始点序号
    int startPos1;
    int startPos2;
        
    //比对点序列
    QList<int> pointSeqList1;
    QList<int> pointSeqList2;
    
    //通道总数
    QMap<int, int> countMap1;
    QMap<int, int> countMap2;

    //比对结论
    QList<float> compareConclusionList;

    //比对通道关键参数图
    QMap<QStringList, QList<int>> keyMap;
    
    //开关量比对通道关键参数
    QMap<QStringList, QList<int>> keySwitchMap;
    
    //结论生成时间
    QDateTime reportTime;

    //比对挑点值序列
    QList<QMap<QVector<float>, QVector<float>>> insertCompareDataList;
    //比对值序列集
    QList<QMap<QVector<float>, QVector<float>>> compareDatalistMapList;
    //比对点序号序列集
    QList<QMap<QList<int>, QList<int>>> pointSeqlistMapList;
    //相对误差
    QList<QVector<float>> relativeErrorVectorList;
    //绝对误差
    QList<QVector<float>> absoluteErrorVectorList;
    //点结论
    QList<QList<int>> pointConclusionlistList;

    friend class compareAlgorithm;
};

#endif // COMPARERESULT_H
