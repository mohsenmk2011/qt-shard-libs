#include "jooyanetwork.h"

JooyaNetwork::JooyaNetwork(QObject *parent) :JooyaNetworkEngine(parent)
{
    currentUrl="";
    setRequestHeader();
    setOperationType(OperationTypes::OperationTypesEnum::NoOperation);
    connect(loginInfo(),SIGNAL(stateChanged(LoginStates::LoginStatesEnum)),this,SLOT(updateRequestHeader()));
    connect(&m_NetworkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(currentReplyFinished(QNetworkReply*)));

    QSslConfiguration sslConfiguration = m_Request.sslConfiguration();
    sslConfiguration.setProtocol(QSsl::AnyProtocol);
    sslConfiguration.setPeerVerifyMode(QSslSocket::QueryPeer);
    m_Request.setSslConfiguration(sslConfiguration);
}

void JooyaNetwork::setRequestHeaderType(HeaderContentTypes::HeaderContentTypesEnum headerContentType,QString boundary)
{
    //    qCritical()<<"*** Initialization request header ***";
    m_Request.rawHeaderList().clear();
    if(headerContentType == HeaderContentTypes::HeaderContentTypesEnum::Json)
    {
        m_Request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    }
    else if(headerContentType == HeaderContentTypes::HeaderContentTypesEnum::Form)
    {
        m_Request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    }
    else
    {
        m_Request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("multipart/form-data; boundary="+boundary));
    }
}
void JooyaNetwork::setRequestHeader(QString headerName,QString headerValue,HeaderContentTypes::HeaderContentTypesEnum headerContentType)
{
    setRequestHeaderType(headerContentType);
    qWarning()<<"heaer name=>"<<headerName;
    if(!(headerName.isNull()||headerName.isEmpty()))
    {
        qInfo()<<"====[ set api Request Header ]====";
        m_Request.setRawHeader(headerName.toUtf8(),headerValue.toUtf8());
    }
    else
    {
        qInfo()<<"====[ set current app Request Header ]====";
        if(loginInfo()->isLoggedIn()){
            QString token=loginInfo()->token();
            QString HeaderName="Authorization";
            QString HeaderValue="Bearer "+token;
            m_Request.setRawHeader(HeaderName.toUtf8(),HeaderValue.toUtf8());
        }
    }
}

void JooyaNetwork::updateRequestHeader()
{
    setRequestHeader();
}

QUrl JooyaNetwork::setUrl(QString url, bool useApiUrl, bool isFullUrl){
    if(url.isEmpty()||url.isNull()){
        return QUrl();
    }
    if(isFullUrl){
        m_Request = QNetworkRequest();
        m_Request.rawHeaderList().clear();
        qDebug()<<"headers==>"<<m_Request.headers();
        currentUrl=url;
    }
    else {
        if(url.at(0)=='/'){
            url= url.remove(0,1);
        }
        if(useApiUrl){
            currentUrl=apiUrl()+"/"+url;
        }
        else {
            currentUrl=baseUrl()+"/"+url;
        }
    }
    QUrl url2(currentUrl);
    m_Request.setUrl(url2);
    return url2;
}

QUrl JooyaNetwork::setFullUrl(QString url){
    //    initializeRequestHeader();
    currentUrl=url;
    QUrl url2(currentUrl);
    m_Request.setUrl(url2);
    return url2;
}

QUrl JooyaNetwork::url()
{
    return currentUrl;
}

QNetworkReply* JooyaNetwork::getRequest(QString url, bool useApiUrl, bool isFullUrl)
{
    if(url.isEmpty()||url.isNull()){
        qDebug()<<"currentUrl=>"<<currentUrl;
        message()->setContent("آدرس خالی است");
        return nullptr;
    }
    setIsProcssing(true);
    setUrl(url,useApiUrl,isFullUrl);
    qDebug()<<"currentUrl=>"<<currentUrl;
    QNetworkReply* r= m_NetworkManager.get(m_Request);
    if(r==nullptr){
        message()->setContent("جواب شبکه خالی است");
        qCritical()<<"network reply is null";
    }
    return r;
}

