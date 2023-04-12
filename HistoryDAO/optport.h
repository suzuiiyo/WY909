#ifndef OPTPORT_H
#define OPTPORT_H
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QVector>
#include "dastruct.h"
class OptPort
{
public:
    typedef QSharedPointer<OptPort> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    OptPort();
    OptPort(const QString &sendValue, const QString &recvValue, const QString &sendUpAlarmValue, const QString &sendDownAlarmValue, const QString &recvUpAlarmValue, const QString &recvDownAlarmValue);
    ~OptPort();
public:
    int GUID() const;
    QString portID() const;
    QString iedName() const;
    QString portDesc() const;
    QString lineRef() const;
    QString sendValueRef() const;
    QString recvValueRef() const;
    QString sendUpAlarmRef() const;
    QString sendDownAlarmRef() const;
    QString recvUpAlarmRef() const;
    QString recvDownAlarmRef() const;
    float sendMax() const;
    float sendMin() const;
    float recvMax() const;
    float recvMin() const;
    int netType() const;
//    float sendValue() const;
//    float recvValue() const;
//    int sendUpAlarmValue() const;
//    int sendDownAlarmValue() const;
//    int recvUpAlarmValue() const;
//    int recvDownAlarmValue() const;
public:
    void setGUID(int guid);
    void setPortID(const QString &portID);
    void setIedName(const QString &iedName);
    void setPortDesc(const QString &portDesc);
    void setLineRef(const QString &lineRef);
    void setSendValueRef(const QString &sendValueRef);
    void setRecvValueRef(const QString &recvValueRef);
    void setSendUpAlarmRef(const QString &sendUpAlarmRef);
    void setSendDownAlarmRef(const QString &sendDownAlarmRef);
    void setRecvUpAlarmRef(const QString &recvUpAlarmRef);
    void setRecvDownAlarmRef(const QString &recvDownAlarmRef);
    void setSendMax(float sendMax);
    void setSendMin(float sendMin);
    void setRecvMax(float recvMax);
    void setRecvMin(float recvMin);
    void setNetType(int netType);
//    void setSendValue(float sendValue);
//    void setRecvValue(float recvValue);
//    void setSendUpAlarmValue(int sendUpAlarmValue);
//    void setSendDownAlarmValue(int sendDownAlarmValue);
//    void setRecvUpAlarmValue(int recvUpAlarmValue);
//    void setRecvDownAlarmValue(int recvDownAlarmValue);
public:
    const QStringList & lstDataValue() const;
    const QList<int> & lstDataType() const;
    void addDataValue(const QString &dataValue);
    void addDataType(int dataType);
    void clearDataValue();
    void clearDataType();
//public:
//    const QVector<DAStruct*> & lstDAStruct() const;
//    void addDAStruct(DAStruct *daStruct);
//    void setLstDAStruct(QVector<DAStruct*> &lstDAStruct);
//    void removeDAStruct(DAStruct *daStruct);
//    void clearDAStruct();
private:
    int m_GUID;
    QString m_portID;
    QString m_iedName;
    QString m_portDesc;
    QString m_lineRef;
    QString m_sendValueRef;
    QString m_recvValueRef;
    QString m_sendUpAlarmRef;
    QString m_sendDownAlarmRef;
    QString m_recvUpAlarmRef;
    QString m_recvDownAlarmRef;
    float m_sendMax;
    float m_sendMin;
    float m_recvMax;
    float m_recvMin;
    int m_netType;
    QList<int> m_lstDataType;
    QStringList m_lstDataValue;
    //QVector<DAStruct*> m_lstDAStruct;
//    float m_sendValue;
//    float m_recvValue;
//    int m_sendUpAlarmValue;
//    int m_sendDownAlarmValue;
//    int m_recvUpAlarmValue;
//    int m_recvDownAlarmValue;
private:
    friend class DBOptPortDAO;
};

inline int OptPort::GUID() const
{ return m_GUID;}

inline void OptPort::setGUID(int guid)
{ m_GUID = guid;}

inline QString OptPort::portID() const
{ return m_portID;}

inline void OptPort::setPortID(const QString &portID)
{ m_portID = portID;}

inline QString OptPort::iedName() const
{ return m_iedName;}

inline void OptPort::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline QString OptPort::portDesc() const
{ return m_portDesc;}

inline void OptPort::setPortDesc(const QString &portDesc)
{ m_portDesc = portDesc;}

