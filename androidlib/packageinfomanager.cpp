#include "packageinfomanager.h"

PackageInfoManager::PackageInfoManager(QObject *parent)
    : QObject{parent}
{

}

QString PackageInfoManager::getAppSign()
{
    qInfo()<<"is going to get the application signature";
#if defined(Q_OS_ANDROID)
    {
        QJniEnvironment env;
        QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
        if (activity.isValid())
        {
            QJniObject context = QNativeInterface::QAndroidApplication::context();
            QString className= getPackageName()+"PackageinfoManager";


            QJniObject  t= QJniObject::callStaticObjectMethod(className.toStdString().c_str(),"getAppSign","(Landroid/content/Context;)Ljava/lang/String;", context.object<jobject>());

            if (env->ExceptionCheck()) {
                env->ExceptionClear();
            }
            return t.toString();
        }
    }
#elif defined(Q_OS_LINUX)
    {
        qWarning()<<"is not implemented in linux";
    }
#elif defined(Q_OS_WIN32)
    {
        qDebug()<<"";

    }
#endif
    return "";
}

QString PackageInfoManager::getApkHash()
{
    qInfo()<<"is going to get the apk hash";
#if defined(Q_OS_ANDROID)
    {
        QJniEnvironment env;
        QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
        if (activity.isValid())
        {
            QJniObject context = QNativeInterface::QAndroidApplication::context();
            QString className= getPackageName()+"PackageinfoManager";


            QJniObject  t= QJniObject::callStaticObjectMethod(className.toStdString().c_str(),"getApkHash","(Landroid/content/Context;)Ljava/lang/String;", context.object<jobject>());

            if (env->ExceptionCheck()) {
                env->ExceptionClear();
            }
            return t.toString();
        }
    }
#endif
    return "";
}

QString PackageInfoManager::getPackageName(QString charSeperator)
{
    QString pn = "org"+charSeperator+"jooya"+charSeperator+getApplicationName().toLower();
    if(charSeperator == "/")
    {
        return pn + charSeperator;
    }
    // else charSeperator is "."
    return pn;

}

QString PackageInfoManager::getApplicationName()
{
    return "Rokhshid";
}
