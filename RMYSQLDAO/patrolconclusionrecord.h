#ifndef PATROLCONCLUSIONRECORD_H
#define PATROLCONCLUSIONRECORD_H
#include <QSharedPointer>
#include <QString>
#include <QList>
class PatrolConclusionRecord
{
public:
    typedef QSharedPointer<PatrolConclusionRecord> Ptr;
    typedef QList<Ptr> List;
public:
    PatrolConclusionRecord();
    ~PatrolConclusionRecord();
public:
    int     GUID() const;
    QString iedName() const;
    QString conclusion() const;
    QString taskType() const;
    QString taskTime() const;
    QString belongFileName() const;
    int     falseReason() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setConclusion(const QString &conclusion);
    void setTaskType(const QString &taskType);
    void setTaskTime(const QString &taskTime);
    void setBelongFileName(const QString &fileName);
    void setFalseReason(int falseReason);
    void setAckTip(int ackTip);
private:
    int     m_GUID;
    QString m_iedName;
    QString m_conclusion;
    QString m_taskType;
    QString m_taskTime;
    QString m_belongFileName;
    int     m_falseReason;
    int     m_ackTip;
private:
    friend class DBPatrolConclusionRecordDAO;
};

inline int PatrolConclusionRecord::GUID() const
{ return m_GUID;}

inline void PatrolConclusionRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString PatrolConclusionRecord::iedName() const
{ return m_iedName;}

inline void PatrolConclusionRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString PatrolConclusionRecord::conclusion() const
{ return m_conclusion;}

inline void PatrolConclusionRecord::setConclusion(const QString &conclusion)
{ m_conclusion = conclusion;}

inline QString PatrolConclusionRecord::taskType() const
{ return m_taskType;}

inline void PatrolConclusionRecord::setTaskType(const QString &taskType)
{ m_taskType = taskType;}

inline QString PatrolConclusionRecord::taskTime() const
{ return m_taskTime;}

inline void PatrolConclusionRecord::setTaskTime(const QString &taskTime)
{ m_taskTime = taskTime;}

inline QString PatrolConclusionRecord::belongFileName() const
{ return m_belongFileName;}

inline void PatrolConclusionRecord::setBelongFileName(const QString &belongFileName)
{ m_belongFileName = belongFileName;}

inline int PatrolConclusionRecord::falseReason() const
{ return m_falseReason;}

inline void PatrolConclusionRecord::setFalseReason(int falseReason)
{ m_falseReason = falseReason;}

inline int PatrolConclusionRecord::ackTip() const
{ return m_ackTip;}

inline void PatrolConclusionRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // PATROLCONCLUSIONRECORD_H
