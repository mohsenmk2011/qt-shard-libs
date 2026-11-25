#ifndef ALARMTYPES_H
#define ALARMTYPES_H

#include <QObject>

class AlarmTypes : public QObject
{
    Q_OBJECT
public:
    enum class AlarmTypesEnum:unsigned int
    {
        DisplayPage=0,
        SimpleNotification=1,
    };
    Q_ENUM(AlarmTypesEnum)
};

#endif // ALARMTYPES_H
