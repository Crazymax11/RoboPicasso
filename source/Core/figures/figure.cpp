#include "figure.h"


Figure::Figure()
{

}

Figure::Figure(FigureTypes type, double x, double y, double radius, QRgb color, double opacity, double angle){
    this->type = type;
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->color = color;
    this->opacity = opacity;
    this->angle = angle;
}
Figure::Figure(const Figure& mother, const Figure& father){
    const Figure* parents[2];
    parents[0]= &mother;
    parents[1]= &father;
    int randnum = qrand()%2;
    x = parents[randnum]->x;
    y = parents[randnum]->y;
    type = parents[qrand()%2]->type;
    angle = (parents[0]->angle + parents[1]->angle) / 2;
    color = (parents[0]->color + parents[1]->color) / 2;
    radius = (parents[0]->radius + parents[1]->radius) / 2;
    opacity = (parents[0]->opacity + parents[1]->opacity) /2;
}

Figure Figure::createRandomFigure(double minOpacity, double radiusLim){
    Figure figure;
    figure.type = static_cast<FigureTypes>(qrand()%3);
    figure.radius = double(qrand()%int(1000*radiusLim))/1000;
    figure.x = double(qrand()%1000)/1000;
    figure.y = double(qrand()%1000)/1000;
    figure.angle = double(qrand()%1000)/1000;
    figure.color = qRgb(qrand()%255, qrand()%255, qrand()%255);
    figure.opacity = minOpacity + double(qrand()%int(1000-minOpacity*1000))/1000;
    return figure;
}

QJsonObject Figure::serializeToJson() const{
    QJsonObject result;
    result["type"] = FigureTypesNames[type];
    result["radius"] = QString::number(radius);
    result["x"] = QString::number(x);
    result["y"] = QString::number(y);
    result["angle"] = QString::number(angle);
    result["opacity"] = QString::number(opacity);
    QJsonObject colorJSON;
    colorJSON["red"] = QString::number(qRed(color));
    colorJSON["blue"] = QString::number(qBlue(color));
    colorJSON["green"] = QString::number(qGreen(color));
    result["color"]=colorJSON;
    return result;
}


Figure::Figure(QJsonObject jsonobj){
    loadFromJSON(jsonobj);
}

void Figure::loadFromJSON(QJsonObject jsonobj){
    type = static_cast<FigureTypes>(FigureTypesNames.indexOf(jsonobj["type"].toString()));
    radius = jsonobj["radius"].toString().toDouble();
    x = jsonobj["x"].toString().toDouble();
    y = jsonobj["y"].toString().toDouble();
    angle = jsonobj["angle"].toString().toDouble();
    opacity = jsonobj["opacity"].toString().toDouble();
    QJsonObject colorJSON = jsonobj["color"].toObject();
    color = qRgb(colorJSON["red"].toString().toInt(), colorJSON["blue"].toString().toInt(), colorJSON["green"].toString().toInt());
}
