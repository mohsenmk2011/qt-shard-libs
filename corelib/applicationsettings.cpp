#include "applicationsettings.h"

ApplicationSettings::ApplicationSettings(QObject *parent) : JooyaSettings(parent)
{

}

QString ApplicationSettings::alarmInfo()
{
    return get("alarmInfo").toString();
}

void ApplicationSettings::setAlarmInfo(QString ai)
{
    qInfo()<<"alarm info=> "<<ai;
    set("alarmInfo",ai);
}

QString ApplicationSettings::theme()
{
    return get("theme").toString();
}

void ApplicationSettings::setTheme(QString t)
{
    set("theme",t);
    emit themeChanged();
}

void ApplicationSettings::setDefaultTheme(QString t)
{
    set("DefaultTheme",t);
}

QString ApplicationSettings::defaultTheme()
{
    return get("DefaultTheme").toString();
}

QString ApplicationSettings::userInfo()
{
    return get("userInfo").toString();
}

void ApplicationSettings::setUserInfo(QString t)
{
    set("userInfo",t);
}

QString ApplicationSettings::lastTriedPaymentOrderId()
{
    return get("lastTriedPaymentOrderId").toString();
}

void ApplicationSettings::setLastTriedPaymentOrderId(QString id)
{
    set("lastTriedPaymentOrderId",id);
}

bool ApplicationSettings::seenAppIntroducing()
{
    return get("seenAppIntroducing").toBool();
}

void ApplicationSettings::setSeenAppIntroducing(bool seen)
{
    set("seenAppIntroducing",seen);
    void seenAppIntroducingChanged();
}
