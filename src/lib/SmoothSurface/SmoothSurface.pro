QT       += gui

TARGET = SmoothSurface

DEFINES += SMOOTHSURFACE_LIBRARY
DEFINES += _USE_MATH_DEFINES


!exists("$$PWD/sleek-surface/surface.cpp") {
    error("Coudn't find sleek-surface lib. Run git submodule update --init inside project root directory")
}

SOURCES += \
        smoothsurface.cpp \
        sleek-surface/surface.cpp \
        sleek-surface/curve.cpp \
        sleek-surface/common.cpp

HEADERS += \
        smoothsurface.h \
        smoothsurface_global.h \ 
        sleek-surface/surface.h \
        sleek-surface/curve.h \
        sleek-surface/common.h

DISTFILES += \
    sleek-surface/LICENSE

include(../common.pri)
