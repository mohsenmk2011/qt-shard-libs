#ifndef BASEUSER_H
#define BASEUSER_H

#include<QObject>
#include<jooyanetwork.h>
#include<applicationsettings.h>
#include<applicationpath.h>
#include<imageutility.h>
#include<userimage.h>
#include<userroles.h>
#include<imagefile.h>
#include<QJsonDocument>
#include<QJsonObject>

class BaseUser : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(UserImage* lastImage READ lastImage CONSTANT)
    Q_PROPERTY(bool hasImage READ hasImage WRITE setHasImage NOTIFY hasImageChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged)

public:
    explicit BaseUser(QObject *parent = nullptr);

    QString displayName();
    void setDisplayName(QString l);

    QString userName();
    void setUserName(QString un);

    QString firstName();
    void setFirstName(QString name);

    QString lastName();
    void setLastName(QString name);

    QString city();
    void setCity(QString c);

    bool hasImage();
    void setHasImage(bool hi);

    Q_INVOKABLE bool isNameIsDefault();

    UserImage *lastImage();

    void fromJson(QJsonObject json) override;
    QJsonObject toJson() override;
    //========================================

    void load();

    ///loads user info from server
    Q_INVOKABLE void getUserInfo(bool refreshImage=false);
    Q_INVOKABLE void getLastImage();

    //Q_INVOKABLE void resetExistanceCheckedUserImage();
    void deleteUserImages();
signals:
    void userNameChanged();
    void displayNameChanged();
    void hasImageChanged();
    void userInfoLoadedFromSettings();

    void firstNameChanged();
    void lastNameChanged();
    void cityChanged();
private slots:
    void onGetUserInfo();
    void getLastImageFinished();
    void userLoginStateChanged(LoginStates::LoginStatesEnum s);

    //virtual void userLoginStateChanged(LoginStates::LoginStatesEnum s);

private:
    ApplicationSettings appSettings;
    QString m_UserName;
    QString m_DisplayName;
    QString m_FirstName;
    QString m_LastName;
    QString m_City;
    UserImage m_LastImage;
    bool m_CheckedLastImage;
    bool m_HasImage;
    //void readLastImageProfile(QString res);
    //bool refreshLastUserImagePath();
    void setInfo(QString name="کاربر مهمان", QString userName="Guest", UserRoles::UserRolesEnum role=UserRoles::UserRolesEnum::Guest);
};
#endif // BASEUSER_H
