#ifndef CRCFILETASKRECORD_H
#define CRCFILETASKRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class CRCFileTaskRecord
{
public:
    typedef QSharedPointer<CRCFileTaskRecord> Ptr;
    typedef QList<Ptr> List;
public:
    CRCFileTaskRecord();
    ~CRCFileTaskRecord();
public:
    int     GUID() const;
    QString iedName() const;
    QString recordTime() const;
    int     taskType() const;
    QString csCRC() const;
    QString fileCRC() const;
    QString virCRC() const;
    int     recordType() const;
    int     ackTip() const;
public:
    void    setGUID(int guid);
    void    setIedName(const QString &iedName);
    void    setRecordTime(const QString &recordTime);
    void    setTaskType(int taskType);
    void    setCSCRC(const QString &csCRC);
    void    setFileCRC(const QString &fileCRC);
    void    setVirCRC(const QString &virCRC);
    void    setRecordType(int recordType);
    void    setAckTip(int ackTip);
private:
    int         m_GUID;
    QString     m_iedName;
    QString     m_recordTime;
    int         m_taskType;
    QString     m_csCRC;
    QString     m_fileCRC;
    QString     m_virCRC;
    int         m_recordType;
    int         m_ackTip;
private:
    friend class DBCRCFileTaskRecordDAO;
};

inline int CRCFileTaskRecord::GUID() const
{ return m_GUID;}

inline void CRCFileTaskRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString CRCFileTaskRecord::iedName() const
{ return m_iedName;}

inline void CRCFileTaskRecord::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString CRCFileTaskRecord::recordTime() const
{ return m_recordTime;}

inline int CRCFileTaskRecord::taskType() const
{ return m_taskType;}

inline void CRCFileTaskRecord::setTaskType(int taskType)
{ m_taskType = taskType;}

inline QString CRCFileTaskRecord::csCRC() const
{ return m_csCRC;}

inline void CRCFileTaskRecord::setCSCRC(const QString &csCRC)
{ m_csCRC = csCRC;}

inline QString CRCFileTaskRecord::fileCRC() const
{ return m_fileCRC;}

inline void CRCFileTaskRecord::setFileCRC(const QString &fileCRC)
{ m_fileCRC = fileCRC;}

inline QString CRCFileTaskRecord::virCRC() const
{ return m_virCRC;}

inline void CRCFileTaskRecord::setVirCRC(const QString &virCRC)
{ m_virCRC = virCRC;}

inline int CRCFileTaskRecord::recordType() const
{ return m_recordType;}

inline void CRCFileTaskRecord::setRecordType(int recordType)
{ m_recordType = recordType;}

inline int CRCFileTaskRecord::ackTip() const
{ return m_ackTip;}

inline void CRCFileTaskRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // CRCFILETASKRECORD_H
