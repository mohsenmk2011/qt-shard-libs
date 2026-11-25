#ifndef JOOYAANDROIDCONTEXT_H
#define JOOYAANDROIDCONTEXT_H

#include <QObject>
#if defined(Q_OS_ANDROID)
#include<QCoreApplication>
#endif

class JooyaAndroidContext : public QObject
{
    Q_OBJECT
public:
    explicit JooyaAndroidContext(QObject *parent = nullptr);

    QString packageName();

signals:

};

#endif // JOOYAANDROIDCONTEXT_H
