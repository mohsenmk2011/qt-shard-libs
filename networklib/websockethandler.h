#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include<QtWebSockets/QWebSocket>
#include<QNetworkRequest>
#include<jooyanetworkengine.h>
#include<QAbstractSocket>
#include<QtQml>
#include<QJsonObject>
#include<QJsonDocument>
#include<websocketinfo.h>
#include<QTimer>
#include<jsonutility.h>
#include<newconnectionmodel.h>
#include<websocketstates.h>

class WebSocketHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(int onlineUsers READ onlineUsers WRITE setOnlineUsers NOTIFY onlineUsersChanged)
    Q_PROPERTY(WebSocketStates::WebSocketStatesEnum state READ state WRITE setState NOTIFY stateChanged)
    QML_ELEMENT
public:
    explicit WebSocketHandler(QObject *parent = nullptr);

    bool connected();
    void setConnected(bool c);

    WebSocketStates::WebSocketStatesEnum state();
    void setState(WebSocketStates::WebSocketStatesEnum s);

    int onlineUsers();
    void setOnlineUsers(int o);

    static void setUrl(QString url);
    Q_INVOKABLE bool sendTextMessage(QString message);
    void sendJsonObject(QString type, QString message);
    Q_INVOKABLE void open();
    Q_INVOKABLE void close();
signals:
    void connectedChanged();
    void stateChanged();
    void newInfoReceived(WebSocketInfo* newInfo);
    void onlineUsersChanged();
    void newConnection(QString uerId);
    void newDisconnection(QString userId);
private slots:
    void onConnected();
    void onError(QAbstractSocket::SocketError error);
    void onDisconnected();
    void pingPongTimerTimeout();
    void onSocketStateChanged(QAbstractSocket::SocketState state);
    void onSslErrors(const QList<QSslError> &erros);
    void onTextMessageReceived(const QString &message);
    void onTextFrameReceived(const QString &frame,bool isLastFrame);
    void onBinaryMessageReceived(const QByteArray &frame);
    void onBinaryFrameReceived(const QByteArray &frame,bool isLastFrame);
    void onPong(quint64 elapsedTime, const QByteArray &payload);
private:
    QWebSocket m_WebSocket;
    static QString m_Url;
    bool m_Connected;
    WebSocketStates::WebSocketStatesEnum m_State;
    int m_OnlineUsers;
    QTimer m_PingPongTimer;

};

#endif // WEBSOCKETHANDLER_H
