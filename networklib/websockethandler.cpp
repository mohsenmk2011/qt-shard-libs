#include "websockethandler.h"

WebSocketHandler::WebSocketHandler(QObject *parent) : QObject{parent}
{
    m_OnlineUsers=0;
    m_PingPongTimer.setSingleShot(true);
    m_PingPongTimer.setInterval(45000);
    connect(&m_PingPongTimer,&QTimer::timeout,this,&WebSocketHandler::pingPongTimerTimeout);
    connect(&m_WebSocket, &QWebSocket::pong, this, &WebSocketHandler::onPong);


    connect(&m_WebSocket, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
    connect(&m_WebSocket, &QWebSocket::disconnected, this, &WebSocketHandler::onDisconnected);
    connect(&m_WebSocket,&QWebSocket::stateChanged,this,&WebSocketHandler::onSocketStateChanged);


    connect(&m_WebSocket, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageReceived);
//    connect(&m_WebSocket, &QWebSocket::textFrameReceived, this, &WebSocketHandler::onTextFrameReceived);
    connect(&m_WebSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketHandler::onBinaryMessageReceived);
    connect(&m_WebSocket, &QWebSocket::binaryFrameReceived, this, &WebSocketHandler::onBinaryFrameReceived);

    connect(&m_WebSocket, QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),this, &WebSocketHandler::onSslErrors);
//    QSslConfiguration sslconfig=m_WebSocket.sslConfiguration();
//    sslconfig.setPeerVerifyMode(QSslSocket::VerifyPeer);
//    m_WebSocket.setSslConfiguration(sslconfig);
//    m_WebSocket.ignoreSslErrors();
}

void WebSocketHandler::pingPongTimerTimeout()
{
    //APPSTEP:send ping to web socket
    qInfo()<<"sending ping to server";
    QByteArray payload=QByteArray("Hello Jooya");
    m_WebSocket.ping(payload);
}
void WebSocketHandler::onPong(quint64 elapsedTime, const QByteArray &payload)
{
    qInfo()<<"***[ Pong ]***";
    qInfo()<<"elapsedTime => "<<elapsedTime;
    qInfo()<<" payload => "<<payload;
    qInfo()<<" payload toString => "<<QString(payload);
    if(!m_PingPongTimer.isActive()){
        m_PingPongTimer.start();
    }
}

bool WebSocketHandler::connected()
{
    return m_Connected;
}

void WebSocketHandler::setConnected(bool c)
{
    if(m_Connected!=c){
        m_Connected=c;
        emit connectedChanged();
    }
}

WebSocketStates::WebSocketStatesEnum WebSocketHandler::state()
{
    return m_State;
}

void WebSocketHandler::setState(WebSocketStates::WebSocketStatesEnum s)
{
    if(m_State!=s){
        m_State=s;
        emit stateChanged();
    }
}

int WebSocketHandler::onlineUsers()
{
    return m_OnlineUsers;
}

void WebSocketHandler::setOnlineUsers(int o)
{
    if(m_OnlineUsers!=o){
        m_OnlineUsers=o;
        emit onlineUsersChanged();
    }
}

void WebSocketHandler::open()
{
    qInfo()<<"### [ Is going to open socket ] ###";
    if(!JooyaNetworkEngine::m_loginInfo->isLoggedIn()){
//        connect(&m_WebSocket, &QWebSocket::error, this, &WebSocketHandler::onError);
//        connect(m_WebSocket,QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),this,&WebSocketHandler::onError);
        m_WebSocket.open(m_Url);
        return;
    }
    /// Open with QQNetworkRequest so server can find the UserId from token
    QNetworkRequest r=QNetworkRequest();
    r.setUrl(m_Url);
    r.rawHeaderList().clear();
    r.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));

    QString token=JooyaNetworkEngine:: m_loginInfo->token();
    QString HeaderName="Authorization";
    QString HeaderValue="Bearer "+token;
    r.setRawHeader(HeaderName.toUtf8(),HeaderValue.toUtf8());

    m_WebSocket.open(r);
}

void WebSocketHandler::close()
{
    m_WebSocket.close(QWebSocketProtocol::CloseCodeNormal,"websocket is closed with user");

}

void WebSocketHandler::setUrl(QString url)
{
    m_Url=url;
}

