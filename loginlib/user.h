#ifndef USER_H
#define USER_H

#include <QObject>
#include<qdebug.h>
#include<QJsonObject>
#include<qjsondocument.h>
#include<QUrlQuery>
#include<rolelistmodel.h>
#include<jooyanetwork.h>
#include<QImage>
#include<QVariant>

class User : public JooyaNetwork
{
    Q_OBJECT

    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString registerDate READ registerDate WRITE setRegisterDate NOTIFY registerDateChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)

    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)


    Q_PROPERTY(QString referralCode READ referralCode WRITE setReferralCode NOTIFY referralCodeChanged)
    Q_PROPERTY(bool isSupporter READ isSupporter WRITE setIsSupporter NOTIFY isSupporterChanged)
    Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)

    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(bool gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(RoleListModel* roles READ roles CONSTANT)
public:
    explicit User(QObject *parent = nullptr);
    User(QString userId,QString un,QString rd);

    QString userId();
    void setUserId(QString i);

    QString registerDate();
    void setRegisterDate(QString rd);

    QString lastName();
    void setLastName(QString ln);

    QString firstName();
    void setFirstName(QString fn);

    QString displayName();
    void setDisplayName(QString dn);

    QString userName();
    void setUserName(QString un);

    QString referralCode();
    void setReferralCode(QString code);

    int score();
    void setScore(int s);

    bool isSupporter();
    void setIsSupporter(bool is);

    QString phoneNumber();
    void setPhoneNumber(QString pn);

    QString email();
    void setEmail(QString e);

    bool gender();
    void setGender(bool g);

    QImage image();
    void setImage(QImage img);

    RoleListModel* roles();
    //====================================
    ///نقشی هایی که کاربر کنونی دارد را می گیرد
    Q_INVOKABLE void getRoles();
    Q_INVOKABLE void addToRole(QString roleName);
    Q_INVOKABLE void removeFromRole(QString roleName);

    Q_INVOKABLE void setAsSupporter(bool isSupporter);

    Q_INVOKABLE void getReferralCode();
    Q_INVOKABLE void signup();
signals:
    void userIdChanged();
    void userNameChanged();
    void registerDateChanged();
    void lastNameChanged();
    void firstNameChanged();
    void referralCodeChanged();
    void scoreChanged();
    void isSupporterChanged();
    void displayNameChanged();
    void phoneNumberChanged();
    void emailChanged();
    void genderChanged();
    void profileChanged();
    void imageChanged();
    void referralInfoIsReady(QString referralLink,int clicks,int signedUps);
    void signupSucceed(QString userId);
private slots:
    void getRolesFinished();
    void addToRoleFinished();
    void removeFromRoleFinished();
    void onGetReferralCode();
    void onSetAsSupporter();
    void onSignup();
private:
    ///کاربر را از رشته جی سون مقدار دهی می کند
    void setFromJson(QString jsonUser);
    QString mId;
    QString m_RegisterDate;
    QString m_UserName;
    QString m_ReferralCode;
    bool m_IsSupporter;
    QString m_DisplayName;
    int m_Score;
    QString m_FirstName;
    QString m_LastName;
    QString m_PhoneNumber;
    QString m_Email;
    bool m_Gender;
    QImage m_Image;
    QByteArray m_ImageBytes;

    int m_ImageWidth;
    int m_ImageHeight;

    RoleListModel m_ListModel;
    QString m_CurrentRoleName;

    void readUserProfile(QString r);

    QJsonObject readFields();
    bool isFieldsValid();
    QJsonObject readProfileImage();

};

#endif // USER_H
