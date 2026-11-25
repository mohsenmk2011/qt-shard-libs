#include "jooyaandroidcontext.h"

JooyaAndroidContext::JooyaAndroidContext(QObject *parent) : QObject(parent)
{

}

QString JooyaAndroidContext::packageName()
{
#if defined(Q_OS_ANDROID)
    auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());
    QJniObject result = activity.callObjectMethod("getPackageName","");
    return result.toString();
#else
    return "";
#endif
}
