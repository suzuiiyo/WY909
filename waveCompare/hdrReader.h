#ifndef XMLREADER_H
#define XMLREADER_H
#include <QString>
#include <QFile>
#include <QDomDocument>

class HdrReader
{
public:
    HdrReader(const QString &);
    bool init(const QString &);
    QMap<QString, QMap<QString, QString>> getTrigInfo();
    QSet<QString> getFaultInfo();
    QString getMessValue();
    QString getFaultReason();

private:
    QDomDocument docXML;
    QString hdrFile;
    QString messValue;
    QString faultReason;
};

#endif // XMLREADER_H
