#ifndef DOWNLOADSERVICEMANAGER_H
#define DOWNLOADSERVICEMANAGER_H

#include <QObject>
#include<androidservicemanager.h>

class DownloadServiceManager : public AndroidServiceManager
{
    Q_OBJECT
public:
    explicit DownloadServiceManager(QObject *parent = nullptr);

signals:
};

#endif // DOWNLOADSERVICEMANAGER_H
