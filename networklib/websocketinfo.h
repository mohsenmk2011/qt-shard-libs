#ifndef WEBSOCKETINFO_H
#define WEBSOCKETINFO_H

#include <QObject>
#include<QJsonObject>
#include<QJsonDocument>

class WebSocketInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString information READ information WRITE setInformation NOTIFY informationChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString senderId READ senderId WRITE setSenderId NOTIFY senderIdChanged)
    Q_PROPERTY(QString receiverId READ receiverId WRITE setReceiverId NOTIFY receiverIdChanged)

public:
    explicit WebSocketInfo(QObject *parent = nullptr);

    void setInformation(QString info);
    QString information();

    void setType(QString t);
    QString type();

    QString senderId();
    void setSenderId(QString c);

    QString receiverId();
    void setReceiverId(QString r);

    QString toJson();
    void fromJson(QString json);

signals:
    void informationChanged();
    void typeChanged();
    void senderIdChanged();
    void receiverIdChanged();
private:
    QString m_Info;
    QString m_Type;
    QString m_SenderId;
    QString m_ReceiverId;

};

#endif // WEBSOCKETINFO_H
