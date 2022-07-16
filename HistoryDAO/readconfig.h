#ifndef READCONFIG_H
#define READCONFIG_H
#include "sqlitedbconfig.h"
class ReadConfig
{
public:
    ReadConfig();
    ~ReadConfig();
public:
    QString getConfigPath();
    SqliteDBConfig::Ptr getSqliteDBConfig(const QString &filePath);
};
#endif // READCONFIG_H
