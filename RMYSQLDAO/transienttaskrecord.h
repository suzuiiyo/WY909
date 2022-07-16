#ifndef TRANSIENTTASKRECORD_H
#define TRANSIENTTASKRECORD_H
#include <QSharedPointer>
#include <QString>
#include <QList>
#include <QHash>
class TransientTaskRecord
{
public:
    typedef QSharedPointer<TransientTaskRecord> Ptr;
    typedef QList<Ptr> List;
public:
    TransientTaskRecord();
    ~TransientTaskRecord();
public:
    int     GUID() const;
    QString iedName1() const;
    QString iedCateGory1() const;
    QString waveFile1() const;
    QString iedName2() const;
    QString iedCateGory2() const;
    QString waveFile2() const;
    int     taskState() const;
    QString taskRequestTime() const;
    QString taskRespondTime() const;
    QString taskResult() const;
    QString taskDataFileName() const;
public:
    void setGUID(int guid);
    void setIedName1(const QString &iedName1);
    void setIedCateGory1(const QString &iedCateGory1);
    void setWaveFile1(const QString &waveFile1);
    void setIedName2(const QString &srIedName);
    void setIedCateGory2(const QString &iedCateGory2);
    void setWaveFile2(const QString &waveFile2);
    void setTaskState(int taskState);
    void setTaskRequestTime(const QString &taskRequestTime);
    void setTaskRespondTime(const QString &taskRespondTime);
    void setTaskResult(const QString &taskResult);
    void setTaskDataFileName(const QString &taskDataFileName);
private:
    int     m_GUID;
    QString m_iedName1;
    QString m_iedCateGory1;
    QString m_waveFile1;
    QString m_iedName2;
    QString m_iedCateGory2;
    QString m_waveFile2;
    int     m_taskState;
    QString m_taskRequestTime;
    QString m_taskRespondTime;
    QString m_taskResult;
    QString m_taskDataFileName;
private:
    friend class DBTransientTaskRecordDAO;
};

inline int TransientTaskRecord::GUID() const
{ return m_GUID;}

inline void TransientTaskRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString TransientTaskRecord::iedName1() const
{ return m_iedName1;}

inline void TransientTaskRecord::setIedName1(const QString &iedName1)
{ m_iedName1 = iedName1;}

inline QString TransientTaskRecord::iedCateGory1() const
{ return m_iedCateGory1;}

inline void TransientTaskRecord::setIedCateGory1(const QString &iedCateGory1)
{ m_iedCateGory1 = iedCateGory1;}

inline QString TransientTaskRecord::waveFile1() const
{ return m_waveFile1;}

inline void TransientTaskRecord::setWaveFile1(const QString &waveFile1)
{ m_waveFile1 = waveFile1;}

inline QString TransientTaskRecord::iedName2() const
{ return m_iedName2;}

inline void TransientTaskRecord::setIedName2(const QString &iedName2)
{ m_iedName2 = iedName2;}

inline QString TransientTaskRecord::iedCateGory2() const
{ return m_iedCateGory2;}

inline void TransientTaskRecord::setIedCateGory2(const QString &iedCateGory2)
{ m_iedCateGory2 = iedCateGory2;}

inline QString TransientTaskRecord::waveFile2() const
{ return m_waveFile2;}

inline void TransientTaskRecord::setWaveFile2(const QString &waveFile2)
{ m_waveFile2 = waveFile2;}

inline int TransientTaskRecord::taskState() const
{ return m_taskState;}

inline void TransientTaskRecord::setTaskState(int taskState)
{ m_taskState = taskState;}

inline QString TransientTaskRecord::taskRequestTime() const
{ return m_taskRequestTime;}

inline void TransientTaskRecord::setTaskRequestTime(const QString &taskRequestTime)
{ m_taskRequestTime = taskRequestTime;}

inline QString TransientTaskRecord::taskRespondTime() const
{ return m_taskRespondTime;}

inline void TransientTaskRecord::setTaskRespondTime(const QString &taskRespondTime)
{ m_taskRespondTime = taskRespondTime;}

inline QString TransientTaskRecord::taskResult() const
{ return m_taskResult;}

inline void TransientTaskRecord::setTaskResult(const QString &taskResult)
{ m_taskResult = taskResult;}

inline QString TransientTaskRecord::taskDataFileName() const
{ return m_taskDataFileName;}

inline void TransientTaskRecord::setTaskDataFileName(const QString &taskDataFileName)
{ m_taskDataFileName = taskDataFileName;}
#endif // TRANSIENTTASKRECORD_H
