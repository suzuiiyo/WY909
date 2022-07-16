QT -= gui
QT += sql xml

CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = waveComparee
CONFIG(debug, debug|release) {
DESTDIR = ../bin
LIBS += -L../bin -lWYCmtdAna -lRMYSQLDAO -lHistoryDAO
OBJECTS_DIR = ../build/waveCompare/debug/
}
else {
DESTDIR = ../publish
LIBS += -L../publish -lWYCmtdAna -lRMYSQLDAO -lHistoryDAO
OBJECTS_DIR = ../build/waveCompare/release/
}

MOC_DIR += ../build/waveCompare/


INCLUDEPATH += . \
    ../Analib_include \
    ../HistoryDAO \
    ../RMYSQLDAO \

HEADERS += \
    calparameter.h \
    chanelparadao.h \
    compareresult.h \
    hdrReader.h \
    loadcomtrade.h \
    parsefilename.h \
    reportWriter.h \
    writeresultdao.h \
    resultintodb.h \
    recognizecomtradefile.h \
    comparealgorithm.h \
    caleffectivevalue.h

SOURCES += \
        calparameter.cpp \
        chanelparadao.cpp \
        compareresult.cpp \
        hdrReader.cpp \
        loadcomtrade.cpp \
        main.cpp \
        parsefilename.cpp \
        reportWriter.cpp \
        writeresultdao.cpp \
        resultintodb.cpp \
        recognizecomtradefile.cpp \
        comparealgorithm.cpp \
        caleffectivevalue.cpp \

