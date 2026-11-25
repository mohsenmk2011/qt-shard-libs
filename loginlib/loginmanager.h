#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QObject>
#include <QString>
#include<QNetworkAccessManager>
#include<jooyanetwork.h>
#include<QStandardPaths>
#include<QNetworkReply>
#include<qurlquery.h>
#include<qsettings.h>
#include<qjsondocument.h>
#include<QJsonObject>
#include<QJsonValue>

#include<qnetworkrequest.h>
#include<jooyasettings.h>
#include<signupresult.h>
#include<loginstates.h>
#include<jooyanetworkengine.h>
#include<androidpermissionmanager.h>
#include<permissiontypes.h>
#include<smsmanager.h>
#include<QRegularExpression>
#include<QRegularExpressionMatchIterator>
#include<QRegularExpressionMatch>
class LoginManager : public JooyaNetwork
{
    Q_OBJECT

public:
    explicit LoginManager(QObject *parent = nullptr);

    void readAndSaveToken(QByteArray jsonToken);

    Q_INVOKABLE void login(QString un, QString pass);
    Q_INVOKABLE void loginUN(QString un, QString pass,QString captha,QString capthaHash);
    Q_INVOKABLE void logout();

    Q_INVOKABLE void signUp(QString un, QString pass, QString passRepeat, QString captha, QString capthaHash);    
    Q_INVOKABLE void signUp(QString phoneNumber, bool hasActivationCode=false);    

    Q_INVOKABLE void activate(QString phoneNumber, QString activationCode);

    Q_INVOKABLE void loginWithGoogle(const QString &idToken);

    Q_INVOKABLE void login(QString code);

signals:
    void signupSucceed();
    void signUpPhoneSucceed(SignupResult* result);
    void activationSucceed();
    void activationCodeReceived(const QString &activationCode);
    void googleLoginSucceed();
private slots:
    void loginFinished();
    void signUpFinished();
    void activateFinished();
    void signUpPhoneFinished();
    void googleLoginFinished();
    void onNewSmsReceived(const QString &sms);

private:
    SignupResult *readResult(QByteArray r);
    SmsManager* m_SmsManager;

};

#endif // LOGINMANAGER_H
