#ifndef RCDDEVICE_H
#define RCDDEVICE_H
#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QHash>
#include <QList>
#include "filercd.h"
class RcdDevice
{
public:
    typedef QSharedPointer<RcdDevice> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    RcdDevice();
    RcdDevice(int guid, const QString &iedName, const QString &ip, const QString &iedCateGory);
    ~RcdDevice();
public:
    struct RelationChannel
    {
        QString m_selfChannel;
        QString m_belongIed;
        QString m_name;
    };
public:
    int     GUID() const;
    QString iedName() const;
    QString ip() const;
    QString iedCateGory() const;
    bool    isConnected() const;
    qint64  pullFileTime() const;
public:
    void    setGUID(int guid);
    void    setIedName(const QString &iedName);
    void    setIp(const QString &ip);
    void    setIedCateGory(const QString &iedCateGory);
    void    setIsConnected(bool isConnected);
    void    setPullFileTime(qint64 time);
public:
    const FileRcd::List & fileRcd() const;
    FileRcd * fileRcd(const QString &name) const;
    FileRcd * getNewestFileRcd() const;
    FileRcd * addFileRcd(const QString &name, qint64 time);
    void removeFileRcd(FileRcd *fileRcd);
    void clearFileRcd();
public:
    const FileRcd::Hash & lstHadPullRcdFile() const;
    FileRcd * hadPullRcdFile(const QString &name) const;
    FileRcd * addHadPullRcdFile(const QString &name, qint64 time);
    //void removeHadPullRcdFile(FileRcd *fileRcd);
    void clearHadPullRcdFile();
public:
    const FileRcd::List & lstNeedPullRcdFile() const;
    FileRcd * needPullRcdFile(const QString &name) const;
    FileRcd * getNewestNeedPullRcdFile() const;
    FileRcd * addNeedPullRcdFile(const QString &name, qint64 time);
    void removeNeedPullRcdFile(FileRcd *fileRcd);
    void clearNeedPullRcdFile();
public:
    FileRcd * pullingFileRcd();
    bool havePullingFileRcd() const;
    bool haveNotPullFileRcd() const;
    bool haveFileNotPull() const;
    FileRcd * haveFileIsPulling();
public:
    const QHash<QString, QString> & relationIed() const;
    void addRelationIed(const QString &iedName, const QString &ip);
public:
    void addTMChannel(RcdDevice::RelationChannel &channel);
    void addTSChannel(RcdDevice::RelationChannel &channel);
    const QVector<RelationChannel> &tmChannel() const;
    const QVector<RelationChannel> &tsChannel() const;
    void clearTMChannel();
    void clearTSChannel();
protected:
    void adjustLstNeedPullRcdFile();
private:
    int                         m_GUID;
    QString                     m_iedName;
    QString                     m_ip;
    QString                     m_iedCateGory;
    bool                        m_isConnected;
    qint64                      m_pullFileTime;
    FileRcd::List               m_lstFileRcd;
    FileRcd::Hash               m_lstHadPullRcdFile;
    FileRcd::List               m_lstNeedPullRcdFile;
    QHash<QString, QString>     m_lstRelationIed;
    QVector<RelationChannel>    m_lstTMChannel;
    QVector<RelationChannel>    m_lstTSChannel;
private:
    friend class DBRcdDeviceDAO;
};

inline int RcdDevice::GUID() const
{ return m_GUID;}

inline void RcdDevice::setGUID(int guid)
{ m_GUID = guid;}

inline QString RcdDevice::iedName() const
{ return m_iedName;}

inline void RcdDevice::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString RcdDevice::ip() const
{ return m_ip;}

inline void RcdDevice::setIp(const QString &ip)
{ m_ip = ip;}

inline QString RcdDevice::iedCateGory() const
{ return m_iedCateGory;}

inline void RcdDevice::setIedCateGory(const QString &iedCateGory)
{ m_iedCateGory = iedCateGory;}

inline bool RcdDevice::isConnected() const
{ return m_isConnected;}

inline void RcdDevice::setIsConnected(bool isConnected)
{ m_isConnected = isConnected;}

inline qint64 RcdDevice::pullFileTime() const
{ return m_pullFileTime;}

inline const FileRcd::List & RcdDevice::fileRcd() const
{ return m_lstFileRcd;}

inline const FileRcd::Hash & RcdDevice::lstHadPullRcdFile() const
{ return m_lstHadPullRcdFile;}

inline const FileRcd::List & RcdDevice::lstNeedPullRcdFile() const
{ return m_lstNeedPullRcdFile;}

inline const QHash<QString, QString> & RcdDevice::relationIed() const
{ return m_lstRelationIed;}

inline const QVector<RcdDevice::RelationChannel> & RcdDevice::tmChannel() const
{ return m_lstTMChannel;}

inline const QVector<RcdDevice::RelationChannel> & RcdDevice::tsChannel() const
{ return m_lstTSChannel;}
#endif // RCDDEVICE_H
