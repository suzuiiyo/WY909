#ifndef TRANSIENTTASKFILE_H
#define TRANSIENTTASKFILE_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class TransientTaskFile
{
public:
    typedef QSharedPointer<TransientTaskFile> Ptr;
    typedef QList<Ptr> List;
public:
    TransientTaskFile(){}
    ~TransientTaskFile(){}
public:
    QString fileName() const;
    QString recordTime() const;
public:
    void setFileName(const QString &fileName);
    void setRecordTime(const QString &recordTime);
private:
    QString m_fileName;
    QString m_recordTime;
private:
    friend class DBTransientTaskFileDAO;
};

inline QString TransientTaskFile::fileName() const
{ return m_fileName;}

inline void TransientTaskFile::setFileName(const QString &fileName)
{ m_fileName = fileName;}

inline QString TransientTaskFile::recordTime() const
{ return m_recordTime;}

inline void TransientTaskFile::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // TRANSIENTTASKFILE_H
