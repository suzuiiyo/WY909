#ifndef FIBREOPTICAL_H
#define FIBREOPTICAL_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
class FibreOptical
{
public:
    typedef QSharedPointer<FibreOptical> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    FibreOptical();
    ~FibreOptical();
public:
    int GUID() const;
    QString lineRef() const;
    QString lineDesc() const;
    QString iedName1() const;
    QString port1() const;
    QString iedName2() const;
    QString port2() const;
public:
    void setGUID(int guid);
    void setLineDesc(const QString lineDesc);
    void setLineRef(const QString &lineRef);
    void setIedName1(const QString &iedName1);
    void setPort1(const QString &port1);
    void setIedName2(const QString &iedName2);
    void setPort2(const QString &port2);
private:
    int m_GUID;
    QString m_lineRef;
    QString m_lineDesc;
    QString m_iedName1;
    QString m_port1;
    QString m_iedName2;
    QString m_port2;
private:
    friend class DBFibreOpticalDAO;
};
inline int FibreOptical::GUID() const
{ return m_GUID;}

inline void FibreOptical::setGUID(int guid)
{ m_GUID = guid;}

inline QString FibreOptical::lineRef() const
{ return m_lineRef;}

inline void FibreOptical::setLineRef(const QString &lineRef)
{ m_lineRef = lineRef;}

inline QString FibreOptical::lineDesc() const
{ return m_lineDesc;}

inline void FibreOptical::setLineDesc(const QString lineDesc)
{ m_lineDesc = lineDesc;}

inline QString FibreOptical::iedName1() const
{ return m_iedName1;}

inline void FibreOptical::setIedName1(const QString &iedName1)
{ m_iedName1 = iedName1;}

inline QString FibreOptical::port1() const
{ return m_port1;}

inline void FibreOptical::setPort1(const QString &port1)
{ m_port1 = port1;}

inline QString FibreOptical::iedName2() const
{ return m_iedName2;}

inline void FibreOptical::setIedName2(const QString &iedName2)
{ m_iedName2 = iedName2;}

inline QString FibreOptical::port2() const
{ return m_port2;}

inline void FibreOptical::setPort2(const QString &port2)
{ m_port2 = port2;}
#endif // FIBREOPTICAL_H
