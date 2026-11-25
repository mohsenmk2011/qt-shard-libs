#ifndef ANDROIDDEEPLINKMANAGER_H
#define ANDROIDDEEPLINKMANAGER_H

#include <QObject>
#include <QtDebug>
// #include<QtQml>
#if defined(Q_OS_ANDROID)
#include <QCoreApplication>
#include <QJniEnvironment>
#include <QJniObject>
#include<packageinfomanager.h>
#endif

class AndroidDeepLinkManager : public QObject
{
    Q_OBJECT
public:
    explicit AndroidDeepLinkManager(QObject *parent = nullptr);

    static AndroidDeepLinkManager *instance() { return m_instance; }
    void registerNativesMethod();
    Q_INVOKABLE void checkDeepLink();
    static int m_OrderId;
signals:
    void newOrderIdReceived(int orderId);
private:

    static AndroidDeepLinkManager *m_instance;
};

#endif // ANDROIDDEEPLINKMANAGER_H
