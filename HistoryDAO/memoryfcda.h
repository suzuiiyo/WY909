#ifndef MEMORYFCDA_H
#define MEMORYFCDA_H
#include <QVector>
#include <QString>
#include <QHash>
#include "dastruct.h"
class MemoryFCDA
{
public:
    typedef QHash<QString, MemoryFCDA*> Hash;
public:
    MemoryFCDA();
    ~MemoryFCDA();
public:
    QString refName() const;
    QString fcdaDesc() const;
public:
    void setRefName(const QString &refName);
    void setFCDADesc(const QString &fcdaDesc);
public:
    const QVector<DAStruct*> & lstDAStruct() const;
    void addDAStruct(DAStruct *daStruct);
    void setLstDAStruct(QVector<DAStruct*> &lstDAStruct);
    void removeDAStruct(DAStruct *daStruct);
    void clearDAStruct();
private:
    QString m_refName;
    QString m_fcdaDesc;
    QVector<DAStruct*> m_lstDAStruct;
private:
    friend class DBIedDataSetDAO;
};

inline QString MemoryFCDA::refName() const
{ return m_refName;}

inline void MemoryFCDA::setRefName(const QString &refName)
{ m_refName = refName;}

inline QString MemoryFCDA::fcdaDesc() const
{ return m_fcdaDesc;}

inline void MemoryFCDA::setFCDADesc(const QString &fcdaDesc)
{ m_fcdaDesc = fcdaDesc;}

inline const QVector<DAStruct*> & MemoryFCDA::lstDAStruct() const
{ return m_lstDAStruct;}

inline void MemoryFCDA::setLstDAStruct(QVector<DAStruct*> &lstDAStruct)
{ m_lstDAStruct = lstDAStruct;}
#endif // MEMORYFCDA_H
