#ifndef USERLOGININFO_H
#define USERLOGININFO_H

#include <QObject>
#include<loginstates.h>
#include<userloginsettings.h>
#include<QString>
#include<userroles.h>
#include <QQmlEngine>
#include<QtQml>

class UserLoginInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isLoggedIn READ isLoggedIn WRITE setIsLoggedIn NOTIFY isLoggedInChanged)
    Q_PROPERTY(bool isAdmin READ isAdmin WRITE setIsAdmin NOTIFY isAdminChanged)
    Q_PROPERTY(bool isAnyAdmin READ isAnyAdmin WRITE setIsAnyAdmin NOTIFY isAnyAdminChanged)
    Q_PROPERTY(LoginStates::LoginStatesEnum state READ state WRITE setState NOTIFY stateChanged)    
    QML_ELEMENT
public:
    explicit UserLoginInfo(QObject *parent = nullptr);

    bool isLoggedIn();
    void setIsLoggedIn(bool isLoggedIn);

    bool isAdmin();
    void setIsAdmin(bool isAdmin);
    ///آیا یکی از انواع ادمین هاست؟
    bool isAnyAdmin();
    void setIsAnyAdmin(bool isAnyAdmin);

    LoginStates::LoginStatesEnum state();
    void setState(LoginStates::LoginStatesEnum state);

    QString token();
    void setToken(QString t);

    UserRoles::UserRolesEnum role();
    void setRole(UserRoles::UserRolesEnum r);

    void initialState();
signals:
    void isLoggedInChanged();
    void isAdminChanged();
    void isAnyAdminChanged();
    void stateChanged(LoginStates::LoginStatesEnum loginState);
public slots:
private:
    LoginStates::LoginStatesEnum m_LoginState;
    bool m_IsPaid;
    bool m_IsAdmin;
    bool m_IsAnyAdmin;
    bool m_IsLoggedIn;
    UserRoles::UserRolesEnum m_Role;
};

#endif // USERLOGININFO_H
