#ifndef ALARMMANAGER_H
#define ALARMMANAGER_H

#include <QObject>
#include<QDebug>
#include<QDateTime>
#include<alarminfo.h>
#if defined(Q_OS_ANDROID)
#include<QJniObject>
#include<QJniEnvironment>
#include<QCoreApplication>
#include <QtCore/private/qandroidextras_p.h>
#include<androidpermissionmanager.h>
#endif

class AlarmManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AlarmInfo* alarmInfo READ alarmInfo CONSTANT)
    Q_PROPERTY(bool isUpAndRunning READ isUpAndRunning WRITE setIsUpAndRunning NOTIFY isUpAndRunningChanged)
public:
    explicit AlarmManager(QObject *parent = nullptr);
    AlarmInfo* alarmInfo();

    bool isUpAndRunning();
    void setIsUpAndRunning(bool r);

    bool isTimeValid(int hour,int minute);
    Q_INVOKABLE void displayAlarmPage(QString alarmType="Notification", QString notificationContent="پیام هشدار");
    ///=====================================[alarm with alarm manager]=========================
    //is alarm up and running?
    Q_INVOKABLE bool isAlarmUp();
    Q_INVOKABLE bool startAlarmWithAlamManager(QString alarmType="Notification", QString notificationContent="پیام هشدار");
    Q_INVOKABLE void cancelAlarm();
    ///=====================================[alarm with work manager]=========================
    /// is alram that is set with work manager is in process ?
    Q_INVOKABLE bool isAlarmWorkUp();
    /// will set alarm with work manager
    Q_INVOKABLE bool startAlarmWithWorkManager(QString alarmType="Notification", QString notificationContent="پیام هشدار");
    /// cancle that alarm that is set with work manager
    Q_INVOKABLE bool cancelAlarmWork();
signals:
    void isUpAndRunningChanged();
private slots:
private:
    AlarmInfo* m_AlarmInfo;
    bool m_IsUpAndRunning;
    /// will return alarm interval in minutes in string format
    QString getIntervalInMintues();
};

#endif // ALARMMANAGER_H
