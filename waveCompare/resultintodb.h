#ifndef RESULTINTODB_H
#define RESULTINTODB_H
#include <QString>
#include <compareresult.h>
#include <reportWriter.h>

class ResultIntoDb : public QObject
{
    Q_OBJECT
public:
    ResultIntoDb();
    ResultIntoDb(QStringList&, QStringList&, QStringList&);
    ~ResultIntoDb();

    bool productResult();
    //计算保护比对结果
    bool productProtResult();
    bool productResult(int &, xmlINFO &);
    QString getSurgeTime(const int& num);
    QString getReportTime();
    QMultiMap<QStringList, QStringList> getProtKeyWordMap();
    QStringList getKeyWordList();

private:
    QString cfgFile1;
    QString cfgFile2;
    QString hdrFile1;
    QString hdrFile2;

    QString iedName1;
    QString iedName2;

    QStringList keyWordList;
    QStringList keyWordListRef2;
    QMap<QStringList, QList<int> > chKeyMap;
    QMap<QStringList, QStringList> chChanelNameMap;
    //比对值序列集
    QList<QList<QVector<double>>> chCompareDatalistMapList;
    //比对点序号序列集
    QList<QList<QList<int>>> chPointSeqlistMapList;
    //比对结论
    QList<double> chCompareConclusionList;
    //相对误差
    QList<QVector<double>> relativeErrorVectorList;
    //绝对误差
    QList<QVector<double>> absoluteErrorVectorList;
    //点结论
    QList<QList<int>>  pointConclusionlistList;

    //开关量
    QStringList dcKeyWordList;
    QMap<QStringList, QList<int>> dcChKeyMap;
    QMap<QStringList, QStringList> dcChanelNameMap;
    //开关通道动作时延结论序列集
    QList<QList<int>> dcConclusionlistList;
    //开关动作时延比对结果序列集
    QList<QList<int>> dcAckResultlistList;
    //开关是否动作结论
    QList<QStringList> jumpAckResultlistList;
    //开关动作时延值
    QList<QList<int>> dcAckDelaylistList;
    //缺少的开关量通道号
    QList<int> lackNumlistList;

public:
    QString reportTime;
    QMultiMap<QStringList, QStringList> protkeyWordMap;
};

#endif // RESULTINTODB_H
