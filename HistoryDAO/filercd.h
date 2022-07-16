#ifndef FILERCD_H
#define FILERCD_H
#include <QString>
#include <QHash>
#include <QSharedPointer>
class FileRcd
{
public:
    typedef QList<FileRcd*> List;
    typedef QHash<QString, FileRcd*> Hash;
public:
    FileRcd();
    FileRcd(const QString &name, qint64 time);
public:
    QString name() const;
    qint64 time() const;
    QString path() const;
    int nPullCount() const;
    int pullingState() const;
    int tranisentTaskState() const;
public:
    void setName(const QString &name);
    void setTime(qint64 time);
    void setPath(const QString &path);
    void setNPullCount(int nPullCount);
    void setPullingState(int pullingState);
    void setTranisentTaskState(int tranisentTaskState);
public:
    const QStringList & lstFile() const;
    void addFile(const QString &strFile);
    void clearFile();
private:
    QString m_name;
    qint64 m_time;
    QString m_path;
    int m_nPullCount;
    int m_pullingState;
    int m_tranisentTaskState;
    QStringList m_lstFile;
private:
    friend class RcdDevice;
};

inline QString FileRcd::name() const
{ return m_name;}

inline void FileRcd::setName(const QString &name)
{ m_name = name;}

inline qint64 FileRcd::time() const
{ return m_time;}

inline void FileRcd::setTime(qint64 time)
{ m_time = time;}

inline QString FileRcd::path() const
{ return m_path;}

inline void FileRcd::setPath(const QString &path)
{ m_path = path;}

inline int FileRcd::nPullCount() const
{ return m_nPullCount;}

inline void FileRcd::setNPullCount(int nPullCount)
{ m_nPullCount = nPullCount;}

inline int FileRcd::pullingState() const
{ return m_pullingState;}

inline void FileRcd::setPullingState(int pullingState)
{ m_pullingState = pullingState;}

inline int FileRcd::tranisentTaskState() const
{ return m_tranisentTaskState;}

inline void FileRcd::setTranisentTaskState(int tranisentTaskState)
{ m_tranisentTaskState = tranisentTaskState;}

inline const QStringList & FileRcd::lstFile() const
{ return m_lstFile;}

inline void FileRcd::clearFile()
{ m_lstFile.clear();}
#endif // FILERCD_H
