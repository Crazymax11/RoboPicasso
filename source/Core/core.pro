include( ../../common.pri)
include(core.pri)

QT += gui

TARGET = robopicassoCore$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += c++11
DEFINES += ROBOPICASSOCORE_LIBRARY

SOURCES += figures/figure.cpp \
    figures/mypainter.cpp \
    geneticAlgorithm/genalgobject.cpp \
    geneticAlgorithm/geneticalgorithmprocessor.cpp \

HEADERS += figures/figure.h \
    figures/mypainter.h \
    geneticAlgorithm/genalgobject.h \
    geneticAlgorithm/geneticalgorithmprocessor.h \
    corelib.h

win32 {
    QMAKE_TARGET_PRODUCT = Subtitler Lib
    QMAKE_TARGET_DESCRIPTION = Library for subtitler applications
}
