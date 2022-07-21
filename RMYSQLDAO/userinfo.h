#ifndef USERINFO_H
#define USERINFO_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class UserInfo
{
public:
    typedef QSharedPointer<UserInfo> Ptr;
    typedef QList<Ptr> List;
public:
    UserInfo();
    ~UserInfo();
public:
    int     GUID() const;
    QString userName() const;
    QString nickName() const;
    int     authorityID() const;
    QString authorityDesc() const;
    QString passward() const;
    QString createTime() const;
    QString lastUpdateTime() const;
public:
    void setGUID(int guid);
    void setUserName(const QString &userName);
    void setNickName(const QString &nickName);
    void setAuthorityID(int authorityID);
    void setAuthorityDesc(const QString &authorityDesc);
    void setPassward(const QString &passward);
    void setCreateTime(const QString &createTime);
    void setLastUpdateTime(const QString &lastUpdateTime);
private:
    int     m_GUID;
    QString m_userName;
    QString m_nickName;
    int     m_authorityID;
    QString m_authorityDesc;
    QString m_passward;
    QString m_createTime;
    QString m_lastUpdateTime;
private:
    friend class DBUserInfoDAO;
};

inline int UserInfo::GUID() const
{ return m_GUID;}

inline void UserInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString UserInfo::userName() const
{ return m_userName;}

inline void UserInfo::setUserName(const QString &userName)
{ m_userName = userName;}

inline QString UserInfo::nickName() const
{ return m_nickName;}

inline void UserInfo::setNickName(const QString &nickName)
{ m_nickName = nickName;}

inline int UserInfo::authorityID() const
{ return m_authorityID;}

inline void UserInfo::setAuthorityID(int authorityID)
{ m_authorityID = authorityID;}

inline QString UserInfo::authorityDesc() const
{ return m_authorityDesc;}

inline void UserInfo::setAuthorityDesc(const QString &authorityDesc)
{ m_authorityDesc = authorityDesc;}

inline QString UserInfo::passward() const
{ return m_passward;}

inline void UserInfo::setPassward(const QString &passward)
{ m_passward = passward;}

inline QString UserInfo::createTime() const
{ return m_createTime;}

inline void UserInfo::setCreateTime(const QString &createTime)
{ m_createTime = createTime;}

inline QString UserInfo::lastUpdateTime() const
{ return m_lastUpdateTime;}

inline void UserInfo::setLastUpdateTime(const QString &lastUpdateTime)
{ m_lastUpdateTime = lastUpdateTime;}
#endif // USERINFO_H
