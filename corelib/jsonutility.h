#ifndef JSONUTILITY_H
#define JSONUTILITY_H

#include <QObject>
#include<QNetworkReply>
#include<QByteArray>
#include<QString>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonDocument>

class JsonUtility : public QObject
{
    Q_OBJECT
public:
    explicit JsonUtility(QObject *parent = nullptr);

    QJsonObject convertToJsonObject(QByteArray response);
    QJsonObject convertToJsonObject(QString response);
    QJsonObject convertToJsonObject(QNetworkReply *r);
    QJsonObject convertToJsonObject(QJsonValue jsonValue);
    QString convertToJsonString(QByteArray response);
    QString convertToJsonString(QString response);
    QString convertToJsonString(QJsonObject obj);

    QJsonArray convertToJsonArray(QByteArray response);
    QJsonArray convertToJsonArray(QString response);
signals:

};

#endif // JSONUTILITY_H
