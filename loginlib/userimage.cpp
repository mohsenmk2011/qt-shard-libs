#include "userimage.h"

UserImage::UserImage(QObject *parent) : ImageFile(parent)
{
    setWidth(72);
    setHeight(72);
    m_Date = QDateTime::currentDateTime().addYears(-9);
    qCritical()<<"date ===> "<<m_Date;

    ApplicationPath appPath;
    setFolderPath(appPath.userFolderPath());
}

UserImage::UserImage(int id, QDateTime date,QString link):UserImage()
{
    setDate(date);
    setFileId(id);
    setDownloadLink(link);
    setImageName(QString::number(id));
    setUrl(QUrl::fromLocalFile(folderPath()+imageName()+ext()));
}

UserImage::UserImage(QJsonObject jobj):UserImage()
{
    loadFromJson(jobj);
}

void UserImage::loadFromJson(QJsonObject obj)
{
    if(obj.isEmpty()){
        qCritical()<<"json image is null";
        return;
    }
    else {
        qInfo()<<"json image is not null";
    }
    setFileId(obj.value("id").toInt());
    setImageName(QString::number(fileId()));
    setDownloadLink(obj.value("url").toString());
    setPersianDate(obj.value("persianDate").toString());
    setDate(m_DateTimeUtility.toDateTime(obj.value("date").toString()));
}

QJsonObject UserImage::toJson()
{
    QJsonObject obj;
    obj.insert("id",fileId());
    obj.insert("name",fileId());
    obj.insert("url",downloadLink());
    obj.insert("date",m_DateTimeUtility.fromDateTime(date()));
    obj.insert("persianDate",persianDate());
    return obj;
}

void UserImage::resetImage()
{
    setFileId(0);
    setImageName("");
    setDownloadLink("");
    setPersianDate("");
    setDate(QDateTime());
    setUrl(QUrl());
}

void UserImage::deleteItem()
{
    if(fileId()<=0){
        return;
    }
    setIsProcssing(true);
    QNetworkReply* r=deleteRequest(QString("api/User/DeleteImage/%1").arg(fileId()));
    connect(r,SIGNAL(finished()),this,SLOT(deleteItemFinished()));
}

bool UserImage::isDefault()
{
    qInfo()<<toJson();
    return imageName().isNull()||imageName().isEmpty();
}

void UserImage::deleteItemFinished()
{
    QNetworkReply* r=convertToReply(sender());

    if(r->error()==QNetworkReply::NoError){
        remove();
        emit deleted();
    }
    showMessage(r);
}

QDateTime UserImage::date()
{
    return m_Date;
}

void UserImage::setDate(QDateTime d)
{
    if(m_Date!=d&&d.isValid()){
        m_Date=d;
        emit dateChanged();
    }
}

QString UserImage::persianDate()
{
    return m_PersianDate;
}

void UserImage::setPersianDate(QString d)
{
    if(m_PersianDate!=d){
        m_PersianDate=d;
        emit persianDateChanged();
    }
}

