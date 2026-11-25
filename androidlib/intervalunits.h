#ifndef INTERVALUNITS_H
#define INTERVALUNITS_H

#include <QObject>

class IntervalUnits : public QObject
{
    Q_OBJECT
public:
    enum class IntervalUnitsEnum:unsigned int
    {
        Seconds = 0,
        Minutes = 1,
        Hours = 2,
        Days = 3,
        Months = 4,
        Years = 5,
    };
    Q_ENUM(IntervalUnitsEnum)
};

#endif // INTERVALUNITS_H
