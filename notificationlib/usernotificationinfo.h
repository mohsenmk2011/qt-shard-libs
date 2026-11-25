#ifndef USERNOTIFICATIONINFO_H
#define USERNOTIFICATIONINFO_H

#include <QObject>

class UserNotificationInfo : public QObject
{
    Q_OBJECT
public:
    explicit UserNotificationInfo(QObject *parent = nullptr);

signals:

};

#endif // USERNOTIFICATIONINFO_H
