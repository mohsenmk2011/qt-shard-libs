#include "websocketinfo.h"

WebSocketInfo::WebSocketInfo(QObject *parent)
    : QObject{parent}
{
    m_Info="not set";
}

void WebSocketInfo::setInformation(QString info)
{
    if(m_Info!=info){
        m_Info=info;
        emit informationChanged();
    }
}

void WebSocketInfo::setType(QString t)
{
    if(m_Type!=t){
        m_Type=t;
        emit typeChanged();
    }
}

QString WebSocketInfo::type()
{
    return m_Type;
}

QString WebSocketInfo::receiverId()
{
    return m_ReceiverId;
}

void WebSocketInfo::setReceiverId(QString r)
{
    if(m_ReceiverId!=r){
        m_ReceiverId=r;
        emit receiverIdChanged();
    }
}

QString WebSocketInfo::information()
{
    return m_Info;
}

QString WebSocketInfo::senderId()
{
    return m_SenderId;
}

void WebSocketInfo::setSenderId(QString c)
{
    if(m_SenderId!=c){
        m_SenderId=c;
        emit senderIdChanged();
    }
}

QString WebSocketInfo::toJson()
{
    QJsonObject obj;
    obj.insert("type",type());
    obj.insert("information",information());
    obj.insert("senderId",senderId());
    obj.insert("receiverId",receiverId());
    QJsonDocument doc(obj);
    return doc.toJson(QJsonDocument::Compact);
}

void WebSocketInfo::fromJson(QString json)
{
    QJsonDocument doc=QJsonDocument::fromJson(json.toUtf8());
    QJsonObject obj=doc.object();

    QString t=doc.toJson(QJsonDocument::Compact);
    if(t.isNull()||t.isEmpty()){
        setInformation(json);
        qDebug()<<"Text=> "<<json;
        return;
    }
    setType(obj.value("type").toString());
    setInformation(obj.value("information").toString());
    setSenderId(obj.value("senderId").toString());
    setReceiverId(obj.value("receiverId").toString());
}