inline QString OptPort::lineRef() const
{ return m_lineRef;}

inline void OptPort::setLineRef(const QString &lineRef)
{ m_lineRef = lineRef;}

inline QString OptPort::sendValueRef() const
{ return m_sendValueRef;}

inline void OptPort::setSendValueRef(const QString &sendValueRef)
{ m_sendValueRef = sendValueRef;}

inline QString OptPort::recvValueRef() const
{ return m_recvValueRef;}

inline void OptPort::setRecvValueRef(const QString &recvValueRef)
{ m_recvValueRef = recvValueRef;}

inline QString OptPort::sendUpAlarmRef() const
{ return m_sendUpAlarmRef;}

inline void OptPort::setSendUpAlarmRef(const QString &sendUpAlarmRef)
{ m_sendUpAlarmRef = sendUpAlarmRef;}

inline QString OptPort::sendDownAlarmRef() const
{ return m_sendDownAlarmRef;}

inline void OptPort::setSendDownAlarmRef(const QString &sendDownAlarmRef)
{ m_sendDownAlarmRef = sendDownAlarmRef;}

inline QString OptPort::recvUpAlarmRef() const
{ return m_recvUpAlarmRef;}

inline void OptPort::setRecvUpAlarmRef(const QString &recvUpAlarmRef)
{ m_recvUpAlarmRef = recvUpAlarmRef;}

inline QString OptPort::recvDownAlarmRef() const
{ return m_recvDownAlarmRef;}

inline void OptPort::setRecvDownAlarmRef(const QString &recvDownAlarmRef)
{ m_recvDownAlarmRef = recvDownAlarmRef;}

inline float OptPort::sendMax() const
{ return m_sendMax;}

inline void OptPort::setSendMax(float sendMax)
{ m_sendMax = sendMax;}

inline float OptPort::sendMin() const
{ return m_sendMin;}

inline void OptPort::setSendMin(float sendMin)
{ m_sendMin = sendMin;}

inline float OptPort::recvMax() const
{ return m_recvMax;}

inline void OptPort::setRecvMax(float recvMax)
{ m_recvMax = recvMax;}

inline float OptPort::recvMin() const
{ return m_recvMin;}

inline void OptPort::setRecvMin(float recvMin)
{ m_recvMin = recvMin;}

inline int OptPort::netType() const
{ return m_netType;}

inline void OptPort::setNetType(int netType)
{ m_netType = netType;}

inline const QStringList &OptPort::lstDataValue() const
{ return m_lstDataValue;}

inline void OptPort::clearDataValue()
{ m_lstDataValue.clear();}

inline const QList<int> &OptPort::lstDataType() const
{ return m_lstDataType;}

inline void OptPort::clearDataType()
{ m_lstDataType.clear();}

//inline const QVector<DAStruct*> & OptPort::lstDAStruct() const
//{ return m_lstDAStruct;}

//inline void OptPort::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
//{ m_lstDAStruct = lstDAStruct;}

//inline float OptPort::sendValue() const
//{ return m_sendValue;}

//inline void OptPort::setSendValue(float sendValue)
//{ m_sendValue = sendValue;}

//inline float OptPort::recvValue() const
//{ return m_recvValue;}

//inline void OptPort::setRecvValue(float recvValue)
//{ m_recvValue = recvValue;}

//inline int OptPort::sendUpAlarmValue() const
//{ return m_sendUpAlarmValue;}

//inline void OptPort::setSendUpAlarmValue(int sendUpAlarmValue)
//{ m_sendUpAlarmValue = sendUpAlarmValue;}

//inline int OptPort::sendDownAlarmValue() const
//{ return m_sendDownAlarmValue;}

//inline void OptPort::setSendDownAlarmValue(int sendDownAlarmValue)
//{ m_sendDownAlarmValue = sendDownAlarmValue;}

//inline int OptPort::recvUpAlarmValue() const
//{ return m_recvUpAlarmValue;}

//inline void OptPort::setRecvUpAlarmValue(int recvUpAlarmValue)
//{ m_recvUpAlarmValue = recvUpAlarmValue;}

//inline int OptPort::recvDownAlarmValue() const
//{ return m_recvDownAlarmValue;}

//inline void OptPort::setRecvDownAlarmValue(int recvDownAlarmValue)
//{ m_recvDownAlarmValue = recvDownAlarmValue;}
#endif // OPTPORT_H
