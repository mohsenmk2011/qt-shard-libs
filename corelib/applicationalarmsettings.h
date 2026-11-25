#ifndef APPLICATIONALARMSETTINGS_H
#define APPLICATIONALARMSETTINGS_H

#include <QObject>
#include<applicationalarmsettingshelper.h>
#include<jooyaapplication.h>
#include<QtQml>

class ApplicationAlarmSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AlarmClasses::AlarmClassesEnum alarmClass READ alarmClass CONSTANT)
    QML_ATTACHED(ApplicationAlarmSettingsHelper)
    QML_ELEMENT
public:
    static ApplicationAlarmSettingsHelper *qmlAttachedProperties(QObject *object)
    {
        return JooyaApplication::m_ApplicationAlarmSettingsHelper;
    }
    AlarmClasses::AlarmClassesEnum alarmClass(){return AlarmClasses::AlarmClassesEnum::AlarmManager;}
};

#endif // APPLICATIONALARMSETTINGS_H
