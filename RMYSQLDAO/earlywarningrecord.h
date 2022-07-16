#ifndef EARLYWARNINGRECORD_H
#define EARLYWARNINGRECORD_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class EarlyWarningRecord
{
public:
    typedef QSharedPointer<EarlyWarningRecord> Ptr;
    typedef QList<Ptr> List;
public:
    EarlyWarningRecord();
    ~EarlyWarningRecord();
public:
    int     GUID() const;
    QString dataRef() const;
    int     warningType() const;
    int     ewType() const;
    float   dataValue() const;
    QString recordTime() const;
    float   maxData() const;
    float   minData() const;
    float   mutationValue() const;
    int     ackTip() const;
public:
    void setGUID(int guid);
    void setDataRef(const QString &dataRef);
    void setWarningType(int warningType);
    void setEWType(int ewType);
    void setDataValue(float dataValue);
    void setRecordTime(const QString &recordTime);
    void setMaxData(float maxData);
    void setMinData(float minData);
    void setMutationValue(float mutationValue);
    void setAckTip(int ackTip);
private:
    int         m_GUID;
    QString     m_dataRef;
    int         m_warningType;
    int         m_ewType;
    float       m_dataValue;
    QString     m_recordTime;
    float       m_maxData;
    float       m_minData;
    float       m_mutationValue;
    int         m_ackTip;
private:
    friend class DBEarlyWarningRecordDAO;
};

inline int EarlyWarningRecord::GUID() const
{ return m_GUID;}

inline void EarlyWarningRecord::setGUID(int guid)
{ m_GUID = guid;}

inline QString EarlyWarningRecord::dataRef() const
{ return m_dataRef;}

inline void EarlyWarningRecord::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline int EarlyWarningRecord::warningType() const
{ return m_warningType;}

inline void EarlyWarningRecord::setWarningType(int warningType)
{ m_warningType = warningType;}

inline int EarlyWarningRecord::ewType() const
{ return m_ewType;}

inline void EarlyWarningRecord::setEWType(int ewType)
{ m_ewType = ewType;}

inline float EarlyWarningRecord::dataValue() const
{ return m_dataValue;}

inline void EarlyWarningRecord::setDataValue(float dataValue)
{ m_dataValue = dataValue;}

inline QString EarlyWarningRecord::recordTime() const
{ return m_recordTime;}

inline void EarlyWarningRecord::setRecordTime(const QString &recordTime)
{ m_recordTime = recordTime;}

inline float EarlyWarningRecord::maxData() const
{ return m_maxData;}

inline void EarlyWarningRecord::setMaxData(float maxData)
{ m_maxData = maxData;}

inline float EarlyWarningRecord::minData() const
{ return m_minData;}

inline void EarlyWarningRecord::setMinData(float minData)
{ m_minData = minData;}

inline float EarlyWarningRecord::mutationValue() const
{ return m_mutationValue;}

inline void EarlyWarningRecord::setMutationValue(float mutationValue)
{ m_mutationValue = mutationValue;}

inline int EarlyWarningRecord::ackTip() const
{ return m_ackTip;}

inline void EarlyWarningRecord::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // EARLYWARNINGRECORD_H
