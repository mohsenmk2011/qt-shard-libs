#ifndef NOTIFICATIONCLIENT_H
#define NOTIFICATIONCLIENT_H

#include <QObject>
#include<jooyaandroidcontext.h>

#if defined(Q_OS_ANDROID)
#include <QCoreApplication>
#include<QJniEnvironment>
#include<QJniObject>
#endif

class NotificationClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString notification READ notification WRITE setNotification NOTIFY notificationChanged)
public:
    explicit NotificationClient(QObject *parent = nullptr);

    QString notification();
    void setNotification(QString n);
signals:
    void notificationChanged();
private:
    QString m_Notification;
    QString m_NotificationJavaClassName;
    void updateAndroidNotification();
};

#endif // NOTIFICATIONCLIENT_H
