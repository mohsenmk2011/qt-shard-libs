#ifndef LOGINLIB_H
#define LOGINLIB_H

#include<QtQml/QQmlApplicationEngine>
#include<baseuser.h>
#include<capthamanager.h>
#include<googleauth.h>
#include<loginmanager.h>
#include<usermanager.h>
#include<user.h>
#include<userimage.h>
#include<role.h>
#include<rolemanager.h>
#include<userprofile.h>
#include<signupresult.h>

class Loginlib
{
public:
    Loginlib();
    static void registerTypes()
    {
        qmlRegisterType<BaseUser>("Jooya",1,0,"BaseUser");
        qmlRegisterType<LoginManager>("Jooya",1,0,"LoginManager");
        qmlRegisterType<CapthaManager>("Jooya",1,0,"CapthaManager");
        qmlRegisterType<GoogleAuth>("Jooya",1,0,"GoogleAuth");
        qmlRegisterType<UserManager>("Jooya",1,0,"UserManager");
        qmlRegisterType<User>("Jooya",1,0,"User");
        qmlRegisterType<Role>("Jooya",1,0,"Role");
        qmlRegisterType<RoleManager>("Jooya",1,0,"RoleManager");
        qmlRegisterType<SignupResult>("Jooya",1,0,"SignupResult");
        qmlRegisterType<UserImage>("Jooya",1,0,"UserImage");
        qmlRegisterType<UserProfile>("Jooya",1,0,"UserProfile");
        qmlRegisterType<UserImageListModel>("Jooya",1,0,"UserImageListModel");

    }
};

#endif // LOGINLIB_H
