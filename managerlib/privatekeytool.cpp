#include "privatekeytool.h"

PrivateKeyTool::PrivateKeyTool(QObject *parent) : JooyaNetwork(parent)
{
}

void PrivateKeyTool::isPirvateKeyExists()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest("api/Privatekey");
    connect(r,SIGNAL(finished()),this,SLOT(pirvateKeyRequestFinished()));
}

void PrivateKeyTool::deletePrivateKey()
{
    setIsProcssing(true);
    QNetworkReply* r=deleteRequest("api/Privatekey/1");
    connect(r,SIGNAL(finished()),this,SLOT(pirvateKeyRequestFinished()));
}

void PrivateKeyTool::createPrivateKey()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest("api/Privatekey/Create");
    connect(r,SIGNAL(finished()),this,SLOT(pirvateKeyRequestFinished()));
}

void PrivateKeyTool::pirvateKeyRequestFinished()
{
    showMessage(sender());
    setIsProcssing(false);
}