bool WebSocketHandler::sendTextMessage(QString message)
{
    qInfo()<<"Text=> "<<message;
    qDebug()<<"connected()=> "<<connected();
    qint64 count= m_WebSocket.sendTextMessage(message);
    qInfo()<<"count of byte that sent=> "<<count;
    if(!count){
        qCritical()<<"@@@@@@@[ Erro In Sending Text ]@@@@@@@@";
        qCritical()<<"@@@[ Error=> "<<m_WebSocket.errorString()<<" ]@@@";
        qCritical()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        return false;
        qCritical()<<"@@@[ WebSocket was not send text ]@@@";
    }
    return true;
}

void WebSocketHandler::sendJsonObject(QString type, QString message)
{
    WebSocketInfo* wsi=new WebSocketInfo();
    wsi->setInformation(message);
    wsi->setType(type);
    sendTextMessage(wsi->toJson());
}

void WebSocketHandler::onConnected()
{
    qInfo()<<"***[ socket is connected ]***";
    setConnected(true);
    if(!m_PingPongTimer.isActive()){
        m_PingPongTimer.start();
    }
}

void WebSocketHandler::onError(QAbstractSocket::SocketError error)
{
    qInfo()<<"***[ Error ]***";

}

void WebSocketHandler::onDisconnected()
{
    qCritical()<<"***[ socket is disconnected ]***";
    m_WebSocket.close(QWebSocketProtocol::CloseCodeNormal,"websocket is closed with user");
    setConnected(false);
}


void WebSocketHandler::onSocketStateChanged(QAbstractSocket::SocketState state)
{
    qCritical()<<"****************************************";
    qCritical()<<"***[ Current state=> "<<state<<" ]***";
    qCritical()<<"****************************************";

    switch (state) {
    case QAbstractSocket::SocketState::UnconnectedState:
        setState(WebSocketStates::WebSocketStatesEnum::Unconnected);
        break;
    case QAbstractSocket::SocketState::HostLookupState:
        setState(WebSocketStates::WebSocketStatesEnum::HostLookup);
        break;
    case QAbstractSocket::SocketState::ConnectingState:
        setState(WebSocketStates::WebSocketStatesEnum::Connecting);
        break;
    case QAbstractSocket::SocketState::ConnectedState:
        setState(WebSocketStates::WebSocketStatesEnum::Connected);
        break;
    case QAbstractSocket::SocketState::BoundState:
        setState(WebSocketStates::WebSocketStatesEnum::Bound);
        break;
    case QAbstractSocket::SocketState::ListeningState:
        setState(WebSocketStates::WebSocketStatesEnum::Listening);
        break;
    case QAbstractSocket::SocketState::ClosingState:
        setState(WebSocketStates::WebSocketStatesEnum::Closing);
        break;
    default:
        setState(WebSocketStates::WebSocketStatesEnum::Unconnected);
        break;
    }
}

void WebSocketHandler::onSslErrors(const QList<QSslError> &erros)
{
    qCritical()<<" SslErrors.count => "<<erros.count();
    m_WebSocket.ignoreSslErrors();
    for (int i = 0; i < erros.count(); ++i) {
        qCritical()<<"=> "<<erros.at(i).errorString();
    }
}

void WebSocketHandler::onTextMessageReceived(const QString &message)
{
    qInfo()<<"message received reset ping timer=> ";
    if(m_PingPongTimer.isActive()){
        m_PingPongTimer.stop();
        m_PingPongTimer.start();
    }
    WebSocketInfo* wsi =new WebSocketInfo();
    wsi->fromJson(message);    
    emit newInfoReceived(wsi);
    JsonUtility ju;
    if(wsi->type()=="NewConnection"){
        NewConnectionModel* ncm=new NewConnectionModel(ju.convertToJsonObject(wsi->information()));
        setOnlineUsers(ncm->onlineUsersCount());
        if(ncm->isAdded()){
            emit newConnection(ncm->userId());
        }
        else
        {
            emit newDisconnection(ncm->userId());
        }
    }
}

void WebSocketHandler::onTextFrameReceived(const QString &frame, bool isLastFrame)
{
}

void WebSocketHandler::onBinaryMessageReceived(const QByteArray &frame)
{
    qDebug()<<"Binary Message Received => "<<frame;    
    QJsonDocument doc=QJsonDocument::fromJson(frame);
    QJsonObject obj=doc.object();
    qInfo()<<"json=>"<< doc.toJson(QJsonDocument::Compact);
}

void WebSocketHandler::onBinaryFrameReceived(const QByteArray &frame, bool isLastFrame)
{
    qDebug()<<"Binary Frame Received => "<<frame;
    qDebug()<<"isLastFrame =>"<<isLastFrame;

}

QString WebSocketHandler::m_Url="";
