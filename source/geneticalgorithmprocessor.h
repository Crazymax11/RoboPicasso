#ifndef GENETICALGORITHMPROCESSOR_H
#define GENETICALGORITHMPROCESSOR_H

#include <QImage>
#include "genalgobject.h"
#include <QObject>


//model: ["рулетка", "турнир", "каждый с каждым", "каждый с соседом", "каждый с обратным"]
enum crossoverType {
    ROULETTE,
    TOURNAMENT,
    EACH_WITH_EACH,
    EACH_WITH_NEIGHBORS,
    EACH_WITH_REVERSE

};


class GeneticAlgorithmProcessor: public QObject
{
    Q_OBJECT
signals:
    void newBestValue(double value);
    void newBestPopulationNumber(int num);
    void finished();
    void startNewIteration();
    void generationIndexIncreased(int index);
public slots:
    void start();
    void pause();
    void resume();

    void shake(bool isBig);

    void setPopulationSize(int newsize){
        populationSize=newsize;
        if (newsize < population.size())
            population = population.mid(0,newsize);
    }
    void setMutationChance(double newMutChance){mutationChance=newMutChance;}
    void setMutationAmount(double newMutAmount){mutationAmount=newMutAmount;}
    void setNumOfMutationParametrs(int newnum){numOfParametrsToMutate=newnum;}
    void setBestUntouchables(double newBestUntouchables){bestUntouchables=newBestUntouchables;}
    void setMinimalOpacity(double newMinOpacity){minOpacity=newMinOpacity;}
    void setGenerationsLimit(int newLimit){generationsLimit=newLimit;}
    void setMutationFigures(double newMutFigures){mutationFiguresNum=newMutFigures;}
    void setPopulationCrossoverKoef(int newk){crossoverPopulationK=newk;}
    void setPopulationSelectionKoef(double newk){selectionPopulationK=newk;}
    void setSmallShakeRange(double newrange){smallShakeRange=newrange;}
    void setBigShakeRange(int newrange){bigShakeRange=newrange;}
    void setSmallShakeInterval(int newInterval){smallShakeInterval=newInterval;}
    void setBigShakeInterval(int newInterval){bigShakeInterval=newInterval;}
    void setUntouchablesNum(int newval){bestUntouchables = newval;}
    void setMitosNum(int newval){mitosNum=newval;}
    //работает перед стартом работы
    void setFiguresNum(int figures){
        if ((!isRunning)&&(generationIndex==0))
            this->figures=figures;
    }

    void setCrossoverType(crossoverType newtype){
        m_crossoverType = newtype;
    }

    int getCurrentIndex(){return generationIndex;}
public:
    GeneticAlgorithmProcessor();
    QImage targetImage;


    QImage* bestImage;
    int width;
    int height;
    double maxSize;
    QString targetPath;

    QJsonArray getPopulationInJSON();
    QJsonObject getElementInJSON(int index);
    QList<GenAlgObject> population;

    GenAlgObject _bestObject;
private slots:
    double FitnessFunction(GenAlgObject& obj);

    //разделено, после финиша посылается сигнал. Сигнал становится в очередь -> можно в очереди обрабатывать изменение параметров, паузу и тд и тп
    void startIteration();
    void finishIteration();

    void selection();
    void crossover();
    void mutation();

    //встряска, оставляет топ range, остальных заменяет на рандом
    void shakePopulation(double range);
    void shakePopulation(int range);

    Figure mutateFigure(const Figure &b);
    GenAlgObject mutateObject(const GenAlgObject &b);
    void sortPopulation();
    double mutateValue(double val, double minVal = 0);

    void increaseGenerationIndex();

    int findWeakestFigure(const GenAlgObject& b);
    Figure& getWeakesFigure(GenAlgObject& b);
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
    int numOfParametrsToMutate; //0-5
    // лучших не трогаем в процессе мутации
    int bestUntouchables;

    double minOpacity;
    int maxSizeKoef;
    int generationsLimit;
    double targetFitness;

    int figures;
    double bestResult;

    bool isPaused;
    int bestResultIndex;
    int indexOfLastShake;


    int nextSmallShakeIndex;
    int nextBigShakeIndex;
    int bigShakeInterval;
    int smallShakeInterval;
    int bigShakeRange;
    double smallShakeRange;
    int mitosNum=0;
    int crossoverPopulationK;
    double selectionPopulationK;

    crossoverType m_crossoverType;
};

#endif // GENETICALGORITHMPROCESSOR_H
