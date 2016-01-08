#include "animatorapplication.h"

AnimatorApplication::AnimatorApplication(int &argc, char** argv): QApplication(argc, argv){
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    rootQML = engine.rootObjects()[0];
    QObject::connect(rootQML,SIGNAL(start()),
                     this,SLOT(animate()));
}


void AnimatorApplication::animate(){

    printed = 0;
    QDir sourceDir(rootQML->property("sourceDirectory").toUrl().toLocalFile());
    destinationDir = rootQML->property("destinationDirectory").toUrl().toLocalFile();
    QString pathToSave(destinationDir);
    QDir saveDir(sourceDir);
    QStringList nameFilters;
    nameFilters << QString("*.json");
    QStringList filelist = saveDir.entryList(nameFilters);
    //QMap сам сортирует по ключу вроде как
    QMap<int,GenAlgObject> map;
    QMap<int,double> fitnessMap;
    foreach(QString file, filelist){
        int popNum = file.split("-")[0].toInt();
        QFile jsonFile(sourceDir.absolutePath()+"\\" + file);
        jsonFile.open(QIODevice::ReadOnly);
        QByteArray data = jsonFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        map[popNum] = GenAlgObject(doc.object());
        fitnessMap[popNum] = file.split("-")[1].toDouble();
    }
    QMap<int,GenAlgObject>::iterator src = map.begin();
    QMap<int,GenAlgObject>::iterator dst = map.begin();
    dst++;

    QList<QImage*> frames;
    QList<QImage*> imagesToDelete;
    int fps = 30;
    double originalSeconds = rootQML->property("originalSecondsVal").toDouble();
    double transitionSeconds = rootQML->property("transitionSecondsVal").toDouble();
    double generationSeconds = rootQML->property("generationSecondsVal").toDouble();

    QPainter textDrower;

    QImage original(sourceDir.absoluteFilePath("original.png"));
    for(int i=0;i<fps*originalSeconds;i++){
        saveImage(original);
    }

    while(dst != map.end()){
        const GenAlgObject srcObject = src.value();
        const GenAlgObject dstObject = dst.value();

        QImage generationImage = drawImage(original.width(),original.height(),src.value(),QString::number(src.key()));
        for(int i=0;i<generationSeconds*fps;i++){
            saveImage(generationImage);
        }

        for(int i=0;i<transitionSeconds*fps;i++){
            GenAlgObject transObject(srcObject);
            for(int j=0;j<transObject.figureList.size();j++){
                double koef = double(i)/(transitionSeconds*fps);
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
            QString transText = QString::number(src.key()) + " --> " + QString::number(dst.key());
            saveImage(drawImage(original.width(),original.height(),transObject,transText));
        }
        src++;
        dst++;
    }

    QImage lastImage = drawImage(original.width(),original.height(),src.value(),QString::number(src.key()));
    for(int i=0;i<generationSeconds*fps;i++){
        saveImage(lastImage);
    }
    QString ffmpegPath = rootQML->property("ffmpegPath").toUrl().toLocalFile();

    QProcess ffmpegProcess;
    ffmpegProcess.setProgram(ffmpegPath);

    QStringList args;
    args << "-f" << "image2" << "-i" << destinationDir + "\/%%d.png" << destinationDir + "\/" + QDateTime::currentDateTime().toString(Qt::ISODate)+".avi";
    ffmpegProcess.setArguments(args);

    ffmpegProcess.start();
    ffmpegProcess.waitForFinished();

    qDebug() << ffmpegProcess.readAllStandardError();
    for(int i=0;i<imagesToDelete.size();i++)
        delete imagesToDelete[i];
}


QImage AnimatorApplication::drawImage(int width, int height, const GenAlgObject& obj, QString text){
    QImage result(width,height,QImage::Format_ARGB32);
    GenAlgObject copy(obj);
    copy.drawResult(&result);
    QPainter textDrower(&result);

    textDrower.drawText(width/3, height-10, text);
    textDrower.end();
    return result;
}

bool AnimatorApplication::saveImage(const QImage& image){
    image.save(destinationDir + "\\" + QString::number(printed++) + QString(".png"));
}
