#ifndef PARSEXML_H
#define PARSEXML_H
#include <QString>
#include "dbconfig.h"
class ParseConfig
{
public:
    ParseConfig();
    ~ParseConfig();
public:
    DBConfig::Ptr getConfigPath(int type);
protected:
    DBConfig::Ptr parse(int type, const QString &filePath);
};
#endif // PARSEXML_H
