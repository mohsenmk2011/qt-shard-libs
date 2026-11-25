#include "androidservicemanager.h"

AndroidServiceManager *AndroidServiceManager::m_instance = nullptr;

#if defined(Q_OS_ANDROID)
static void appMessagereceivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString message=env->GetStringUTFChars(value, nullptr);
    qInfo()<<"***[ Application Message Received From Service ]***";
    qInfo()<<"***[ the message=> ]***"<<message;
    if(AndroidServiceManager::instance()==nullptr)
    {
        qCritical()<<"***[ AndroidServiceManager::instance() was null]***";
        return;
    }
    emit AndroidServiceManager::instance()->appMessageReceived(message);
}

static void serviceMessagereceivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString message=env->GetStringUTFChars(value, nullptr);
    qInfo()<<"***[ Service Message Received From Service ]***";
    qInfo()<<"***[ the message=> ]***"<<message;
    if(AndroidServiceManager::instance()==nullptr)
    {
        qCritical()<<"***[ AndroidServiceManager::instance() was null]***";
        return;
    }
    emit AndroidServiceManager::instance()->serviceMessageReceived(message);
}
#endif

AndroidServiceManager::AndroidServiceManager(QObject *parent) : QObject(parent)
{
    m_ServiceClassName = "";
    m_ServiceBroadcastReceiverClassName = "";
    m_AppBroadcastReceiverClassName = "";
    m_instance = this;
}

void AndroidServiceManager::sendToService(const QString &message)
{
#if defined(Q_OS_ANDROID)
    if(getServiceClassName().isNull()||getServiceClassName().isEmpty())
    {
        qCritical() <<"send message faild => serivce class name is null";
        return;
    }
    if(isInApp())
    {
        qDebug()<<"is sending message from qt app to service => "<< message;
    }
    else
    {
        qDebug()<<"is sending message from service to qt app => "<< message;
    }
    QJniObject activity = QJniObject(QNativeInterface::QAndroidApplication::context());

    QString serviceClassPath = PackageInfoManager::getPackageName()+getServiceClassName();
    QAndroidIntent serviceIntent(activity.object(), serviceClassPath.toUtf8());
    serviceIntent.putExtra("ServiceClassName", getServiceClassName().toUtf8());
    QString isInServiceString = isInService()?"Yes":"No";
    serviceIntent.putExtra("IsInService",isInServiceString.toUtf8());
    serviceIntent.putExtra("MessageFromQt", message.toUtf8());
    QJniObject result = activity.callObjectMethod(
        "startService",
        "(Landroid/content/Intent;)Landroid/content/ComponentName;",
        serviceIntent.handle().object());
#endif
}

void AndroidServiceManager::sendMessage(const QString &message)
{
#if defined (Q_OS_ANDROID)
    QJniObject javaMessage = QJniObject::fromString(message);
    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    if (activity.isValid()) {
        activity.callObjectMethod("printFromJava", "org/jooya/rokhshid/QtAndroidService", javaMessage.object<jstring>());

        //        if (window.isValid()) {
        //            const int FLAG_KEEP_SCREEN_ON = 128;
        //            window.callObjectMethod("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
        //        }
    }

#endif
}

void AndroidServiceManager::startService()
{
#if defined(Q_OS_ANDROID)
    // QJniObject::callStaticMethod<void>(
    //     "org/jooya/rokhshid/QtAndroidService",
    //     "startQtAndroidService",
    //     "(Landroid/content/Context;)V",
    //     QNativeInterface::QAndroidApplication::context());
    sendToService("StartService");
#endif
}

void AndroidServiceManager::stopService()
{
#if defined(Q_OS_ANDROID)

    //    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
    //                                 "org/jooya/rokhshid/QtAndroidService");
    //    QJniObject result = QtAndroid::androidActivity().callObjectMethod(
    //                "stopService",
    //                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
    //                serviceIntent.handle().object());

    sendToService("StopService");
#endif
}

bool AndroidServiceManager::isInService()
{
    bool t = !isInApp();
    //qDebug()<<"is in Service => "<<t;
    return t;
}

