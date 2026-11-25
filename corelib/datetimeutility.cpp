#include "datetimeutility.h"

DateTimeUtility::DateTimeUtility(QObject *parent)
    : QObject{parent}
{

}

QDateTime DateTimeUtility::toDateTime(QString date)
{
    QLocale locale(QLocale::English,QLocale::UnitedStates);
    return locale.toDateTime(date,"yyyyMMddHHmmss");
}

QString DateTimeUtility::toPersianHourString(QDateTime date)
{
    QLocale locale(QLocale::Persian,QLocale::Iran);
    return locale.toString(date,"HH:mm");
}

QString DateTimeUtility::fromDateTime(QDateTime date)
{
    QLocale locale(QLocale::English,QLocale::UnitedStates);
    return locale.toString(date,"yyyyMMddHHmmss");
}
