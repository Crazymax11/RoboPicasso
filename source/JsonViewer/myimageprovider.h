#ifndef MYIMAGEPROVIDER_H
#define MYIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QObject>
class MyImageProvider : public QQuickImageProvider
{
public:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    QImage image;
    explicit MyImageProvider();
    ~MyImageProvider();
};

#endif // MYIMAGEPROVIDER_H
