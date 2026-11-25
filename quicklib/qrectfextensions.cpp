#include "qrectfextensions.h"

QRectFExtensions::QRectFExtensions(QObject *parent)
    : QObject{parent}
{

}

QRectF QRectFExtensions::topLeft(const QRectF& rect, qreal width, qreal height)
{
    qreal x = rect.topLeft().x() - width / 2;
    qreal y = rect.topLeft().y() - height / 2;
    return QRectF(x, y, width, height);
}

QRectF QRectFExtensions::topRight(const QRectF &rect, qreal width, qreal height)
{

    qreal x = rect.topRight().x() - width / 2;
    qreal y = rect.topRight().y() - height / 2;
    return QRectF(x, y, width, height);
}

QRectF QRectFExtensions::bottomLeft(const QRectF &rect, qreal width, qreal height)
{

    qreal x = rect.bottomLeft().x() - width / 2;
    qreal y = rect.bottomLeft().y() - height / 2;
    return QRectF(x, y, width, height);
}

QRectF QRectFExtensions::bottomRight(const QRectF &rect, qreal width, qreal height)
{

    qreal x = rect.bottomRight().x() - width / 2;
    qreal y = rect.bottomRight().y() - height / 2;
    return QRectF(x, y, width, height);
}

QRectF QRectFExtensions::top(const QRectF &rect, qreal height)
{
    qreal y = rect.y() - height / 2;
    return QRectF(rect.x(),y, rect.width(), height);
}

QRectF QRectFExtensions::bottom(const QRectF &rect, qreal height)
{
    qreal y = rect.bottom() - height / 2;
    return QRectF(rect.x(),y, rect.width(), height);
}

QRectF QRectFExtensions::left(const QRectF &rect, qreal width)
{
    qreal x = rect.x() - width / 2;
    return QRectF(x,rect.y(), width, rect.height());
}

QRectF QRectFExtensions::right(const QRectF &rect, qreal width)
{
    qreal x = rect.right() - width / 2;
    return QRectF(x,rect.y(), width, rect.height());
}
