#include "jooyax509certificate.h"

JooyaX509Certificate::JooyaX509Certificate(QObject *parent) : JooyaNetwork(parent)
{

}

void JooyaX509Certificate::getInfo()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest("api/SignTokenCert/Info");
    connect(r,SIGNAL(finished()),this,SLOT(getInfoFinished()));
}

void JooyaX509Certificate::getInfoFinished()
{
    QNetworkReply* r=convertToReply(sender());
    showMessage(r);
    setIsProcssing(false);
}
void JooyaX509Certificate::save()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest("api/SignTokenCert/Save");
    connect(r,SIGNAL(finished()),this,SLOT(saveFinished()));
}

void JooyaX509Certificate::saveFinished()
{
    QNetworkReply* r=convertToReply(sender());
    showMessage(r);
    setIsProcssing(false);
}

