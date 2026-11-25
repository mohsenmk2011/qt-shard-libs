#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include<QtQml/QQmlApplicationEngine>
#include<QNetworkReply>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include <qurlquery.h>
#include<QSettings>
#include<QString>
#include<QByteArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<qurl.h>
#include<jooyanetworkengine.h>
#include<userroles.h>
#include<jooyasettings.h>
#include<websockethandler.h>
#include<datetimeutility.h>
#include<headercontenttypes.h>

class JooyaNetwork : public JooyaNetworkEngine
{
    Q_OBJECT

public:
    explicit JooyaNetwork(QObject *parent = nullptr);

    QUrl setUrl(QString url, bool useApiUrl=false, bool isFullUrl=false);
    QUrl url();

    void showBadMessage(QByteArray replyMessage);
    void showOkMessage(QString replyMessage);
    void showMessage(QNetworkReply* reply);
    void showMessage(QObject* obj);

    QNetworkReply* getRequest(QString url, bool useApiUrl=false, bool isFullUrl=false);
    void getAndReturnObject(QString url);

    void setRequestHeaderType(HeaderContentTypes::HeaderContentTypesEnum headerContentType = HeaderContentTypes::HeaderContentTypesEnum::Json,QString boundary ="");

    QNetworkRequest m_Request;
    QNetworkAccessManager m_NetworkManager;
    QNetworkReply *convertToReply(QObject *obj);
    bool isNotFound(QNetworkReply *r);
    //    QNetworkReply *postRequest(QString url, QByteArray data);
    QNetworkReply *postRequest(QString url, QJsonObject obj, bool useApiUrl=false, bool isFullUrl=false);
    void post(QString url, QJsonObject obj);
    QNetworkReply * post(QString url, QHttpMultiPart *multiPart);
    void postAndReturnObject(QString url, QJsonObject obj);
    QNetworkReply *postRequest(QString url, QUrlQuery query, bool useApiUrl=false, bool isFullUrl=false);
    QNetworkReply *deleteRequest(QString url,bool useApiUrl=false);
    QNetworkReply *putRequest(QString url, QJsonObject obj);
    QUrl setFullUrl(QString url);

    int getHttpCode(QNetworkReply *reply);
    static WebSocketHandler* m_WebSocketHandler;
    DateTimeUtility m_DateTimeUtility;
signals:
    void unAuthorizedAccess();
    void tokenChanged();
    void connectionError();
    void pageManagerChanged();
    void requestFinished(bool isSucceed,OperationTypes::OperationTypesEnum operation);
    void requestSucceedWithObject(QJsonObject obj);
    void requestSucceedWithArray(QJsonArray array);

private:
    void checkCommonErrors(QNetworkReply *r);
    bool isAcceptedResposeCode(int code);
    QString currentUrl;
    QString removeQuotationMarks(QString m);
public slots:
    void setRequestHeader(QString headerName="",QString headerValue="",HeaderContentTypes::HeaderContentTypesEnum headerContentType=HeaderContentTypes::HeaderContentTypesEnum::Json);
private slots:
    void updateRequestHeader();
    virtual void currentReplyFinished(QNetworkReply *r);
    void onRequestFinished();
    void onRequestFinishedReturnObject();
};

#endif // NETWORKMANAGER_H