bool AndroidServiceManager::isInApp()
{
    bool t = false;
#if defined(Q_OS_ANDROID)
    t = QNativeInterface::QAndroidApplication::isActivityContext();
    //qDebug()<<"is in Qt App => "<<t;
    return t;
#endif
    return t;
}

void AndroidServiceManager::registerNativesOfApp()
{
#if defined(Q_OS_ANDROID)
    if(getAppBroadcastReceiverClassName().isNull()||getAppBroadcastReceiverClassName().isEmpty())
    {
        qCritical() <<"register app native methods faild,app broadcast receiver class name was null";
        return;
    }
    JNINativeMethod methods[] {
        {"sendToQtApp", "(Ljava/lang/String;)V", reinterpret_cast<void *>(appMessagereceivedFromAndroidService)},
    };
    QString appBroadcastClassName = PackageInfoManager::getPackageName()+getAppBroadcastReceiverClassName();
    QJniObject javaClass(appBroadcastClassName.toUtf8());

    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
#endif
}

void AndroidServiceManager::unregisterNativesOfApp()
{
#if defined(Q_OS_ANDROID)
    if(getAppBroadcastReceiverClassName().isNull()||getAppBroadcastReceiverClassName().isEmpty())
    {
        qCritical() <<"register app native methods faild,app broadcast receiver class name was null";
        return;
    }
    QString appBroadcastClassName = PackageInfoManager::getPackageName()+getAppBroadcastReceiverClassName();
    QJniObject javaClass(appBroadcastClassName.toUtf8());

    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->UnregisterNatives(objectClass);
    env->DeleteLocalRef(objectClass);
#endif
}

void AndroidServiceManager::registerNativesOfService()
{
#if defined(Q_OS_ANDROID)
    if(getServiceBroadcastReceiverClassName().isNull()||getServiceBroadcastReceiverClassName().isEmpty())
    {
        qCritical() <<"register service native methods faild,service broadcast receiver class name was null";
        return;
    }
    JNINativeMethod methods[] {
        {"sendToCPPService", "(Ljava/lang/String;)V", reinterpret_cast<void *>(serviceMessagereceivedFromAndroidService)},
    };
    QString serviceBroadcastClassName = PackageInfoManager::getPackageName()+getServiceBroadcastReceiverClassName();
    QJniObject javaClass(serviceBroadcastClassName.toUtf8());

    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
#endif
}

