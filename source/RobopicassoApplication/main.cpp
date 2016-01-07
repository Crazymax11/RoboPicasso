#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include "figures/mypainter.h"
#include "geneticAlgorithm/genalgobject.h"
#include "geneticAlgorithm/geneticalgorithmprocessor.h"
#include <QTime>
#include <QCommandLineParser>
#include <QFile>
#include <QDir>
#include <QQmlApplicationEngine>
#include "robopicassodesktopapp.h"
int main(int argc, char *argv[])
{
    RobopicassoDesktopApp app(argc, argv);

    return app.exec();
}
