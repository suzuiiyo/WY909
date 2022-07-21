#ifndef STATIONINFO_H
#define STATIONINFO_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class StationInfo
{
public:
    typedef QSharedPointer<StationInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    StationInfo();
    ~StationInfo();
public:
    int GUID() const;
    QString stationName() const;
    QString stationDesc() const;
    QString scheduleName() const;
    QString longitude() const;
    QString latitude() const;
public:
    void setGUID(int guid);
    void setStationName(const QString &stationName);
    void setStationDesc(const QString &stationDesc);
    void setScheduleName(const QString &scheduleName);
    void setLongitude(const QString &longitude);
    void setLatitude(const QString &latitude);
private:
    int m_GUID;
    QString m_stationName;
    QString m_stationDesc;
    QString m_scheduleName;
    QString m_longitude;
    QString m_latitude;
private:
    friend class DBStationInfoDAO;
};

inline int StationInfo::GUID() const
{ return m_GUID;}

inline void StationInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString StationInfo::stationName() const
{ return m_stationName;}

inline void StationInfo::setStationName(const QString &stationName)
{ m_stationName = stationName;}

inline QString StationInfo::stationDesc() const
{ return m_stationDesc;}

inline void StationInfo::setStationDesc(const QString &stationDesc)
{ m_stationDesc = stationDesc;}

inline QString StationInfo::scheduleName() const
{ return m_scheduleName;}

inline void StationInfo::setScheduleName(const QString &scheduleName)
{ m_scheduleName = scheduleName;}

inline QString StationInfo::longitude() const
{ return m_longitude;}

inline void StationInfo::setLongitude(const QString &longitude)
{ m_longitude = longitude;}

inline QString StationInfo::latitude() const
{ return m_latitude;}

inline void StationInfo::setLatitude(const QString &latitude)
{ m_latitude = latitude;}
#endif // STATIONINFO_H
