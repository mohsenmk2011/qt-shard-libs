#include "jooyanetworkaccessmanager.h"

JooyaNetworkAccessManager::JooyaNetworkAccessManager(QObject *parent) : QNetworkAccessManager(parent)
{
    connect(this, SIGNAL(finished(QNetworkReply*)),this,SLOT(requestFinished(QNetworkReply*)));
}

QNetworkReply *JooyaNetworkAccessManager::get(const QNetworkRequest &request)
{
    qWarning()<<"4444444444444444444444444444444444444444444444";
    qWarning()<<"444444444444444 API REQUEST 444444444444444444";
    qWarning()<<"4444444444444444444444444444444444444444444444";
    if (request.url().path().contains("jooyabash.ir"))
    {
        //request.setRawHeader("Accept-Charset", "UTF-8,*;q=0.5");
        qWarning()<<"4444444444444444444444444444444444444444444444";
        qWarning()<<"444444444444444 API REQUEST 444444444444444444";
        qWarning()<<"4444444444444444444444444444444444444444444444";
    }
    else {
        qWarning()<<"4444444444444444444444444444444444444444444444";
        qWarning()<<"444444444444444 WebView REQUEST 444444444444444444";
        qWarning()<<request.url().path();
        qWarning()<<"4444444444444444444444444444444444444444444444";

    }
    return QNetworkAccessManager::get(request);
}

void JooyaNetworkAccessManager::requestFinished(QNetworkReply * reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        qInfo()<<"+++++++++++++++ [ NoError ] ++++++++++++++++";
        auto r=reply->readAll();
        qInfo()<<reply->url();

        qInfo()<<r;
        qInfo()<<"+++++++++++++++++++++++++++++++++++++++++++++++";
        emit replyAvailable(r);
    }
    else
    {
        qCritical()<<"+++++++++++++ [ Error ] ++++++++++++";
        qCritical()<<"++++++++++++++++++++++++++++++++++++++";
    }
}
