#include "applicationalarmsettingshelper.h"

ApplicationAlarmSettingsHelper::ApplicationAlarmSettingsHelper(QObject *parent)
    : QObject{parent}
{
    m_hasAlarm = false;
    m_hasRepeat = false;
    m_alarmClass = AlarmClasses::AlarmClassesEnum::AlarmManager;
    m_notificationContent = "";
}

bool ApplicationAlarmSettingsHelper::hasAlarm() const
{
    return m_hasAlarm;
}

void ApplicationAlarmSettingsHelper::setHasAlarm(bool newHasAlarm)
{
    if (m_hasAlarm == newHasAlarm)
        return;
    m_hasAlarm = newHasAlarm;
    emit hasAlarmChanged();
}

bool ApplicationAlarmSettingsHelper::hasRepeat() const
{
    return m_hasRepeat;
}

void ApplicationAlarmSettingsHelper::setHasRepeat(bool newHasRepeat)
{
    if (m_hasRepeat == newHasRepeat)
        return;
    m_hasRepeat = newHasRepeat;
    emit hasRepeatChanged();
}

AlarmClasses::AlarmClassesEnum ApplicationAlarmSettingsHelper::alarmClass() const
{
    return m_alarmClass;
}

void ApplicationAlarmSettingsHelper::setAlarmClass(const AlarmClasses::AlarmClassesEnum &newAlarmClass)
{
    if (m_alarmClass == newAlarmClass)
        return;
    m_alarmClass = newAlarmClass;
    emit alarmClassChanged();
}

QString ApplicationAlarmSettingsHelper::notificationContent() const
{
    return m_notificationContent;
}

void ApplicationAlarmSettingsHelper::setNotificationContent(const QString &newNotificationContent)
{
    if (m_notificationContent == newNotificationContent)
        return;
    m_notificationContent = newNotificationContent;
    emit notificationContentChanged();
}
