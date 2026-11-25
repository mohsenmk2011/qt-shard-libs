#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include<jooyanetwork.h>
#include<QDateTime>
#include<imagefile.h>
#include<applicationpath.h>
#include<persiandatetime.h>

class Contact : public ImageFile
{
    Q_OBJECT
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(QDateTime lastActivityDate READ lastActivityDate WRITE setLastActivityDate NOTIFY lastActivityDateChanged)
    Q_PROPERTY(QString lastActivityText READ lastActivityText WRITE setLastActivityText NOTIFY lastActivityTextChanged)
    Q_PROPERTY(bool isMe READ isMe WRITE setIsMe NOTIFY isMeChanged)
    Q_PROPERTY(bool isOnline READ isOnline WRITE setIsOnline NOTIFY isOnlineChanged)
    Q_PROPERTY(bool isOffline READ isOffline WRITE setIsOffline NOTIFY isOfflineChanged)
public:
    explicit Contact(QObject *parent = nullptr);
    explicit Contact(QJsonObject obj);

    bool isMe();
    void setIsMe(bool me);

    bool isOnline();
    void setIsOnline(bool o);

    bool isOffline();
    void setIsOffline(bool o);

    QString userId();
    void setUserId(QString userId);

    QString displayName();
    void setDisplayName(QString name);

    QString ip();
    void setIp(QString ip);

    QDateTime lastActivityDate();
    void setLastActivityDate(QDateTime date);

    QString lastActivityText();
    void setLastActivityText(QString l);

    void fromJson(QJsonObject obj) override;
    QJsonObject toJson() override;

    void getFromServer();
signals:
    void deleteSucceed();
    void isMeChanged();
    void isOnlineChanged();
    void isOfflineChanged();
    void userIdChanged();
    void ipChanged();
    void lastActivityTextChanged();
    void lastActivityDateChanged();
    void displayNameChanged();
    void updateFinished();
private slots:

    void onGetContactFinished();
    void timerIsOnlineTimeout();
private:
    QString m_UserId;
    QString m_DisplayName;
    QString m_Ip;
    bool m_IsMe;
    QDateTime m_LastActivityDate;    
    PersianDateTime* m_PersianDateTime;
    QString m_LastActivityText;
    bool m_IsOnline;
    bool m_IsOffline;
    QTimer* m_TimerIsOnline;
    void updateLastActivityText();

};

#endif // CONTACT_H
