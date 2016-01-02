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
#include <QDir>
#include <QFile>
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
    void newBestValue(double value);
    void newBestPopulationNumber(int num);

    void finished();
public slots:
    void loadPopulationFromJSON(QString filepath);
    void savePopulationToJSON(QString filepath);
    void saveCurrentBestToJSON(QString filepath);
    void saveCurrentBestAsImage(QString filepath);
    void pause();
    void resume();
    void start();


    void setSaveFlag(bool saveAll);
    void setSavePath(QUrl newpath);

private slots:
    void drawBest(double val);
    void saveBest();

    void setMinimalOpacity();

    void setSaveAsJsonFlag(bool newval);
private:
    bool saveAll;
    bool saveAsJson = false;
    QString pathToSave;
    QQmlApplicationEngine engine;
    QObject* rootQML;
    GeneticAlgorithmProcessor* proc;
    QThread procThread;
    bestResultImageProvider imageProvider;
};
#endif // ROBOPICASSODESKTOPAPP_H
