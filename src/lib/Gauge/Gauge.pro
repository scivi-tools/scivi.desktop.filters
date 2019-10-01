QT += qml quick
QT       -= gui

TARGET = Gauge

DEFINES += GAUGE_LIBRARY

SOURCES += \
        gauge.cpp

HEADERS += \
        gauge.h \
        gauge_global.h 

RESOURCES += \
    res.qrc

include(../common.pri)
