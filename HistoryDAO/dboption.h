#ifndef DBOPTION_H
#define DBOPTION_H
#include <QString>
class DBOption
{
public:
    DBOption();
    ~DBOption();
public:
    bool openFastInsertPattern();
    bool closeFastInsertPattern();
private:
    QString m_connectionName;
};
#endif // DBOPTION_H
