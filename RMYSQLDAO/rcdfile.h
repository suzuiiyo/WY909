#ifndef RCDFILE_H
#define RCDFILE_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class RcdFile
{
public:
    typedef QSharedPointer<RcdFile> Ptr;
    typedef QList<Ptr> List;
public:
    RcdFile();
    ~RcdFile();
public:
    int GUID() const;
    QString filePath() const;
    QString fileName() const;
    QString iedName() const;
    QString ip() const;
    QString endStr() const;
    QString size() const;
    QString fileTime() const;
    QString dbRecordTime() const;
    int recvState() const;
public:
    void setGUID(int guid);
    void setFilePath(const QString &filePath);
    void setFileName(const QString &fileName);
    void setIedName(const QString &iedName);
    void setIp(const QString &ip);
    void setEndStr(const QString &endStr);
    void setSize(const QString &size);
    void setFileTime(const QString &fileTime);
    void setDBRecordTime(const QString &dbRecordTime);
    void setRecvState(int recvState);
private:
    int m_GUID;
    QString m_filePath;
    QString m_fileName;
    QString m_iedName;
    QString m_ip;
    QString m_endStr;
    QString m_size;
    QString m_fileTime;
    QString m_dbRecordTime;
    int m_recvState;
private:
    friend class DBRcdFileDAO;
};

inline int RcdFile::GUID() const
{ return m_GUID;}

inline void RcdFile::setGUID(int guid)
{ m_GUID = guid;}

inline QString RcdFile::filePath() const
{ return m_filePath;}

inline void RcdFile::setFilePath(const QString &filePath)
{ m_filePath = filePath;}

inline QString RcdFile::fileName() const
{ return m_fileName;}

inline void RcdFile::setFileName(const QString &fileName)
{ m_fileName = fileName;}

inline QString RcdFile::iedName() const
{ return m_iedName;}

inline void RcdFile::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString RcdFile::ip() const
{ return m_ip;}

inline void RcdFile::setIp(const QString &ip)
{ m_ip = ip;}

inline QString RcdFile::endStr() const
{ return m_endStr;}

inline void RcdFile::setEndStr(const QString &endStr)
{ m_endStr = endStr;}

inline QString RcdFile::size() const
{ return m_size;}

inline void RcdFile::setSize(const QString &size)
{ m_size = size;}

inline QString RcdFile::fileTime() const
{ return m_fileTime;}

inline void RcdFile::setFileTime(const QString &fileTime)
{ m_fileTime = fileTime;}

inline QString RcdFile::dbRecordTime() const
{ return m_dbRecordTime;}

inline void RcdFile::setDBRecordTime(const QString &dbRecordTime)
{ m_dbRecordTime = dbRecordTime;}

inline int RcdFile::recvState() const
{ return m_recvState;}

inline void RcdFile::setRecvState(int recvState)
{ m_recvState = recvState;}
#endif // RCDFILE_H
