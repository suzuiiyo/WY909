#ifndef REALDATA_H
#define REALDATA_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class RealData
{
public:
    typedef QSharedPointer<RealData> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    RealData();
    ~RealData();
public:
    int GUID() const;
    QString quality() const;
    QString updateTime() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
    QString business() const;
public:
    void setGUID(int guid);
    void setDataRef(const QString &dataRef);
    void setIedName(const QString &iedName);
    void setDataDesc(const QString &dataDesc);
    void setQuality(const QString &quality);
    void setUpdateTime(const QString &updateTime);
    void setBusiness(const QString &business);
public:
    const QList<int> & lstDataType() const;
    void addDataType(int dataType);
    void changeDataType(int type, int num);
    void clearDataType();
public:
    const QStringList & lstDataValue() const;
    void addDataValue(const QString &dataValue);
    void changeDataValue(const QString &dataValue, int num);
    void clearDataValue();
private:
    int m_GUID;
    QString m_dataRef;
    QString m_dataDesc;
    QString m_iedName;
    QString m_quality;
    QString m_updateTime;
    QString m_business;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
private:
    friend class DBRealDataDAO;
};

inline int RealData::GUID() const
{ return m_GUID;}

inline void RealData::setGUID(int guid)
{ m_GUID = guid;}

inline QString RealData::quality() const
{ return m_quality;}

inline void RealData::setQuality(const QString &quality)
{ m_quality = quality;}

inline QString RealData::updateTime() const
{ return m_updateTime;}

inline void RealData::setUpdateTime(const QString &updateTime)
{ m_updateTime = updateTime;}

inline QString RealData::iedName() const
{ return m_iedName;}

inline void RealData::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString RealData::dataRef() const
{ return m_dataRef;}

inline void RealData::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString RealData::dataDesc() const
{ return m_dataDesc;}

inline void RealData::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString RealData::business() const
{ return m_business;}

inline void RealData::setBusiness(const QString &business)
{ m_business = business;}

inline const QList<int> &RealData::lstDataType() const
{ return m_lstDataType;}

inline void RealData::clearDataType()
{ m_lstDataType.clear();}

inline const QStringList &RealData::lstDataValue() const
{ return m_lstDataValue;}

inline void RealData::clearDataValue()
{ m_lstDataValue.clear();}

inline void RealData::changeDataType(int type, int num)
{ m_lstDataType[num] = type;}

inline void RealData::changeDataValue(const QString &dataValue, int num)
{ m_lstDataValue[num] = dataValue;}
#endif // REALDATA_H
