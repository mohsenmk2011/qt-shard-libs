#ifndef APPINTRODUCE_H
#define APPINTRODUCE_H

#include <QObject>
#include<qdebug.h>
#include<jooyanetwork.h>
#include<qbytearray.h>
#include<imageutility.h>
#include<QDateTime>
#include<file.h>
#include<applicationpath.h>
#include<keywordtypelistmodel.h>
#include<keyword.h>
#include<notificationtypes.h>
#include<imagefile.h>
#include<applicationpath.h>

class Notify : public ImageFile
{
    Q_OBJECT
    Q_PROPERTY(KeywordTypeListModel* keywords READ keywords CONSTANT)
    Q_PROPERTY(Keyword* selectedKeyword READ selectedKeyword WRITE setSelectedKeyword/* NOTIFY selectedKeywordChanged*/)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool visible READ visible WRITE setBeVisibleForUsers NOTIFY beVisibleForUsersChanged)
    Q_PROPERTY(int amount READ amount WRITE setAmount NOTIFY amountChanged)
    Q_PROPERTY(QDateTime endDate READ endDate WRITE setEndDate NOTIFY endDateChanged)
    Q_PROPERTY(QString endDateString READ endDateString WRITE setEndDateString NOTIFY endDateStringChanged)
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(QString dateString READ dateString WRITE setDateString NOTIFY dateStringChanged)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(QString moreInfoLink READ moreInfoLink WRITE setMoreInfoLink NOTIFY moreInfoLinkChanged)
    Q_PROPERTY(NotificationTypes::NotificationTypesEnum type READ type WRITE setType NOTIFY typeChanged)

public:
    explicit Notify(QObject *parent = nullptr);
    explicit Notify(NotificationTypes::NotificationTypesEnum type);
    explicit Notify(QJsonObject obj);

    QString title();
    void setTitle(QString t);

    QString description();
    void setDescription(QString d);

    bool visible();
    void setBeVisibleForUsers(bool visible);

    int amount();
    void setAmount(int a);

    QDateTime date();
    void setDate(QDateTime d);

    QString dateString();
    void setDateString(QString d);

    QDateTime endDate();
    void setEndDate(QDateTime ed);

    QString endDateString();
    void setEndDateString(QString e);

    int duration();
    void setDuration(int d);

    NotificationTypes::NotificationTypesEnum type();
    void setType(NotificationTypes::NotificationTypesEnum t);

    QString moreInfoLink();
    void setMoreInfoLink(QString link);
    Keyword* selectedKeyword();
    void setSelectedKeyword(Keyword* sk);

    KeywordTypeListModel* keywords();

    Q_INVOKABLE void save();
    Q_INVOKABLE void load(int id);
    Q_INVOKABLE void deleteItem();
    Q_INVOKABLE void loadKeywords();
    Q_INVOKABLE void addKeyword(int keywordId);
    Q_INVOKABLE void removeKeyword(int keywordId);

    void loadFromJson(QJsonObject jobj);
signals:
    void titleChanged();
    void descriptionChanged();
    void beVisibleForUsersChanged();
    void amountChanged();
    void endDateChanged();
    void endDateStringChanged();
    void dateChanged();
    void dateStringChanged();
    void durationChanged();
    void moreInfoLinkChanged();
    void deleteSucceed();
    void typeChanged();
private slots:
    void onSaveFinished();
    void reqLoadFinished();
    void loadKeywordsFinished();
    void addKeywordFinished();
    void removeKeywordFinished();
    void onDeleteItemFinished();
private:
    Keyword* m_SelectedKeyword;
    QString m_EndDateString;
    QString m_DateString;
    QString m_Title;
    int m_Amount;
    QDateTime m_EndDate;
    QDateTime m_Date;
    int m_Duration;
    QString m_Description;
    bool m_Visible;
    QByteArray m_ImageBytes;
    QString m_MoreInfoLink;
    KeywordTypeListModel m_Keywords;
    NotificationTypes::NotificationTypesEnum m_Type;

    bool isFeildsValid();
    QJsonObject readFeilds();
    void reSetType(QString t);
};

#endif // APPINTRODUCE_H
