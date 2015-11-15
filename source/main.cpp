#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include "mypainter.h"
#include "genalgobject.h"
#include "geneticalgorithmprocessor.h"
#include <QTime>
#include <QCommandLineParser>
#include <QFile>
#include <QDir>
#include <QQmlApplicationEngine>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


//    QCommandLineParser parser;
//        parser.setApplicationDescription(QCoreApplication::translate("main",
//        "Genetic Alg"));
//    parser.addHelpOption();
//    parser.addVersionOption();


//    QCommandLineOption pathToSave(QStringList() << "p" << "pathToSave", QCoreApplication::translate("main", "папка для сохранения результатов"), "path", ".");
//    QCommandLineOption mutationChance(QStringList() << "m" << "mutationChance", QCoreApplication::translate("main", "шанс мутирования"), "mutChance", "0.2");
//    QCommandLineOption mutationAmount(QStringList() << "M" << "mutationAmount", QCoreApplication::translate("main", "величина мутации"), "muAmount", "0.1");
//    QCommandLineOption minOpacity(QStringList() << "o" << "minOpacity", QCoreApplication::translate("main", "Минимальная видимость"), "minOpcaity", "0.3");
//    QCommandLineOption maxSizeKoef(QStringList() << "s" << "maxSizeKoef", QCoreApplication::translate("main", "maxsize"), "maxSIze", "2");
//    QCommandLineOption popSize(QStringList() << "g" <<"popSize", QCoreApplication::translate("main", "Размер популяции"), "popSize", "40");
//    QCommandLineOption bestUntouch(QStringList() << "u" <<"bestUntouch", QCoreApplication::translate("main", "Неприкасаемые при мутации"), "untouch", "2");
//    QCommandLineOption generationsLimit(QStringList() << "l" <<"generationsLimit", QCoreApplication::translate("main", "Лимит поколений"), "genLim", "10000");
//    QCommandLineOption figures(QStringList() << "f" <<"figures", QCoreApplication::translate("main", "количество фигур"), "num", "40");
//    QCommandLineOption image(QStringList() << "i" <<"image", QCoreApplication::translate("main", "изображение которому будем подражать"), "image", ".");

//    parser.addOption(pathToSave);
//    parser.addOption(mutationChance);
//    parser.addOption(mutationAmount);
//    parser.addOption(minOpacity);
//    parser.addOption(maxSizeKoef);
//    parser.addOption(popSize);
//    parser.addOption(bestUntouch);
//    parser.addOption(generationsLimit);
//    parser.addOption(figures);
//    parser.addOption(image);
//    parser.process(a);


//    GeneticAlgorithmProcessor proc;
//    QString dirToSave = parser.value("pathToSave");
//    dirToSave += QString("\\") + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

//    QDir().mkdir(dirToSave);
//    QFile f(dirToSave + QString("\\metaInfo"));
//    f.open(QIODevice::WriteOnly);
//    f.write( (QString("started at ") +QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).toUtf8());
//    f.write( (QString("\npopulation size =") +parser.value("popSize")).toUtf8());
//    f.write( (QString("\nmutation chance =") +parser.value("mutationChance")).toUtf8());
//    f.write( (QString("\nmutation amount =") +parser.value("mutationAmount")).toUtf8());
//    f.write( (QString("\nmin Opacity =") +parser.value("minOpacity")).toUtf8());
//    f.write( (QString("\nbestUntouch =") +parser.value("bestUntouch")).toUtf8());
//    f.write( (QString("\ngenerationsLimit =") +parser.value("generationsLimit")).toUtf8());
//    f.write( (QString("\nfigures =") +parser.value("figures")).toUtf8());
//    f.write( (QString("\nimage =") +parser.value("image")).toUtf8());
//    f.flush();
//    proc.targetPath = dirToSave;
//    proc.populationSize = parser.value("popSize").toInt();
//    proc.mutationChance = parser.value("mutationChance").toFloat();
//    proc.mutationAmount = parser.value("mutationAmount").toFloat();
//    proc.minOpacity = parser.value("minOpacity").toFloat();
//    proc.maxSizeKoef = parser.value("maxSizeKoef").toInt();
//    proc.bestUntouchables = parser.value("bestUntouch").toInt();
//    proc.generationsLimit = parser.value("generationsLimit").toInt();
//    proc.figures = parser.value("figures").toInt();
//    proc.targetImage = QImage(parser.value("image"));
//    proc.start();

//    f.write( (QString("finished at ") +QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).toUtf8());
//    f.close();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
