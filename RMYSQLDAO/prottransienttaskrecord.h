#ifndef PROTTRANSIENTTASKRECORD_H
#define PROTTRANSIENTTASKRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class ProtTransientTaskRecord
{
public:
    typedef QSharedPointer<ProtTransientTaskRecord> Ptr;
    typedef QList<Ptr> List;
public:
    ProtTransientTaskRecord();
    ~ProtTransientTaskRecord();
public:
    int GUID() const;
    QString startTime() const;
    QString startResetTime() const;
    int faultNum() const;
    float faultValue() const;
public:
    void setGUID(int guid);
    void setStartTime(const QString &startTime);
    void setStartResetTime(const QString &startResetTime);
    void setFaultNum(int faultNum);
    void setFaultValue(float faultValue);
private:
    int         m_GUID;
    QString     m_startTime;
    QString     m_startResetTime;
    int         m_faultNum;
    float       m_faultValue;
private:
    friend class DBProtTransientTaskRecordDAO;
};

inline int ProtTransientTaskRecord::GUID() const
{ return m_GUID;}

inline void ProtTransientTaskRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString ProtTransientTaskRecord::startTime() const
{ return m_startTime;}

inline void ProtTransientTaskRecord::setStartTime(const QString &startTime)
{ m_startTime = startTime;}

inline QString ProtTransientTaskRecord::startResetTime() const
{ return m_startResetTime;}

inline void ProtTransientTaskRecord::setStartResetTime(const QString &startResetTime)
{ m_startResetTime = startResetTime;}

inline int ProtTransientTaskRecord::faultNum() const
{ return m_faultNum;}

inline void ProtTransientTaskRecord::setFaultNum(int faultNum)
{ m_faultNum = faultNum;}

inline float ProtTransientTaskRecord::faultValue() const
{ return m_faultValue;}

inline void ProtTransientTaskRecord::setFaultValue(float faultValue)
{ m_faultValue = faultValue;}
#endif // PROTTRANSIENTTASKRECORD_H
