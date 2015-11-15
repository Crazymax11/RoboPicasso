#include "mypainter.h"
#include <QtMath>

MyPainter::MyPainter()
{
}


void MyPainter::drawFigure(QImage* image, Figure &fig)
{
    //image->fill(QColor(0,0,0));
    double angle = fig.angle*360;
    angle = angle/180 * M_PI;
    QPainter painter(image);
    //painter.setBrush(Qt::NoBrush);
    painter.setPen(fig.color);
    painter.setOpacity(fig.opacity);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int x = fig.x * image->width();
    int y = fig.y * image->height();
    int radius = fig.radius*(sqrt(image->width()*image->width() + image->height()*image->height()));
    QPainterPath path;
    switch (fig.type)
    {
    case SQUARE:
        path.moveTo(x + rotateCoordinate(-radius, -radius, angle), y + rotateCoordinate(-radius, -radius, angle, false));
        path.lineTo(x + rotateCoordinate(radius, -radius, angle), y + rotateCoordinate(radius, -radius, angle, false));
        path.lineTo(x + rotateCoordinate(radius, radius, angle), y + rotateCoordinate(radius, radius, angle, false));
        path.lineTo(x + rotateCoordinate(-radius, radius, angle), y + rotateCoordinate(-radius, radius, angle, false));
        path.lineTo(x + rotateCoordinate(-radius, -radius, angle), y + rotateCoordinate(-radius, -radius, angle, false));
        painter.fillPath(path, QBrush(fig.color));
        break;
    case CIRCLE:
        path.moveTo(x, y);
        path.arcTo(x-radius, y-radius,2*radius, 2*radius,0,360);
        painter.fillPath(path, QBrush(fig.color));
        break;
    case TRIANGLE:
        path.moveTo(x + rotateCoordinate(0, -radius, angle), y + rotateCoordinate(0, -radius, angle, false));
        path.lineTo(x + rotateCoordinate(radius, 0, angle), y + rotateCoordinate(radius, 0, angle, false));
        path.lineTo(x + rotateCoordinate(-radius, 0, angle), y + rotateCoordinate(-radius, 0, angle, false));
        path.lineTo(x + rotateCoordinate(0, -radius, angle), y + rotateCoordinate(0, -radius, angle, false));
        painter.fillPath(path, QBrush(fig.color));
        break;
    }
    painter.end();
}

int MyPainter::rotateCoordinate(int x, int y, float angle, bool isX)
{
    return isX? x*qCos(angle)+y*qSin(angle) : y*qCos(angle) - x*qSin(angle);
}
