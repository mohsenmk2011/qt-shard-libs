#ifndef CORELIB_H
#define CORELIB_H

#include <QObject>
#include<message.h>
#include<jooyanetworkengine.h>
#include<imageutility.h>
#include<applicationpath.h>
#include<jooyasettings.h>
#include<applicationsettings.h>
#include<QtQml/QQmlApplicationEngine>
#include<userroles.h>
#include<currentuser.h>
#include<userlogininfo.h>
#include<messageboard.h>

#include<materialstylehelper.h>
#include<materialstyle.h>
#include<materialcolor.h>
#include<materialcolors.h>
#include<materialshades.h>
#include<materialthemes.h>
#include<operationtypes.h>
#include<persiandatetime.h>
#include<apppagesmanager.h>
#include<qmllive.h>
#include<filewatcher.h>
#include<QQmlEngine>
#include<datetimeutility.h>
#include<urlutility.h>
#include<isoscelestrianglemath.h>
#include<currentapplication.h>
#include<currentapplicationhelper.h>
#include<alarmclasses.h>
#include<applicationalarmsettings.h>
#include<applicationalarmsettingshelper.h>
#include<androidservicemanager.h>

class Corelib
{
public:
    Corelib();
    static void registerTypes()
    {
        qmlRegisterType<UserRoles>("Jooya",1,0,"UserRoles");
        qmlRegisterType<Message>("Jooya",1,0,"Message");
        qmlRegisterType<UserLoginInfo>("Jooya",1,0,"UserLoginInfo");
        qmlRegisterType<ApplicationPath>("Jooya",1,0,"ApplicationPath");
        qmlRegisterType<JooyaNetworkEngine>("Jooya",1,0,"JooyaNetworkEngine");
        qmlRegisterType<FileUtility>("Jooya",1,0,"JooyaFile");
        qmlRegisterType<ImageUtility>("Jooya",1,0,"ImageUtility");
        qmlRegisterType<JooyaSettings>("Jooya",1,0,"JooyaSettings");
        qmlRegisterType<ApplicationSettings>("Jooya",1,0,"ApplicationSettings");
        qmlRegisterType<CurrentUser>("Jooya",1,0,"CurrentUser");
        qmlRegisterType<AndroidServiceManager>("Jooya",1,0,"AndroidServiceManager");
        qmlRegisterType<MessageBoard>("Jooya",1,0,"MessageBoard");
        qmlRegisterType<AppPagesManager>("Jooya",1,0,"AppPagesManager");
        qmlRegisterType<QmlLive>("Jooya",1,0,"QmlLive");
        qmlRegisterType<FileWatcher>("Jooya",1,0,"FileWatcher");
        qmlRegisterType<DateTimeUtility>("Jooya",1,0,"DateTimeUtility");
        qmlRegisterType<UrlUtility>("Jooya",1,0,"UrlUtility");
        qmlRegisterType<IsoscelesTriangleMath>("Jooya",1,0,"IsoscelesTriangleMath");

        qmlRegisterType<PersianDateTime>("Jooya",1,0,"PersianDateTime");

        qmlRegisterType<MaterialStyleHelper>("JooyaQuick.Controls.Material",1,0,"MaterialStyleHelper");
        qmlRegisterType<MaterialStyle>("JooyaQuick.Controls.Material",1,0,"MaterialStyle");
        qmlRegisterType<MaterialColor>("JooyaQuick.Controls.Material",1,0,"MaterialColor");


        qmlRegisterType<CurrentApplication>("Jooya",1,0,"CurrentApplication");
        qmlRegisterType<CurrentApplicationHelper>("Jooya",1,0,"CurrentApplicationHelper");

        qmlRegisterUncreatableType<OperationTypes>("Jooya",1,0,"OperationTypes","Operation Types");
        qmlRegisterType<AlarmClasses>("Jooya",1,0,"AlarmClasses");
        qmlRegisterType<ApplicationAlarmSettingsHelper>("Jooya",1,0,"ApplicationAlarmSettingsHelper");
        qmlRegisterType<ApplicationAlarmSettings>("Jooya",1,0,"ApplicationAlarmSettings");

        qmlRegisterUncreatableType<MaterialColors>("JooyaQuick.Controls.Material",1,0,"MaterialColors","Material Colors");
        qmlRegisterUncreatableType<MaterialShades>("JooyaQuick.Controls.Material",1,0,"MaterialShades","Material Shades");
        qmlRegisterUncreatableType<MaterialThemes>("JooyaQuick.Controls.Material",1,0,"MaterialThemes","Material Themes");
    }
};

#endif // CORELIB_H
