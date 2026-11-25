#ifndef GOOGLEAUTH_H
#define GOOGLEAUTH_H

#include <QObject>
#include <QString>
#include <QtDebug>
#include<jooyanetwork.h>

#if defined(Q_OS_ANDROID)
#include <QCoreApplication>
#include <QJniEnvironment>
#include <QJniObject>
#include <packageinfomanager.h>
#else
#include <QtNetworkAuth/QOAuth2AuthorizationCodeFlow>
#include <QtNetworkAuth/QOAuthHttpServerReplyHandler>
#include <QDesktopServices>
#include <QUrlQuery>
#endif

/**
 * @brief Obtains a Google id_token on desktop and Android.
 *
 * Desktop: QtNetworkAuth authorization-code flow with a loopback redirect,
 *          id_token is extracted from the token response (scope: openid email profile).
 * Android: calls GoogleSignInManager.java (Credential Manager / Google Identity Services)
 *          through JNI; the java side calls back sendIdTokenToQtApp(idToken).
 *
 * On success the idTokenReady(idToken) signal is emitted; connect it to
 * LoginManager::loginWithGoogle(idToken).
 */
class GoogleAuth : public JooyaNetwork
{
    Q_OBJECT
public:
    explicit GoogleAuth(QObject *parent = nullptr);
    ~GoogleAuth() override;

    Q_INVOKABLE void signIn(QString googleClientId,QString googleClientSecret);

    static GoogleAuth *instance() { return m_instance; }
    void registerNativesMethod();

signals:
    void idTokenReady(const QString &idToken);
    void signInFailed(const QString &message);

private:
#if !defined(Q_OS_ANDROID)
    void startDesktopFlow(QString clientId,QString clientSecret);
#endif
    static GoogleAuth *m_instance;
#if !defined(Q_OS_ANDROID)
    QOAuth2AuthorizationCodeFlow *m_oauthFlow = nullptr;
    QOAuthHttpServerReplyHandler *m_replyHandler = nullptr;
#endif
};

#endif // GOOGLEAUTH_H
