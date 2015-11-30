#include "genalgobject.h"
#include "mypainter.h"
#include <QDebug>
GenAlgObject::GenAlgObject(int width, int height)
{
    res = -qInf();
}
GenAlgObject::GenAlgObject()
{
    res = -qInf();
    index = -1;
}
GenAlgObject::GenAlgObject(const GenAlgObject& mother, const GenAlgObject& father){
    const GenAlgObject* parents[2];
    parents[0]= &mother;
    parents[1]= &father;
    for(int i=0;i<mother.figureList.size();i++)
    {
        figureList.append(Figure(mother.figureList[i], father.figureList[i]));
    }
}

GenAlgObject::~GenAlgObject()
{
}
GenAlgObject::GenAlgObject(const GenAlgObject& b){
    res = -qInf();
    this->width = b.width;
    this->height = b.height;
    this->figureList = b.figureList;
    index = b.index;
    res = b.res;

}

GenAlgObject& GenAlgObject::operator=(const GenAlgObject& b){
    res = -qInf();
    this->figureList = b.figureList;
    index = b.index;
    res = b.res;
    return *this;
}

void GenAlgObject::genRandomObject(double opacityMin)
{
    for(int i=0;i<100;i++)
        figureList.append(Figure::createRandomFigure(opacityMin));
}

void GenAlgObject::drawResult(QImage* im){
    MyPainter mypainter;
    for(int i =0;i<figureList.size();i++)
        mypainter.drawFigure(im, figureList[i]);
}

bool GenAlgObject::operator<(GenAlgObject& obj2)
{
    return this->res < obj2.res;
}

QJsonObject GenAlgObject::serializeToJson() const{
    QJsonObject result;
    QJsonArray figuresJSON;
    for(int i=0;this->figureList.size();i++)
        figuresJSON.append(figureList[i].serializeToJson());
    result["figures"] = figuresJSON;
    return result;
}


GenAlgObject::GenAlgObject(QJsonObject jsonobj){
    loadFromJSON(jsonobj);
}

void GenAlgObject::loadFromJSON(QJsonObject jsonobj){
    QJsonArray figuresJSON = jsonobj["figures"].toArray();
    QJsonObject figure;
    for(int i=0;i<figuresJSON.size();i++){
        figureList.append(Figure(figuresJSON[i].toObject()));
    }
}

