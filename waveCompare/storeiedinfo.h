#ifndef STOREIEDINFO_H
#define STOREIEDINFO_H
#include <QString>
#include <QStringList>

typedef struct storeIed
{
    QString iedName1;
    QString iedName2;
    QString iedName3;
    
    QString iedFile1;
    QString iedFile2;
    QString iedFile3;
}storeIed;

class storeIedinfo
{
public:
    storeIedinfo(QStringList&, QStringList&);
    
private:
    storeIed iedReceived;
};

#endif // STOREIEDINFO_H
