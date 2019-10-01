QT       += gui

TARGET = Mouse

DEFINES += MOUSE_LIBRARY

SOURCES += \
        mouse.cpp

HEADERS += \
        mouse.h \
        mouse_global.h

mac: LIBS += -framework CoreGraphics -framework CoreFoundation

include(../common.pri)
