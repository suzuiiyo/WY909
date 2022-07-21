#ifndef SVINFO_H
#define SVINFO_H
#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QHash>
class SVInfo
{
public:
    typedef QSharedPointer<SVInfo> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    SVInfo();
    ~SVInfo();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataSet() const;
    QString dataDesc() const;
    QString dimension() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataSet(const QString &dataSet);
    void setDataDesc(const QString &dataDesc);
    void setDimension(const QString &dimension);
private:
    int m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataSet;
    QString m_dataDesc;
    QString m_dimension;
private:
    friend class DBSVInfoDAO;
};
inline int SVInfo::GUID() const
{ return m_GUID;}

inline void SVInfo::setGUID(int guid)
{ m_GUID = guid;}

inline QString SVInfo::iedName() const
{ return m_iedName;}

inline void SVInfo::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString SVInfo::dataRef() const
{ return m_dataRef;}

inline void SVInfo::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString SVInfo::dataSet() const
{ return m_dataSet;}

inline void SVInfo::setDataSet(const QString &dataSet)
{ m_dataSet = dataSet;}

inline QString SVInfo::dataDesc() const
{ return m_dataDesc;}

inline void SVInfo::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}

inline QString SVInfo::dimension() const
{ return m_dimension;}

inline void SVInfo::setDimension(const QString &dimension)
{ m_dimension = dimension;}
#endif // SVINFO_H
