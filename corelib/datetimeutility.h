#ifndef DATETIMEUTILITY_H
#define DATETIMEUTILITY_H

#include <QObject>
#include<QDateTime>
#include<qlocale.h>
class DateTimeUtility : public QObject
{
    Q_OBJECT
public:
    explicit DateTimeUtility(QObject *parent = nullptr);

    Q_INVOKABLE QDateTime toDateTime(QString date);
    Q_INVOKABLE QString fromDateTime(QDateTime date);
    Q_INVOKABLE QString toPersianHourString(QDateTime date);
signals:

};

#endif // DATETIMEUTILITY_H
