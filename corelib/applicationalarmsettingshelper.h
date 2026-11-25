#ifndef APPLICATIONALARMSETTINGSHELPER_H
#define APPLICATIONALARMSETTINGSHELPER_H

#include <QObject>
#include<alarmclasses.h>
#include<QtQml>

class ApplicationAlarmSettingsHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasAlarm READ hasAlarm WRITE setHasAlarm NOTIFY hasAlarmChanged FINAL)
    Q_PROPERTY(bool hasRepeat READ hasRepeat WRITE setHasRepeat NOTIFY hasRepeatChanged FINAL)
    Q_PROPERTY(AlarmClasses::AlarmClassesEnum alarmClass READ alarmClass WRITE setAlarmClass NOTIFY alarmClassChanged FINAL)
    Q_PROPERTY(QString notificationContent READ notificationContent WRITE setNotificationContent NOTIFY notificationContentChanged FINAL)
    QML_ANONYMOUS
public:
    explicit ApplicationAlarmSettingsHelper(QObject *parent = nullptr);

    bool hasAlarm() const;
    void setHasAlarm(bool newHasAlarm);

    bool hasRepeat() const;
    void setHasRepeat(bool newHasRepeat);

    AlarmClasses::AlarmClassesEnum alarmClass() const;
    void setAlarmClass(const AlarmClasses::AlarmClassesEnum &newAlarmClass);

    QString notificationContent() const;
    void setNotificationContent(const QString &newNotificationContent);

signals:
    void hasAlarmChanged();
    void hasRepeatChanged();
    void alarmClassChanged();
    void notificationContentChanged();

private:
    bool m_hasAlarm;
    bool m_hasRepeat;
    AlarmClasses::AlarmClassesEnum m_alarmClass;
    QString m_notificationContent;
};

#endif // APPLICATIONALARMSETTINGSHELPER_H
