#include "robopicassodesktopapp.h"

RobopicassoDesktopApp::RobopicassoDesktopApp(int & argc, char ** argv) : QApplication(argc, argv)
{
    engine.addImageProvider("imageProvider", &imageProvider);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    rootQML = engine.rootObjects()[0];

    QObject::connect(rootQML,SIGNAL(start()),
                     this,SLOT(start()));


    proc = new GeneticAlgorithmProcessor();

    //procThread.setPriority(QThread::LowPriority);
    proc->moveToThread(&procThread);
    QObject::connect(&procThread,SIGNAL(started()),
                     proc,SLOT(start()));
    QObject::connect(rootQML,SIGNAL(pause()),
                     proc,SLOT(pause()));
    QObject::connect(rootQML,SIGNAL(resume()),
                     proc,SLOT(resume()));

    QObject::connect(proc,SIGNAL(newBestValue(double)),
                     this,SLOT(drawBest(double)));
}
void RobopicassoDesktopApp::savePopulationToJSON(QString filepath){
    QJsonArray result = proc->getPopulationInJSON();
    QFile file(filepath);
    file.open(QIODevice::WriteOnly);
    QJsonDocument doc(result);
    file.write(doc.toJson());
    file.close();
}

void RobopicassoDesktopApp::saveCurrentBestAsImage(QString filepath){
    QImage res = proc->bestImage->copy();
    res.save(filepath);
}

void RobopicassoDesktopApp::saveCurrentBestToJSON(QString filepath){
    QFile file(filepath);
    file.open(QIODevice::WriteOnly);
    QJsonDocument doc(proc->getElementInJSON(0));
    file.write(doc.toJson());
    file.close();
}

void RobopicassoDesktopApp::pause(){

}
void RobopicassoDesktopApp::resume(){

}

void RobopicassoDesktopApp::loadPopulationFromJSON(QString filepath){

}

void RobopicassoDesktopApp::start(){
    double mutChance = rootQML->property("mutationChance").toDouble();
    double mutAmount = rootQML->property("mutationAmount").toDouble();
    double mutationFigures = rootQML->property("mutationFigures").toDouble();
    double minimalOpacity = rootQML->property("minimalOpacity").toDouble();
    int populationNum = rootQML->property("populationNum").toInt();
    int figuresNum = rootQML->property("figuresNum").toInt();
    QString tarImage = rootQML->property("tarImage").toUrl().toLocalFile();

    proc->setMutationChance(mutChance);
    proc->setMutationAmount(mutAmount);
    proc->setMinimalOpacity(minimalOpacity);
    proc->setFiguresNum(figuresNum);
    proc->setPopulationSize(populationNum);
    proc->setMutationAmount(mutAmount);
    proc->targetImage.load(tarImage);


    procThread.start();
}


void RobopicassoDesktopApp::drawBest(double val){

    QImage temp(proc->targetImage);
    temp.fill(QColor(255,255,255));
    proc->population[0].drawResult(&temp);
    imageProvider.image = temp;
    QVariant returnedValue;
    QMetaObject::invokeMethod(rootQML, "updateImage",
            Q_RETURN_ARG(QVariant, returnedValue));
    rootQML->setProperty("bestResValue",val);
}