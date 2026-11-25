#ifndef NOTIFICATIONLIB_H
#define NOTIFICATIONLIB_H

#include <QObject>
#include<QtQml/QQmlApplicationEngine>
#include<keywordtypemanager.h>
#include<keywordtype.h>
#include<keywordmanager.h>
#include<keywordlistmodel.h>
#include<keyword.h>
#include<notify.h>
#include<notifymanager.h>
#include<notificationtypes.h>
#include<notificationcounts.h>
#include<notificationreceiver.h>
#include<notifylistmodel.h>

class Notificationlib
{
public:
    Notificationlib();
    static void registerTypes()
    {
        qmlRegisterType<KeywordTypeManager>("Jooya",1,0,"KeywordTypeManager");
        qmlRegisterType<KeywordType>("Jooya",1,0,"KeywordType");
        qmlRegisterType<KeywordTypeListModel>("Jooya",1,0,"KeywordTypeListModel");

        qmlRegisterType<Keyword>("Jooya",1,0,"Keyword");
        qmlRegisterType<KeywordManager>("Jooya",1,0,"KeywordManager");
        qmlRegisterType<KeywordListModel>("Jooya",1,0,"KeywordListModel");

        qmlRegisterType<NotifyManager>("Jooya",1,0,"NotifyManager");
        qmlRegisterType<Notify>("Jooya",1,0,"Notify");
        qmlRegisterType<NotifyListModel>("Jooya",1,0,"NotifyListModel");
        qmlRegisterType<NotificationTypes>("Jooya",1,0,"NotificationTypes");
        qmlRegisterType<NotificationCounts>("Jooya",1,0,"NotificationCounts");
        qmlRegisterType<NotificationReceiver>("Jooya",1,0,"NotificationReceiver");
    }

};

#endif // NOTIFICATIONLIB_H
