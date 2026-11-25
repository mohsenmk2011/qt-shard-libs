#include "googleauth.h"

GoogleAuth *GoogleAuth::m_instance = nullptr;

GoogleAuth::GoogleAuth(QObject *parent)
    : JooyaNetwork{parent}
{
    m_instance = this;
}

#if defined(Q_OS_ANDROID)

GoogleAuth::~GoogleAuth()
{

}

static void idTokenReceivedFromJava(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString idToken = env->GetStringUTFChars(value, nullptr);
    qDebug()<<"***[ google signing step 5: signIn succeed";
    qInfo() << "***[ jooya google id_token received from java ]***" << (idToken.size() > 20 ? "yes" : "no");
    if (GoogleAuth::instance() == nullptr) {
        qWarning() << "***[ jooya no instance of GoogleAuth, drop id_token ]***";
        return;
    }
    qDebug()<<"***[ google signing step 5: send it to qml singing page";
    emit GoogleAuth::instance()->idTokenReady(idToken);
}

static void signInFailedFromJava(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString message = env->GetStringUTFChars(value, nullptr);
    qDebug()<<"***[ google signing step 5: signIn failed";
    qWarning() << "***[ google signing step 5: signIn failed => message ]***" << message;
    if (GoogleAuth::instance() == nullptr) {
        return;
    }
    emit GoogleAuth::instance()->signInFailed(message);
}

void GoogleAuth::registerNativesMethod()
{
    JNINativeMethod methods[] {
        {"sendIdTokenToQtApp", "(Ljava/lang/String;)V", reinterpret_cast<void *>(idTokenReceivedFromJava)},
        {"sendSignInErrorToQtApp", "(Ljava/lang/String;)V", reinterpret_cast<void *>(signInFailedFromJava)},
    };
    QString className = PackageInfoManager::getPackageName() + "GoogleSignInManager";
    QJniObject javaClass(className.toUtf8());
    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

void GoogleAuth::signIn(QString googleClientId,QString googleClientSecret)
{
    qDebug() << "***[ google signing step 2: is calling java GoogleSignInManager.signIn ]***";
    QString className = PackageInfoManager::getPackageName() + "GoogleSignInManager";
    QJniObject::callStaticMethod<void>(className.toUtf8(),
                                       "signIn",
                                       "(Landroid/content/Context;Ljava/lang/String;)V",
                                       QNativeInterface::QAndroidApplication::context(),QJniObject::fromString(googleClientId).object<jstring>());
}

#else // desktop

GoogleAuth::~GoogleAuth()
{
    if (m_replyHandler) m_replyHandler->deleteLater();
    if (m_oauthFlow) m_oauthFlow->deleteLater();
}

void GoogleAuth::registerNativesMethod()
{
    // nothing to do on desktop
}

void GoogleAuth::signIn(QString googleClientId,QString googleClientSecret)
{
    qDebug()<<"m_clientId ==> "<<googleClientId;
    if (googleClientId.isEmpty()) {
        qWarning() << "GoogleAuth: clientId is empty";
        emit signInFailed("شناسه کلاینت گوگل تنظیم نشده است");
        return;
    }
    setIsProcssing(true);
    qDebug() << "***[ google signing step 2: start desktop flow ]***";
    startDesktopFlow(googleClientId,googleClientSecret);
}

void GoogleAuth::startDesktopFlow(QString clientId,QString clientSecret)
{
    if (m_replyHandler) {
        m_replyHandler->deleteLater();
        m_replyHandler = nullptr;
    }
    if (m_oauthFlow) {
        m_oauthFlow->deleteLater();
        m_oauthFlow = nullptr;
    }

    m_oauthFlow = new QOAuth2AuthorizationCodeFlow(this);
    m_oauthFlow->setAuthorizationUrl(QUrl("https://accounts.google.com/o/oauth2/auth"));
    m_oauthFlow->setAccessTokenUrl(QUrl("https://oauth2.googleapis.com/token"));
    m_oauthFlow->setClientIdentifier(clientId);
    m_oauthFlow->setClientIdentifierSharedKey(clientSecret);
    m_oauthFlow->setScope("openid email profile");
    m_oauthFlow->setPkceMethod(QOAuth2AuthorizationCodeFlow::PkceMethod::S256);
    m_replyHandler = new QOAuthHttpServerReplyHandler(1270, this); // loopback redirect
    m_oauthFlow->setReplyHandler(m_replyHandler);

    QObject::connect(m_oauthFlow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
                     &QDesktopServices::openUrl);

    QObject::connect(m_oauthFlow, &QOAuth2AuthorizationCodeFlow::granted, this, [this]() {
        qInfo()<<"google signing step 4 ";
        // id_token arrives as part of the token response when scope contains "openid"
        const QString idToken = m_oauthFlow->extraTokens().value("id_token").toString();
        if (idToken.isEmpty()) {
            qWarning() << "GoogleAuth: no id_token in token response";
            emit signInFailed("توکن گوگل دریافت نشد");
            return;
        }
        qInfo()<<"google signing step 4 => grant succeed(id token received from google) => send id token to qml signing page";
        emit idTokenReady(idToken);
        setIsProcssing(false);
    });

    QObject::connect(m_oauthFlow, &QOAuth2AuthorizationCodeFlow::error, this, [this](const QString &error, const QString &errorDescription, const QUrl &uri) {
        qCritical()<<"google signing step 4 => grant failed";
        qWarning() << "GoogleAuth error:" << error << errorDescription << uri;
        emit signInFailed(errorDescription.isEmpty() ? error : errorDescription);
        setIsProcssing(false);
    });

    qDebug()<<"google signing step 3 => start grant";
    m_oauthFlow->grant();
}

#endif // !Q_OS_ANDROID
