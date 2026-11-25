#include "userloginsettings.h"

UserLoginSettings::UserLoginSettings(QObject *parent) : JooyaSettings(parent)
{

}

QString UserLoginSettings::token()
{
    return get("token").toString();
}

void UserLoginSettings::setToken(QString t)
{
    set("token",t);
}
