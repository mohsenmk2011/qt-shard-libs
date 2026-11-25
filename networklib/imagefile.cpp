#include "imagefile.h"

ImageFile::ImageFile(QObject *parent) : File(parent)
{
    setExt("jpg");
    ApplicationPath u;
    setFolderPath(u.imagesFolderPath());
    setImageName("deufalt_image_name");
}

int ImageFile::width()
{
    return m_Width;
}

void ImageFile::setWidth(int w)
{
    if(m_Width!=w){
        m_Width=w;
        emit widthChanged();
    }
}


int ImageFile::height()
{
    return m_Height;
}

void ImageFile::setHeight(int h)
{
    if(m_Height!=h){
        m_Height=h;
        emit heightChanged();
    }
}

QJsonObject ImageFile::toJson()
{
    ImageUtility iu;
    iu.loadFromPath(url());
    QJsonObject obj;
    obj.insert("id",fileId());
    obj.insert("imageBase64",iu.base64Img());
    obj.insert("imageUrl",downloadLink());
    return obj;
}

void ImageFile::fromJson(QJsonObject obj)
{
    setFileId(obj.value("id").toInt());
    setDownloadLink(obj.value("imageUrl").toString());
    setImageName(obj.value("imageName").toString());
    setIsExistsInServer(obj.value("isImageExistes").toBool());
}

QNetworkReply *ImageFile::uploadImage()
{
    qDebug()<<"is going to upload the image => ";
    QNetworkReply* r = File::upload("api/File/SaveImage",toJson());
    if(r==nullptr)
    {
        qCritical()<<"upload was not succeed => return";
        return nullptr;
    }
    connect(r,&QNetworkReply::finished,this,&ImageFile::onUploadImage);
    return r;
}

void ImageFile::onUploadImage()
{
    qDebug()<<"upload image finished";
    QNetworkReply* r = convertToReply(sender());

    if(r->error()==QNetworkReply::NoError)
    {
        qInfo()<<"with no error -> download it";
        download();
    }
    else
    {
        qCritical()<<"with error";
    }
    showMessage(r);
}

QNetworkReply *ImageFile::deleteImage()
{
    qDebug()<<"is going to delete the image => ";
    QJsonObject obj;
    obj.insert("imageUrl",downloadLink());
    QNetworkReply* r = postRequest("api/File/DeleteImage",obj);
    connect(r,&QNetworkReply::finished,this,&ImageFile::deleteImageFinished);
    return r;
}

void ImageFile::deleteImageFinished()
{
    QNetworkReply* r = convertToReply(sender());
    if(r->error()==QNetworkReply::NoError)
    {
        qInfo()<<"delete image finished with no error => delete local file";
        if(remove())
        {
            setIsExists(false);
        }
    }
    else
    {
        qCritical()<<"delete image finished with error";
    }
}