void AndroidServiceManager::unregisterNativesOfService()
{
#if defined(Q_OS_ANDROID)
    if(getServiceBroadcastReceiverClassName().isNull()||getServiceBroadcastReceiverClassName().isEmpty())
    {
        qCritical() <<"register service native methods faild,service broadcast receiver class name was null";
        return;
    }
    QString serviceBroadcastClassName = PackageInfoManager::getPackageName()+getServiceBroadcastReceiverClassName();
    QJniObject javaClass(serviceBroadcastClassName.toUtf8());

    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->UnregisterNatives(objectClass);
    env->DeleteLocalRef(objectClass);
#endif
}
#if defined(Q_OS_ANDROID)
QJniObject AndroidServiceManager::registerAppBroadcastReceiver()
{
#if defined(Q_OS_ANDROID)
    if(getAppBroadcastReceiverClassName().isNull()||getAppBroadcastReceiverClassName().isEmpty())
    {
        qCritical() <<"register app broadcast receiver faild,app broadcast receiver class name was null";
        return NULL;
    }
    QJniEnvironment env;
    // ex :"org/jooya/my_app_name/AppBroadcastUtility"
    QString appBroadcastClassName = PackageInfoManager::getPackageName()+getAppBroadcastReceiverClassName();
    jclass javaClass = env.findClass(appBroadcastClassName.toUtf8());
    QJniObject classObject(javaClass);

    classObject.callMethod<void>("registerServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QNativeInterface::QAndroidApplication::context());
    return classObject;
#endif
    return NULL;
}

void AndroidServiceManager::unregisterAppBroadcastReceiver(QJniObject receiverObject)
{
#if defined(Q_OS_ANDROID)
    if(receiverObject == NULL)
    {
        qCritical() <<"un register app broadcast receiver faild,app broadcast receiver object was null";
        return;
    }
    receiverObject.callMethod<void>("unregisterServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QNativeInterface::QAndroidApplication::context());
#endif
}

QJniObject AndroidServiceManager::registerServiceBroadcastReceiver()
{
#if defined(Q_OS_ANDROID)
    if(getServiceBroadcastReceiverClassName().isNull()||getServiceBroadcastReceiverClassName().isEmpty())
    {
        qCritical() <<"register service broadcast receiver faild,service broadcast receiver class name was null";
        return NULL;
    }
    QJniEnvironment env;
    QString serviceBroadcastClassName = PackageInfoManager::getPackageName()+getServiceBroadcastReceiverClassName();
    jclass javaClass = env.findClass(serviceBroadcastClassName.toUtf8());
    QJniObject classObject(javaClass);

    classObject.callMethod<void>("registerServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QNativeInterface::QAndroidApplication::context());
    return classObject;
#endif
    return NULL;
}

void AndroidServiceManager::unregisterServiceBroadcastReceiver(QJniObject receiverObject)
{
#if defined(Q_OS_ANDROID)
    if(receiverObject == NULL)
    {
        qCritical() <<"un register service broadcast receiver faild,service broadcast receiver object was null";
        return;
    }
    receiverObject.callMethod<void>("unregisterServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QNativeInterface::QAndroidApplication::context());
#endif
}

QJniObject AndroidServiceManager::registerNativeMethodsAndBroadcastReceiver()
{
    QJniObject r = NULL;
#if defined(Q_OS_ANDROID)
    if(isInService())
    {
        qInfo() << "%%%%%%%%[ => registerServiceBroadcastReceiver  ]%%%%%%%%%%%%";
        r = registerServiceBroadcastReceiver();
        qInfo() << "%%%%%%%%[ registerNativesOfService();  ]%%%%%%%%%%%%";
        registerNativesOfService();
    }
    else
    {
        qInfo() << "%%%%%%%%[ registerAppBroadcastReceiver();  ]%%%%%%%%%%%%";
        r = registerAppBroadcastReceiver();
        qInfo() << "%%%%%%%%[ registerNativesOfApp();  ]%%%%%%%%%%%%";
        registerNativesOfApp();
    }
#endif
    return r;
}

void AndroidServiceManager::unregisterNativeMethodsAndBroadcastReceiver(QJniObject broadcastReceiver)
{
#if defined(Q_OS_ANDROID)
    if(isInService())
    {
        qInfo() << "%%%%%%%%[ => un registerServiceBroadcastReceiver  ]%%%%%%%%%%%%";
        unregisterServiceBroadcastReceiver(broadcastReceiver);
        qInfo() << "%%%%%%%%[ un registerNativesOfService();  ]%%%%%%%%%%%%";
        unregisterNativesOfService();
    }
    else
    {
        qInfo() << "%%%%%%%%[ un registerAppBroadcastReceiver();  ]%%%%%%%%%%%%";
        unregisterAppBroadcastReceiver(broadcastReceiver);
        qInfo() << "%%%%%%%%[ un registerNativesOfApp();  ]%%%%%%%%%%%%";
        unregisterNativesOfApp();
    }
#endif
}
#endif
void AndroidServiceManager::setServiceClassName(QString name)
{
    m_ServiceClassName = name;
}

QString AndroidServiceManager::getServiceClassName()
{
    return m_ServiceClassName;
}

void AndroidServiceManager::setServiceBroadcastReceiverClassName(QString name)
{
    m_ServiceBroadcastReceiverClassName = name;
}

QString AndroidServiceManager::getServiceBroadcastReceiverClassName()
{
    return m_ServiceBroadcastReceiverClassName;
}

void AndroidServiceManager::setAppBroadcastReceiverClassName(QString name)
{
    m_AppBroadcastReceiverClassName = name;
}

QString AndroidServiceManager::getAppBroadcastReceiverClassName()
{
    return m_AppBroadcastReceiverClassName;
}
