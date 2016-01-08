#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T12:46:39
#
#-------------------------------------------------
# Default rules for deployment.
include( ../../common.pri)
include( RobopicassoApplication.pri)
QT +=qml quick widgets gui

TARGET = Robopicasso

CONFIG   += c++14

TEMPLATE = app

LIBS += -lrobopicassoCore$${LIB_SUFFIX}1

SOURCES += main.cpp \
    robopicassodesktopapp.cpp \
    bestresultimageprovider.cpp

HEADERS += \
    robopicassodesktopapp.h \
    bestresultimageprovider.h

RESOURCES += \
    qml.qrc \
    images.qrc
