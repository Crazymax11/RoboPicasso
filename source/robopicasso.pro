#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T12:46:39
#
#-------------------------------------------------

QT +=qml quick widgets gui

TARGET = Robopicasso

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

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
