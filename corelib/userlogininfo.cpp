#include "userlogininfo.h"

UserLoginInfo::UserLoginInfo(QObject *parent) : QObject(parent)
{    
    qInfo()<<"=>>>[ Initialization User Login Info ]<<<=";
    m_Role=UserRoles::UserRolesEnum::Guest;
    m_LoginState=LoginStates::LoginStatesEnum::LoggedOut;
    m_IsLoggedIn=false;
    m_IsAnyAdmin=false;
    m_IsAdmin=false;
    m_IsPaid=false;
}
///// بر اساس اینکه توکن در تنظیمات ذخیره شده یا نه لاگین استیت را رفرش می کند
void UserLoginInfo::initialState()
{
    QString t=this->token();
    bool tokenIsNull=t.isNull()||t.isEmpty();
    if(tokenIsNull){
        qDebug()<<"Token Is Null-> Initializing State to LoggedOut";
        m_LoginState=LoginStates::LoginStatesEnum::LoggedOut;
    }
    else {
        qDebug()<<"Token Is not Null-> Initializing State to LoggedIn";
        m_LoginState=LoginStates::LoginStatesEnum::LoggedIn;
    }
    m_IsLoggedIn=m_LoginState==LoginStates::LoginStatesEnum::LoggedIn;
}

QString UserLoginInfo::token()
{
    UserLoginSettings js;
    return js.token();
}

void UserLoginInfo::setToken(QString t)
{
    UserLoginSettings sm;
    sm.setToken(t);
    if(t.isNull()||t.isEmpty()){
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!! Is setting empty Token !!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qWarning()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    }
}

UserRoles::UserRolesEnum UserLoginInfo::role()
{
    return m_Role;
}

void UserLoginInfo::setRole(UserRoles::UserRolesEnum r)
{
    m_Role=r;
    setIsAdmin(m_Role==UserRoles::UserRolesEnum::Admin);
    setIsAnyAdmin(m_Role==UserRoles::UserRolesEnum::Admin||m_Role==UserRoles::UserRolesEnum::Admin2);
}

bool UserLoginInfo::isLoggedIn()
{
    return m_IsLoggedIn;
}

void UserLoginInfo::setIsLoggedIn(bool isLoggedIn)
{
    if(m_IsLoggedIn!=isLoggedIn){
        m_IsLoggedIn=isLoggedIn;
        emit isLoggedInChanged();
    }
}

bool UserLoginInfo::isAdmin()
{
    return m_IsAdmin;
}

void UserLoginInfo::setIsAdmin(bool isAdmin)
{
    if(m_IsAdmin!=isAdmin){
        m_IsAdmin=isAdmin;
        emit isAdminChanged();
    }
}

bool UserLoginInfo::isAnyAdmin()
{
    return m_IsAnyAdmin;
}

void UserLoginInfo::setIsAnyAdmin(bool isAnyAdmin)
{
    if(m_IsAnyAdmin!=isAnyAdmin){
        m_IsAnyAdmin=isAnyAdmin;
        emit isAnyAdminChanged();
    }
}

LoginStates::LoginStatesEnum UserLoginInfo::state()
{
    return m_LoginState;
}

void UserLoginInfo::setState(LoginStates::LoginStatesEnum loginState)
{
    if(m_LoginState!=loginState){
        m_LoginState=loginState;
        setIsLoggedIn(m_LoginState==LoginStates::LoginStatesEnum::LoggedIn);
        emit stateChanged(loginState);
    }
}
