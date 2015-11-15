#ifndef FIGURE_H
#define FIGURE_H
#include <QImage>

enum FigureTypes
{
    SQUARE,
    TRIANGLE,
    CIRCLE
};


class Figure
{
public:
    Figure();
    Figure(const Figure& mother, const Figure& father);
    Figure(FigureTypes type, double x, double y, double radius, QRgb color, double opacity, double angle);
    static Figure createRandomFigure(double minOpacity, double radiusLim = 0.25);


    FigureTypes type;
    double radius; //0 to 0.5, 0.5 от диагонали картинки
    double x; //0 to 1
    double y; //0 to 1
    QRgb color;
    double opacity; //0 to 1
    double angle; //0 to 1

};

#endif // FIGURE_H
