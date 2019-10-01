QT       -= gui
QT += websockets

TARGET = WebSocketInput

DEFINES += WEBSOCKETINPUT_LIBRARY

SOURCES += \
        websocketinput.cpp

HEADERS += \
        websocketinput.h \
        websocketinput_global.h 

unix|win32: LIBS += -L$$OUT_PWD/../BaseWebSocketInput/ -lBaseWebSocketInput

INCLUDEPATH += $$PWD/../BaseWebSocketInput
DEPENDPATH += $$PWD/../BaseWebSocketInput

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../BaseWebSocketInput/BaseWebSocketInput.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../BaseWebSocketInput/libBaseWebSocketInput.a

include(../common.pri)
