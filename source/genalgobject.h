#ifndef GENALGOBJECT_H
#define GENALGOBJECT_H
#include <QImage>
#include "figure.h"

class GenAlgObject
{
public:
    GenAlgObject();
    GenAlgObject(int width, int height);
    GenAlgObject(const GenAlgObject& mother, const GenAlgObject& father);
    ~GenAlgObject();
    GenAlgObject(const GenAlgObject& b);
    GenAlgObject& operator=(const GenAlgObject& b);
    void drawResult(QImage* im);
    QList<Figure> figureList;
    void genRandomObject(double opacityMin);
    bool operator<(GenAlgObject& obj2);
    quint64 res;
    int index;
private:
    int width;
    int height;


};

#endif // GENALGOBJECT_H
