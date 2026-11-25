#ifndef ALARMINFO_H
#define ALARMINFO_H

#include <QObject>
#include <QJsonObject>
#include<QDateTime>
#include<QJsonDocument>
#include<alarmtypes.h>
#include<intervalunits.h>

class AlarmInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int alarmHour READ alarmHour WRITE setAlarmHour NOTIFY alarmHourChanged)
    Q_PROPERTY(int alarmMinutes READ alarmMinutes WRITE setAlarmMinutes NOTIFY alarmMinutesChanged)
    Q_PROPERTY(int audioVolume READ audioVolume WRITE setAudioVolume NOTIFY audioVolumeChanged)
    Q_PROPERTY(AlarmTypes::AlarmTypesEnum alarmType READ alarmType WRITE setAlarmType NOTIFY alarmTypeChanged)
    Q_PROPERTY(bool hasRepeat READ hasRepeat WRITE setHasRepeat NOTIFY hasRepeatChanged FINAL)
    Q_PROPERTY(int alarmInterval READ alarmInterval WRITE setAlarmInterval NOTIFY alarmIntervalChanged)
    Q_PROPERTY(IntervalUnits::IntervalUnitsEnum intervalUnit READ intervalUnit WRITE setIntervalUnit NOTIFY intervalUnitChanged FINAL)
public:
    explicit AlarmInfo(QObject *parent = nullptr);

    AlarmTypes::AlarmTypesEnum alarmType();
    void setAlarmType(AlarmTypes::AlarmTypesEnum at);

    int alarmHour();
    void setAlarmHour(int h);

    int alarmMinutes();
    void setAlarmMinutes(int m);

    int audioVolume();
    void setAudioVolume(int v);

    Q_INVOKABLE QJsonObject toJson();

    Q_INVOKABLE QString convertToString();
    Q_INVOKABLE void fromString(QString s);
    Q_INVOKABLE void fromJson(QJsonObject json);

    IntervalUnits::IntervalUnitsEnum intervalUnit() const;
    void setIntervalUnit(const IntervalUnits::IntervalUnitsEnum &newIntervalUnit);

    int alarmInterval();
    void setAlarmInterval(int newAlarmInterval);

    bool hasRepeat() const;
    void setHasRepeat(bool newHasRepeat);

signals:
    void alarmHourChanged();
    void alarmMinutesChanged();
    void audioVolumeChanged();
    void alarmTypeChanged();
    void intervalUnitChanged();
    void alarmIntervalChanged();

    void hasRepeatChanged();

private:
    int m_AlarmHour;
    int m_AlarmMinutes;
    int m_AudioVolume;
    AlarmTypes::AlarmTypesEnum m_AlarmType;
    int m_alarmInterval;
    IntervalUnits::IntervalUnitsEnum m_intervalUnit;
    bool m_hasRepeat;
};

#endif // ALARMINFO_H
