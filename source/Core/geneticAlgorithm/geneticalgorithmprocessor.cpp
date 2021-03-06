#include "geneticalgorithmprocessor.h"
#include <QDebug>
#include <QColor>
#include "math.h"
#include "figures/mypainter.h"
GeneticAlgorithmProcessor::GeneticAlgorithmProcessor(): QObject()
{
    populationSize = 120;
    mutationChance = 0.1;
    // лучших не трогаем в процессе мутации
    bestUntouchables = 2;

    generationsLimit = 100000;
    targetFitness = 0.98;

    figures = 40;
    targetPath = ".";
    isRunning = false;
    isPaused = false;
    generationIndex = 0;
    bestResultIndex=0;
    nextSmallShakeIndex = -1;
    nextBigShakeIndex = -1;

    crossoverPopulationK = 4;
    selectionPopulationK = 0.7;
    numOfParametrsToMutate = 1;
    bigShakeRange = 1;
    smallShakeRange = 0.2;
    smallShakeInterval = 5;
    bigShakeInterval = 100;

    m_crossoverType = crossoverType::ROULETTE;
    QObject::connect(this,SIGNAL(startNewIteration()),
                     this,SLOT(startIteration()),Qt::QueuedConnection);
}


void GeneticAlgorithmProcessor::start()
{
    isRunning = true;
    width = targetImage.width();
    height = targetImage.height();
    maxSize = width>height? height: width;
    //задолбали огромные фигуры :С перекрывают все
    //нужно сделать настройку
    maxSize = double(1)/8;

    tempIm = new QImage(width,height,QImage::Format_ARGB32);

    //генерируем первое поколение
    for(int i=0;i<populationSize;i++)
    {
        population.append(generateRandomObject());
        population[i].index = i;
    }
    bestResult = qInf();
    generationIndex = 0;
    indexOfLastShake = 0;
    QImage res(targetImage.width(), targetImage.height(), QImage::Format_ARGB32);
    emit(startNewIteration());
}

GenAlgObject GeneticAlgorithmProcessor::generateRandomObject()
{
    GenAlgObject result(width, height);
    for(int i =0;i<figures; i++)
    {
        Figure figure;
        figure = figure.createRandomFigure(this->minOpacity, this->maxSize);
        result.figureList.append(figure);
    }
    return result;
}

void GeneticAlgorithmProcessor::selection()
{
    //возьмем топ selectionPopulationK, и остальных рандомно добавим
    population = population.mid(0,populationSize*selectionPopulationK);
    // счастливчики
    while(population.size()<populationSize)
        population.append(generateRandomObject());
}

void GeneticAlgorithmProcessor::crossover()
{
    //QList<GenAlgObject> tempList;
    //скрещиваются рандомные 2 особи добирая популяцию до crossoverPopulationK

    //расширяем не менее указанного предела
    int populationSizeAtStart = population.size();

    while(population.size()<populationSizeAtStart*crossoverPopulationK){
        switch (m_crossoverType){
        case crossoverType::ROULETTE:
            for(int i=0;i<populationSize*crossoverPopulationK;i++)
                population.append(GenAlgObject(population[qrand()%populationSize],population[qrand()%populationSize]));
            break;
        case crossoverType::TOURNAMENT:
            // перед тем как сделать нужно переделать 1. метод оценки, чем лучше тем больше фитнес
            // 2. переоценка объекта только если изменилась фигура объекта
            // 3. при изменении фигуры пересчитывать только те пиксели, которые затронуты измененными фигурами
            break;
        case crossoverType::EACH_WITH_EACH:
            for(int i=0;i<populationSizeAtStart;i++){
                for(int j=i+1;j<populationSizeAtStart;j++){
                    population.append(GenAlgObject(population[i],population[j]));
                }
            }
            break;
        case crossoverType::EACH_WITH_NEIGHBORS:
            for(int i=0;i<populationSizeAtStart;i++){
                population.append(GenAlgObject(population[i],population[(i-1+populationSizeAtStart)%populationSizeAtStart]));
                population.append(GenAlgObject(population[i],population[(i-1+populationSizeAtStart)%populationSizeAtStart]));
            }
            break;
        case crossoverType::EACH_WITH_REVERSE:
            for(int i=0;i<populationSizeAtStart;i++){
                population.append(GenAlgObject(population[i], population[populationSizeAtStart-1-i]));
            }
            break;
        }
    }





//    for(int i=0;i<population.size()-1;i+=2)
//        tempList.append(GenAlgObject(population[i], population[i+1]));
    //первые 3 особей самые крутые, мутируем их по 3 раз
//    for(int i=0;i<3;i++)
//        for(int j=0;j<3;j++)
//            tempList.append(mutateObject(population[i]));
//    //добавим 5 рандомных объектов
//    for(int i=0;i<10;i++)
//        tempList.append(generateRandomObject());
//    for(int i=0;i<tempList.size();i++)
//        population.append(tempList[i]);
}

