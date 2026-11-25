#include "newconnectionmodel.h"

NewConnectionModel::NewConnectionModel(QObject *parent)
    : QObject{parent}
{

}

NewConnectionModel::NewConnectionModel(QJsonObject obj)
{
    m_UserId=obj.value("userId").toString();
    m_IsAdded=obj.value("isAdded").toBool();
    m_OnlineUsersCount=obj.value("onlineUsersCount").toInt();
}

bool NewConnectionModel::isAdded()
{
    return m_IsAdded;
}

QString NewConnectionModel::userId()
{
    return m_UserId;
}

int NewConnectionModel::onlineUsersCount()
{
    return m_OnlineUsersCount;
}