void JooyaNetwork::getAndReturnObject(QString url)
{
    if(url.isEmpty()||url.isNull()){
        return;
    }
    setIsProcssing(true);
    setUrl(url);
    QNetworkReply* r= m_NetworkManager.get(m_Request);
    connect(r,&QNetworkReply::finished,this,&JooyaNetwork::onRequestFinished);
}

QNetworkReply* JooyaNetwork::deleteRequest(QString url, bool useApiUrl)
{
    setIsProcssing(true);
    setUrl(url,useApiUrl);
    QNetworkReply* r= m_NetworkManager.deleteResource(m_Request);
    return r;
}

QNetworkReply* JooyaNetwork::postRequest(QString url, QJsonObject obj, bool useApiUrl, bool isFullUrl)
{
    setIsProcssing(true);
    setUrl(url,useApiUrl,isFullUrl);
    QNetworkReply* r=m_NetworkManager.post(m_Request,QJsonDocument(obj).toJson());
    return r;
}

void JooyaNetwork::post(QString url, QJsonObject obj)
{
    setIsProcssing(true);
    setUrl(url);
    QNetworkReply* r=m_NetworkManager.post(m_Request,QJsonDocument(obj).toJson());
    connect(r,&QNetworkReply::finished,this,&JooyaNetwork::onRequestFinished);
}

QNetworkReply *JooyaNetwork::post(QString url, QHttpMultiPart* multiPart)
{
    setIsProcssing(true);
    setUrl(url);
    setRequestHeaderType(HeaderContentTypes::HeaderContentTypesEnum::MultiPart,multiPart->boundary());
    QNetworkReply* r=m_NetworkManager.post(m_Request,multiPart);
    return r;
}

void JooyaNetwork::postAndReturnObject(QString url, QJsonObject obj)
{
    setIsProcssing(true);
    setUrl(url);
    QNetworkReply* r=m_NetworkManager.post(m_Request,QJsonDocument(obj).toJson());
    connect(r,&QNetworkReply::finished,this,&JooyaNetwork::onRequestFinishedReturnObject);
}
QNetworkReply* JooyaNetwork::postRequest(QString url, QUrlQuery query, bool useApiUrl, bool isFullUrl)
{
    setIsProcssing(true);
    // for login should use form header content type
    //https://stackoverflow.com/questions/37702013/webapi2-0-owin-token-request-using-json
    setRequestHeaderType(HeaderContentTypes::HeaderContentTypesEnum::Form);
    setUrl(url,useApiUrl,isFullUrl);

    QNetworkReply* r= m_NetworkManager.post(m_Request,query.toString(QUrl::FullyEncoded).toUtf8());
    return r;
}
QNetworkReply* JooyaNetwork::putRequest(QString url,QJsonObject obj)
{
    setIsProcssing(true);
    setUrl(url);
    QNetworkReply* r=m_NetworkManager.put(m_Request,QJsonDocument(obj).toJson());
    return r;
}

QString JooyaNetwork::removeQuotationMarks(QString m)
{
    if(m[0]=='"')
    {
        m=m.remove(0,1);
    }
    if(m[m.length()-1]=='"')
    {
        m=m.remove(m.length()-1,1);
    }
    return m;
}

void JooyaNetwork::currentReplyFinished(QNetworkReply* r)
{
    checkCommonErrors(r);
    setIsProcssing(false);
    setDisplayCommonErrorMessage(true);
    emit requestFinished(r->error() == QNetworkReply::NoError || isNotFound(r),operationType());
    setOperationType(OperationTypes::OperationTypesEnum::NoOperation);
}

void JooyaNetwork::onRequestFinished()
{
    showMessage(sender());
}

void JooyaNetwork::onRequestFinishedReturnObject()
{
    QNetworkReply* r = convertToReply(sender());
    if(r->error()== QNetworkReply::NoError)
    {
        emit requestSucceedWithObject(jsonUtility()->convertToJsonObject(r));
    }
    else
    {
        showBadMessage(r->readAll());
    }
}

