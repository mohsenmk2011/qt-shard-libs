#include "post.h"

Post::Post(QObject *parent) : PostBase{parent}
{

}

Post::Post(QJsonObject obj):Post()
{
    fromJson(obj);
}

Post::Post(QString userId, QString contactId, QString content):Post()
{
    setUserId(userId);
    setChatId(contactId);
    setContent(content);
    setFromMe(true);    
}

Post::Post(QDateTime date, bool isJustDate):Post()
{
    setDate(date);
    setIsJustDate(isJustDate);
}

QJsonObject Post::toJson()
{
    QJsonObject obj;
    obj.insert("id",id());
    obj.insert("content",content());
    obj.insert("date",dateTimeUtility()->fromDateTime(date()));
    obj.insert("chatId",chatId());
    obj.insert("userId",userId());
    obj.insert("status",(int)status());
    qDebug()<<obj;
    return obj;
}

QJsonObject Post::toJsonStatus()
{
    QJsonObject obj;
    obj.insert("id",id());
    obj.insert("status",(int)status());
    return obj;
}

void Post::fromJson(QJsonObject json)
{
    qDebug()<<json;
    setId(json.value("id").toString());
    setContent(json.value("content").toString());
    setDate(dateTimeUtility()->toDateTime(json.value("date").toString()));
    setUserId(json.value("userId").toString());
    setChatId(json.value("chatId").toString());
    setStatus((TalkStatus::TalkStatusEnum)(json.value("status").toInt()));
}

bool Post::hasNotReceivedStatus()
{

}

void Post::save(){
    qDebug()<<"tojson post=> "<<toJson();
    QNetworkReply* reply= postRequest("api/Post/Save",toJson());
    connect(reply,&QNetworkReply::finished,this,&Post::onSaveFinished);
}

void Post::onSaveFinished()
{
    qDebug()<<"***[ Send Post Finished ]***";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        setStatus(TalkStatus::TalkStatusEnum::Seen);
    }
    else{

    }
    showMessage(r);
}

void Post::send(QString receiverId)
{
    if(isJustDate()){
        return;
    }
    if(receiverId.isNull()||receiverId.isEmpty()){
        message()->setContent("شناسه مخاطب خالی است");
        return;
    }
    WebSocketInfo* wsi=new WebSocketInfo();
    wsi->setType("NewTalk");
    wsi->setReceiverId(receiverId);
    qInfo()<<"is sending=> "<<toJson();
    wsi->setInformation(jsonUtility()->convertToJsonString(toJson()));
    if(!m_WebSocketHandler->sendTextMessage(wsi->toJson())){
        m_WebSocketHandler->open();
    }
}

void Post::sendStatus(bool requestForResend)
{
    if(isJustDate()){
        return;
    }
    if(requestForResend){
        setWaitingForResendStatus(true);
    }
    qDebug()<<"is going to send status of post";
    WebSocketInfo* wsi=new WebSocketInfo();
    wsi->setType("TalkStatus");
    if(fromMe()){
        qDebug()<<"this post im my post,so my contact has requested for status again(may be not receved status before)";
        wsi->setReceiverId(chatId());
    }
    else {
        qDebug()<<"is going to send status of my contact's post";
        wsi->setReceiverId(userId());
    }
    wsi->setInformation(jsonUtility()->convertToJsonString(toJsonStatus()));
    if(!m_WebSocketHandler->sendTextMessage(wsi->toJson())){
        m_WebSocketHandler->open();
    }
}

void Post::sendSeenStatus()
{
    qDebug()<<"***[ Send Seen Status(id = "<<id()<<"]***";
    if(fromMe()){
        qDebug()<<"is from me -> return";
        return;
    }
    if(status()==TalkStatus::TalkStatusEnum::Seen){
        qDebug()<<"status is Seen (status has been sended before) -> return";
        return;
    }
    qDebug()<<"set Status to Seen and send it";
    setStatus(TalkStatus::TalkStatusEnum::Seen);
    sendStatus();
}

void Post::getStatus()
{
    qWarning()<<"disabled";
//    QNetworkReply* r=getRequest(QString("api/Post/%1").arg(id()));
//    connect(r,&QNetworkReply::finished,this,&Post::onGetStatus);
}

void Post::onGetStatus()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError)
    {
        QJsonObject obj=jsonUtility()->convertToJsonObject(r->readAll());
        setStatus((TalkStatus::TalkStatusEnum)(obj.value("status").toInt()));
    }
    else if(isNotFound(r))
    {
        //TODO: delete message because this message has been removed from server
    }
}

void Post::deleteItem(bool deleteFromServer)
{
    if(deleteFromServer){
        setOperationType(OperationTypes::OperationTypesEnum::IsDeleting);
        QNetworkReply* r=deleteRequest("api/Post/"+id());
        connect(r,&QNetworkReply::finished,this,&Post::onDeleteItem);
    }
    else{
        emit deleteSucceed();
    }
}

void Post::onDeleteItem()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        showOkMessage(r->readAll());
        emit deleteSucceed();
    }
    else {
        showBadMessage(r->readAll());
    }
}

