#ifndef ANDROIDSERVICEMANAGER_H
#define ANDROIDSERVICEMANAGER_H

#include <QObject>
#include <QtDebug>
#include<QtQml>
#if defined(Q_OS_ANDROID)
#include<QJniObject>
#include<QJniEnvironment>
#include <QCoreApplication>
#include <QtCore/private/qandroidextras_p.h>
#include<packageinfomanager.h>
#endif

class AndroidServiceManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    AndroidServiceManager(QObject *parent = nullptr);

    static AndroidServiceManager *instance() { return m_instance; }
    Q_INVOKABLE void sendToService(const QString &message="StartQtService");
    Q_INVOKABLE void sendMessage(const QString &message);
    Q_INVOKABLE void startService();
    Q_INVOKABLE void stopService();
    /// is this class is running in servic
    bool isInService();
    /// is this class is running in qt app
    bool isInApp();

    void registerNativesOfApp();
    void unregisterNativesOfApp();

    void registerNativesOfService();
    void unregisterNativesOfService();

#if defined(Q_OS_ANDROID)
    QJniObject registerAppBroadcastReceiver();
    void unregisterAppBroadcastReceiver(QJniObject receiverObject);

    QJniObject registerServiceBroadcastReceiver();
    void unregisterServiceBroadcastReceiver(QJniObject receiverObject);
    // will register native methods and broadcast receiver based that is running on service or app
    QJniObject registerNativeMethodsAndBroadcastReceiver();
    void unregisterNativeMethodsAndBroadcastReceiver(QJniObject broadcastReceiver);
#endif
    void setServiceClassName(QString name);
    QString getServiceClassName();

    void setServiceBroadcastReceiverClassName(QString name);
    QString getServiceBroadcastReceiverClassName();

    void setAppBroadcastReceiverClassName(QString name);
    QString getAppBroadcastReceiverClassName();

signals:
    void appMessageReceived(const QString &appMessage);
    void serviceMessageReceived(const QString &message);

private:
    static AndroidServiceManager *m_instance;
    QString m_ServiceClassName;
    QString m_ServiceBroadcastReceiverClassName;
    QString m_AppBroadcastReceiverClassName;
};

#endif // ANDROIDSERVICEMANAGER_H
