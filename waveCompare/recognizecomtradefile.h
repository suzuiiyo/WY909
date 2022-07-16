#ifndef RECOGNIZECOMTRADEFILE_H
#define RECOGNIZECOMTRADEFILE_H
#include <QMap>
#include <resultintodb.h>

class RecognizeComtradeFile
{
public:
    RecognizeComtradeFile(const QString& ,const QString& ,QStringList&);
    ~RecognizeComtradeFile();

    //判断文件是否存在
    bool getFileExistStatus();
    //传入文件是否成功
    bool transCompareFile();
    //获取录波文件名
    bool getFileUpperName();
    bool getFileLowName();
    QMap<QString, QString> getCompareFileMap() const;
    ResultIntoDb* getResultIntoDb();
    ResultIntoDb* ridb;

private:
    bool isFileExist;
    bool upperFlag;
    bool lowFlag;

    //传入文件
    QStringList cfglist;
    QStringList hdrlist;

    QString namePath1;
    QString namePath2;

    QStringList iedNameList;
};

#endif // RECOGNIZECOMTRADEFILE_H
