#ifndef BESTRESULTIMAGEPROVIDER_H
#define BESTRESULTIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QObject>
class bestResultImageProvider : public QQuickImageProvider
{
public:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    QImage image;
    explicit bestResultImageProvider();
    ~bestResultImageProvider();
};

#endif // BESTRESULTIMAGEPROVIDER_H
