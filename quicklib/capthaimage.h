#ifndef CAPTHAIMAGE_H
#define CAPTHAIMAGE_H

#include <QQuickItem>
#include<QQuickPaintedItem>
#include<QImage>
#include<QPainter>
#include<imageutility.h>

class CapthaImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:
    CapthaImage(QQuickItem *parent = Q_NULLPTR) : QQuickPaintedItem(parent){m_Image=QImage();m_Path="";}

    void paint(QPainter* painter) Q_DECL_OVERRIDE;

    QImage image();
    void setImage(QImage img);

    QString path();
    void setPath(QString p);

signals:
    void imageChanged();
    void pathChanged();
private slots:
    void imageLoadingChanged(bool loaded);
private:
    QImage m_Image;
    QString m_Path;
};

#endif // CAPTHAIMAGE_H
