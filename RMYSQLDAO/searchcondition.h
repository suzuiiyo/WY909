#ifndef SEARCHCONDITION_H
#define SEARCHCONDITION_H
#include <QString>
#include <QSharedPointer>
#include <QList>
class SearchCondition
{
public:
    typedef QSharedPointer<SearchCondition> Ptr;
    typedef QList<Ptr> List;
public:
    SearchCondition();
    ~SearchCondition();
public:
    int     startCount() const;
    int     recordCount() const;
    int     dataType() const;
    QString stationName() const;
    QString voltClass() const;
    QString bayName() const;
    QString iedName() const;
    QString startTime() const;
    QString endTime() const;
    int     ackTip() const;
public:
    void setStartCount(int startCount);
    void setDataType(int &dataType);
    void setRecordCount(int recordCount);
    void setStationName(const QString &stationName);
    void setVoltClass(const QString &voltClass);
    void setBayName(const QString &bayName);
    void setIedName(const QString &iedName);
    void setStartTime(const QString &startTime);
    void setEndTime(const QString &endTime);
    void setAckTip(int ackTip);
private:
    int     m_startCount;
    int     m_recordCount;
    int     m_dataType;
    QString m_stationName;
    QString m_voltClass;
    QString m_bayName;
    QString m_iedName;
    QString m_startTime;
    QString m_endTime;
    int     m_ackTip;
private:
    friend class DBActionEventDAO;
    friend class DBAlarmEventDAO;
};

inline int SearchCondition::startCount() const
{ return m_startCount;}

inline void SearchCondition::setStartCount(int startCount)
{ m_startCount = startCount;}

inline int SearchCondition::recordCount() const
{ return m_recordCount;}

inline void SearchCondition::setRecordCount(int recordCount)
{ m_recordCount = recordCount;}

inline int SearchCondition::dataType() const
{ return m_dataType;}

inline void SearchCondition::setDataType(int &dataType)
{ m_dataType = dataType;}

inline QString SearchCondition::stationName() const
{ return m_stationName;}

inline void SearchCondition::setStationName(const QString &stationName)
{ m_stationName = stationName;}

inline QString SearchCondition::voltClass() const
{ return m_voltClass;}

inline void SearchCondition::setVoltClass(const QString &voltClass)
{ m_voltClass = voltClass;}

inline QString SearchCondition::bayName() const
{ return m_bayName;}

inline void SearchCondition::setBayName(const QString &bayName)
{ m_bayName = bayName;}

inline QString SearchCondition::iedName() const
{ return m_iedName;}

inline void SearchCondition::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString SearchCondition::startTime() const
{ return m_startTime;}

inline void SearchCondition::setStartTime(const QString &startTime)
{ m_startTime = startTime;}

inline QString SearchCondition::endTime() const
{ return m_endTime;}

inline void SearchCondition::setEndTime(const QString &endTime)
{ m_endTime = endTime;}

inline int SearchCondition::ackTip() const
{ return m_ackTip;}

inline void SearchCondition::setAckTip(int ackTip)
{ m_ackTip = ackTip;}
#endif // SEARCHCONDITION_H
