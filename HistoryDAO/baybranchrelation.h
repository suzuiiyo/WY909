#ifndef BAYBRANCHRELATION_H
#define BAYBRANCHRELATION_H
#include <QSharedPointer>
#include <QList>
#include <QString>
#include <QHash>
class BayBranchRelation
{
public:
    typedef QSharedPointer<BayBranchRelation> Ptr;
    typedef QList<Ptr> List;
    typedef QHash<QString, Ptr> Hash;
public:
    BayBranchRelation();
    ~BayBranchRelation();
public:
    int GUID() const;
    QString makeupBayName() const;
    QString baseBayName() const;
    QString makeupBayType() const;
    QString branch() const;
public:
    void setGUID(int guid);
    void setMakeupBayName(const QString &makeupBayName);
    void setBaseBayName(const QString &baseBayName);
    void setMakeupBayType(const QString &makeupBayType);
    void setBranch(const QString &branch);
private:
    int m_GUID;
    QString m_makeupBayName;
    QString m_baseBayName;
    QString m_makeupBayType;
    QString m_branch;
private:
    friend class DBBayBranchRelationDAO;
};

inline int BayBranchRelation::GUID() const
{ return m_GUID;}

inline void BayBranchRelation::setGUID(int guid)
{ m_GUID = guid;}

inline QString BayBranchRelation::makeupBayName() const
{ return m_makeupBayName;}

inline void BayBranchRelation::setMakeupBayName(const QString &makeupBayName)
{ m_makeupBayName = makeupBayName;}

inline QString BayBranchRelation::baseBayName() const
{ return m_baseBayName;}

inline void BayBranchRelation::setBaseBayName(const QString &baseBayName)
{ m_baseBayName = baseBayName;}

inline QString BayBranchRelation::makeupBayType() const
{ return m_makeupBayType;}

inline void BayBranchRelation::setMakeupBayType(const QString &makeupBayType)
{ m_makeupBayType = makeupBayType;}

inline QString BayBranchRelation::branch() const
{ return m_branch;}

inline void BayBranchRelation::setBranch(const QString &branch)
{ m_branch = branch;}
#endif // BAYBRANCHRELATION_H
