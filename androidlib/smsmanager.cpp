#include "smsmanager.h"

SmsManager *SmsManager::m_instance = nullptr;

#if defined(Q_OS_ANDROID)
static void newSmsReceivedFromQtActivity(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString message=env->GetStringUTFChars(value, nullptr);
    qInfo()<<"***[ New SMS received from qt activity  => ]***"<<message;
    emit SmsManager::instance()->newSmsReceived(message);
}
#endif

SmsManager::SmsManager(QObject *parent) : QObject{parent}
{
    m_instance = this;
}

void SmsManager::registerNativesMethod()
{
#if defined(Q_OS_ANDROID)
    JNINativeMethod methods[] {
        {"sendToQtApp", "(Ljava/lang/String;)V", reinterpret_cast<void *>(newSmsReceivedFromQtActivity)},
    };
    QString className = PackageInfoManager::getPackageName()+"SmsManager";
    QJniObject javaClass(className.toUtf8());

    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
#endif
}
