#ifndef NEWCONNECTIONMODEL_H
#define NEWCONNECTIONMODEL_H

#include <QObject>
#include<QJsonObject>

class NewConnectionModel : public QObject
{
    Q_OBJECT
public:
    explicit NewConnectionModel(QObject *parent = nullptr);
    explicit NewConnectionModel(QJsonObject obj);

    bool isAdded();
    QString userId();
    int onlineUsersCount();

signals:
private:
    bool m_IsAdded;
    QString m_UserId;
    int m_OnlineUsersCount;
};

#endif // NEWCONNECTIONMODEL_H
