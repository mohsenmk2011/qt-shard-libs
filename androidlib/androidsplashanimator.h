#ifndef ANDROIDSPLASHANIMATOR_H
#define ANDROIDSPLASHANIMATOR_H

#include <QObject>
//#include<QtAndroidExtras/qandroidjniobject.h>
//#include<QtAndroid>
#include<qdebug.h>
class AndroidSplashAnimator : public QObject
{
    Q_OBJECT
public:
    explicit AndroidSplashAnimator(QObject *parent = nullptr);

    void animate();

signals:

public slots:
};

#endif // ANDROIDSPLASHANIMATOR_H
