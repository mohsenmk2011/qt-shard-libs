#include "downloadservicemanager.h"

DownloadServiceManager::DownloadServiceManager(QObject *parent)
    : AndroidServiceManager{parent}
{
    setServiceClassName("DownloadService");
    setServiceBroadcastReceiverClassName("DownloadServiceBroadcastUtility");
    setAppBroadcastReceiverClassName("DownloadAppBroadcastUtility");
}
