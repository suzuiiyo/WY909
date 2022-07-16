#-------------------------------------------------
#
# Project created by QtCreator 2021-05-27T14:14:04
#
#-------------------------------------------------

QT       += sql
QT += xml

QT       -= gui

TARGET = RMYSQLDAO
TEMPLATE = lib

CONFIG += staticlib

DEFINES += RMYSQLDAO_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
DESTDIR = ../bin
OBJECTS_DIR = ../build/RMYSQLDAO/debug/
}
else {
DESTDIR = ../publish
OBJECTS_DIR = ../build/RMYSQLDAO/release/
}

MOC_DIR += ../build/

HEADERS += \
    acteventinfo.h \
    ackrecord.h \
    acteventinfo.h \
    alarmeventinfo.h \
    anarecord.h \
    baystate.h \
    connectionhistory.h \
    connectionstate.h \
    crcfiletaskrecord.h \
    dbactioneventdao.h \
    dbalarmeventdao.h \
    dbanarecorddao.h \
    dbbaystatedao.h \
    dbcondition.h \
    dbconfig.h \
    dbconnectionhistorydao.h \
    dbconnectionreal.h \
    dbconnectionstatedao.h \
    dbcrcfiletaskrecorddao.h \
    dbdevnoncorrespondingrecorddao.h \
    dbdevtemperaturedao.h \
    dbdiagnosisofprotoperaterecorddao.h \
    dbdifferentialcurrentdao.h \
    dbearlywarningdao.h \
    dbearlywarningrecorddao.h \
    dbgooserealdatadao.h \
    dbgooserecorddao.h \
    dbiedrealstatedao.h \
    dbinspectionresultdao.h \
    dblogrecorddao.h \
    dblooplinkalarmrecorddao.h \
    dbloopportalarmrecorddao.h \
    dborm.h \
    dbormfactory.h \
    dbpatrolconclusionrecorddao.h \
    dbpatrolfiledao.h \
    dbpatroltsrecorddao.h \
    dbpilotchanneloptpowerdao.h \
    dbpilotchannelothertmdatadao.h \
    dbpowervoltagedao.h \
    dbprotcurrentdao.h \
    dbprottransienttaskrecorddao.h \
    dbprotvoltagedao.h \
    dbrcdfiledao.h \
    dbrealdatadao.h \
    dbrecvoptpowerdao.h \
    dbrunstaterecorddao.h \
    dbsendoptpowerdao.h \
    dbsrtransienttaskrecorddao.h \
    dbsteadytasktmrecorddao.h \
    dbsteadytasktsrecorddao.h \
    dbstraprecorddao.h \
    dbtimesynrecorddao.h \
    dbtransienttaskconclusionrecorddao.h \
    dbtransienttaskfiledao.h \
    dbtransienttaskrecorddao.h \
    dbuserinfodao.h \
    devnoncorrespondingrecord.h \
    devtemperature.h \
    diagnosisofprotoperaterecord.h \
    differentialcurrent.h \
    earlywarning.h \
    earlywarningrecord.h \
    gooserealdata.h \
    gooserecord.h \
    iedstate.h \
    initmariadb.h \
    inspectionresult.h \
    logrecord.h \
    looplinkalarmrecord.h \
    loopportalarmrecord.h \
    mmsrecvserver.h \
    parseconfig.h \
    patrolconclusionrecord.h \
    patrolfile.h \
    patroltsrecord.h \
    pilotchanneloptpower.h \
    pilotchannelothertmdata.h \
    powervoltage.h \
    protcurrent.h \
    prottransienttaskrecord.h \
    protvoltage.h \
    qdbconnectionreal.h \
    rcdfile.h \
    realdata.h \
    recvoptpower.h \
    rmysqldao_global.h \
    rmysqldao.h \
    runstaterecord.h \
    searchcondition.h \
    sendoptpower.h \
    srtransienttaskrecord.h \
    steadytasktmrecord.h \
    steadytasktsrecord.h \
    straprecord.h \
    timesynrecord.h \
    transienttaskconclusionrecord.h \
    transienttaskfile.h \
    transienttaskrecord.h \
    userinfo.h \
    transientswitchtaskconclusionrecord.h \
    dbtransientswitchconclusionrecorddao.h

