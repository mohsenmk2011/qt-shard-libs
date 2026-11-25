#include "notificationclient.h"

NotificationClient::NotificationClient(QObject *parent) : QObject(parent)
{
    JooyaAndroidContext context;
    //m_NotificationJavaClassName=context.packageName()+"/NotificationClient";
    m_NotificationJavaClassName="org/jooya/bimehpardaz/NotificationClient";
}

QString NotificationClient::notification()
{
    return m_Notification;
}

void NotificationClient::setNotification(QString n)
{
    if(n!=m_Notification){
        m_Notification=n;
        emit notificationChanged();
        updateAndroidNotification();
    }
}

void NotificationClient::updateAndroidNotification()
{
#if defined(Q_OS_ANDROID)
    QJniObject javaNotification = QJniObject::fromString(m_Notification);
    QJniObject::callStaticMethod<void>(
                m_NotificationJavaClassName.toUtf8(),
                "notify",
                "(Ljava/lang/String;Ljava/lang/String;)V",
                javaNotification.object<jstring>());
#endif
}
