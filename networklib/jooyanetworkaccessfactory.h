#ifndef JOOYANETWORKACCESSFACTORY_H
#define JOOYANETWORKACCESSFACTORY_H

#include<QQmlNetworkAccessManagerFactory>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<jooyanetworkaccessmanager.h>
class JooyaNetworkAccessFactory : public QQmlNetworkAccessManagerFactory
{
public:
    JooyaNetworkAccessManager *create(QObject *parent) override;

private:
};

#endif // JOOYANETWORKACCESSFACTORY_H
