#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T12:46:39
#
#-------------------------------------------------

QT       += core qml quick widgets gui

TARGET = genImages
CONFIG   += console
CONFIG   -= app_bundle



TEMPLATE = app


SOURCES += main.cpp \
    mypainter.cpp \
    geneticalgorithmprocessor.cpp \
    genalgobject.cpp \
    figure.cpp

HEADERS += \
    mypainter.h \
    geneticalgorithmprocessor.h \
    genalgobject.h \
    figure.h

RESOURCES += \
    qml.qrc
