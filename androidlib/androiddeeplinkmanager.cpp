#include "androiddeeplinkmanager.h"

AndroidDeepLinkManager::AndroidDeepLinkManager(QObject *parent)
    : QObject{parent}
{

    m_instance = this;
}

AndroidDeepLinkManager *AndroidDeepLinkManager::m_instance = nullptr;

#if defined(Q_OS_ANDROID)
static void newOrderIdReceivedFromQtActivity(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString message=env->GetStringUTFChars(value, nullptr);
    if(AndroidDeepLinkManager::instance()==nullptr){
        qWarning()<<"***[ jooya No instace of AndroidDeepLinkManager so return ]***"<<message;
        return;
    }
    else{
        qDebug()<<"***[ jooya  AndroidDeepLinkManager is not null ]***"<<message;
    }
    qInfo()<<"***[ jooya New OrderId received from qt activity  => ]***"<<message;
    int id = message.toInt();
    qDebug()<<"jooya id=> "<<id;
    AndroidDeepLinkManager::m_OrderId = message.toInt();
    emit AndroidDeepLinkManager::instance()->newOrderIdReceived(message.toInt());
//    AndroidDeepLinkManager::instance()->setOrderId(message);
//    AndroidDeepLinkManager::instance()->checkDeepLink();
}
#endif

void AndroidDeepLinkManager::registerNativesMethod()
{
#if defined(Q_OS_ANDROID)
    JNINativeMethod methods[] {
        {"sendToQtApp", "(Ljava/lang/String;)V", reinterpret_cast<void *>(newOrderIdReceivedFromQtActivity)},
    };
    QString className = PackageInfoManager::getPackageName()+"DeepLinkManager";
    QJniObject javaClass(className.toUtf8());
    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
#endif
}

void AndroidDeepLinkManager::checkDeepLink()
{
    if(m_OrderId>0){
        emit newOrderIdReceived(m_OrderId);
    }
}

int AndroidDeepLinkManager::m_OrderId = 0;