void GeneticAlgorithmProcessor::mutation()
{
    //первые n пожалуй не будем мутировать
    for(int i = bestUntouchables;i<population.size(); i++){
        double randVal = double(qrand()%100)/100;
        if (randVal < mutationChance)
            population[i] = mutateObject(population[i]);
    }
    //мутейтим лучших не удаляя их
//    for(int i=0;i<bestUntouchables;i++){
//        population.append(mutateObject(population[i]));
//    }

}

void GeneticAlgorithmProcessor::mitosis(){
    //делаем по 1 копии
    for(int i=0;i<mitosNum;i++){
        //временный код
        // в митозе мутируем ТОЛЬКО слабейшую фигуру
        int weakestFigureIndex = findWeakestFigure(population[i]);
        GenAlgObject mitozed(population[i]);
        mitozed.figureList[weakestFigureIndex] = mutateFigure(population[i].figureList[weakestFigureIndex]);
        population.append(mitozed);
        //population[i].figureList[weakestFigureIndex] = mutateFigure(population[i].figureList[weakestFigureIndex]);
    }
}

double GeneticAlgorithmProcessor::FitnessFunction(GenAlgObject& obj1)
{
    double result = 0;
    //obj1.drawResult();
    MyPainter mypainter;
    //tempIm->fill(QColor(255,255,255));
    obj1.drawResult(tempIm);
    const QImage* res;
    res = tempIm;
    for(int i = 0;i<targetImage.width();i++)
        for(int j =0;j<targetImage.height();j++){

            //\Delta E_{ab}^* = \sqrt{ (L^*_2-L^*_1)^2+(a^*_2-a^*_1)^2 + (b^*_2-b^*_1)^2 }
            //\Delta E_{94}^* = \sqrt{ \left(\frac{L^*_2-L^*_1}{K_L}\right)^2 + \left(\frac{C^*_2-C^*_1}{1+K_1 C^*_1}\right)^2 + \left(\frac{h_2-h_1}{1+K_2 C^*_1}\right)^2 }
            QColor sourcePixel(targetImage.pixel(i,j));
            QColor objPixel(res->pixel(i,j));

            double kl = 2;
            double k1 = 0.048;
            double k2 = 0.014;
            //result += sqrt(pow(double(sourcePixel.red() - objPixel.red())/kl,2) + pow(double(sourcePixel.blue() - objPixel.blue())/(1+k1*objPixel.blue()),2) + pow(double(sourcePixel.green() - objPixel.green())/(1+ k2*objPixel.blue()),2) );

//            result += sqrt((sourcePixel.red() - objPixel.red())*(sourcePixel.red() - objPixel.red()) +
//                           (sourcePixel.blue() - objPixel.blue())*(sourcePixel.blue() - objPixel.blue()) +
//                           (sourcePixel.green() - objPixel.green())*(sourcePixel.green() - objPixel.green()));

//            result += (sourcePixel.red() - objPixel.red())*(sourcePixel.red() - objPixel.red()) +
//                           (sourcePixel.blue() - objPixel.blue())*(sourcePixel.blue() - objPixel.blue()) +
//                           (sourcePixel.green() - objPixel.green())*(sourcePixel.green() - objPixel.green());

              result += double(qAbs(sourcePixel.red() - objPixel.red()) +  qAbs(sourcePixel.blue() - objPixel.blue()) + qAbs(sourcePixel.green() - objPixel.green()) );
        }

    double maxDiff = double(targetImage.height()) * targetImage.width() * 255*255*255;
    //result = result/ maxDiff;
    obj1.res=result;
    return result;

}

