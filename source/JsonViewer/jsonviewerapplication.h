#ifndef JSONVIEWERAPPLICATION_H
#define JSONVIEWERAPPLICATION_H

#include <QObject>
#include <QApplication>
#include "figures/figure.h"
#include "figures/mypainter.h"
#include <QUrl>
#include <QQmlApplicationEngine>
#include "myimageprovider.h"
#include <QJsonDocument>
#include <QFile>
#include <geneticAlgorithm/genalgobject.h>
class JsonViewerApplication : public QApplication
{
    Q_OBJECT
public:
    JsonViewerApplication(int& argc, char** argv);
private slots:
    void loadJson(QUrl jsonPath);
private:
    QObject* rootQML;
    QQmlApplicationEngine engine;
    MyImageProvider imageProvider;
};

#endif // JSONVIEWERAPPLICATION_H
