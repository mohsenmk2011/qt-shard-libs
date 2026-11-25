#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <QObject>
#include<websockethandler.h>
#include<QtQml>
#include<jooyanetwork.h>

class WebSocketManager : public QObject
{
    Q_OBJECT
    QML_ATTACHED(WebSocketHandler)
    QML_ANONYMOUS
public:
    static WebSocketHandler *qmlAttachedProperties(QObject *object){
        return JooyaNetwork::m_WebSocketHandler;
    }


};

#endif // WEBSOCKETMANAGER_H
