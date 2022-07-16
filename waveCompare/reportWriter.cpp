#include "reportWriter.h"
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QCoreApplication>
#include <QDir>

ReportWriter::ReportWriter(const xmlINFO &varInfo, const QString& varTime):
   time(varTime)
{
    resultInfo.bayName = varInfo.bayName;
    resultInfo.station = varInfo.station;
    resultInfo.iedNameList = varInfo.iedNameList;
    resultInfo.iedDescList = varInfo.iedDescList;
    resultInfo.fileNameList = varInfo.fileNameList;

    resultInfo.resultSet = varInfo.resultSet;
}

ReportWriter::~ReportWriter()
{
    
}

bool ReportWriter::createFile()
{
    //打开或创建文件
    QString timeA = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss.zzz").toString("yyyyMMddhhmmss");
    QString fileName = "sourcereport_" + timeA + ".xml";

    QString curWorkPath = QCoreApplication::applicationDirPath();
    QString savePath = curWorkPath + QString("/data/SOURCE/");

    QDir dir(savePath);
    if(!dir.exists()){
        dir.mkpath(savePath);
    }

    file = new QFile(savePath + fileName);                     //相对路径、绝对路径、资源路径都可以
    if(!file->open(QFile::WriteOnly | QFile::Truncate)){       //可以用QIODevice，Truncate表示清空原来的内容
        return false;
    }else{
        return true;
    }
}

void ReportWriter::closeFile()
{
    if(file->isOpen()){
        file->close();
    }
    delete file;
}

void ReportWriter::writeReportThree()
{
    qDebug() << resultInfo.resultSet.size() << "resultInfo长度";
    QDomDocument doc;
    //写入xml头部
    QDomProcessingInstruction instruction;               //添加处理命令
    instruction=doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    //添加根节点
    QDomElement root = doc.createElement("SourceReport");
    root.setAttribute("station", resultInfo.station);
    doc.appendChild(root);
    //添加第一个子节点及其子元素
    QDomElement bay = doc.createElement("Bay");
    bay.setAttribute("name", resultInfo.bayName);

    QDomElement Ied =doc.createElement("Ied");                         //创建子元素
    for(int i=0; i<resultInfo.iedNameList.size(); i++){
        QDomElement IED = doc.createElement("IED");
        IED.setAttribute("name", resultInfo.iedNameList.at(i));
        IED.setAttribute("desc", resultInfo.iedDescList.at(i));
        IED.setAttribute("FileName", resultInfo.fileNameList.at(i));
        Ied.appendChild(IED);
    }
    bay.appendChild(Ied);

    QMap<QStringList, QList<QStringList>> writeScrelistMap;
    QList<QList<QStringList>> writelistTemplistList;
    foreach(QStringList iList, resultInfo.resultSet){
        QList<QStringList> tempList;
        foreach(QStringList jList, resultInfo.resultSet){
            foreach(QStringList kList, resultInfo.resultSet){
                QStringList oneList;
                QStringList twoList;
                QStringList threeList;
                if(iList.at(0) != jList.at(0) && iList.at(3) == jList.at(3)
                   && kList.at(2) == iList.at(2) && kList.at(3) == jList.at(2)
                   && !kList.contains(iList.at(1)) && !kList.contains(jList.at(1))){
                   oneList << iList.at(0) << iList.at(2) << iList.at(4);
                   twoList << jList.at(0) << jList.at(2) << jList.at(4);
                   threeList << iList.at(1) << iList.at(3) << kList.at(4);

                   tempList << oneList << twoList << threeList;
                }
            }
        }
        writelistTemplistList.append(tempList);
    }

    foreach(QList<QStringList> iList, writelistTemplistList){
       foreach(QList<QStringList> jList, writelistTemplistList){
           if(!iList.isEmpty() && !jList.isEmpty() && iList.at(2) == jList.at(2)){
              QList<QStringList> infoTempList;
              infoTempList.append(iList.at(0));
              infoTempList.append(iList.at(1));
              writeScrelistMap.insert(iList.at(2), infoTempList);
           }
       }
    }

    QMap<QStringList, QList<QStringList>>::const_iterator i;
    for(i=writeScrelistMap.constBegin(); i!=writeScrelistMap.constEnd(); i++){
        QDomElement RefChannel = doc.createElement("RefChannel");          //创建子元素

        QDomElement Channel = doc.createElement("Channel");
        Channel.setAttribute("IED", i.key().at(0));
        Channel.setAttribute("name", i.key().at(1));
        RefChannel.appendChild(Channel);

        foreach(QStringList varStrList, i.value()){
           QDomElement Channel = doc.createElement("Channel");
           Channel.setAttribute("IED", varStrList.at(0));
           Channel.setAttribute("name", varStrList.at(1));

           RefChannel.appendChild(Channel);
       }

       QDomElement result = doc.createElement("Result");
       QString desc1 = i.key().at(0) + " " + i.value().at(0).at(0) + " " + i.value().at(0).at(2);
       QString desc2 = i.key().at(0) + " " + i.value().at(1).at(0) + " " + i.value().at(1).at(2);
       QString desc3 = i.value().at(0).at(0) + " " + i.value().at(1).at(0) + " " + i.key().at(2);
       if(QString::compare(i.value().at(0).at(2), i.value().at(1).at(2)) == 0 &&
          QString::compare(i.value().at(0).at(2), i.key().at(2)) == 0 &&
          QString::compare(i.value().at(1).at(2), i.key().at(2)) == 0){
          result.setAttribute("desc", "保护装置AB套与故障录波装置本通道比对结果一致");
       }else{
          result.setAttribute("desc", desc1 + ", " + desc2 + ", " + desc3);
       }

       RefChannel.appendChild(result);
       bay.appendChild(RefChannel);
    }

    root.appendChild(bay);

    bool createSuc = createFile();
    if(createSuc){
       //输出到文件
       QTextStream out_stream(file);
       doc.save(out_stream, 4);    //缩进4格
       qDebug() << "生成报告成功";
    }else{
       qDebug() << "生成报告失败";
    }
    closeFile();
}

