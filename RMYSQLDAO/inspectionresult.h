#ifndef INSPECTIONRESULT_H
#define INSPECTIONRESULT_H
#include <QSharedPointer>
#include <QList>
#include <QString>
class InspectionResult
{
public:
    typedef QSharedPointer<InspectionResult> Ptr;
    typedef QList<Ptr> List;
public:
    InspectionResult();
    ~InspectionResult();
public:
    QString iedName() const;
    int     result() const;
    QString dbTime() const;
    QString nextTaskTime() const;
    QString content() const;
    QString installTime() const;
    QString deliveryTime() const;
public:
    void setIedName(const QString &iedName);
    void setResult(int result);
    void setDBTime(const QString &dbTime);
    void setNextTaskTime(const QString &nextTaskTime);
    void setContent(const QString &content);
    void setInstallTime(const QString &installTime);
    void setDeliveryTime(const QString &deliveryTime);
private:
    QString m_iedName;
    int     m_result;
    QString m_dbTime;
    QString m_nextTaskTime;
    QString m_content;
    QString m_installTime;
    QString m_deliveryTime;
private:
    friend class DBInspectionResultDAO;
};

inline QString InspectionResult::iedName() const
{ return m_iedName;}

inline void InspectionResult::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline int InspectionResult::result() const
{ return m_result;}

inline void InspectionResult::setResult(int result)
{ m_result = result;}

inline QString InspectionResult::dbTime() const
{ return m_dbTime;}

inline void InspectionResult::setDBTime(const QString &dbTime)
{ m_dbTime = dbTime;}

inline QString InspectionResult::nextTaskTime() const
{ return m_nextTaskTime;}

inline void InspectionResult::setNextTaskTime(const QString &nextTaskTime)
{ m_nextTaskTime = nextTaskTime;}

inline QString InspectionResult::content() const
{ return m_content;}

inline void InspectionResult::setContent(const QString &content)
{ m_content = content;}

inline QString InspectionResult::installTime() const
{ return m_installTime;}

inline void InspectionResult::setInstallTime(const QString &installTime)
{ m_installTime = installTime;}

inline QString InspectionResult::deliveryTime() const
{ return m_deliveryTime;}

inline void InspectionResult::setDeliveryTime(const QString &deliveryTime)
{ m_deliveryTime = deliveryTime;}
#endif // INSPECTIONRESULT_H
