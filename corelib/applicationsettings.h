#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include<jooyasettings.h>
#include<datetimeutility.h>

class ApplicationSettings : public JooyaSettings
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QString alarmInfo READ alarmInfo WRITE setAlarmInfo NOTIFY alarmInfoChanged)
    Q_PROPERTY(bool seenAppIntroducing READ seenAppIntroducing WRITE setSeenAppIntroducing NOTIFY seenAppIntroducingChanged)
public:
    explicit ApplicationSettings(QObject *parent = nullptr);

    QString alarmInfo();
    void setAlarmInfo(QString ai);

    QString theme();
    void setTheme(QString t);

    void setDefaultTheme(QString t);
    QString defaultTheme();

    QString userInfo();
    void setUserInfo(QString t);

    //the last order that user tried for payment
    QString lastTriedPaymentOrderId();
    void setLastTriedPaymentOrderId(QString id);

    bool seenAppIntroducing();
    void setSeenAppIntroducing(bool seen);

signals:
    void alarmInfoChanged();
    void themeChanged();
    void seenAppIntroducingChanged();
private:
};

#endif // APPLICATIONSETTINGS_H
