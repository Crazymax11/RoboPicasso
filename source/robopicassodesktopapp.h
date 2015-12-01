#ifndef ROBOPICASSODESKTOPAPP_H
#define ROBOPICASSODESKTOPAPP_H

#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "geneticalgorithmprocessor.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QColor>
#include <QThread>
#include "bestresultimageprovider.h"
class RobopicassoDesktopApp : public QApplication
{
    Q_OBJECT
public:
    explicit RobopicassoDesktopApp(int & argc, char ** argv);
    enum status {
        IDLE,
        RUNNING,
        PAUSED,
        FINISHED
    };
signals:
    newBestValue(double value);
    newBestPopulationNumber(int num);

    finished();
public slots:
    void loadPopulationFromJSON(QString filepath);
    void savePopulationToJSON(QString filepath);
    void saveCurrentBestToJSON(QString filepath);
    void saveCurrentBestAsImage(QString filepath);
    void pause();
    void resume();
    void start();
private slots:
    void drawBest(double val);

    void setMinimalOpacity();

private:
    QQmlApplicationEngine engine;
    QObject* rootQML;
    GeneticAlgorithmProcessor* proc;
    QThread procThread;
    bestResultImageProvider imageProvider;
};
#endif // ROBOPICASSODESKTOPAPP_H
