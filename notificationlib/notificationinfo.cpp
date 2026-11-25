#include "notificationinfo.h"

NotificationInfo::NotificationInfo(QObject *parent) : JooyaSettings(parent)
{

}

QDateTime NotificationInfo::discountViewDate()
{    
    qCritical()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qCritical()<<"%%%%%%%%%%%%%%%%%%toverfy%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo()<<m_DateTimeUtility.toDateTime(get("discountViewDate").toString());
    qInfo()<<get("discountViewDate").toDateTime();
    qCritical()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qCritical()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";

    return m_DateTimeUtility.toDateTime(get("discountViewDate").toString());
    //return get("discountViewDate").toDateTime();
}

void NotificationInfo::refreshDiscountDateView()
{
    set("discountViewDate",m_DateTimeUtility.fromDateTime(QDateTime::currentDateTime()));
}
