#ifndef JOOYANETWORKACCESSMANAGER_H
#define JOOYANETWORKACCESSMANAGER_H

#include <QObject>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QUrl>
#include<QString>

class JooyaNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit JooyaNetworkAccessManager(QObject *parent = nullptr);

    QNetworkReply* get(const QNetworkRequest &request);
signals:
    void replyAvailable(QByteArray reponse);
private slots:
    void requestFinished(QNetworkReply *reply);
};

#endif // JOOYANETWORKACCESSMANAGER_H
