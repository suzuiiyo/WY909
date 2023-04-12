#ifndef DBIEDCONFIGHISTORYDAO_H
#define DBIEDCONFIGHISTORYDAO_H
#include <QString>
class DBIedConfigHistoryDAO
{
public:
    DBIedConfigHistoryDAO();
    ~DBIedConfigHistoryDAO();
public:
    bool syn();
private:
    QString m_connectionName;
};
#endif // DBIEDCONFIGHISTORYDAO_H