void ReportWriter::writeReportTwo()
{
    qDebug() << resultInfo.resultSet.size() << "resultInfo长度";
    QDomDocument doc;
    //写入xml头部
    QDomProcessingInstruction instruction;              //添加处理命令
    instruction=doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    //添加根节点
    QDomElement root = doc.createElement("SourceReport");
    root.setAttribute("station", resultInfo.station);
    doc.appendChild(root);
    //添加第一个子节点及其子元素
    QDomElement bay = doc.createElement("bay");
    bay.setAttribute("name", resultInfo.bayName);

    QDomElement Ied =doc.createElement("Ied");                         //创建子元素
    for(int i=0; i<resultInfo.iedNameList.size(); i++){
        QDomElement IED = doc.createElement("IED");
        IED.setAttribute("name", resultInfo.iedNameList.at(i));
        IED.setAttribute("desc", resultInfo.iedDescList.at(i));
        IED.setAttribute("FileName", resultInfo.fileNameList.at(i));
        Ied.appendChild(IED);
    }
    bay.appendChild(Ied);

    foreach(QStringList iList, resultInfo.resultSet){
        QDomElement RefChannel = doc.createElement("RefChannel");          //创建子元素
        QDomElement Channel = doc.createElement("Channel");
        Channel.setAttribute("IED", resultInfo.iedNameList.at(0));
        Channel.setAttribute("name", iList.at(0));

        QDomElement Channel1 = doc.createElement("Channel");
        Channel1.setAttribute("IED", resultInfo.iedNameList.at(1));
        Channel1.setAttribute("name", iList.at(1));

        RefChannel.appendChild(Channel);
        RefChannel.appendChild(Channel1);

        QDomElement result = doc.createElement("result");
        result.setAttribute("desc", iList.at(2));

        RefChannel.appendChild(result);
        bay.appendChild(RefChannel);
    }

    root.appendChild(bay);
    bool createSuc = createFile();
    if(createSuc){
        //输出到文件
        QTextStream out_stream(file);
        doc.save(out_stream, 4);      //缩进4格
        qDebug() << "生成报告成功";
    }else{
        qDebug() << "生成报告失败";
    }
    closeFile();
}
