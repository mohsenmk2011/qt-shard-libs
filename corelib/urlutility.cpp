#include "urlutility.h"

UrlUtility::UrlUtility(QObject *parent)
    : QObject{parent}
{

}

int UrlUtility::getQueryValueAsInt(const QString &key, const QUrl &url)
{
    QUrlQuery query(url);
    QString value = query.queryItemValue(key);
    return value.toInt();
}

QUrl UrlUtility::removeAllQueries(const QUrl &url)
{
    qDebug()<<"current url=> "<<url;
    QUrl urlWithoutQuery(url);
    if (!urlWithoutQuery.query().isEmpty()) {
        urlWithoutQuery.setUrl(urlWithoutQuery.toString(QUrl::RemoveQuery));
    }

    qDebug()<<"urlWithoutQuery => "<<urlWithoutQuery;
    return urlWithoutQuery;
}
