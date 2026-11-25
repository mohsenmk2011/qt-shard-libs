#ifndef ANDROIDUTILITY_H
#define ANDROIDUTILITY_H

#include <QObject>
#include<QtNetwork/QNetworkInterface>
#include<QDebug>

#if defined (Q_OS_ANDROID)
#include<QCoreApplication>
#include<QJniEnvironment>
#include<QJniObject>
#endif
class AndroidUtility : public QObject
{
    Q_OBJECT
public:
    explicit AndroidUtility(QObject *parent = nullptr);
    Q_INVOKABLE void keepScreenOn(bool on);
    QString getMacAddress();

signals:

public slots:
};

#endif // ANDROIDUTILITY_H
