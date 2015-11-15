#ifndef GENETICALGORITHMPROCESSOR_H
#define GENETICALGORITHMPROCESSOR_H

#include <QImage>
#include "genalgobject.h"
#include <QObject>

class GeneticAlgorithmProcessor: QObject
{
    Q_OBJECT
signals:
    newBestValue(double value);
    newBestPopulationNumber(int num);
    finished();
public slots:
    void start();
public:
    GeneticAlgorithmProcessor();
    QImage targetImage;

    // параметры
    int populationSize;
    double mutationChance;
    double mutationAmount; //от 0 до 1
    // лучших не трогаем в процессе мутации
    int bestUntouchables;

    double minOpacity;
    int maxSizeKoef;
    int generationsLimit;
    double targetFitness;

    int figures;
    double bestResult;
    QImage* bestImage;
    int width;
    int height;
    int maxSize;
    QString targetPath;
private:

    double FitnessFunction(GenAlgObject& obj);
    void selection();
    void crossover();
    void mutation();
    Figure mutateFigure(const Figure &b);
    GenAlgObject mutateObject(const GenAlgObject &b);
    void sortPopulation();
    QList<GenAlgObject> population;
    int generationIndex;

    GenAlgObject generateRandomObject();
    bool compareObjects(GenAlgObject obj1, GenAlgObject obj2);

    QImage* tempIm;
    double mutateValue(double val, double minVal = 0);
};

#endif // GENETICALGORITHMPROCESSOR_H
