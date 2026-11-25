#include "fontsizemanager.h"

FontSizeManager::FontSizeManager(QObject *parent) : QObject(parent)
{

}

float FontSizeManager::width()
{
    return m_Width;
}

void FontSizeManager::setWidth(float w)
{
    if(m_Width!=w){
        m_Width=w;
        emit widthChanged();
        calculateFixNumber();
    }
}

float FontSizeManager::newWidth()
{
    return m_NewWidth;
}

void FontSizeManager::setNewWidth(float nw)
{
    if(m_NewWidth!=nw){
        m_NewWidth=nw;
        emit heightChanged();
        calculateNewFontSize();
    }
}

float FontSizeManager::fontSize()
{
    return m_FontSize;
}

void FontSizeManager::setFontSize(float fs)
{
    if(m_FontSize!=fs){
        m_FontSize=fs;
        emit fontSizeChanged();
        calculateFixNumber();
    }
}

float FontSizeManager::newFontSize()
{
    return m_NewFontSize;
}

void FontSizeManager::setNewFontSize(float nfs)
{
    if(m_NewFontSize!=nfs){
        m_NewFontSize=nfs;
        emit newFontSizeChanged();
    }
}

void FontSizeManager::calculateNewFontSize()
{
    setNewFontSize(newWidth()*m_FixNumber);
}

void FontSizeManager::calculateFixNumber()
{
    m_FixNumber=fontSize()/width();
}
