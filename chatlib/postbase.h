#ifndef POSTBASE_H
#define POSTBASE_H

#include <QObject>
#include<QDateTime>
#include<datetimeutility.h>
#include<persiandatetime.h>
#include<jooyalistitem.h>
#include<QUuid>
#include<talkstates.h>

class PostBase : public JooyaListItem
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString chatId READ chatId WRITE setChatId NOTIFY chatIdChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(TalkStatus::TalkStatusEnum status READ status WRITE setStatus NOTIFY statusChanged)

    Q_PROPERTY(QString hour READ hour CONSTANT)
    Q_PROPERTY(QString dateText READ dateText WRITE setDateText NOTIFY dateTextChanged)

    Q_PROPERTY(int topMargin READ topMargin WRITE setTopMargin NOTIFY topMarginChanged)
    Q_PROPERTY(bool fromMe READ fromMe WRITE setFromMe NOTIFY fromMeChanged)
    Q_PROPERTY(bool isJustDate READ isJustDate WRITE setIsJustDate NOTIFY isJustDateChanged)
public:
    explicit PostBase(QObject *parent = nullptr);
//    PostBase(QString userId, QString contactId, QString content);
//    explicit Post(QJsonObject obj);
    explicit PostBase(QDateTime date,bool isJustDate);

    QString id();
    void setId(QString id);

    QString chatId();
    void setChatId(QString cId);

    QString content();
    void setContent(QString c);

    QString userId();
    void setUserId(QString uId);

    QDateTime date();
    void setDate(QDateTime d);

    TalkStatus::TalkStatusEnum status();
    void setStatus(TalkStatus::TalkStatusEnum s);

    bool waitingForResendStatus();
    void setWaitingForResendStatus(bool w);

    QString hour();
    QString persianDate();

    QString dateText();
    void setDateText(QString d);

    void updatedateText();

    int topMargin();
    void setTopMargin(int m);

    bool fromMe();
    void setFromMe(bool me);

    bool isJustDate();
    void setIsJustDate(bool i);

    virtual void send(QString contactId);
signals:
    void idChanged();
    void chatIdChanged();
    void contentChanged();
    void userIdChanged();
    void dateChanged();
    void statusChanged();
    void dateTextChanged();
    void topMarginChanged();
    void fromMeChanged();
    void isJustDateChanged();

    void postSendSucceed();

private:
    QString m_Id;
    QString m_ChatId;
    QString m_Content;
    QString m_UserId;
    QDateTime m_Date;
    TalkStatus::TalkStatusEnum m_Status;
    bool m_ResendingStatusRequestDone;
    QString m_DateText;
    PersianDateTime* m_PersianDateTime;
    int m_TopMargin;
    bool m_FromMe;
    bool m_IsJustDate;
};

#endif // POSTBASE_H
