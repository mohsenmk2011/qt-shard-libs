#include "jooyanetworkengine.h"

JooyaNetworkEngine::JooyaNetworkEngine(QObject *parent) : QObject(parent)
{
    m_IsProccessing=false;
    m_DisplayCommonErrorMessage = true;
    m_OperationType=OperationTypes::OperationTypesEnum::NoOperation;
    m_OperationMessage="";
}

QJsonObject JooyaNetworkEngine::toJson()
{
    return QJsonObject();
}

void JooyaNetworkEngine::fromJson(QJsonObject json)
{
    Q_UNUSED(json);
}

Message *JooyaNetworkEngine::message(){
    return m_Message;
}

JsonUtility* JooyaNetworkEngine::jsonUtility()
{
    return new JsonUtility();
}

DateTimeUtility *JooyaNetworkEngine::dateTimeUtility()
{
    return new DateTimeUtility();
}

//void JooyaNetworkEngine::setMessage(Message* m){
//    m_Message=m;
//}

UserLoginInfo *JooyaNetworkEngine::loginInfo()
{
    return m_loginInfo;
}

bool JooyaNetworkEngine::isProcessing()
{
    return m_IsProccessing;
}

void JooyaNetworkEngine::setIsProcssing(bool isProcessing)
{
    m_IsProccessing=isProcessing;
    emit isProcessingChanged(m_IsProccessing);
}

bool JooyaNetworkEngine::displayCommonErrorMessage()
{
    return m_DisplayCommonErrorMessage;
}

void JooyaNetworkEngine::setDisplayCommonErrorMessage(bool show)
{
    m_DisplayCommonErrorMessage = show;
}

QString JooyaNetworkEngine::operationMessage()
{
    return m_OperationMessage;
}

void JooyaNetworkEngine::setOperationMessage(QString message)
{
    if(m_OperationMessage!=message){
        m_OperationMessage=message;
        emit operationMessageChanged();
    }
}

OperationTypes::OperationTypesEnum JooyaNetworkEngine::operationType()
{
    return m_OperationType;
}

void JooyaNetworkEngine::setOperationType(OperationTypes::OperationTypesEnum o)
{
    if(m_OperationType!=o){
        m_OperationType=o;
        emit operationTypeChanged();
    }
}

 QString JooyaNetworkEngine::m_BaseUrl="";
 QString JooyaNetworkEngine::m_ApiUrl="";

 QString JooyaNetworkEngine::baseUrl()
 {
     return m_BaseUrl;
 }

 void JooyaNetworkEngine::setBaseUrl(QString url)
 {
     m_BaseUrl=url;
 }

 QString JooyaNetworkEngine::apiUrl()
 {
     return m_ApiUrl;
 }

 void JooyaNetworkEngine::setApiUrl(QString url)
 {
     m_ApiUrl=url;
 }

 UserLoginInfo* JooyaNetworkEngine::m_loginInfo=new UserLoginInfo();

 FileWatcher* JooyaNetworkEngine::m_FileWather = new FileWatcher();


  bool JooyaNetworkEngine::isNetworkIsAccessible=false;

  Message* JooyaNetworkEngine::m_Message=new Message();
