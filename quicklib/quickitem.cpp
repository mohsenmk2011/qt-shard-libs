#include "quickitem.h"

QuickItem::QuickItem(QObject *parent) : QQuickPaintedItem()
{
    m_Color=QColor("#FFFFFF");
}

QColor QuickItem::color()
{
    return m_Color;
}

void QuickItem::setColor(QColor c)
{
    if(m_Color.operator!=(c)){
        m_Color=c;
        emit colorChanged();
    }
}
