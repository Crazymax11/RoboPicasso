#include "geneticalgorithmprocessor.h"
#include <QDebug>
#include <QColor>
#include "math.h"
#include <windows.h>
#include "mypainter.h"
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
}


void GeneticAlgorithmProcessor::start()
{

    width = targetImage.width();
    height = targetImage.height();
    maxSize = width>height? height: width;
    maxSize /=4;

    tempIm = new QImage(width,height,QImage::Format_ARGB32);

    //генерируем первое поколение
    for(int i=0;i<populationSize;i++)
    {
        population.append(generateRandomObject());
        population[i].index = i;
    }
    double bestResult = qInf();
    generationIndex = 0;
    QImage res(targetImage.width(), targetImage.height(), QImage::Format_ARGB32);
    double prevBest = qInf();
    while((generationIndex < generationsLimit))
    {
        double resultAfter;
        qDebug() << QString("started %1 generation").arg(QString::number(generationIndex));
        crossover();        
        sortPopulation();
        mutation();
        sortPopulation();
        selection();


        generationIndex++;
        bestResult = population[0].res;
        QString toSave = targetPath + QString("\\") + QString::number(generationIndex) ;

        if (bestResult < prevBest){
            prevBest = bestResult;

            qDebug() << QString("current best diff is %1").arg(bestResult);
            toSave+=QString("-%1").arg(bestResult);
            res.fill(QColor(255,255,255));
            population[0].drawResult(&res);
            toSave+= QString(".png");
            res.save(toSave);
        }

    }
}

GenAlgObject GeneticAlgorithmProcessor::generateRandomObject()
{
    GenAlgObject result(width, height);
    for(int i =0;i<figures; i++)
    {
        Figure figure;
        figure = figure.createRandomFigure(this->minOpacity);
        result.figureList.append(figure);
    }
    return result;
}

void GeneticAlgorithmProcessor::selection()
{
    population = population.mid(0,populationSize);
}

void GeneticAlgorithmProcessor::crossover()
{
    QList<GenAlgObject> tempList;
    for(int i=0;i<population.size()-1;i+=2)
        tempList.append(GenAlgObject(population[i], population[i+1]));
    //первые 3 особей самые крутые, мутируем их по 3 раз
//    for(int i=0;i<3;i++)
//        for(int j=0;j<3;j++)
//            tempList.append(mutateObject(population[i]));
    //добавим 5 рандомных объектов
    for(int i=0;i<10;i++)
        tempList.append(generateRandomObject());
    for(int i=0;i<tempList.size();i++)
        population.append(tempList[i]);
}

void GeneticAlgorithmProcessor::mutation()
{
    //первые n пожалуй не будем мутировать
    for(int i = bestUntouchables;i<population.size(); i++){
        for(int j =0; j<population[i].figureList.size();j++){
            double randVal = double(qrand()%100)/100;
            if (randVal < mutationChance)
                population[i] = mutateObject(population[i]);
        }
    }
    //мутейтим лучших не удаляя их
    for(int i=0;i<bestUntouchables;i++){
        population.append(mutateObject(population[i]));
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
    int newVal = mVal + (oldVal - mVal + diff + (1000-mVal))%(1000-mVal);
    double newRes = double(newVal)/1000;
    return newRes;
}

Figure GeneticAlgorithmProcessor::mutateFigure(const Figure &b){
    Figure result(b);
    result.type =  static_cast<FigureTypes>(qrand()%3);


    result.opacity = mutateValue(result.opacity, minOpacity);
//    result.opacity += double(qrand()%int(1000*mutationAmount*2) -1000*mutationAmount) /1000;
//    if (result.opacity<minOpacity)
//        result.opacity = minOpacity;
//    else if (result.opacity>1)
//            result.opacity = 1;


    result.x = mutateValue(result.x);
    result.y = mutateValue(result.y);
    result.angle = mutateValue(result.angle);
    //максимум должен быть 0.25
    result.radius = mutateValue(result.radius*4)/4;

    QRgb clr = result.color;
    int newred;
    int newgreen;
    int newblue;
    newred = mutateValue(double(qRed(clr))/255)*255;
    newgreen = mutateValue(double(qGreen(clr))/255)*255;
    newblue = mutateValue(double(qBlue(clr))/255)*255;
    QColor newclr(newred,newgreen,newblue);
    result.color = newclr.rgb();
    return result;
}
GenAlgObject GeneticAlgorithmProcessor::mutateObject(const GenAlgObject &b){
    GenAlgObject result(b);
    //а что если мутейтить одну фигуру?
    int randIndex = qrand()%figures;
    result.figureList[randIndex] = mutateFigure(result.figureList[randIndex]);
    //старый код с рандом мутейтом
//    for(int i=0;i<result.figureList.size();i++){
//        double randVal = double(qrand()%100)/100;
//        if (randVal < mutationChance*2)
//            result.figureList[i] = mutateFigure(result.figureList[i]);
//    }
    return result;
}
