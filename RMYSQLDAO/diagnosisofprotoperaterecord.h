#ifndef DIAGNOSISOFPROTOPERATERECORD_H
#define DIAGNOSISOFPROTOPERATERECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class DiagnosisOfProtOperateRecord
{
public:
    typedef QSharedPointer<DiagnosisOfProtOperateRecord> Ptr;
    typedef QList<Ptr> List;
public:
    DiagnosisOfProtOperateRecord();
    ~DiagnosisOfProtOperateRecord();
public:
    int GUID() const;
    QString iedName() const;
    QString opType() const;
    QString conclusion() const;
    QString recordTime() const;
    QString criterion() const;
    QString process() const;
    QString iedNameComp() const;
    QString isConsistent() const;
    QString relationIed() const;
    QString nonAnticipatoryOp() const;
    QString anticipatoryOp() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setOpType(const QString &opType);
    void setConclusion(const QString &conclusion);
    void setRecordTime(const QString &recordTime);
    void setCriterion(const QString &criterion);
    void setProcess(const QString &process);
    void setIedNameComp(const QString &iedNameComp);
    void setIsConsistent(const QString &isConsistent);
    void setRelationIed(const QString &relationIed);
    void setNonAnticipatoryOp(const QString &nonAnticipatoryOp);
    void setAnticipatoryOp(const QString &anticipatoryOp);
    void setAckTip(int ackTip);
private:
    int     m_GUID;
    QString m_iedName;
    QString m_opType;
    QString m_conclusion;
    QString m_recordTime;
    QString m_criterion;
    QString m_process;
    QString m_iedNameComp;
    QString m_isConsistent;
    QString m_relationIed;
    QString m_nonAnticipatoryOp;
    QString m_anticipatoryOp;
    int     m_ackTip;
private:
    friend class DBDiagnosisOfProtOperateRecordDAO;
};

inline int DiagnosisOfProtOperateRecord::GUID() const
{ return m_GUID;}

inline void DiagnosisOfProtOperateRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString DiagnosisOfProtOperateRecord::iedName() const
{ return m_iedName;}

inline void DiagnosisOfProtOperateRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString DiagnosisOfProtOperateRecord::opType() const
{ return m_opType;}

inline void DiagnosisOfProtOperateRecord::setOpType(const QString &opType)
{ m_opType = opType;}

inline QString DiagnosisOfProtOperateRecord::conclusion() const
{ return m_conclusion;}

inline void DiagnosisOfProtOperateRecord::setConclusion(const QString &conclusion)
{ m_conclusion = conclusion;}

inline QString DiagnosisOfProtOperateRecord::recordTime() const
{ return m_recordTime;}

inline void DiagnosisOfProtOperateRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}

inline QString DiagnosisOfProtOperateRecord::criterion() const
{ return m_criterion;}

inline void DiagnosisOfProtOperateRecord::setCriterion(const QString &criterion)
{ m_criterion = criterion;}

inline QString DiagnosisOfProtOperateRecord::process() const
{ return m_process;}

inline void DiagnosisOfProtOperateRecord::setProcess(const QString &process)
{ m_process = process;}

inline QString DiagnosisOfProtOperateRecord::iedNameComp() const
{ return m_iedNameComp;}

inline void DiagnosisOfProtOperateRecord::setIedNameComp(const QString &iedNameComp)
{ m_iedNameComp = iedNameComp;}

inline QString DiagnosisOfProtOperateRecord::isConsistent() const
{ return m_isConsistent;}

inline void DiagnosisOfProtOperateRecord::setIsConsistent(const QString &isConsistent)
{ m_isConsistent = isConsistent;}

inline QString DiagnosisOfProtOperateRecord::relationIed() const
{ return m_relationIed;}

inline void DiagnosisOfProtOperateRecord::setRelationIed(const QString &relationIed)
{ m_relationIed = relationIed;}

inline QString DiagnosisOfProtOperateRecord::nonAnticipatoryOp() const
{ return m_nonAnticipatoryOp;}

inline void DiagnosisOfProtOperateRecord::setNonAnticipatoryOp(const QString &nonAnticipatoryOp)
{ m_nonAnticipatoryOp = nonAnticipatoryOp;}

inline QString DiagnosisOfProtOperateRecord::anticipatoryOp() const
{ return m_anticipatoryOp;}

inline void DiagnosisOfProtOperateRecord::setAnticipatoryOp(const QString &anticipatoryOp)
{ m_anticipatoryOp = anticipatoryOp;}

inline int DiagnosisOfProtOperateRecord::ackTip() const
{ return m_ackTip;}

inline void DiagnosisOfProtOperateRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // DIAGNOSISOFPROTOPERATERECORD_H
