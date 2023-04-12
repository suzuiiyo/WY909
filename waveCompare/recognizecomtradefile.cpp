#include "recognizecomtradefile.h"
#include <QFile>
#include <QDebug>
#include <QFileInfo>

RecognizeComtradeFile::RecognizeComtradeFile(const QString& var1,const QString& var2, QStringList& var3):
    ridb(nullptr)
    ,isFileExist(true)
    ,upperFlag(false)
    ,lowFlag(false)
    ,namePath1(var1)
    ,namePath2(var2)
    ,iedNameList(var3)
{
    //先存保护, 再存录波
}

RecognizeComtradeFile::~RecognizeComtradeFile()
{
    if(ridb!=nullptr){
        delete ridb;
    }
}

bool RecognizeComtradeFile::getFileUpperName()
{   
    QString standCfgPath = namePath1 + QString(".CFG");
    QString taskCfgPath = namePath2 + QString(".CFG");

    QFile file1(standCfgPath);
    QFile file2(taskCfgPath);

    if(file1.exists() && file2.exists()){
        return true;
    }else{
        return false;
    }
}

bool RecognizeComtradeFile::getFileLowName()
{
    QString standCfgPath = namePath1 + QString(".cfg");
    QString taskCfgPath = namePath2 + QString(".cfg");

    QFile file1(standCfgPath);
    QFile file2(taskCfgPath);

    if(file1.exists() && file2.exists()){
        return true;
    }else{
        return false;
    }
}

ResultIntoDb* RecognizeComtradeFile::getResultIntoDb()
{
    if(ridb==nullptr){
        ridb = new ResultIntoDb(cfglist, hdrlist, iedNameList);
    }
    return ridb;
}

bool RecognizeComtradeFile::transCompareFile()
{
    if(upperFlag){
        QString standCfgPath = namePath1 + QString(".CFG");
        QString taskCfgPath = namePath2 + QString(".CFG");

        QString standHdrPath = namePath1 + QString(".HDR");
        QString taskHdrPath = namePath2 + QString(".HDR");

        cfglist.append(standCfgPath);
        cfglist.append(taskCfgPath);

        hdrlist.append(standHdrPath);
        hdrlist.append(taskHdrPath);

        return true;
    }else if(lowFlag){
        QString standCfgPath = namePath1 + QString(".cfg");
        QString taskCfgPath = namePath2 + QString(".cfg");

        QString standHdrPath = namePath1 + QString(".hdr");
        QString taskHdrPath = namePath2 + QString(".hdr");

        cfglist.append(standCfgPath);
        cfglist.append(taskCfgPath);

        hdrlist.append(standHdrPath);
        hdrlist.append(taskHdrPath);

        return true;
    }else {
        return false;
    }
}

bool RecognizeComtradeFile::getFileExist()
{
    //传入文件
    upperFlag = getFileUpperName();
    lowFlag = getFileLowName();
    if(!upperFlag && !lowFlag){
        isFileExist = false;
    }else{
        isFileExist = true;
    }
    return isFileExist;
}
