#include "androidpermissionmanager.h"

AndroidPermissionManager::AndroidPermissionManager(QObject *parent)
{

}

void AndroidPermissionManager::addPermission(PermissionTypes::PermissionTypesEnum permission)
{
    m_PermissionList<<convertToString(permission);
}

QString AndroidPermissionManager::convertToString(PermissionTypes::PermissionTypesEnum permission)
{
    switch (permission) {
    case PermissionTypes::PermissionTypesEnum::READ_EXTERNAL_STORAGE:
        return "android.permission.READ_EXTERNAL_STORAGE";
    case PermissionTypes::PermissionTypesEnum::WRITE_EXTERNAL_STORAGE:
        return "android.permission.WRITE_EXTERNAL_STORAGE";

    case PermissionTypes::PermissionTypesEnum::READ_MEDIA_AUDIO:
        return "android.permission.READ_MEDIA_AUDIO";
    case PermissionTypes::PermissionTypesEnum::READ_MEDIA_IMAGES:
        return "android.permission.READ_MEDIA_IMAGES";
    case PermissionTypes::PermissionTypesEnum::READ_MEDIA_VIDEO:
        return "android.permission.READ_MEDIA_VIDEO";

    case PermissionTypes::PermissionTypesEnum::INTERNET:
        return "android.permission.INTERNET";
    case PermissionTypes::PermissionTypesEnum::ACCESS_NETWORK_STATE:
        return "android.permission.ACCESS_NETWORK_STATE";
    case PermissionTypes::PermissionTypesEnum::ACCESS_WIFI_STATE:
        return "android.permission.ACCESS_WIFI_STATE";

    case PermissionTypes::PermissionTypesEnum::DELETE_PACKAGES:
        return "android.permission.DELETE_PACKAGES";
    case PermissionTypes::PermissionTypesEnum::INSTALL_PACKAGES:
        return "android.permission.INSTALL_PACKAGES";

    case PermissionTypes::PermissionTypesEnum::CAMERA:
        return "android.permission.CAMERA";
    case PermissionTypes::PermissionTypesEnum::RECEIVE_BOOT_COMPLETED:
        return "android.permission.RECEIVE_BOOT_COMPLETED";
    case PermissionTypes::PermissionTypesEnum::FOREGROUND_SERVICE:
        return "android.permission.FOREGROUND_SERVICE";

    case PermissionTypes::PermissionTypesEnum::RECEIVE_SMS:
        return "android.permission.RECEIVE_SMS";
    case PermissionTypes::PermissionTypesEnum::READ_SMS:
        return "android.permission.READ_SMS";
    case PermissionTypes::PermissionTypesEnum::RECEIVE_MMS:
        return "android.permission.RECEIVE_MMS";
    case PermissionTypes::PermissionTypesEnum::SEND_SMS:
        return "android.permission.SEND_SMS";
    case PermissionTypes::PermissionTypesEnum::RECEIVE_WAP_PUSH:
        return "android.permission.RECEIVE_WAP_PUSH";

    case PermissionTypes::PermissionTypesEnum::SET_ALARM:
        return "com.android.alarm.permission.SET_ALARM";
    case PermissionTypes::PermissionTypesEnum::SCHEDULE_EXACT_ALARM:
        return "android.permission.SCHEDULE_EXACT_ALARM";
    case PermissionTypes::PermissionTypesEnum::WAKE_LOCK:
        return "android.permission.WAKE_LOCK";
    case PermissionTypes::PermissionTypesEnum::POST_NOTIFICATIONS:
        return "android.permission.POST_NOTIFICATIONS";
    case PermissionTypes::PermissionTypesEnum::USE_FULL_SCREEN_INTENT:
        return "android.permission.USE_FULL_SCREEN_INTENT";
    case PermissionTypes::PermissionTypesEnum::REQUEST_IGNORE_BATTERY_OPTIMIZATIONS:
        return "android.permission.REQUEST_IGNORE_BATTERY_OPTIMIZATIONS";
    case PermissionTypes::PermissionTypesEnum::VIBRATE:
        return "android.permission.VIBRATE";
    case PermissionTypes::PermissionTypesEnum::USE_EXACT_ALARM:
        return "android.permission.USE_EXACT_ALARM";
    case PermissionTypes::PermissionTypesEnum::DISABLE_KEYGUARD:
        return "android.permission.DISABLE_KEYGUARD";
    case PermissionTypes::PermissionTypesEnum::SYSTEM_ALERT_WINDOW:
        return "android.permission.SYSTEM_ALERT_WINDOW";

    default: return "";
    }
}

bool AndroidPermissionManager::isPermissionGranted(PermissionTypes::PermissionTypesEnum permission){
    return isPermissionGranted(convertToString(permission));
}

bool AndroidPermissionManager::isPermissionGranted(QString permission)
{
#if defined(Q_OS_ANDROID)
    QtAndroidPrivate::PermissionResult r= QtAndroidPrivate::checkPermission(permission).result();
    if(r==QtAndroidPrivate::PermissionResult::Denied){
        qCritical()<<"permission was not greanted";
        return false;
    }
    else {
        qInfo()<<"permission was greanted";
        return true;
    }
    return true;
#else
    return  true;
#endif
}

