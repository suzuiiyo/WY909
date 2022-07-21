#ifndef DBUSERINFODAO_H
#define DBUSERINFODAO_H
#include "userinfo.h"
class DBUserInfoDAO
{
public:
    DBUserInfoDAO();
    ~DBUserInfoDAO();
public:
    int countRecord(bool *ok=0);
public:
    UserInfo::Ptr doQuery(const QString &userName, const QString &passward, bool *ok=0);
    UserInfo::List doQuery(bool *ok=0);
    UserInfo::List doQuery(int authorityID, bool *ok=0);
public:
    bool doInsert(const UserInfo::Ptr &ptr);
    bool doInsert(UserInfo::List &lst);
public:
    bool doUpdate(const UserInfo::Ptr &ptr);
    bool doUpdate(UserInfo::List &lst);
public:
    bool doDelete(const UserInfo::Ptr &ptr);
    bool doDelete(UserInfo::List &lst);
public:
    bool doCreateTable();
private:
    QString m_connectionName;
};
#endif // DBUSERINFODAO_H
