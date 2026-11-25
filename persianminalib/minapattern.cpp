#include "minapattern.h"

MinaPattern::MinaPattern(QObject *parent) : QObject(parent)
{

}

QColor MinaPattern::backColor()
{
    return m_BackColor;
}

void MinaPattern::setBackColor(QColor bc)
{
    if(m_BackColor!=bc){
        m_BackColor=bc;
        emit backColorChanged();
    }
}
