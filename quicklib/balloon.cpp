#include "balloon.h"

Balloon::Balloon(QQuickItem *parent) : QuickItem(parent)
{
    m_RightAligned=false;
    m_CornerAtTop=true;
    m_CornerWidth=9;
    m_CornerHeight=9;
    m_Radius=9;
    setWidth(27);
    setHeight(27);
}
void Balloon::paint(QPainter *painter)
{
    QBrush brush(color());
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(getRoundedPath().GetPath());
}

bool Balloon::rightAligned()
{
    return m_RightAligned;
}

void Balloon::setRightAligned(bool r)
{
    if(m_RightAligned!=r){
        m_RightAligned=r;
        emit rightAlignedChanged();
    }
}

bool Balloon::cornerAtTop()
{
    return m_CornerAtTop;
}

void Balloon::setCornerAtTop(bool c)
{
    if(m_CornerAtTop!=c){
        m_CornerAtTop=c;
        emit cornerAtTopChanged();
    }
}

float Balloon::cornerWidth()
{
    return m_CornerWidth;
}

void Balloon::setCornerWidth(float w)
{
    if(m_CornerWidth!=w){
        m_CornerWidth=w;
        emit cornerWidthChanged();
    }
}

float Balloon::cornerHeight()
{
    return m_CornerHeight;
}

void Balloon::setCornerHeight(float h)
{
    if(m_CornerHeight!=h){
        m_CornerHeight=h;
        emit cornerHeightChanged();
    }
}

int Balloon::radius()
{
    return m_Radius;
}

void Balloon::setRadius(float r)
{
    if(m_Radius!=r){
        m_Radius=r;
        emit radiusChanged();
    }
}

RoundedPolygon Balloon::getRoundedPath(){
    RoundedPolygon poly;
    if(cornerAtTop()){
        if(rightAligned()){
            QRectF r={0,0,width()-cornerWidth(),height()};
            poly<<QPointF(r.topLeft());
            poly<<QPointF(r.topRight()+QPointF(cornerWidth(),0));
            poly<<QPointF(r.topRight()+QPointF(0,cornerHeight()));
            poly<<QPointF(r.bottomRight());
            poly<<QPointF(r.bottomLeft());
        }
        else {
            QRectF r={cornerWidth(),0,width()-cornerWidth(),height()};
            poly<<QPointF(r.topLeft()-QPointF(cornerWidth(),0));
            poly<<QPointF(r.topRight());
            poly<<QPointF(r.bottomRight());
            poly<<QPointF(r.bottomLeft());
            poly<<QPointF(r.topLeft()+QPointF(0,cornerHeight()));
        }
    }
    else {
        if(rightAligned()){
            QRectF r={0,0,width()-cornerWidth(),height()};
            poly<<QPointF(r.topLeft());
            poly<<QPointF(r.topRight());
            poly<<QPointF(r.bottomRight()-QPointF(0,cornerHeight()));
            poly<<QPointF(r.bottomRight()+QPointF(cornerWidth(),0));
            poly<<QPointF(r.bottomLeft());
        }
        else {
            QRectF r={cornerWidth(),0,width()-cornerWidth(),height()};
            poly<<QPointF(r.topLeft());
            poly<<QPointF(r.topRight());
            poly<<QPointF(r.bottomRight());
            poly<<QPointF(r.bottomLeft()-QPointF(cornerWidth(),0));
            poly<<QPointF(r.bottomLeft()-QPointF(0,cornerHeight()));
        }
    }
    poly.SetRadius(radius());
    return poly;
}

