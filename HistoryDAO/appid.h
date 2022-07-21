#ifndef APPID_H
#define APPID_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class AppId
{
public:
    typedef QSharedPointer<AppId> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    AppId();
    ~AppId();
public:
    int GUID() const;
    QString appId() const;
    QString iedName() const;
public:
    void setGUID(int guid);
    void setAppId(const QString &appId);
    void setIedName(const QString &iedName);
private:
    int m_GUID;
    QString m_appId;
    QString m_iedName;
private:
    friend class DBAppIdDAO;
};

inline int AppId::GUID() const
{ return m_GUID;}

inline void AppId::setGUID(int guid)
{ m_GUID = guid;}

inline QString AppId::appId() const
{ return m_appId;}

inline void AppId::setAppId(const QString &appId)
{ m_appId = appId;}

inline QString AppId::iedName() const
{ return m_iedName;}

inline void AppId::setIedName(const QString &iedName)
{ m_iedName = iedName;}
#endif // APPID_H
