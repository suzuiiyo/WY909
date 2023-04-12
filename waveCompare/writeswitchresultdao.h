#ifndef WRITESWITCHRESULTDAO_H
#define WRITESWITCHRESULTDAO_H
#include <QString>
#include <QSqlDatabase>
#include "dbtransientswitchconclusionrecorddao.h"

class WriteSwitchResultDao
{
public:
    WriteSwitchResultDao();
    ~WriteSwitchResultDao();
    
public:
    bool init();
    void setIedName(const QString &);
    void setSetType(const QString &);
    void setIedNameComp(const QString &);
    void setSetTypeComp(const QString &);
    void setRecloseAckDelay(const QString &);
    void setBreakerAckDelay(const QString &);
    void setFaultZeroTime(const QString &);
    
    void setSrIedAFileName(const QString &);
    void setSrIedBFileName(const QString &);
    void setTaskFileName(const QString &);
    void setStandardFileName(const QString &);
    void setChannelType(const QString &);
    void setConclusion(const QString&);
    void setRecloseConclusion(const float&);
    void setBreakerConclusion(const float&);
    void setReclosingInnormalTime(const QString&);
    void setReclosingSeriousTime(const QString&);
    
    void setbreakerInnormalTime(const QString &);
    void setbreakerSeriousTime(const QString &);
    void setReclosingResult(const int&);
    void setBreakerResult(const int&);
    
    void setTaskChannelRef(const int&);
    void setTaskChannelDesc(const QString &);
    void setStandardChannelRef(const int &);
    void setStandardChannelDesc(const QString &);
    void setRecordTime(const QString &);
    void setAckTip(int &);
    void setIedTaskType(const QString &);
    void setIedPhase(const QString &);
    void setBayName(const QString &);
    void setItemName(const QString &);

    TransientSwitchTaskConclusionRecord::Ptr getTSCR();
    
private:
    TransientSwitchTaskConclusionRecord::Ptr tscr;
};

#endif // WRITESWITCHRESULTDAO_H
