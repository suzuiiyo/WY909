#ifndef LIGHTPLATE_H
#define LIGHTPLATE_H
#include <QString>
#include <QList>
#include <QSharedPointer>
class LightPlate
{
public:
    typedef QSharedPointer<LightPlate> Ptr;
    typedef QList<Ptr> List;
public:
    LightPlate();
    ~LightPlate();
public:
    int GUID() const;
    QString iedName() const;
    QString dataRef() const;
    QString dataDesc() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setDataRef(const QString &dataRef);
    void setDataDesc(const QString &dataDesc);
private:
    int m_GUID;
    QString m_iedName;
    QString m_dataRef;
    QString m_dataDesc;
private:
    friend class DBAlarmLightPlateDAO;
    friend class DBPELightPlateDAO;
};

inline int LightPlate::GUID() const
{ return m_GUID;}

inline void LightPlate::setGUID(int guid)
{ m_GUID = guid;}

inline QString LightPlate::iedName() const
{ return m_iedName;}

inline void LightPlate::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString LightPlate::dataRef() const
{ return m_dataRef;}

inline void LightPlate::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString LightPlate::dataDesc() const
{ return m_dataDesc;}

inline void LightPlate::setDataDesc(const QString &dataDesc)
{ m_dataDesc = dataDesc;}
#endif // LIGHTPLATE_H
