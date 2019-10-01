QT       -= gui
QT += websockets

include(../common.pri)

TARGET = BaseWebSocketInput
TEMPLATE = lib
CONFIG -= plugin
CONFIG += static

DEFINES += BASEWEBSOCKETINPUT_LIBRARY

SOURCES += \
        basewebsocketinput.cpp

HEADERS += \
        basewebsocketinput.h \
        basewebsocketinput_global.h 

DESTDIR = $$OUT_PWD