SOURCES += \
    ackrecord.cpp \
    acteventinfo.cpp \
    alarmeventinfo.cpp \
    anarecord.cpp \
    baystate.cpp \
    connectionhistory.cpp \
    connectionstate.cpp \
    crcfiletaskrecord.cpp \
    dbactioneventdao.cpp \
    dbalarmeventdao.cpp \
    dbanarecorddao.cpp \
    dbbaystatedao.cpp \
    dbcondition.cpp \
    dbconfig.cpp \
    dbconnectionhistorydao.cpp \
    dbconnectionreal.cpp \
    dbconnectionstatedao.cpp \
    dbcrcfiletaskrecorddao.cpp \
    dbdevnoncorrespondingrecorddao.cpp \
    dbdevtemperaturedao.cpp \
    dbdiagnosisofprotoperaterecorddao.cpp \
    dbdifferentialcurrentdao.cpp \
    dbearlywarningdao.cpp \
    dbearlywarningrecorddao.cpp \
    dbgooserealdatadao.cpp \
    dbgooserecorddao.cpp \
    dbiedrealstatedao.cpp \
    dbinspectionresultdao.cpp \
    dblogrecorddao.cpp \
    dblooplinkalarmrecorddao.cpp \
    dbloopportalarmrecorddao.cpp \
    dborm.cpp \
    dbormfactory.cpp \
    dbpatrolconclusionrecorddao.cpp \
    dbpatrolfiledao.cpp \
    dbpatroltsrecorddao.cpp \
    dbpilotchanneloptpowerdao.cpp \
    dbpilotchannelothertmdatadao.cpp \
    dbpowervoltagedao.cpp \
    dbprotcurrentdao.cpp \
    dbprottransienttaskrecorddao.cpp \
    dbprotvoltagedao.cpp \
    dbrcdfiledao.cpp \
    dbrealdatadao.cpp \
    dbrecvoptpowerdao.cpp \
    dbrunstaterecorddao.cpp \
    dbsendoptpowerdao.cpp \
    dbsrtransienttaskrecorddao.cpp \
    dbsteadytasktmrecorddao.cpp \
    dbsteadytasktsrecorddao.cpp \
    dbstraprecorddao.cpp \
    dbtimesynrecorddao.cpp \
    dbtransienttaskconclusionrecorddao.cpp \
    dbtransienttaskfiledao.cpp \
    dbtransienttaskrecorddao.cpp \
    dbuserinfodao.cpp \
    devnoncorrespondingrecord.cpp \
    devtemperature.cpp \
    diagnosisofprotoperaterecord.cpp \
    differentialcurrent.cpp \
    earlywarning.cpp \
    earlywarningrecord.cpp \
    gooserealdata.cpp \
    gooserecord.cpp \
    iedstate.cpp \
    initmariadb.cpp \
    inspectionresult.cpp \
    logrecord.cpp \
    looplinkalarmrecord.cpp \
    loopportalarmrecord.cpp \
    parseconfig.cpp \
    patrolconclusionrecord.cpp \
    patrolfile.cpp \
    patroltsrecord.cpp \
    pilotchanneloptpower.cpp \
    pilotchannelothertmdata.cpp \
    powervoltage.cpp \
    protcurrent.cpp \
    prottransienttaskrecord.cpp \
    protvoltage.cpp \
    qdbconnectionreal.cpp \
    rcdfile.cpp \
    realdata.cpp \
    recvoptpower.cpp \
    rmysqldao.cpp \
    runstaterecord.cpp \
    searchcondition.cpp \
    sendoptpower.cpp \
    srtransienttaskrecord.cpp \
    steadytasktmrecord.cpp \
    steadytasktsrecord.cpp \
    straprecord.cpp \
    timesynrecord.cpp \
    transienttaskconclusionrecord.cpp \
    transienttaskrecord.cpp \
    userinfo.cpp \
    transientswitchtaskconclusionrecord.cpp \
    dbtransientswitchconclusionrecorddao.cpp
