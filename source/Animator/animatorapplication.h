#ifndef ANIMATORAPPLICATION_H
#define ANIMATORAPPLICATION_H

#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>
class AnimatorApplication : public QApplication
{
    Q_OBJECT
public:
    AnimatorApplication(int & argc, char** argv);
private:
    QObject* rootQML;
    QQmlApplicationEngine engine;
};

#endif // ANIMATORAPPLICATION_H
