#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QImage>
#include <QPainter>


#include "figure.h"

#include <corelib.h>
class ROBOPICASSOCORE_LIBRARY_EXPORT MyPainter
{
public:
    MyPainter();
    void drawFigure(QImage* image, Figure &fig);
private:
    int rotateCoordinate(int x, int y, float angle, bool isX = true);
};

#endif // MYPAINTER_H
