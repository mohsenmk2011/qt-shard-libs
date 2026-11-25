#include "triangle.h"

Triangle::Triangle(QObject *parent) : QQuickPaintedItem()
{
   m_needUpdate=true;
    setColor(Qt::red);
    setFlag(QQuickItem::ItemHasContents);
}

QColor Triangle::color()
{
    return m_Color;
}

void Triangle::setColor(QColor c)
{
    if(m_Color != c) {
        m_Color = c;
        //            m_needUpdate = true;
        update();
        colorChanged();
    }
}

void Triangle::paint(QPainter *painter)
{
    painter->setPen (Qt :: NoPen);
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.moveTo(width() / 2, 0);
    path.lineTo(width() ,height());
    path.lineTo(0, height()/2);
    path.lineTo(width() / 2, 0);
    painter->fillPath (path, QBrush (color()));
}
