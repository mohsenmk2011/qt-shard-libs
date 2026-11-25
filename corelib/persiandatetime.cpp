#include "persiandatetime.h"

PersianDateTime::PersianDateTime(QObject *parent): QObject(parent)
{
    m_Calendar=QCalendar(QCalendar::System::Jalali);
    m_DateTime=QDateTime();
}

PersianDateTime::PersianDateTime(QDateTime dateTime):PersianDateTime()
{
    setDate(dateTime);
}

PersianDateTime::PersianDateTime(int persianYear, int persianMonth, int persianDay):PersianDateTime()
{
    m_DateTime=QDateTime(m_Calendar.dateFromParts(persianYear,persianMonth,persianDay),QTime());
    qInfo()<<"Date=> 2464 "<<m_DateTime.toString();
}

PersianDateTime::PersianDateTime(int persianYear, int persianMonth, int persianDay, int hour, int minute, int second)
{
    m_DateTime=QDateTime(m_Calendar.dateFromParts(persianYear,persianMonth,persianDay),QTime(hour,minute,second));
    qInfo()<<"Date=> 24614 "<<m_DateTime.toString();
}

int PersianDateTime::year()
{
    if(!m_DateTime.isValid()&&m_DateTime.isNull()){
        return 0;
    }
    QCalendar::YearMonthDay ymd=m_Calendar.partsFromDate(m_DateTime.date());
    return ymd.year;
}

int PersianDateTime::shortYear()
{
    return year()%100;
}

int PersianDateTime::hour()
{
    return m_DateTime.time().hour();
}

int PersianDateTime::shortHour()
{
    int h=hour();
    if(h>12){
        return h%12;
    }
    return h;
}

int PersianDateTime::minute()
{
    return m_DateTime.time().minute();
}

int PersianDateTime::second()
{
    return m_DateTime.time().second();
}

int PersianDateTime::msec()
{
    return m_DateTime.time().msec();
}

int PersianDateTime::getMonthDays()
{
    switch (month()) {
    case 1:return 31;
    case 2:return 31;
    case 3:return 31;
    case 4:return 31;
    case 5:return 31;
    case 6:return 31;
    case 7:return 30;
    case 8:return 30;
    case 9:return 30;
    case 10:return 30;
    case 11:return 30;
    case 12:{
        if(isLeapYear()){
            return 30;
        }
        else {
            return 29;
        }
    };
    default: return 0;
    }
}

int PersianDateTime::dayOfYear()
{
    return m_DateTime.date().dayOfYear(m_Calendar);
}

//int PersianDateTime::weekOfYear()
//{
//    m_DateTime.date().weekNumber()
//}

bool PersianDateTime::isLeapYear()
{
    return m_Calendar.isLeapYear(year());
}

bool PersianDateTime::isTomorrow()
{
    if(!m_DateTime.isValid()&&m_DateTime.isNull()){
        return false;
    }
   QDateTime today=QDateTime::currentDateTime();
   if(today.daysTo(m_DateTime)==1){
       return true;
   }
   return false;
}

bool PersianDateTime::isYesterday()
{
    if(!m_DateTime.isValid()&&m_DateTime.isNull()){
        return false;
    }
   QDateTime today=QDateTime::currentDateTime();
   if(m_DateTime.daysTo(today)==1){
       return true;
   }
   return false;
}

bool PersianDateTime::isToday()
{
    if(!m_DateTime.isValid()&&m_DateTime.isNull()){
        return false;
    }
   QDateTime today=QDateTime::currentDateTime();
   if(m_DateTime.daysTo(today)==0){
       return true;
   }
   return false;
}

int PersianDateTime::month()
{
    if(!m_DateTime.isValid()&&m_DateTime.isNull()){
        return 0;
    }
    QCalendar::YearMonthDay ymd=m_Calendar.partsFromDate(m_DateTime.date());
    return ymd.month;
}

int PersianDateTime::day()
{
    if(!m_DateTime.isValid()&&m_DateTime.isNull()){
        return 0;
    }
    QCalendar::YearMonthDay ymd=m_Calendar.partsFromDate(m_DateTime.date());
    return ymd.day;
}


QDateTime PersianDateTime::date()
{
    return m_DateTime;
}

void PersianDateTime::setDate(QDateTime d)
{
    if(!d.isValid()&&d.isNull()){
        return;
    }
    if(m_DateTime!=d){
        m_DateTime=d;
        emit dateChanged();
    }
}

PersianDateTime* PersianDateTime::now()
{
    return new PersianDateTime(QDateTime::currentDateTime());
}

QString PersianDateTime::monthName()
{
    QLocale iran(QLocale::Persian,QLocale::Iran);
    return m_Calendar.monthName(iran,month());
}

QString PersianDateTime::weekName()
{
    QLocale iran(QLocale::Persian,QLocale::Iran);
    return m_Calendar.weekDayName(iran,dayOfWeek());
}

QString PersianDateTime::shortWeekName()
{
    QLocale iran(QLocale::Persian,QLocale::Iran);
    return m_Calendar.weekDayName(iran,dayOfWeek(),QLocale::FormatType::ShortFormat);
}

QString PersianDateTime::shortTimeOfDay()
{
   return m_DateTime.time().toString("HH:mm:ss");
}
QString PersianDateTime::shortTime()
{
   return m_DateTime.time().toString("HH:mm");
}

QString PersianDateTime::toString(PersianDateTime::TextFormats format)
{
    switch (format) {
    case PersianDateTime::TextFormats::ShortTime:
        return m_DateTime.time().toString("HH:mm");
    case PersianDateTime::TextFormats::ShortTimeOfDay:
        return m_DateTime.time().toString("HH:mm::ss");
    case PersianDateTime::TextFormats::ShortDate:
        return shortDate();
    case PersianDateTime::TextFormats::ShortDateTime:
        return m_DateTime.toString("HH:mm::ss");
    default:
        return m_DateTime.time().toString("HH:mm");
    }    
}

QString PersianDateTime::shortDate(QChar seperator)
{
   return QString("%1%2%3%4%5").arg(year()).arg(seperator).arg(month()).arg(seperator).arg(day());
}

int PersianDateTime::dayOfWeek()
{
    return m_Calendar.dayOfWeek(m_DateTime.date());
}
