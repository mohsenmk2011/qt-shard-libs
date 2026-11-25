#include "windowdistancecalculator.h"

WindowDistanceCalculator::WindowDistanceCalculator(QObject *parent) : QObject(parent)
{
    m_FixNumber=1;
}

float WindowDistanceCalculator::distance()
{
    return m_Distance;
}

void WindowDistanceCalculator::setDistance(float d)
{
    if(d!=m_Distance){
        m_Distance=d;
        emit distanceChanged();
        qDebug()<<"%%%=== m_Distance==> "<<m_Distance<<" ===%%%";
        calculateFixNumber();
    }
}

float WindowDistanceCalculator::newDistance()
{
    return m_NewDistance;
}

void WindowDistanceCalculator::setNewDistance(float nm)
{
    if(nm!=m_NewDistance){
        m_NewDistance=nm;
        emit newDistanceChanged();

        qDebug()<<"=== m_NewDistance==> "<<m_NewDistance<<" ===";
    }
}

float WindowDistanceCalculator::baseWidth()
{
    return m_BaseWidth;
}

void WindowDistanceCalculator::setBaseWidth(float bw)
{
    if(m_BaseWidth!=bw){
        m_BaseWidth=bw;
        emit baseWidthChanged();
        qDebug()<<"%%%=== m_BaseWidth==> "<<m_BaseWidth<<" ===%%%";
        calculateFixNumber();
    }
}

float WindowDistanceCalculator::currentWidth()
{
    return m_CurrentWidth;
}

void WindowDistanceCalculator::setCurrentWidth(float cw)
{
    if(m_CurrentWidth!=cw){
        m_CurrentWidth=cw;
        qDebug()<<"WindowDistanceCalculator::setCurrentWidth(int cw="<<m_CurrentWidth<<")";
        calculateNewDistance();
        emit currentWidthChanged();
    }
}

float WindowDistanceCalculator::fixNumber()
{
    return m_FixNumber;
}

void WindowDistanceCalculator::setFixNumber(float fn)
{
    if(fn!=m_FixNumber){
        m_FixNumber=fn;
        emit fixNumberChanged();
    }
}

void WindowDistanceCalculator::calculateFixNumber()
{
    if(distance()<=0||baseWidth()<=0){
        return;
    }
    m_FixNumber=distance()/baseWidth();
    qDebug()<<"*** m_FixNumber("<<m_FixNumber<<")="<<distance()<<"/"<<baseWidth()<<"***";
}

void WindowDistanceCalculator::calculateNewDistance()
{
    setNewDistance(m_FixNumber*currentWidth());
}
