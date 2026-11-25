#ifndef ALARMCLASSES_H
#define ALARMCLASSES_H

#include <QObject>

class AlarmClasses : public QObject
{
    Q_OBJECT
public:
    enum class AlarmClassesEnum:unsigned int{
        AlarmManager = 0,
        WorkoutManager = 1,
    };
    Q_ENUM(AlarmClassesEnum)
};

#endif // ALARMCLASSES_H
