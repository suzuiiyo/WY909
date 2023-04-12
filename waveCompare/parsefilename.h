#ifndef PARSEFILENAME_H
#define PARSEFILENAME_H

#include <QStringList>
#include <QString>
#include <QMap>

class ParseFileName
{
public:
    ParseFileName();

    ~ParseFileName();
    QStringList getDataList(const QString &, const QString &);
    QStringList getIedNameList();
    void getWordList(QStringList&);
    QStringList getDeviceTypeList();
    QStringList getFaultSeqList();

private:
    bool fileStatus;
    QStringList nameList;
    QStringList wordList;
    QStringList wordList2;
};

#endif // PARSEFILENAME_H
