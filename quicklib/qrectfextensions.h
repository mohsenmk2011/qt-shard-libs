#ifndef QRECTFEXTENSIONS_H
#define QRECTFEXTENSIONS_H

#include <QObject>
#include<QRectF>

class QRectFExtensions : public QObject
{
    Q_OBJECT
public:
    explicit QRectFExtensions(QObject *parent = nullptr);

    /// returns a QRectF that it's center is top left of rect
    static QRectF topLeft(const QRectF &rect, qreal width , qreal height);
    static QRectF topRight(const QRectF &rect, qreal width , qreal height);
    static QRectF bottomLeft(const QRectF &rect, qreal width , qreal height);
    static QRectF bottomRight(const QRectF &rect, qreal width , qreal height);

    static QRectF top(const QRectF &rect , qreal height);
    static QRectF bottom(const QRectF &rect , qreal height);
    static QRectF left(const QRectF &rect, qreal width );
    static QRectF right(const QRectF &rect, qreal width );


signals:

};

#endif // QRECTFEXTENSIONS_H
