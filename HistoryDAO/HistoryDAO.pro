#-------------------------------------------------
#
# Project created by QtCreator 2021-03-30T13:40:56
#
#-------------------------------------------------

QT       += sql
QT       += xml

QT       -= gui

TARGET = HistoryDAO
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbconnection.cpp \
    ied.cpp \
    ieddataset.cpp \
    dboption.cpp \
    devrunstate.cpp \
    strap.cpp \
    dbiedinfodao.cpp \
    dbieddatasetdao.cpp \
    dbstraplightplatedao.cpp \
    monitorinfo.cpp \
    dbiedstatedao.cpp \
    devstate.cpp \
    svinfo.cpp \
    dbsvinfodao.cpp \
    tsdatainfo.cpp \
    tmdatainfo.cpp \
    eventinfo.cpp \
    alarminfo.cpp \
    otherdatainfo.cpp \
    dbtmdatainfodao.cpp \
    dbtsdatainfodao.cpp \
    dbeventinfodao.cpp \
    dbalarminfodao.cpp \
    dbdevrunstatedao.cpp \
    dbsettingdao.cpp \
    dbgooseinfodao.cpp \
    setting.cpp \
    gooseinfo.cpp \
    dbotherdatainfodao.cpp \
    indicatorlamp.cpp \
    dbindicatorlampdao.cpp \
    eventrecord.cpp \
    rcdinfo.cpp \
    dbrcdinfodao.cpp \
    dastruct.cpp \
    dbdastructdao.cpp \
    fibreoptical.cpp \
    optport.cpp \
    dboptportdao.cpp \
    dbfibreopticaldao.cpp \
    stationinfo.cpp \
    voltclassinfo.cpp \
    bayinfo.cpp \
    dbbayinfodao.cpp \
    dbvoltclassinfodao.cpp \
    dbstationinfodao.cpp \
    primarydeviceinfo.cpp \
    dbprimarydeviceinfodao.cpp \
    earlywarningconfig.cpp \
    dbearlywarningconfigdao.cpp \
    appid.cpp \
    dbappiddao.cpp \
    virloopconfig.cpp \
    dbvirloopconfigdao.cpp \
    virloopiedinfo.cpp \
    virlooprecvied.cpp \
    virloopsendied.cpp \
    switchdevice.cpp \
    gooseinst.cpp \
    baybranchrelation.cpp \
    dbbaybranchrelationdao.cpp \
    dbcolumntypetransform.cpp \
    softversion.cpp \
    dbsoftversiondao.cpp \
    switchport.cpp \
    dbswitchportdao.cpp \
    memoryfcda.cpp \
    memoryied.cpp \
    patrol.cpp \
    dbpatroldao.cpp \
    dbrcddevicedao.cpp \
    rcddevice.cpp \
    filercd.cpp \
    sqlitedbconfig.cpp \
    readconfig.cpp \
    anaconfig.cpp \
    dbanaconfigdao.cpp \
    steadytasktmconfig.cpp \
    dbsteadytasktmconfigdao.cpp \
    transienttasktmconfig.cpp \
    transienttasktsconfig.cpp \
    steadytasktsconfig.cpp \
    dbtransienttasktmconfigdao.cpp \
    dbtransienttasktsconfigdao.cpp \
    dbsteadytasktsconfigdao.cpp \
    qdbconnection.cpp \
    diagnosisofprotoperateconfig.cpp \
    dbdiagnosisofprotoperateconfigdao.cpp \
    dbiedconfighistorydao.cpp

HEADERS += \
    dbconnection.h \
    ied.h \
    ieddataset.h \
    dboption.h \
    devrunstate.h \
    lightplate.h \
    strap.h \
    dbiedinfodao.h \
    dbieddatasetdao.h \
    dbstraplightplatedao.h \
    monitorinfo.h \
    dbiedstatedao.h \
    dbsvinfodao.h \
    tsdatainfo.h \
    tmdatainfo.h \
    eventinfo.h \
    alarminfo.h \
    otherdatainfo.h \
    setting.h \
    svinfo.h \
    gooseinfo.h \
    dbtmdatainfodao.h \
    dbeventinfodao.h \
    dbalarminfodao.h \
    dbdevrunstatedao.h \
    dbsettingdao.h \
    dbgooseinfodao.h \
    dbotherdatainfodao.h \
    eventrecord.h \
    indicatorlamp.h \
    dbindicatorlampdao.h \
    dbtsdatainfodao.h \
    devstate.h \
    rcdinfo.h \
    dbrcdinfodao.h \
    dastruct.h \
    dbdastructdao.h \
    fibreoptical.h \
    optport.h \
    dboptportdao.h \
    dbfibreopticaldao.h \
    stationinfo.h \
    voltclassinfo.h \
    bayinfo.h \
    dbbayinfodao.h \
    dbvoltclassinfodao.h \
    dbstationinfodao.h \
    primarydeviceinfo.h \
    dbprimarydeviceinfodao.h \
    dbearlywarningconfigdao.h \
    earlywarningconfig.h \
    appid.h \
    dbappiddao.h \
    virloopconfig.h \
    dbvirloopconfigdao.h \
    virloopiedinfo.h \
    gooseinst.h \
    virlooprecvied.h \
    virloopsendied.h \
    switchdevice.h \
    childbayinfo.h \
    baybranchrelation.h \
    dbbaybranchrelationdao.h \
    dbcolumntypetransform.h \
    softversion.h \
    dbsoftversiondao.h \
    switchport.h \
    dbswitchportdao.h \
    memoryied.h \
    memoryfcda.h \
    patrol.h \
    dbpatroldao.h \
    dbrcddevicedao.h \
    rcddevice.h \
    filercd.h \
    readconfig.h \
    sqlitedbconfig.h \
    anaconfig.h \
    dbanaconfigdao.h \
    steadytasktmconfig.h \
    dbsteadytasktmconfigdao.h \
    transienttasktmconfig.h \
    transienttasktsconfig.h \
    steadytasktsconfig.h \
    dbtransienttasktmconfigdao.h \
    dbtransienttasktsconfigdao.h \
    dbsteadytasktsconfigdao.h \
    qdbconnection.h \
    diagnosisofprotoperateconfig.h \
    dbdiagnosisofprotoperateconfigdao.h \
    dbiedconfighistorydao.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
DESTDIR = ../bin
OBJECTS_DIR = ../build/HistoryDAO/debug/
}
else {
DESTDIR = ../publish
OBJECTS_DIR = ../build/HistoryDAO/release/
}

MOC_DIR += ../build/
