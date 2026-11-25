#ifndef URLUTILITY_H
#define URLUTILITY_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QDebug>

class UrlUtility : public QObject
{
    Q_OBJECT
public:
    explicit UrlUtility(QObject *parent = nullptr);

    Q_INVOKABLE int getQueryValueAsInt(const QString& key, const QUrl& url);
    Q_INVOKABLE QUrl removeAllQueries(const QUrl& url);

signals:

};

#endif // URLUTILITY_H
