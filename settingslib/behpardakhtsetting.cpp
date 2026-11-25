#include "behpardakhtsetting.h"

BehpardakhtSetting::BehpardakhtSetting(QObject *parent) : JooyaNetwork(parent)
{
    setTerminalId(0);
    setPayerId(0);
}

int BehpardakhtSetting::terminalId()
{
    return m_terminalId;
}

int BehpardakhtSetting::payerId()
{
    return m_payerId;
}

bool BehpardakhtSetting::enabled()
{
    return m_enabled;
}

QString BehpardakhtSetting::userName()
{
    return m_userName;
}

QString BehpardakhtSetting::password()
{
    return m_password;
}

QString BehpardakhtSetting::additionalData()
{
    return m_additionalData;
}

QString BehpardakhtSetting::termainalUrl()
{
    return m_termainalUrl;
}

QString BehpardakhtSetting::callBackUrl()
{
    return m_callBackUrl;
}

void BehpardakhtSetting::setTerminalId(int v)
{
    if(m_terminalId!=v){
        m_terminalId=v;
        emit terminalIdChanged();
    }
}

void BehpardakhtSetting::setPayerId(int v)
{
    if(m_payerId!=v){
        m_payerId=v;
        emit payerIdChanged();
    }
}

void BehpardakhtSetting::setEnabled(bool v)
{
    if(m_enabled!=v){
        m_enabled=v;
        emit enabledChanged();
    }
}

void BehpardakhtSetting::setUserName(QString v)
{
    if(m_userName!=v){
        m_userName=v;
        emit userNameChanged();
    }
}

void BehpardakhtSetting::setPassword(QString v)
{
    if(m_password!=v){
        m_password=v;
        emit passwordChanged();
    }
}

void BehpardakhtSetting::setAdditionalData(QString v)
{
    if(m_additionalData!=v){
        m_additionalData=v;
        emit additionalDataChanged();
    }
}

void BehpardakhtSetting::setTermainalUrl(QString v)
{
    if(m_termainalUrl!=v){
        m_termainalUrl=v;
        emit termainalUrlChanged();
    }
}

void BehpardakhtSetting::setCallBackUrl(QString v)
{
    if(m_callBackUrl!=v){
        m_callBackUrl=v;
        emit callBackUrlChanged();
    }
}

void BehpardakhtSetting::load()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest("api/Settings/Behpardakht");
    connect(r,SIGNAL(finished()),this,SLOT(loadFinished()));
}

void BehpardakhtSetting::save()
{
    setIsProcssing(true);
    QNetworkReply* r=postRequest("api/Settings/SaveBehpardakht",readFeilds());
    connect(r,SIGNAL(finished()),this,SLOT(saveFinished()));
}

void BehpardakhtSetting::loadFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonDocument doc=QJsonDocument::fromJson(r->readAll());
        QJsonObject jobj=doc.object();
        setCallBackUrl(jobj.value("callBackUrl").toString());
        setTermainalUrl(jobj.value("terminalUrl").toString());
        setTerminalId(jobj.value("terminalId").toInt());
        setPayerId(jobj.value("payerId").toInt());

        setUserName(jobj.value("userName").toString());
        setPassword(jobj.value("password").toString());
        setEnabled(jobj.value("enabled").toBool());
        setAdditionalData(jobj.value("additionalData").toString());
    }
    else {
        showMessage(r);
    }
    setIsProcssing(false);
}

void BehpardakhtSetting::saveFinished()
{
    QNetworkReply* r= convertToReply(sender());
    if(r->error()!=QNetworkReply::NoError){
        qDebug()<<r->readAll();
    }
    showMessage(sender());
    setIsProcssing(false);
}

QJsonObject BehpardakhtSetting::readFeilds()
{
    QJsonObject obj;
    obj.insert("userName",userName());
    obj.insert("password",password());
    obj.insert("enabled",enabled());
    obj.insert("additionalData",additionalData());
    obj.insert("callBackUrl",callBackUrl());
    obj.insert("payerId",payerId());
    obj.insert("terminalId",terminalId());
    obj.insert("terminalUrl",termainalUrl());
    return  obj;
}

