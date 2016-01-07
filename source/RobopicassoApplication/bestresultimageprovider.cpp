#include "bestresultimageprovider.h"

bestResultImageProvider::bestResultImageProvider(): QQuickImageProvider(ImageType::Image)
{
}
QImage bestResultImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize){
    QImage result;

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
    }
    *size = result.size();
    return result;
}

bestResultImageProvider::~bestResultImageProvider(){

}
