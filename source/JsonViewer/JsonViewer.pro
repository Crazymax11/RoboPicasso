# Default rules for deployment.
include(../../common.pri)
include(JsonViewer.pri)


QT += qml quick widgets gui

CONFIG += c++14

HEADERS += \
    jsonviewerapplication.h \
    myimageprovider.h
SOURCES += main.cpp \
    jsonviewerapplication.cpp \
    myimageprovider.cpp

RESOURCES += qml.qrc

TEMPLATE = app
TARGET = JsonViewer
LIBS += -lrobopicassoCore$${LIB_SUFFIX}1



