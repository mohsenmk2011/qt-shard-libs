#include "jooyanetworkaccessfactory.h"

JooyaNetworkAccessManager *JooyaNetworkAccessFactory::create(QObject *parent)
{
    return new JooyaNetworkAccessManager(parent);
}

