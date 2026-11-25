#ifndef CAPTHAMANAGER_H
#define CAPTHAMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<imageutility.h>
#include<QNetworkReply>
#include<QJsonDocument>
#include<QJsonObject>
#include<QImage>


class CapthaManager : public JooyaNetwork
{
    Q_OBJECT

    Q_PROPERTY(QString capthaHash READ capthaHash WRITE setCapthaHash NOTIFY capthaHashChanged)
//    Q_PROPERTY(QImage* captha READ captha WRITE setCaptha NOTIFY capthaChanged)
public:
    explicit CapthaManager(QObject *parent = nullptr);

    Q_INVOKABLE void loadCaptha();

//    QImage* captha();
    void setCaptha(QImage *p);

    QString capthaHash();
    void setCapthaHash(QString p);

signals:
    void capthaHashChanged();
    void capthaChanged(QImage argCaptha);
public slots:
private slots:
    void loadCapthaFinished();
private:

    QString m_CapthaHash;
    QImage* m_Captha;
};

#endif // CAPTHAMANAGER_H
