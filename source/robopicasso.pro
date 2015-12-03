#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T12:46:39
#
#-------------------------------------------------

QT +=qml quick widgets gui

TARGET = genImages

CONFIG   += c++14

TEMPLATE = app

SOURCES += main.cpp \
    mypainter.cpp \
    geneticalgorithmprocessor.cpp \
    genalgobject.cpp \
    figure.cpp \
    QtJson/json.cpp \
    robopicassodesktopapp.cpp \
    bestresultimageprovider.cpp

HEADERS += \
    mypainter.h \
    geneticalgorithmprocessor.h \
    genalgobject.h \
    figure.h \
    QtJson/json.h \
    robopicassodesktopapp.h \
    bestresultimageprovider.h

RESOURCES += \
    qml.qrc \
    images.qrc
