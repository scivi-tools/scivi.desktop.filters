QT       += qml quick
QT       -= gui

TARGET = HorizontalStack

DEFINES += HORIZONTALSTACK_LIBRARY

SOURCES += \
        horizontalstack.cpp

HEADERS += \
        horizontalstack.h \
        horizontalstack_global.h 

RESOURCES += \
    res.qrc

include(../common.pri)
