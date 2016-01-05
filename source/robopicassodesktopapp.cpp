#include "robopicassodesktopapp.h"

RobopicassoDesktopApp::RobopicassoDesktopApp(int & argc, char ** argv) : QApplication(argc, argv)
{

    engine.addImageProvider("imageProvider", &imageProvider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    rootQML = engine.rootObjects()[0];

    QObject::connect(rootQML,SIGNAL(start()),
                     this,SLOT(start()));
    saveAll = false;
    pathToSave = "results\\";
    if (!QDir(pathToSave).exists()){
        QDir dir;
        dir.mkdir(pathToSave);
    }
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

    QObject::connect(rootQML,SIGNAL(newMutationChance(double)),
                     proc,SLOT(setMutationChance(double)));
    QObject::connect(rootQML,SIGNAL(newMutationAmount(double)),
                     proc,SLOT(setMutationAmount(double)));
    QObject::connect(rootQML,SIGNAL(newMutationFigures(double)),
                     proc,SLOT(setMutationFigures(double)));

    QObject::connect(rootQML,SIGNAL(newMutationParametrsNum(int)),
                     proc,SLOT(setNumOfMutationParametrs(int)));

    QObject::connect(rootQML,SIGNAL(newMinimalOpacity(double)),
                     proc,SLOT(setMinimalOpacity(double)));

    QObject::connect(proc,SIGNAL(generationIndexIncreased(int)),
                     rootQML,SIGNAL(setGenerationIndex(int)));

    QObject::connect(rootQML,SIGNAL(shake(bool)),
                     proc,SLOT(shake(bool)));

    QObject::connect(rootQML, SIGNAL(setSaveAll(bool)),
                     this,SLOT(setSaveFlag(bool)));

    QObject::connect(rootQML, SIGNAL(saveCurrentBest()),
                     this, SLOT(saveBest()));

    QObject::connect(rootQML,SIGNAL(setSavePath(QUrl)),
                     this,SLOT(setSavePath(QUrl)));

    QObject::connect(rootQML,SIGNAL(setPopulationCrossoverKoef(int)),
                     proc,SLOT(setPopulationCrossoverKoef(int)));
    QObject::connect(rootQML,SIGNAL(setPopulationSelectionKoef(double)),
                     proc,SLOT(setPopulationSelectionKoef(double)));

    QObject::connect(rootQML,SIGNAL(setSmallShakeRange(double)),
                     proc,SLOT(setSmallShakeRange(double)));
    QObject::connect(rootQML,SIGNAL(setBigShakeRange(int)),
                     proc,SLOT(setBigShakeRange(int)));
    QObject::connect(rootQML,SIGNAL(setSmallShakeInterval(int)),
                     proc,SLOT(setSmallShakeInterval(int)));
    QObject::connect(rootQML,SIGNAL(setBigShakeInterval(int)),
                     proc,SLOT(setBigShakeInterval(int)));
    QObject::connect(rootQML,SIGNAL(setUntouchablesNum(int)),
                     proc,SLOT(setUntouchablesNum(int)));
    QObject::connect(rootQML,SIGNAL(setUntouchablesNum(int)),
                     proc,SLOT(setUntouchablesNum(int)));
    QObject::connect(rootQML,SIGNAL(setMitosNum(int)),
                     proc,SLOT(setMitosNum(int)));

    QObject::connect(rootQML,SIGNAL(setSaveAsJson(bool)),
                     this,SLOT(setSaveAsJsonFlag(bool)));

    QObject::connect(rootQML,SIGNAL(visualize()),
                     this,SLOT(visualize()));
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
    imageProvider.image.save(filepath);
//    QImage res = proc->bestImage->copy();
//    res.save(filepath);
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


void RobopicassoDesktopApp::setSaveAsJsonFlag(bool newval){
    saveAsJson = newval;
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
    proc->setMutationFigures(mutationFigures);
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
    if (saveAll)
        saveBest();
}

void RobopicassoDesktopApp::saveBest(){
    if (saveAsJson)
        saveCurrentBestToJSON(pathToSave + "\\" + rootQML->property("generationIndex").toString() + QString("-") + rootQML->property("bestResValue").toString() + QString(".JSON"));
    else
        saveCurrentBestAsImage(pathToSave + "\\" + rootQML->property("generationIndex").toString() + QString("-") + rootQML->property("bestResValue").toString() + QString(".png"));
    //imageProvider.image.save(pathToSave + "\\" + rootQML->property("generationIndex").toString() + QString("-") + rootQML->property("bestResValue").toString() + QString(".png"));
}


void RobopicassoDesktopApp::setMinimalOpacity(){
    double minimalOpacity = rootQML->property("minimalOpacity").toDouble();
    proc->setMinimalOpacity(minimalOpacity);
}

void RobopicassoDesktopApp::setSaveFlag(bool saveAll){
    this->saveAll=saveAll;
}

void RobopicassoDesktopApp::setSavePath(QUrl newpath){
    pathToSave = newpath.toLocalFile();
}


void RobopicassoDesktopApp::visualize(){
    QDir saveDir(pathToSave);
    QStringList nameFilters;
    nameFilters << QString("*.json");
    QStringList filelist = saveDir.entryList(nameFilters);
    //QMap сам сортирует по ключу вроде как
    QMap<int,GenAlgObject> map;
    foreach(QString file, filelist){
        int popNum = file.split("-")[0].toInt();
        QFile jsonFile(pathToSave+"\\" + file);
        jsonFile.open(QIODevice::ReadOnly);
        QByteArray data = jsonFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        map[popNum] = GenAlgObject(doc.object());
    }
    QMap<int,GenAlgObject>::iterator src = map.begin();
    QMap<int,GenAlgObject>::iterator dst = map.begin();
    dst++;

    QList<QImage*> frames;
    int transitionsFrames = 48;
    while(dst != map.end()){
        const GenAlgObject srcObject = src.value();
        const GenAlgObject dstObject = dst.value();
        for(int i=0;i<transitionsFrames;i++){
            GenAlgObject transObject(srcObject);
            for(int j=0;j<transObject.figureList.size();j++){
                double koef = double(i)/transitionsFrames;
                transObject.figureList[j].x += (dstObject.figureList[j].x - transObject.figureList[j].x)*koef;
                transObject.figureList[j].y += (dstObject.figureList[j].y - transObject.figureList[j].y)*koef;
                transObject.figureList[j].angle += (dstObject.figureList[j].angle - transObject.figureList[j].angle)*koef;
                transObject.figureList[j].opacity += (dstObject.figureList[j].opacity - transObject.figureList[j].opacity)*koef;
                transObject.figureList[j].radius += (dstObject.figureList[j].radius - transObject.figureList[j].radius)*koef;

                //после половины - тип dst
                transObject.figureList[j].type = (koef>= 0.5)? dstObject.figureList[j].type: transObject.figureList[j].type;

                int newRed = qRed(transObject.figureList[j].color) + (qRed(dstObject.figureList[j].color) - qRed(transObject.figureList[j].color))*koef;
                int newGreen = qGreen(transObject.figureList[j].color) + (qGreen(dstObject.figureList[j].color) - qGreen(transObject.figureList[j].color))*koef;
                int newBlue = qBlue(transObject.figureList[j].color) + (qBlue(dstObject.figureList[j].color) - qBlue(transObject.figureList[j].color))*koef;
                transObject.figureList[j].color = qRgb(newRed, newGreen, newBlue);
                //transObject.figureList[j].type += (transObject.figureList[j].x - dstObject.figureList[i].x)*(double(i)/transitionsFrames);
                //transObject.figureList[j].color += (transObject.figureList[j].x - dstObject.figureList[i].x)*(double(i)/transitionsFrames);
            }
            //заменить
            QImage* transResImage = new QImage(QSize(490, 274), QImage::Format_ARGB32);
            transObject.drawResult(transResImage);
            frames << transResImage;
        }
        src++;
        dst++;
    }
    for(int i=0;i<frames.size();i++){
        frames[i]->save("vis\\" + QString::number(i) + QString(".png"));
        delete frames[i];
    }
}
