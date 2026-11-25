#include "capthaimage.h"

void CapthaImage::paint(QPainter *painter)
{
    if(image().isNull()) return;
    painter->drawImage(QPoint(0, 0),image().scaled(width(), height()));
}

QImage CapthaImage::image()
{
    return m_Image;
}

void CapthaImage::setImage(QImage img)
{
    m_Image=img;
    emit imageChanged();
    update();

    setImplicitHeight(image().height());
    setImplicitWidth(image().width());
}

QString CapthaImage::path()
{
    return m_Path;
}

void CapthaImage::setPath(QString p)
{
    if(p.isNull()||p.isEmpty())
    {
        return;
    }
    qDebug()<<"path=>"<<p;
    if(m_Path!=p){
        m_Path=p;
        emit pathChanged();
        ImageUtility im;
        im.loadFromPath(p);
        setImage(im.image());
        qDebug()<<"width=>"<<image().width();
        qDebug()<<"height=>"<<image().height();
    }
}

void CapthaImage::imageLoadingChanged(bool loaded)
{
    qDebug()<<"&&&&&&&&&&&& image was loaded"<<loaded<<" &&&&&&&&&&&&&&&";
    setImage(image());
}

