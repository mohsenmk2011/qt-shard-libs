#ifndef BEHPARDAKHTSETTINGMANAGER_H
#define BEHPARDAKHTSETTINGMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<QJsonObject>
#include<qdebug.h>

class BehpardakhtSetting : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(int terminalId READ terminalId WRITE setTerminalId NOTIFY terminalIdChanged)
    Q_PROPERTY(int payerId READ payerId WRITE setPayerId NOTIFY payerIdChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString additionalData READ additionalData WRITE setAdditionalData NOTIFY additionalDataChanged)
    Q_PROPERTY(QString termainalUrl READ termainalUrl WRITE setTermainalUrl NOTIFY termainalUrlChanged)
    Q_PROPERTY(QString callBackUrl READ callBackUrl WRITE setCallBackUrl NOTIFY callBackUrlChanged)

public:
    explicit BehpardakhtSetting(QObject *parent = nullptr);

    int terminalId();
    int payerId();
    bool enabled();
    QString userName();
    QString password();
    QString additionalData();
    QString termainalUrl();
    QString callBackUrl();

    void setTerminalId(int v);
    void setPayerId(int v);
    void setEnabled(bool v);
    void setUserName(QString v);
    void setPassword(QString v);
    void setAdditionalData(QString v);
    void setTermainalUrl(QString v);
    void setCallBackUrl(QString v);

    Q_INVOKABLE void load();
    Q_INVOKABLE void save();

signals:
    void terminalIdChanged();
    void payerIdChanged();
    void enabledChanged();
    void userNameChanged();
    void passwordChanged();
    void additionalDataChanged();
    void termainalUrlChanged();
    void callBackUrlChanged();

private slots:
    void loadFinished();
    void saveFinished();
private:
    QJsonObject readFeilds();
    int m_terminalId;
    int m_payerId;
    bool m_enabled;
    QString m_userName;
    QString m_password;
    QString m_additionalData;
    QString m_termainalUrl;
    QString m_callBackUrl;
};

#endif // BEHPARDAKHTSETTINGMANAGER_H
