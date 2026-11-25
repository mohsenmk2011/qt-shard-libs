#include "currentapplicationhelper.h"

CurrentApplicationHelper::CurrentApplicationHelper(QObject *parent)
    : QObject{parent}
{

}

const QString &CurrentApplicationHelper::name() const
{
    return m_name;
}

void CurrentApplicationHelper::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

bool CurrentApplicationHelper::hasChat() const
{
    return m_hasChat;
}

void CurrentApplicationHelper::setHasChat(bool newHasChat)
{
    if (m_hasChat == newHasChat)
        return;
    m_hasChat = newHasChat;
    emit hasChatChanged();
}

bool CurrentApplicationHelper::hasSignup() const
{
    return m_hasSignup;
}

void CurrentApplicationHelper::setHasSignup(bool newHasSignup)
{
    if (m_hasSignup == newHasSignup)
        return;
    m_hasSignup = newHasSignup;
    emit hasSignupChanged();
}

QString CurrentApplicationHelper::googleClientId() const
{
    return m_googleClientId;
}

void CurrentApplicationHelper::setGoogleClientId(const QString &newGoogleClientId)
{
    if (m_googleClientId == newGoogleClientId)
        return;
    m_googleClientId = newGoogleClientId;
    emit googleClientIdChanged();
}

QString CurrentApplicationHelper::googleClientSecret() const
{
    return m_googleClientSecret;
}

void CurrentApplicationHelper::setGoogleClientSecret(const QString &newGoogleClientSecret)
{
    if (m_googleClientSecret == newGoogleClientSecret)
        return;
    m_googleClientSecret = newGoogleClientSecret;
    emit googleClientSecretChanged();
}
