#ifndef CURRENTAPPLICATIONHELPER_H
#define CURRENTAPPLICATIONHELPER_H

#include <QObject>
#include<QtQml>

class CurrentApplicationHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool hasChat READ hasChat WRITE setHasChat NOTIFY hasChatChanged FINAL)
    Q_PROPERTY(bool hasSignup READ hasSignup WRITE setHasSignup NOTIFY hasSignupChanged FINAL)
    Q_PROPERTY(QString googleClientId READ googleClientId WRITE setGoogleClientId NOTIFY googleClientIdChanged FINAL)
    Q_PROPERTY(QString googleClientSecret READ googleClientSecret WRITE setGoogleClientSecret NOTIFY googleClientSecretChanged FINAL)
    QML_ANONYMOUS
public:
    explicit CurrentApplicationHelper(QObject *parent = nullptr);

    const QString &name() const;
    void setName(const QString &newName);

    bool hasChat() const;
    void setHasChat(bool newHasChat);

    bool hasSignup() const;
    void setHasSignup(bool newHasSignup);

    QString googleClientId() const;
    void setGoogleClientId(const QString &newGoogleClientId);

    QString googleClientSecret() const;
    void setGoogleClientSecret(const QString &newGoogleClientSecret);

signals:

    void nameChanged();
    void hasChatChanged();

    void hasSignupChanged();

    void googleClientIdChanged();

    void googleClientSecretChanged();

private:
    QString m_name;
    bool m_hasChat;
    bool m_hasSignup;
    QString m_googleClientId;
    QString m_googleClientSecret;
};

#endif // CURRENTAPPLICATIONHELPER_H
