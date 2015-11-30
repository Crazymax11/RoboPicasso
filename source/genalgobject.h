#ifndef GENALGOBJECT_H
#define GENALGOBJECT_H
#include <QImage>
#include "figure.h"
#include <QJsonObject>
#include <QJsonArray>
class GenAlgObject
{
public:
    GenAlgObject();
    GenAlgObject(int width, int height);
    GenAlgObject(const GenAlgObject& mother, const GenAlgObject& father);
    GenAlgObject(QJsonObject jsonobj);
    ~GenAlgObject();
    GenAlgObject(const GenAlgObject& b);
    GenAlgObject& operator=(const GenAlgObject& b);
    void drawResult(QImage* im);
    QList<Figure> figureList;
    void genRandomObject(double opacityMin);
    bool operator<(GenAlgObject& obj2);
    quint64 res;
    int index;
    QJsonObject serializeToJson() const;
private:
    void loadFromJSON(QJsonObject jsonobj);
    int width;
    int height;


};

#endif // GENALGOBJECT_H
