#ifndef INITMARIADB_H
#define INITMARIADB_H
#include <QStringList>
class InitMariaDB
{
public:
    InitMariaDB();
    ~InitMariaDB();
public:
    bool initRealData();
    bool initGooseRealData();
    bool initActionEvent();
    bool initAlarmEvent();
    bool initConnectionState();
    bool initConnectHistory();
    bool initDevtemperature();
    bool initSendOptPower();
    bool initRecvOptPower();
    bool initPilotChannelOptPower();
    bool initPowerVoltage();
    bool initDifferentialCurrent();
    bool initEarlyWarning();
    bool initEarlyWarningRecord();
    bool initIedState();
    bool initBayState();
    bool initDevNonCorrespondingRecord();
    bool initLoopPortAlarmRecord();
    bool initLoopLinkAlarmRecord();
    bool initGooseRecord();
    bool initRunStateRecord();
    bool initAnaRecord();
    bool initStrapRecord();
    bool initTimeSynRecord();
private:
    void initLstIedName();
private:
    QStringList m_lstIedName;
};
#endif // INITMARIADB_H
