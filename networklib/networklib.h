#ifndef NETWORKLIB_H
#define NETWORKLIB_H

#include <QObject>
#include<QtQml/QQmlApplicationEngine>
#include<jooyanetwork.h>
#include<listmanager.h>
#include<downloadmanager.h>
#include<file.h>
#include<imagefile.h>
#include<websockethandler.h>
#include<websocketmanager.h>
#include<websocketinfo.h>
#include<jooyalistitem.h>
#include<filedownloadstates.h>
#include<websocketstates.h>
#include<fileexplorer.h>
#include<fileuploadstatus.h>
#include<headercontenttypes.h>

class Networklib
{
public:
    Networklib();
    static void registerTypes()
    {
        qmlRegisterType<JooyaListItem>("Jooya",1,0,"JooyaListItem");
        qmlRegisterType<JooyaNetwork>("Jooya",1,0,"JooyaNetwork");
        qmlRegisterType<ListManager>("Jooya",1,0,"ListManager");
        qmlRegisterType<DownloadManager>("Jooya",1,0,"DownloadManager");
        qmlRegisterType<File>("Jooya",1,0,"File");
        qmlRegisterType<ImageFile>("Jooya",1,0,"ImageFile");
        qmlRegisterType<WebSocketHandler>("Jooya",1,0,"WebSocketHandler");
        qmlRegisterType<WebSocketManager>("Jooya",1,0,"WebSocketManager");
        qmlRegisterType<WebSocketInfo>("Jooya",1,0,"WebSocketInfo");
        qmlRegisterType<FileExplorer>("Jooya",1,0,"FileExplorer");
        qmlRegisterUncreatableType<WebSocketStates>("Jooya",1,0,"WebSocketStates","states of WebSocket");

        qmlRegisterUncreatableType<FileDownloadStates>("Jooya",1,0,"FileDownloadStates","File Download States");
        qmlRegisterUncreatableType<FileUploadStatus>("Jooya",1,0,"FileUploadStatus","File upload status");
        qmlRegisterUncreatableType<HeaderContentTypes>("Jooya",1,0,"HeaderContentTypes","Header Content Types");
    }
};

#endif // NETWORKLIB_H
