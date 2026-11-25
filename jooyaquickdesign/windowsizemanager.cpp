#include "windowsizemanager.h"

WindowSizeManager::WindowSizeManager(QObject *parent) : QObject(parent)
{
    setXsHeight(12);
    setXsWidth(12);
    setSmHeight(12);
    setSmWidth(12);
    setMdHeight(12);
    setMdWidth(12);
    setLgHeight(12);
    setLgWidth(12);
    setXlHeight(12);
    setXlWidth(12);
    m_X=0;
    m_Y=0;
}

QString WindowSizeManager::tTest()
{
    return  t;
}

void WindowSizeManager::setTTest(QString tt)
{
    t=tt;
    emit tTestChanged();
}

double WindowSizeManager::rootWidth()
{
    return m_RootWidth;
}

void WindowSizeManager::setRootWidth(double w)
{
    qDebug()<<"%%%%%%%%%%% WindowSizeManager::setRootWidth => "<<w<<"%%%%%%%%%%";
    int intW=static_cast<int>(w);
    int intRootWidth=static_cast<int>(m_RootWidth);

    if(intW!=intRootWidth){
        m_RootWidth=w;
        refreshWidth();
        refreshX();
    }
}

double WindowSizeManager::rootHeight()
{
    return  m_RootHeight;
}

void WindowSizeManager::setRootHeight(double h)
{
    qDebug()<<"%%%%%%%%%%% setRootHeight => "<<h<<"%%%%%%%%%%";
    int intH=static_cast<int>(h);
    int intRootHeight=static_cast<int>(m_RootHeight);

    if(intRootHeight!=intH)
    {
        m_RootHeight=h;
        refreshHeight();
        refreshY();
    }
}

double WindowSizeManager::width()
{
    return m_Width;
}

void WindowSizeManager::setWidth(double w)
{
    m_Width=w;
    emit widthChanged();
}

double WindowSizeManager::height()
{
    return  m_Height;
}

void WindowSizeManager::setHeight(double h)
{
    m_Height=h;
    emit heightChanged();
}

int WindowSizeManager::xsWidth()
{
    return  m_XsWidth;
}

void WindowSizeManager::setXsWidth(int v)
{
    qDebug()<<"*********** m_XsWidth="<<m_XsWidth<<" *************";
    if(v<1||v>12){
        m_XsWidth=12;
        return;
    }
    m_XsWidth=v;
}

int WindowSizeManager::smWidth()
{
    return  m_SmWidth;
}

void WindowSizeManager::setSmWidth(int v)
{
    qDebug()<<"*********** m_SmWidth="<<m_SmWidth<<" *************";
    if(v<1||v>12){
        m_SmWidth=12;
        return;
    }
    m_SmWidth=v;
}

int WindowSizeManager::mdWidth()
{
    return  m_MdWidth;
}

void WindowSizeManager::setMdWidth(int v)
{
    qDebug()<<"*********** m_MdWidth="<<m_MdWidth<<" *************";
    if(v<1||v>12){
        m_MdWidth=12;
        return;
    }
    m_MdWidth=v;
}

int WindowSizeManager::lgWidth()
{
    return  m_LgWidth;
}

void WindowSizeManager::setLgWidth(int v)
{
    qDebug()<<"*********** m_LgWidth="<<m_LgWidth<<" *************";
    if(v<1||v>12){
        m_LgWidth=12;
        return;
    }
    m_LgWidth=v;
}

int WindowSizeManager::xlWidth()
{
    return m_XlWidth;
}

void WindowSizeManager::setXlWidth(int v)
{
    qDebug()<<"*********** m_XlWidth="<<m_XlWidth<<" *************";
    if(v<1||v>12){
        m_XlWidth=12;
        return;
    }
    m_XlWidth=v;
}

int WindowSizeManager::xsHeight()
{
    return  m_XsHeight;
}

void WindowSizeManager::setXsHeight(int v)
{
    if(v<1||v>12){
        m_XsHeight=12;
        return;
    }
    m_XsHeight=v;
}

int WindowSizeManager::smHeight()
{
    return m_SmHeight;
}

void WindowSizeManager::setSmHeight(int v)
{
    if(v<1||v>12){
        m_SmHeight=12;
        return;
    }
    m_SmHeight=v;
}

int WindowSizeManager::mdHeight()
{
    return  m_MdHeight;
}

void WindowSizeManager::setMdHeight(int v)
{
    if(v<1||v>12){
        m_MdHeight=12;
        return;
    }
    m_MdHeight=v;
}

int WindowSizeManager::lgHeight()
{
    return  m_LgHeight;
}

void WindowSizeManager::setLgHeight(int v)
{
    if(v<1||v>12){
        m_LgHeight=12;
        return;
    }
    m_LgHeight=v;
}

int WindowSizeManager::xlHeight()
{
    return  m_XlHeight;
}

void WindowSizeManager::setXlHeight(int v)
{
    if(v<1||v>12){
        m_XlHeight=12;
        return;
    }
    m_XlHeight=v;
}

