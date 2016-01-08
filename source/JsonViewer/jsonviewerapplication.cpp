#include "jsonviewerapplication.h"

JsonViewerApplication::JsonViewerApplication(int& argc, char** argv): QApplication(argc, argv){
    engine.addImageProvider("imageProvider", &imageProvider);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    rootQML = engine.rootObjects()[0];
    QObject::connect(rootQML,SIGNAL(jsonLoaded(QUrl)),
                     this,SLOT(loadJson(QUrl)));
}


void JsonViewerApplication::loadJson(QUrl jsonPath){
    QFile jsonFile(jsonPath.toLocalFile());
    jsonFile.open(QIODevice::ReadOnly);
    QByteArray data = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    GenAlgObject obj(doc.object());
    QImage temp(300,300,QImage::Format_ARGB32);
    obj.drawResult(&temp);
    imageProvider.image = temp;
    QVariant returnedValue;
    QMetaObject::invokeMethod(rootQML, "updateImage",
            Q_RETURN_ARG(QVariant, returnedValue));
    jsonFile.close();
}
