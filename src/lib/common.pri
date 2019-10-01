TEMPLATE = lib
CONFIG += plugin
CONFIG -= debug_and_release_target

DEFINES += QT_DEPRECATED_WARNINGS

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(../../scivi2core.pri)
