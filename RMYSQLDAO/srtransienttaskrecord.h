#ifndef SRTRANSIENTTASKRECORD_H
#define SRTRANSIENTTASKRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class SRTransientTaskRecord
{
public:
    typedef QSharedPointer<SRTransientTaskRecord> Ptr;
    typedef QList<Ptr> List;
public:
    SRTransientTaskRecord();
    ~SRTransientTaskRecord();
public:
    int         GUID() const;
    QString     iedAFileName() const;
    QString     iedBFileName() const;
    int         tmDataType() const;
    float       tmDataValue() const;
    float       tmThreshold() const;
public:
    void setGUID(int guid);
    void setIedAFileName(const QString &iedAFileName);
    void setIedBFileName(const QString &iedBFileName);
    void setTMDataType(int tmDataType);
    void setTMDataValue(float tmDataValue);
    void setTMThreshold(float tmThreshold);
private:
    int         m_GUID;
    QString     m_iedAFileName;
    QString     m_iedBFileName;
    int         m_tmDataType;
    float       m_tmDataValue;
    float       m_tmThreshold;
private:
    friend class DBSRTransientTaskRecordDAO;
};

inline int SRTransientTaskRecord::GUID() const
{ return m_GUID;}

inline void SRTransientTaskRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString SRTransientTaskRecord::iedAFileName() const
{ return m_iedAFileName;}

inline void SRTransientTaskRecord::setIedAFileName(const QString &iedAFileName)
{ m_iedAFileName = iedAFileName;}

inline QString SRTransientTaskRecord::iedBFileName() const
{ return m_iedBFileName;}

inline void SRTransientTaskRecord::setIedBFileName(const QString &iedBFileName)
{ m_iedBFileName = iedBFileName;}

inline int SRTransientTaskRecord::tmDataType() const
{ return m_tmDataType;}

inline void SRTransientTaskRecord::setTMDataType(int tmDataType)
{ m_tmDataType = tmDataType;}

inline float SRTransientTaskRecord::tmDataValue() const
{ return m_tmDataValue;}

inline void SRTransientTaskRecord::setTMDataValue(float tmDataValue)
{ m_tmDataValue = tmDataValue;}

inline float SRTransientTaskRecord::tmThreshold() const
{ return m_tmThreshold;}

inline void SRTransientTaskRecord::setTMThreshold(float tmThreshold)
{ m_tmThreshold = tmThreshold;}
#endif // SRTRANSIENTTASKRECORD_H
