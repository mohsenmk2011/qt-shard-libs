#ifndef NOTIFICATIONRECEIVER_H
#define NOTIFICATIONRECEIVER_H

#include <QObject>
#include<notificationcounts.h>
#include<notifymanager.h>

class NotificationReceiver : public QObject
{
    Q_OBJECT
    QML_ATTACHED(NotificationCounts)
public:
    explicit NotificationReceiver(QObject *parent = nullptr);
    static NotificationCounts* qmlAttachedProperties(QObject *object)
    {
        return NotifyManager::m_Counts;
    }
signals:

};

#endif // NOTIFICATIONRECEIVER_H
