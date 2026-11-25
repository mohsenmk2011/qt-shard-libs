#ifndef SIGNUPRESULT_H
#define SIGNUPRESULT_H

#include <QObject>
#include<qtimer.h>
#include<QTime>
#include<QtDebug>

class SignupResult : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString timeToSendNext READ timeToSendNext WRITE setTimeToSendNext NOTIFY timeToSendNextChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)    
    Q_PROPERTY(int waitNextSms READ waitNextSms WRITE setWaitNextSms NOTIFY waitNextSmsChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)

public:
    explicit SignupResult(QObject *parent = nullptr);

    QString timeToSendNext();
    void setTimeToSendNext(QString dId);

    QString message();
    void setMessage(QString m);

    QString phoneNumber();
    void setPhoneNumber(QString number);

    int waitNextSms();
    void setWaitNextSms(int wait);

    Q_INVOKABLE void startTimer();
    Q_INVOKABLE void stopTimer();
signals:
    void timeToSendNextChanged();
    void messageChanged();
    void phoneNumberChanged();
    void waitNextSmsChanged();
    void sendNextSms();
public slots:
    void timerTimeOut();
private:
    QString m_TimeSendNext;
    QString m_Message;
    int m_WaitNextSms;
    QTimer m_Timer;
    QTime m_Time;
    QString m_PhoneNumber;
};

#endif // SIGNUPRESULT_H
