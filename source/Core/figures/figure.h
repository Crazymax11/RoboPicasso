#ifndef FIGURE_H
#define FIGURE_H
#include <QImage>
#include <QJsonObject>
#include <QJsonArray>

enum FigureTypes
{
    SQUARE,
    TRIANGLE,
    CIRCLE
};
static const QList<QString> FigureTypesNames = QList<QString>() << "SQUARE" << "TRIANGLE" << "CIRCLE";

#include <corelib.h>
class ROBOPICASSOCORE_LIBRARY_EXPORT Figure
{
public:
    Figure();
    Figure(const Figure& mother, const Figure& father);
    Figure(FigureTypes type, double x, double y, double radius, QRgb color, double opacity, double angle);
    Figure(QJsonObject jsonobj);
    static Figure createRandomFigure(double minOpacity, double radiusLim = 0.25);


    FigureTypes type;
    double radius; //0 to 0.5, 0.5 от диагонали картинки
    double x; //0 to 1
    double y; //0 to 1
    QRgb color;
    double opacity; //0 to 1
    double angle; //0 to 1
    QJsonObject serializeToJson() const;
private:
    void loadFromJSON(QJsonObject jsonobj);
};

#endif // FIGURE_H
