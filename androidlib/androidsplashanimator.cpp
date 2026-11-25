#include "androidsplashanimator.h"

AndroidSplashAnimator::AndroidSplashAnimator(QObject *parent) : QObject(parent)
{

}

void AndroidSplashAnimator::animate()
{
    qDebug()<<"calling animate mehtod";
//    QtAndroid::androidActivity().callMethod<void>("animate");
//    QAndroidJniObject::callStaticMethod<void>("org/jooya/rokhshid/AppActivity","animate");
}
