#ifndef ANDROIDLIB_H
#define ANDROIDLIB_H

#include<QtQml/QQmlApplicationEngine>
#include<androidpermissionmanager.h>
#include<notificationclient.h>
#include<sharemanager.h>
#include<androidutility.h>
#include<smsmanager.h>
#include<alarmmanager.h>
#include<alarminfo.h>
#include<alarmtypes.h>
#include<androiddeeplinkmanager.h>
#include<intervalunits.h>
#include<packageinfomanager.h>

class Androidlib
{
public:
    static void registerTypes()
    {
        qmlRegisterType<AndroidUtility>("Jooya",1,0,"AndroidUtility");
        qmlRegisterType<AndroidPermissionManager>("Jooya",1,0,"AndroidPermissionManager");
        qmlRegisterType<NotificationClient>("Jooya",1,0,"NotificationClient");
        qmlRegisterType<AlarmManager>("Jooya",1,0,"AlarmManager");
        qmlRegisterType<AlarmInfo>("Jooya",1,0,"AlarmInfo");
        qmlRegisterType<ShareManager>("Jooya",1,0,"ShareManager");
        qmlRegisterType<SmsManager>("Jooya",1,0,"SmsManager");
        qmlRegisterType<AndroidDeepLinkManager>("Jooya",1,0,"AndroidDeepLinkManager");
        qmlRegisterType<PackageInfoManager>("Jooya",1,0,"PackageInfoManager");
        qmlRegisterUncreatableType<PermissionTypes>("Jooya",1,0,"PermissionTypes","Permission Types");
        qmlRegisterUncreatableType<AlarmTypes>("Jooya",1,0,"AlarmTypes","Alarm Types");
        qmlRegisterUncreatableType<IntervalUnits>("Jooya",1,0,"IntervalUnits","Interval Units");
    }
};

#endif // ANDROIDLIB_H
