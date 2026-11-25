#include "smssettings.h"

SmsSettings::SmsSettings(QObject *parent) : JooyaNetwork(parent)
{
    setWaitTimeForNextSend(15);
}

QString SmsSettings::userName()
{
    return m_userName;
}

void SmsSettings::setUserName(QString v)
{
    if(m_userName!=v){
        m_userName=v;
        emit userNameChanged();
    }
}

QString SmsSettings::password()
{
    return m_password;
}

void SmsSettings::setPassword(QString v)
{
    if(m_password!=v){
        m_password=v;
        emit passwordChanged();
    }
}

int SmsSettings::waitTimeForNextSend()
{
    return m_WaitTimeForNextSend;
}

void SmsSettings::setWaitTimeForNextSend(int waitTime)
{
    if(m_WaitTimeForNextSend!=waitTime){
        m_WaitTimeForNextSend=waitTime;
        emit waitTimeForNextSendChanged();
    }
}

QString SmsSettings::senderNumber()
{
    return m_SenderNumber;
}

void SmsSettings::setSenderNumber(QString number)
{
    if(m_SenderNumber!=number){
        m_SenderNumber=number;
        emit senderNumberChanged();
    }
}

void SmsSettings::load()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest("api/Settings/Sms");
    connect(r,SIGNAL(finished()),this,SLOT(loadFinished()));
}
void SmsSettings::loadFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonDocument doc=QJsonDocument::fromJson(r->readAll());
        QJsonObject jobj=doc.object();
        setWaitTimeForNextSend(jobj.value("waitTimeForNextSend").toInt());
        setUserName(jobj.value("userName").toString());
        setPassword(jobj.value("password").toString());
        setSenderNumber(jobj.value("senderNumber").toString());
    }
    else {
        showMessage(r);
    }
    setIsProcssing(false);
}

void SmsSettings::save()
{
    setIsProcssing(true);
    QNetworkReply* r=postRequest("api/Settings/SaveSms",readFeilds());
    connect(r,SIGNAL(finished()),this,SLOT(saveFinished()));
}
void SmsSettings::saveFinished()
{
    showMessage(sender());
    setIsProcssing(false);
}

QJsonObject SmsSettings::readFeilds()
{
    QJsonObject obj;
    obj.insert("userName",userName());
    obj.insert("password",password());
    obj.insert("senderNumber",senderNumber());
    obj.insert("waitTimeForNextSend",waitTimeForNextSend());
    return  obj;
}
