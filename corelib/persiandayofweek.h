#ifndef PERSIANDAYOFWEEK_H
#define PERSIANDAYOFWEEK_H

#include <QObject>

class PersianDayOfWeek : public QObject
{
    Q_OBJECT
public:
    enum class PersianDayOfWeekEnum:unsigned int{

        /// <summary>
        /// شنبه
        /// </summary>
        Saturday = 0,

        /// <summary>
        /// یکشنبه
        /// </summary>
        Sunday = 1,

        /// <summary>
        /// دو شنبه
        /// </summary>
        Monday = 2,

        /// <summary>
        /// سه شنبه
        /// </summary>
        Tuesday = 3,

        /// <summary>
        /// چهار شنبه
        /// </summary>
        Wednesday = 4,

        /// <summary>
        /// پنج شنبه
        /// </summary>
        Thursday = 5,

        /// <summary>
        /// جمعه
        /// </summary>
        Friday = 6
    };
    Q_ENUM(PersianDayOfWeekEnum)

};

#endif // PERSIANDAYOFWEEK_H