bool AndroidPermissionManager::requestStorage()
{
#if defined(Q_OS_ANDROID)
    m_PermissionList.clear();
    if(QtAndroidPrivate::androidSdkVersion()>=33) //android 13+
    {
        qDebug()<<"get gallery storage permission => ";
        addPermission(PermissionTypes::PermissionTypesEnum::READ_MEDIA_IMAGES);
        addPermission(PermissionTypes::PermissionTypesEnum::READ_MEDIA_VIDEO);
        addPermission(PermissionTypes::PermissionTypesEnum::READ_MEDIA_AUDIO);
    }
    else //android 6-12
    {
        qDebug()<<"get storage permission => ";
        // still works until Android 12 (API 31), but even there, if you only access your app’s private storage, you don’t need it.
        addPermission(PermissionTypes::PermissionTypesEnum::READ_EXTERNAL_STORAGE);
        // ignored for apps targeting API 30+ (Android 11). No dialog will show, because Google deprecated it
        addPermission(PermissionTypes::PermissionTypesEnum::WRITE_EXTERNAL_STORAGE);
        // it is automatically granted at install time
        // addPermission(PermissionTypes::PermissionTypesEnum::INTERNET);
    }
    return requestPermissions();
#else
    return  true;
#endif
}

bool AndroidPermissionManager::requestSms()
{
    qDebug()<<"get sms permission => ";
    m_PermissionList.clear();
    addPermission(PermissionTypes::PermissionTypesEnum::RECEIVE_SMS);
    addPermission(PermissionTypes::PermissionTypesEnum::RECEIVE_MMS);
    addPermission(PermissionTypes::PermissionTypesEnum::SEND_SMS);
    addPermission(PermissionTypes::PermissionTypesEnum::READ_SMS);
    addPermission(PermissionTypes::PermissionTypesEnum::RECEIVE_WAP_PUSH);
    return requestPermissions();
}

bool AndroidPermissionManager::requestCamera()
{
    addPermission(PermissionTypes::PermissionTypesEnum::CAMERA);
    return requestPermissions();
}

bool AndroidPermissionManager::requestSetAlarm()
{
    qDebug()<<"is requesting permissions for set alarm";
    addPermission(PermissionTypes::PermissionTypesEnum::USE_FULL_SCREEN_INTENT);//
    addPermission(PermissionTypes::PermissionTypesEnum::POST_NOTIFICATIONS);//
    addPermission(PermissionTypes::PermissionTypesEnum::WAKE_LOCK);//
    addPermission(PermissionTypes::PermissionTypesEnum::REQUEST_IGNORE_BATTERY_OPTIMIZATIONS);
    addPermission(PermissionTypes::PermissionTypesEnum::VIBRATE);//
    addPermission(PermissionTypes::PermissionTypesEnum::RECEIVE_WAP_PUSH);//
    addPermission(PermissionTypes::PermissionTypesEnum::SET_ALARM);//
    addPermission(PermissionTypes::PermissionTypesEnum::DISABLE_KEYGUARD);
    //https://developer.android.com/training/scheduling/alarms#exact-permission-declare
    //if your app targets api 31(anndroid 12(S)) and later you need to grantd
    //https://developer.android.com/reference/android/Manifest.permission#SCHEDULE_EXACT_ALARM
    addPermission(PermissionTypes::PermissionTypesEnum::SCHEDULE_EXACT_ALARM);
    addPermission(PermissionTypes::PermissionTypesEnum::USE_EXACT_ALARM);//android 13 and later
    return requestPermissions();
}

bool AndroidPermissionManager::requestSetAlertWindow()
{
    //How to grant ? -> https://developer.android.com/reference/android/Manifest.permission#SYSTEM_ALERT_WINDOW
    qWarning()<<"TODO: not implemented";
    addPermission(PermissionTypes::PermissionTypesEnum::SYSTEM_ALERT_WINDOW);
    return requestPermissions();
}

bool AndroidPermissionManager::requestIgnoringBatteryOptimizations()
{
    bool isIgnored=false;
    qInfo()<<"***[ check Battery Optimization ]***";
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        QString className = PackageInfoManager::getPackageName()+"PermissionManager";
        isIgnored = (bool) QJniObject::callStaticMethod<jboolean>(className.toUtf8(),"requestIgnoringBatteryOptimizations","(Landroid/content/Context;)Z",QNativeInterface::QAndroidApplication::context());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
    return isIgnored;
}

bool AndroidPermissionManager::requestSetExactAlarmPermission()
{
    bool isIgnored=false;
    qInfo()<<"***[ check SetExactAlarm Permission ]***";
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        QString className = PackageInfoManager::getPackageName()+"PermissionManager";
        isIgnored = (bool) QJniObject::callStaticMethod<jboolean>(className.toUtf8(),"requestSetExactAlarmPermission","(Landroid/content/Context;)Z",QNativeInterface::QAndroidApplication::context());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
    return isIgnored;
}

bool AndroidPermissionManager::requestPermissions()
{
#if defined(Q_OS_ANDROID)
    qDebug()<<"is going to request permissions => count="<<m_PermissionList.count();;
    for (int i = 0; i < m_PermissionList.count(); ++i) {
        qDebug()<<"check this permission => "<<m_PermissionList.at(i);
        if(!isPermissionGranted(m_PermissionList.at(i)))
        {
            qDebug()<<"not granted so request it => ";
            QtAndroidPrivate::PermissionResult rs= QtAndroidPrivate::requestPermission(m_PermissionList.at(i)).result();

            if(rs==QtAndroidPrivate::PermissionResult::Denied){
                qCritical()<<" => after requesting => Denied";
                return false;
            }
            else{
                qInfo()<<" => after requesting =>  Greanted";
            }
        }
    }
    return  true;
#else
    return  true;
#endif
}
