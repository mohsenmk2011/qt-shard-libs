#include "jsonutility.h"

JsonUtility::JsonUtility(QObject *parent)
    : QObject{parent}
{

}

QJsonObject JsonUtility::convertToJsonObject(QJsonValue jsonValue)
{
    return jsonValue.toObject();
}

QString JsonUtility::convertToJsonString(QByteArray response)
{
    QJsonDocument doc=QJsonDocument::fromJson(response);
    return  doc.toJson(QJsonDocument::Compact);
}

QString JsonUtility::convertToJsonString(QString response)
{
    return convertToJsonString(response.toUtf8());
}

QString JsonUtility::convertToJsonString(QJsonObject obj)
{
    QJsonDocument doc(obj);
    return doc.toJson(QJsonDocument::Compact);
}

QJsonObject JsonUtility::convertToJsonObject(QNetworkReply* r)
{
    return convertToJsonObject(r->readAll());
}
QJsonObject JsonUtility::convertToJsonObject(QByteArray response)
{
    QJsonDocument doc=QJsonDocument::fromJson(response);
    return doc.object();
}

QJsonObject JsonUtility::convertToJsonObject(QString response)
{
    return convertToJsonObject(response.toUtf8());
}

QJsonArray JsonUtility::convertToJsonArray(QByteArray response)
{
    QJsonDocument doc=QJsonDocument::fromJson(response);
    return doc.array();
}

QJsonArray JsonUtility::convertToJsonArray(QString response)
{
    return convertToJsonArray(response.toUtf8());
}