bool GeneticAlgorithmProcessor::compareObjects(GenAlgObject obj1, GenAlgObject obj2)
{
    double res1 = FitnessFunction(obj1);
    double res2 = FitnessFunction(obj2);
    return res1 < res2;
}

void GeneticAlgorithmProcessor::sortPopulation()
{
    for(int i=0;i<population.size();i++)
    {
        FitnessFunction(population[i]);
    }
    std::sort(population.begin(),population.end());
}

double GeneticAlgorithmProcessor::mutateValue(double val, double minVal){
    //далаем все мутации цилкичными. 1.01 => 0.01
    int mVal = minVal*1000;
    int oldVal = val*1000;
    //зарандомить надо +- mutationAmount от 1000
    int diff = rand()%int(2*1000*mutationAmount) - int(1000*mutationAmount);
    // % делаем по возможному интервалу, т.е. если mVal 380, максимум val на самом деле не 1000 а 620
    int newVal = mVal + (oldVal - mVal + diff +(1000-mVal))%(1000-mVal);
    double newRes = double(newVal)/1000;
    return newRes;
}

Figure GeneticAlgorithmProcessor::mutateFigure(const Figure &b){
    Figure result(b);
    QStringList mutationParametrs;
    mutationParametrs << "type" << "position" << "size" << "color" << "angle" << "opacity";
    QList<int> mutPars;
    mutPars << 0 << 1 << 2 << 3 << 4 << 5;

    QRgb clr = result.color;
    for(int i=0;i<numOfParametrsToMutate;i++){
        int par = qrand()%mutPars.size();
        switch(mutPars[par]){
        case 0:
            result.type =  static_cast<FigureTypes>(qrand()%3);
            break;
        case 1:
            result.x = mutateValue(result.x);
            result.y = mutateValue(result.y);
            break;
        case 2:
            //приведем обратно
            result.radius = mutateValue(result.radius*12)/12;
            break;
        case 3:
            int newred;
            int newgreen;
            int newblue;
            newred = mutateValue(double(qRed(clr))/255)*255;
            newgreen = mutateValue(double(qGreen(clr))/255)*255;
            newblue = mutateValue(double(qBlue(clr))/255)*255;
            result.color = QColor(newred,newgreen,newblue).rgb();
            break;
        case 4:
            result.angle = mutateValue(result.angle);
            break;
        case 5:
            result.opacity = mutateValue(result.opacity, minOpacity);
        }
        mutPars.removeAt(par);
    }
    return result;
}
GenAlgObject GeneticAlgorithmProcessor::mutateObject(const GenAlgObject &b){
    GenAlgObject result(b);
//    //а что если мутейтить одну фигуру?
//    int randIndex = qrand()%figures;
//    result.figureList[randIndex] = mutateFigure(result.figureList[randIndex]);
    for(int i=0;i<mutationFiguresNum;i++){
        int index = qrand()%result.figureList.size();
        result.figureList[index] = mutateFigure(result.figureList[index]);
    }
//    for(int i=0;i<result.figureList.size();i++){
//        //по мат ожиданию все сойдется
//        if ((double(qrand()%100)/100) > mutationFiguresNum)
//            result.figureList[i] = mutateFigure(result.figureList[i]);
//    }

    //старый код с рандом мутейтом
//    for(int i=0;i<result.figureList.size();i++){
//        double randVal = double(qrand()%100)/100;
//        if (randVal < mutationChance*2)
//            result.figureList[i] = mutateFigure(result.figureList[i]);
//    }
    return result;
}


