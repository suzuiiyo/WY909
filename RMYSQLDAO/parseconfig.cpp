#include <QFile>
#include <QDomDocument>
#include <QVariant>
#include <QProcessEnvironment>
#include <QObject>
#include <QVariant>
#include <QFileInfo>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include "parseconfig.h"
ParseConfig::ParseConfig()
{

}

ParseConfig::~ParseConfig()
{

}

DBConfig::Ptr ParseConfig::parse(int type, const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return NULL;
    }

    QString fileData = file.readAll();
    file.close();

    QJsonParseError parseJsonError;
    QJsonDocument doc = QJsonDocument::fromJson(fileData.toUtf8(), &parseJsonError);
    if(!(parseJsonError.error == QJsonParseError::NoError))
    {
        qDebug()<<QObject::tr("parse json file false!");
        return NULL;
    }

    QJsonObject jsonObject = doc.object();
    if(type==0 && jsonObject.contains(QStringLiteral("MySQLDB")))
    {
        QJsonValue jsonList = jsonObject.value(QStringLiteral("MySQLDB"));
        QJsonObject item = jsonList.toObject();
        DBConfig::Ptr ptr(new DBConfig());
        ptr->setHostName(item["hostAddress"].toString());
        ptr->setPort(item["port"].toInt());
        ptr->setUserName(item["userName"].toString());
        ptr->setPassword(item["password"].toString());

        return ptr;
    }

    return NULL;
}

DBConfig::Ptr ParseConfig::getConfigPath(int type)
{
    QString vPath = QProcessEnvironment::systemEnvironment().value("WY909_HOME");
    QString configPath = "";
    if(vPath != "")
        configPath = vPath + "/appsettings.json";
    else
        configPath = "./appsettings.json";

    QFileInfo fileInfo(configPath);
    if(fileInfo.exists())
    {
        DBConfig::Ptr ptrConfig = this->parse(type, configPath);
        return ptrConfig;
    }

    return NULL;
}
