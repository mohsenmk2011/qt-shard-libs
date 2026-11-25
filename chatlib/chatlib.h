#ifndef CHATLIB_H
#define CHATLIB_H

#include<QtQml/QQmlApplicationEngine>
#include<chat.h>
#include<chattypes.h>
#include<talklistmodel.h>
#include<talkstates.h>
#include<contactmanager.h>
#include<contact.h>
#include<contactlistmodel.h>
#include<chatlistmodel.h>
#include<chatmanager.h>
#include<tcpserver.h>
#include<postbase.h>
#include<post.h>

class Chatlib
{
public:
    Chatlib();
    static void registerTypes()
    {
        qmlRegisterType<Chat>("Jooya",1,0,"Chat");
        qmlRegisterType<PostBase>("Jooya",1,0,"PostBase");
        qmlRegisterType<Post>("Jooya",1,0,"Post");
        qmlRegisterType<TalkListModel>("Jooya",1,0,"TalkListModel");
        qmlRegisterUncreatableType<TalkStatus>("Jooya",1,0,"TalkStates","states of post");
        qmlRegisterUncreatableType<ChatTypes>("Jooya",1,0,"ChatTypes","kine of chat");
        qmlRegisterType<ChatListModel>("Jooya",1,0,"ChatListModel");
        qmlRegisterType<ChatManager>("Jooya",1,0,"ChatManager");
        qmlRegisterType<TcpServer>("Jooya",1,0,"TcpServer");
        qmlRegisterType<Contact>("Jooya",1,0,"Contact");
        qmlRegisterType<ContactManager>("Jooya",1,0,"ContactManager");
        qmlRegisterType<ContactListModel>("Jooya",1,0,"ContactListModel");
    }
};

#endif // CHATLIB_H
