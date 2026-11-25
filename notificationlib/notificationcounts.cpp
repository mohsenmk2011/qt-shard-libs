#include "notificationcounts.h"

NotificationCounts::NotificationCounts(QObject *parent) : QObject(parent)
{
    qDebug()<<"=>>>[ Initialization NotificationCounts ]<<<=";
    m_Discount=0;
    m_AppIntro=0;
    m_AppUpdate=0;
    m_HasSeenAppUpdate=true;
    m_HasSeenDiscount=true;
    m_HasSeenAppIntro=true;
    m_HasAppIntro=false;
    m_HasDiscount=false;
    m_HasAppUpdate=false;
}

NotificationCounts::NotificationCounts(QJsonObject obj):NotificationCounts()
{
    loadFromJson(obj);
}

void NotificationCounts::loadFromJson(QJsonObject obj)
{
    setDiscount(obj.value("discount").toInt());
    setAppIntro(obj.value("appIntro").toInt());
    setAppUpdate(obj.value("appUpdate").toInt());

    setHasSeenAppUpdate(obj.value("hasSeenAppUpdate").toBool());
    setHasSeenDiscount(obj.value("hasSeenDiscount").toBool());
    setHasSeenAppIntro(appIntro()<=0);
}

bool NotificationCounts::getHasSeen(NotificationTypes::NotificationTypesEnum type)
{
    switch (type) {
        case NotificationTypes::NotificationTypesEnum::Discount:
            return hasSeenDiscount();
            break;
        case NotificationTypes::NotificationTypesEnum::AppUpdate:
            return hasSeenAppUpdate();
            break;
        case NotificationTypes::NotificationTypesEnum::AppIntroducing:
            return hasSeenAppIntro();
            break;
        default:
            return false;
            break;
    }
}

void NotificationCounts::setHasSeen(NotificationTypes::NotificationTypesEnum type)
{
    switch (type) {
    case NotificationTypes::NotificationTypesEnum::Discount:
        setHasSeenDiscount(true);
        break;
    case NotificationTypes::NotificationTypesEnum::AppUpdate:
        setHasSeenAppUpdate(true);
        break;
    case NotificationTypes::NotificationTypesEnum::AppIntroducing:
        setHasSeenAppIntro(true);
        break;
    case NotificationTypes::NotificationTypesEnum::UnKnown:
        return;
        break;
    }
}

int NotificationCounts::discount()
{
    return m_Discount;
}

void NotificationCounts::setDiscount(int count)
{
    m_Discount=count;
    emit discountChanged();
    if(count>0){
        setHasDiscount(true);
    }
    else {
        setHasDiscount(false);
    }
}

int NotificationCounts::appIntro()
{
    return m_AppIntro;
}

void NotificationCounts::setAppIntro(int count)
{
    m_AppIntro=count;
    emit appIntroChanged();
    setHasAppIntro(count>0);
}

int NotificationCounts::appUpdate()
{
    return m_AppUpdate;
}

void NotificationCounts::setAppUpdate(int count)
{
    m_AppUpdate=count;
    emit appUpdateChanged();
    if(count>0){
        setHasAppUpdate(true);
    }
    else {
        setHasAppUpdate(false);
    }
}

bool NotificationCounts::hasDiscount()
{
    return m_HasDiscount;
}

void NotificationCounts::setHasDiscount(bool has)
{
    m_HasDiscount=has;
    emit hasDiscountChanged();
}

bool NotificationCounts::hasAppUpdate()
{
    return m_HasAppUpdate;
}

void NotificationCounts::setHasAppUpdate(bool has)
{
    m_HasAppUpdate=has;
    emit hasAppUpdateChanged();
}

bool NotificationCounts::hasAppIntro()
{
    return m_HasAppIntro;
}

void NotificationCounts::setHasAppIntro(bool has)
{
    m_HasAppIntro=has;
    emit hasAppIntroChanged();
}

bool NotificationCounts::hasSeenDiscount()
{
    return m_HasSeenDiscount;
}

void NotificationCounts::setHasSeenDiscount(bool has)
{
    m_HasSeenDiscount=has;
    emit hasSeenDiscountChanged();
}

bool NotificationCounts::hasSeenAppUpdate()
{
    return m_HasSeenAppUpdate;
}

void NotificationCounts::setHasSeenAppUpdate(bool has)
{
    m_HasSeenAppUpdate=has;
    emit hasSeenAppUpdateChanged();
}

bool NotificationCounts::hasSeenAppIntro()
{
    return m_HasSeenAppIntro;
}

void NotificationCounts::setHasSeenAppIntro(bool has)
{
    m_HasSeenAppIntro=has;
    emit hasSeenAppIntroChanged();
}