int WindowSizeManager::x()
{
    return  m_X;
}

void WindowSizeManager::setX(int v)
{
    if(v!=m_X){
        m_X=v;
        qDebug()<<"^^^^^^^^^^^^setX="<<v<<"^^^^^^^^^^^^^^^^^^^^^^^^";
        emit xChanged();
    }
}

int WindowSizeManager::y()
{
    return  m_Y;
}

void WindowSizeManager::setY(int v)
{
    if(m_Y!=v){
        qDebug()<<"^^^^^^^^^^^^setY="<<v<<"^^^^^^^^^^^^^^^^^^^^^^^^";
        m_Y=v;
        emit yChanged();
    }
}

void WindowSizeManager::refreshWidth()
{
    qDebug()<<"*************"<<"refreshWidth tTest="<<tTest()<<"*************";
    double z=m_RootWidth/12;
    double w1=0;
    double w2=0;

    if(m_RootWidth<=544)//xs
    {
        qDebug()<<"m_XsWidth"<<xsWidth();
        w1=z*m_XsWidth;
        w2=calculateSize(m_XsWidth,m_RootWidth);
    }
    else if(m_RootWidth<=768)//sm
    {
        qDebug()<<"m_SmWidth"<<m_SmWidth;
        w1=z*m_SmWidth;
        w2=calculateSize(m_SmWidth,m_RootWidth);
    }
    else if(m_RootWidth<=992)//md
    {
        qDebug()<<"m_MdWidth"<<m_MdWidth;
        w1=z*m_MdWidth;
        w2=calculateSize(m_MdWidth,m_RootWidth);
    }
    else if(m_RootWidth<=1200)//lg
    {
        qDebug()<<"m_LgWidth"<<m_LgWidth;
        w1=z*m_LgWidth;
        w2=calculateSize(m_LgWidth,m_RootWidth);
    }
    else if(m_RootWidth>1200)//xl
    {
        qDebug()<<"m_XlWidth"<<m_XlWidth;
        w1=z*m_XlWidth;
        w2=calculateSize(m_XlWidth,m_RootWidth);
    }

    qDebug()<<"Width z="<<w1;
    qDebug()<<"Width cal="<<w2;
    setWidth(w2);

}

double WindowSizeManager::calculateSize(int v,double rootSize)
{
    switch (v) {
    case 1: return (rootSize*8.33)/100;
    case 2: return (rootSize*16.66)/100;
    case 3: return (rootSize*25)/100;
    case 4: return (rootSize*33.33)/100;
    case 5: return (rootSize*41.66)/100;
    case 6: return (rootSize*50)/100;
    case 7: return (rootSize*58.33)/100;
    case 8: return (rootSize*66.66)/100;
    case 9: return (rootSize*75)/100;
    case 10: return (rootSize*83.33)/100;
    case 11: return (rootSize*91.66)/100;
    case 12: return  rootSize;
    default:return  rootSize;
    }
}

void WindowSizeManager::refreshHeight()
{
    qDebug()<<"*************"<<"refreshHeight"<<"*************";
    double z=m_RootHeight/12;
    double h1=0;
    double h2=0;
    if(m_RootHeight<=544)//xs
    {
        qDebug()<<"m_XsHeight"<<m_XsHeight;
        h1=z*m_XsHeight;
        h2=calculateSize(m_XsHeight,m_RootHeight);
    }
    else if(m_RootHeight<=768)//sm
    {
        qDebug()<<"m_SmHeight"<<m_SmHeight;
        h1=z*m_SmHeight;
        h2=calculateSize(m_SmHeight,m_RootHeight);
    }
    else if(m_RootHeight<=992)//md
    {
        qDebug()<<"m_MdHeight"<<m_MdHeight;
        h1=z*m_MdHeight;
        h2=calculateSize(m_MdHeight,m_RootHeight);
    }
    else if(m_RootHeight<=1200)//lg
    {
        qDebug()<<"m_LgHeight"<<m_LgHeight;
        h1=z*m_LgHeight;
        h2=calculateSize(m_LgHeight,m_RootHeight);
    }
    else if(m_RootHeight>1200)//xl
    {
        qDebug()<<"m_XlHeight"<<m_XlHeight;
        h1=z*m_XlHeight;
        h2=calculateSize(m_XlHeight,m_RootHeight);
    }
    qDebug()<<"Height z="<<h1;
    qDebug()<<"Height cal="<<h2;
    setHeight(h2);

}
void WindowSizeManager::refreshX()
{
    if(width()<rootWidth()){
        int t=static_cast<int>((rootWidth()-width())/2);
        if(t>3){
            setX(t);
            return;
        }
    }
    setX(0);
}

void WindowSizeManager::refreshY()
{
    if(height()<rootHeight()){
        int t=static_cast<int>((rootHeight()-height())/2);
        if(t>3){
            setY(t);
            return;
        }
    }
    setY(0);
}

