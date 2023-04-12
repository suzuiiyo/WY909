#ifndef DBCOLUMNTYPETRANSFORM_H
#define DBCOLUMNTYPETRANSFORM_H
#include <QString>
#include <QList>
class DBColumnTypeTransform
{
public:
    DBColumnTypeTransform();
    ~DBColumnTypeTransform();
public:
    QList<int> toQList(const QString &dataValueType);
    int toInt(const QString &dataValueType);
};
#endif // DBCOLUMNTYPETRANSFORM_H
