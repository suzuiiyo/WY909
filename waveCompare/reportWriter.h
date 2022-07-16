#ifndef XMLPROCESS_H
#define XMLPROCESS_H

#include <QDomDocument>
#include <QStringList>
#include <QFile>
#include <QSet>

typedef struct xmlINFO{
    QString station;
    QString bayName;
    QStringList iedNameList;

    QStringList iedDescList;

    QStringList fileNameList;

    QSet<QStringList> resultSet;
}xmlINFO;

class ReportWriter
{
public:
    explicit ReportWriter(const xmlINFO &, const QString&);
    ~ReportWriter();

    bool createFile();
    void closeFile();
    void writeReportThree();
    void writeReportTwo();

private:
    xmlINFO resultInfo;
    int iCount;
    QString time;
    QFile* file;
};

#endif // XMLPROCESS_H
