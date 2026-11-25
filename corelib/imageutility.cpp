#include "imageutility.h"

ImageUtility::ImageUtility(QObject *parent) : FileUtility(parent)
{
    m_image =QImage();
    m_ImageBytes={};
}
ImageUtility::ImageUtility(QByteArray imgBytes) :ImageUtility()
{
    loadFromData(imgBytes);
}

ImageUtility::ImageUtility(QImage img)
{
    m_image=img;
}
ImageUtility::ImageUtility(QString path) :ImageUtility()
{
    loadFromPath(path);
}

bool ImageUtility::save(QUrl imageUrl)
{
    qDebug()<<"image url => "<<imageUrl;
    qDebug()<<"image path => "<<imageUrl.path();
    return m_image.save(imageUrl.path());
}

QImage ImageUtility::image()
{
    return m_image;
}

int ImageUtility::imgWidth()
{
    return m_image.width();
}

int ImageUtility::imgHeight()
{
    return m_image.height();
}

void ImageUtility::setImage(QImage img)
{
    m_image=img;
    emit imageChanged();
}

bool ImageUtility::loadFromPath(QUrl url)
{
    qDebug()<<"load image from image path => " << url;
    qDebug()<<"path.toLocalFile() => " << url.toLocalFile();
    qDebug()<<"path.path() => " << url.path();
    qDebug()<<"path.path() => " << url.toString();
    QString ttt = "";
    /// check if the url is content url or not
    if(url.toString().contains("content://"))
    {
        ttt = url.toString();
    }
    else
    {
        ttt = url.toLocalFile();
    }

    QFile imgFile(ttt);
    if(!imgFile.exists()){
        qCritical()<<"Image File Not Exists";
        return false;
    }
    if(!imgFile.open(QIODevice::ReadOnly)){
        qCritical()<<"Image File Not Opened";
        return false;
    }
    m_ImageBytes=imgFile.readAll();
    qDebug()<<"image Bytes Count=>"<<m_ImageBytes.count();

    bool isOpend= m_image.loadFromData(m_ImageBytes);

    if(!isOpend){
        return false;
        qCritical()<<"Image was not loaded !";
    }
    emit imageLoadingStateChanged(isOpend);
    return true;
}

bool ImageUtility::loadFromData(QByteArray base64Data)
{
    return m_image.loadFromData(base64Data);
}

void ImageUtility::crop(int x,int y,int width,int height )
{
    setImage(image().copy(x,y,width,height));
}

bool ImageUtility::clip(QRectF rect,double scale)
{
    // Define the region to be clipped
    qInfo()<<"scale=> "<<scale;
    int x = rect.x() / scale;
    int y = rect.y() / scale;
    int width = rect.width() / scale;
    int height = rect.height() / scale;
    qInfo()<<"clip rect "<<rect;
    QRectF clipRect(x, y, width, height);
    qInfo()<<"scaled clip rect "<<clipRect;

    //setImage(image().copy(x,y,width,height));

    // Create the target image
    QImage clippedImage(clipRect.size().toSize(), QImage::Format_RGB32);
    // Draw the clipped portion onto the target image
    QPainter painter(&clippedImage);
    painter.drawImage(QPoint(0, 0), m_image, clipRect);
    qInfo()<<"clippedImage.isNull => "<<clippedImage.isNull();
    m_image = clippedImage;
    qInfo()<<"m_image.isNull => "<<m_image.isNull();
    return !m_image.isNull();
}

// void ImageUtility::rotate(int angel)
// {
//     if(angel==0||angel==360){
//         return;
//     }
//     QPoint center = image().rect().center();
//     QMatrix matrix;
//     matrix.translate(center.x(), center.y());
//     matrix.rotate(angel);
//     QImage dstImg = image().transformed(matrix);
//     setImage(dstImg);
//     //    QPixmap dstPix = QPixmap::fromImage(dstImg);
// }

void ImageUtility::resize(int width, int height)
{
    setImage(image().scaled(width, height,Qt::KeepAspectRatio));
}

QByteArray ImageUtility::imageBytes()
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image().save(&buffer,"JPEG");
    return  ba;
}

QString ImageUtility::base64Img(){
    QByteArray barray;
    QBuffer buffer(&barray);
    m_image.save(&buffer,"JPG");
    return QString::fromLatin1(barray.toBase64().data());
}

QString ImageUtility::htmlImg(bool copyToClipboard){
    qDebug()<<"return htm image =>";
    QString t=QString("<img src=\"data:image/png;base64,%1\"/>").arg(base64Img());
    qDebug()<< "html tag => commented :)";//<<t;
    if(copyToClipboard){
        QClipboard *cb=QGuiApplication::clipboard();
        cb->setText(t);
    }
    return t;
}

bool ImageUtility::loadImageFromClipboard(){
    qDebug()<<"load image from clipboard => ";
    const QClipboard *cb=QGuiApplication::clipboard();
    const QMimeData *md=cb->mimeData();
    if(md->hasImage()){
        setImage(cb->image());
        return true;
    }
    else{
        return false;
    }
    return false;
}

bool ImageUtility::loadFromBase64String(QString base64)
{
    base64=decodeBase64(base64);
    if(base64.isNull()||base64.isEmpty()){
        return false;
    }
    QByteArray ba=QByteArray::fromBase64(base64.toUtf8());
    return loadFromData(ba);
}

QString ImageUtility::decodeBase64(QString base64)
{
    if(!base64.contains("base64")){
        if(base64.contains("data:,")){
            base64=base64.remove(0,5);
        }
    }
    if(base64.contains("data:image")&&base64.contains("base64")){
        auto index=base64.indexOf("base64");
        //        qWarning()<<"index=> "<<index;
        //        qWarning()<<"str=> "<<base64;
        base64=base64.remove(0,index+7);
        //        qWarning()<<"base64=> "<<base64;
    }
    return base64;
}

