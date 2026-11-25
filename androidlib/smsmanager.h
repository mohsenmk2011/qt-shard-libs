#ifndef SMSMANAGER_H
#define SMSMANAGER_H

#include <QObject>
#include <QtDebug>
#if defined(Q_OS_ANDROID)
#include<QJniObject>
#include<QJniEnvironment>
#include <QCoreApplication>
#include<packageinfomanager.h>
#endif

class SmsManager : public QObject
{
    Q_OBJECT
public:
    explicit SmsManager(QObject *parent = nullptr);

    static SmsManager *instance() { return m_instance; }
    void registerNativesMethod();

signals:
    void newSmsReceived(const QString &message);
private:
    static SmsManager *m_instance;

};

#endif // SMSMANAGER_H
