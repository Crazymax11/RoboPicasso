#include "myimageprovider.h"

MyImageProvider::MyImageProvider(): QQuickImageProvider(ImageType::Image)
{
}
QImage MyImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize){
    QImage result;

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
    }
    *size = result.size();
    return result;
}

MyImageProvider::~MyImageProvider(){

}

