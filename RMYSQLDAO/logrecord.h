#ifndef LOGRECORD_H
#define LOGRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class LogRecord
{
public:
    typedef QSharedPointer<LogRecord> Ptr;
    typedef QList<Ptr> List;
public:
    enum
    {
        Unknown,
        Running,
        Operation,
        Maintain
    };
public:
    LogRecord();
    ~LogRecord();
public:
    int     logType() const;
    int     GUID() const;
    QString fileName() const;
    QString recordTime() const;
public:
    void    setLogType(int logType);
    void    setGUID(int guid);
    void    setFileName(const QString &fileName);
    void    setRecordTime(const QString &recordTime);
private:
    int     m_logType;
    int     m_GUID;
    QString m_fileName;
    QString m_recordTime;
private:
    friend class DBLogRecordDAO;
};

inline int LogRecord::logType() const
{ return m_logType;}

inline void LogRecord::setLogType(int logType)
{ m_logType = logType;}

inline int LogRecord::GUID() const
{ return m_GUID;}

inline void LogRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString LogRecord::fileName() const
{ return m_fileName;}

inline void LogRecord::setFileName(const QString &fileName)
{ m_fileName = fileName;}

inline QString LogRecord::recordTime() const
{ return m_recordTime;}

inline void LogRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}
#endif // LOGRECORD_H
