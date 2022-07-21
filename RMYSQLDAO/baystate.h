#ifndef BAYSTATE_H
#define BAYSTATE_H
#include <QString>
#include <QSharedPointer>
#include <QList>
class BayState
{
public:
    typedef QSharedPointer<BayState> Ptr;
    typedef QList<Ptr> List;
public:
    BayState();
    ~BayState();
public:
    QString bayName() const;
    int bayState() const;
    QString setType() const;
    QString updateTime() const;
    int devCorrespondingState() const;
public:
    void setBayName(const QString &bayName);
    void setBayState(int bayState);
    void setSetType(const QString &setType);
    void setUpdateTime(const QString &updateTime);
    void setDevCorrespondingState(int devCorrespondingState);
private:
    QString m_bayName;
    int m_bayState;
    QString m_setType;
    QString m_updateTime;
    int m_devCorrespondingState;
private:
    friend class DBBayStateDAO;
};

inline QString BayState::bayName() const
{ return m_bayName;}

inline void BayState::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline int BayState::bayState() const
{ return m_bayState;}

inline void BayState::setBayState(int bayState)
{ m_bayState = bayState;}

inline QString BayState::setType() const
{ return m_setType;}

inline void BayState::setSetType(const QString &setType)
{ m_setType = setType;}

inline QString BayState::updateTime() const
{ return m_updateTime;}

inline void BayState::setUpdateTime(const QString &updateTime)
{ m_updateTime = updateTime;}

inline int BayState::devCorrespondingState() const
{ return m_devCorrespondingState;}

inline void BayState::setDevCorrespondingState(int devCorrespondingState)
{ m_devCorrespondingState = devCorrespondingState;}
#endif // BAYSTATE_H
