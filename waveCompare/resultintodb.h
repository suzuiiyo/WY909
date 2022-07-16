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
    QList<QMap<QVector<float>, QVector<float>>> chCompareDatalistMapList;
    //比对点序号序列集
    QList<QMap<QList<int>, QList<int>>> chPointSeqlistMapList;
    //比对结论
    QList<float> chCompareConclusionList;
    //相对误差
    QList<QVector<float>> relativeErrorVectorList;
    //绝对误差
    QList<QVector<float>> absoluteErrorVectorList;
    //点结论
    QList<QList<int>>  pointConclusionlistList;

public:
    QString reportTime;
    QMultiMap<QStringList, QStringList> protkeyWordMap;
};

#endif // RESULTINTODB_H
