#ifndef NOTIFICATIONCOUNTS_H
#define NOTIFICATIONCOUNTS_H

#include <QObject>
#include<QJsonObject>
#include<notificationtypes.h>
#include<applicationsettings.h>

class NotificationCounts : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int discount READ discount WRITE setDiscount NOTIFY discountChanged)
    Q_PROPERTY(int appIntro READ appIntro WRITE setAppIntro NOTIFY appIntroChanged)
    Q_PROPERTY(int appUpdate READ appUpdate WRITE setAppUpdate NOTIFY appUpdateChanged)

    Q_PROPERTY(bool hasDiscount READ hasDiscount WRITE setHasDiscount NOTIFY hasDiscountChanged)
    Q_PROPERTY(bool hasAppUpdate READ hasAppUpdate WRITE setHasAppUpdate NOTIFY hasAppUpdateChanged)
    Q_PROPERTY(bool hasAppIntro READ hasAppIntro WRITE setHasAppIntro NOTIFY hasAppIntroChanged)

    Q_PROPERTY(bool hasSeenDiscount READ hasSeenDiscount WRITE setHasSeenDiscount NOTIFY hasSeenDiscountChanged)
    Q_PROPERTY(bool hasSeenAppUpdate READ hasSeenAppUpdate WRITE setHasSeenAppUpdate NOTIFY hasSeenAppUpdateChanged)
    Q_PROPERTY(bool hasSeenAppIntro READ hasSeenAppIntro WRITE setHasSeenAppIntro NOTIFY hasSeenAppIntroChanged)

public:
    explicit NotificationCounts(QObject *parent = nullptr);
    explicit NotificationCounts(QJsonObject obj);

    int discount();
    void setDiscount(int count);

    int appIntro();
    void setAppIntro(int count);

    int appUpdate();
    void setAppUpdate(int count);

    bool hasDiscount();
    void setHasDiscount(bool has);

    bool hasAppUpdate();
    void setHasAppUpdate(bool has);

    bool hasAppIntro();
    void setHasAppIntro(bool has);

    bool hasSeenDiscount();
    void setHasSeenDiscount(bool has);

    bool hasSeenAppUpdate();
    void setHasSeenAppUpdate(bool has);

    bool hasSeenAppIntro();
    void setHasSeenAppIntro(bool has);

    void loadFromJson(QJsonObject obj);
    bool getHasSeen(NotificationTypes::NotificationTypesEnum type);
    void setHasSeen(NotificationTypes::NotificationTypesEnum type);
signals:
    void discountChanged();
    void appIntroChanged();
    void appUpdateChanged();

    void hasDiscountChanged();
    void hasAppUpdateChanged();
    void hasAppIntroChanged();

    void hasSeenDiscountChanged();
    void hasSeenAppUpdateChanged();
    void hasSeenAppIntroChanged();

private:    
    int m_Discount;
    int m_AppIntro;
    int m_AppUpdate;

    bool m_HasDiscount;
    bool m_HasAppUpdate;
    bool m_HasAppIntro;

    bool m_HasSeenDiscount;
    bool m_HasSeenAppUpdate;
    bool m_HasSeenAppIntro;
};

#endif // NOTIFICATIONCOUNTS_H
