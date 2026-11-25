#include "androidutility.h"

AndroidUtility::AndroidUtility(QObject *parent) : QObject(parent)
{

}

void AndroidUtility::keepScreenOn(bool on)
{
#if defined (Q_OS_ANDROID) 
        QJniObject activity =  QJniObject(QNativeInterface::QAndroidApplication::context());
        if (activity.isValid()) {
          QJniObject window =
              activity.callObjectMethod("getWindow", "()Landroid/view/Window;");

          if (window.isValid()) {
            const int FLAG_KEEP_SCREEN_ON = 128;
            if (on) {
              window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
            } else {
              window.callMethod<void>("clearFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
            }
          }
        }
        QJniEnvironment env;
        if (env->ExceptionCheck()) {
          env->ExceptionClear();
        }      
#endif

}

QString AndroidUtility::getMacAddress()
{
    QNetworkInterface networkInterface;
    QString m_strHWAddress1;
    QList<QNetworkInterface> list1=QNetworkInterface::allInterfaces();
    foreach(networkInterface, list1)
    {
        if(networkInterface.flags().testFlag(QNetworkInterface::IsUp) && !networkInterface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            m_strHWAddress1 = networkInterface.hardwareAddress();
        }
        if(!(m_strHWAddress1.isNull()||m_strHWAddress1.isEmpty())){
            break;
        }
    }
    qDebug()<<"#### MacAdress===>>>>:  "<<m_strHWAddress1.toStdString().c_str()<<" ###";
    return m_strHWAddress1;
}
