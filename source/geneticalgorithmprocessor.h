#ifndef GENETICALGORITHMPROCESSOR_H
#define GENETICALGORITHMPROCESSOR_H

#include <QImage>
#include "genalgobject.h"
#include <QObject>

class GeneticAlgorithmProcessor: public QObject
{
    Q_OBJECT
signals:
    newBestValue(double value);
    newBestPopulationNumber(int num);
    finished();
    startNewIteration();
    generationIndexIncreased(int index);
public slots:
    void start();
    void pause();
    void resume();
    void setPopulationSize(int newsize){
        populationSize=newsize;
        if (newsize < population.size())
            population = population.mid(0,newsize);
    }
    void setMutationChance(double newMutChance){mutationChance=newMutChance;}
    void setMutationAmount(double newMutAmount){mutationAmount=newMutAmount;}
    void setBestUntouchables(double newBestUntouchables){bestUntouchables=newBestUntouchables;}
    void setMinimalOpacity(double newMinOpacity){minOpacity=newMinOpacity;}
    void setGenerationsLimit(int newLimit){generationsLimit=newLimit;}
    void setMutationFigures(double newMutFigures){mutationFiguresNum=newMutFigures;}
    //работает перед стартом работы
    void setFiguresNum(int figures){
        if ((!isRunning)&&(generationIndex==0))
            this->figures=figures;
    }

    int getCurrentIndex(){return generationIndex;}
public:
    GeneticAlgorithmProcessor();
    QImage targetImage;


    QImage* bestImage;
    int width;
    int height;
    int maxSize;
    QString targetPath;

    QJsonArray getPopulationInJSON();
    QJsonObject getElementInJSON(int index);
    QList<GenAlgObject> population;
private slots:
    double FitnessFunction(GenAlgObject& obj);

    //разделено, после финиша посылается сигнал. Сигнал становится в очередь -> можно в очереди обрабатывать изменение параметров, паузу и тд и тп
    void startIteration();
    void finishIteration();

    void selection();
    void crossover();
    void mutation();

    Figure mutateFigure(const Figure &b);
    GenAlgObject mutateObject(const GenAlgObject &b);
    void sortPopulation();
    double mutateValue(double val, double minVal = 0);

    void increaseGenerationIndex();
private:
    int generationIndex;

    GenAlgObject generateRandomObject();
    bool compareObjects(GenAlgObject obj1, GenAlgObject obj2);
    bool isRunning;
    QImage* tempIm;

    // параметры
    int populationSize;
    double mutationChance;
    double mutationAmount; //от 0 до 1
    double mutationFiguresNum; // от 0 до 1
    // лучших не трогаем в процессе мутации
    int bestUntouchables;

    double minOpacity;
    int maxSizeKoef;
    int generationsLimit;
    double targetFitness;

    int figures;
    double bestResult;

    bool isPaused;

};

#endif // GENETICALGORITHMPROCESSOR_H
