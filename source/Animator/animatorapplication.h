#ifndef ANIMATORAPPLICATION_H
#define ANIMATORAPPLICATION_H

#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include "geneticAlgorithm/genalgobject.h"
#include "figures/mypainter.h"
#include <QProcess>
#include <QDateTime>
#include <QJsonDocument>
#include <QDebug>
class AnimatorApplication : public QApplication
{
    Q_OBJECT
public:
    AnimatorApplication(int & argc, char** argv);
private slots:
    void animate();
    QImage drawImage(int width, int height, const GenAlgObject& obj, QString text);
    bool saveImage(const QImage& image);
private:
    QObject* rootQML;
    QQmlApplicationEngine engine;
    int printed;
    QString destinationDir;
};

#endif // ANIMATORAPPLICATION_H
