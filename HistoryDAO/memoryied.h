#ifndef MEMORYIED_H
#define MEMORYIED_H
#include <QString>
#include <QHash>
#include <QSharedPointer>
#include "memoryfcda.h"
class MemoryIed
{
public:
    typedef QSharedPointer<MemoryIed> Ptr;
    typedef QHash<QString, Ptr> Hash;
public:
    MemoryIed();
    ~MemoryIed();
public:
    int GUID() const;
    QString iedName() const;
    QString iedDesc() const;
    QString iedCateGory() const;
    QString ip() const;
    int connectionState() const;
public:
    void setGUID(int guid);
    void setIedName(const QString &iedName);
    void setIedDesc(const QString &iedDesc);
    void setIedCateGory(const QString &iedCateGory);
    void setIp(const QString &ip);
    void setConnectionState(int state);
public:
    const MemoryFCDA::Hash & hashFCDA() const;
    void addFCDA(MemoryFCDA *fcda);
    void setLstFCDA(MemoryFCDA::Hash &hashFCDA);
    void clearFCDA();
private:
    int m_GUID;
    QString m_iedName;
    QString m_iedDesc;
    QString m_iedCateGory;
    QString m_ip;
    int m_connectionState;
    MemoryFCDA::Hash m_hashMemoryFCDA;
private:
    friend class DBIedInfoDAO;
};

inline int MemoryIed::GUID() const
{ return m_GUID;}

inline void MemoryIed::setGUID(int guid)
{ m_GUID = guid;}

inline QString MemoryIed::iedName() const
{ return m_iedName;}

inline void MemoryIed::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString MemoryIed::iedDesc() const
{ return m_iedDesc;}

inline void MemoryIed::setIedDesc(const QString &iedDesc)
{ m_iedDesc = iedDesc;}

inline QString MemoryIed::iedCateGory() const
{ return m_iedCateGory;}

inline void MemoryIed::setIedCateGory(const QString &iedCateGory)
{ m_iedCateGory = iedCateGory;}

inline QString MemoryIed::ip() const
{ return m_ip;}

inline void MemoryIed::setIp(const QString &ip)
{ m_ip = ip;}

inline int MemoryIed::connectionState() const
{ return m_connectionState;}

inline void MemoryIed::setConnectionState(int state)
{ m_connectionState = state;}

inline const MemoryFCDA::Hash & MemoryIed::hashFCDA() const
{ return m_hashMemoryFCDA;}

inline void MemoryIed::setLstFCDA(MemoryFCDA::Hash &hashFCDA)
{ m_hashMemoryFCDA = hashFCDA;}
#endif // MEMORYIED_H
