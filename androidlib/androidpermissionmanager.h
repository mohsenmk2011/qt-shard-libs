#ifndef ANDROIDPERMISSIONMANAGER_H
#define ANDROIDPERMISSIONMANAGER_H

#include <QObject>
#include<qdebug.h>
#include<permissiontypes.h>
#include <QPermissions>

#if defined(Q_OS_ANDROID)
#include<QCoreApplication>
#include <QtCore/private/qandroidextras_p.h>
#include<packageinfomanager.h>
#include<QFuture>
#include<QtConcurrent/QtConcurrent>
#endif
class AndroidPermissionManager : public QObject
{
    Q_OBJECT
public:
    explicit AndroidPermissionManager(QObject *parent = nullptr);
    ///adds permission to the list
    void addPermission(PermissionTypes::PermissionTypesEnum permission);

    QString convertToString(PermissionTypes::PermissionTypesEnum permission);

    bool requestPermissions();
    bool isPermissionGranted(PermissionTypes::PermissionTypesEnum permission);
    bool isPermissionGranted(QString permission);

    Q_INVOKABLE bool requestStorage();
    Q_INVOKABLE bool requestSms();
    Q_INVOKABLE bool requestCamera();
    Q_INVOKABLE bool requestSetAlarm();
    Q_INVOKABLE bool requestSetAlertWindow();
    Q_INVOKABLE bool requestIgnoringBatteryOptimizations();
    Q_INVOKABLE bool requestSetExactAlarmPermission();
signals:

public slots:
private:
    QStringList m_PermissionList;
};
#endif // ANDROIDPERMISSIONMANAGER_H
