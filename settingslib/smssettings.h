#ifndef SMSSETTINGS_H
#define SMSSETTINGS_H

#include <QObject>
#include<jooyanetwork.h>

class SmsSettings : public JooyaNetwork
{
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(int waitTimeForNextSend READ waitTimeForNextSend WRITE setWaitTimeForNextSend NOTIFY waitTimeForNextSendChanged)
    Q_PROPERTY(QString senderNumber READ senderNumber WRITE setSenderNumber NOTIFY senderNumberChanged)

public:
    explicit SmsSettings(QObject *parent = nullptr);

    QString userName();
    void setUserName(QString v);

    QString password();
    void setPassword(QString v);

    int waitTimeForNextSend();
    void setWaitTimeForNextSend(int waitTime);

    QString senderNumber();
    void setSenderNumber(QString waitTime);

    Q_INVOKABLE void load();
    Q_INVOKABLE void save();
signals:
    void waitTimeForNextSendChanged();
    void userNameChanged();
    void passwordChanged();
    void senderNumberChanged();
private slots:

    void loadFinished();
    void saveFinished();
private:
    int m_WaitTimeForNextSend;
    QString m_SenderNumber;
    QString m_userName;
    QString m_password;
    QJsonObject readFeilds();
};

#endif // SMSSETTINGS_H