QJsonArray GeneticAlgorithmProcessor::getPopulationInJSON(){
    QJsonArray result;
    for(int i=0;i<population.size();i++)
        result.push_back(population.at(i).serializeToJson());
    return result;
}
QJsonObject GeneticAlgorithmProcessor::getElementInJSON(int index){
    return population.at(index).serializeToJson();
}


void GeneticAlgorithmProcessor::startIteration(){
    increaseGenerationIndex();
    //захардкодим 10 поколений без изменений и шейк 0.2
    if (generationIndex==nextBigShakeIndex){
            shake(true);
        }
    else if (generationIndex==nextSmallShakeIndex){
        shake(false);
    }

    qDebug() << QString("started %1 generation").arg(QString::number(generationIndex));
    crossover();
    qDebug() << QString("crossover");
    //закоменчено, сортировка это хорошо, но тем не менее пусть будет потом
//    sortPopulation();
//    qDebug() << QString("sortPopulation");
    mutation();
    mitosis();
    qDebug() << QString("mutation");
    sortPopulation();
    qDebug() << QString("sortPopulation");
    selection();
    qDebug() << QString("selection");
    finishIteration();
    qDebug() << QString("finishIteration");
}

void GeneticAlgorithmProcessor::finishIteration(){
    double currentBestResult = population[0].res;
    if (bestResult > currentBestResult){
        bestResultIndex = generationIndex;
        bestResult = currentBestResult;
        nextSmallShakeIndex=generationIndex+smallShakeInterval;
        nextBigShakeIndex=generationIndex+bigShakeInterval;
        emit(newBestValue(bestResult));
        qDebug() << QString("current best diff is %1").arg(bestResult);
    }
    if (!isPaused)
        emit(startNewIteration());
}
void GeneticAlgorithmProcessor::pause(){
    if(isRunning){
        isPaused = true;
        isRunning = false;
    }
}

void GeneticAlgorithmProcessor::resume(){
    if(isPaused){
        isPaused = false;
        isRunning = true;
        emit(startNewIteration());
    }
}


void GeneticAlgorithmProcessor::increaseGenerationIndex(){
    generationIndex++;
    emit(generationIndexIncreased(generationIndex));
}

void GeneticAlgorithmProcessor::shakePopulation(int range){
    qDebug() << QString("shake with ") + QString::number(range);
    population = population.mid(0,range);
    while(population.size()<populationSize)
        population.append(generateRandomObject());
}
void GeneticAlgorithmProcessor::shakePopulation(double range){
    qDebug() << QString("shake with ") + QString::number(range);
    population = population.mid(0,populationSize*range);
    while(population.size()<populationSize)
        population.append(generateRandomObject());
}
void GeneticAlgorithmProcessor::shake(bool isBig){
    if (isBig){
        shakePopulation(bigShakeRange);
        nextBigShakeIndex=generationIndex+bigShakeInterval;
    }
    else{
        shakePopulation(smallShakeRange);
    }
    nextSmallShakeIndex=generationIndex+smallShakeInterval;
}


int GeneticAlgorithmProcessor::findWeakestFigure(const GenAlgObject& b){
    GenAlgObject temp(b);
    int weakestIndex = -1;
    double weakestDiff = qInf();
    for(int i=0;i<temp.figureList.size();i++){
        double fitnessValueBefore = FitnessFunction(temp);
        double oldRadius = temp.figureList[i].radius;
        temp.figureList[i].radius = 0;
        double fitnessValueAfter = FitnessFunction(temp);
        double diff = fitnessValueAfter - fitnessValueBefore;
        if (diff < weakestDiff){
            weakestDiff= diff;
            weakestIndex = i;
        }
        temp.figureList[i].radius = oldRadius;
    }
    return weakestIndex;
}

Figure& GeneticAlgorithmProcessor::getWeakesFigure(GenAlgObject& b){
    return b.figureList[findWeakestFigure(b)];
}
