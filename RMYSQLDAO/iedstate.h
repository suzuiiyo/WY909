#ifndef IEDSTATE_H
#define IEDSTATE_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class IedState
{
public:
    typedef QSharedPointer<IedState> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    IedState();
    ~IedState();
public:
    QString iedName() const;
    QString bayName() const;
    int shouldIedState() const;
    int iedState() const;
    //int devCorrespondingState() const;
    QString updateTime() const;
    QString setType() const;
public:
    void setIedName(const QString &iedName);
    void setBayName(const QString &bayName);
    void setShouldIedState(int shouldIedState);
    void setIedState(int iedState);
    //void setDevCorrespondingState(int devCorrespondingState);
    void setUpdateTime(const QString &updateTime);
    void setSetType(const QString &setType);
private:
    QString m_iedName;
    QString m_bayName;
    int m_shouldIedState;
    int m_iedState;
    QString m_updateTime;
    QString m_setType;
private:
    friend class DBIedRealStateDAO;
};

inline QString IedState::iedName() const
{ return m_iedName;}

inline void IedState::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString IedState::bayName() const
{ return m_bayName;}

inline void IedState::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline int IedState::shouldIedState() const
{ return m_shouldIedState;}

inline void IedState::setShouldIedState(int shouldIedState)
{ m_shouldIedState = shouldIedState;}

inline int IedState::iedState() const
{ return m_iedState;}

inline void IedState::setIedState(int iedState)
{ m_iedState = iedState;}

//inline int IedState::devCorrespondingState() const
//{ return m_devCorrespondingState;}

//inline void IedState::setDevCorrespondingState(int devCorrespondingState)
//{ m_devCorrespondingState = devCorrespondingState;}

inline QString IedState::updateTime() const
{ return m_updateTime;}

inline void IedState::setUpdateTime(const QString &updateTime)
{ m_updateTime = updateTime;}

inline QString IedState::setType() const
{ return m_setType;}

inline void IedState::setSetType(const QString &setType)
{ m_setType = setType;}
#endif // IEDSTATE_H
