#ifndef PERSIANDATETIME_H
#define PERSIANDATETIME_H

#include <QObject>
#include<QDateTime>
#include<QDate>
#include<qlocale.h>
#include<QCalendar>
#include<persiandayofweek.h>
#include<qdebug.h>

class PersianDateTime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int day READ day CONSTANT)
    Q_PROPERTY(int month READ month CONSTANT)
    Q_PROPERTY(int year READ year CONSTANT)

    Q_PROPERTY(QString monthName READ monthName CONSTANT)
    Q_PROPERTY(QString weekName READ weekName CONSTANT)

    Q_PROPERTY(QString shortTimeOfDay READ shortTimeOfDay CONSTANT)

    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged)

public:
    explicit PersianDateTime(QObject *parent = nullptr);
    PersianDateTime(QDateTime dateTime);
    PersianDateTime(int persianYear,int persianMonth,int persianDay);
    PersianDateTime(int persianYear,int persianMonth,int persianDay,int hour, int minute, int second);

    enum class TextFormats : unsigned int
    {
        ///
        /// Format Like: 18:27
        ///
        ShortTime=0,
        ///
        /// Format Like: 12:15:18
        ///
        ShortTimeOfDay=1,
        ///
        /// Format Like: 1400.9.29
        ///
        ShortDate=2,
        ///
        /// Format Like: 1400.9.29 12:15
        ///
        ShortDateTime=3,
    };
    Q_ENUM(TextFormats)

    int day();
    int month();
    int year();
    int shortYear();


    int hour();
    int shortHour();
    int minute();
    int second();
    int msec();

    int getMonthDays();

//    int weekOfYear();
//    int weekOfMonth():
    int dayOfYear();

    bool isLeapYear();
    bool isToday();
    bool isYesterday();
    bool isTomorrow();

    QString monthName();
    QString weekName();
    QString shortWeekName();

     QString shortTimeOfDay();
     QString shortTime();

     Q_INVOKABLE QString toString(PersianDateTime::TextFormats format);

    Q_INVOKABLE QString shortDate(QChar seperator='/');

    int dayOfWeek();

    QDateTime date();
    void setDate(QDateTime d);
    static PersianDateTime *now();
signals:
    void dateChanged();
private:
    int m_Day;
    int m_Month;
    int m_Year;
    QDateTime m_DateTime;
    QCalendar m_Calendar;
};

#endif // PERSIANDATETIME_H
