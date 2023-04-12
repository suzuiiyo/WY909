#include <QFile>
#include <QString>
#include <QDomDocument>
#include <QProcessEnvironment>
#include <QDir>
#include <QStringList>
#include <QFileInfo>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>
#include "readconfig.h"
ReadConfig::ReadConfig()
{

}

ReadConfig::~ReadConfig()
{

}

QString ReadConfig::getConfigPath()
{
    QString configPath = "";
    QString pathValue = QProcessEnvironment::systemEnvironment().value("WY909_HOME");
    if(pathValue == "")
    {
        QDir dir("/home/gdwy/WY909/");
        if(!dir.exists())
            return "./config/db/SysConfig.db";
        else
            configPath = "/home/gdwy/WY909/appsettings.json";
    }
    else
        configPath = pathValue + "/appsettings.json";

    SqliteDBConfig::Ptr ptr = this->getSqliteDBConfig(configPath);
    if(ptr && ptr->sqlitePath() != "")
        return ptr->sqlitePath();
    else
        return "/home/gdwy/WY909/config/db/SysConfig.db";
}

SqliteDBConfig::Ptr ReadConfig::getSqliteDBConfig(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return NULL;

    QString fileData = file.readAll();
    file.close();

    QJsonParseError parseJsonError;
    QJsonDocument doc = QJsonDocument::fromJson(fileData.toUtf8(), &parseJsonError);
    if(!(parseJsonError.error == QJsonParseError::NoError))
    {
        qDebug() << QObject::tr("parse json file false!");
        return NULL;
    }

    QJsonObject jsonObject = doc.object();
    if(jsonObject.contains(QStringLiteral("SqliteDB")))
    {
        QJsonValue jsonList = jsonObject.value(QStringLiteral("SqliteDB"));
        QJsonObject item = jsonList.toObject();
        SqliteDBConfig::Ptr ptr(new SqliteDBConfig());
        ptr->setSqlitePath(item["filePath"].toString());

        return ptr;
    }

    return NULL;
}

//SqliteDBConfig::Ptr ReadConfig::getSqliteDBConfig(const QString &filePath)
//{
//    QFile file(filePath);
//    if(!file.open(QFile::ReadOnly | QFile::Text))
//    {
//        return NULL;
//    }

//    QString errorStr;
//    int errorLine;
//    int errorColumn;

//    QDomDocument doc;
//    if(!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
//    {
//        return NULL;
//    }

//    QDomElement root = doc.documentElement();
//    QString root_name = root.tagName();
//    if(root_name == "appset")
//    {
//        QDomNode child_lv1 = root.firstChild();
//        while(!child_lv1.isNull())
//        {
//            QString child_lv1_name = child_lv1.toElement().tagName();
//            if(child_lv1_name == "database")
//            {
//                auto child_lv2 = child_lv1.childNodes();
//                auto child_lv2_ip = child_lv2.at(0).toElement();
//                auto child_lv2_port = child_lv2.at(1).toElement();
//                auto child_lv2_userName = child_lv2.at(2).toElement();
//                auto child_lv2_password = child_lv2.at(3).toElement();
//                auto child_lv2_sqlitePath = child_lv2.at(4).toElement();
//                QString ip = child_lv2_ip.text();
//                int port = child_lv2_port.text().toInt();
//                QString userName = child_lv2_userName.text();
//                QString password = child_lv2_password.text();
//                QString sqlitePath = child_lv2_sqlitePath.text();

//                SqliteDBConfig::Ptr ptr(new SqliteDBConfig());
//                ptr->setHostName(ip);
//                ptr->setPort(port);
//                ptr->setUserName(userName);
//                ptr->setPassword(password);
//                ptr->setSqlitePath(sqlitePath);

//                return ptr;
//            }
//            child_lv1 = child_lv1.nextSibling();
//        }
//    }

//    return NULL;
//}
