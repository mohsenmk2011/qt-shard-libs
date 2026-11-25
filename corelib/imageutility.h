#ifndef IMAGEUTILITY_H
#define IMAGEUTILITY_H

#include <QObject>
#include<QFile>
#include<QByteArray>
#include<QDebug>
#include<QDir>
#include<QImage>

#include<QByteArray>
#include<QBuffer>
#include<QMimeData>
//#include<QApplication>
#include<QString>
#include<qurl.h>
#include<qbuffer.h>
#include<fileutility.h>
#include<QImageReader>
#include<QPainter>
#include<QClipboard>

class ImageUtility : public FileUtility
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int imgWidth READ imgWidth CONSTANT)
    Q_PROPERTY(int imgHeight READ imgHeight CONSTANT)
public:
    explicit ImageUtility(QObject *parent = nullptr);
    ImageUtility(QByteArray imgBytes);
    ImageUtility(QImage img);
    ImageUtility(QString path);
    Q_INVOKABLE bool save(QUrl imageUrl);

    QImage image();
    int imgWidth();
    int imgHeight();

    void setImage(QImage img);
    Q_INVOKABLE bool loadFromPath(QUrl url);
    Q_INVOKABLE bool loadFromData(QByteArray base64Data);
    Q_INVOKABLE bool loadImageFromClipboard();
    Q_INVOKABLE bool loadFromBase64String(QString base64);

    QString decodeBase64(QString base64);
    Q_INVOKABLE bool clip(QRectF rect, double scale=1);
    // Q_INVOKABLE void rotate(int angel);
    Q_INVOKABLE void resize(int width,int height);
    QByteArray imageBytes();

    /// convert the loaded QImage to base64 string
    QString base64Img();

    Q_INVOKABLE QString htmlImg(bool copyToClipboard=false);

    Q_INVOKABLE void crop(int x, int y, int width, int height);
signals:
    void imageLoadingStateChanged(bool loaded);
    void imageChanged();
public slots:
private:
    QImage m_image;
    QByteArray m_ImageBytes;
};

#endif // IMAGEUTILITY_H
