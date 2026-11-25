#include "capthamanager.h"

CapthaManager::CapthaManager(QObject *parent) : JooyaNetwork(parent)
{
    m_CapthaHash="";
    m_Captha=new QImage();
}

void CapthaManager::loadCaptha()
{
    if(isProcessing())
    {
        return;
    }
    qDebug()<<"loading Captha ...";
    QNetworkReply* reply=getRequest("api/Captha");
    connect(reply,SIGNAL(finished()),this,SLOT(loadCapthaFinished()));
}

//QImage* CapthaManager::captha()
//{
//    return m_Captha;
//}

//void CapthaManager::setCaptha(QImage* p)
//{
//    m_Captha=p;
//    emit capthaChanged();
//}

void CapthaManager::loadCapthaFinished()
{
    QNetworkReply* reply=convertToReply(sender());
    if(reply->error()==QNetworkReply::NoError){
        QString response=reply->readAll();
        QJsonDocument doc=QJsonDocument::fromJson(response.toUtf8());
        QJsonObject obj=doc.object();
        QString base64img= obj.value("capthaBytes").toString();
        QString c= obj.value("capthaHash").toString();
        setCapthaHash(c);
        ImageUtility im(base64img);
        emit capthaChanged(im.image());
    }
    else {
        message()->setContent("تصویر امنیتی بارگذاری نشد");
    }
}

QString CapthaManager::capthaHash()
{
    return m_CapthaHash;
}

void CapthaManager::setCapthaHash(QString p)
{
    if(p!=m_CapthaHash){
        m_CapthaHash=p;
        emit capthaHashChanged();
    }
}