void JooyaNetwork::showMessage(QObject* obj)
{
    QNetworkReply* reply=qobject_cast<QNetworkReply*>(obj);
    showMessage(reply);
}
int JooyaNetwork::getHttpCode(QNetworkReply *reply)
{
    return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

void JooyaNetwork::checkCommonErrors(QNetworkReply* r)
{
    int httpCode= getHttpCode(r);
    qDebug()<<"***[ Reply of => "<<r->url().path()<<"(HTTPStatusCode => "<<httpCode<<") ]***";
    if(isAcceptedResposeCode(httpCode)){
        return;
    }
    qWarning()<<"***[ ErrorString => "<<r->errorString()<<" ]***";
    QString m= "";
    if(httpCode==0&& !r->bytesAvailable())
    {
        m = "اتصال اینترنت را بررسی کنید";
        qDebug()<<"NetworkManager::readReplyMessage =>content="<<message()->content();
        qInfo()<<"faild url=> "<<r->url().path();
        emit connectionError();
    }
    else if(httpCode==405)
    {
        if(r->errorString().contains("Method Not Allowed")){
            m = "چنین متدی تعریف نشده است";
        }
        else{
            m = QString("خطای شماره %1 رخ داد").arg(httpCode);
        }
    }
    else if(httpCode==403)//UnAuthorized
    {
        m = "دسترسی غیر مجاز";
        emit unAuthorizedAccess();
    }
    else if(httpCode==404)
    {
        m = "آدرس یا منبع مورد نظر یافت نشد";
    }
    else if(httpCode==500)
    {
        qCritical()<<"Error ==>> "<<r->readAll();
        m = "خطای سرور";
    }
    else
    {
        m = QString("خطای شماره %1 رخ داد").arg(httpCode);
    }
    if(displayCommonErrorMessage()&&!m.isNull()&&!m.isEmpty())
    {
        message()->setContent(m);
    }
}

bool JooyaNetwork::isAcceptedResposeCode(int code)
{
    //           [ OK ]    [ Bad Request ]
    return code == 200 || code==400 ;
}

void JooyaNetwork::showMessage(QNetworkReply *r)
{
    if(!isAcceptedResposeCode(getHttpCode(r))){
        return;
    }
    if(r->error()== QNetworkReply::NoError)
    {
        showOkMessage(r->readAll());
    }
    else
    {
        qDebug()<<"^^^   BadRequest  ^^^";
        showBadMessage(r->readAll());
    }
}

void JooyaNetwork::showBadMessage(QByteArray replyMessage)
{
    QString messageString =replyMessage;
    qDebug()<<"reply.readAll()=> "<<messageString;
    try
    {
        if(replyMessage.isNull()||replyMessage.isEmpty())
        {
            qWarning()<<"reply.readAll()=> was null";

        }
        else if(messageString.contains("message"))
        {
            QJsonDocument doc=QJsonDocument::fromJson(messageString.toUtf8());
            QJsonObject obj=doc.object();
            QJsonValue value=obj.value("message");
            value.toString();
        }
        else {
            message()->setContent(removeQuotationMarks(replyMessage));
        }
    }
    catch(int d)
    {
    }
}
void JooyaNetwork::showOkMessage(QString replyMessage)
{
    try
    {
        if(replyMessage.isNull()||replyMessage.isEmpty())
        {
            message()->setContent("پیام تهی است");
        }
        else
        {
            message()->setContent(removeQuotationMarks(replyMessage),true);
        }
    }
    catch(int d)
    {
    }
}

QNetworkReply* JooyaNetwork::convertToReply(QObject* obj){
    QNetworkReply* reply=qobject_cast<QNetworkReply*>(obj);
    return reply;
}

bool JooyaNetwork::isNotFound(QNetworkReply* r){
    return r->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()==404;
}

WebSocketHandler* JooyaNetwork::m_WebSocketHandler=new WebSocketHandler();
