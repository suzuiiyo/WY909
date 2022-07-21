#-------------------------------------------------
#
# Project created by QtCreator 2010-07-26T15:54:09
#
#-------------------------------------------------

QT -= gui

TARGET = WYCmtdAna
TEMPLATE = lib
CONFIG += staticlib

DEFINES += MARKUP_STL MARKUP_WCHAR MARKUP_STDCONV
DEFINES += GDWY_JIANCE

SOURCES += \
    WyCal.cpp \
    SwitchStatusList.cpp \
    GenerateReport.cpp \
    EleTrans.cpp \
    EleRemark.cpp \
    EleLine.cpp \
    EleDChanel.cpp \
    EleDC.cpp \
    EleBus.cpp \
    EleAChanel.cpp \
    CmtdSegment.cpp \
    CmtdFile.cpp \
    readthread.cpp \
    CnCodec.cpp \
    DMFReader.cpp \
    EleTransWiding.cpp \
    EleExciter.cpp \
    EleGenerator.cpp \
    Markup.cpp

HEADERS += \
    ../Analib_include/WyCal.h \
    ../Analib_include/VarDef.h \
    ../Analib_include/SwitchStatusList.h \
    ../Analib_include/GenerateReport.h \
    ../Analib_include/EleTrans.h \
    ../Analib_include/EleRemark.h \
    ../Analib_include/EleLine.h \
    ../Analib_include/EleDChanel.h \
    ../Analib_include/EleDC.h \
    ../Analib_include/EleBus.h \
    ../Analib_include/EleAChanel.h \
    ../Analib_include/CmtdSegment.h \
    ../Analib_include/CmtdFile.h \
    ../Analib_include/readthread.h \
    ../Analib_include/DMFReader.h \
    ../Analib_include/EleTransWiding.h \
    ../Analib_include/EleGenerator.h \
    ../Analib_include/EleExciter.h \
    ../Analib_include/Markup.h \
    ../Analib_include/CnCodec.h
INCLUDEPATH += ../Analib_include/ ./

# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}
# ensure one "debug" or "release" in CONFIG so they can be used as
# conditionals instead of writing "CONFIG(debug, debug|release)"...
#CONFIG(debug, debug|release) {
#    CONFIG -= debug release
#    CONFIG += debug
#}
#CONFIG(release, debug|release) {
#    CONFIG -= debug release
#    CONFIG += release
#}

#UI_DIR += ../build/WYCmtdAna/
#MOC_DIR += ../build/WYCmtdAna/

CONFIG(debug, debug|release) {
DESTDIR = ../bin
OBJECTS_DIR = ../build/WYCmtdAna/debug/
}
else {
DESTDIR = ../publish
OBJECTS_DIR = ../build/WYCmtdAna/release/
}

MOC_DIR += ../build/
