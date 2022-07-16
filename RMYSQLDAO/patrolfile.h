#ifndef PATROLFILE_H
#define PATROLFILE_H
#include <QSharedPointer>
#include <QString>
#include <QList>
class PatrolFile
{
public:
    typedef QSharedPointer<PatrolFile> Ptr;
    typedef QList<Ptr> List;
public:
    PatrolFile();
    ~PatrolFile();
public:
    QString fileName() const;
    QString taskFinishTime() const;
    int     accessDevNum() const;
    int     taskDevNum() const;
    int     abnormalDevNum() const;
    int     seriousDevNum() const;
public:
    void setFileName(const QString &fileName);
    void setTaskFinishTime(const QString &taskFinishTime);
    void setAccessDevNum(int accessDevNum);
    void setTaskDevNum(int taskDevNum);
    void setAbnormalDevNum(int abnormalDevNum);
    void setSeriousDevNum(int seriousDevNum);
private:
    QString     m_fileName;
    QString     m_taskFinishTime;
    int         m_accessDevNum;
    int         m_taskDevNum;
    int         m_abnormalDevNum;
    int         m_seriousDevNum;
private:
    friend class DBPatrolFileDAO;
};

inline QString PatrolFile::fileName() const
{ return m_fileName;}

inline void PatrolFile::setFileName(const QString &fileName)
{ m_fileName = fileName;}

inline QString PatrolFile::taskFinishTime() const
{ return m_taskFinishTime;}

inline void PatrolFile::setTaskFinishTime(const QString &taskFinishTime)
{ m_taskFinishTime = taskFinishTime;}

inline int PatrolFile::accessDevNum() const
{ return m_accessDevNum;}

inline void PatrolFile::setAccessDevNum(int accessDevNum)
{ m_accessDevNum = accessDevNum;}

inline int PatrolFile::taskDevNum() const
{ return m_taskDevNum;}

inline void PatrolFile::setTaskDevNum(int taskDevNum)
{ m_taskDevNum = taskDevNum;}

inline int PatrolFile::abnormalDevNum() const
{ return m_abnormalDevNum;}

inline void PatrolFile::setAbnormalDevNum(int abnormalDevNum)
{ m_abnormalDevNum = abnormalDevNum;}

inline int PatrolFile::seriousDevNum() const
{ return m_seriousDevNum;}

inline void PatrolFile::setSeriousDevNum(int seriousDevNum)
{ m_seriousDevNum = seriousDevNum;}
#endif // PATROLFILE_H
