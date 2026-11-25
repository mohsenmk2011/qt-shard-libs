#ifndef POST_H
#define POST_H

#include <QObject>
#include<postbase.h>

class Post : public PostBase
{
    Q_OBJECT
public:
    explicit Post(QObject *parent = nullptr);
    explicit Post(QJsonObject obj);
    explicit Post(QString userId, QString contactId, QString content);
    explicit Post(QDateTime date,bool isJustDate);
    //-----------------------------------------
    void send(QString contactId) override;
    void sendStatus(bool requestForResend=false);
    Q_INVOKABLE void sendSeenStatus();

    void deleteItem(bool deleteFromServer=false);

    void getStatus();
    //-----------------------------------------

    void fromJson(QJsonObject json) override;
    QJsonObject toJson() override;
    ///Is there a contact that not received this post?
    bool hasNotReceivedStatus();
    void save();
private slots:

    void onDeleteItem();
    void onGetStatus();
    void onSaveFinished();
signals:
    void deleteSucceed();

    void widthChanged();
    void heightChanged();
private:

    QJsonObject toJsonStatus();
};

#endif // POST_H
