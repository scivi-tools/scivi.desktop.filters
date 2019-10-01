QT       += gui quick datavisualization

TARGET = Surface3D

DEFINES += SURFACE3D_LIBRARY

SOURCES += \
        surface3d.cpp \
    surfacedatamodel.cpp

HEADERS += \
        surface3d.h \
        surface3d_global.h \ 
    surfacedatamodel.h

DISTFILES += \
    Surface3D.qml

RESOURCES += \
    res.qrc

include(../common.pri)
