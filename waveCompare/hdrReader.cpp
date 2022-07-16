#include "hdrReader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

HdrReader::HdrReader(const QString & fileStr):
    hdrFile(fileStr)
{

}

bool HdrReader::init(const QString &fileStr)
{
    QFile xmlFile(fileStr);
    if(!xmlFile.open(QFile::ReadOnly))
    {
        return false;
    }

    if(!docXML.setContent(&xmlFile))
    {
        xmlFile.close();
        return false;
    }else{
        xmlFile.close();
        return true;
    }
}

QMap<QString, QMap<QString, QString> > HdrReader::getTrigInfo()
{
    QMap<QString, QMap<QString, QString>> trigMap;
    QMap<QString, QString> valueMap;
    QString name;
    QString value;
    QString setting;

    bool isOk = init(hdrFile);
    if(isOk){
        QDomElement xmlRoot = docXML.documentElement();		//return root node
        QDomNode domNode = xmlRoot.firstChild();		//first child node
        while(!domNode.isNull())		//if node is not empty
        {
            if(domNode.isElement())		//if node is element
            {
                QDomElement domElement = domNode.toElement();
                if(domElement.tagName() == "TrigInfo"){
                    QDomNodeList sonNodeList = domElement.childNodes();
                    for(int i=0; i<sonNodeList.size(); i++){
                        if(sonNodeList.at(i).toElement().tagName()=="name"){
                            name = QString(sonNodeList.at(i).toElement().text());
                        }else if(sonNodeList.at(i).toElement().tagName()=="value"){
                            value = QString(sonNodeList.at(i).toElement().text());
                        }else if(sonNodeList.at(i).toElement().tagName()=="setting"){
                            setting = QString(sonNodeList.at(i).toElement().text());
                        }
                    }
                    valueMap.insert(value, setting);
                    trigMap.insert(name, valueMap);
                }
                //next bro node, nextSiblingElement() is next bro element
                domElement = domElement.nextSiblingElement();
            }
            domNode = domNode.nextSibling();
        }
    }
    return trigMap;
}

QSet<QString> HdrReader::getFaultInfo()
{
    QSet<QString> faultInfoSet;
    QString time;
    QString name;
    QString value;
    QString unit;

    bool isOk = init(hdrFile);
    if(isOk){
        QDomElement xmlRoot = docXML.documentElement();
        QDomNode domNode = xmlRoot.firstChild();

        while (!domNode.isNull()){
            if(domNode.isElement())
            {
                QDomElement domElement = domNode.toElement();
                if(domElement.tagName() == "FaultInfo"){
                   QDomNodeList sonNodeList = domElement.childNodes();
                   QString faultInfo;
                   for(int i=0; i<sonNodeList.size(); i++){
                       if(sonNodeList.at(i).toElement().tagName()=="time"){
                          time = QString(sonNodeList.at(i).toElement().text());
                       }else if(sonNodeList.at(i).toElement().tagName()=="name"){
                          name = QString(sonNodeList.at(i).toElement().text());
                       }else if(sonNodeList.at(i).toElement().tagName()=="value"){
                          value = QString(sonNodeList.at(i).toElement().text());
                       }else if(sonNodeList.at(i).toElement().tagName()=="unit"){
                          unit = QString(sonNodeList.at(i).toElement().text());
                       }
                    }
                    faultInfo.append("<FaultInfo>");
                    faultInfo.append("<time>");
                    faultInfo.append(time);
                    faultInfo.append("</time>");
                    faultInfo.append("<name>");
                    faultInfo.append(name);
                    faultInfo.append("</name>");
                    faultInfo.append("<value>");
                    faultInfo.append(value);
                    faultInfo.append("</value>");
                    faultInfo.append("<unit>");
                    faultInfo.append(unit);
                    faultInfo.append("</unit>");
                    faultInfo.append("</FaultInfo>");
                    faultInfoSet.insert(faultInfo);

                    if(name.contains("测距")){
                        messValue = value + unit;
                    }else if(name.contains("相别") || name.contains("类型")){
                        faultReason = value;
                    }
                }
                domElement = domElement.nextSiblingElement();
            }
            domNode = domNode.nextSibling();
        }
    }
    return faultInfoSet;
}

QString HdrReader::getMessValue()
{
    return messValue;
}

QString HdrReader::getFaultReason()
{
    return faultReason;
}
