#include <QStringList>
#include <QHash>
#include "dbcolumntypetransform.h"
DBColumnTypeTransform::DBColumnTypeTransform()
{

}

DBColumnTypeTransform::~DBColumnTypeTransform()
{

}

QList<int> DBColumnTypeTransform::toQList(const QString &dataValueType)
{
    QHash<QString, int> hsh{
        {"UNKNOWNTYPE", 0},
        {"BOOLEAN", 1},
        {"BIT_STRING", 2},
        {"INTEGER8", 3},
        {"INTEGER16", 4},
        {"INTEGER32", 5},
        {"INTEGER64", 6},
        {"UNSIGNED8", 7},
        {"UNSIGNED16", 8},
        {"UNSIGNED32", 9},
        {"UNSIGNED64", 10},
        {"FLOAT", 11},
        {"DOUBLE", 12},
        {"OCTET_STRING", 13},
        {"VISIBLE_STRING", 14},
        {"GENERAL_TIME", 15},
        {"BINARY_TIME4", 16},
        {"BINARY_TIME6", 17},
        {"BCD1", 18},
        {"BCD2", 19},
        {"BCD4", 20},
        {"UTCTIME", 21},
        {"UTF8_STRING", 22},
        {"ARRAY", 23}
    };
    QStringList lstStr = dataValueType.split("$");
    QList<int> lst;
    for(int i=0; i<lstStr.size(); i++)
    {
        QString dataTypeStr = lstStr.at(i);
        if(hsh.count(dataTypeStr) != 0)
        {
            int dataType = hsh[dataTypeStr];
            lst.append(dataType);
        }
        else
        {
            lst.append(0);
        }
    }

    return lst;
}

int DBColumnTypeTransform::toInt(const QString &dataValueType)
{
    QHash<QString, int> hsh{
        {"UNKNOWNTYPE", 0},
        {"BOOLEAN", 1},
        {"BIT_STRING", 2},
        {"INTEGER8", 3},
        {"INTEGER16", 4},
        {"INTEGER32", 5},
        {"INTEGER64", 6},
        {"UNSIGNED8", 7},
        {"UNSIGNED16", 8},
        {"UNSIGNED32", 9},
        {"UNSIGNED64", 10},
        {"FLOAT", 11},
        {"DOUBLE", 12},
        {"OCTET_STRING", 13},
        {"VISIBLE_STRING", 14},
        {"GENERAL_TIME", 15},
        {"BINARY_TIME4", 16},
        {"BINARY_TIME6", 17},
        {"BCD1", 18},
        {"BCD2", 19},
        {"BCD4", 20},
        {"UTCTIME", 21},
        {"UTF8_STRING", 22},
        {"ARRAY", 23}
    };

    int dataType = hsh[dataValueType];

    return dataType;
}
