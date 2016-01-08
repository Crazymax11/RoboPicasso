#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T12:46:39
#
#-------------------------------------------------
# Default rules for deployment.
include( ../../common.pri)
include( Animator.pri)
QT +=qml quick widgets gui

TARGET = RobopicassoAnimator

CONFIG   += c++14

TEMPLATE = app

LIBS += -lrobopicassoCore$${LIB_SUFFIX}1


SOURCES += main.cpp \ 
    animatorapplication.cpp

HEADERS += \
    animatorapplication.h

RESOURCES += \
    qml.qrc
