QT       -= gui
QT += websockets

TARGET = Glove

DEFINES += GLOVE_LIBRARY

SOURCES += \
        glove.cpp

HEADERS += \
        glove.h \
        glove_global.h 

unix|win32: LIBS += -L$$OUT_PWD/../BaseWebSocketInput/ -lBaseWebSocketInput

INCLUDEPATH += $$PWD/../BaseWebSocketInput
DEPENDPATH += $$PWD/../BaseWebSocketInput

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../BaseWebSocketInput/BaseWebSocketInput.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../BaseWebSocketInput/libBaseWebSocketInput.a

include(../common.pri)
