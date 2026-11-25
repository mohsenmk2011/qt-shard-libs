#include "sharemanager.h"

ShareManager::ShareManager(QObject *parent)
    : QObject{parent}
{

}

void ShareManager::share(QString message)
{
    qInfo()<<"share this message=> "<<message;
#if defined(Q_OS_ANDROID)
    {
    QJniEnvironment _env;
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (_env->ExceptionCheck()) {
        _env->ExceptionClear();
    }
    if (activity.isValid() )
    {
        QString className = PackageInfoManager::getPackageName()+"ShareManager";
        QJniObject::callStaticMethod<void>(className.toUtf8(),"share","(Landroid/app/Activity;Ljava/lang/String;)V",activity.object<jobject>(),QJniObject::fromString(message).object<jstring>());
        if (_env->ExceptionCheck()) {
            _env->ExceptionClear();
        }
    }
    }
#elif defined(Q_OS_LINUX)
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(message);
    }
#elif defined(Q_OS_WIN32)
    {
        qDebug()<<"";

    }
#endif
}
