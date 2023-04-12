#ifndef GOOSEREALDATA_H
#define GOOSEREALDATA_H
#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QHash>
class GooseRealData
{
public:
    typedef QSharedPointer<GooseRealData> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    GooseRealData();
    ~GooseRealData();
public:
    int GUID() const;
    quint32 appId() const;
    QString dataRef() const;
    QString iedName() const;
    int dataType() const;
    QString dataValue() const;
    QString updateTime() const;
public:
    void setGUID(int guid);
    void setAppId(quint32 appId);
    void setDataRef(const QString &dataRef);
    void setIedName(const QString &iedName);
    void setDataType(int dataType);
    void setDataValue(const QString &dataValue);
    void setUpDateTime(const QString &updateTime);
private:
    int m_GUID;
    quint32 m_appId;
    QString m_dataRef;
    QString m_iedName;
    int m_dataType;
    QString m_dataValue;
    QString m_updateTime;
private:
    friend class DBGooseRealDataDAO;
};
inline int GooseRealData::GUID() const
{ return m_GUID;}

inline void GooseRealData::setGUID(int guid)
{ m_GUID = guid;}

inline quint32 GooseRealData::appId() const
{ return m_appId;}

inline void GooseRealData::setAppId(quint32 appId)
{ m_appId = appId;}

inline QString GooseRealData::dataRef() const
{ return m_dataRef;}

inline void GooseRealData::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString GooseRealData::iedName() const
{ return m_iedName;}

inline void GooseRealData::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline int GooseRealData::dataType() const
{ return m_dataType;}

inline void GooseRealData::setDataType(int dataType)
{ m_dataType = dataType;}

inline QString GooseRealData::dataValue() const
{ return m_dataValue;}

inline void GooseRealData::setDataValue(const QString &dataValue)
{ m_dataValue = dataValue;}

inline QString GooseRealData::updateTime() const
{ return m_updateTime;}

inline void GooseRealData::setUpDateTime(const QString &updateTime)
{ m_updateTime = updateTime;}
#endif // GOOSEREALDATA_H
