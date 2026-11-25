#ifndef NOTIFICATIONINFO_H
#define NOTIFICATIONINFO_H

#include <QObject>
#include<QDateTime>
#include<jooyasettings.h>

class NotificationInfo : public JooyaSettings
{
    Q_OBJECT
    Q_PROPERTY(QDateTime discountViewDate READ discountViewDate CONSTANT)
public:
    explicit NotificationInfo(QObject *parent = nullptr);

    QDateTime discountViewDate();
    void refreshDiscountDateView();
signals:

};

#endif // NOTIFICATIONINFO_H
