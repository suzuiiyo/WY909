#include "parsefilename.h"
#include <QDebug>

ParseFileName::ParseFileName()
    : fileStatus(false)
{

}

ParseFileName::~ParseFileName()
{

}

QStringList ParseFileName::getDataList(const QString & filePath1, const QString & filePath2)
{
    QRegExp rx("[^/]+(?!.*/)");
    int p=0;
    int q=0;

    while((p = rx.indexIn(filePath1, p)) != -1)
    {
        nameList.append(rx.cap(0));
        p += rx.matchedLength();
    }

    while((q = rx.indexIn(filePath2, q)) != -1)
    {
        nameList.append(rx.cap(0));
        q += rx.matchedLength();
    }

    return nameList;
}

void ParseFileName::getWordList(QStringList& varNameList)
{
   wordList = varNameList.at(0).split("_");
   wordList2 = varNameList.at(1).split("_");

   if(!wordList.isEmpty() && !wordList2.isEmpty()){
       fileStatus = true;
   }else{
       fileStatus = false;
   }
}

QStringList ParseFileName::getIedNameList()
{
    QStringList iedNameList;
    if(fileStatus){
        QString iedName = wordList.at(0);
        QString iedName2 = wordList2.at(0);

        iedNameList.append(iedName);
        iedNameList.append(iedName2);

        return iedNameList;
    }else{
        return iedNameList;
    }
}

QStringList ParseFileName::getDeviceTypeList()
{
    QStringList deviceTypeList;
    if(fileStatus){
        QString deviceType = wordList.at(1);
        QString deviceType2 = wordList2.at(1);

        deviceTypeList.append(deviceType);
        deviceTypeList.append(deviceType2);

        return deviceTypeList;
     }else{
        return deviceTypeList;
     }
}

QStringList ParseFileName::getFaultSeqList()
{
    QStringList faultSeqList;
    if(fileStatus){
        QString faultSeq = wordList.at(2);
        QString faultSeq2 = wordList2.at(2);

        faultSeqList.append(faultSeq);
        faultSeqList.append(faultSeq2);

        return faultSeqList;
    }else{
        return faultSeqList;
    }
}
