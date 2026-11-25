#ifndef PERMISSIONTYPES_H
#define PERMISSIONTYPES_H

#include <QObject>

class PermissionTypes : public QObject
{
    Q_OBJECT

public:
    enum class PermissionTypesEnum:unsigned int
    {
        READ_EXTERNAL_STORAGE=0,
        WRITE_EXTERNAL_STORAGE,

        INTERNET,
        ACCESS_NETWORK_STATE,
        ACCESS_WIFI_STATE,

        INSTALL_PACKAGES,
        DELETE_PACKAGES,

        CAMERA,

        RECEIVE_BOOT_COMPLETED,
        FOREGROUND_SERVICE,
        //SMS
        RECEIVE_SMS,
        READ_SMS,
        SEND_SMS,
        RECEIVE_MMS,
        RECEIVE_WAP_PUSH,
        USE_FULL_SCREEN_INTENT,
        POST_NOTIFICATIONS,
        SET_ALARM,
        WAKE_LOCK,
        REQUEST_IGNORE_BATTERY_OPTIMIZATIONS,
        SCHEDULE_EXACT_ALARM,
        USE_EXACT_ALARM,
        VIBRATE,
        DISABLE_KEYGUARD,
        SYSTEM_ALERT_WINDOW,

        // Gallery Storage
        READ_MEDIA_IMAGES,
        READ_MEDIA_VIDEO,
        READ_MEDIA_AUDIO,
        // full access storage
        MANAGE_EXTERNAL_STORAGE
    };
    Q_ENUMS(PermissionTypesEnum)
};

#endif // PERMISSIONTYPES_H
