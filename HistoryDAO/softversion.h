#ifndef SOFTVERSION_H
#define SOFTVERSION_H
#include <QSharedPointer>
#include <QList>
#include <QString>
#include <QVector>
#include "dastruct.h"
class SoftVersion
{
public:
    typedef QSharedPointer<SoftVersion> Ptr;
    typedef QList<Ptr> List;
public:
    SoftVersion();
    ~SoftVersion();
public:
    int GUID() const;
    QString iedName() const;
    QString iedCateGory() const;
    int type() const;
    QString softVerDesc() const;
    QString standardValue() const;
    QString defaultValue() const;
    QString dataRef() const;
    QString dataType() const;
    int selfType() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setIedCateGory(const QString &iedCateGory);
    void setType(int type);
    void setSoftVerDesc(const QString &softVerDesc);
    void setStandardValue(const QString &standardValue);
    void setDefaultValue(const QString &defaultValue);
    void setDataRef(const QString &dataRef);
    void setDataType(const QString &dataType);
    void setSelfType(int selfType);
public:
    const QVector<DAStruct*> & lstDAStruct() const;
    void addDAStruct(DAStruct *daStruct);
    void setLstDAStruct(QVector<DAStruct*> &lstDAStruct);
    void removeDAStruct(DAStruct *daStruct);
    void clearDAStruct();
private:
    int m_GUID;
    QString m_iedName;
    QString m_iedCateGory;
    int m_type;
    QString m_softVerDesc;
    QString m_standardValue;
    QString m_defaultValue;
    QString m_dataRef;
    QString m_dataType;
    int m_selfType;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBSoftVersionDAO;
};

inline int SoftVersion::GUID() const
{ return m_GUID;}

inline void SoftVersion::setGUID(int guid)
{ m_GUID = guid;}

inline QString SoftVersion::iedName() const
{ return m_iedName;}

inline void SoftVersion::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString SoftVersion::iedCateGory() const
{ return m_iedCateGory;}

inline void SoftVersion::setIedCateGory(const QString &iedCateGory)
{ m_iedCateGory = iedCateGory;}

inline int SoftVersion::type() const
{ return m_type;}

inline void SoftVersion::setType(int type)
{ m_type = type;}

inline QString SoftVersion::softVerDesc() const
{ return m_softVerDesc;}

inline void SoftVersion::setSoftVerDesc(const QString &softVerDesc)
{ m_softVerDesc = softVerDesc;}

inline QString SoftVersion::standardValue() const
{ return m_standardValue;}

inline void SoftVersion::setStandardValue(const QString &standardValue)
{ m_standardValue = standardValue;}

inline QString SoftVersion::defaultValue() const
{ return m_defaultValue;}

inline void SoftVersion::setDefaultValue(const QString &defaultValue)
{ m_defaultValue = defaultValue;}

inline QString SoftVersion::dataRef() const
{ return m_dataRef;}

inline void SoftVersion::setDataRef(const QString &dataRef)
{ m_dataRef = dataRef;}

inline QString SoftVersion::dataType() const
{ return m_dataType;}

inline void SoftVersion::setDataType(const QString &dataType)
{ m_dataType = dataType;}

inline int SoftVersion::selfType() const
{ return m_selfType;}

inline void SoftVersion::setSelfType(int selfType)
{ m_selfType = selfType;}

inline const QVector<DAStruct*> & SoftVersion::lstDAStruct() const
{ return m_lstDAStruct;}

inline void SoftVersion::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // SOFTVERSION_H
