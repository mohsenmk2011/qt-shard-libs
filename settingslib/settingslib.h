#ifndef SETTINGSLIB_H
#define SETTINGSLIB_H

#include<QtQml/QQmlApplicationEngine>
#include<smssettings.h>
#include<behpardakhtsetting.h>
class Settingslib
{
public:
    Settingslib();
    static void registerTypes()
    {
        qmlRegisterType<BehpardakhtSetting>("Jooya",1,0,"BehpardakhtSetting");
        qmlRegisterType<SmsSettings>("Jooya",1,0,"SmsSettings");
    }
};

#endif // SETTINGSLIB_H
